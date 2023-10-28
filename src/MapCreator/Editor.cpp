//
// Created by alexandre on 20/10/23.
//

#include "Editor.hpp"
#include <iostream>

Editor::Editor() {
    LoadAssets();
}

Editor::~Editor() {
    UnloadAssets();
}

void Editor::LoadFromJSON(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }
    nlohmann::json j;
    file >> j;

    if (j.find("mobs") != j.end() && j["mobs"].is_array()) {
        for (const auto& mob : j["mobs"]) {
            int tick = mob["tick"].get<int>();
            int x = (tick - 1) / 15;
            int y = std::round(mob["position"]["y"].get<float>() / TILE_SIZE);

            if (x >= 0 && x < GRID_WIDTH && y >= 0 && y < GRID_HEIGHT) {
                grid[x][y].type = StringToElementType(mob["mobType"].get<std::string>());
                grid[x][y].isPowerUp = mob["dropPowerup"].get<bool>();
            }
        }
    }

    showLoadPopup = true;
    loadPopupTimer = 0.0f;
}

void Editor::SaveToJSON(const std::string& filename) {
    nlohmann::json j;
    nlohmann::json mobs = nlohmann::json::array();

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            if (grid[x][y].type != ElementType::EMPTY) {
                nlohmann::json mob;

                mob["tick"] = (x * 15 + 1);
                mob["mobType"] = ElementTypeToString(grid[x][y].type);

                mob["position"]["x"] = 2000.0;
                mob["position"]["y"] = y * TILE_SIZE;

                mob["dropPowerup"] = grid[x][y].isPowerUp;

                mobs.push_back(mob);
            }
        }
    }

    j["mobs"] = mobs;

    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return;
    }

    std::cout << "Saving to file: " << filename << std::endl;
    file << j.dump(4);
    showSavePopup = true;
    savePopupTimer = 0.0f;
}

void Editor::LoadAssets() {
    for (const auto& element : ELEMENTS) {
        int index = static_cast<int>(element.type);
        sprites[index].texture = LoadTexture(element.path.c_str());
        sprites[index].frame = { 0, 0, static_cast<float>(sprites[index].texture.width), static_cast<float>(sprites[index].texture.height) };
    }
}

ElementType Editor::StringToElementType(const std::string& name) {
    for (const auto& element : ELEMENTS) {
        if (element.name == name) return element.type;
    }
    return ElementType::EMPTY;
}

std::string Editor::ElementTypeToString(ElementType type) {
    for (const auto& element : ELEMENTS) {
        if (element.type == type) return element.name;
    }
    return "unknown";
}


void Editor::UnloadAssets() {
    for (int i = static_cast<int>(ElementType::ELEMENT_1); i < static_cast<int>(ElementType::ELEMENT_COUNT); i++) {
        UnloadTexture(sprites[i].texture);
    }
    UnloadTexture(backgroundTexture);
}

Vector2 Editor::GetWorldPosition(Vector2 screenPosition, Camera2D camera) {
    Vector2 result;
    result.x = screenPosition.x / camera.zoom + camera.target.x - static_cast<float>(GetScreenWidth()) * 0.5f / camera.zoom;
    result.y = screenPosition.y / camera.zoom + camera.target.y - static_cast<float>(GetScreenHeight()) * 0.5f / camera.zoom;
    return result;
}

void Editor::Init() {
    TOOLBAR_HEIGHT = 0.1f * GetScreenHeight();
    float availableHeight = GetScreenHeight() - TOOLBAR_HEIGHT - SCALE_TEXT_HEIGHT;
    float TILE_SIZE_X = static_cast<float>(GetScreenWidth()) / VISIBLE_CELLS_X;
    float TILE_SIZE_Y = availableHeight / GRID_HEIGHT;
    TILE_SIZE = (TILE_SIZE_X < TILE_SIZE_Y) ? TILE_SIZE_X : TILE_SIZE_Y;

    hideShowButton = { 10, GetScreenHeight() - TOOLBAR_HEIGHT - 25, 50, 20 };

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            grid[x][y].type = ElementType::EMPTY;
            grid[x][y].isPowerUp = false;
        }
    }

    camera.target = {
            TILE_SIZE / 2 + GetScreenHeight() / 2,
            GRID_HEIGHT * TILE_SIZE / 2 + TOOLBAR_HEIGHT / 2 + SCALE_TEXT_HEIGHT / 2
    };
    camera.offset = { GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
}

