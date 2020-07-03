#include "bernstein.h"

//4个参数 第一 double  第二 int  第三 int  第四 TrianglePascal &tp
double Bernstein::bernstein( const double & t , const int & i , const int & m , const TrianglePascal & tp ){
    return tp.get( m , i ) * pow( ( 1 - t ) , ( m - i ) ) * pow( t , i );
}
