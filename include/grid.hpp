///
/// @file include/grid.hpp
///
/// @brief Grid World
///

#pragma once
#include <memory>
#include <array>
#include <profile.hpp>

namespace tetris { namespace utility {
  class cell;
  class block;
  class grid;  
} // namespace grid
} // namespace tetris





namespace tetris { namespace utility {


class cell 
{
  public:
  cell() noexcept {};
  cell(const cell &) noexcept = default; 
  cell(cell&&) noexcept = default;
  cell& operator=(cell &&) noexcept = default;
  cell& operator=(const cell&) noexcept  = default;
  ~cell() noexcept = default;

  cell(coord loc)  : loc {loc} { }

  void draw()
  {
    DrawRectangleRounded(
      (Rectangle){loc.x, loc.y, __cell_size__, __cell_size__}, 
      0.0f, 
      1, 
      DARKBLUE);
  }



  private:
  coord loc;
  // color clr;

  friend block;
}; // class cell



// class block
// {
//   block(block_type type)
//   : type {type}
//   , body {std::make_unique<cell[]>(BLOCK_CELL_COUNT)}
//   {
//     std::array<coord, BLOCK_CELL_COUNT> position;

//     switch (type)
//     {
//       case L      : 
//       case Lmir   :
//       case Z      :
//       case Zmir   :
//       case Cube   :
//       case Bar    :
//       case Py     :
//       default     :
//     }
//     // for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) body[0] = cell(coord loc);
//   }

//   void rotate_clockwise(Bool clockwise);


//   void move();


//   private:
//   orientation ori;
//   block_type type;
//   std::unique_ptr<cell[]> body;

// }; // class block


}}