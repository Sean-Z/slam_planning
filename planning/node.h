#ifndef NODE_H
#define NODE_H
#include <math.h>

class node
{

public:
    node(): node(0, 0, 0, 0, nullptr) {}
    node(int x, int y, float g, float h, node* pred) {
        this->x = x;
        this->y = y;

        this->g = g;
        this->h = h;
        this->pred = pred;
        this->idx = -1;
    }
    ~node(){};

    // A*邻居节点的扩充方向
    static const int dir = 8;
    int dx[8] = {-1,-1, 0, 1, 1, 1, 0,-1};
    int dy[8] = { 0, 1, 1, 1, 0,-1,-1,-1};


    void open()  { o = true; c = false; }
    void close() { c = true; o = false; }
    void reset() { c = false; o = false;}
    void discover() { d = true; }

    float getC() const { return g + h; }
    float getG() const { return g; }
    int getX() const { return x;}
    int getY() const { return y;}
    const node* getPred() const { return pred; }

    bool isOpen() const { return o; }
    bool isClosed() const { return c; }
    bool isOnGrid(const int width, const int height) const;


    int setIdx(int width) { this->idx = y * width + x; return idx;}
    void setPred(const node* pred) { this->pred = pred; }
    node* createSuccessor(const int i);

    void updateG() { g += movementCost(*pred); d = true; }
    void updateH(const node& goal) { h = movementCost(goal); }
    float movementCost(const node& pred) const { return sqrt((x - pred.x) * (x - pred.x) + (y - pred.y) * (y - pred.y)); }
    bool operator == (const node& rhs) const;



    int x;              //节点的横坐标
    int y;              //节点的纵坐标
private:
    int idx;            //节点的序号
    float g;            //到起点的代价
    float h;            //到终点的代价
    bool o;             //节点的状态 open
    bool c;             //节点的状态 close
    bool d;             //已经遍历过该节点
    const node* pred;   //父节点
};

#endif // NODE_H
