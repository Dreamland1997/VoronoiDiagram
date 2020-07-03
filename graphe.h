#ifndef GRAPHE_H
#define GRAPHE_H

#include "face.h"

using namespace std;

//画图形类
class Graphe{
    Element< Sommet * > * listeSommets;      //顶点列表
    Element< Arete * > * listeAretes;        //棱列表
    Element< Face * > * listeFaces;          //面列表
    int prochaineClef;                       //下一个键

public:
    Graphe();
    Graphe( const Graphe & );
    virtual ~Graphe();

    Sommet * creeSommet( const string & nom , Point * position );
    void ajouterSommets( Sommet * );
    Arete * creeArete( Sommet * debut , Sommet * fin , const string & nom );
    Face * creeFace( const string & nom );

    int nombreSommets() const;
    int nombreAretes() const;
    int nombreFaces() const;
    int getProchaineClef() const;

    Sommet * getSommetParIndice( const int & indice ) const;
    Arete * getAreteParSommets( const Sommet * s1 , const Sommet * s2 ) const;
    bool areteEntrePointsExiste( Sommet *  , Sommet *  ) const;

    operator string() const;
    const Graphe & operator = ( const Graphe & );

    Element< Sommet * > * getSommets() const;
    Element< Arete * > * getAretes() const;
    Element< Face * > * getFaces() const;
};

//内联函数 重载<<运算符
inline ostream & operator << ( ostream & f , const Graphe & g ){
    return f << ( string )g;
}

#endif // GRAPHE_H
