#ifndef LISTECIRCULAIRE_H
#define LISTECIRCULAIRE_H

#include <string>
#include <sstream>
#include "element.h"

using namespace std;

//类模板(线段到循环)
template< class T >
void lineaireToCirculaire( Element<T> * l ){
    Element<T> *d = Element<T>::dernier(l);
    d->s = l;
}

//类模板（循环到线段）
template< class T >
void circulaireToLineaire( Element<T> * l ){
    Element<T> *d;
    d = l;
    while ( d->s != l ) d = d->s;
    d->s = NULL;
}

//字符串循环
template< class T >
const string toStringCirculaire( const Element<T> * p , const char * debut = "(" , const char * separateur = ", " , const char * fin = ")" ){
    circulaireToLineaire( ( Element<T> * ) p );
    string s = Element<T>::toString( p , debut , separateur , fin );
    lineaireToCirculaire( ( Element<T> * ) p );
    return s;
}

//大小循环
template< class T >
int tailleCirculaire( const Element<T> * p ){
    int i;
    const Element<T> * r;
    i = 0 ; r = p;
    do{

        ++ i ;
        r = r->s;
    }while ( r != p );
    return i;
}

//三角形
template< class T >
Element<T> * creeTriangle( const T & A , const T & B , const T & C ){
    Element<T> * p , * d;
    d = p = new Element<T>( C , NULL );
    p = new Element<T>( B , p );
    p = new Element<T>( A , p );
    d->s = p;
    return p;
}

#endif // LISTECIRCULAIRE_H
