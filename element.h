#ifndef ELEMENT_H
#define ELEMENT_H

#include <iostream>
#include <string>
#include <sstream>
#include "erreur.h"

using namespace std;

//数据类模板
template< class T >
class Element{
public:
    //v用于存放任意类型的数据
    T v;

    //类的对象s
    Element<T> *s;

    //构造函数初始化
    Element( const T & v , Element<T> * s ) : v(v) , s(s) {}

    //静态成员（大小）函数
    static int taille( const Element<T> * l );

    //静态函数成员
    static const string toString( const Element<T> *p , const char * debut = "(" , const char * separateur = ", " , const char * fin = ")" );

    static Element<T> * copie( const Element<T> * l );

    template< class FONCTEUR >
    static Element<T> * appartient( Element<T> * l , const FONCTEUR & condition );

    template< class FONCTEUR >
    static void insertionEnOrdre( const T & a , Element<T> * & l , const FONCTEUR & estPlusPetitOuEgal );

    static T depiler( Element<T> * & l );

    static void retirer( const T a , Element<T> * l );

    static void effacer( Element<T> * & l );

    static int estDans( const T v , const Element<T> * l );

    static Element<T> * dernier( Element<T> * l );

    friend ostream & operator << ( ostream & os , const Element<T> * p ){
        return os << Element<T>::toString(p);
    }
};

template < class T >
T Element<T>::depiler( Element<T> * & l ){
    if( l == NULL )
        throw  Erreur("Unable to depilate, the list is empty");
    T temp = l->v;
    Element<T> * r = l;
    l = l->s;
    delete r;
    return temp;
}

//回收操作
template< class T >
void Element<T>::retirer( const T a , Element<T> * l){
    if( l == NULL )
        throw Erreur("Unable to depilate, the list is empty");
    if( l->v == a ){
        Element<T> * r = l;
        l = l->s;
        delete r;
    }
    else
        Element::retirer( a , l->s );
}

//类模板 删除操作
template< class T >
void Element<T>::effacer( Element<T> * & l ){
    if( l != NULL ){
        Element::effacer( l->s );
        delete l->v;
        delete l;
        l = NULL;
    }
}

template< class T >
int Element<T>::taille( const Element<T> * l ){
    if( !l ) return 0;
    else
        return 1 + Element<T>::taille( l->s );
}

template< class T >
const string Element<T>::toString( const Element<T> * p , const char * debut , const char * separateur , const char * fin ){
    ostringstream o;
    for( o << debut ; p ; p = p->s ) o << *p->v << separateur;
    o << fin;
    return o.str();
}

//类模板 拷贝操作
template< class T >
Element<T> * Element<T>::copie( const Element<T> * l ){
    if( !l )
        return NULL;
    else
        return new Element<T>( l->v , Element<T>::copie( l->s ) );
}

template< class T >
int Element<T>::estDans( const T v , const Element<T> * l ){
    if( l == NULL )
        return -1;
    else if ( v == l->v)
        return 0;
    return 1 + Element::estDans( v , l->s );
}

template< class T >
template< class FONCTEUR >
Element<T> * Element <T>::appartient( Element<T> * l , const FONCTEUR & condition ){
    for( ; l ; l = l->s )
        if( condition ( l->v ) )
            return l;
    return l;
}

//按顺序插入
template <class T >
template< class FONCTEUR >
void Element<T>::insertionEnOrdre( const T & a , Element<T> * & l , const FONCTEUR & estPlusPetitOuEgal ){
    if( !l || estPlusPetitOuEgal( a , l->v ) ) l = new Element<T>( a , l );
    else insertionEnOrdre( a , l->s , estPlusPetitOuEgal );
}

//最新列表
template< class T >
Element<T> * Element<T>::dernier( Element<T> * l ){
    Element<T> *p;
    if( l == NULL )
        throw Erreur("the last element of an empty list does not exist");
    for( p = l ; p->s ; p = p->s );
    return p;
}

#endif // ELEMENT_H
