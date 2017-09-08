#include "boundaryDetection.hpp"
#include "CalculateGap.hpp"

using namespace std;

Rect getBoundingBox(std::list<Point_2> points)
{
  /**
   * Returns axis-aligned bounding box of 2D points
   */
  Rect box = CGAL::bounding_box(points.begin(), points.end());
  // std::cout << box << std::endl;
  return box;
}


list<Segment> getSegments(std::list<Line> lines) {
  /**
   * Return CGAL::segments from myGeometry lines, this weill removed later
   * TODO : Remove this method.
   */
  list<Segment> segments;

  for (list<Line>::iterator it = lines.begin(); it != lines.end(); it++) {
    Point_2 start(it->start.x, it->start.y);
    Point_2 end(it->end.x, it->end.y);
    Segment segment(start, end);
    segments.push_back(segment);
  }

  return segments;
}

bool doIntersect(Segment a, Segment b ){
 /**
  * This replaces CGAL::do_intersect(), becuase it does not work with VS2017 compiler.
  * This returns true if the two given line segments intersects
  * https://stackoverflow.com/questions/14176776/find-out-if-2-lines-intersect
  */

  Point_2 p1 = a.source();
  Point_2 p2 = a.target();
  Point_2 q1 = b.source();
  Point_2 q2 = b.target();

  bool ans1 =  (((q1.x()-p1.x())*(p2.y()-p1.y()) - (q1.y()-p1.y())*(p2.x()-p1.x())) * ((q2.x()-p1.x())*(p2.y()-p1.y()) - (q2.y()-p1.y())*(p2.x()-p1.x())) < 0);
  bool ans2 = (((p1.x()-q1.x())*(q2.y()-q1.y()) - (p1.y()-q1.y())*(q2.x()-q1.x())) * ((p2.x()-q1.x())*(q2.y()-q1.y()) - (p2.y()-q1.y())*(q2.x()-q1.x())) < 0);

 return (ans1 && ans2);
}

bool doIntersect(Segment line, std::list<Segment> lines, Segment except_line) {
  /**
   * Check if the passed line segments intersects with any of the
   * lines inside the given list of lines without checking for the
   * line that is an exception.
   */

  for (std::list<Segment>::iterator it = lines.begin(); it != lines.end(); it++)
    if(*it == except_line)
      continue;
    else if(doIntersect(line , *it))
      return true;
  return false;
}

std::list<Segment> removeInnerLines(std::list<Line> temp_lines) {
    /**
     * Returns the lines that lies outside-most in the given list of
     * lines. Special algorithm , slow now thou.
     */
    list<Segment> boundaries;

    list<Point_2> points = getSources(temp_lines);   // Get points from lines
    list<Segment> lines  = getSegments(temp_lines);  // Get CGAL segments from my lines
    Rect box             = getBoundingBox(points);   // Get the bounding box of the points

    for (list<Segment>::iterator it = lines.begin(); it != lines.end(); it++) {
        // Test 01: Check for intersections to the left
        Point_2 midpoint = getMidPoint(*it);  // Get the midpoint

        // Make line from midpoint to sides of the bounding box
        Point_2 point_left(box.xmin(), midpoint.y());
        Point_2 point_right(box.xmax(), midpoint.y());
        Point_2 point_up(midpoint.x(), box.ymax());
        Point_2 point_down(midpoint.x(), box.ymin());

        Segment test_line1(midpoint, point_left);
        Segment test_line2(midpoint, point_right);
        Segment test_line3(midpoint, point_up);
        Segment test_line4(midpoint, point_down);

        // If the test lines does not intersect in any one of the side
        // then that is a boundary
        if (!doIntersect(test_line1, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line2, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line3, lines, *it)) {
            boundaries.push_back(*it);
        } else if (!doIntersect(test_line4, lines, *it)) {
            boundaries.push_back(*it);
        } else
            continue;
    }

    return boundaries;
}

Polygon_2 getPolygon(std::list<Point_2> points){
    /**
     * Returns a cgal polygon from the given list of points. Remember
     * points passed should already be sorted clockwise. Or error will thrown.
     */

    Polygon_2 polygon;
    for (list<Point_2>::iterator it = points.begin(); it != points.end(); it++) {
        polygon.push_back(*it);
    }
    return polygon;
}
