#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include "cercle.h"
#include "equationdroiteverticale.h"
#include "outils.h"
#include "vecteur2d.h"

using namespace std;

//三角形类
class Triangle{
private:
    vector< Triangle * > voisins;         //三角形的三个邻接点
    vector< Point * > lesTroisPoints;     //三点
    Cercle cercleCirconscrit;             //外接圆
    bool null;
public:
    Triangle();
    Triangle( Point * , Point * , Point * );
    Triangle( Point * , Point * , Point * , bool );
    ~Triangle();

    int getNbVoisins() const;
    void ajouterVoisin( Triangle * );
    void supprimerVoisin( Triangle * );
    bool contientPoint( Point * ) const;

    void setVoisin( int , Triangle * );
    Point * getPoint( int ) const;
    vector< Point * > getAreteCommune( const Triangle * ) const;
    bool ontUneAreteCommune( const Triangle * );
    bool appartient( vector< Triangle * > * ) const;

    bool operator == ( const Triangle & ) const;
    operator string() const;
    vector< Point * > mettreDansSensTrigo( vector< Point * > );
    bool operator != ( const Triangle & ) const;

    void calculerCercleCirconscrit();
    void seSupprimerDeSesVoisins();

    const vector< Triangle * > & getVoisins() const;
    const vector< Point * > & getLesTroisPoints() const;
    const Cercle & getCercle() const;

    bool isNull() const;
    void setCercle( const Cercle & );
    void setNull( const bool & );
    bool estVoisinAvec( Triangle * ) const;

    vector< vector < Point * > > getAretesSansVoisin() const;
};

//内联函数 重载<< 运算符 通用输出流
inline ostream & operator << ( ostream & f , const Triangle & t ){
    return f << ( string )t;
}

#endif // TRIANGLE_H
