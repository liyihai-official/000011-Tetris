#include <grid.hpp>

namespace tetris { namespace utility {

Color GetColorFromEnum(cell_color color) {
  switch (color) {
    case cell_color::Black:   return CLITERAL(Color){ 0, 0, 0, 255 };
    case cell_color::White:   return CLITERAL(Color){ 255, 255, 255, 255 };
    case cell_color::Red:     return CLITERAL(Color){ 255, 0, 0, 255 };
    case cell_color::Green:   return CLITERAL(Color){ 0, 255, 0, 255 };
    case cell_color::Blue:    return CLITERAL(Color){ 0, 0, 255, 255 };
    case cell_color::Yellow:  return CLITERAL(Color){ 255, 255, 0, 255 };
    case cell_color::Purple:  return CLITERAL(Color){ 128, 0, 128, 255 };
    default:                  return CLITERAL(Color){ 0, 0, 0, 255 }; // 默认返回黑色
  }
}

cell::cell()          noexcept {};
cell::cell(coord loc) noexcept : loc {loc} {}

cell& cell::operator+=(const coord & momentum) noexcept
{ loc += momentum; return *this; }

cell& cell::operator-=(const coord & momentum) noexcept
{ loc -= momentum; return *this; }

void 
cell::draw()
{
DrawRectangleRounded(
  (Rectangle){loc.x, loc.y, __cell_size__, __cell_size__}, 
  0.0f, 
  1, 
  DARKBLUE);
}


block::block(
  block_type type
, const Float & x) noexcept
: type {type}
, body {std::make_unique<cell[]>(BLOCK_CELL_COUNT)}
, default_momentum {coord(0, 0.5)}
{
  coord loc (x, 80);
  std::cout << "Calling Block Constructor" 
            << "\nAt " << loc.x << ", " << loc.y << std::endl;

  std::array<coord, BLOCK_CELL_COUNT> position;

  position[0] = loc + coord(0, 0) * __cell_size__;
switch (type)
{
  case L      : 
    std::cout << "Type: L " << std::endl;
    position[1] = loc + coord(1, 0)  * __cell_size__;
    position[2] = loc + coord(1, -1) * __cell_size__;
    position[3] = loc + coord(1, -2) * __cell_size__;
    break;
  case Lmir   :
    std::cout << "Type: L Mirror" << std::endl;
    position[1] = loc + coord(1, 0)  * __cell_size__;
    position[2] = loc + coord(0, -1) * __cell_size__;
    position[3] = loc + coord(0, -2) * __cell_size__;
    break;
  case Z      :
    std::cout << "Type: Z " << std::endl;
    position[1] = loc + coord(1, 0)  * __cell_size__;
    position[2] = loc + coord(1, -1) * __cell_size__;
    position[3] = loc + coord(2, -1) * __cell_size__;
  case Zmir   :
    std::cout << "Type: Z Mirror " << std::endl;
    position[1] = loc + coord(1, 0)  * __cell_size__;
    position[2] = loc + coord(0, -1) * __cell_size__;
    position[3] = loc + coord(-1, -1) * __cell_size__;
  case Cube   :
    std::cout << "Type: Cube " << std::endl;
    position[1] = loc + coord(1, 0)  * __cell_size__;
    position[2] = loc + coord(1, -1) * __cell_size__;
    position[3] = loc + coord(0, -1) * __cell_size__;
  case Bar    :
    std::cout << "Type: Bar " << std::endl;
    position[1] = loc + coord(0, -1)  * __cell_size__;
    position[2] = loc + coord(0, -2) * __cell_size__;
    position[3] = loc + coord(0, -3) * __cell_size__;
  case Py     :
    std::cout << "Type: Pyramid " << std::endl;
    position[1] = loc + coord(1, -1)  * __cell_size__;
    position[2] = loc + coord(1, 0) * __cell_size__;
    position[3] = loc + coord(2, 0) * __cell_size__;
  default     :
    std::cout << "Unknown Type " << std::endl;
    break;
}
  for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) body[i] = cell(position[i]);   
}


// block& 
// block::operator+=(const coord & momentum)
// {
//   for (int i = 0; i < BLOCK_CELL_COUNT; ++i)
//   {
//     body[i] += momentum;
//   }
//   return *this;
// }


void 
block::move()
{
  int UserPress { GetKeyPressed() };
  coord Momentum { default_momentum };
  
  switch (UserPress)
  {
    case KEY_LEFT:
      Momentum -= coord(__cell_size__, 0);
      break;
    case KEY_RIGHT:
      Momentum += coord(__cell_size__, 0);
      break;
    case KEY_DOWN:
      Momentum += coord(0, __cell_size__);
      break;
    case KEY_UP:
      rotate_clockwise();
      break;
    case KEY_SPACE:
      break;
    default:
      break;
  }

  for (int i = 0; i < BLOCK_CELL_COUNT; ++i) 
  {
    body[i] += Momentum;
  }

}

void
block::draw()
{ for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) body[i].draw(); }

