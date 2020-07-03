#ifndef GENERATEURCARAPACEALEA_H
#define GENERATEURCARAPACEALEA_H

#include "generateurcarapace.h"

//生成壳GenerateurCarapaceAlea 类 公有继承 生成壳GenerateurCarapace 类
class GenerateurCarapaceAlea : public GenerateurCarapace{
public:
    GenerateurCarapaceAlea();
    GenerateurCarapaceAlea( Carapace * );
    vector< Point * > calculPositionSites( const Bezier * ) const;
};

#endif // GENERATEURCARAPACEALEA_H
