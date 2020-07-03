#include "application.h"

//应用程序窗口类 的默认构造函数实现
Application::Application() : QMainWindow(){
    this->carapace = Carapace( this );
    this->generateurCarapaceAlea = GenerateurCarapaceAlea( &this->carapace );
    this->generateurCarapaceParfaite = GenerateurCarapaceParfaite( &this->carapace );
    this->genererInterface();
    this->genererMenu();
    this->genererBarreOutils();
}

//析构函数的实现
Application::~Application(){
//窗口中的所有小组件均已销毁,当关闭时，因此无需在这里销毁
}

//生成接口的实现
void Application::genererInterface(){
    this->sizeAndCenterWindow();
    this->setWindowIcon( QIcon( ":/icones/carapace" ) );                         //设置窗口图标
    //创建中央窗口部件
    this->widgetFenetreCentral = new QWidget();
    //此窗口的布局 垂直 水平
    this->mainLayoutWidgetCentral = new QVBoxLayout();
    this->layoutBoutons = new QHBoxLayout();
    //生成按钮
    this->genererCarapaceBtn = new QPushButton( "Generer carapace" );                               //“生成壳” 按钮
    this->genererCarapaceBtn->setIcon( QIcon( ":/icones/carapaceRouge" ) );                         //设置“生成壳”按钮的图标
    this->genererNouveauxSitesBtn = new QPushButton( "Generer nouveaux sites" );                    //“生成新站点”按钮
    this->genererNouveauxSitesBtn->setIcon( QIcon( ":/icones/sitesPasRanges" ) );                   //设置“生成新站点”按钮的图标
    this->genererNouveauxSitesParfaitsBtn = new QPushButton( "Generer nouveaux sites parfaits" );   //“生成新的完美的站点”按钮
    this->genererNouveauxSitesParfaitsBtn->setIcon( QIcon( ":/icones/sitesRanges" ) );              //设置“生成新的完美的站点”按钮的图标
    this->genererCarapaceParfaitBtn = new QPushButton( "Generer carapace parfaite" );               //“生成完美的壳” 按钮
    this->genererCarapaceParfaitBtn->setIcon( QIcon( ":/icones/carapaceVerte" ) );                  //设置“生成完美的壳”按钮的图标
    //绘制视图
    this->vueDessin = new QGraphicsView();
    //场景视图
    this->sceneDessin = new QGraphicsScene();
    //将场景添加到视图中
    this->vueDessin->setScene( this->sceneDessin );
    //将视图和按钮添加到布局中
    this->mainLayoutWidgetCentral->addWidget( this->vueDessin );
    this->layoutBoutons->addWidget( this->genererCarapaceParfaitBtn );
    this->layoutBoutons->addWidget( this->genererCarapaceBtn );
    this->layoutBoutons->addWidget( this->genererNouveauxSitesBtn );
    this->layoutBoutons->addWidget( this->genererNouveauxSitesParfaitsBtn );
    this->mainLayoutWidgetCentral->addLayout( layoutBoutons );                                      //按钮水平方式布局
    //将部件应用到布局中央
    this->widgetFenetreCentral->setLayout( this->mainLayoutWidgetCentral );
    //最后，主窗口小部件的中央窗口小部件成为我刚刚创建的窗口小部件
    this->setCentralWidget( this->widgetFenetreCentral );

    //信号槽的连接
    QObject::connect( this->genererCarapaceBtn , SIGNAL( clicked( bool ) ) , this , SLOT( genererCarapace() ) );
    QObject::connect( this->genererNouveauxSitesBtn , SIGNAL( clicked( bool ) ) , this , SLOT( genererNouveauxSites() ) );
    QObject::connect( this->genererNouveauxSitesParfaitsBtn , SIGNAL( clicked( bool ) ) , this , SLOT( genererNouveauxSitesParfaits() ) );
    QObject::connect( this->genererCarapaceParfaitBtn , SIGNAL( clicked( bool ) ) , this , SLOT( genererCarapaceParfaite() ) );
}

