#include <array>
#include <memory>
#include <raylib.h>
#include <types>
#include <assert>
#include <iostream>
#include <iomanip>
#include <vector>

#define NX 1504
#define NY 846
namespace tetris { namespace utility
{
  class Matrix;
  class Grid_World;
  class Tetromino;
} // namespace utility
} // namespace tetris

namespace tetris { namespace utility
{



class Matrix 
{
  private:
  std::unique_ptr<value_type[]> body;
  size_type nx, ny;

  public:
  Matrix()                                      noexcept;
  Matrix(const size_type &, const size_type &)  noexcept;
  ~Matrix()                           noexcept;

  Matrix(Matrix &&)                   noexcept;
  Matrix(const Matrix &)              noexcept;
  Matrix& operator=(Matrix &&);
  Matrix& operator=(const Matrix &);

  Matrix( const size_type &, const size_type &, 
          std::initializer_list<std::initializer_list<value_type>>) noexcept;

  // Other Operators
  public:
  value_type & operator()(size_type, size_type);
  const value_type & operator()(size_type, size_type) const;

  value_type & operator()(size_type);
  const value_type & operator()(size_type) const;

  Matrix operator+(Matrix &&);
  Matrix operator+(const Matrix &);

  Matrix& operator+=(Matrix &&);
  Matrix& operator+=(const Matrix &);

  Matrix operator*(Matrix &&);
  Matrix operator*(const Matrix &);

  Matrix& operator*=(Matrix &&);
  Matrix& operator*=(const Matrix &);

  friend std::ostream & operator<< (std::ostream &, const Matrix &);

  // Profiling Features
  public:
  size_type size() const noexcept;

  // 
  public:
  void reset()  noexcept;
  void fill()   noexcept;
  void assign(value_type)   noexcept;
  void assign(value_type &) noexcept;
  void swap(Matrix &)       noexcept;


}; // Matrix

class Grid_World
{
  private:
  Matrix Grid;

  public:
  Grid_World()                    noexcept = default; 
  Grid_World(const Grid_World &)            noexcept;
  Grid_World& operator=(const Grid_World &) noexcept;
  Grid_World(Grid_World &&)                 noexcept;
  Grid_World& operator=(Grid_World &&);
  ~Grid_World() { std::cout << "Calling Grid World Destructor." << std::endl; }


  Grid_World(size_type, size_type)  noexcept;

  // Other Operators  
  // ...
  value_type& operator()(size_type x, size_type y) { return Grid(x, y); }
  const value_type& operator()(size_type x, size_type y) const { return Grid(x, y); }

  // Other Features
  public:
  void ClearFullRows();
  void FixToGrid(const Tetromino &);
  void Draw();


  public:
  size_type nx, ny;

  friend std::ostream & operator<< (std::ostream &, const Grid_World &);
}; // end of class Grid_World


class Tetromino
{
  public:
  Tetromino()                             noexcept;
  Tetromino(const Tetromino &)            noexcept;
  Tetromino& operator=(const Tetromino &) noexcept;
  Tetromino(Tetromino &&)                 noexcept;
  Tetromino& operator=(Tetromino &&)      noexcept;

  value_type& operator()(size_type x, size_type y) { return NESW[idx](x, y); }
  const value_type& operator()(size_type x, size_type y) const { return NESW[idx](x, y); }

  public:
  void move(value_type);
  void Draw();
  bool isCollision(Grid_World &);

  value_type & x() { return coord(0, 0); }
  const value_type & x() const { return coord(0, 0); }
  value_type & y() { return coord(0, 1); }
  const value_type & y() const { return coord(0, 1); }

  private:
  static constexpr size_type count {4};
  std::vector<Matrix> NESW;
  Tetromino_type type;
  Matrix coord;
  size_type idx;
  std::vector<Matrix> Move;
  value_type move_interval {1.0f}, timer {0.0f};
}; // end of class Tetromino

}}


