#include "mainwindow.h"
#include <qdebug.h>
#include <QToolBar>
#include <QtAlgorithms>
#include <iostream>
#include <windows.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //设置主窗口名称
    setWindowTitle ("welcome optics valley of china");
    //实例化算法程序
    dj = new MainWindow::DijkstraFindPath();
    //创建邻接图
    dj->CreateGrap();
    //场景、窗口设置
    scene = new QGraphicsScene;
    //设定一个场景，把地图放到场景里，避免地图随着窗口大小的改变而变化
    //（0，0）是自定义坐标；该坐标的初始值和setpos设定的值确定item在视图中的起点，调节（1150，700）可以让item在视图中显示更多细节
    scene->setSceneRect(0, 0, 1150, 700);
    //场景初始化
    initScene();
    //视图
    view = new QGraphicsView;
    view->setScene(scene);
    //设置视图的最小尺寸，可根据场景的大小变化
    view->setMinimumSize(800, 800);
    //显示
    view->show();
    //把视图放在窗口中间
    setCentralWidget(view);

    //操作类调用
    //搜索路径、clear等
    createAction();
    //工具栏
    createToolBar();
    //设置最小尺寸
    setMinimumSize(800, 800);
    Sleep(2000);
}

MainWindow::~MainWindow()
{
}
//加载地图
void MainWindow::initScene(){
    QGraphicsPixmapItem *item =
            scene->addPixmap(QPixmap(":/resource/OpticsValley.jpg"));
    item->setPos(0, -50);
}
//鼠标事件，获取目标的坐标值
void MainWindow::mouseDoubleClickEvent(QMouseEvent *e){
    QDialog *dialog = new QDialog;
    QGridLayout *layout = new QGridLayout(dialog);
    label = new QLabel;

    qDebug() << "x : " << e->x() << " y: " << e->y();
    //光谷转盘（487，391）
    if((e->x() <= 487 + 50 && e->x() >= 487 - 50) && (e->y() <= 391 + 50 && e->y() >= 391 - 50)){
        strPath = ":/resource/OpticalSquare.jpg";
        //加载目标信息
        Quare.load(strPath);
        label->setPixmap(Quare);
        //布局
        layout->addWidget(label);
        //设置信息显示窗口的大小 名字 并显示
        dialog->setMinimumSize(1193, 274);
        dialog->setWindowTitle("光谷大转盘");
        dialog->show();
    }
    //光谷资本大厦(610, 652)
    else if ((e->x () >= 610-50 && e->x () <= 610 + 50) &&
             (e->y () >= 652 - 40 && e->y () <= 652 + 10 ) ) {
        strPath = ":/resource/OpticalCapitalTower.jpg";
        CapBuilding.load (strPath);
        label->setPixmap (CapBuilding);
        layout->addWidget (label);
        dialog->setMinimumSize (437, 265);
        dialog->setWindowTitle ("光谷资本大厦)");
        dialog->show ();
    }
    //光谷世界城(843, 507)
    else if ((e->x () >= 835-50 && e->x () <= 835 + 50) &&
             (e->y () >= 507 - 50 && e->y () <= 507 + 50 ) ) {
        strPath = ":/resource/OpticalValleyWorldCity.jpg";
        OWVCity.load (strPath);
        label->setPixmap (OWVCity);
        layout->addWidget (label);
        dialog->setMinimumSize (397, 340);
        dialog->setWindowTitle ("光谷世界城");
        dialog->show ();
    }
    //国网电力科学研究院(905,133)
    else if((e->x () >= 905 - 50 && e->x () <= 905 + 50) &&
            (e->y () >= 133 - 50 && e->y() <= 133 + 50)){
        strPath = ":/resource/NESRI.jpg";
        Institute.load(strPath);
        label->setPixmap(Institute);
        layout->addWidget(label);
        dialog->setMinimumSize(500,500);
        dialog->setWindowTitle("国家电力科学研究院");
        dialog->show();
    }
}
//算法实现最优路径，初始化图结构
MainWindow::DijkstraFindPath::DijkstraFindPath(){
    //初始化点数 暂时设为40个目标地点
    mgraph.vexnum = 40;
    //给每个点设置一个编号
    for(int i = 0; i < mgraph.vexnum; i++){
        mgraph.vexs.push_back(i);
    }
    //边数，暂定100
    mgraph.arcnum = 100;
    for(int i = 0; i < mgraph.vexnum; i++){
        for(int j = 0; j < mgraph.vexnum; j++){
            if(i == j){
                mgraph.arcs[i][j].adj = 0;
            }
            else{
                mgraph.arcs[i][j].adj = INF;
            }
        }
    }
}
//获取目标地点的坐标--双击两个目标点可获得坐标
void MainWindow::setStart(int X, int Y){
    startX = X; startY = Y;
}
void MainWindow::setEnd(int X, int Y){
    endX = X; endY = Y;
}
void MainWindow::setStartStation(){
    switch (startComboBox->currentIndex()) {
    case 0:
        setStart (201, 191); break;
    case 1:
        setStart (401, 306); break;
    case 2:
        setStart (262, 335); break;
    case 3:
        setStart (118, 270); break;
    case 4:
        setStart (108, 325); break;
    case 5:
        setStart (72, 503); break;
    case 6:
        setStart (81, 617); break;
    case 7:
        setStart (116, 694); break;
    case 8:
        setStart (326, 672); break;
    case 9:
        setStart (402, 555); break;
    case 10:
        setStart (308, 439); break;
    case 11:
        setStart (487, 391); break;
    case 12:
        setStart (632, 587); break;
    case 13:
        setStart (610, 652); break;
    case 14:
        setStart (843, 507); break;
    case 15:
        setStart (1014, 575); break;
    case 16:
        setStart (1074, 572); break;
    case 17:
        setStart (1081, 426); break;
    case 18:
        setStart (1004, 350); break;
    case 19:
        setStart (998, 246); break;
    case 20:
        setStart (791, 303); break;
    case 21:
        setStart (532, 302); break;
    case 22:
        setStart (570, 192); break;
    case 23:
        setStart (569, 133); break;
    case 24:
        setStart (714, 151); break;
    case 25:
        setStart (776, 85); break;
    case 26:
        setStart (905, 133); break;
    case 27:
        setStart (299, 279); break;
    default:
        break;
    }
}
void MainWindow::setEndStation ()
{
    switch (endComboBox->currentIndex ()) {
    case 0:
        setEnd (201, 191); break;
    case 1:
        setEnd (401, 306); break;
    case 2:
        setEnd (262, 335); break;
    case 3:
        setEnd (118, 270); break;
    case 4:
        setEnd (108, 325); break;
    case 5:
        setEnd (72, 503); break;
    case 6:
        setEnd (81, 617); break;
    case 7:
        setEnd (116, 694); break;
    case 8:
        setEnd (326, 672); break;
    case 9:
        setEnd (402, 555); break;
    case 10:
        setEnd (308, 439); break;
    case 11:
        setEnd (487, 391); break;
    case 12:
        setEnd (632, 587); break;
    case 13:
        setEnd (610, 652); break;
    case 14:
        setEnd (843, 507); break;
    case 15:
        setEnd (1014, 575); break;
    case 16:
        setEnd (1074, 572); break;
    case 17:
        setEnd (1081, 426); break;
    case 18:
        setEnd (1004, 350); break;
    case 19:
        setEnd (998, 246); break;
    case 20:
        setEnd (791, 303); break;
    case 21:
        setEnd (532, 302); break;
    case 22:
        setEnd (570, 192); break;
    case 23:
        setEnd (569, 133); break;
    case 24:
        setEnd (714, 151); break;
    case 25:
        setEnd (776, 85); break;
    case 26:
        setEnd (905, 133); break;
    case 27:
        setEnd (299, 279); break;
    default:
        break;
    }
}
void MainWindow::setNextPos (int index)
{
    switch (index) {
    case 0:
        setEnd (201, 191); break;
    case 1:
        setEnd (401, 306); break;
    case 2:
        setEnd (262, 335); break;
    case 3:
        setEnd (118, 270); break;
    case 4:
        setEnd (108, 325); break;
    case 5:
        setEnd (72, 503); break;
    case 6:
        setEnd (81, 617); break;
    case 7:
        setEnd (116, 694); break;
    case 8:
        setEnd (326, 672); break;
    case 9:
        setEnd (402, 555); break;
    case 10:
        setEnd (308, 439); break;
    case 11:
        setEnd (487, 391); break;
    case 12:
        setEnd (632, 587); break;
    case 13:
        setEnd (610, 652); break;
    case 14:
        setEnd (843, 507); break;
    case 15:
        setEnd (1014, 575); break;
    case 16:
        setEnd (1074, 572); break;
    case 17:
        setEnd (1081, 426); break;
    case 18:
        setEnd (1004, 350); break;
    case 19:
        setEnd (998, 246); break;
    case 20:
        setEnd (791, 303); break;
    case 21:
        setEnd (532, 302); break;
    case 22:
        setEnd (570, 192); break;
    case 23:
        setEnd (569, 133); break;
    case 24:
        setEnd (714, 151); break;
    case 25:
        setEnd (776, 85); break;
    case 26:
        setEnd (905, 133); break;
    case 27:
        setEnd (299, 279); break;
    default:
        break;
    }
}
//将目标路径写入图中--在地图中双击两个目标点获得坐标后，计算权值：勾股定理
void MainWindow::DijkstraFindPath::CreateGrap(){
    //左上
    mgraph.arcs[0][1].adj = mgraph.arcs[1][0].adj = 220;    //融众国际-光谷广场商场
    //mgraph.arcs[1][2].adj = mgraph.arcs[2][1].adj = 140;    //光谷广场商场-KFC
    mgraph.arcs[2][3].adj = mgraph.arcs[3][2].adj = 160;    //KFC-中国电信
    mgraph.arcs[0][3].adj = mgraph.arcs[3][0].adj = 110;   //中国电信-融众国际
    //左下
    mgraph.arcs[3][4].adj = mgraph.arcs[4][3].adj = 50;    //中国电信-北大青鸟综合楼
    mgraph.arcs[4][5].adj = mgraph.arcs[5][4].adj = 180;    //北大青鸟综合楼-洪山区住房保障和房管局
    mgraph.arcs[5][6].adj = mgraph.arcs[6][5].adj = 110;    //洪山区住房保障和房管局-双塘小区
    mgraph.arcs[6][7].adj = mgraph.arcs[7][6].adj = 85;    //双塘小区-洪山区市场监督管理局关山工商所
    mgraph.arcs[7][8].adj = mgraph.arcs[8][7].adj = 210;    //洪山区市场监督管理局关山工商所-米莱公寓
    mgraph.arcs[8][9].adj = mgraph.arcs[9][8].adj = 145;    //米莱公寓-武汉地铁光谷广场售票处
    mgraph.arcs[9][10].adj = mgraph.arcs[10][9].adj = 150;  //武汉地铁光谷广场售票处-光谷广场地铁站
    mgraph.arcs[9][11].adj = mgraph.arcs[11][9].adj = 170;  //武汉地铁光谷广场售票处-光谷转盘
    mgraph.arcs[9][12].adj = mgraph.arcs[12][9].adj = 230;  //武汉地铁光谷广场售票处-招商银行
    mgraph.arcs[10][5].adj = mgraph.arcs[5][10].adj = 245;  //光谷广场地铁站-洪山区住房保障和房管局
    mgraph.arcs[10][11].adj = mgraph.arcs[11][10].adj = 185;//光谷广场地铁站--光谷转盘
    mgraph.arcs[10][2].adj = mgraph.arcs[2][10].adj = 110;  //光谷广场地铁站-KFC
    mgraph.arcs[2][11].adj = mgraph.arcs[11][2].adj = 230;  //KFC-光谷转盘
    //右上
    mgraph.arcs[1][21].adj = mgraph.arcs[21][1].adj = 130;  //光谷广场商场-武汉场内招待所
    mgraph.arcs[21][11].adj = mgraph.arcs[11][21].adj = 100;//武汉场内招待所-光谷转盘
    mgraph.arcs[21][22].adj = mgraph.arcs[22][21].adj = 105;//武汉场内招待所-东成专业电动工具
    mgraph.arcs[21][20].adj = mgraph.arcs[20][21].adj = 160; //武汉场内招待所-湖北省五建小区
    mgraph.arcs[21][23].adj = mgraph.arcs[23][21].adj = 170;//东成专业电动工具-鲁巷综合市场
    mgraph.arcs[23][24].adj = mgraph.arcs[24][23].adj = 145;//鲁巷综合市场-7435公寓
    mgraph.arcs[24][25].adj = mgraph.arcs[25][24].adj = 90; //7435公寓-pejafan
    mgraph.arcs[24][26].adj = mgraph.arcs[26][24].adj = 140; //7435公寓-国网电力科学研究所
    mgraph.arcs[24][20].adj = mgraph.arcs[20][24].adj = 170; //7435公寓-湖北省五建小区
    mgraph.arcs[20][19].adj = mgraph.arcs[19][20].adj = 210; //湖北省五建小区-武汉高压研究所
    mgraph.arcs[26][19].adj = mgraph.arcs[19][26].adj = 140; //国网电力科学研究所-武汉高压研究所
    mgraph.arcs[19][18].adj = mgraph.arcs[18][19].adj = 110; //武汉高压研究所-珞雄路地铁站
    //右下
    mgraph.arcs[12][13].adj = mgraph.arcs[13][12].adj = 70; //招商银行-光谷资本大厦
    mgraph.arcs[12][14].adj = mgraph.arcs[14][12].adj = 220;  //招商银行-光谷世界城
    mgraph.arcs[14][11].adj = mgraph.arcs[11][14].adj = 370; //光谷世界城-光谷转盘
    mgraph.arcs[14][15].adj = mgraph.arcs[15][14].adj = 185; //光谷世界城-东亚银行
    mgraph.arcs[15][16].adj = mgraph.arcs[16][15].adj = 60; //东亚银行-加州阳光
    mgraph.arcs[15][18].adj = mgraph.arcs[18][15].adj = 220;//东亚银行-珞雄路地铁站
    mgraph.arcs[16][17].adj = mgraph.arcs[17][16].adj = 150; //加州阳光-光谷步行街
    mgraph.arcs[14][17].adj = mgraph.arcs[17][14].adj = 250; //光谷步行街-光谷世界城
    mgraph.arcs[14][16].adj = mgraph.arcs[16][14].adj = 175;   //光谷世界城-加州阳光

    //细节处理
    mgraph.arcs[0][27].adj = mgraph.arcs[27][0].adj = 130;//光谷广场商场到KFC不能用直线 增加27号拐点
    mgraph.arcs[1][27].adj = mgraph.arcs[27][1].adj = 100;
    mgraph.arcs[2][27].adj = mgraph.arcs[27][2].adj = 65;
}
//dijkstra算法
void MainWindow::DijkstraFindPath::dijkstra(int startPos){
    //把默认的边值都设为最大值
    for(int i = 0; i < mgraph.vexnum; i++) d[i] = INF;
    //把每条边都设为未使用过
    for(int i = 0; i < mgraph.vexnum; i++) used[i] = false;
    for(int i = 0; i < mgraph.vexnum; i++) prev[i] = -1;
    d[startPos] = 0;

    while(true){
        int v = -1;
        //遍历路径信息的图
        for(int u = 0; u < mgraph.vexnum; u++){
            if(!used[u] && (v == -1 || d[u] < d[v])) v =u;
        }

        if(v == -1) break;
        used[v] = true;

        for(int u = 0; u < mgraph.vexnum; u++){
            if(d[u] > d[v] + mgraph.arcs[v][u].adj){
                d[u] = d[v] +mgraph.arcs[v][u].adj;
                prev[u] = v;
            }
        }
    }
}
//获得路径
QVector<int> MainWindow::DijkstraFindPath::get_Path(int endPos){
    QVector<int> path;
    for(; endPos != -1; endPos = prev[endPos]){
        path.push_back(endPos);
    }
    std::reverse(path.begin(), path.end());
    return path;
}
//绘制路径
void MainWindow::FindPath(){
    //在图片上绘线，在原有基础上（+0， -95）
    QVector<QPoint> v;
    //设置起点
    dj->dijkstra(startComboBox->currentIndex());
    //设置下一处的终点
    nextPath = dj->get_Path(endComboBox->currentIndex());

    //准备绘制
    Clear();
    //绘制路线
    QGraphicsPathItem *item = new QGraphicsPathItem();
    QPen pen;
    pen.setWidth(4);
    pen.setColor(Qt::red);
    item->setPen(pen);
    item->setFlag(QGraphicsItem::ItemIsPanel);
    for(int i = 1; i< nextPath.size(); i++){
        qDebug() << nextPath[i] << " , ";
    }
    scene->addItem(item);
    QPainterPath pa;
    pa.moveTo(startX, startY - 95);
    //将路径用坐标存入到路径中
    for(int i = 1; i< nextPath.size(); i++){
        setNextPos(nextPath[i]);
        pa.lineTo(endX, endY - 95);
    }
    item->setPath(pa);
}
//清除路径
void MainWindow::Clear(){
    QList<QGraphicsItem*> listItem = scene->items();
    while(!listItem.empty()){
        scene->removeItem((listItem.at(0)));
        listItem.removeAt(0);
    }
    QGraphicsPixmapItem *item =
            scene->addPixmap (QPixmap(":/resource/OpticsValley.jpg"));
    item->setPos(0, -50);
}
//控件设置 命名和连接信号槽
void MainWindow::createToolBar(){
    QToolBar *toolBar = addToolBar("Tool");
    startLabel = new QLabel(tr("起点："));
    startComboBox = new QComboBox;
    startComboBox->addItem(tr("融众国际"));//0
    startComboBox->addItem (tr("光谷广场商场"));  //1
    startComboBox->addItem (tr("KFC"));  //2
    startComboBox->addItem (tr("中国电信"));  //3
    startComboBox->addItem (tr("北大青鸟综合楼"));  //4
    startComboBox->addItem (tr("洪山区住房保障和房管局"));  //5

    startComboBox->addItem (tr("双塘小区")); //6
    startComboBox->addItem (tr("洪山区市场监督管理局关山工商所"));  //7
    startComboBox->addItem (tr("米莱公寓"));  //8
    startComboBox->addItem (tr("武汉地铁光谷广场售票处"));  //9
    startComboBox->addItem (tr("光谷广场地铁站"));     //10
    startComboBox->addItem (tr("光谷转盘")); startComboBox->addItem (tr("招商银行"));  //11 12
    startComboBox->addItem (tr("光谷资本大厦")); startComboBox->addItem (tr("光谷世界城")); //13 14
    startComboBox->addItem (tr("东亚银行")); startComboBox->addItem (tr("加州阳光")); //15 16
    startComboBox->addItem (tr("光谷步行街")); startComboBox->addItem (tr("珞雄路地铁站"));     //17 18
    startComboBox->addItem (tr("武汉高压研究所"));  startComboBox->addItem (tr("湖北省五建小区"));    //19 20
    startComboBox->addItem (tr("武汉场内招待所")); startComboBox->addItem (tr("东成专业电动工具"));     //21 22
    startComboBox->addItem (tr("鲁巷综合市场")); startComboBox->addItem (tr("7435公寓"));           //23 24
    startComboBox->addItem (tr("pejafan")); startComboBox->addItem (tr("国网电力科学研究所"));    //25 26
    startComboBox->addItem(tr("珞瑜路人行横道")); //27

    endLabel = new QLabel(tr("终点: "));

    endComboBox = new QComboBox;
    endComboBox->addItem (tr("融众国际"));  //0
    endComboBox->addItem (tr("光谷广场商场"));  //1
    endComboBox->addItem (tr("KFC"));  //2
    endComboBox->addItem (tr("中国电信"));  //3
    endComboBox->addItem (tr("北大青鸟综合楼"));  //4
    endComboBox->addItem (tr("洪山区住房保障和房管局"));  //5

    endComboBox->addItem (tr("双塘小区")); //6
    endComboBox->addItem (tr("洪山区市场监督管理局关山工商所"));  //7
    endComboBox->addItem (tr("米莱公寓"));  //8
    endComboBox->addItem (tr("武汉地铁光谷广场售票处"));  //9
    endComboBox->addItem (tr("光谷广场地铁站"));     //10
    endComboBox->addItem (tr("光谷转盘")); endComboBox->addItem (tr("招商银行"));  //11 12
    endComboBox->addItem (tr("光谷资本大厦")); endComboBox->addItem (tr("光谷世界城")); //13 14
    endComboBox->addItem (tr("东亚银行")); endComboBox->addItem (tr("加州阳光")); //15 16
    endComboBox->addItem (tr("光谷步行街")); endComboBox->addItem (tr("珞雄路地铁站"));     //17 18
    endComboBox->addItem (tr("武汉高压研究所"));  endComboBox->addItem (tr("湖北省五建小区"));    //19 20
    endComboBox->addItem (tr("武汉场内招待所")); endComboBox->addItem (tr("东成专业电动工具"));     //21 22
    endComboBox->addItem (tr("鲁巷综合市场")); endComboBox->addItem (tr("7435公寓"));           //23 24
    endComboBox->addItem (tr("pejafan")); endComboBox->addItem (tr("国网电力科学研究所"));    //25 26
    endComboBox->addItem(tr("珞瑜路人行横道"));//27

    //连接信号

    connect(startComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::setStartStation);
    connect (endComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::setEndStation);
    //将工具栏停靠在窗口
    toolBar->addWidget (startLabel);
    toolBar->addWidget (startComboBox);
    toolBar->addSeparator ();
    toolBar->addWidget (endLabel);
    toolBar->addWidget (endComboBox);
    toolBar->addSeparator ();
    toolBar->addAction(findPathAction);
    toolBar->addSeparator ();
    toolBar->addAction(clearAction);
    toolBar->addSeparator ();
    toolBar->addAction(reviseAction);
    toolBar->addSeparator ();
    toolBar->addAction(callMap);
}

