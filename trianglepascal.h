#ifndef TRIANGLEPASCAL_H
#define TRIANGLEPASCAL_H

#include <iostream>
#include <sstream>

using namespace std;

//Pascal三角形类
class TrianglePascal{
public:
    TrianglePascal( int );
    ~TrianglePascal();
    void creerTrianglePascal();
    int get( const int & , const int & ) const;
    operator string() const;

private:
    const int static TAILLE_MAX = 15;
    int taille;
    int trianglePascal[TAILLE_MAX][TAILLE_MAX];
};

#endif // TRIANGLEPASCAL_H
