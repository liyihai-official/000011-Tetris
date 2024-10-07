#include <array>
#include <memory>
#include <raylib.h>
#include <types>
#include <assert>
#include <iostream>
#include <iomanip>

#define NX 1504
#define NY 846


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

  // Other Operators
  public:
  value_type operator()(size_type, size_type);
  const value_type operator()(size_type, size_type) const;

  Matrix operator+(Matrix &&);
  Matrix operator+(const Matrix &);

  // Matrix operator+=(Matrix &&);
  // Matrix operator+=(const Matrix &);

  // bool operator==(Matrix &&);
  // bool operator==(const Matrix &);


  friend std::ostream & operator<< (std::ostream &, const Matrix &);
  // Profiling Features
  public:
  Dword size() const noexcept;


  // 
  public:
  void reset() noexcept;
  void fill()  noexcept;



}; // Matrix


// class Grid_World
// {
//   private:


//   public:
//   Grid_World();
//   ~Grid_World() { std::cout << "Calling Grid World Destructor." << std::endl; }

//   Grid_World(Grid_World &&);
//   Grid_World(const Grid_World &);

//   Grid_World& operator=(Grid_World &&);
//   Grid_World& operator=(const Grid_World &);


//   public:
//   void ClearFullRows();
//   void UpdateUpperBounds();



//   private:





// }; // Grid_World
}}


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
value_type Matrix::operator()(size_type ix, size_type jy)
{ return body[ix*ny + jy]; }

inline 
const
value_type Matrix::operator()(size_type ix, size_type jy) 
const
{ return body[ix*ny + jy]; }


// inline 
// Matrix Matrix::operator+(Matrix && other)
// {
//   ASSERT_TETRIS_MSG((other.nx == nx && other.ny == ny), "Add operator +, extents mismatch.");
//   Matrix res {*this};
  
//   return res;
// }
//   // Matrix operator+(const Matrix &);



inline 
std::ostream & operator<<(std::ostream & os, const Matrix & in)
{
  for (size_type i = 0; i < in.nx; ++i)
  {
    std::cout << "| ";
    for (size_type j = 0; j < in.ny; ++j)
    {
      std::cout << std::fixed 
                << std::setw(9) 
                << std::setprecision(3) 
                << in(i,j) << " ";
    }
    std::cout << "|" << std::endl;;
  }
  std::cout << std::endl;
  return os;
}


inline 
Dword Matrix::size() 
const
noexcept
{ return nx*ny; }

inline 
void Matrix::reset()
noexcept
{ body = nullptr; nx = 0; ny = 0; }

inline 
void Matrix::fill()
noexcept
{ for (size_type i = 0; i < this->size(); ++i) body[i] = static_cast<value_type>(i); }


} // namespace utility
} // namespace tetris
