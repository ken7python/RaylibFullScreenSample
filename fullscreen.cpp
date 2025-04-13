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
}

void FullScreenFunc::drawTarget(RenderTexture2D* target) {
    BeginDrawing();
        ClearBackground(BLACK);

        this->windowWidth = GetScreenWidth();
        this->windowHeight = GetScreenHeight();

        this->scale = fminf((float)this->windowWidth / this->baseWidth, (float)this->windowHeight / this->baseHeight);
        if (this->scale < 0.01f) this->scale = 0.01f; // 安全のための最小スケール保証

        this->scaledW = this->baseWidth * this->scale;
        this->scaledH = this->baseHeight * this->scale;
        this->offsetX = (this->windowWidth - this->scaledW) / 2;
        //this->offsetY = (this->windowHeight - this->scaledH) / 2;
        float aspect = (float)this->windowWidth / this->windowHeight;
        if (aspect < 0.75f) {
            this->offsetY = 0; // スマホ縦長比率なら上寄せ！
        } else {
            this->offsetY = (this->windowHeight - this->scaledH) / 2;
        }

        DrawTexturePro(
            target->texture,
            (Rectangle){ 0.0f, 0.0f, (float)this->baseWidth, -(float)this->baseHeight }, // 上下反転
            (Rectangle){ (float)this->offsetX, (float)this->offsetY, (float)this->scaledW, (float)this->scaledH },
            (Vector2){ 0, 0 },
            0.0f,
            WHITE
        );
    EndDrawing();
}

Vector2 FullScreenFunc::GetGameMouse() {
    #if defined(PLATFORM_WEB)
        //return GetMousePosition();
        Vector2 pos = IsMouseButtonDown(MOUSE_LEFT_BUTTON)
        ? GetTouchPosition(0)
        : GetMousePosition();
        return pos;
    #else
        /*
        cout << this->offsetX << " " << this->offsetY << endl;
        cout << this->scale << endl;
        */
        float mx = (GetMouseX() - this->offsetX) / this->scale;
        float my = (GetMouseY() - this->offsetY) / this->scale;

        // 範囲内に収める（Clampは raylib の関数）
        mx = Clamp(mx, 0.0f, (float)this->baseWidth);
        my = Clamp(my, 0.0f, (float)this->baseHeight);

        return (Vector2){ mx, my };
    #endif
}