#ifndef DEFLECTION_MONITORING_POINT_H
#define DEFLECTION_MONITORING_POINT_H


#include<QTextStream>
#include"measuring_point.h"
#include"deflection_sensor.h"

class deflection_monitoring_point :public measuring_point//挠度测点
{
private:

    deflection_sensor The_sensor;

    QString Baseline_monitoring_value;//基准点监测值

    double result;

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>historical_data;

public:
    deflection_monitoring_point(const QString& name="0",
                                const QString &number="0",
                                const QString &position="0",
                                const QString &baselineMonitoringValue="0");

    friend QTextStream  &operator<<(QTextStream &os, const deflection_monitoring_point &point);
    friend QTextStream  &operator>>(QTextStream &os,  deflection_monitoring_point &point);

    double getResult() ;

    void setTheSensor(const deflection_sensor& theSensor);

    deflection_sensor &getTheSensor();

    void setBaselineMonitoringValue(const QString & baselineMonitoringValue);

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>& get_historical_data_list();
};

#endif // DEFLECTION_MONITORING_POINT_H
