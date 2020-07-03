#include "equationdroiteverticale.h"

//默认构造函数的实现
EquationDroiteVerticale::EquationDroiteVerticale( const double & c ) : c(c) {}

//构造函数的实现
EquationDroiteVerticale::EquationDroiteVerticale( const Point & p1 ) : c() {
    c = p1.getX();
}

//复制构造函数的实现
EquationDroiteVerticale::EquationDroiteVerticale( const EquationDroiteVerticale & edv ) : c(edv.c) {}

//字符串运算符的重载
EquationDroiteVerticale::operator string() const{
    ostringstream oss;
    oss << "x = " << c;
    return oss.str();
}

//重载=运算符的实现
const EquationDroiteVerticale & EquationDroiteVerticale::operator=(const EquationDroiteVerticale & edv){
    c = edv.c;
    return *this;
}

//获取C的实现
double EquationDroiteVerticale::getC() const{
    return this->c;
}

//设置C的实现
void EquationDroiteVerticale::setC(const double & c){
    this->c = c;
}

//法线方程（截距）的实现
EquationDroite * EquationDroiteVerticale::getEquationDroitePerpendiculairePassantParPoint(Point * p) const{
    return new EquationDroite( 0 , p->getY() );  //法线方程 y = -（1/a）x + b   a = 0（斜率）   b = y(截距)
}
