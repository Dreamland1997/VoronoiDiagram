#ifndef ANGLECAPABLE_H
#define ANGLECAPABLE_H

#include "point.h"
#include <cmath>

using namespace std;

//角度类
class AngleCapable{
private:
    double alpha;
public:
    AngleCapable();
    AngleCapable( const Point * , const Point * , const Point * );
    operator string() const;
    bool operator == ( const AngleCapable & ) const;
    bool operator != ( const AngleCapable & ) const;
    const AngleCapable operator = ( const AngleCapable & );
    const AngleCapable operator += ( const AngleCapable & );
    double getAlpha() const;
    void setAlpha( const double & );
};

//内联函数：输出流<<的重载
inline ostream & operator << ( ostream & f , const AngleCapable & ac ){
    return f << ( string )ac;
}

#endif // ANGLECAPABLE_H