void Editor::Update() {
    Vector2 mousePos = GetWorldPosition(GetMousePosition(), camera);
    int gridX = static_cast<int>(mousePos.x / TILE_SIZE);
    int gridY = static_cast<int>(mousePos.y / TILE_SIZE);

    if (IsKeyPressed(KEY_RIGHT)) camera.target.x += TILE_SIZE;
    if (IsKeyPressed(KEY_LEFT)) camera.target.x -= TILE_SIZE;

    if (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL)) {
        if (IsKeyPressed(KEY_S)) {
            SaveToJSON("config/map/namefile.json");
        }
        if (IsKeyPressed(KEY_L)) {
            LoadFromJSON("config/map/namefile.json");
        }
    }


    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (CheckCollisionPointRec(GetMousePosition(), hideShowButton)) {
            showGridLines = !showGridLines;
        } else if (GetMousePosition().y > GetScreenHeight() - TOOLBAR_HEIGHT) {
            int index = static_cast<int>(GetMousePosition().x / (TOOLBAR_HEIGHT + 10));
            if (index < static_cast<int>(ElementType::ELEMENT_COUNT) - 1) {
                currentSelection = static_cast<ElementType>(index + 1);
            }
        } else if (gridX >= 0 && gridX < GRID_WIDTH && gridY < GRID_HEIGHT) {
            if (grid[gridX][gridY].isPowerUp) {
                grid[gridX][gridY].type = ElementType::EMPTY;
                grid[gridX][gridY].isPowerUp = false;
            } else if (grid[gridX][gridY].type == currentSelection) {
                grid[gridX][gridY].isPowerUp = !grid[gridX][gridY].isPowerUp;
            } else {
                grid[gridX][gridY].type = currentSelection;
                grid[gridX][gridY].isPowerUp = false;
            }
        }
    }

    if (showSavePopup) {
        savePopupTimer += GetFrameTime();
        if (savePopupTimer > SAVE_POPUP_DURATION) {
            showSavePopup = false;
        }
    }
    if (showLoadPopup) {
        loadPopupTimer += GetFrameTime();
        if (loadPopupTimer > LOAD_POPUP_DURATION) {
            showLoadPopup = false;
        }
    }
}

void Editor::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode2D(camera);

    for (int x = 0; x < GRID_WIDTH; x++) {
        for (int y = 0; y < GRID_HEIGHT; y++) {
            Rectangle cell = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };

            if (grid[x][y].type != ElementType::EMPTY) {
                Color tint = grid[x][y].isPowerUp ? GOLD : WHITE;

                Texture2D texture = sprites[static_cast<int>(grid[x][y].type)].texture;

                float scaleFactor = 2.0f;

                Vector2 centerPos = {
                    cell.x + (cell.width - texture.width * scaleFactor) * 0.5f,
                    cell.y + (cell.height - texture.height * scaleFactor) * 0.5f
                };

                DrawTexturePro(texture,
                    {0, 0, static_cast<float>(texture.width), static_cast<float>(texture.height)},
                    {centerPos.x, centerPos.y, static_cast<float>(texture.width) * scaleFactor, static_cast<float>(texture.height) * scaleFactor},
                    {0, 0}, 0.0f, tint);
                            }

            if (showGridLines) {
                DrawRectangleLinesEx(cell, 1, DARKGRAY);
            }
        }
    }

    EndMode2D();

    DrawRectangle(0, GetScreenHeight() - TOOLBAR_HEIGHT, GetScreenWidth(), TOOLBAR_HEIGHT + 40, noirProfond
);
    DrawRectangleRec(hideShowButton, fondVert);
    DrawText("Grid", 15, GetScreenHeight() - TOOLBAR_HEIGHT - 25, 20, BLACK);

    for (int i = static_cast<int>(ElementType::ELEMENT_1); i < static_cast<int>(ElementType::ELEMENT_COUNT); i++) {
        Rectangle dest = { (i - 1) * (TOOLBAR_HEIGHT + 10), GetScreenHeight() - TOOLBAR_HEIGHT, TOOLBAR_HEIGHT, TOOLBAR_HEIGHT };
        DrawTexturePro(sprites[i].texture, sprites[i].frame, dest, { 0, 0 }, 0.0f, WHITE);
        if (static_cast<int>(currentSelection) == i) {
            DrawRectangleLinesEx(dest, 3, RED);
        }
    }

        if (showSavePopup) {
            const int popupWidth = 270;
            const int popupHeight = 100;
            Rectangle popupRect = { static_cast<float>((GetScreenWidth() - popupWidth) / 2), static_cast<float>((GetScreenHeight() - popupHeight) / 2), popupWidth, popupHeight };

            DrawRectangleRec(popupRect, fondVert);
            DrawText("File Saved Successfully!", popupRect.x + 10, popupRect.y + popupHeight / 2 - 10, 20, texteBlanc);
    }
        if (showLoadPopup) {
            const int popupWidth = 270;
            const int popupHeight = 100;
            Rectangle popupRect = { static_cast<float>((GetScreenWidth() - popupWidth) / 2), static_cast<float>((GetScreenHeight() - popupHeight) / 2), popupWidth, popupHeight };
            DrawRectangleRec(popupRect, fondVert);
            DrawText("File Loaded Successfully!", popupRect.x + 10, popupRect.y + popupHeight / 2 - 10, 20, texteBlanc);
    }

    EndDrawing();
}
