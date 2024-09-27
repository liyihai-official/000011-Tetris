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

  typedef Word          size_type;
  typedef Qword         super_size_type;

}

#endif // end of define TETRIS_TYPES_HPP