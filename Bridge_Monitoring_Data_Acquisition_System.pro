#-------------------------------------------------
#
# Project created by QtCreator 2019-05-31T00:05:29
#
#-------------------------------------------------

QT       += core gui
QT += charts

RC_FILE = exe_icon.rc

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bridge_Monitoring_Data_Acquisition_System
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        add_point_dialog.cpp \
        add_sensor_dialog.cpp \
        deflection_monitoring_point.cpp \
        deflection_sensor.cpp \
        displacement_monitoring_point.cpp \
        displacement_sensor.cpp \
        login_dialog.cpp \
        main.cpp \
        main_widget.cpp \
        measuring_point.cpp \
        modify_point_dialog.cpp \
        modify_sensor_dialog.cpp \
        sensor.cpp \
        sensor_information_widget.cpp \
        sensor_selection_dialog.cpp \
        strain_measuring_point.cpp \
        strain_sensor.cpp \
        view_of_monitoring_point_information_widget.cpp

HEADERS += \
        add_point_dialog.h \
        add_sensor_dialog.h \
        deflection_monitoring_point.h \
        deflection_sensor.h \
        displacement_monitoring_point.h \
        displacement_sensor.h \
        login_dialog.h \
        main_widget.h \
        measuring_point.h \
        modify_point_dialog.h \
        modify_sensor_dialog.h \
        sensor.h \
        sensor_information_widget.h \
        sensor_selection_dialog.h \
        strain_measuring_point.h \
        strain_sensor.h \
        view_of_monitoring_point_information_widget.h

FORMS += \
        add_point_dialog.ui \
        add_sensor_dialog.ui \
        login_dialog.ui \
        main_widget.ui \
        modify_point_dialog.ui \
        modify_sensor_dialog.ui \
        sensor_information_widget.ui \
        sensor_selection_dialog.ui \
        view_of_monitoring_point_information_widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
