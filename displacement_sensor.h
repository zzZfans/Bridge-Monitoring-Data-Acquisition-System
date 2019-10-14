#ifndef DISPLACEMENT_SENSOR_H
#define DISPLACEMENT_SENSOR_H


#include<QTextStream>
#include "sensor.h"

class displacement_sensor : public sensor//位移传感器
{
private:

    QString Initial_value_of_expansion_joint;//伸缩缝初始值

    QString Displacement_monitoring_value;//位移监测值

public:

    displacement_sensor(const QString& name="0",
                        const QString& specifications="0",
                        const QString& model="0",
                        const QString& manufacturer="0",
                        const QString& dateOfManufacture="0",
                        const QString& number="0",
                        const QString& initial_value_of_expansion_joint="0" );

    friend QTextStream  &operator<<(QTextStream &os, const displacement_sensor &sensor);
    friend QTextStream  &operator>>(QTextStream &os,  displacement_sensor &sensor);

    const QString& getDisplacementMonitoringValue() const;

    const QString& getInitial_value_of_expansion_joint() const;

    void set_Displacement_Monitoring_Value(const QString & displacementMonitoringValue);

    void set_Initial_value_of_expansion_joint(const QString & initial_value_of_expansion_joint);

};

#endif // DISPLACEMENT_SENSOR_H
