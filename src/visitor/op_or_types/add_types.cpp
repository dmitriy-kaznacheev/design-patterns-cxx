/*** Point *******************************/

struct Point
{
  double x, y;
};

/*** Shape ********************************/

#include <iostream> /* какая-нибудь графическая библиотека */

class Shape
{
public:
  Shape() = default;
  virtual ~Shape() = default;
  virtual void draw() const = 0;
};

/*** Circle *******************************/

class Circle : public Shape
{
public:
  Circle(double radius, Point center)
    : radius_{ radius }
    , center_{ center }
  {
  }

  void draw() const override
  {
    std::cout << "draw Circle" << std::endl;
  }

private:
  double radius_;
  Point center_;
};

/*** Square ******************************/

class Square : public Shape
{
public:
  Square(double side, Point center)
    : side_{ side }
    , center_{ center }
  {
  }

  void draw() const override
  {
    std::cout << "draw Square" << std::endl;
  }

private:
  double side_;
  Point center_;
};

/*** draw ********************************/

#include <memory>
#include <vector>

void draw_shapes(const std::vector<std::unique_ptr<Shape>> &shapes)
{
  for (const auto &shape : shapes)
  {
    shape->draw();
  }
}

/*** main *********************************/

#include <cstdlib>
#include <memory>
#include <vector>

int main()
{
   using Shapes = std::vector<std::unique_ptr<Shape>>;

   Shapes shapes{};
   shapes.emplace_back( std::make_unique<Circle>(1.1, Point{}) );
   shapes.emplace_back( std::make_unique<Square>(2.2, Point{}) );
   shapes.emplace_back( std::make_unique<Circle>(3.3, Point{}) );

   draw_shapes(shapes);

   return EXIT_SUCCESS;
}
