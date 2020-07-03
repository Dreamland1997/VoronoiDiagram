#include "generateurcarapaceparfaite.h"

//生成完美的壳类 默认构造函数的实现
GenerateurCarapaceParfaite::GenerateurCarapaceParfaite() : GenerateurCarapace() {}

//生成完美的壳类 构造函数的实现
GenerateurCarapaceParfaite::GenerateurCarapaceParfaite( Carapace * c ) : GenerateurCarapace( c ) {}

//计算站点的位置
vector< Point * > GenerateurCarapaceParfaite::calculPositionSites( const Bezier * b ) const{
    vector< Point * > pointsResultats;
    Point * point;

    for ( double t = 0.1 ; t <= 0.9 ; t += 0.2 ){
        point = b->bezier( t );
        pointsResultats.push_back( point );
        point = new Point( point->getX() , -point->getY() );
        pointsResultats.push_back( point );
        point = new Point( t * 10 , 0 );
        pointsResultats.push_back( point );
    }
    return pointsResultats;
}
