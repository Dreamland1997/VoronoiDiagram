QT += quick
CONFIG += c++11
CONFIG -= app_bundle
CONFIG += qt
QT += core

QT += widgets

SOURCES += \
        anglecapable.cpp \
        application.cpp \
        arete.cpp \
        bernstein.cpp \
        bezier.cpp \
        carapace.cpp \
        cercle.cpp \
        diagrammevoronoi.cpp \
        equationdroite.cpp \
        equationdroitebase.cpp \
        equationdroiteverticale.cpp \
        face.cpp \
        generateurcarapace.cpp \
        generateurcarapacealea.cpp \
        generateurcarapaceparfaite.cpp \
        graphe.cpp \
        main.cpp \
        outils.cpp \
        point.cpp \
        segment.cpp \
        sommet.cpp \
        triangle.cpp \
        trianglepascal.cpp \
        triangulationdelaunay.cpp

RESOURCES += qml.qrc

HEADERS += \
    anglecapable.h \
    application.h \
    arete.h \
    bernstein.h \
    bezier.h \
    carapace.h \
    cercle.h \
    diagrammevoronoi.h \
    element.h \
    equationdroite.h \
    equationdroitebase.h \
    equationdroiteverticale.h \
    erreur.h \
    face.h \
    generateurcarapace.h \
    generateurcarapacealea.h \
    generateurcarapaceparfaite.h \
    graphe.h \
    listecirculaire.h \
    outils.h \
    point.h \
    segment.h \
    sommet.h \
    triangle.h \
    trianglepascal.h \
    triangulationdelaunay.h \
    vecteur2d.h