//设置中心窗口的大小（高 和 宽 是屏幕的百分之八十）
void Application::sizeAndCenterWindow(){
    int heightScreen , widthScreen , heightWindow , widthWindow , x , y;                             //屏幕高度 ，屏幕宽度 ，窗口高度 ，窗口宽度 ，x ，y
    double percentage = 0.8;                                                                         //百分比（80%）
    heightScreen = QApplication::desktop()->screenGeometry().height();
    widthScreen = QApplication::desktop()->screenGeometry().width();
    heightWindow = heightScreen * percentage;                                                        //窗口高度取屏幕高度的百分之八十
    widthWindow = widthScreen * percentage;                                                          //窗口宽度取屏幕宽度的百分之八十
    x = widthScreen - widthWindow - ( widthScreen - widthWindow ) / 2;
    y = heightScreen - heightWindow - ( heightScreen - heightWindow ) / 2;
    this->move( x , y );
    this->setFixedSize( widthWindow , heightWindow );                                                //设置固定大小

    this->unite = widthWindow / 20;
}

//生成菜单框架界面
void Application::genererMenu(){
    this->menuFichier = this->menuBar()->addMenu( "&File" );                                         //创建“文件菜单”栏
    this->menuAffichage = this->menuBar()->addMenu( "&Display" );                                    //创建“显示(查看)菜单”栏
    this->actionQuitter = new QAction( "&Exit" , this );                                             //创建“退出菜单”栏
    this->actionQuitter->setIcon( QIcon( ":/icones/quitter" ) );                                //设置“退出菜单栏”的图标
    this->actionQuitter->setToolTip( "Exit" );
    this->actionCacherMontrerSites = new QAction( "Afficher/Cacher sites" , this );
    this->actionCacherMontrerSites->setCheckable( true );
    this->actionCacherMontrerSites->setIcon( QIcon(":/icones/site") );                               //设置“显示/隐藏 站点”的图标
    this->actionCacherMontrerSites->setToolTip( "Afficher/Cacher sites" );

    this->actionCacherMontrerTriangulation = new QAction( "Afficher/Cacher triangulation" , this );
    this->actionCacherMontrerTriangulation->setCheckable( true );
    this->actionCacherMontrerTriangulation->setIcon( QIcon( ":/icones/triangle" ) );                  //设置“显示/隐藏 三角形”的图标
    this->actionCacherMontrerTriangulation->setToolTip( "Afficher/Cacher triangulation" );

    this->actionCacherMontrerCerclesCirconscrits = new QAction( "Afficher/Cacher cercles circonscrits" , this );
    this->actionCacherMontrerCerclesCirconscrits->setCheckable( true );
    this->actionCacherMontrerCerclesCirconscrits->setIcon( QIcon( ":/icones/cercle" ) );               //设置“显示/隐藏 外接圆”的图标
    this->actionCacherMontrerCerclesCirconscrits->setToolTip( "Afficher/Cacher cercles circonscrits" );

    this->actionCacherMontrerCentresCerclesCirconscrits = new QAction( "Afficher/Cacher centres cercles circonscrits" , this );
    this->actionCacherMontrerCentresCerclesCirconscrits->setCheckable( true );
    this->actionCacherMontrerCentresCerclesCirconscrits->setIcon( QIcon( ":/icones/centreCercle" ) );  //设置“显示/隐藏 外接圆圆心”的图标
    this->actionCacherMontrerCentresCerclesCirconscrits->setToolTip( "Afficher/Cacher centres cercles circonscrits" );

    this->actionCacherMontrerDiagrammeVoronoi = new QAction( "Afficher/Cacher diagramme de Voronoi" , this );
    this->actionCacherMontrerDiagrammeVoronoi->setCheckable( true );
    this->actionCacherMontrerDiagrammeVoronoi->setIcon( QIcon( ":/icones/voronoi") );                  //设置“显示/隐藏 Voronoi图”的图标
    this->actionCacherMontrerDiagrammeVoronoi->setToolTip( "Afficher/Cacher diagramme de Voronoi" );

    this->menuFichier->addAction( this->actionQuitter );
    this->menuAffichage->addAction( this->actionCacherMontrerSites );
    this->menuAffichage->addAction( this->actionCacherMontrerTriangulation );
    this->menuAffichage->addAction( this->actionCacherMontrerCerclesCirconscrits );
    this->menuAffichage->addAction( this->actionCacherMontrerCentresCerclesCirconscrits );
    this->menuAffichage->addAction( this->actionCacherMontrerDiagrammeVoronoi );

    //信号槽的连接
    QObject::connect( this->actionQuitter , SIGNAL( triggered( bool ) ) , qApp , SLOT( quit() ) );
    QObject::connect( this->actionCacherMontrerSites , SIGNAL( changed() ) , this , SLOT( afficherCacherSites() ) );
    QObject::connect( this->actionCacherMontrerTriangulation , SIGNAL( changed() ) , this , SLOT( afficherCacherTriangulation() ) );
    QObject::connect( this->actionCacherMontrerCerclesCirconscrits , SIGNAL( changed() ) , this , SLOT( afficherCacherCerclesCirconscrits() ) );
    QObject::connect( this->actionCacherMontrerCentresCerclesCirconscrits , SIGNAL( changed() ) , this , SLOT( afficherCacherCentresCerclesCirconscrits() ) );
    QObject::connect( this->actionCacherMontrerDiagrammeVoronoi , SIGNAL( changed() ) , this , SLOT( afficherCacherDiagrammeVoronoi() ) );

}

