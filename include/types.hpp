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
#include <profile.hpp>
#include <array>

namespace tetris {

  using Byte    = uint8_t;
  using Word    = uint16_t;
  using Dword   = uint32_t;
  using Qword   = uint64_t;

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

  enum orientation  : direction
  { North, South, East, West }; // enumerate orientation

  enum block_type   : Byte
  { L, Lmir, Z, Zmir, Cube, Bar, Py }; // enumerate block_type

  enum class cell_color 
  { Black, White, Blue, Red, Green, Yellow, Purple };
}



#endif // end of define TETRIS_TYPES_HPP