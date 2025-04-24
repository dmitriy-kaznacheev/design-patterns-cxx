/*** Point *******************************/

struct Point
{
  double x, y;
};

/*** Shape ********************************/

enum ShapeType
{
  CIRCLE,
  SQUARE
};

class Shape
{
public:
  virtual ~Shape() = default;
  
  ShapeType get_type() const
  {
    return type_;
  }

protected:
  Shape(ShapeType type)
    : type_{ type }
  {
  }

private:
  ShapeType type_;
};

/*** Circle *******************************/

class Circle : public Shape
{
public:
  Circle(double radius, Point center)
    : Shape{ CIRCLE }
    , radius_{ radius }
    , center_{ center }
  {
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
    : Shape{ SQUARE }
    , side_{ side }
    , center_{ center }
  {
  }

private:
  double side_;
  Point center_;
};

/*** draw ********************************/

#include <memory>
#include <vector>
#include <iostream> /* какая-нибудь графическая библиотека */

void draw(const Circle &circle)
{
  std::cout << "draw Circle" << std::endl; 
}

void draw(const Square &square)
{
  std::cout << "draw Square" << std::endl; 
}

void draw_shapes(const std::vector<std::unique_ptr<Shape>> &shapes)
{
  for (const auto &shape : shapes)
  {
    switch (shape->get_type())
    {
      case CIRCLE:
        draw( static_cast<const Circle&>(*shape) );
        break;
      case SQUARE:
        draw( static_cast<const Square&>(*shape) );
        break;
    }
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
