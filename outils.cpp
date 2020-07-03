#include "outils.h"

//获取[a,b]之间的随机数
int Outils::getNombreAleatoireEntreDeuxNombres( const int a , const int b ){
    return ( unsigned int )( ( QRandomGenerator::global()->generate() % ( b + 1 - a ) ) + a );
}

//设置随机点x 和 y 的坐标
void Outils::faireVarierStochastiquementLocalementUnPoint( Point * p ){
    p->setX( p->getX() + ( Outils::getNombreAleatoireEntreDeuxNombres( -1 , 1 ) * 0.1 ) );
    p->setY( p->getY() + ( Outils::getNombreAleatoireEntreDeuxNombres( -1 , 1 ) * 0.1 ) );
}

//计算中间控制点
Point * Outils::calculerPointDeControleMilieu( const Point * pointDebut , const Point * pointFin ){
    //范围限制   ， x  ， y
    int limiteDroite = pointFin->getX() - pointDebut->getX() , xPointMilieu = limiteDroite / 2 , yPointMilieu;
    /*
          *为了拥有漂亮的龟壳，我限制了
          *中点高度在直线的40％到90％之间
          *这样可以避免铃铛壳和扁平壳
          */
    int limiteBasseYPointMilieu = limiteDroite * 0.4 , limiteHauteYpointMilieu = limiteDroite * 0.9 ;
    yPointMilieu = Outils::getNombreAleatoireEntreDeuxNombres( limiteBasseYPointMilieu , limiteHauteYpointMilieu );
    return new Point( xPointMilieu , yPointMilieu );
}

//判断点是否在三角形内
bool Outils::pointEstDansTriangle( const Point * point , const Triangle * triangle ){
    AngleCapable angleCapable;
    for ( int i = 0 ; i < 2 ; i ++ )
        angleCapable += AngleCapable( triangle->getLesTroisPoints()[i] , point , triangle->getLesTroisPoints()[i + 1] );
    angleCapable += AngleCapable( triangle->getLesTroisPoints()[2] , point , triangle->getLesTroisPoints()[0] );
    //如果有效角度的总和大于2PI，则该点位于面中
    return ( fabs( angleCapable.getAlpha() ) > 3 );
}

//判断是否属于外接圆
bool Outils::appartientACercle( const Point * point , const Cercle * cercle ){
    double distance;
    //两点间距离公式
    distance = sqrt( ( cercle->getCentre()->getX() - point->getX() ) * ( cercle->getCentre()->getX() - point->getX() ) + ( cercle->getCentre()->getY() - point->getY() ) * ( cercle->getCentre()->getY() - point->getY() ) );
    return distance <= cercle->getRayon();
}

//交叉点(直线方程)
Point * Outils::intersection2Droites( const EquationDroite & ed1 , const EquationDroite & ed2 ){
    double xInter , yInter;
    if ( fabs( ed2.getA() - ed1.getA() ) < 0.0001 )
        throw Erreur("No intersection, the two lines are parallel");
    xInter = ( ed1.getB() - ed2.getB() ) / ( ed2.getA() - ed1.getA() );    //斜率k = y/x
    yInter = ed1.getA() * xInter + ed1.getB();                             //y = kx + b
    return new Point( xInter , yInter );
}

//法线方程
Point * Outils::intersectionDroiteVerticaleEtAutre( const EquationDroiteVerticale & ed1 , const EquationDroite & ed2 ){
    double xInter , yInter;
    xInter = ed1.getC();
    yInter = ed2.getA() * xInter + ed2.getB();
    return new Point( xInter , yInter );
}

//(法线)点的平均值
const EquationDroiteVerticale Outils::equationMediatriceOrdonneesEgales( const Point * p1 , const Point * p2 ){
    double x1 , x2 , c;
    x1 = p1->getX() , x2 = p2->getX();
    c = ( x1 + x2 ) / 2 ;
    return EquationDroiteVerticale(c);
}

//(法线)
const EquationDroite Outils::equationMediatriceOrdonneesPasEgales( const Point * p1 , const Point * p2 ){
    double a , b;
    double x1 , x2 , y1 , y2;
    x1 = p1->getX() , x2 = p2->getX() , y1 = p1->getY() , y2 = p2->getY();
    if( x2 == x1 ){
        a = 0;                    //斜率为0
        b = ( y2 + y1 ) / 2 ;     //截距为一半
    }
    else{
        a = -1 / ( ( y2 - y1 ) / ( x2 - x1 ) );
        b = ( x2 * x2 - x1 * x1 + y2 * y2 - y1 * y1 ) /( 2 * ( y2 - y1 ));
    }
    return EquationDroite( a , b );
}

