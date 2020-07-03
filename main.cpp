#include <QApplication>
#include "application.h"

#include "point.h"
#include "triangulationdelaunay.h"

int main( int argc , char *argv[] )
{
    QApplication Qapp( argc, argv );
    Application app;
    app.show();
    return Qapp.exec();
}
