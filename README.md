# Raylib Fullscreen Sample

このプロジェクトは、Raylibがデフォルトで提供していない**正確なフルスクリーン描画**と、**Web（Emscripten/WebGL）でも動作する座標補正付きの入力処理**を実装したサンプルです。

## 特徴 ✨
- PC版とWeb版の両方で、ベース解像度に合わせてスケーリング
- 余白処理・アスペクト比の保持
- マウス／タッチ入力の補正関数付き（`ToVirtualMouse()`）
- `DrawTexturePro` による上下反転と拡大描画

## 必要な環境

- C++11 以上
- [raylib](https://www.raylib.com/) ライブラリ

## ビルドと実行

以下のコマンドを使用してプログラムをビルドし、実行します。

```bash
c++ -std=c++11 base.cpp fullscreen.cpp -lraylib
```