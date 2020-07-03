#ifndef EQUATIONDROITE_H
#define EQUATIONDROITE_H

#include "point.h"
#include "equationdroitebase.h"

using namespace std;

//（直线方程式）EquationDroite类公有继承类EquationDroiteBase（基本方程式）
class EquationDroite : public EquationDroiteBase{
//公有成员
public:
    EquationDroite( const double & , const double & );
    EquationDroite( const Point & , const Point & );
    EquationDroite( const EquationDroite & );
    operator string() const;
    double getA() const;
    double getB() const;
    void setA( const double & );
    void setB( const double & );
    EquationDroite * getEquationDroitePerpendiculairePassantParPoint( Point * )const;

//私有成员
private:
    double a  , b;   //y = ax + b
};

#endif // EQUATIONDROITE_H
