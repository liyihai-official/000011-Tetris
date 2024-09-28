#include "raylib.h"
#include <profile.hpp>
#include <grid.hpp>
#include <iostream>

int main() {

  InitWindow(HORIZON_SIZE, VERTICAL_SIZE, "Tetris on macOS");
  SetTargetFPS(120);  // 设置帧率

  // float loc_x = 10.0f;
  // float loc_y = 10.0f;

  // // 定义速度变量，控制格子的运动
  // float speed_x = 2.0f;
  // float speed_y = 2.0f;
  tetris::coord loc(10, 20);
  tetris::utility::cell c (loc);


  while (!WindowShouldClose()) {  // 主游戏循环，直到窗口关闭
  //   // 更新格子的坐标
  //   loc_x += speed_x;
  //   // loc_y += speed_y;
    std::array<tetris::coord, BLOCK_CELL_COUNT> position;

    position[0] = loc + tetris::coord(1, 0) * __cell_size__;
    position[1] = loc + tetris::coord(1, 1) * __cell_size__;
    position[2] = loc + tetris::coord(1, 2) * __cell_size__;

    tetris::utility::cell b (position[1]);
    tetris::utility::cell e (position[2]);
    tetris::utility::cell d (position[0]);
    
    c.draw();
    b.draw();
    e.draw();
    d.draw();
    
  //   // 检测边界并反弹
  //   if (loc_x <= 0 || loc_x >= (HORIZON_SIZE - __cell_size__)) {
  //       speed_x *= -1;  // 反转 X 轴速度
  //   }
  //   if (loc_y <= 0 || loc_y >= (1000 - 10)) {
  //       speed_y *= -1;  // 反转 Y 轴速度
  //   }

  //   // 开始绘制
  //   BeginDrawing();
  //   ClearBackground(BLACK);  // 设置背景颜色为黑色

  //   // 显示文本
  //   DrawText("Hello Raylib on macOS!", 190, 200, 20, LIGHTGRAY);

  //   // 绘制矩形
  //   DrawRectangleRounded((Rectangle){320, 55, 170, 60}, 0.3f, 6, DARKGRAY);

  //   // 绘制移动的蓝色格子
  //   DrawRectangleRounded((Rectangle){loc_x, loc_y, 10, 10}, 0.0f, 1, DARKBLUE);

    EndDrawing();
  }

  // CloseWindow();  // 关闭窗口并释放资源

  return 0;
}