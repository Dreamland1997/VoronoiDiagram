#include "anglecapable.h"

//默认构造函数的实现
AngleCapable::AngleCapable() : alpha(0) {}

//构造函数的实现
AngleCapable::AngleCapable( const Point * p1 , const Point * p , const Point * p2 ) : alpha(0){
    double sinus , cosinus;
    sinus = ( ( p2->getY() - p->getY() ) * ( p1->getX() - p->getX() ) ) - ( ( p1->getY() - p->getY() ) * ( p2->getX() - p->getX() ) );    //正弦值
    cosinus = ( ( p2->getX() - p->getX() ) * ( p1->getX() - p->getX() ) ) + ( ( p2->getY() - p->getY() ) * ( p1->getY() - p->getY() ) );  //余弦值
    alpha = atan2( sinus , cosinus );     //正切值
}

//重载字符串的实现
AngleCapable::operator string() const{
    ostringstream oss;
    oss << alpha;
    return oss.str();
}

//重载==运算符的实现
bool AngleCapable::operator == ( const AngleCapable & ac ) const{
    return ( alpha == ac.alpha );
}

//重载=运算符的实现
const AngleCapable AngleCapable::operator = ( const AngleCapable & ac ){
    if( this != &ac )
        alpha = ac.alpha;
    return *this;
}

//重载！=运算符的实现
bool AngleCapable::operator != ( const AngleCapable & ac ) const{
    return !( *this == ac );
}

//重载+=运算符的实现
const AngleCapable AngleCapable::operator += ( const AngleCapable & ac ){
    alpha += ac.alpha;
    return *this;
}

//获取正切值函数的实现
double AngleCapable::getAlpha() const{
    return this->alpha;
}

//设置正切值函数的实现
void AngleCapable::setAlpha( const double &a ){
    this->alpha = a;
}
