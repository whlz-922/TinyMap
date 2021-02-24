#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*项目目标以及实现思路：
 *1.绘制输入起点，终点最短路径--用图结构存储主要地点的坐标及权值，然后用Dijkstra算法
 *  计算最短路径，在地图中画出来
 *2.双击著名地点的附近，显示该地方的信息图--用mouseEvent来监听用户操作
 *3.修改著名地点的信息--file操作
 * 4.打开测试地图，查看地图坐标，实现地图的缩放
*/
#include <QMainWindow>
#include <QToolButton>
#include <QGraphicsLineItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QComboBox>
#include <QTextEdit>
#include <QVector>
#include <QMouseEvent>
#include <QDialog>
#include <QPixmap>
#include <QGridLayout>
#include <QLineEdit>
#include <QFileDialog>
#include <QPushButton>
#include <QHBoxLayout>
#include <QAction>
#include "mapwidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //工具栏按钮接口：搜索、清除、修改、测试
    void createToolBar();
    //行为
    void createAction();
    //起点 记录著名地点的坐标
    void setStart(int X, int Y);
    //终点 与起点一样，换个说法是回头路的起点
    void setEnd(int X, int Y);
    //目标路径的中间点
    void setNextPos(int index);
    //初始化场景
    void initScene();

public slots:
    //目标路径的起点
    void setStartStation();
    //目标路径的终点
    void setEndStation();
    //寻找最优路径
    void FindPath();
    //清除路径
    void Clear();
    //修改目标信息
    void Revise();
    //查看其它地图
    void callOtherMap();
    //显示目录
    void ShowDialog();

private:
    //基本控件
    QLabel *startLabel;
    QLabel *endLabel;
    QComboBox *startComboBox;
    QComboBox *endComboBox;
    QComboBox *reviseComboBox;

    QAction *findPathAction;
    QAction *clearAction;
    QAction *reviseAction;
    QAction *callMap;

    //场景
    QGraphicsScene *scene;
    QGraphicsView *view;

    //坐标
    int startX, startY, endX, endY;

    QVector<int> nextPath;
    /***************图的实现及最短路径算法声明************/
    //弧信息--近似两点之间的距离 权值
    struct ArcCell{
        //对无权图有1，0表示是否相邻，对带权图，则为权值类型
        int adj;
    };
    //内部类
    static const int MAX_VERTEX_NUM = 50;
    static const int INF = 999999;

    struct MGrap{
        QVector<int> vexs;
        //临接矩阵 无权值则置为0
        ArcCell arcs[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
        //点数--著名地点个数
        int vexnum;
        //边数--地点周围路径数
        int arcnum;
    };

    //路径算法--dijkstra算法
    class DijkstraFindPath{
    public:
        DijkstraFindPath();
        MGrap mgraph;
        void CreateGrap();

        //最短路上的前驱顶点
        int prev[MAX_VERTEX_NUM];
        //表示边e = (u,v)的权值(不存在时为INF,不过d[i][i]=0)
        int d[MAX_VERTEX_NUM];
        //已经使用过的图
        bool used[MAX_VERTEX_NUM];
        //求起点startPos出发到各个顶点的最短距离
        void dijkstra(int startPos);
        //到顶点endPos的最短路
        QVector<int> get_Path(int endPos);
    };
    DijkstraFindPath *dj;
    //鼠标事件
protected:
    void mouseDoubleClickEvent(QMouseEvent *e);
private:
    //图片显示
    QPixmap Quare;      //光谷转盘
    QPixmap CapBuilding;  //光谷资本大厦
    QPixmap OWVCity;     //光谷世界城
    QPixmap Institute;    //国家电力科学研究院
    QString strPath;      //文件路径
    QLabel *label;
    //测试类
    MapWidget *map;

};
#endif // MAINWINDOW_H
