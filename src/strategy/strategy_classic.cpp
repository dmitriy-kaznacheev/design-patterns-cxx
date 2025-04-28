/*** DrawStrategy *************************/

template <typename Shape>
class DrawStrategy
{
public:
  virtual ~DrawStrategy() = default;
  virtual void draw(const Shape &s) const = 0;
};

/*** Shape ********************************/

class Shape
{
public:
  virtual ~Shape() = default;
  virtual void draw() = 0;
};

/*** Circle *******************************/

#include <memory>

class Circle : public Shape
{
public:
  using DrawCircleStrategy = DrawStrategy<Circle>;

  Circle(double radius, std::unique_ptr<DrawCircleStrategy> drawer)
    : radius_{ radius }
    , drawer_{ std::move(drawer) }
  {
  }

  void draw() override 
  { 
    drawer_->draw(*this);
  }

private:
  double radius_;
  std::unique_ptr<DrawCircleStrategy> drawer_;
};

/*** Square ******************************/

#include <memory>

class Square : public Shape
{
public:
  using DrawSquareStrategy = DrawStrategy<Square>;

  Square(double side, std::unique_ptr<DrawSquareStrategy> drawer)
    : side_{ side }
    , drawer_{ std::move(drawer) }
  {
  }

  void draw() override
  {
    drawer_->draw(*this);
  }

private:
  double side_;
  std::unique_ptr<DrawSquareStrategy> drawer_;
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

class OpenGLCircleStrategy : public DrawStrategy<Circle>
{
public:
  explicit OpenGLCircleStrategy()
  {
  }

  void draw(const Circle &c) const override
  {
    (void)c;
    std::cout << "draw Circle" << std::endl;
  }
};


class OpenGLSquareStrategy : public DrawStrategy<Square>
{
public:
  explicit OpenGLSquareStrategy()
  {
  }

  void draw(const Square &s) const override
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
    std::make_unique<Circle>(
      1.1,
      std::make_unique<OpenGLCircleStrategy>()
    )
  );
  shapes.emplace_back( 
    std::make_unique<Square>(
      2.2,
      std::make_unique<OpenGLSquareStrategy>()
    ) 
  );
  shapes.emplace_back( 
    std::make_unique<Circle>(
      3.3,
      std::make_unique<OpenGLCircleStrategy>()
    ) 
  ); 

  draw_shapes(shapes);

  return EXIT_SUCCESS;
}
