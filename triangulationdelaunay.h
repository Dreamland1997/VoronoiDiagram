#ifndef TRIANGULATIONDELAUNAY_H
#define TRIANGULATIONDELAUNAY_H

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <tuple>
#include "outils.h"
#include "triangle.h"

using namespace std;

//三角剖分Delaunay类
class TriangulationDelaunay{
private:
    //凸包框架
    Point * coinInferieurGauche , * coinInferieurDroit , * coinSuperieurGauche , * coinSuperieurDroit;  //左下角 ，右下角 ， 左上角 ，右上角
    vector< Triangle * > DT;         //三角形的向量
    vector< Point * > points;        //点
public:
    TriangulationDelaunay( vector< Point * > );

    tuple< Triangle * , Triangle * > genererTrianglesFictifs( vector< Point * > );

    void calculerTriangulation( Point * );

    void determiner_DTL( const Point * , Triangle * , vector< Triangle * > * );
    vector< Triangle * > determiner_NTL( Point * , vector< Triangle * > * );
    Triangle * determinerTriangleContenantNouveauPoint( const Point * );

    void supprimerTriangles( vector <Triangle * > * );
    int indiceTriangleDansDT( Triangle * ) const;
    vector< Triangle * > getTriangulation();

    const vector< Triangle * > & getDT() const;
    const vector< Point * > & getPoints() const;
};

#endif // TRIANGULATIONDELAUNAY_H
