#ifndef PLAN_H
#define PLAN_H
#include "node.h"
#include <utility>
#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <boost/heap/binomial_heap.hpp>

struct CompareNodes {
  /// Sorting 2D nodes by increasing C value - the total estimated cost
  bool operator()(const node* lhs, const node* rhs) const {
    return lhs->getC() > rhs->getC();
  }
};

class plan
{
public:
    plan();
    ~plan(){}
public:
    void Plannig();
    node* Astar();
    bool Valid_Point();              //判断起点和终点是否合法
    void TracePath(const node* path_end,std::vector<node> path = std::vector<node>());

public:
    //std::pair<int,int> start;       // 起点位置
    //std::pair<int,int> end;         // 终点位置
    cv::Mat img;
    cv::Point p;
    node start;
    node end;
    double *map;                    // 地图数组指针
    node *nodes;                    // 节点地图
    int width;                      // 地图宽度
    int height;                     // 地图高度
    int distance_mahaton;           // 起点到终点的曼哈顿距离
    std::vector<node> path;
};

#endif // PLAN_H
