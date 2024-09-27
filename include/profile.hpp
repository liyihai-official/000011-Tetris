///
/// @file include/profile.hpp
///
/// @brief Essential Profile
///
///
#pragma once
#include <types.hpp>

constexpr tetris::size_type __cell_size__ {10};

#if !defined(HORIZON_NUM) || !defined(VERTICAL_NUM)
  #define HORIZON_NUM 30
  #define VERTICAL_NUM 10 
#endif

