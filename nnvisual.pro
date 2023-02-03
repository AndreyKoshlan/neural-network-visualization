QT       += core gui
QT       += 3dcore 3drender 3dinput 3dextras
QT       += quick quick3d

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    model/dataset/datasetreader.cpp \
    model/dataset/datasetreadermnist.cpp \
    model/visualization/neuralnetworkvisual.cpp \
    model/visualization/visuallayer.cpp \
    model/visualization/visualsynapses.cpp \
    qml/controller.cpp \
    qml/instancetable.cpp \
    main.cpp \
    model/dataset/dataset.cpp \
    model/core/layer.cpp \
    model/core/neuralnetwork.cpp \
    model/core/synapses.cpp

HEADERS += \
    model/dataset/datasetmnist.h \
    model/dataset/datasetreader.h \
    model/dataset/datasetreadermnist.h \
    model/visualization/neuralnetworkpreferences.h \
    model/visualization/neuralnetworkvisual.h \
    model/visualization/visuallayer.h \
    model/visualization/visualsynapses.h \
    qml/controller.h \
    qml/instancetable.h \
    model/dataset/dataset.h \
    model/core/layer.h \
    model/core/neuralnetwork.h \
    model/core/synapses.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    qml.qrc