//用户操作接口
void MainWindow::createAction(){
    //搜索路径
    findPathAction = new QAction(QIcon(":/resource/Search.png"),tr("搜索路径"), this);
    findPathAction->setShortcut(tr("Ctrl+w"));
    findPathAction->setStatusTip(tr("搜索路径"));
    connect (findPathAction, &QAction::triggered, this, &MainWindow::FindPath);
    //清理路径
    clearAction = new QAction(QIcon(":/resource/Clear.png"), tr("清理路径"), this);
    clearAction->setShortcut (tr("Ctrl+W"));
    clearAction->setStatusTip (tr("清理路径"));
    connect (clearAction, &QAction::triggered, this, &MainWindow::Clear);
    //修改景点
    reviseAction = new QAction(QIcon(":/resource/revise.png"), tr("修改景点"), this);
    reviseAction->setShortcut (tr("Ctrl+R"));
    clearAction->setStatusTip (tr("修改景点"));
    connect (reviseAction, &QAction::triggered, this, &MainWindow::Revise);
    //调用测试地图
    callMap = new QAction(QIcon(":/resource/map.png"), tr("调用测试地图"), this);
    callMap->setShortcut (tr("Ctrl+M"));
    callMap->setStatusTip (tr("调用测试地图"));
    connect (callMap, &QAction::triggered, this, &MainWindow::callOtherMap);
}

