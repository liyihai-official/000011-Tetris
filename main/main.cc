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
  // tetris::block_type type {static_cast<tetris::block_type>(tetris::rng(tetris::rde))};
  // tetris::utility::Matrix Mat (2, 5), other (5, 1);
  // Mat.fill(); other.fill();
  // // Mat.swap(other);
  // std::cout << Mat << std::endl;
  // std::cout << other << std::endl;
  // Mat *= other;

  
  // std::cout << Mat << std::endl;
  

  // print({1.1, 2.2, 3.1, 3.0});
  // tetris::Matrix_slice<3> Slice (3, {3, 4, 5});

  // tetris::Matrix_slice<3> Slice_Use_Dims (3, 4, 5);

  // std::cout << Slice_Use_Dims(2, 1, 3) << std::endl;
  // tetris::size_type A = Slice_Use_Dims(1, 1, 1);
  // std::cout << A << std::endl;
  tetris::utility::Grid_World gw (10, 15);

  InitWindow(NX, NY, "Title");
  SetTargetFPS(120);


  while (!WindowShouldClose()) 
  {
    BeginDrawing();
    ClearBackground(WHITE);

    gw.Draw();
    T.move();
    T.Draw();
    



    EndDrawing();
    // sleep(1);
  }

  
  

  return 0;
}