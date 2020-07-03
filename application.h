#ifndef APPLICATION_H
#define APPLICATION_H

#include <QApplication>
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QPoint>
#include <QPolygon>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QAction>
#include <QDesktopWidget>
#include <QVector>
#include <QPainterPath>
#include <QGraphicsItem>
#include <QToolBar>
#include <QGraphicsPolygonItem>
#include <QResizeEvent>
#include <QGraphicsLineItem>
#include "carapace.h"
#include "generateurcarapacealea.h"
#include "generateurcarapaceparfaite.h"

//应用程序窗口类 公有继承 主窗口类
class Application : public QMainWindow{
    Q_OBJECT
public:
    Application();
    ~Application();
    const Carapace & getCarapace() const;
    void update();

signals:

public slots:
    void genererCarapace();                                           //生成壳信号槽
    void genererNouveauxSites();                                      //生成新的站点信号槽
    void afficherCacherSites();                                       //显示隐藏的站点
    void afficherCacherTriangulation();                              //显示隐藏的三角剖分
    void afficherCacherCerclesCirconscrits();                        //显示隐藏的外接圆
    void afficherCacherCentresCerclesCirconscrits();                //显示隐藏的外接圆的圆心
    void afficherCacherDiagrammeVoronoi();                           //显示隐藏的Voronoi图
    void genererCarapaceParfaite();                                  //生成完美的壳
    void genererNouveauxSitesParfaits();                             //生成完美的新的站点


private:
    QWidget * widgetFenetreCentral;                                      //中央窗口部件
    QVBoxLayout * mainLayoutWidgetCentral;                               //部件中央的主布局（垂直）
    QHBoxLayout * layoutBoutons;                                         //按钮的布局（水平）
    QPushButton * genererCarapaceBtn , * genererNouveauxSitesBtn , * genererCarapaceParfaitBtn , * genererNouveauxSitesParfaitsBtn;  //生成壳 生成新的站点 生成完美的壳 生成完美壳的新的站点（按钮）
    QGraphicsView * vueDessin;                                           //图形视图
    QGraphicsScene * sceneDessin;                                        //场景图
    QMenu * menuFichier , * menuAffichage;                               //文件菜单栏 显示(查看)菜单栏
    /*** 退出的动作 ，隐藏显示站点的动作 ，隐藏显示三角剖分的动作，
         隐藏显示外接圆的动作 ，隐藏显示外接圆的中心的动作，
         隐藏显示Voronoi图的动作  */
    QAction * actionQuitter , * actionCacherMontrerSites , * actionCacherMontrerTriangulation ,
            * actionCacherMontrerCerclesCirconscrits , * actionCacherMontrerCentresCerclesCirconscrits ,
            * actionCacherMontrerDiagrammeVoronoi;
    vector< QGraphicsEllipseItem * > listeCercleSites , listeCerclesCirconscritsDessin ,
                                     listeCentresCerclesCirconscrits;    //圆站点的列表，外接圆图的列表，外接圆中心的列表
    vector< QGraphicsPolygonItem * > listePolygonsDessin;                //多边形图的列表
    vector< QGraphicsLineItem * > listeLignes;                           //直线图列表
    QToolBar * barreOutils;                                              //工具栏

    Carapace carapace;                                                   //壳对象
    GenerateurCarapaceAlea generateurCarapaceAlea;                       //生成壳对象
    GenerateurCarapaceParfaite generateurCarapaceParfaite;               //生成完美壳对象
    int unite;                                                           //联合

    void genererInterface();                                           //生成接口
    void sizeAndCenterWindow();                                        //设置中心窗口的大小
    void genererMenu();                                                 //生成菜单框架界面
    void genererBarreOutils();                                         //生成工具栏
    void dessinerContours();                                           //画轮廓
};

#endif // APPLICATION_H
