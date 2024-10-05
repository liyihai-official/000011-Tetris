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

/// @brief The Grid class contains the ground-level features of draw & clear Rows.
///         Aligned with others interact with Blocks.
class grid
{
  public:
  grid()                        noexcept;
  grid(const grid &)            = delete;
  grid(grid &&)                 = delete;
  grid& operator=(grid &&)      = delete;
  grid& operator=(const grid &) = delete;
  ~grid() {std::cout << "Calling Grid Destructor." << std::endl;}


  void draw()           noexcept;
  void ClearFullRows()  noexcept;
  

  void UpdateUpperBound() noexcept;

  private:
  std::array<std::array<cell_color, HORIZON_NUM>, VERTICAL_SIZE> world;

  std::array<size_type, VERTICAL_SIZE> UpperBound;
  friend block;
}; // class grid






class cell 
{
  public:
  cell()                        noexcept;
  cell(const cell &)            noexcept = default; 
  cell(cell&&)                  noexcept = default;
  cell& operator=(cell &&)      noexcept = default;
  cell& operator=(const cell&)  noexcept = default;
  cell& operator+=(const coord &)   noexcept; 
  cell& operator-=(const coord &)   noexcept; 
  ~cell()                       noexcept = default;

  cell(coord)                   noexcept;

  void draw();


  private:
  coord loc;
  // color clr;

  friend block;
}; // class cell



class block
{
  public:
  block(block_type, const Float & ) noexcept;
  
  void rotate_clockwise(); // Using Matrix Multiplication to Perform Rotation.
  void move();
  void draw();

  private:
  coord default_momentum;
  orientation ori;
  block_type type;
  std::unique_ptr<cell[]> body;
  std::array<Float, BLOCK_CELL_COUNT> rotate_factor = {0, 1, -1, 0};

}; // class block




}}