#include "arete.h"

//默认构造函数的实现
Arete::Arete() : nom( "" ) , clef(0) , extremite1( NULL ) , extremite2( NULL ) {}

//构造函数的实现
Arete::Arete( const string & n , Sommet * extremiteA , Sommet * extremiteB , const int & c ) :
    nom(n) , extremite1(extremiteA) , extremite2(extremiteB) , clef(c){
    extremite1->setDegre( extremite1->getDegre() + 1 );
    extremite2->setDegre( extremite2->getDegre() + 1 );
}

//复制构造函数的实现
Arete::Arete( const Arete & a ) : nom(a.nom) , clef(a.clef) , extremite1(a.extremite1) , extremite2(a.extremite2) {}

//析构函数的实现
Arete::~Arete(){
    extremite1->setDegre( extremite1->getDegre() - 1 );
    extremite2->setDegre( extremite2->getDegre() - 1 );
}

//获取Nom的实现
const string & Arete::getNom() const{
    return nom;
}

//获取Clef的实现
const int & Arete::getClef() const{
    return clef;
}

//获取Extremite1（极点 极边）的实现
Sommet * Arete::getExtremite1() const{
    return extremite1;
}

//获取Extremite2的实现
Sommet * Arete::getExtremite2() const{
    return extremite2;
}

//设置Nom的实现
void Arete::setNom( const string & n ){
    nom = n;
}

//设置Clef的实现
void Arete::setClef( const int & c ){
    clef = c;
}

//设置Extremite1(极点 极边)的实现
void  Arete::setExtremite1( Sommet * s ){
    extremite1 = s;
}

//设置Extremite2的实现
void Arete::setExtremite2( Sommet * s ){
    extremite2 = s;
}

//判断是否相等的实现
bool Arete::estEgal( const Sommet * s1, const Sommet * s2 ) const{
    return ( s1 == extremite1 && s2 == extremite2 ) || ( s1 == extremite2 && s2 == extremite2 );
}

//判断棱的位置是否相等
bool Arete::positionsAreteSontEgales( Sommet * s1, Sommet * s2 ) const{
    return ( s1->getPosition() == this->extremite1->getPosition() && s2->getPosition() == this->extremite2->getPosition() ) ||
           ( s1->getPosition() == this->extremite2->getPosition() && s2->getPosition() == this->extremite1->getPosition() );
}

//重载==运算符的判断
bool Arete::operator == ( const Arete & objet ) const{
    return estEgal( objet.extremite1 , objet.extremite2 )
            && nom == objet.nom && clef == objet.clef;
}

//重载!=运算符的判断
bool Arete::operator != ( const Arete & a ) const{
    return !( *this == a );
}

//重载=运算符的实现
const Arete & Arete::operator = ( const Arete & a ){
    if( *this != a ){
        nom = a.nom;
        clef = a.clef;
        extremite1 = a.extremite1;
        extremite2 = a.extremite2;
    }
    return *this;
}

//重载字符串运算符的实现
Arete::operator string() const{
    ostringstream oss;
    oss << "Arc[" << "Nom : " << nom << ", clef : " << clef << ", extremite 1 : " << extremite1->getNom() << ", extremite 2 : " << extremite2->getNom() << "]";
    return oss.str();
}

//复制函数的实现
Arete * Arete::clone() const{
    return new Arete( *this );
}

