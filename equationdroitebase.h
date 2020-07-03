#ifndef EQUATIONDROITEBASE_H
#define EQUATIONDROITEBASE_H

#include <iostream>
#include <string>
#include "point.h"

using namespace std;

//基本直线方程式类
class EquationDroiteBase{
public:
    EquationDroiteBase();
    virtual operator string() const = 0;
    virtual EquationDroite * getEquationDroitePerpendiculairePassantParPoint ( Point * ) const = 0;
};

//内联函数：编译时在调用处用函数体进行替换，节省了参数传递，控制转移等开销，输出流迭代器
inline ostream & operator << ( ostream & f , const EquationDroiteBase & edb ){
    return f << ( string ) edb;
}

#endif // EQUATIONDROITEBASE_H
