#include "trianglepascal.h"

//构造函数的实现
TrianglePascal::TrianglePascal( int taille ) : taille(taille) {
    creerTrianglePascal();
}

//析构函数的实现
TrianglePascal::~TrianglePascal() {}

//Pascal三角形函数的实现
void TrianglePascal::creerTrianglePascal(){
    for( int i = 0 ; i <= this->taille ; i ++ ){
        //对角线是1
        this->trianglePascal[i][i] = 1;
        //第一列是1
        this->trianglePascal[i][0] = 1;
        //其他情况下的数值
        for( int j = 1 ; j < i ; j ++ ){
            this->trianglePascal[i][j] = this->trianglePascal[i - 1][j] + this->trianglePascal[i - 1][j - 1];
        }
    }
}

//获取Pascal三角形的值
int TrianglePascal::get( const int & ligne , const int & colonne ) const{
    if( ligne <= this->taille && colonne <= this->taille )
        return this->trianglePascal[ligne][colonne];
    return 0;
}

//重载字符串运算符的实现
TrianglePascal::operator string() const{
    ostringstream oss;
    for( int i = 0 ; i <= taille ; i ++ ){
        for( int j = 0 ; j <= i ; j ++ )
            if( this->trianglePascal[i][j] )
                oss << this->trianglePascal[i][j] << " ";
        oss << endl;
    }
    return oss.str();
}