//最小索引
int Outils::indicePointLePlusAGauche( const vector<Point *> & points ){
    int indice = 0;
    double minX = INT_MAX;
    for ( size_t i = 0 ; i < points.size() ; i ++ ){
        if ( points[i]->getX() < minX ){
            indice = i;
            minX = points[i]->getX();
        }
    }
    return indice;
}

//获取顶点x的最小值
double Outils::getxMin( const vector<Point *> & points ){
    double xMin = DBL_MAX;
    for ( Point * p : points )
        if ( p->getX() < xMin )
            xMin = p->getX();
    return xMin - 1;
}

//获取顶点x的最大值
double Outils::getxMax( const vector<Point *> & points ){
    double xMax = DBL_MIN;
    for ( Point * p : points )
        if ( p->getX() > xMax )
            xMax = p->getX();
    return xMax + 1;
}

//获取顶点y的最大值
double Outils::getyMax( const vector<Point *> & points ){
    double yMax = DBL_MIN;
    for ( Point * p : points )
        if ( p->getY() > yMax )
            yMax = p->getY();
    return yMax + 1;
}

//获取顶点y的最小值
double Outils::getyMin( const vector<Point *> &  points ){
    double yMin = DBL_MAX;
    for ( Point * p : points )
        if ( p->getY() < yMin )
            yMin = p->getY();
    return yMin - 1;
}

//获取三角形的外接圆的中心
Triangle * Outils::getTriangleParCentreCercleCirconscrit( Point * point , const vector<Triangle *> & triangles ){
    for ( Triangle * triangle : triangles )
        if ( triangle->getCercle().getCentre() == point )
            return triangle;
    return NULL;
}

//获得少于三个邻居的三角形
vector< Triangle * > Outils::getTrianglesAyantMoinsDeTroisVoisins( const vector<Triangle *> & triangles ){
    vector< Triangle * > trianglesAyantMoinsDeTroisVoisins;
    for ( Triangle * triangle : triangles )
        if ( triangle->getNbVoisins() < 3 )
            trianglesAyantMoinsDeTroisVoisins.push_back(triangle);
    return trianglesAyantMoinsDeTroisVoisins;
}

//判断点是否在线段上
bool Outils::pointEstSurSegment( Point * p , Segment * s ){
    Point * a , * b;
    a = s->getA();
    b = s->getB();
    Vecteur2D * aB , * aP;
    aB = new Vecteur2D( b->getX() - a->getX() , b->getY() - a->getY() );
    aP = new Vecteur2D( p->getX() - a->getX() , p->getY() - a->getY() );
    double coefX = aP->getX() / aB->getX();      //系数
    double coefY = aP->getY() / aB->getY();
    if ( ( coefX - coefY ) < 0.00000001 && coefX >= 0 && coefX <= 1 )
        return true;
    return false;
}

//获取两点间的距离
double Outils::getDistanceEuclidienne( Point * a , Point * b ){
    return sqrt( ( ( b->getX() - a->getX() ) * ( b->getX() - a->getX() ) ) + ( ( b->getY() - a->getY() ) * ( b->getY() - a->getY() ) ) );
}

//获取最近的轮廓点
Point * Outils::getPointDuContourLePlusProche( Point *inter , const vector<Point *> & contour ){
    double max = DBL_MAX , distance;
    Point * pt;
    for ( Point * point : contour ){
        distance = Outils::getDistanceEuclidienne( inter , point );
        if ( distance < max ){
            max = distance;
            pt = point;
        }
    }
    return pt;
}

//获取顶点的中点
Point * Outils::getPointMilieu( Point * p1 , Point * p2 ){
    double x , y;
    x = ( p1->getX() + p2->getX() ) / 2;
    y = ( p1->getY() + p2->getY() ) / 2;
    return new Point( x , y );
}

//获取棱包含的点
vector< Point * > Outils::getAreteContenantPoint( const vector<vector<Point *> > & aretes , Point * point ){
    for ( vector< Point * > arete : aretes )
        if ( arete.at(0) == point || arete.at(1) == point )
            return arete;
    return vector< Point * >();
}

//获取最小的邻接点
Point * Outils::getPointLePlusAGauche( const vector<Point *> & points ){
    double min = DBL_MAX;
    Point * point = NULL;
    for ( Point * p : points ){
        if ( p->getX() < min ){
            min = p->getX();
            point = p;
        }
    }
    return point;
}

//获取最大的邻接点
Point * Outils::getPointLePlusADroite( const vector<Point * > & points ){
    double max = DBL_MIN;
    Point * point = NULL;
    for ( Point * p : points ){
        if ( p->getX() > max ){
            max = p->getX();
            point = p;
        }
    }
    return point;
}
