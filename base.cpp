// c++ -std=c++11 base.cpp fullscreen.cpp -lraylib
#include "raylib.h"
#include "fullscreen.h"

// メインプログラム
const int screenWidth = 800;
const int screenHeight = 450;

int main(void) {
    FullScreenFunc fullScreen;
    fullScreen.init(screenWidth, screenHeight);

    InitWindow(screenWidth, screenHeight, "raylib fullscreen class example");
    SetTargetFPS(60);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // 仮想画面に描画
        fullScreen.DrawBegin(target);
            ClearBackground(RAYWHITE);
            DrawText("Click to test mouse mapping", 100, 100, 20, BLACK);

            Vector2 mouse = fullScreen.GetGameMouse();
            DrawCircle(mouse.x, mouse.y, 10, RED);
        fullScreen.DrawEnd(&target);
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}