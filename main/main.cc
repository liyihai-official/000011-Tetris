#include "raylib.h"

int main() {
  // 初始化窗口
  InitWindow(800, 450, "Hello Raylib on macOS");

  SetTargetFPS(60);  // 设置帧率

  while (!WindowShouldClose()) {  // 主游戏循环，直到窗口关闭
    BeginDrawing();
    ClearBackground(RAYWHITE);  // 设置背景颜色为白色
    DrawText("Hello Raylib on macOS!", 190, 200, 20, LIGHTGRAY);  // 显示文本
    EndDrawing();
  }

  CloseWindow();  // 关闭窗口并释放资源

  return 0;
}