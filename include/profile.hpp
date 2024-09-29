///
/// @file include/profile.hpp
///
/// @brief Essential Profile
///
///
#pragma once
#ifndef TETRIS_PROFILE
#define TETRIS_PROFILE
#include <types.hpp>
#include <raylib.h>

constexpr tetris::size_type __cell_size__ {20};  


#if !defined(HORIZON_NUM) || !defined(VERTICAL_NUM)
  #define HORIZON_NUM    5
  #define VERTICAL_NUM   8
  #define HORIZON_SIZE   (HORIZON_NUM  * __cell_size__)
  #define VERTICAL_SIZE  (VERTICAL_NUM * __cell_size__)
#endif

#if !defined(BLOCK_CELL_COUNT)
  #define BLOCK_CELL_COUNT 4
#endif 




namespace tetris
{
  struct coord {
    coord()                               noexcept : x {0}, y {0} {}
    
    coord(Float x, Float y)               noexcept : x {x}, y {y} {}
    coord operator+(const coord & other)  noexcept
      { return coord(x+other.x, y+other.y); }

    coord operator-(const coord & other)  noexcept 
      { return coord(x-other.x, y-other.y); }

    coord operator*(const Float mpl)      noexcept
      { return coord(x*mpl, y*mpl); }

    coord operator*(const std::array<Float, BLOCK_CELL_COUNT> & mat) noexcept
      { return coord(mat[0] * x + mat[1] * y, mat[2] * x + mat[3] * y); }

    Float x, y;
  };


} // namespace tetris




#endif // #define TETRIS_PROFILE