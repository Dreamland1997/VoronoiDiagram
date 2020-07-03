#ifndef EQUATIONDROITEVERTICALE_H
#define EQUATIONDROITEVERTICALE_H

#include "point.h"
#include "equationdroitebase.h"
#include "equationdroite.h"

using namespace std;

//法线（垂直）方程类
class EquationDroiteVerticale{
private:
    double c;
public:
    EquationDroiteVerticale( const double & );
    EquationDroiteVerticale( const Point & );
    EquationDroiteVerticale( const EquationDroiteVerticale & );
    operator string() const;
    const EquationDroiteVerticale & operator = ( const EquationDroiteVerticale & );
    double getC() const;
    void setC( const double & );
    EquationDroite * getEquationDroitePerpendiculairePassantParPoint( Point * ) const;
};

#endif // EQUATIONDROITEVERTICALE_H
