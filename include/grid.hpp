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
  
  Color GetColorFromEnum(cell_color);
} // namespace grid
} // namespace tetris





namespace tetris { namespace utility {

class cell 
{
  public:
  cell()                        noexcept;
  cell(const cell &)            noexcept = default; 
  cell(cell&&)                  noexcept = default;
  cell& operator=(cell &&)      noexcept = default;
  cell& operator=(const cell&)  noexcept = default;
  ~cell()                       noexcept = default;

  cell(coord) noexcept;

  void draw();


  private:
  coord loc;
  // color clr;

  friend block;
}; // class cell



class block
{
  public:
  block(block_type, const Float & x) noexcept;

  void rotate_clockwise(); // Using Matrix Multiplication to Perform Rotation.
  void move();
  void draw();

  private:
  orientation ori;
  block_type type;
  std::unique_ptr<cell[]> body;
  std::array<Float, BLOCK_CELL_COUNT> rotate_factor = {0, 1, -1, 0};

}; // class block


class grid
{
  public:
  grid()      noexcept;

  void draw() noexcept;

  private:
  void ClearFullRow() noexcept;
  std::array<std::array<cell_color, HORIZON_NUM>, VERTICAL_SIZE> world;

}; // class grid



}}