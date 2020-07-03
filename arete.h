#ifndef ARETE_H
#define ARETE_H

#include "sommet.h"

using namespace std;

//棱 类
class Arete{
    string nom;
    int clef;               //键
    Sommet * extremite1;
    Sommet * extremite2;

public:
    Arete();
    Arete( const string & , Sommet * extremiteA , Sommet * extremiteB , const int & clef );
    Arete( const Arete & );
    virtual ~Arete();

    const string & getNom() const;
    const int & getClef() const;
    Sommet * getExtremite1() const;
    Sommet * getExtremite2() const;

    void setNom( const string & );
    void setClef( const int & );
    void setExtremite1( Sommet * );
    void setExtremite2( Sommet * );

    bool estEgal( const Sommet * s1 , const Sommet * s2 ) const;
    bool positionsAreteSontEgales( Sommet * s1 , Sommet * s2 ) const;

    bool operator == ( const Arete & ) const;
    bool operator != ( const Arete & ) const;
    const Arete & operator = ( const Arete & );
    operator string() const;
    Arete * clone() const;
};

//内联函数 重载<<运算符的实现
inline ostream & operator << ( ostream & f , const Arete & a ){
    return f << ( string )a;
}
#endif // ARETE_H
