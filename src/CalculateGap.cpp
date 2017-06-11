#include "CalculateGap.hpp"
#include "PrimitiveTile.hpp"
#include "myGeometry.hpp"
#include <math.h>

#define PI 3.14159265
using namespace std;

double getGap(Tile tile) {
  /*
   * This is the main method that returns the gap minimum between the
   * tiles when arranged with any particular order. Current this only
   * calculates gap between primitive tiles of size 2.
   */
  double tile_area = getTileArea(tile);
  PrimitiveTile p_tile(tile);
  double p_tile_area = 0;
  double gap_list[25] = {0}; // 25 is the maximum number of
  // combinations in this case.
  int gap_index = 0;
  if (!validateTile(tile))
    return -101; // Negative gap means the tile is not valid.
  int i = 3;
  int j = 3;
  p_tile.del(); // Reset the primitiveTile
  Link link(tile.side[i], tile.side[j]);
  if (p_tile.isLinkable(link)) {
    p_tile.addTile(i,j); // i and j are the side indexs that are linked.
    p_tile_area = p_tile.size * tile_area;
    p_tile.drawPrimitiveTile();
    gap_list[gap_index] = calculateGap(p_tile, p_tile_area);
  }

  // Returning the minimumgap in the gap list
  double min_gap = gap_list[0];
  double gap_list_size = sizeof(gap_list);
  for (int i = 0; i < gap_list_size; ++i) {
    if (gap_list[i] < min_gap)
      min_gap = gap_list[i];
  }
  return min_gap;
}

bool validateTile(Tile tile) {
  /*
   * This method returns whether the Tile inputted is valid or not.
   * This method is used by getgap()
   */
  double max_side = getMaxSide(tile);
  double max_angle = getMaxAngle(tile);
  if (max_angle <= 180.00)
    if (tile.angle[4] > 0)
      if (tile.side[0].value + tile.side[1].value + tile.side[2].value +
	  tile.side[3].value + tile.side[4].value >
          (2 * max_side))
        // 2 x Biggest side becauase we don't know which one is the
        // biggest side now and we should count that twice on the right
        // side because we are taking the sum of all sides instead of
        // the other 4..soo..
        return true;
      else
        return false;
    else
      return false;
  else
    return false;
}

double getMaxSide(Tile tile) {
  /*
   * This method returns the biggest side of the tile.
   */
  double max_side = tile.side[0].value;
  for (int i = 0; i < 5; ++i) {
    if (tile.side[i].value > max_side)
      max_side = tile.side[i].value;
  }
  return max_side;
}

double getMaxAngle(Tile tile) {
  /*
   * This method returns the biggest angle of the tile.
   */
  double max_angle = tile.angle[0];
  for (int i = 0; i < 5; ++i) {
    if (tile.angle[i] > max_angle)
      max_angle = tile.angle[i];
  }
  return max_angle;
}

double getThirdSide(Side a, Side b, double angle) {
  /*
   * This method returns the third side of the triangle formed inside
   * a polygon used for area calculating purposes
   */
  angle = angle * PI / 180;
  double side_c = sqrt((a.value * a.value) + (b.value * b.value) -
                       (2 * a.value * b.value * cos(angle)));
  return side_c;
}

double getTriangleArea(double a, double b, double c) {
  /*
   * This method returns the Area of the triagle using Heron's
   * Formulae
   */
  double S = (a + b + c) / 2;
  double area = sqrt(S * (S - a) * (S - b) * (S - c));
  return area;
}

double getTileArea(Tile tile) {
  /*
   * This method returns the Area of the pentagon dividing it into
   * three triangles, calculating its area and summing them up.
   */
  double ac = getThirdSide(tile.side[0], tile.side[1], tile.angle[1]);
  double ce = getThirdSide(tile.side[2], tile.side[3], tile.angle[3]);
  double triangle1 =
      getTriangleArea(tile.side[0].value, tile.side[1].value, ac);
  double triangle2 =
      getTriangleArea(tile.side[2].value, tile.side[3].value, ce);
  double triangle3 = getTriangleArea(ac, ce, tile.side[4].value);
  double pentagonArea = triangle1 + triangle2 + triangle3;
  return pentagonArea;
}

double calculateGap(PrimitiveTile p_tile, double p_tile_area) {
  Square square;
  double gap = 0;
  square = p_tile.drawSquare(p_tile_area);
  return gap;
}
