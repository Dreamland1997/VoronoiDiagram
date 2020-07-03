#include "triangle.h"

//默认构造函数的实现
Triangle::Triangle() : voisins() , lesTroisPoints() , cercleCirconscrit() {
    lesTroisPoints.push_back(NULL);
    lesTroisPoints.push_back(NULL);
    lesTroisPoints.push_back(NULL);
}

//构造函数三角形的初始化
Triangle::Triangle( Point * p1 , Point * p2 , Point * p3 ){
    this->null = false;

    vector< Point * > points;

    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);

    vector< Point * > pointsTrigo = mettreDansSensTrigo(points);

    lesTroisPoints.push_back(pointsTrigo[0]);
    lesTroisPoints.push_back(pointsTrigo[1]);
    lesTroisPoints.push_back(pointsTrigo[2]);
    calculerCercleCirconscrit();
}

//构造函数三角形的初始化
Triangle::Triangle( Point * p1 , Point * p2 , Point * p3 , bool n ) : Triangle( p1 , p2 , p3 ){
    this->null = n;
}

//析构函数实现
Triangle::~Triangle(){

}

//获取nb的邻接点
int Triangle::getNbVoisins() const{
    int nb = 0;
    for( Triangle * t : voisins )
        if( t != NULL && !t->isNull())
            nb ++;
    return nb;
}

//添加邻接点
void Triangle::ajouterVoisin( Triangle * t ){
    if( this->voisins.size() < 3 && !t->appartient( & this->voisins))
        this->voisins.push_back(t);
}

//删除邻居
void Triangle::supprimerVoisin( Triangle * t ){
    for( size_t i = 0 ; i < this->voisins.size() ; i ++ )
        if( this->voisins[i] == t )
            this->voisins.erase( this->voisins.begin() + i );
}

//判断是否包含的点
bool Triangle::contientPoint( Point * point ) const{
    for( Point * p : this->lesTroisPoints )
        if( point == p )
            return true;
    return false;
}

//设置邻接点
void Triangle::setVoisin( int indice , Triangle * nouveauVoisin ){
    if ( voisins.size() < 3 )
        voisins.push_back( nouveauVoisin);
    else
        voisins[indice] = nouveauVoisin;
}

//获取顶点
Point * Triangle::getPoint( int indice ) const{
    return lesTroisPoints[indice];
}

//获取公共的棱
vector< Point * > Triangle::getAreteCommune( const Triangle * t ) const{
    vector< Point * > areteCommnue;
    Point *p1 , *p2;
    p1 = p2 = NULL;
    for ( Point * pThis : this->lesTroisPoints ){
        for ( Point * pT : t->lesTroisPoints ){
            if ( pThis == pT ){
                p1 = pThis;
                for ( Point * pThis1 : this->lesTroisPoints ){
                    if ( pThis1 != p1 ){
                        for ( Point * pT1 : t->lesTroisPoints ){
                            if ( pT1 != p1 && pThis1 == pT1 ){
                                p2 = pThis1;
                            }
                        }
                    }
                }
            }
        }
    }
    if ( p1 != NULL && p2 != NULL ){
        areteCommnue.push_back(p1);
        areteCommnue.push_back(p2);
    }
    return areteCommnue;
}

//判断公共棱是否为空
bool Triangle::ontUneAreteCommune( const Triangle * t ){
    vector< Point * > areteCommune = this->getAreteCommune(t);
    if ( !areteCommune.empty() )
        return true;
    return false;
}

//判断是否属于
bool Triangle::appartient( vector< Triangle * > * DTL ) const{
    bool trouve = false;
    unsigned int i = 0;
    while ( !trouve && i < DTL->size() ){
        if ( DTL->at(i) == this )
            trouve = true;
        else
            i++;
    }
    return trouve;
}

//判断重载运算符==的实现
bool Triangle::operator == ( const Triangle & objet ) const{
    if ( objet.getPoint(0)->estDans(this->lesTroisPoints) &&
         objet.getPoint(1)->estDans(this->lesTroisPoints) &&
         objet.getPoint(2)->estDans(this->lesTroisPoints) )
        return true;
    return false;
}

//字符串的重载
Triangle::operator string() const{
    ostringstream oss;
    oss << "Triangle [" << *lesTroisPoints[0] << ", ";
    oss << *lesTroisPoints[1] << ", " << *lesTroisPoints[2];
    oss << "]";
    return oss.str();
}

