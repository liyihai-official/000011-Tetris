///
/// @file include/types.hpp
///
/// @brief Datatypes
///

#pragma once
#ifndef TETRIS_TYPES_HPP
#define TETRIS_TYPES_HPP

#include <cstdint>
#include <string>

namespace tetris {

  using Byte  = uint8_t;
  using Word  = uint16_t;
  using Dword = uint32_t;
  using Qword = uint64_t;

  using Integer         = int;
  using UnsignedInteger = unsigned int;
  using Float           = float;
  using Double          = double;
  using Char            = char;
  using Bool            = bool;

  using String          = std::string;

  typedef Byte          direction;
  typedef Word          size_type;
  typedef Qword         super_size_type;
  


  struct coord {
    coord() : x {0}, y {0} {}
    coord(Float x, Float y) : x {x}, y {y} {}
    coord operator+(const coord & other) noexcept
      { return coord(x+other.x, y+other.y); }

    coord operator-(const coord & other) noexcept 
      { return coord(x-other.x, y-other.y); }

    coord operator*(const Float mpl) noexcept
      { return coord(x*mpl, y*mpl); }

    Float x, y;
  };
  

  
  enum orientation 
  : direction
  {
    North,
    South,
    East,
    West
  }; // enumerate orientation

  enum block_type
  : Byte
  {
    L,
    Lmir,
    Z,
    Zmir,
    Cube,
    Bar,
    Py
  }; // enumerate block_type

}

#endif // end of define TETRIS_TYPES_HPP