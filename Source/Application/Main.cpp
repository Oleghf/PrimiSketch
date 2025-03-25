#include <iostream>
#include <iomanip>

#include <LineSegment.h>
#include <BrokenLine.h>
#include <Rectangle.h>

int main()
{
  LineSegment segment({4, 5}, {2,5});

  std::cout << "Line Segment start: " << std::endl;
  std::cout << "start = x: " << segment.start.x << std::endl;
  std::cout << std::setw(11) << "y: " << segment.start.y << std::endl;

  std::cout << "end = x: " << segment.end.x << std::endl;
  std::cout << std::setw(9) << "y: " << segment.end.y << std::endl;
  std::cout << "Line Segment end.\n\n";

  std::cout << "Broken Line start :" << std::endl;

  BrokenLine brokenLine({segment});

  std::cout << "length: " << brokenLine.Length() << std::endl;
  
  const std::vector<LineSegment> lineSegments = brokenLine.GetSegments();
  for (const LineSegment & segment : lineSegments)
  {
    std::cout << "segment start x y: " << segment.start.x << " " << segment.start.y << std::endl;
    std::cout << "segment end x y: " << segment.end.x << " " << segment.end.y << std::endl;
  }

  std::cout << "Broken Line end.\n\n";

  std::cout << "Rectangle start: " << std::endl;
  Rectangle rect({ 1, 2 }, {3, 4});

  std::cout << "rect top left x y: " << rect.TopLeft().x << " " << rect.TopLeft().y << std::endl;
  std::cout << "rect bottom right x y: " << rect.BottomRight().x << " " << rect.BottomRight().y << std::endl;

  std::cout << "Rectangle end.\n\n";

}
