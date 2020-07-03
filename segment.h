#ifndef SEGMENT_H
#define SEGMENT_H

#include "point.h"

//线段类
class Segment{
private:
    Point *a , *b;
public:
    Segment();
    Segment( Point * , Point * );

    Point * getA() const;
    void setA( Point * );

    Point * getB() const;
    void setB( Point * );

    operator string() const;

    double getLongueur() const;
};

//内联函数：重载 << 通用输出流
inline ostream & operator << ( ostream & f , const Segment & s ){
    return f << ( string )s;
}

#endif // SEGMENT_H
