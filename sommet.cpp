#include "sommet.h"

//4个参数 默认构造函数的实现 int string Point int
Sommet::Sommet() : clef(0) , nom("") , position() , degre(0) {}

//构造函数的实现
Sommet::Sommet( const string & nom , Point * position , const int & clef ) :
    clef(clef) , nom(nom) , position(position) , degre(0) {}

//复制构造函数的实现
Sommet::Sommet( const Sommet & s ) : clef(s.clef) , nom(s.nom) , position(s.position) , degre(s.degre) {}

//析构函数的实现
Sommet::~Sommet() {}

//获取Nom（大小）函数的实现
const string & Sommet::getNom() const{
    return nom;
}

//获取Position（位置）函数的实现
Point * Sommet::getPosition() const{
    return position;
}

//获取Degre（名称）函数的实现
const int & Sommet::getDegre() const{
    return degre;
}

//获取Clef（）函数的实现
const int & Sommet::getClef() const{
    return clef;
}

//设置Nom（）函数的实现
void Sommet::setNom( const string & n ){
    nom = n;
}

//设置Position（）函数的实现
void Sommet::setPosition( Point * p ){
    position = p;
}

//设置Degre（）函数的实现
void Sommet::setDegre( const int & d ){
    degre = d;
}

//设置Cleft（）函数的实现
void Sommet::setClef( const int & c ){
    clef = c;
}

//重载== !=  = string()运算符的实现
bool Sommet::operator == ( const Sommet & s ) const{
    return nom == s.nom && clef == s.clef && position == s.position && degre == s.degre;
}

bool Sommet::operator != ( const Sommet & s) const{
    return !( *this == s );
}

const Sommet & Sommet::operator = ( const Sommet & s ){
    if( this != &s ){
        nom = s.nom;
        clef = s.clef;
        position = s.position;
        degre = s.degre;
    }
    return *this;
}

Sommet::operator string() const{
    ostringstream oss;
    oss << "Sommet[" << "Nom : " << nom << ", clef : " << clef << ", position : " << position << ", Degre : " << degre << "]";
    return oss.str();
}

//克隆函数的实现
Sommet * Sommet::clone() const{
    return new Sommet( * this );
}
