#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <cmath>

//直线方程类的前项引用声明
class EquationDroite;

using namespace std;

//点类
class Point{
    double x , y;
public:
    Point( const double & x = 0 , const double & y = 0 );
    Point ( const Point & );
    //虚析构
    virtual ~Point();
    double getX() const;
    double getY() const;
    void setX( const double & );
    void setY( const double & );
    //重载运算符
    operator string() const;
    bool operator == ( const Point & ) const;
    bool operator != ( const Point & ) const;
    bool estDans( vector<Point *>) const;
    const Point & operator = ( const Point & );
    bool pointVerifieEquationDroite( EquationDroite * ) const;
};

//内联函数：编译时在调用处用函数体进行替换，节省了参数传递，控制转移等开销，通用输出流
inline ostream & operator << ( ostream & f , const Point & p ){
    return f << ( string ) p;
}

#endif // POINT_H
