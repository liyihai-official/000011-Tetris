#include <array>
#include <memory>
#include <raylib.h>
#include <types>
#include <assert>
#include <iostream>


#define NX 1504
#define NY 846

// namespace tetris { namespace utility {




// } // namespace utility
// } // namespace tetris


namespace tetris { namespace utility
{



class Matrix 
{
  private:
  std::unique_ptr<Float[]> body;
  Word nx, ny;

  public:
  Matrix()                            noexcept;
  Matrix(const Word &, const Word &)  noexcept;
  ~Matrix()                           noexcept;

  Matrix(Matrix &&)                   noexcept;
  Matrix(const Matrix &)              noexcept;
  Matrix& operator=(Matrix &&);
  Matrix& operator=(const Matrix &);

  // Other Operators
  public:
  // Matrix operator+(Matrix &&);
  // Matrix operator+(const Matrix &);

  // Matrix operator+=(Matrix &&);
  // Matrix operator+=(const Matrix &);

  // bool operator==(Matrix &&);
  // bool operator==(const Matrix &);

  // Profiling Features
  public:
  Dword size() const noexcept;


  // 
  public:
  void reset() noexcept;



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
Matrix::Matrix(const Word & nx, const Word & ny)
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
Dword Matrix::size() 
const
noexcept
{ return nx*ny; }

inline 
void Matrix::reset()
noexcept
{ body = nullptr; nx = 0; ny = 0; }




} // namespace utility
} // namespace tetris
