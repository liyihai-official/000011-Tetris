#include <unistd.h>
#include <raylib.h>
#include <grid.hpp>
#include <iostream>
#include <types>

template <typename T>
void print(const std::initializer_list<T> list)
{
  for (auto const & elem : list)
  {
    std::cout << elem << " ";
  }
  std::cout << std::endl;
}

// void DrawBoard() {
//   for (int i = 0; i < rows; ++i) {
//     for (int j = 0; j < cols; ++j) {
//       if (board[i][j] != 0) {
//         DrawRectangle(j * 30, i * 30, 30, 30, GRAY); // 绘制每个方块
//       }
//     }
//   }
// }


int main(int argc, char ** argv)
{
  // tetris::utility::Grid_World Grid (10, 4);
  // std::cout << Grid << std::endl;

  tetris::utility::Tetromino T;

  // tetris::utility::Grid_World gw (10, 5);

  // InitWindow(NX, NY, "Title");
  // SetTargetFPS(120);


  // while (!WindowShouldClose()) 
  // {
  //   float deltaTime = GetFrameTime();
  //   T.move(deltaTime);
  //   bool Coll = T.isCollision(gw);


  //   BeginDrawing();
  //   ClearBackground(WHITE);

  //   gw.Draw();
  //   if (Coll) {
  //     gw.FixToGrid(T);
  //     // tetris::utility::Tetromino other;
  //     // T = std::move(other);
  //     // break;
  //     T.reset();
  //   }
  //   else {
  //     T.Draw();
  //   }
  //   std::cout << Coll << std::endl;
    
    

  //   EndDrawing();
  // }
  // CloseWindow();
  
  

  return 0;
}