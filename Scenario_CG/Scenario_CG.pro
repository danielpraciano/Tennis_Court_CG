#-------------------------------------------------
#
# Project created by QtCreator 2017-10-21T14:34:54
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Scenario_CG
TEMPLATE = app

CONFIG += c++11
QMAKE_CXX = /usr/local/bin/g++-7
QMAKE_LINK = /usr/local/bin/g++-7
QMAKE_CXXFLAGS += -std=c++11

#QMAKE_CXXFLAGS+= -openmp -fopenmp -DARMA_DONT_USE_WRAPPER -lopenblas -llapack -lglut -lGL -lGLU -lm
QMAKE_CXXFLAGS+= -O3 -fopenmp -DARMA_DONT_USE_WRAPPER
#QMAKE_LFLAGS +=  -openmp
LIBS += -fopenmp -framework Accelerate -framework OpenGL -framework GLUT
INCLUDEPATH += /usr/local/Cellar/armadillo/8.300.1/include/
LIBS += -L/usr/local/Cellar/armadillo/8.300.1/lib/ -larmadillo

#INCLUDEPATH += /usr/local/Cellar/boost/1.65.1/include/
#LIBS += -L/usr/local/Cellar/boost/1.65.1/lib/ -lboost_system

#INCLUDEPATH += /usr/local/Cellar/jpeg/9b/include/
#LIBS += -L/usr/local/Cellar/jpeg/9b/lib/ -ljpeg
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#LIBS += -DARMA_DONT_USE_WRAPPER -lopenblas -llapack\
#LIBS += -larmadillo -lopenblas -llapack\
#        -lglut -lGL -lGLU -lm

#SOURCES += main.cpp\
#        mainwindow.cpp

#HEADERS  += mainwindow.h

#FORMS    += mainwindow.ui
#
SOURCES = $$files(*.cpp, true)
HEADERS = $$files(*.h  , true)
FORMS   = $$files(*.ui , true)
