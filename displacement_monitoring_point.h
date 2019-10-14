#ifndef DISPLACEMENT_MONITORING_POINT_H
#define DISPLACEMENT_MONITORING_POINT_H


#include<QTextStream>
#include"displacement_sensor.h"
#include"measuring_point.h"

class displacement_monitoring_point :public measuring_point//位移测点
{
private:

    displacement_sensor The_sensor;

    double result;

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>historical_data;

public:
    displacement_monitoring_point(const QString& name="0",
                                  const QString &number="0",
                                  const QString &position="0");

    friend QTextStream  &operator<<(QTextStream &os, const displacement_monitoring_point &point);
    friend QTextStream  &operator>>(QTextStream &os,  displacement_monitoring_point &point);

    double getResult() ;

    void setTheSensor(const displacement_sensor& theSensor);

    displacement_sensor &getTheSensor() ;

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>& get_historical_data_list();

};

#endif // DISPLACEMENT_MONITORING_POINT_H
