/*** ShapeVisitor ************************/

class AbstractVisitor
{
public:
  virtual ~AbstractVisitor() = default;
};

template <typename Shape>
class Visitor
{
public:
  virtual void visit(const Shape &shape) const = 0;

protected:
  virtual ~Visitor() = default;
};

/*** Shape ********************************/

class Shape
{
public:
  virtual ~Shape() = default;
  virtual void accept(const AbstractVisitor &v) = 0;
};

/*** Circle *******************************/

class Circle : public Shape
{
public:
  Circle(double radius)
    : radius_{ radius }
  {
  }

  void accept(const AbstractVisitor &v) override 
  { 
    if (const auto *cv = dynamic_cast<const Visitor<Circle>*>(&v)) {
      cv->visit(*this); 
    }
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

  void accept(const AbstractVisitor &v) override
  {
    if (const auto *cv = dynamic_cast<const Visitor<Square>*>(&v)) {
      cv->visit(*this);
    }
  }

private:
  double side_;
};

/*** draw ********************************/

#include <memory>
#include <vector>
#include <iostream> /* какая-нибудь графическая библиотека */

class Draw final 
  : public AbstractVisitor
  , public Visitor<Circle>
  , public Visitor<Square>
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
