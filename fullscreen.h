#ifndef FULLSCREEN_H
#define FULLSCREEN_H

#include "raylib.h"

// Clamp関数のテンプレート定義
template <typename T>
T Clamp(T value, T min, T max);

// FullScreenFunc構造体の定義
struct FullScreenFunc {
    int baseWidth;
    int baseHeight;
    int windowWidth;
    int windowHeight;
    float scale;
    int scaledW;
    int scaledH;
    int offsetX;
    int offsetY;

    void init(int w, int h);
    void drawTarget(RenderTexture2D* target);
    Vector2 GetGameMouse();
};

#endif // FULLSCREEN_H