#include "raylib.h"
#include "fullscreen.h"

// メインプログラム
const int screenWidth = 800;
const int screenHeight = 450;

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "raylib fullscreen class example");
    SetTargetFPS(60);

    FullScreenFunc fullScreen;
    fullScreen.init(screenWidth, screenHeight);

    RenderTexture2D target = LoadRenderTexture(screenWidth, screenHeight);

    while (!WindowShouldClose()) {
        // 仮想画面に描画
        BeginTextureMode(target);
            ClearBackground(RAYWHITE);
            DrawText("Click to test mouse mapping", 100, 100, 20, BLACK);

            Vector2 mouse = fullScreen.GetGameMouse();
            DrawCircle(mouse.x, mouse.y, 10, RED);
        EndTextureMode();

        // 実際の画面に出力（比率維持・中央配置）
        fullScreen.drawTarget(&target);
    }

    UnloadRenderTexture(target);
    CloseWindow();

    return 0;
}