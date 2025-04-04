#include <iostream>
#include <iomanip>

#include <Box.h>
#include <LineSegment.h>
#include <BrokenLine.h>
#include <Rectangle.h>

int main()
{
  std::cout << "Line Segment start: " << std::endl;

  LineSegment segment({4, 5}, {2,5});
  std::cout << "start = x: " << segment.start.x << std::endl;
  std::cout << std::setw(11) << "y: " << segment.start.y << std::endl;
  std::cout << "end = x: " << segment.end.x << std::endl;
  std::cout << std::setw(9) << "y: " << segment.end.y << std::endl;

  std::cout << "InBox: " << std::boolalpha << segment.InBox({{0, 0}, {10, 10}}) << std::endl;
  std::cout << "Intersects Point: " << segment.IntersectsPoint(segment.start, 1) << std::endl;

  std::cout << "Line Segment end.\n\n";

  std::cout << "Broken Line start:" << std::endl;

  BrokenLine brokenLine({{0, 0}, {1, 1}});
  std::cout << "Points: " << std::endl;
  const std::vector<Point> points = brokenLine.GetPoints();
  for (const Point & point : points)
    std::cout << "x y: " << point.x << " " << point.y << std::endl;

  std::cout << "InBox: " << brokenLine.InBox({{0, 0}, {10, 10}}) << std::endl;
  std::cout << "Intersects Point: " << brokenLine.IntersectsPoint(segment.start, 100) << std::endl;

  std::cout << "Broken Line end.\n\n";

  std::cout << "Rectangle start: " << std::endl;

  Rectangle rect({ 1, 2 }, {3, 4});
  std::cout << "top left x y: " << rect.TopLeft().x << " " << rect.TopLeft().y << std::endl;
  std::cout << "bottom right x y: " << rect.BottomRight().x << " " << rect.BottomRight().y << std::endl;

  std::cout << "InBox: " << rect.InBox({{0, 0}, {10, 10}}) << std::endl;
  std::cout << "Intersects Point: " << rect.IntersectsPoint(segment.start, 1) << std::endl;

  std::cout << "Rectangle end.\n\n";

}
