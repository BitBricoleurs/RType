//
// Created by alexandre on 20/10/23.
//

#include "raylib.h"
#include "Editor.hpp"

int main() {
    InitWindow(1920, 1080, "Map Editor");
    SetTargetFPS(60);

    Editor editor;
    editor.Init();

    while (!WindowShouldClose()) {
        editor.Update();
        editor.Draw();
    }

    CloseWindow();
    return 0;
}
