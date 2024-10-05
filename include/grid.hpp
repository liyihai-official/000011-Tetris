#include <array>
#include <memory>
#include <raylib.h>

#define NX 1504
#define NY 846

class Matrix // 
{
  private:
  std::unique_ptr<float[]> body; 

  public:
  Matrix();
  ~Matrix();

  Matrix(Matrix &&);
  Matrix(const Matrix &);
  Matrix& operator=(Matrix &&);
  Matrix& operator=(const Matrix &);

  public:
  // Matrix operator+(Matrix &&);
  // Matrix operator+(const Matrix &);

  // Matrix operator+=(Matrix &&);
  // Matrix operator+=(const Matrix &);

  // bool operator==(Matrix &&);
  // bool operator==(const Matrix &);

  



}; // Matrix


class Grid_World
{
  private:


  public:
  Grid_World();
  ~Grid_World() { std::cout << "Calling Grid World Destructor." << std::endl; }

  Grid_World(Grid_World &&);
  Grid_World(const Grid_World &);

  Grid_World& operator=(Grid_World &&);
  Grid_World& operator=(const Grid_World &);


  public:
  void ClearFullRows();
  void UpdateUpperBounds();



  private:





}; // Grid_World


