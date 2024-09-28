///
/// @file include/profile.hpp
///
/// @brief Essential Profile
///
///
#pragma once
#include <types.hpp>

constexpr tetris::size_type __cell_size__ {20};

#if !defined(HORIZON_NUM) || !defined(VERTICAL_NUM)
  #define HORIZON_NUM    10
  #define VERTICAL_NUM   30 
  #define HORIZON_SIZE   (HORIZON_NUM  * __cell_size__)
  #define VERTICAL_SIZE  (VERTICAL_NUM * __cell_size__)
#endif



#if !defined(BLOCK_CELL_COUNT)
  #define BLOCK_CELL_COUNT 4
#endif 

