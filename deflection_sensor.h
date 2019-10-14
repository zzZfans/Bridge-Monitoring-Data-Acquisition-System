#ifndef DEFLECTION_SENSOR_H
#define DEFLECTION_SENSOR_H


#include<QTextStream>
#include "sensor.h"

class deflection_sensor : public sensor//挠度传感器
{
private:

    QString GPS_monitoring_value;//GPS监测值

public:
    deflection_sensor(const QString& name="0",
                      const QString& specifications="0",
                      const QString& model="0",
                      const QString& manufacturer="0",
                      const QString& dateOfManufacture="0",
                      const QString& number="0");

    friend QTextStream  &operator<<(QTextStream &os, const deflection_sensor &sensor);
    friend QTextStream  &operator>>(QTextStream &os,  deflection_sensor &sensor);

    const QString& getGpsMonitoringValue() const;

    void setGpsMonitoringValue(const QString & gpsMonitoringValue);

};

#endif // DEFLECTION_SENSOR_H
