#ifndef ERREUR_H
#define ERREUR_H

#include <iostream>
#include <string>
#include <exception>

using namespace std;

//异常误差类
class Erreur : public exception{
public:
    string message;

    //默认构造函数实现
    Erreur() : message("Erreur !") {}

    //构造函数实现
    Erreur( const string & messageErreur ) : Erreur() { this->message += " " + messageErreur ; }

    Erreur( const char * messageErreur ) : Erreur( ( string )messageErreur ) {}

    //模板(相等测试) 测试a == b 如果a != b 那是一个异常
    template< class T >
    inline static void testeEgalite( const T & a , const T & b , const char * message );

    //模板（不等测试）测试a != b 如果a == b 那是一个异常
    template< class T >
    inline static void testeNonEgalite( const T & a , const T & b , const char * message );

    //模板（ <= 测试 ） 测试a <= b 如果a > b 那是一个异常
    template< class T >
    inline static void testePlusPetitOuEgal( const T & a , const T & b , const char * message );

    //模板（x的范围测试） 测试x是否在【a , b】中 如果不在 那是一个异常
    template< class T >
    inline static void testeAppartient( const T & a , const T & x , const T & b , const char * message );

    //模板（void 返回值测试）
    inline static void testeNonVide( const void *d , const char * message );

    //重载字符串运算符
    operator string() const { return this->message ; }
};

//内联函数：重载 << 运算符 通用输出流
inline ostream & operator << ( ostream & os , const Erreur & erreur ){
    os << ( string )erreur;
    return os;
}

//模板(相等测试) 测试a == b 如果a != b 那是一个异常的实现
template< class T >
inline void Erreur::testeEgalite( const T & a , const T & b , const char * message ){
#ifdef DEBUG
    if( a != b ) throw Erreur( message );
#endif
}

//模板（不等测试）测试a != b 如果a == b 那是一个异常的实现
template< class T >
inline void Erreur::testeNonEgalite( const T & a , const T & b ,const char * message ){
#ifdef DEBUG
    if( a == b ) throw Erreur( message );
#endif
}

//模板（ <= 测试 ） 测试a <= b 如果a > b 那是一个异常的实现
template< class T >
inline void Erreur::testePlusPetitOuEgal( const T & a , const T & b , const char * message ){
#ifdef DEBUG
    if( a > b ) { throw Erreur( message ); }
#endif
}

//模板（x的范围测试） 测试x是否在【a , b】中 如果不在 那是一个异常
template< class T >
inline void Erreur::testeAppartient( const T & a , const T & x , const T & b , const char * message ){
    Erreur::testePlusPetitOuEgal<T>( a , x , message );
    Erreur::testePlusPetitOuEgal<T>( x , b , message );
}

//模板（void 返回值测试）的实现
inline void Erreur::testeNonVide( const void *d, const char *message ){
    if( !d ) throw Erreur( message );
}

#endif // ERREUR_H
