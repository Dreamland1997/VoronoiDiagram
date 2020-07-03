#include "point.h"
#include "equationdroite.h"

//构造函数实现
Point::Point( const double & x , const double & y ) : x(x) , y(y){}

//复制构造函数实现(已存在的对象去初始化一个新对象)
Point::Point( const Point & p ) : x( p.x ) , y( p.y ){}

//析构函数的实现
Point::~Point() {}

//获取X的实现
double Point::getX() const{
    return  x;
}

//获取Y的实现
double Point::getY() const{
    return y;
}

//设置X的实现
void Point::setX( const double & nouveauX ){
    x = nouveauX;
}

//设置Y的实现
void Point::setY( const double & nouveauY ){
    y = nouveauY;
}

//字符串输出流的实现
Point::operator string () const{
    ostringstream oss;
    oss << "(" << x << "," << y << ")";
    return oss.str();
}

//重载等于运算符的实现
bool Point::operator == ( const Point & p ) const{
    return  ( fabs( x - p.getX() ) < 0.0001 && fabs( y - p.getY() ) < 0.0001 );
}

//重载不等运算符的实现
bool Point::operator != ( const Point & p ) const{
    return !( *this == p );
}

//判断点是否相等的实现
bool Point::estDans( vector<Point *> points ) const{
    for( const Point * point : points )
        if( this == point )
            return true;
    return false;
}

//复制构造的实现
const Point & Point::operator = ( const Point & p ){
    if( this != &p ){
        x = p.getX();
        y = p.getY();
    }
    return *this;
}

//点验证是否在方程的实现
bool Point::pointVerifieEquationDroite( EquationDroite *e ) const{
    if( this->getY() == ( e->getA() * this-> getX() + e->getB()))   //验证 y = ax + b 是否相等
        return true;
    return false;
}
