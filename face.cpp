#include "face.h"

//默认构造函数的实现
Face::Face() : nom("") , clef(0) , listeAretes(NULL) {}

//构造函数的实现
Face::Face( const string & n , const int & c ) : nom(n) , clef(c) , listeAretes(NULL) {}

//复制构造函数的实现
Face::Face( const Face & f ) : nom(f.nom) , clef(f.clef) , listeAretes(NULL){
    listeAretes = Element< Arete * >::copie( f.listeAretes );
}

//析构函数的实现
Face::~Face(){
    Element< Arete * >::effacer( listeAretes );
}

//获取Arete的实现
Arete * Face::getArete( const int & indice ) const{
    Element< Arete * > * l = listeAretes;
    for( int i = 0 ; i == indice ; i ++ ){
        Element< Arete * >::depiler( l );
    }
    return l->v;
}

//获取Nom的实现
const string & Face::getNom() const{
    return nom;
}

//获取Clef的实现
int Face::getClef() const{
    return clef;
}

//获取大小的实现
int Face::nombreAretes() const{
    return tailleCirculaire(listeAretes);
}

//获取索引
int Face::getIndiceArete( Arete * a ) const{
    return Element< Arete * >::estDans( a , listeAretes );
}

//添加棱
void Face::ajouterArete( Arete * a ){
    if( listeAretes == NULL ){
        listeAretes = new Element< Arete * >( a , listeAretes );
    }
    else{
        listeAretes = new Element< Arete * >( a , listeAretes );
    }
}

//设置Nom的实现
void Face::setNom( const string & n ){
    nom = n;
}

//设置Clef的实现
void Face::setClef( const int & c ){
    clef = c;
}

//撤销Arete
void Face::supprimerArete( Arete * a ){
    Element< Arete * >::retirer( a , listeAretes );
}

//重载字符串的实现
Face::operator string() const{
    ostringstream oss;
    oss << "Face" << endl;
    oss << "[" << endl;
    oss << "Nom : " << nom << ", Clef : " << clef << endl;
    oss << "Aretes : " << endl << toStringCirculaire( listeAretes , "" , "\n" , "" );
    oss << "]";
    return oss.str();
}

//重载==运算符的判断实现
bool Face::operator == ( const Face & face ) const{
    bool egaux = ( nom == face.nom ) && ( clef == face.clef );
    int taille = nombreAretes();
    Element< Arete * > * l = listeAretes;
    for( int i = 0 ; i < taille ; i ++ ){
        if( l->v != face.listeAretes->v ){
            return false;
        }
        else
            l = l->s;
    }
    return egaux;
}

//重载!=运算符的判断实现
bool Face::operator != ( const Face & face ) const{
    return !( *this == face );
}

//重载=运算符的实现
const Face & Face::operator = ( const Face & face ){
    if( * this != face ){
        nom = face.nom;
        clef = face.clef;
        Element< Arete * > * l;
        for( l = face.listeAretes ; l != NULL ; l = l->s ){
            listeAretes = new Element< Arete * > ( l->v , listeAretes );
        }
    }
    return *this;
}

//获取Aretes的实现
Element< Arete * > * Face::getAretes() const{
    return this->listeAretes;
}