//生成工具栏(将 隐藏/显示 动作添加到工具栏)
void Application::genererBarreOutils(){
    this->barreOutils = this->addToolBar( "ToolBar" );
    this->barreOutils->setMovable( false );                                                              //工具栏不可移动
    this->barreOutils->addAction( this->actionQuitter );
    this->barreOutils->addAction( this->actionCacherMontrerSites );
    this->barreOutils->addAction( this->actionCacherMontrerTriangulation );
    this->barreOutils->addAction( this->actionCacherMontrerCerclesCirconscrits );
    this->barreOutils->addAction( this->actionCacherMontrerCentresCerclesCirconscrits );
    this->barreOutils->addAction( this->actionCacherMontrerDiagrammeVoronoi );
}

//获取壳
const Carapace & Application::getCarapace() const{
    return this->carapace;
}

//更新操作
void Application::update(){
    this->sceneDessin->clear();
    //画轮廓
    this->dessinerContours();
    //显示隐藏的站点
    this->afficherCacherSites();
    //显示隐藏的三角剖分
    this->afficherCacherTriangulation();
    //显示隐藏的外接圆
    this->afficherCacherCerclesCirconscrits();
    //显示隐藏的外接圆圆心
    this->afficherCacherCentresCerclesCirconscrits();
    //显示隐藏的Voronoi图
    this->afficherCacherDiagrammeVoronoi();
}

//画轮廓
void Application::dessinerContours(){
    //顶点列表
    QVector< QPointF > pointsHaut , pointsBas;
    //在“路径”中集合点
    QPainterPath contourHaut , contourBas;
    for ( size_t i = 0 ; i < this->carapace.getContourHaut().size() ; i ++ ){
        pointsHaut.push_back( QPoint( this->carapace.getContourHaut()[i]->getX() * this->unite , this->carapace.getContourHaut()[i]->getY() * this->unite ) );
        pointsBas.push_back( QPoint( this->carapace.getContourBas()[i]->getX() * this->unite , this->carapace.getContourBas()[i]->getY() * this->unite ) ) ;
    }
    if ( !pointsHaut.isEmpty() && !pointsBas.isEmpty() ){
        contourHaut = QPainterPath( pointsHaut.front() );
        contourBas = QPainterPath( pointsBas.front() );
    }
    for ( int i = 1 ; i < pointsHaut.size() ; ++ i ){
        contourHaut.lineTo( pointsHaut[i] );
        contourBas.lineTo( pointsBas[i] );
    }
    this->sceneDessin->addPath( contourHaut );
    this->sceneDessin->addPath( contourBas );
}

//显示隐藏的站点
void Application::afficherCacherSites(){
    QPen pen( Qt::black , 5 , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin );
    QBrush brush( Qt::black );
    int rayon = 2;
    if ( this->actionCacherMontrerSites->isChecked() ){
        this->listeCercleSites.clear();
        for ( size_t i = 0 ; i < this->carapace.getSites().size() ; i ++ )
            this->listeCercleSites.push_back( this->sceneDessin->addEllipse( this->carapace.getSites()[i]->getX() * this->unite ,
                                                                             this->carapace.getSites()[i]->getY() * this->unite ,
                                                                             rayon * 2 , rayon * 2 , pen , brush ) );
    }
    else{
        for ( size_t i = 0 ; i < this->listeCercleSites.size() ; i ++ )
            this->sceneDessin->removeItem( this->listeCercleSites[i] );
        this->listeCercleSites.clear();
    }
}

