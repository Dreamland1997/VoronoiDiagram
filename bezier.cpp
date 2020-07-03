#include "bezier.h"

//默认构造函数的实现
Bezier::Bezier() {}

//析构函数的实现
Bezier::~Bezier() {}

//添加点的实现
void Bezier::ajouterPoint(const Point & point){
    this->pointsDeControle.push_back( point );
}

//大小
int Bezier::taille() const{
    return this->pointsDeControle.size();    //返回大小
}

//
Point * Bezier::bezier(const double & t) const{
    int m = taille() - 1;
    double resultatX = 0 , resultatY = 0;
    TrianglePascal tp(m);
    double d;
    for( int i = 0 ; i <= m ; i ++ ){
        d = Bernstein::bernstein( t , i , m , tp );
        resultatX += ( d * this->pointsDeControle[i].getX() );
        resultatY += ( d * this->pointsDeControle[i].getY() );
    }
    return new Point( resultatX , resultatY );
}
