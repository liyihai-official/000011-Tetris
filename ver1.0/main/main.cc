#include "raylib.h"
#include <profile.hpp>
#include <grid.hpp>
#include <iostream>
#include <unistd.h>

// void inline tetris::utility::grid::draw() noexcept;

int main() {

  InitWindow(HORIZON_SIZE, VERTICAL_SIZE, "Tetris on macOS");
  SetTargetFPS(120);  // 设置帧率

  // float loc_x = 10.0f;
  // float loc_y = 10.0f;

  // // 定义速度变量，控制格子的运动
  // float speed_x = 2.0f;
  // float speed_y = 20.0f;
  tetris::coord loc(0, 80);

  tetris::coord mom(1,1);

  tetris::utility::cell CE (loc);

  CE += mom;

  tetris::utility::block b (
    tetris::block_type::L, 
    0
  );

  tetris::utility::block c (
    tetris::block_type::Py, 
    100
  );

  tetris::utility::grid g;
  
  while (!WindowShouldClose()) {  // 主游戏循环，直到窗口关闭
    BeginDrawing();
    ClearBackground(WHITE);  // 设置背景颜色为黑色

    g.draw();
    g.ClearFullRows();

    b.move();
    b.draw();
    
    // tetris::utility::grid other;
    // g = other;
    // DrawRectangleRounded(
    //   (Rectangle){0, 0, HORIZON_SIZE * 2.0 / 3.0, VERTICAL_SIZE}, 
    //   0.1f, 6, WHITE);


    // c.rotate_clockwise();
    // b.rotate_clockwise();
    // b.draw();
    // c.draw();
  //   // 更新格子的坐标
  //   loc_x += speed_x;
    // loc.y += speed_y;
    // tetris::utility::cell c (loc);
    // std::array<tetris::coord, BLOCK_CELL_COUNT> position;

    // position[0] = loc + tetris::coord(1, 0) * __cell_size__;
    // position[1] = loc + tetris::coord(1, -1) * __cell_size__;
    // position[2] = loc + tetris::coord(1, -2) * __cell_size__;

    // tetris::utility::cell b (position[1]);
    // tetris::utility::cell e (position[2]);
    // tetris::utility::cell d (position[0]);
    
    // c.draw();
    // b.draw();
    // e.draw();
    // d.draw();

    // if (position[2].y >= VERTICAL_SIZE - __cell_size__)
    // {
    //   // speed_y = 0;
    //   loc.y = 20;
    //   loc.x += 10;
    // }

  //   // 检测边界并反弹
  //   if (loc_x <= 0 || loc_x >= (HORIZON_SIZE - __cell_size__)) {
  //       speed_x *= -1;  // 反转 X 轴速度
  //   }
  //   if (loc_y <= 0 || loc_y >= (1000 - 10)) {
  //       speed_y *= -1;  // 反转 Y 轴速度
  //   }

  //   // 开始绘制

    

  //   // 显示文本
  //   DrawText("Hello Raylib on macOS!", 190, 200, 20, LIGHTGRAY);

  //   // 绘制矩形
    

  //   // 绘制移动的蓝色格子
  //   DrawRectangleRounded((Rectangle){loc_x, loc_y, 10, 10}, 0.0f, 1, DARKBLUE);

    for (int x = 0; x <= HORIZON_SIZE; x += __cell_size__) {
        DrawLine(x, 0, x, VERTICAL_SIZE, GRAY);  // 从上到下的垂直线
    }

    // 绘制水平线条 (横线)
    for (int y = 0; y <= VERTICAL_SIZE; y += __cell_size__) {
        DrawLine(0, y, HORIZON_SIZE, y, GRAY);  // 从左到右的水平线
    }
    EndDrawing();
    sleep(1); 
  }

  // CloseWindow();  // 关闭窗口并释放资源

  return 0;
}