#include "segment.h"

//默认构造函数的实现
Segment::Segment() {}

//构造函数的实现
Segment::Segment( Point * a , Point * b ) : a(a) , b(b) {}

//获取A  设置A的实现
Point * Segment::getA() const{
    return this->a;
}

void Segment::setA( Point * p){
    this->a = p;
}

//获取B 设置B的实现
Point * Segment::getB() const{
    return this->b;
}

void Segment::setB( Point * p ){
    this->b = p;
}

//重载字符串的实现
Segment::operator string() const{
    ostringstream oss;
    oss << "Segment[" << *this->a << ", " << *this->b << "]";
    return oss.str();
}

//获取线段长度(两点间的距离公式)
double Segment::getLongueur() const{
    return sqrt( ( ( this->b->getX() - this->a->getX() ) * ( this->b->getX() - this->a->getX() ) ) + ( ( this->b->getY() - this->a->getY() ) * ( this->b->getY() - this->a->getY() ) ) );
}
