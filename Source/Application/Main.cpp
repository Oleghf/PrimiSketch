#include <iostream>
#include <iomanip>

#include <LineSegment.h>
#include <BrokenLine.h>
#include <Rectangle.h>

int main()
{
  LineSegment segment({4, 5}, {2,5});

  std::cout << "start = x: " << segment.start.x << std::endl;
  std::cout << std::setw(11) << "y: " << segment.start.y << std::endl;

  std::cout << "end = x: " << segment.end.x << std::endl;
  std::cout << std::setw(9) << "y: " << segment.end.y << std::endl;

  BrokenLine brokenLine({segment});

  std::cout << "broken line length: " << brokenLine.Length() << std::endl;
  
  for (const LineSegment & segment : brokenLine.GetSegments())
  {
    std::cout << "broken line segment start point x y: " << segment.start.x << " " << segment.end.y << std::endl;
    std::cout << "broken line segment end point x y: " << segment.end.x << " " << segment.end.y << std::endl << std::endl;
  }

  Rectangle rect({ 1, 2 }, {3, 4});

  std::cout << "rect top left x y: " << rect.TopLeft().x << " " << rect.TopLeft().y << std::endl;
  std::cout << "rect bottom right x y: " << rect.BottomRight().x << " " << rect.BottomRight().y << std::endl;

}
