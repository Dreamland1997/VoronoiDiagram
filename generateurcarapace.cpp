#include "generateurcarapace.h"

//静态成员对象的实现
Point * GenerateurCarapace::pointMilieuPrecedent;

//生成壳 默认构造函数的实现
GenerateurCarapace::GenerateurCarapace() {}

//生成壳 构造函数的实现
GenerateurCarapace::GenerateurCarapace( Carapace * c ) : carapace( c ) {}

//生成壳函数实现
void GenerateurCarapace::genererCarapace(){
    Bezier bez;                                        //曲线对象
    Point * pointDebut , * pointMilieu , * pointFin;   //起点 中间点 终点
    //确定点
    int origine = 0 , limiteDroite = 10;
    pointDebut = new Point( origine , 0 );
    pointFin = new Point( limiteDroite , 0 );
    pointMilieu = Outils::calculerPointDeControleMilieu( pointDebut , pointFin );

    //在类中保存先前的环境
    pointMilieuPrecedent = pointMilieu;

    bez.ajouterPoint( * pointDebut );
    bez.ajouterPoint( * pointMilieu );
    bez.ajouterPoint( * pointFin );

    vector< Point * > contourHaut , contourBas;  //高轮廓 ， 低轮廓
    Point * pointResultat;
    for ( double t = 0 ; t <= 1 ; t += 0.01 ){
        pointResultat = bez.bezier(t);
        contourHaut.push_back( pointResultat );
        pointResultat = new Point( pointResultat->getX() , -pointResultat->getY() );
        contourBas.push_back( pointResultat );
    }
    contourHaut.push_back( pointFin );
    contourBas.push_back( pointFin );

    this->carapace->setContourHaut( contourHaut );
    this->carapace->setContourBas( contourBas );
    this->carapace->setSites( this->genererSitesPourCarapace( * pointDebut , * pointMilieu , * pointFin ) );

    //三角剖分
    TriangulationDelaunay triangulation( this->carapace->getSites() );
    this->carapace->setTriangles( triangulation.getTriangulation() );

    //Voronoi图
    DiagrammeVoronoi *diagrammeVoronoi = new DiagrammeVoronoi( this->carapace );
    this->carapace->setVoronoi( diagrammeVoronoi );

    this->carapace->updateVue();
}

//生成外壳站点
vector< Point * > GenerateurCarapace::genererSitesPourCarapace(const Point & pointDebut , const Point & pointMilieu , const Point & pointFin ) const{
    Bezier bez;
    int longueurCarapace , dixPourcentLongueurCarapace , quarantePourcentHauteurPointMilieu;  //甲壳长度，甲壳长度的百分之十，高度中点的百分之四十；
    longueurCarapace = pointFin.getX() - pointDebut.getX();
    dixPourcentLongueurCarapace = longueurCarapace * 0.1;
    quarantePourcentHauteurPointMilieu = pointMilieu.getY() * 0.4;

    bez.ajouterPoint( Point ( pointDebut.getX() + dixPourcentLongueurCarapace , pointDebut.getY() ) );
    bez.ajouterPoint( Point ( pointMilieu.getX() , pointMilieu.getY() - quarantePourcentHauteurPointMilieu ) );
    bez.ajouterPoint( Point ( pointFin.getX() - dixPourcentLongueurCarapace , pointFin.getY() ) );

    return this->calculPositionSites( & bez );
}

//生成新的站点
void GenerateurCarapace::genererNouveauxSites() const{
    Point * pointDebut , * pointFin , * pointMilieu;      //起点 终点 中间点
    if ( !this->carapace->getContourHaut().empty() ){
        pointDebut = this->carapace->getContourHaut()[0];
        pointFin = this->carapace->getContourHaut()[ this->carapace->getContourHaut().size() - 1 ];
        pointMilieu = GenerateurCarapace::pointMilieuPrecedent;
        this->carapace->setSites( this->genererSitesPourCarapace( * pointDebut , * pointMilieu , * pointFin ) );
        //三角剖分
        TriangulationDelaunay triangulation( this->carapace->getSites() );
        this->carapace->setTriangles( triangulation.getTriangulation() );
        DiagrammeVoronoi * diagrammeVoronoi = new DiagrammeVoronoi( this->carapace );
        this->carapace->setVoronoi( diagrammeVoronoi );
        this->carapace->updateVue();
    }
}
