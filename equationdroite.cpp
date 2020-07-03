#include "equationdroite.h"

//构造函数的实现
EquationDroite::EquationDroite( const double & a , const double & b ) : a(a) , b(b) {}

//构造函数的实现
EquationDroite::EquationDroite( const Point & p1 , const Point & p2 ) : a() , b(){
    a = ( p2.getY() - p1.getY() ) / ( p2.getX() - p1.getX() );  // 求直线斜率a = y / x
    b = p1.getY() - a * p1.getX();    //求直线方程 y = ax + b   b = y - ax
}

//复制构造函数的实现
EquationDroite::EquationDroite( const EquationDroite & ed ) : a( ed.a ) , b( ed.b ) {}

//重载运算符的实现
EquationDroite::operator string() const{
    ostringstream oss;
    oss << "y = " << a << "x + " << b;     //输出y = ax + b的值
    return oss.str();
}

//获取A(斜率)的实现
double EquationDroite::getA() const{
    return this->a;
}

//获取B(截距)的实现
double EquationDroite::getB() const{
    return this->b;
}

//设置A(斜率)的实现
void EquationDroite::setA( const double & a ){
    this->a = a;
}

//设置B(截距)的实现
void EquationDroite::setB(const double & b ){
    this->b = b;
}

//法线方程的实现
EquationDroite *EquationDroite::getEquationDroitePerpendiculairePassantParPoint( Point * p ) const{
    double aP = -1 / ( this->a );   //法线方程斜率 = -(1/a)
    double bP =  p->getY() + ( ( 1 / this->a ) * p->getX() );  //法线方程 y = -（1/a）x + b   b = y + (1/a)x
    return new EquationDroite( aP , bP );
}
