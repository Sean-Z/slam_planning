#include "node.h"
bool node::operator == (const node& rhs) const {
  return x == rhs.x && y == rhs.y;
}
node* node::createSuccessor(const int i) {
  int xSucc = x + dx[i];
  int ySucc = y + dy[i];
  return new node(xSucc, ySucc, g, h, k, this);
}

double node::Distance_Angle(const node& newnode, int width, int height)
{
    double azimuth_curr = 360 / width * x * PI /180;
    double elevation_curr = (90 - 180 / height * y) * PI / 180;

    double x_curr = cos(elevation_curr) * cos(azimuth_curr);
    double y_curr = cos(elevation_curr) * sin(azimuth_curr);
    double z_curr = sin(elevation_curr);

    double azimuth_pre = 360 / width * newnode.x;
    double elevation_pre = 90 - 180 / height * newnode.y;

    double x_pre = cos(elevation_pre) * cos(azimuth_pre) * PI /180;
    double y_pre = cos(elevation_pre) * sin(azimuth_pre) * PI /180;
    double z_pre = sin(elevation_pre);

    double up = x_curr * x_pre + y_curr * y_pre + z_curr * z_pre;
    double down = sqrt(x_curr * x_curr + y_curr * y_curr + z_curr * z_curr) * sqrt(x_pre * x_pre + y_pre * y_pre + z_pre * z_pre);
    return fabs(acos((up) / (down)));

}
bool node::isOnGrid(const int width, const int height) const {
  return  x >= 0 && x < width && y >= 0 && y < height;
}