//显示隐藏的三角剖分
void Application::afficherCacherTriangulation(){
    QPolygon poly;
    if ( this->actionCacherMontrerTriangulation->isChecked() ){
        this->listePolygonsDessin.clear();
        for ( Triangle * triangle : this->carapace.getTriangles() ){
            poly.clear();
            for ( Point * p : triangle->getLesTroisPoints() )
               poly << QPoint( p->getX() * this->unite , p->getY() * this->unite );
            this->listePolygonsDessin.push_back( this->sceneDessin->addPolygon( poly ) );
        }
    }
    else{
        for ( size_t i = 0 ; i < this->listePolygonsDessin.size() ; i ++ )
            this->sceneDessin->removeItem( this->listePolygonsDessin[i] );
        this->listePolygonsDessin.clear();
    }
}

//显示隐藏的外接圆
void Application::afficherCacherCerclesCirconscrits(){
    QPen pen( Qt::black , 1 , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin );
    QBrush brush( Qt::black );
    if ( this->actionCacherMontrerCerclesCirconscrits->isChecked() ){
        this->listeCerclesCirconscritsDessin.clear();
        for ( Triangle * t : this->carapace.getTriangles() )
            this->listeCerclesCirconscritsDessin.push_back( this->sceneDessin->addEllipse( ( t->getCercle().getCentre()->getX() - t->getCercle().getRayon() ) * this->unite ,
                                                                                           ( t->getCercle().getCentre()->getY() - t->getCercle().getRayon() ) * this->unite ,
                                                                                           t->getCercle().getRayon() * 2 * this->unite ,
                                                                                           t->getCercle().getRayon() * 2 * this->unite ) );
    }
    else{
        for ( QGraphicsEllipseItem * ellipse : this->listeCerclesCirconscritsDessin )
            this->sceneDessin->removeItem( ellipse );
        this->listeCerclesCirconscritsDessin.clear();
    }
}

//显示隐藏的外接圆圆心
void Application::afficherCacherCentresCerclesCirconscrits(){
    QPen pen( Qt::red , 5 , Qt::SolidLine , Qt::RoundCap , Qt::RoundJoin );
    QBrush brush( Qt::black );
    int rayon = 2;
    if( this->actionCacherMontrerCentresCerclesCirconscrits->isChecked() ){
        this->listeCentresCerclesCirconscrits.clear();
        for ( Triangle * t : this->carapace.getTriangles() )
            this->listeCentresCerclesCirconscrits.push_back( this->sceneDessin->addEllipse( t->getCercle().getCentre()->getX() * this->unite ,
                                                                                            t->getCercle().getCentre()->getY() * this->unite ,
                                                                                            rayon * 2 ,
                                                                                            rayon * 2 ,
                                                                                            pen , brush ) );
    }
    else{
        for ( QGraphicsEllipseItem * ellipse : this->listeCentresCerclesCirconscrits )
            this->sceneDessin->removeItem( ellipse );
        this->listeCentresCerclesCirconscrits.clear();
    }
}

//显示隐藏的Voronoi图
void Application::afficherCacherDiagrammeVoronoi(){
    Element< Arete * > * l = NULL;
    QPen pen( Qt::red );
    pen.setWidth(2);
    if ( this->actionCacherMontrerDiagrammeVoronoi->isChecked() ){
        this->listeLignes.clear();
        for ( l = this->carapace.getVoronoi()->getGraphe().getAretes() ; l ; l = l->s ){
            this->listeLignes.push_back( this->sceneDessin->addLine( l->v->getExtremite1()->getPosition()->getX() * this->unite , l->v->getExtremite1()->getPosition()->getY() * this->unite ,
                                                                     l->v->getExtremite2()->getPosition()->getX() * this->unite , l->v->getExtremite2()->getPosition()->getY() * this->unite , pen ) );
        }
    }
    else{
        for ( QGraphicsLineItem * ligne : this->listeLignes )
            this->sceneDessin->removeItem( ligne );
        this->listeLignes.clear();
    }
}

//生成壳(信号槽)
void Application::genererCarapace(){
    this->generateurCarapaceAlea.genererCarapace();
}

//生成新的站点(信号槽)
void Application::genererNouveauxSites(){
    this->generateurCarapaceAlea.genererNouveauxSites();
}

//生成完美的新的站点(信号槽)
void Application::genererNouveauxSitesParfaits(){
    this->generateurCarapaceParfaite.genererNouveauxSites();
}

//生成完美的壳(信号槽)
void Application::genererCarapaceParfaite(){
    this->generateurCarapaceParfaite.genererCarapace();
}
