#ifndef STRAIN_MEASURING_POINT_H
#define STRAIN_MEASURING_POINT_H


#include"measuring_point.h"
#include"strain_sensor.h"

class strain_measuring_point :public measuring_point//应变测点
{

private:

    strain_sensor The_sensor;

    double result;

    QList<QPair<QPair<QString,QString>,QString>> historical_data;

public:

    strain_measuring_point(const QString& name="0",
                           const QString &number="0",
                           const QString &position="0");

    friend QTextStream  &operator<<(QTextStream &os, const strain_measuring_point &point);
    friend QTextStream  &operator>>(QTextStream &os,  strain_measuring_point &point);

    void setTheSensor(const strain_sensor& theSensor);

    QList<QPair<QPair<QString,QString>,QString>> & get_historical_data_list();

    strain_sensor &getTheSensor();

    double getResult();

};

#endif // STRAIN_MEASURING_POINT_H