//修改信息
void MainWindow::Revise(){
    //控件
    QDialog *reviseDlg = new QDialog;
    QLabel *reviseLabel = new QLabel(tr("修改图片路径"));
    QLineEdit *revision = new QLineEdit();
    QPushButton *SureBtn = new QPushButton(tr("确定"));
    QPushButton *CancelBtn = new QPushButton(tr("取消"));
    revision->setEnabled(false);
    //制作下拉框选择要修改的目标
    reviseComboBox = new QComboBox;
    reviseComboBox->addItem(tr("光谷转盘"));
    reviseComboBox->addItem (tr("光谷资本大厦"));
    reviseComboBox->addItem (tr("光谷世界城"));
    reviseComboBox->addItem (tr("国网电力科学研究院"));
    //连接信号
    connect(reviseComboBox, QOverload<int>::of(&QComboBox::activated), this, &MainWindow::ShowDialog);
    connect (SureBtn, &QPushButton::clicked, reviseDlg, &MainWindow::close);
    connect (CancelBtn, &QPushButton::clicked, reviseDlg, &MainWindow::close);
    revision->setText(strPath);
    //控件布局
    QGridLayout *mainlayout = new QGridLayout(reviseDlg);
    mainlayout->addWidget (reviseLabel, 0, 0); mainlayout->addWidget (revision, 0, 1);
    mainlayout->addWidget (reviseComboBox, 0 , 2);
    mainlayout->addWidget (SureBtn, 1, 1, 1, 1); mainlayout->addWidget (CancelBtn, 1, 2, 1, 1);
    reviseDlg->setWindowTitle("修改信息");
    reviseDlg->show();
}
void MainWindow::ShowDialog(){
    strPath = QFileDialog::getOpenFileName(this, "打开","/", "PNG图像(*.png)::JPEG图像(*.jpg)");
    switch(reviseComboBox->currentIndex()){
    case 0:
        Quare.load(strPath); break;
    case 1:
        CapBuilding.load(strPath); break;
    case 2:
        OWVCity.load(strPath); break;
    case 3:
        Institute.load(strPath); break;
    default:
        break;
    }
}

//查看其它地图
void MainWindow::callOtherMap(){
    map = new MapWidget;
    map->show();
}
