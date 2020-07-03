#ifndef BEZIER_H
#define BEZIER_H

#include <vector>
#include "point.h"
#include "bernstein.h"

using namespace std;

//Bezier（贝塞尔）曲线类
class Bezier{
private:
    vector< Point > pointsDeControle;
public:
    Bezier();
    ~Bezier();
    void ajouterPoint( const Point & );
    int taille() const;
    Point * bezier( const double & ) const;
};

#endif // BEZIER_H
