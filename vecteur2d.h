#ifndef VECTEUR2D_H
#define VECTEUR2D_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

//类模板
template< class T >
const T operator - ( const T & u , const T & v ){
    return u + -v;
}

//向量2D类（容器）
class Vecteur2D{
    double x , y;
public:
    //显式的构造函数
    explicit Vecteur2D( const double & x = 0 , const double & y = 0 ) : x(x) , y(y) {}

    //复制构造函数
    Vecteur2D( const Vecteur2D & v ) : x( v.x ) , y( v.y) {}

    //虚析构
    virtual ~Vecteur2D() {}

    //获取X的函数
    double getX() const{
        return x;
    }

    //设置X的函数
    void setX( const double & nouveauX ){
        x = nouveauX;
    }

    //获取Y的函数
    double getY() const{
        return y;
    }

    //设置Y的函数
    void setY( const double & nouveauY ){
        y = nouveauY;
    }

    //重载+运算符
    const Vecteur2D operator + ( const Vecteur2D & u ) const{
        return Vecteur2D( x + u.x , y + u.y );
    }

    //重载*运算符
    const Vecteur2D operator * ( const double & a ) const{
        return Vecteur2D( x * a , y * a );
    }

    //重载-运算符
    const Vecteur2D operator - () const{
        return Vecteur2D( -x , -y );
    }

    //重载^运算符
    bool operator ^( const Vecteur2D & w ) const{
        bool vecteurSortant;
        double composanteZ;
        composanteZ = this->getX() * w.getY() - this->getY() * w.getX();  //Z分量的值
        vecteurSortant = ( composanteZ >= 0 );
        return vecteurSortant;        //1 或者 0
    }

    //字符串输出流
    operator string() const{
        ostringstream oss;
        oss << "(" << x << "," << y << ")";
        return oss.str();
    }

    //重载==运算符
    bool operator == ( const Vecteur2D & v ) const{
        return  ( x == v.getX() && y == v.getY() );
    }

    //重载！=运算符
    bool operator != ( const Vecteur2D & v ) const{
        return !( * this == v );
    }

    //重载=运算符
    const Vecteur2D operator = ( const Vecteur2D & v ){
        if( this != &v ){
            x = v.getX();
            y = v.getY();
        }
        return *this;
    }

    //友远的输出流<<重载
    friend ostream & operator << ( ostream & os , const Vecteur2D & u ){
        os << "(" << u.getX() << "," << u.getY() << ")";
        return os;
    }

    double determinant( const Vecteur2D & ) const;
};

#endif // VECTEUR2D_H
