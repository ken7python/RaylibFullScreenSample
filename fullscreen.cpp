#include <math.h>
#include "fullscreen.h"

// Clamp function definition
template <typename T>
T Clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// FullScreenFunc メンバー関数の定義
void FullScreenFunc::init(int w, int h) {
    baseWidth = w;
    baseHeight = h;
}

void FullScreenFunc::drawTarget(RenderTexture2D* target) {
    BeginDrawing();
        ClearBackground(BLACK);

        windowWidth = GetScreenWidth();
        windowHeight = GetScreenHeight();

        scale = fminf((float)windowWidth / baseWidth, (float)windowHeight / baseHeight);
        if (scale < 0.01f) scale = 0.01f; // 安全のための最小スケール保証

        scaledW = baseWidth * scale;
        scaledH = baseHeight * scale;
        offsetX = (windowWidth - scaledW) / 2;
        offsetY = (windowHeight - scaledH) / 2;

        DrawTexturePro(
            target->texture,
            (Rectangle){ 0.0f, 0.0f, (float)baseWidth, -(float)baseHeight }, // 上下反転
            (Rectangle){ (float)offsetX, (float)offsetY, (float)scaledW, (float)scaledH },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    EndDrawing();
}

Vector2 FullScreenFunc::GetGameMouse() {
    float mx = (GetMouseX() - offsetX) / scale;
    float my = (GetMouseY() - offsetY) / scale;

    // 範囲内に収める（Clampは raylib の関数）
    mx = Clamp(mx, 0.0f, (float)baseWidth);
    my = Clamp(my, 0.0f, (float)baseHeight);

    return (Vector2){ mx, my };
}