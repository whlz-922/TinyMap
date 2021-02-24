#ifndef MAPWIDGET_H
#define MAPWIDGET_H
/**
*查看测试地图，可放大缩小移动，获取某一点的场景坐标和地点坐标等信息
*/
#include <QGraphicsView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMouseEvent>

class MapWidget : public QGraphicsView
{
    Q_OBJECT
public:
    MapWidget();
    //读取地图信息
    void readMap();
    //用于实现场景坐标系与地图坐标间的映射.以获得某点的经纬度
    QPointF mapToMap(QPointF);
public slots:
    //缩放信号
    void slotZoom(int);
protected:
    //完成地图的显示功能
    void drawBackground (QPainter *painter, const QRectF &rect);

    void mouseMoveEvent (QMouseEvent *event);
private:
    QPixmap map;
    qreal zoom;
    QLabel *viewCoord;  //视图目前坐标(以窗口左上为原点)
    QLabel *sceneCoord; //场景目前坐标(以场景中心为原点)
    QLabel *mapCoord;   //地图目前坐标

    double x1, y1;
    double x2, y2;

};

#endif // MAPWIDGET_H#ifndef MAPWIDGET_H
