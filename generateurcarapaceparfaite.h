#ifndef GENERATEURCARAPACEPARFAITE_H
#define GENERATEURCARAPACEPARFAITE_H

#include "generateurcarapace.h"

//生成完美的壳类 公有继承 生成壳类
class GenerateurCarapaceParfaite : public GenerateurCarapace{
public:
    GenerateurCarapaceParfaite();
    GenerateurCarapaceParfaite( Carapace * );
    vector< Point * > calculPositionSites( const Bezier * ) const;
};

#endif // GENERATEURCARAPACEPARFAITE_H
