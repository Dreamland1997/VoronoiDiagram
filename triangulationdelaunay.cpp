#include "triangulationdelaunay.h"

//三角剖分构造函数的实现
TriangulationDelaunay::TriangulationDelaunay( vector< Point * > points ){
    Triangle * triangleFictif1 , * triangleFictif2;    //虚拟三角形1 ，2
    triangleFictif1 = NULL;
    triangleFictif2 = NULL;

    //可操作元组
    std::tie( triangleFictif1 , triangleFictif2 ) = this->genererTrianglesFictifs(points);
    DT.push_back(triangleFictif1);
    DT.push_back(triangleFictif2);

    for ( int i = 0 ; i < 3 ; i ++ ){
        //如果不在三角剖分中，则将点添加到三角形中
        if ( find( this->points.begin() , this->points.end() , triangleFictif1->getLesTroisPoints()[i] ) == this->points.end() )
            this->points.push_back( triangleFictif1->getLesTroisPoints()[i] );
        if ( find( this->points.begin() , this->points.end() , triangleFictif2->getLesTroisPoints()[i] ) == this->points.end() )
            this->points.push_back( triangleFictif2->getLesTroisPoints()[i] );
    }
    for ( Point * point : points )
        this->calculerTriangulation(point);
}

//生成虚拟三角形
std::tuple< Triangle * , Triangle * > TriangulationDelaunay::genererTrianglesFictifs( vector<Point *> points ){
    //恢复边缘的坐标
    double xMin , xMax , yMin , yMax;
    xMin = Outils::getxMin(points);
    xMax = Outils::getxMax(points);
    yMin = Outils::getyMin(points);
    yMax = Outils::getyMax(points);

    //创建4个点
    this->coinInferieurGauche = new Point( xMin , yMin );
    this->coinSuperieurGauche = new Point( xMin , yMax );
    this->coinInferieurDroit = new Point( xMax , yMin );
    this->coinSuperieurDroit = new Point( xMax , yMax );

    //创建起始矩形的两个虚拟三角形
    Triangle * triangleFictif1 , * triangleFictif2;
    triangleFictif1 = new Triangle( coinInferieurGauche , coinSuperieurGauche , coinInferieurDroit );
    triangleFictif2 = new Triangle( coinSuperieurGauche , coinInferieurDroit , coinSuperieurDroit );

    //为虚拟三角形的虚拟邻居创建附加点
    Point * ptVoisin1TF1 , * ptVoisin2TF1 , * ptVoisin1TF2 , * ptVoisin2TF2;
    ptVoisin1TF1 = new Point( xMin - 1 , yMin );
    ptVoisin2TF1 = new Point( xMin , yMin - 1 );
    ptVoisin1TF2 = new Point( xMin , yMax + 1 );
    ptVoisin2TF2 = new Point( xMax + 1 , yMin );

    //建立起始三角形的邻近三角形
    Triangle * voisin1TriangleFictif1 , * voisin2TriangleFictif1 , * voisin1TriangleFictif2 , * voisin2TriangleFictif2;
    voisin1TriangleFictif1 = new Triangle( ptVoisin1TF1 , coinInferieurGauche , coinSuperieurGauche , true );
    voisin2TriangleFictif1 = new Triangle( ptVoisin2TF1 , coinInferieurGauche , coinInferieurDroit , true );
    voisin1TriangleFictif2 = new Triangle( ptVoisin1TF2 , coinSuperieurGauche , coinSuperieurDroit , true );
    voisin2TriangleFictif2 = new Triangle( ptVoisin2TF2 , coinInferieurDroit , coinSuperieurDroit ,true );

    //在三角形之间添加邻居
    triangleFictif1->ajouterVoisin( voisin1TriangleFictif1 );
    triangleFictif1->ajouterVoisin( voisin2TriangleFictif1 );
    triangleFictif1->ajouterVoisin( triangleFictif2 );
    triangleFictif2->ajouterVoisin( voisin1TriangleFictif2 );
    triangleFictif2->ajouterVoisin( voisin2TriangleFictif2 );
    triangleFictif2->ajouterVoisin( triangleFictif1 );

    return std::make_tuple( triangleFictif1 ,triangleFictif2 );
}

//计算三角剖分
void TriangulationDelaunay::calculerTriangulation( Point * nouveauPoint ){
    //第一步
    Triangle * Ti = determinerTriangleContenantNouveauPoint( nouveauPoint );
    //第二步
    vector< Triangle * > * DTL = new vector< Triangle * > ();
    determiner_DTL( nouveauPoint , Ti , DTL );
    vector< Triangle * > NTL = determiner_NTL( nouveauPoint ,DTL );
    supprimerTriangles( DTL );

    //第三步
    for ( size_t i = 0 ; i < NTL.size() ; i ++ )
        DT.push_back( NTL[i] );
    points.push_back( nouveauPoint );
}

