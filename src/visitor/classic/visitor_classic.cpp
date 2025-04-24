/*** ShapeVisitor ************************/

class Circle;
class Square;

class ShapeVisitor
{
public:
  virtual ~ShapeVisitor() = default;

  virtual void visit(const Circle &c) const = 0;
  virtual void visit(const Square &s) const = 0;
  // другие функции visit() для каждой фигуры
};

/*** Shape ********************************/

class Shape
{
public:
  virtual ~Shape() = default;
  virtual void accept(const ShapeVisitor &v) = 0;
};

/*** Circle *******************************/

class Circle : public Shape
{
public:
  Circle(double radius)
    : radius_{ radius }
  {
  }

  void accept(const ShapeVisitor &v) override 
  { 
    v.visit(*this); 
  }

private:
  double radius_;
};

/*** Square ******************************/

class Square : public Shape
{
public:
  Square(double side)
    : side_{ side }
  {
  }

  void accept(const ShapeVisitor &v) override
  {
    v.visit(*this);
  }

private:
  double side_;
};

/*** draw ********************************/

#include <memory>
#include <vector>
#include <iostream> /* какая-нибудь графическая библиотека */

class Draw final : public ShapeVisitor
{
  virtual void visit(const Circle &c) const override
  {
    (void) c;
    std::cout << "draw Circle" << std::endl; 
  }

  virtual void visit(const Square &s) const override
  {
    (void) s;
    std::cout << "draw Square" << std::endl; 
  }

  // другие функции visit() для каждой фигуры
};

void draw_shapes(const std::vector<std::unique_ptr<Shape>> &shapes)
{
  for (const auto &shape : shapes)
  {
    shape->accept( Draw{} );
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
   shapes.emplace_back( std::make_unique<Circle>(1.1) );
   shapes.emplace_back( std::make_unique<Square>(2.2) );
   shapes.emplace_back( std::make_unique<Circle>(3.3) ); 

   draw_shapes(shapes);

   return EXIT_SUCCESS;
}
