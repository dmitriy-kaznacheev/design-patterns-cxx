/*** Circle *******************************/

class Circle final
{
public:
  Circle(double radius)
    : radius_{ radius }
  {
  }

private:
  double radius_;
};

/*** Square ******************************/

class Square final
{
public:
  Square(double side)
    : side_{ side }
  {
  }

private:
  double side_;
};

/*** Shape ********************************/

#include <variant>

using Shape = std::variant<Circle, Square>;

/*** draw ********************************/

#include <vector>
#include <iostream> /* какая-нибудь графическая библиотека */

struct Draw final
{
  void operator()(const Circle &c) const
  {
    (void) c;
    std::cout << "draw Circle" << std::endl; 
  }

  void operator()(const Square &s) const
  {
    (void) s;
    std::cout << "draw Square" << std::endl; 
  }

  // другие oerator() для каждой фигуры
};

void draw_shapes(const std::vector<Shape> &shapes)
{
  for (const auto &shape : shapes)
  {
    std::visit( Draw{}, shape );
  }
}

/*** main *********************************/

#include <vector>

int main()
{
   using Shapes = std::vector<Shape>;

   Shapes shapes{};
   shapes.emplace_back( Circle{1.1} );
   shapes.emplace_back( Square{2.2} );
   shapes.emplace_back( Circle{3.3} ); 

   draw_shapes(shapes);

   return EXIT_SUCCESS;
}
