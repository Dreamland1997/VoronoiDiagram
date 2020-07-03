#include "diagrammevoronoi.h"

//Voronoi图构造函数的实现
DiagrammeVoronoi::DiagrammeVoronoi( Carapace * carapace ){
    this->carapace = carapace;

    //三角形包含的点 ， 少于三个邻居的三角形
    vector< Triangle * > trianglesContenantPoint, trianglesAyantMoinsDeTroisVoisins;
    //顶点
    Sommet * s1 , * s2;
    //棱
    vector< Arete * > aretes;
    //数据
    Element< Arete * > * l;
    //三角形
    Triangle * t1 , * t2;
    //面
    Face * face;
    //点
    Point * p1 , * p2 , *intersection1 , * intersection2 ,
            * ptIntersection1 , * ptIntersection2 , * milieu1 , * milieu2;
    //直线方程式
    EquationDroite * droitePerpendiculaireArete1 , * droitePerpendiculaireArete2 , * droiteContour;
    //线段
    Segment * segmentContour , * segmentTmp1 , * segmentTmp2;
    //向量
    vector< Point * > contour , areteConsideree1 , areteConsideree2;
    vector< vector< Point * > > aretesSansVoisin1 , aretesSansVoisin2;

    //创建简单的面
    for ( Point * point : carapace->getSites() ){
        trianglesContenantPoint = this->getTrianglesParPoint( point , carapace->getTriangles() );
        for ( Triangle * T1 : trianglesContenantPoint ){
            for ( Triangle * T2 : trianglesContenantPoint ){
                if ( T1 != T2 && T1->estVoisinAvec(T2) ){
                    s1 = new Sommet( "" , T1->getCercle().getCentre() , graphe.getProchaineClef() );
                    s2 = new Sommet( "" , T2->getCercle().getCentre() , graphe.getProchaineClef() );
                    if ( !graphe.areteEntrePointsExiste( s1 , s2 ) ){
                        graphe.ajouterSommets(s1);
                        graphe.ajouterSommets(s2);
                        this->graphe.creeArete( s1 , s2 , "" );
                    }
                }
            }
        }
    }

    //管理面（边缘）
    for ( Point * point : carapace->getSites() ){
        aretes.clear();
        trianglesContenantPoint = this->getTrianglesParPoint( point , carapace->getTriangles() );
        for ( l = graphe.getAretes() ; l ; l = l->s ){
            s1 = l->v->getExtremite1();
            s2 = l->v->getExtremite2();
            t1 = Outils::getTriangleParCentreCercleCirconscrit( s1->getPosition() , trianglesContenantPoint );
            t2 = Outils::getTriangleParCentreCercleCirconscrit( s2->getPosition() , trianglesContenantPoint );
            if ( t1 && t2 ){
                aretes.push_back(l->v);
            }
        }
        //整个面，封闭面
        if ( trianglesContenantPoint.size() == aretes.size() ){
            face = graphe.creeFace("");
            for ( Arete * arete : aretes ){
                face->ajouterArete(arete);
            }
        }
        //开放的面 ， 边缘管理
        else if ( point != Outils::getPointLePlusAGauche( carapace->getSites() ) && point != Outils::getPointLePlusADroite( carapace->getSites() ) ){
            trianglesAyantMoinsDeTroisVoisins = Outils::getTrianglesAyantMoinsDeTroisVoisins( trianglesContenantPoint );
            //末端
            if ( trianglesAyantMoinsDeTroisVoisins.size() == 1 ){
            }
            //面不封闭 不开发
            else if ( trianglesAyantMoinsDeTroisVoisins.size() == 2 ){
                t1 = trianglesAyantMoinsDeTroisVoisins.at(0);
                t2 = trianglesAyantMoinsDeTroisVoisins.at(1);

                p1 = t1->getCercle().getCentre();
                p2 = t2->getCercle().getCentre();

                aretesSansVoisin1 = t1->getAretesSansVoisin();
                aretesSansVoisin2 = t2->getAretesSansVoisin();

                //如果有两个没有邻居的边，则结束，选择正确的那个边
                areteConsideree1 = Outils::getAreteContenantPoint( aretesSansVoisin1 , point );
                areteConsideree2 = Outils::getAreteContenantPoint( aretesSansVoisin2 , point );

                milieu1 = Outils::getPointMilieu( areteConsideree1.at(0) , areteConsideree1.at(1) );
                milieu2 = Outils::getPointMilieu( areteConsideree2.at(0) , areteConsideree2.at(1) );

                droitePerpendiculaireArete1 = new EquationDroite( * p1 , * milieu1 );
                droitePerpendiculaireArete2 = new EquationDroite( * p2 , * milieu2 );

                segmentTmp1 = segmentTmp2 = NULL;

                contour = this->getContourParRapportACotePoint(point);

                for ( size_t i = 0 ; i < contour.size() - 1 ; i ++ ){
                    segmentContour = new Segment( contour.at(i) , contour.at( i + 1 ) );
                    droiteContour = new EquationDroite( * segmentContour->getA() , * segmentContour->getB() );
                    try {
                        intersection1 = Outils::intersection2Droites( * droitePerpendiculaireArete1 , * droiteContour );
                        intersection2 = Outils::intersection2Droites( * droitePerpendiculaireArete2 , * droiteContour );
                    } catch ( Erreur e ) {
                        //不做任何事情就没有交集，仅此而已
                    }
                    if ( Outils::pointEstSurSegment( intersection1 , segmentContour ) ){
                        ptIntersection1 = Outils::getPointDuContourLePlusProche( intersection1 , contour );
                        if ( segmentTmp1 == NULL ){
                            segmentTmp1 = new Segment( p1 , ptIntersection1 );
                        }
                        else{
                            if ( segmentTmp1->getLongueur() >= Outils::getDistanceEuclidienne( p1 , ptIntersection1 ) )
                                segmentTmp1 = new Segment( p1 , ptIntersection1 );
                        }
                    }
                    if (Outils::pointEstSurSegment( intersection2 , segmentContour ) ){
                        ptIntersection2 = Outils::getPointDuContourLePlusProche( intersection2 , contour );
                        if ( segmentTmp2 == NULL ){
                            segmentTmp2 = new Segment( p2 , ptIntersection2 );
                        }
                        else{
                            if ( segmentTmp2->getLongueur() >= Outils::getDistanceEuclidienne( p2 , ptIntersection2 ) )
                                segmentTmp2 = new Segment( p2 , ptIntersection2 );
                        }
                    }
                }
                s1 = this->graphe.creeSommet( "" , segmentTmp1->getA() );
                s2 = this->graphe.creeSommet( "" , segmentTmp1->getB() );
                aretes.push_back( this->graphe.creeArete( s1 , s2 , "" ) );
                s1 = this->graphe.creeSommet( "" , segmentTmp2->getA() );
                s2 = this->graphe.creeSommet( "" , segmentTmp2->getB() );
                aretes.push_back( this->graphe.creeArete( s1 , s2 , "" ) );
            }
        }
    }
}

//通过棱获取轮廓
vector< Point * > DiagrammeVoronoi::getContourParRapportACoteArete( vector<Point *> arete ) const{
    Point * p1 , * p2;
    p1 = arete.at(0);
    p2 = arete.at(1);
    if ( p1->getY() < 0 || p2->getY() < 0 )
        return this->carapace->getContourBas();
    return this->carapace->getContourHaut();
}

//通过点获取轮廓
vector< Point * > DiagrammeVoronoi::getContourParRapportACotePoint( Point * point ) const{
    if ( point->getY() < 0 )
        return this->carapace->getContourBas();
    return this->carapace->getContourHaut();
}

//获取三角形包含的点
const vector< Triangle * > DiagrammeVoronoi::getTrianglesParPoint( Point * point , const vector<Triangle *> & triangles ) const{
    vector< Triangle * > trianglesContenantPoint;
    for ( Triangle * triangle : triangles )
        if ( triangle->contientPoint(point) )
            trianglesContenantPoint.push_back(triangle);
    return trianglesContenantPoint;
}

//获取画图工具
const Graphe & DiagrammeVoronoi::getGraphe() const{
    return this->graphe;
}
