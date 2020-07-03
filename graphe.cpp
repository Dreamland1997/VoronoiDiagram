#include "graphe.h"

//默认构造函数的实现
Graphe::Graphe() : listeSommets(NULL) , listeAretes(NULL) , listeFaces(NULL) , prochaineClef() {}

//复制构造函数的实现
Graphe::Graphe( const Graphe & g ) : prochaineClef(g.prochaineClef){
    listeSommets = Element< Sommet * >::copie(g.listeSommets);
    listeAretes = Element< Arete * >::copie(g.listeAretes);
    listeFaces = Element< Face * >::copie(g.listeFaces);
}

//析构函数的实现
Graphe::~Graphe() {}

//顶点
Sommet * Graphe ::creeSommet( const string & nom, Point * position ){
    listeSommets = new Element< Sommet * >( new Sommet( nom , position , prochaineClef++ ) , listeSommets );
    return listeSommets->v;
}

//添加顶点
void Graphe::ajouterSommets( Sommet * s ){
    listeSommets = new Element< Sommet * >( s , listeSommets );
}

//棱
Arete * Graphe::creeArete( Sommet * debut, Sommet * fin, const string & nom ){
    if( Element< Sommet * >::estDans( debut , this->listeSommets ) == -1 )
        throw Erreur( "The start of the edge does not exist in the list of vertices of the graph");
    if( Element< Sommet * >::estDans( fin , this->listeSommets ) == -1 )
        throw Erreur("The end of the edge does not exist in the list of vertices of the graph");
    listeAretes = new Element< Arete * >( new Arete( nom , debut , fin , prochaineClef++ ) , listeAretes );
    return listeAretes->v;
}

//面
Face * Graphe::creeFace( const string & nom ){
    listeFaces = new Element< Face * >( new Face( nom , prochaineClef++ ) , listeFaces );
    return listeFaces->v;
}

//顶点数
int Graphe::nombreSommets() const{
    return Element< Sommet * >::taille( listeSommets );
}

//棱 数
int Graphe::nombreAretes() const{
    return Element< Arete * >::taille( listeAretes );
}

//面 数
int Graphe::nombreFaces() const{
    return Element< Face * >::taille( listeFaces );
}

//获取下一个（索引）
int Graphe::getProchaineClef() const{
    return prochaineClef;
}

//获取顶点的索引
Sommet * Graphe::getSommetParIndice( const int & indice) const{
    if( indice < Element< Sommet * >::taille( listeSommets ) ){
        Element< Sommet * > * l = listeSommets;
        for( int i = 0 ; i <= indice ; i ++ )
            l = l->s;
        return l->v;
    }
    return NULL;
}

//获取棱的顶点
Arete * Graphe::getAreteParSommets( const Sommet * s1, const Sommet * s2 ) const{
    Element< Arete * > * l;
    for( l = this->listeAretes ; l ; l = l->s )
        if( l->v->estEgal( s1 , s2 ) )
            return l->v;
    return NULL;
}

//判断棱之间的点是否存在
bool Graphe::areteEntrePointsExiste( Sommet * s1 , Sommet * s2 ) const{
    Element< Arete * > * l;
    for( l = this->listeAretes ; l ; l = l->s )
        if( l->v->positionsAreteSontEgales( s1 , s2 ) )
            return true;
    return false;
}

//重载字符串的实现
Graphe::operator string() const{
    ostringstream oss;
    oss << "Graphe : " << endl;
    oss << "Sommets : " << endl << Element< Sommet * >::toString( listeSommets , "" , "\n" , "" ) << endl;
    oss << "Aretes : " << endl << Element< Arete * >::toString( listeAretes , "" , "\n" , "" ) << endl;
    oss << "Faces : " << endl << Element< Face * >::toString( listeFaces , "" , "\n" , "" ) << endl;
    return oss.str();
}

//重载=运算符的实现
const Graphe & Graphe::operator = ( const Graphe & ){
    Element< Sommet * >::effacer( listeSommets );
    Element< Arete * >::effacer( listeAretes );
    Element< Face * >::effacer( listeFaces );

    listeSommets = Element< Sommet * >::copie( listeSommets );
    listeAretes = Element< Arete * >::copie( listeAretes );
    listeFaces = Element< Face * >::copie( listeFaces );
    return *this;
}

//获取顶点
Element< Sommet * > * Graphe::getSommets() const{
    return this->listeSommets;
}

//获取棱
Element< Arete * > * Graphe::getAretes() const{
    return this->listeAretes;
}

//获取面
Element< Face * > * Graphe::getFaces() const{
    return this->listeFaces;
}
