#include "generateurcarapacealea.h"

//生成壳 默认构造函数的实现
GenerateurCarapaceAlea::GenerateurCarapaceAlea() : GenerateurCarapace() {}

//生成壳 构造函数的实现
GenerateurCarapaceAlea::GenerateurCarapaceAlea( Carapace * c ) : GenerateurCarapace( c ) {}

//计算站点的位置
vector< Point * > GenerateurCarapaceAlea::calculPositionSites( const Bezier * b ) const{
    vector< Point * > pointsResultats;
    Point * point;

    for ( double t = 0.1 ; t <= 0.9 ; t += 0.2 ){
        point = b->bezier(t);
        Outils::faireVarierStochastiquementLocalementUnPoint( point );
        pointsResultats.push_back( point );
        point = new Point( point->getX() , -point->getY() );
        Outils::faireVarierStochastiquementLocalementUnPoint( point );
        pointsResultats.push_back( point );
        point = new Point( t * 10 , 0 );
        Outils::faireVarierStochastiquementLocalementUnPoint( point );
        pointsResultats.push_back( point );
    }
    return pointsResultats;
}
