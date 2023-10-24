//
// Created by alexandre on 20/10/23.
//

#pragma once

#include "ElementType.hpp"
#include "Sprite.hpp"
#include "Cell.hpp"
#include "raylib.h"
#include <fstream>
#include <nlohmann/json.hpp>
#include "ElementInfo.hpp"

const ElementInfo ELEMENTS[] = {
    { "assets/editor/pata.gif", ElementType::ELEMENT_1, "pataPataMob" },
    { "assets/editor/bellmite.png", ElementType::ELEMENT_2, "pataPataMob" },
};

struct Editor {
    Color fondVert = { 46, 204, 113, 255 };
    Color texteBlanc = { 255, 255, 255, 255 };
    Color noirProfond = { 25, 25, 25, 255 };


    static const int GRID_WIDTH = 1000;
    static const int GRID_HEIGHT = 20;
    static const int VISIBLE_CELLS_X = 20;
    bool showSavePopup = false;
    float savePopupTimer = 0.0f;
    const float SAVE_POPUP_DURATION = 2.0f;
    bool showLoadPopup = false;
    float loadPopupTimer = 0.0f;
    const float LOAD_POPUP_DURATION = 2.0f;


    Sprite sprites[static_cast<int>(ElementType::ELEMENT_COUNT)]{};
    Cell grid[GRID_WIDTH][GRID_HEIGHT]{};
    ElementType currentSelection = ElementType::ELEMENT_1;

    float TILE_SIZE{};
    float TOOLBAR_HEIGHT{};
    float SCALE_TEXT_HEIGHT = 30.0f;
    bool showGridLines = true;
    Rectangle hideShowButton{};
    Texture2D backgroundTexture{};
    Camera2D camera{};

    Editor();
    ~Editor();

    void LoadAssets();
    void UnloadAssets();

    static Vector2 GetWorldPosition(Vector2 screenPosition, Camera2D camera);

    static std::string ElementTypeToString(ElementType type);

    void SaveToJSON(const std::string& filename);
    void LoadFromJSON(const std::string& filename);
    static ElementType StringToElementType(const std::string& type);

    void Init();

    void Update();

    void Draw();

};