//放入SensTrigo
vector< Point * > Triangle::mettreDansSensTrigo( vector< Point * > points ){
    Point * p;
    vector< Point * > pointsTrigo;
    int i = Outils::indicePointLePlusAGauche( points );
    if ( i == 1 ){
        p = points[0];
        points[0] = points[1];
        points[1] = p;
    }
    else if ( i == 2 ){
        p = points[0];
        points[0] = points[2];
        points[2] = p;
    }

    Vecteur2D p0p1( points[1]->getX() - points[0]->getX() , points[1]->getY() - points[0]->getY() );
    Vecteur2D p1p2( points[2]->getX() - points[1]->getX() , points[2]->getY() - points[1]->getY() );

    if ( p0p1 ^ p1p2 )    //sens trigo 三角方向
        return points;
    else{
        pointsTrigo.push_back(points[0]);
        pointsTrigo.push_back(points[2]);
        pointsTrigo.push_back(points[1]);
        return pointsTrigo;
    }
}

//判断!=运算符的重载
bool Triangle::operator != ( const Triangle & objet ) const{
    return !( *this == objet );
}

//将自己从邻接点中移除
void Triangle::seSupprimerDeSesVoisins(){
    for ( Triangle * triangle : this->voisins ){
        if ( triangle != NULL ){
            for ( int j = 0 ; j < triangle->getNbVoisins() ; j ++ ){
                if ( triangle->voisins[j] != NULL ){
                    if ( triangle->voisins[j] == this )
                         triangle->setVoisin( j , NULL );
                }
            }
        }
    }
}

//计算外接圆
void Triangle::calculerCercleCirconscrit(){
    double rayon;               //射线
    double x1 , y1 , y2 , y3;
    Point *centre;              //外接圆圆心

    x1 = lesTroisPoints[0]->getX();
    y1 = lesTroisPoints[0]->getY();
    y2 = lesTroisPoints[1]->getY();
    y3 = lesTroisPoints[2]->getY();

    if ( y1 == y2 ){
        EquationDroiteVerticale ed1 ( Outils::equationMediatriceOrdonneesEgales( lesTroisPoints[0] , lesTroisPoints[1] ) );
        if( y3 == y2 )
            throw Erreur("Ceci ne represente pas un triangle, 3 points alignees!!!");
        else {
            EquationDroite ed2 ( Outils::equationMediatriceOrdonneesPasEgales( lesTroisPoints[1] , lesTroisPoints[2] ) );
            centre = Outils::intersectionDroiteVerticaleEtAutre( ed1 , ed2 );
            cercleCirconscrit.setCentre(centre);
        }
    }
    else{
        EquationDroite ed1 ( Outils::equationMediatriceOrdonneesPasEgales( lesTroisPoints[0] , lesTroisPoints[1] ) );

        if ( y3 == y2 ){
            EquationDroiteVerticale ed2 ( Outils::equationMediatriceOrdonneesEgales( lesTroisPoints[1] , lesTroisPoints[2] ) );
            centre = Outils::intersectionDroiteVerticaleEtAutre( ed2 , ed1 );
            cercleCirconscrit.setCentre(centre);
        }
        else{
            EquationDroite ed2 ( Outils::equationMediatriceOrdonneesPasEgales( lesTroisPoints[1] , lesTroisPoints[2] ) );
            centre = Outils::intersection2Droites( ed1 , ed2 );
            cercleCirconscrit.setCentre(centre);
        }
    }
    rayon = sqrt( ( x1 - cercleCirconscrit.getCentre()->getX() ) * ( x1 - cercleCirconscrit.getCentre()->getX() ) + ( y1 - cercleCirconscrit.getCentre()->getY() ) * ( y1 - cercleCirconscrit.getCentre()->getY() ) );
    cercleCirconscrit.setRayon(rayon);
    cercleCirconscrit.setTriangle(this);
}

//获取邻接点
const vector< Triangle * > & Triangle::getVoisins() const{
    return this->voisins;
}

//获取得到三点
const vector< Point * > & Triangle::getLesTroisPoints() const{
    return this->lesTroisPoints;
}

//获取外接圆
const Cercle & Triangle::getCercle() const{
    return this->cercleCirconscrit;
}

//判断是空
bool Triangle::isNull() const{
    return this->null;
}

//设置外接圆
void Triangle::setCercle( const Cercle & c ){
    this->cercleCirconscrit = c;
}

//设置空
void Triangle::setNull( const bool & n ){
    this->null = n;
}

//判断是否相邻
bool Triangle::estVoisinAvec( Triangle * t ) const{
    for ( Triangle * voisin : this->voisins )
        if ( voisin == t )
            return true;
    return false;
}

//获取棱三角形的三个邻接点
vector< vector < Point * > > Triangle::getAretesSansVoisin() const{
    vector< vector < Point * > > aretesSansVoisin;
    for ( Triangle * voisin : this ->voisins ){
        if ( voisin->isNull() ){
            aretesSansVoisin.push_back( this->getAreteCommune(voisin) );
        }
    }
    return aretesSansVoisin;
}
