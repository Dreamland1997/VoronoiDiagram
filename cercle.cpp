#include "cercle.h"

//默认构造函数的实现
Cercle::Cercle() : centre( new Point( 0 , 0 ) ) , rayon(0) {}

//构造函数的实现
Cercle::Cercle( Point * centre , const double & rayon ) : centre(centre) , rayon(rayon) {}

//复制构造函数的实现
Cercle::Cercle( const Cercle & c ) : centre(c.centre) , rayon(c.rayon) {}

//析构函数的实现
Cercle::~Cercle() {}

//重载=运算符的实现
const Cercle & Cercle::operator = ( const Cercle & c ){
    if( this != &c ){
        centre = c.centre;
        rayon = c.rayon;
    }
    return *this;
}

//重载==运算符的实现
bool Cercle::operator == ( const Cercle & c ) const{
    return ( centre == c.centre && ( fabs( rayon - c.rayon ) < 0.0001 ) );
}

//重载！=运算符的实现
bool Cercle::operator != ( const Cercle & c ) const{
    return !( *this == c );
}

//获取外接圆圆心的实现
Point * Cercle::getCentre() const{
    return this->centre;
}

//获取射线的实现
double Cercle::getRayon() const{
    return this->rayon;
}

//设置外接圆圆心的实现
void Cercle::setCentre( Point * c ){
    this->centre = c;
}

//设置射线的实现
void Cercle::setRayon( const double & r ){
    this->rayon = r;
}

//设置三角形的实现
void Cercle::setTriangle( Triangle * t ){
    this->triangle = t;
}

//获取三角形的实现
Triangle * Cercle::getTriangle() const{
    return this->triangle;
}
