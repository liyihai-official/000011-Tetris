#include "raylib.h"

int main() {
    InitWindow(450, 1000, "Tetris on macOS");
    SetTargetFPS(120);  // 设置帧率

    float loc_x = 10.0f;
    float loc_y = 10.0f;

    // 定义速度变量，控制格子的运动
    float speed_x = 2.0f;
    float speed_y = 2.0f;

    while (!WindowShouldClose()) {  // 主游戏循环，直到窗口关闭
        // 更新格子的坐标
        loc_x += speed_x;
        loc_y += speed_y;

        // 检测边界并反弹
        if (loc_x <= 0 || loc_x >= (450 - 10)) {
            speed_x *= -1;  // 反转 X 轴速度
        }
        if (loc_y <= 0 || loc_y >= (1000 - 10)) {
            speed_y *= -1;  // 反转 Y 轴速度
        }

        // 开始绘制
        BeginDrawing();
        ClearBackground(BLACK);  // 设置背景颜色为黑色

        // 显示文本
        DrawText("Hello Raylib on macOS!", 190, 200, 20, LIGHTGRAY);

        // 绘制矩形
        DrawRectangleRounded((Rectangle){320, 55, 170, 60}, 0.3f, 6, DARKGRAY);

        // 绘制移动的蓝色格子
        DrawRectangleRounded((Rectangle){loc_x, loc_y, 10, 10}, 0.0f, 1, DARKBLUE);

        EndDrawing();
    }

    CloseWindow();  // 关闭窗口并释放资源

    return 0;
}