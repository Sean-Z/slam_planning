#include "plan.h"

plan::plan()
{
    img = cv::imread("D:\\opencv\\2.tif",2);

    width = img.cols - 1;
    height = img.rows - 1;
    map = new double[width * height];

    // 构造地图
    for(int i = 0; i < height; i++)
        for(int j= 0; j < width; j++)
        {
            map[j + i * width] = img.at<float>(i,j);
        }


    // 设置起始点和终止点
    start.x = 100;
    start.y = 90;

    end.x = 255;
    end.y = 30;

    distance_mahaton = std::abs(start.x - end.x) + std::abs(start.y - end.y);

    // 开始规划
    Plannig();
//    std::cout << "***" << std::endl;

    // opencv画轨迹
    for(int i = 0; i < path.size(); i++)
    {
        cv::Point tmp_p(path[i].x,path[i].y);
        cv::circle(img,tmp_p,1,cv::Scalar(255,255,255),-1);
    }


    cv::imshow("MAP", img);
}

void plan::Plannig()
{
    // 判断起点或终点是否合法
    if(!Valid_Point())
    {
        std::cout << "start or end out of map range,process end！" << std::endl;
        return;
    }
    //std::cout << img.at<float>()<<std::endl;
    std::cout << "start planning..."<<std::endl;
    nodes = new node[width * height];
    node* path_end = Astar();
    TracePath(path_end);

    for(int i = 0;i < path.size();++i)
    {
        std::cout << "x: " << path[i].x << " y: " << path[i].y << std::endl;
    }
}

node* plan::Astar()
{
    int iPred, iSucc;
    float newG;

    // 节点地图置空，初始化
    for(int i = 0; i < width * height; i ++)
    {
        nodes[i].reset();
    }

    boost::heap::binomial_heap<node*,boost::heap::compare<CompareNodes>> OpenList; //新建开始列表

    // 对初始点进行操作，更新g值和k值
    start.updateH(end,width,height);
    start.updateK(img);

    // 将初始点加入到openlist中，包括<1> 将该点标记为open,<2> 将该点放入到openlist中,<3> 将该点放入到node中
    start.open();
    OpenList.push(&start);
    iPred = start.setIdx(width);
    nodes[iPred] = start;

    node* nPred;    // 当前节点
    node* nSucc;    // 扩充节点

    while (!OpenList.empty())
    {

        nPred = OpenList.top();         // 弹出节点
        iPred = nPred->setIdx(width);   // 获得节点序号
        if (nodes[iPred].isClosed())
        {
            //std::cout <<"$$$"<<std::endl;
            OpenList.pop();             // 如果在闭式列表中，直接移除节点
            continue;
        }
        else if (nodes[iPred].isOpen())
        {
            // 如果在开式列表中，先加入到闭式列表
            nodes[iPred].close();
            nodes[iPred].discover();
            //std::cout << "index: " << nPred->x << " " << nPred->y << std::endl;

            // 将该点从openlist中删除
            OpenList.pop();

            // 如果发现了终点
            if(*nPred == end){
                std::cout << "find end!" << std::endl;
                return nPred;
            }
            // 否则继续搜索，扩充邻居节点
            else
            {
                for (int i = 0; i < node::dir; i++)
                {
                    nSucc = nPred->createSuccessor(i);  // 有可能的节点
                    iSucc = nSucc->setIdx(width);       // 当前可能节点的索引
                    //if(nSucc->isOnGrid(width, height) && map[iSucc] < 0.6 && !nodes[iSucc].isClosed())
                    if(nSucc->isOnGrid(width, height) && map[iSucc] < 0.5 && !nodes[iSucc].isClosed())
                    {
                        nSucc->updateG(width,height);
                        newG = nSucc->getG();
                        //std::cout << nSucc->k << std::endl;
                        if (!nodes[iSucc].isOpen() || newG < nodes[iSucc].getG())
                        {
                            nSucc->updateH(end,width,height);
                            nSucc->updateK(img);
                            nSucc->open();
                            nodes[iSucc] = *nSucc;
                            OpenList.push(&nodes[iSucc]);
                            delete nSucc;
                        }
                        else
                        {
                            delete nSucc;
                        }
                    }
                    else
                    {
                        delete nSucc;
                    } // end of else
                } // end of for
            } // end of else
        } // end of else if
    } // end of while
}

bool plan::Valid_Point()
{
    if(!(start.x <= width && start.x >= 0 && start.y <= height && start.y >= 0))
        return 0;
    else if(!(end.x <= width && end.x >= 0 && end.y <= height && end.y >= 0))
        return 0;
    return 1;
}

void plan::TracePath(const node *path_end, std::vector<node> tmp_path)
{
    if (path_end == nullptr)
    {
        this->path = tmp_path;
        return;
    }
    tmp_path.push_back(*path_end);
    TracePath(path_end->getPred(),tmp_path);
}
