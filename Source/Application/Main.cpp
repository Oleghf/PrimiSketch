#include <iostream>
#include <iomanip>

#include <LineSegment.h>

int main()
{
  LineSegment segment({4, 5}, {2,5});

  std::cout << "start = x: " << segment.start.x << std::endl;
  std::cout << std::setw(11) << "y: " << segment.start.y << std::endl;

  std::cout << "end = x: " << segment.end.x << std::endl;
  std::cout << std::setw(9) << "y: " << segment.end.y << std::endl;
}