//确定DTL
void TriangulationDelaunay::determiner_DTL( const Point * nouveauPoint , Triangle * Ti , vector<Triangle *> * DTL ){
    //第一步
    DTL->push_back( Ti );
    //第二步
    for ( Triangle * triangle : Ti->getVoisins() ){
        if ( Ti->getVoisins().size() > 0 && triangle != NULL && triangle->getVoisins().size() > 0 && triangle->appartient( DTL ) == false )
            if ( Outils::appartientACercle( nouveauPoint , &triangle->getCercle() ) )
                determiner_DTL( nouveauPoint , triangle , DTL );   //递归调用
    }
}

//确定NTL
vector< Triangle * > TriangulationDelaunay::determiner_NTL( Point * nouveauPoint , vector<Triangle *> * DTL ){
    vector< Triangle * > NTL;

    for ( Triangle * triangle : * DTL ){
        for ( Triangle * triangleVoisin : triangle->getVoisins() ){
            if ( triangleVoisin->isNull() ){
                //用新的顶点Point和边 kij（三角形Ti和Tij共同的边）创建一个新的三角形Tl
                vector< Point * > areteCommune = triangle->getAreteCommune( triangleVoisin );
                Triangle * T1 = new Triangle( nouveauPoint , areteCommune[0] , areteCommune[1] );
                T1->ajouterVoisin( triangleVoisin );
                NTL.push_back( T1 );
            }
            else if ( !triangleVoisin->appartient( DTL ) ){
                //创建具有新顶点和边线的三角形T1
                vector< Point * > areteCommune = triangle->getAreteCommune( triangleVoisin );
                Triangle * T1 = new Triangle( nouveauPoint , areteCommune[0] , areteCommune[1] );
                //建立Tl与Tij之间的邻接关系
                T1->ajouterVoisin( triangleVoisin );
                triangleVoisin->supprimerVoisin( triangle );
                triangleVoisin->ajouterVoisin( T1 );
                //将Tl添加到NTL列表
                NTL.push_back( T1 );
            }
        }
        vector< Point * > areteCommune;
        for ( Triangle * Tk : NTL ){
            for ( Triangle * T1 : NTL ){
                if ( Tk != T1 ){
                    //更新Tl和Tk之间是否存在邻接关系
                    if ( Tk->ontUneAreteCommune( T1 ) ){
                        T1->ajouterVoisin( Tk );
                        Tk->ajouterVoisin( T1 );
                    }
                }
            }
        }
    }
    return NTL;
}

//确定包含新顶点的三角形
Triangle * TriangulationDelaunay::determinerTriangleContenantNouveauPoint( const Point * point ){
    bool TriangleTrouve = false;
    int taille = DT.size() , i = 0;
    while ( !TriangleTrouve && i < taille ){
        if ( Outils::pointEstDansTriangle( point , DT[i] ) )
            TriangleTrouve = true;
        else
            i ++;
    }
    return DT[i];
}

//删除三角形
void TriangulationDelaunay::supprimerTriangles( vector<Triangle *> * DTL ){
    int indice;
    for ( size_t i = 0 ; i < DTL->size() ; i ++ ){
        if ( ( indice = indiceTriangleDansDT( DTL->at(i) ) ) != -1 ){
            DT[indice]->seSupprimerDeSesVoisins();
            DT.erase( DT.begin() + indice );
        }
    }
}

//DT中的三角形索引
int TriangulationDelaunay::indiceTriangleDansDT( Triangle * triangle ) const{
    bool TriangleTrouver = false;
    int taille = DT.size() , i = 0;

    while ( !TriangleTrouver && i < taille ){
        if ( DT[i] == triangle ){
            TriangleTrouver = true;
            return i;
        }
        else
            i ++;
    }
    return -1;
}

//获取三角剖分
vector< Triangle * > TriangulationDelaunay::getTriangulation(){
    vector< Triangle * > trianglesFinaux;       //最终三角形
    for ( size_t i = 0 ; i < this->DT.size() ; i ++ )
        if ( !this->DT[i]->contientPoint( this->coinInferieurDroit )
          && !this->DT[i]->contientPoint( this->coinInferieurGauche )
          && !this->DT[i]->contientPoint( this->coinSuperieurDroit )
          && !this->DT[i]->contientPoint( this->coinSuperieurGauche ) )
            trianglesFinaux.push_back( this->DT[i] );
        else
            this->DT[i]->setNull( true );
    return trianglesFinaux;
}

//获取DT
const vector< Triangle * > & TriangulationDelaunay::getDT() const{
    return this->DT;
}

//获取点
const vector< Point * > & TriangulationDelaunay::getPoints() const{
    return this->points;
}
