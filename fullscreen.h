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

    void DrawBegin(RenderTexture2D target);
    void DrawEnd(RenderTexture2D* target);

    void drawTarget(RenderTexture2D* target);
    Vector2 ToVirtualMouse(Vector2 raw);
    Vector2 GetGameMouse();
};

#endif // FULLSCREEN_H