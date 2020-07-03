#ifndef GENERATEURCARAPACE_H
#define GENERATEURCARAPACE_H

#include <vector>
#include "point.h"
#include "carapace.h"
#include "bezier.h"
#include "outils.h"
#include "triangulationdelaunay.h"
#include "diagrammevoronoi.h"

//生成壳 类
class GenerateurCarapace{
private:
    Carapace * carapace;         //壳对象
protected:
    vector< Point * > genererSitesPourCarapace( const Point & , const Point & , const Point & ) const;   //生成外壳站点
public:
    static Point * pointMilieuPrecedent;   //前一个中中间点

    GenerateurCarapace();
    GenerateurCarapace( Carapace * );

    void genererCarapace();
    void genererNouveauxSites() const;

    virtual vector< Point * > calculPositionSites( const Bezier * ) const = 0;
};

#endif // GENERATEURCARAPACE_H
