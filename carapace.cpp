#include "carapace.h"
#include "application.h"

//壳类 默认构造函数的实现
Carapace::Carapace() {}

//壳类 构造函数的实现
Carapace::Carapace( Application * a ) : application(a) {}

//获取顶部轮廓
const vector< Point * > & Carapace::getContourHaut() const{
    return this->contourHaut;
}

//获取底部轮廓
const vector< Point * > & Carapace::getContourBas() const{
    return this->contourBas;
}

//获取站点
const vector< Point * > & Carapace::getSites() const{
    return this->sites;
}

//设置顶部轮廓
void Carapace::setContourHaut( const vector<Point *> & cH ){
    this->contourHaut.clear();
    for ( size_t i = 0 ; i <  cH.size() ; i ++ )
        this->contourHaut.push_back(cH[i]);
}

//设置底部轮廓
void Carapace::setContourBas( const vector<Point *> & cB ){
    this->contourBas.clear();
    for ( size_t i = 0 ; i < cB.size() ; i ++ )
        this->contourBas.push_back(cB[i]);
}

//设置站点
void Carapace::setSites( const vector<Point *> & s ){
    this->sites.clear();
    for ( size_t i = 0 ; i < s.size() ; i ++ )
        this->sites.push_back(s[i]);
}

//获取三角形
const vector< Triangle * > & Carapace::getTriangles() const{
    return this->triangles;
}

//设置三角形
void Carapace::setTriangles( const vector<Triangle *> & triangles ){
    this->triangles.clear();
    for ( Triangle * t : triangles )
        this->triangles.push_back(t);
}

//更新应用程序视图窗口
void Carapace::updateVue() const{
    this->application->update();
}

//获取Voronoi图
DiagrammeVoronoi * Carapace::getVoronoi() const{
    return this->voronoi;
}

//设置Voronoi图
void Carapace::setVoronoi( DiagrammeVoronoi * dv ){
    this->voronoi = dv;
}

//获取所有轮廓点
vector< Point * > Carapace::getTousLesPointsDuContour() const{
    vector< Point * > tousLesPoints;
    for ( Point * p : this->contourBas )
        tousLesPoints.push_back(p);
    for ( Point * p : this->contourHaut )
        tousLesPoints.push_back(p);
    return tousLesPoints;
}
