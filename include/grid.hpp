///
/// @file include/grid.hpp
///
/// @brief Grid World
///

#pragma once
#include <memory>
#include <array>
#include <profile.hpp>
#include <random>
#include <iostream>
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



class block
{
  public:
  block(block_type type, const Float & x)
  : type {type}
  , body {std::make_unique<cell[]>(BLOCK_CELL_COUNT)}
  {
    coord loc (x, 80);
    std::cout << "Calling Block Constructor" 
              << "\nAt " << loc.x << ", " << loc.y << std::endl;

    std::array<coord, BLOCK_CELL_COUNT> position;

    // position[0] = loc + coord(0, 0) * __cell_size__;
    switch (type)
    {
      case L      : 
        std::cout << "Type: L" << std::endl;
        position[1] = loc + coord(1, 0)   * __cell_size__;
        // position[2] = loc + coord(1, -1) * __cell_size__;
        // position[3] = loc + coord(1, -2) * __cell_size__;
        break;
      case Lmir   :
        // position[1] = loc + coord(1, 0)   * __cell_size__;
        // position[2] = loc + coord(-1, -1) * __cell_size__;
        // position[3] = loc + coord(-1, -2) * __cell_size__;
        break;
      // case Z      :
      // case Zmir   :
      // case Cube   :
      // case Bar    :
      // case Py     :
      default     :
        break;
    }
    for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) body[0] = cell(position[i]);
    
  }

  void rotate_clockwise(Bool clockwise);


  void move();
  void draw()
  {
    // for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) body[i].draw();
    // body[0].draw();
  }


  private:
  orientation ori;
  block_type type;
  std::unique_ptr<cell[]> body;

}; // class block


}}