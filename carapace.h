#ifndef CARAPACE_H
#define CARAPACE_H

#include <vector>
#include "point.h"
#include "triangle.h"
#include "element.h"
#include "arete.h"

//应用程序窗口类和Voronoi图类的前项引用声明
class Application;
class DiagrammeVoronoi;

using namespace std;

//壳类
class Carapace{
private:
    vector< Point * > contourHaut , contourBas , sites;    //顶部轮廓 ， 底部轮廓 ， 站点
    vector< Triangle * > triangles;                        //三角形
    Application * application;                             //应用
    DiagrammeVoronoi * voronoi;                            //Voronoi图
public:
    Carapace();
    Carapace( Application * );

    const vector< Point * > & getContourHaut() const;
    const vector< Point * > & getContourBas() const;
    const vector< Point * > & getSites() const;

    void setContourHaut( const vector< Point * > & );
    void setContourBas( const vector< Point * > & );
    void setSites( const vector< Point * > & );

    const vector< Triangle * > & getTriangles() const;
    void setTriangles( const vector< Triangle * > & );

    void updateVue() const;

    DiagrammeVoronoi * getVoronoi() const;
    void setVoronoi( DiagrammeVoronoi * );

    vector< Point * > getTousLesPointsDuContour() const;

};

#endif // CARAPACE_H
