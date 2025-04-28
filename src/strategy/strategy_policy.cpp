/*** Shape ********************************/

class Shape
{
public:
  virtual ~Shape() = default;
  virtual void draw() = 0;
};

/*** Circle *******************************/

#include <memory>

template <typename DrawStrategy>
class Circle : public Shape
{
public:
  Circle(double radius, DrawStrategy drawer)
    : radius_{ radius }
    , drawer_{ std::move(drawer) }
  {
  }

  void draw() override 
  { 
    drawer_(*this);
  }

private:
  double radius_;
  DrawStrategy drawer_;
};

/*** Square ******************************/

#include <memory>

template <typename DrawStrategy>
class Square : public Shape
{
public:
  Square(double side, DrawStrategy drawer)
    : side_{ side }
    , drawer_{ std::move(drawer) }
  {
  }

  void draw() override
  {
    drawer_(*this);
  }

private:
  double side_;
  DrawStrategy drawer_;
};

/*** draw ********************************/

#include <memory>
#include <vector>
#include <iostream> /* какая-нибудь графическая библиотека */

void draw_shapes(const std::vector<std::unique_ptr<Shape>> &shapes)
{
  for (const auto &shape : shapes)
  {
    shape->draw();
  }
}

/*** OpenGLDrawStrategy *******************/

//#include /* OpenGL graphics library */

struct DrawCircleStrategy
{
  void operator()(const Circle<DrawCircleStrategy> &c)
  {
    (void)c;
    std::cout << "draw Circle" << std::endl;
  }
};

struct DrawSquareStrategy
{
  void operator()(const Square<DrawSquareStrategy> &s)
  {
    (void)s;
    std::cout << "draw Square" << std::endl;
  }
};

/*** main *********************************/

#include <cstdlib>
#include <memory>
#include <vector>

int main()
{
  using Shapes = std::vector<std::unique_ptr<Shape>>;

  Shapes shapes{};

  shapes.emplace_back( 
    std::make_unique<Circle<DrawCircleStrategy>>(
      1.1,
      DrawCircleStrategy{}
    )
  );
  shapes.emplace_back( 
    std::make_unique<Square<DrawSquareStrategy>>(
      2.2,
      DrawSquareStrategy{}
    ) 
  );
  shapes.emplace_back( 
    std::make_unique<Circle<DrawCircleStrategy>>(
      3.3,
      DrawCircleStrategy{}
    ) 
  ); 

  draw_shapes(shapes);

  return EXIT_SUCCESS;
}