void
block::rotate_clockwise()
{
  coord center {body[0].loc};
  switch (type)
  {
case L : case Lmir :
case Z : case Zmir :
  center = body[2].loc;
  break;
case Bar : case Py : 
  center = body[1].loc;
  break;
default: break;
  }
  
  for (auto i = 0; i < BLOCK_CELL_COUNT; ++i) 
    body[i] = cell(center + (body[i].loc - center)*rotate_factor);
}










grid::grid() noexcept
{ 
  UpperBound.fill(HORIZON_SIZE);
  for (auto & row : world) row.fill(cell_color::Black); 
  

////////////////////////////////////////////////////////////////////////////////////////
  for (int r = VERTICAL_NUM - 4; r >= VERTICAL_NUM - 4; --r)
    for (int c = 0; c < HORIZON_NUM; ++c)
    {
      if (c < 2) world[r][c] = cell_color::Green;
      else if (2 < c && c < 4) world[r][c] = cell_color::Red;
      else world[r][c] = cell_color::Purple;
    }

  for (int r = VERTICAL_NUM - 3; r >= VERTICAL_NUM - 3; --r)
    for (int c = 0; c < HORIZON_NUM; ++c)
    {
      if (c < 2) world[r][c] = cell_color::Purple;
      else if (3 < c && c < 5) world[r][c] = cell_color::Black;
      else world[r][c] = cell_color::Yellow;
    }

  for (int r = VERTICAL_NUM - 2; r >= VERTICAL_NUM - 2; --r)
    for (int c = 0; c < HORIZON_NUM; ++c)
    {
      if (c < 2) world[r][c] = cell_color::Green;
      else if (2 < c && c < 4) world[r][c] = cell_color::Red;
      else world[r][c] = cell_color::Purple;
    }

  for (int r = VERTICAL_NUM - 1; r >= VERTICAL_NUM - 1; --r)
    for (int c = 0; c < HORIZON_NUM; ++c)
    {
      if (c < 2) world[r][c] = cell_color::Purple;
      else if (3 < c && c < 5) world[r][c] = cell_color::Black;
      else world[r][c] = cell_color::Yellow;
    }
////////////////////////////////////////////////////////////////////////////////////////


}

void 
grid::UpdateUpperBound() noexcept 
{
  for (size_type j = 0; j < HORIZON_NUM; ++j)
  {
    size_type Up {0};
    // while 
    // for (size_type i = 0; i < VERTICAL_NUM; ++i)
    // {

    // }
  }


}

void 
grid::ClearFullRows() noexcept
{
  for (size_type j = 0; j < HORIZON_NUM; ++j)
  {
    size_type i {0};
    while (world[i][j] == cell_color::Black)
    { 
      ++i;
      if ( i == VERTICAL_NUM ) break;
    }
    std::cout << "Col : " << j << "'s Upper is " << i << std::endl;
  }

  for (int r = VERTICAL_NUM - 1; r >= 0; --r)
  {
    int cell_count { 0 };
    for (int c = 0; c < HORIZON_NUM; ++c)
    {
      if (world[r][c] != cell_color::Black) ++cell_count;
    }

    std::cout << "Row : " << r << " has " << cell_count << "/" << HORIZON_NUM << " cells. " << std::endl;
    if (cell_count == HORIZON_NUM)
    {
      std::cout << "Row : " << r << " is Full " << std::endl;
      
      for (int r_above = r; r_above >= 0; --r_above)
      {
        for (int c = 0; c < HORIZON_NUM; ++c)
        {
          if (r_above == 0) world[r_above][c] = cell_color::Black;
          else world[r_above][c] = world[r_above-1][c];
        }
      }
    }
  }

  std::cout << std::endl;

  // for (size_type j = 0; j < HORIZON_NUM; ++j)
  // {
  //   size_type i {0};
  //   while (world[i][j] == cell_color::Black)
  //   { 
  //     ++i;
  //     if ( i == VERTICAL_NUM ) break;
  //   }
  //   std::cout << "Col : " << j << "'s Upper is " << i << std::endl;
  // }
}




void 
grid::draw() noexcept
{
for (int r = 0; r < VERTICAL_NUM; ++r)
  for (int c = 0; c < HORIZON_NUM; ++c)
  DrawRectangle(
    c*__cell_size__, r*__cell_size__, 
    __cell_size__, __cell_size__,
    GetColorFromEnum(world[r][c])
  );
}

}}