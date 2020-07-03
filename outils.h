#ifndef OUTILS_H
#define OUTILS_H

#include <QRandomGenerator>
#include <cmath>
#include <cfloat>
#include "point.h"
#include "triangle.h"
#include "equationdroite.h"
#include "equationdroiteverticale.h"
#include "anglecapable.h"
#include "erreur.h"
#include "cercle.h"
#include "segment.h"

//三角形类的前项引用声明
class Triangle;

//工具类
class Outils{
public:
    //绘图工具
    static int getNombreAleatoireEntreDeuxNombres( const int , const int );
    static void faireVarierStochastiquementLocalementUnPoint( Point * );
    static Point * calculerPointDeControleMilieu( const Point *  , const Point *  );

    //三角剖分工具
    static bool pointEstDansTriangle( const Point * , const Triangle * );
    static bool appartientACercle( const Point * , const Cercle * );
    static Point * intersection2Droites( const EquationDroite & , const EquationDroite & );
    static Point * intersectionDroiteVerticaleEtAutre( const EquationDroiteVerticale & , const EquationDroite & );
    static const EquationDroiteVerticale equationMediatriceOrdonneesEgales( const Point * , const Point * );
    static const EquationDroite equationMediatriceOrdonneesPasEgales( const Point * , const Point * );
    static int indicePointLePlusAGauche( const vector< Point * > & );
    static double getxMin( const vector< Point * > & );
    static double getxMax( const vector< Point * > & );
    static double getyMax( const vector< Point * > & );
    static double getyMin( const vector< Point * > & );

    //Voronoi图的工具
    static Triangle * getTriangleParCentreCercleCirconscrit( Point * , const vector< Triangle * > & );
    static vector < Triangle * > getTrianglesAyantMoinsDeTroisVoisins( const vector< Triangle * > & );
    static bool pointEstSurSegment( Point *  , Segment * );
    static double getDistanceEuclidienne( Point * , Point * );
    static Point * getPointDuContourLePlusProche( Point * inter , const vector< Point * > & );
    static Point * getPointMilieu( Point * , Point * );
    static vector< Point * > getAreteContenantPoint( const vector< vector< Point * > > & , Point * );
    static Point * getPointLePlusAGauche( const vector< Point * > & );
    static Point * getPointLePlusADroite( const vector< Point * > & );
};

#endif // OUTILS_H
