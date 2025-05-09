#include <math.h>
#include "fullscreen.h"
#include <iostream>

using namespace std;

// Clamp function definition
template <typename T>
T Clamp(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

// FullScreenFunc メンバー関数の定義
void FullScreenFunc::init(int w, int h) {
    this->baseWidth = w;
    this->baseHeight = h;
    #if defined(PLATFORM_WEB)
        
    #else
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    #endif
}

void FullScreenFunc::DrawBegin(RenderTexture2D target) {
    #if defined(PLATFORM_WEB)
        BeginDrawing();
    #else
        BeginTextureMode(target); 
    #endif
}

void FullScreenFunc::DrawEnd(RenderTexture2D* target) {
    #if defined(PLATFORM_WEB)
        EndDrawing();
    #else
        EndTextureMode();
        this->drawTarget(target);
    #endif
}

void FullScreenFunc::drawTarget(RenderTexture2D* target) {
    BeginDrawing();
        ClearBackground((Color){34,34,34, 255} );
        //ClearBackground(BLACK);
            float screenW = (float)GetScreenWidth();
            float screenH = (float)GetScreenHeight();

            this->scale = fminf(screenW / this->baseWidth, screenH / this->baseHeight);
            this->offsetX = (screenW - (this->baseWidth * this->scale)) * 0.5f;
            this->offsetY = (screenH - (this->baseHeight * this->scale)) * 0.5f;

            DrawTexturePro(
                target->texture,
                (Rectangle){ 0.0f, 0.0f, (float)this->baseWidth, -(float)this->baseHeight }, // 上下反転
                (Rectangle){ (float)this->offsetX, (float)this->offsetY, (float)(this->baseWidth * this->scale), (float)(this->baseHeight * this->scale) },
                (Vector2){ 0, 0 },
                0.0f,
                WHITE
            );
        EndDrawing();
}

Vector2 FullScreenFunc::ToVirtualMouse(Vector2 raw) {
    float mx = (raw.x - this->offsetX) / this->scale;
    float my = (raw.y - this->offsetY) / this->scale;

    mx = Clamp(mx, 0.0f, (float)this->baseWidth);
    my = Clamp(my, 0.0f, (float)this->baseHeight);

    return (Vector2){ mx, my };
}

Vector2 FullScreenFunc::GetGameMouse() {
    #if defined(PLATFORM_WEB)
        return GetMousePosition();
    #else
        return ToVirtualMouse(GetMousePosition());
    #endif
}