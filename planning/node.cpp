#include "node.h"
bool node::operator == (const node& rhs) const {
  return x == rhs.x && y == rhs.y;
}
node* node::createSuccessor(const int i) {
  int xSucc = x + dx[i];
  int ySucc = y + dy[i];
  return new node(xSucc, ySucc, g, 0, this);
}
bool node::isOnGrid(const int width, const int height) const {
  return  x >= 0 && x < width && y >= 0 && y < height;
}