namespace tetris { namespace utility
{

inline 
void 
Tetromino::Draw()
{
for (size_type i = 0; i < count; ++i)
for (size_type j = 0; j < count; ++j)
if (NESW[idx](i,j) != 0)
DrawRectangle((i+coord(0, 0)) * 30, (j+coord(0, 1)) * 30, 30, 30, GRAY); // 绘制每个方块
}

inline 
void 
Tetromino::move(value_type delta_time)
{
  timer += delta_time;
  if (timer >= move_interval)
  {
    coord += Move[2];
    if (IsKeyDown(KEY_RIGHT)) coord += Move[0];
    if (IsKeyDown(KEY_LEFT))  coord += Move[1];
    if (IsKeyDown(KEY_DOWN))  coord += Move[2];
    timer = 0.0f;
  }
  if (IsKeyDown(KEY_UP))    ++idx; idx = idx % count;
}

inline 
bool
Tetromino::isCollision(Grid_World & Grid)
{
  for (size_type i = 0; i < count; ++i)
  {
    for (size_type j = 0; j < count; ++j)
    {
      if (NESW[idx](i,j) != 0)
      {
        
size_type newX = this->x() + i;
size_type newY = this->y() + j;
if (newX < 0 || newY < 0 || newX+1 >= Grid.nx || newY+1 >= Grid.ny || Grid(newX, newY) != 0) 
{ return true; }
      }
    }
  }
  return false;
}

inline 
Tetromino::Tetromino() 
noexcept
: type {static_cast<Tetromino_type>(rng(rde))},
  coord {1, 2, {{0, 0}}}, idx {0}, 
  Move {{
      {1, 2, {{1, 0}}},
      {1, 2, {{-1, 0}}},
      {1, 2, {{0, 1}}},
    }}
{
  NESW.reserve(count);
  switch (type)
  {
case L      : 
  std::cout << "Type: L " << std::endl;
  NESW = {{
    {count, count, {{ 0, 0, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 北
    {count, count, {{ 0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0 }}}, // 东
    {count, count, {{ 0, 0, 0, 0}, {1, 1, 1, 0}, {1, 0, 0, 0}, {0, 0, 0, 0 }}}, // 南
    {count, count, {{ 1, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
case J   :
  std::cout << "Type: J" << std::endl;
  NESW = {{
    {count, count, {{ 1, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 北
    {count, count, {{ 0, 1, 1, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}, // 东
    {count, count, {{ 0, 0, 0, 0}, {1, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0 }}}, // 南
    {count, count, {{ 0, 1, 0, 0}, {0, 1, 0, 0}, {1, 1, 0, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
case Z      :
  std::cout << "Type: Z " << std::endl;
  NESW = {{
    {count, count, {{ 1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 北
    {count, count, {{ 0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}, // 东
    {count, count, {{ 1, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 南
    {count, count, {{ 0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
case S   :
  std::cout << "Type: S " << std::endl;
  NESW = {{
    {count, count, {{ 0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 北
    {count, count, {{ 0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0 }}}, // 东
    {count, count, {{ 0, 1, 1, 0}, {1, 1, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 南
    {count, count, {{ 0, 1, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
case O   :
  std::cout << "Type: O " << std::endl;
  NESW = {{
    {count, count, {{ 0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0 }}}, // 北
    {count, count, {{ 0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0 }}}, // 东
    {count, count, {{ 0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0 }}}, // 南
    {count, count, {{ 0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
case I    :
  std::cout << "Type: I " << std::endl;
  NESW = {{
    {count, count, { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }}, // 
    {count, count, { {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0} }},
    {count, count, { {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0}, {0, 1, 0, 0} }},
    {count, count, { {0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0} }}
  }};
  break;
case T     :
  std::cout << "Type: T " << std::endl;
  NESW = {{
      {count, count, {{ 0, 0, 0, 0}, {1, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}, // 北
      {count, count, {{ 0, 1, 0, 0}, {1, 1, 0, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}, // 东
      {count, count, {{ 0, 1, 0, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {0, 0, 0, 0 }}}, // 南
      {count, count, {{ 0, 1, 0, 0}, {0, 1, 1, 0}, {0, 1, 0, 0}, {0, 0, 0, 0 }}}  // 西
  }};
  break;
default     :
  std::cout << "Unknown Type " << std::endl;
  break;
  }
  
}


} // namespace utility
} // namespace tetris



namespace tetris { namespace utility
{

inline 
Grid_World::Grid_World(size_type nx, size_type ny) 
noexcept
: Grid {Matrix(nx, ny)}, nx {nx}, ny {ny}
{ Grid.assign(0); }


inline 
void 
Grid_World::Draw()
{
  for (size_type i = 0; i < nx; ++i)
  {
    for (size_type j = 0; j < ny; ++j)
    {
      if (Grid(i,j) != 0)
      {
        DrawRectangle(i * 30, j * 30, 30, 30, GRAY); // 绘制每个方块
      }
      else 
      {
        DrawRectangle(i * 30, j * 30, 30, 30, PURPLE); // 绘制每个方块
      }
      DrawRectangleLines(i * 30, j * 30, 30, 30, GRAY);
    }
  }
}

inline
void 
Grid_World::FixToGrid(const Tetromino & tetromino)
{
  for (size_type i = 0; i < 4; ++i)
  {
    for (size_type j = 0; j < 4; ++j)
    {
      if (tetromino(i, j) != 0)
      {
size_type x { static_cast<size_type>(tetromino.x()) + i };
size_type y { static_cast<size_type>(tetromino.y()) + j };
Grid(x, y) = tetromino(i, j);
      }
    }
  }
}

inline
std::ostream & operator<< (std::ostream & os, const Grid_World & in)
{
  os << "Grid World: " << "\n" << in.Grid;
  // for (auto const & elem : in.UpperBoundary) os << elem << " ";
  // os << "\n";
  return os;
}

} // namespace utility
} // namespace tetris






namespace tetris { namespace utility
{


inline 
Matrix::Matrix() 
noexcept
: body { nullptr }, nx {0}, ny {0} 
{ std::cout << "Calling Default Constructor." << std::endl; }

inline 
Matrix::Matrix(const size_type & nx, const size_type & ny)
noexcept
: nx {nx}, ny {ny}, body { std::make_unique<Float[]>(nx*ny) }
{ std::cout << "Calling nx * ny Constructor." << std::endl;}

inline 
Matrix::Matrix(const size_type & nx, const size_type & ny, 
                std::initializer_list<std::initializer_list<value_type>> list)
noexcept
: nx {nx}, ny {ny}, body { std::make_unique<Float[]>(nx*ny) }
{ 
  std::cout << "Calling list Constructor." << std::endl; 
  size_type i {0};
  for (const auto& row : list) 
    for (const auto& element : row) 
      if (i < nx * ny)  body[i++] = element;
}



inline 
Matrix::~Matrix() 
noexcept
{ std::cout << "Calling Default Constructor." << std::endl; body.~unique_ptr(); nx = 0; ny = 0;}

inline 
Matrix::Matrix(Matrix && other) 
noexcept
: nx {other.nx}, ny {other.ny}
{
  std::cout << "Calling Move Constructor." << std::endl;
  if (this != &other) 
  {
    body = std::move(other.body);
    other.reset();
  }
}

inline 
Matrix::Matrix(const Matrix & other) 
noexcept
: body { std::make_unique<Float[]>(other.size()) }, 
  nx {other.nx}, ny {other.ny}
{
  std::cout << "Calling Copy Constructor. " << std::endl;
  std::copy(other.body.get(), 
            other.body.get() + other.size(), 
            body.get());
}


inline 
Matrix& Matrix::operator=(Matrix && other)
{
  std::cout << "Calling Move Assignment Operator = " << std::endl;
  if (this != &other)
  {
    body = std::move(other.body);
    nx = other.nx;
    ny = other.ny;

    other.reset();
  }
  return *this;
}

inline 
Matrix& Matrix::operator=(const Matrix & other)
{
  std::cout << "Calling Copy Assignment Operator = " << std::endl;
  if (this != &other)
  {
    body = std::make_unique<Float[]>(other.size());
    std::copy(other.body.get(),
              other.body.get() + other.size(), 
              body.get());
    nx = other.nx;
    ny = other.ny;
  }
  return *this;
}

inline 
value_type & Matrix::operator()(size_type ix, size_type jy)
{
  if (ix*ny+jy < this->size()) return body[ix*ny + jy]; 
  else  throw std::out_of_range("Index out of range.");
}

inline 
const
value_type & Matrix::operator()(size_type ix, size_type jy) 
const
{
  if (ix*ny+jy < this->size()) return body[ix*ny + jy]; 
  else  throw std::out_of_range("Index out of range.");
}


inline 
value_type & Matrix::operator()(size_type idx)
{
  if (idx < this->size()) return body[idx]; 
  else  throw std::out_of_range("Index out of range.");
}


inline 
const
value_type & Matrix::operator()(size_type idx) 
const
{
  if (idx < this->size()) return body[idx]; 
  else  throw std::out_of_range("Index out of range.");
}



inline 
Matrix Matrix::operator+(Matrix && other)
{
  ASSERT_TETRIS_MSG((other.nx == nx && other.ny == ny), "Add operator +, extents mismatch.");
  Matrix res {*this};
  for (size_type i = 0; i < res.size(); ++i) res.body[i] = body[i] + other(i);
  return res;
}

inline 
Matrix Matrix::operator+(const Matrix & other)
{
  ASSERT_TETRIS_MSG((other.nx == nx && other.ny == ny), "Add operator +, extents mismatch.");
  Matrix res {*this};
  for (size_type i = 0; i < res.size(); ++i) res.body[i] = body[i] + other(i);
  return res;
}

inline 
Matrix& Matrix::operator+=(Matrix && other)
{
  ASSERT_TETRIS_MSG((other.nx == nx && other.ny == ny), "Add operator +, extents mismatch.");
  for (size_type i = 0; i < this->size(); ++i) body[i] += other(i);
  return *this;
}

inline 
Matrix& Matrix::operator+=(const Matrix & other)
{
  ASSERT_TETRIS_MSG((other.nx == nx && other.ny == ny), "Add operator +, extents mismatch.");
  for (size_type i = 0; i < this->size(); ++i) body[i] += other(i);
  return *this;
}


inline 
Matrix Matrix::operator*(Matrix && other)
{
  ASSERT_TETRIS_MSG((other.nx == ny), "Multiply operator *, extents mismatch.");
  Matrix res(nx, other.ny);
  res.assign(0);
  for (size_type i = 0; i < nx; ++i)
    for (size_type j = 0; j < other.ny; ++j)
      for (size_type k = 0; k < ny; ++k)
        res(i,j) += (*this)(i, k) * other(k, j);

  return res;
}


inline 
Matrix Matrix::operator*(const Matrix & other)
{
  ASSERT_TETRIS_MSG((other.nx == ny), "Multiply operator *, extents mismatch.");
  Matrix res(nx, other.ny);

  res.assign(0);
  for (size_type i = 0; i < nx; ++i)
    for (size_type j = 0; j < other.ny; ++j)
      for (size_type k = 0; k < ny; ++k)
        res(i,j) += (*this)(i, k) * other(k, j);

  return res;
}

inline 
Matrix & Matrix::operator*=(Matrix && other)
{
  ASSERT_TETRIS_MSG((other.nx == ny), "Multiply operator *, extents mismatch.");
  Matrix res(nx, other.ny);

  res.assign(0);
  for (size_type i = 0; i < nx; ++i)
    for (size_type j = 0; j < other.ny; ++j)
      for (size_type k = 0; k < ny; ++k)
        res(i,j) += (*this)(i, k) * other(k, j);

  *this = std::move(res);
  return *this;
}

inline 
Matrix & Matrix::operator*=(const Matrix & other)
{
  ASSERT_TETRIS_MSG((other.nx == ny), "Multiply operator *, extents mismatch.");
  Matrix res(nx, other.ny);

  res.assign(0);
  for (size_type i = 0; i < nx; ++i)
    for (size_type j = 0; j < other.ny; ++j)
      for (size_type k = 0; k < ny; ++k)
        res(i,j) += (*this)(i, k) * other(k, j);

  *this = std::move(res);
  return *this;
}





inline 
size_type Matrix::size() 
const
noexcept
{ return nx*ny; }

inline 
void Matrix::reset()
noexcept
{ body = nullptr; nx = 0; ny = 0; }

inline
void Matrix::swap(Matrix & other)
noexcept
{
  body.swap(other.body);
  size_type pool { nx };
  nx = other.nx;
  other.nx = pool;

  pool = ny;
  ny = other.ny;
  other.ny = pool;
}


inline 
void Matrix::fill()
noexcept
{ for (size_type i = 0; i < this->size(); ++i) body[i] = static_cast<value_type>(i); }

inline 
void Matrix::assign(value_type val)
noexcept
{ std::fill_n(body.get(), this->size(), val); }

inline 
void Matrix::assign(value_type & val)
noexcept
{ std::fill_n(body.get(), this->size(), val); }

inline 
std::ostream & operator<<(std::ostream & os, const Matrix & in)
{
  
  for (size_type i = 0; i < in.nx; ++i)
  {
    os << "| ";
    for (size_type j = 0; j < in.ny; ++j)
    {
      os  << std::fixed 
          << std::setw(3) 
          << std::setprecision(0) 
          << in(i,j) << " ";
    }
    os << "|" << "\n";
  }
  os << std::endl;
  return os;
}


} // namespace utility
} // namespace tetris








