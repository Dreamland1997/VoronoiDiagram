#ifndef DIAGRAMMEVORONOI_H
#define DIAGRAMMEVORONOI_H

#include <vector>
#include "carapace.h"
#include "graphe.h"
#include "segment.h"

using namespace std;

//Voronoi图类
class DiagrammeVoronoi{
private:
    Graphe graphe;                    //画图形类对象
    Carapace * carapace;              //壳类对象
public:
    DiagrammeVoronoi( Carapace * carapace );

    vector< Point * > getContourParRapportACoteArete( vector< Point * > ) const;
    vector< Point * > getContourParRapportACotePoint( Point * ) const;

    const vector< Triangle * > getTrianglesParPoint( Point * , const vector< Triangle * > & ) const;
    const Graphe & getGraphe() const;
};

#endif // DIAGRAMMEVORONOI_H
