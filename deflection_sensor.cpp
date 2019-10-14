#include "deflection_sensor.h"

deflection_sensor::deflection_sensor(const QString& name, const QString& specifications, const QString& model,
                                     const QString& manufacturer, const QString& dateOfManufacture, const QString& number)
    :
      sensor(name, specifications, model, manufacturer, dateOfManufacture, number) {}


QTextStream &operator<<(QTextStream &os, const deflection_sensor &sensor)
{
    os  <<sensor.name<<" "
       <<sensor.specification<<" "
      <<sensor.model<<" "
     <<sensor.manufacturer<<" "
    <<sensor.DateOfManufacture<<" "
    <<sensor.number<<" "
    <<sensor.Bound_state<<endl;

    return os;
}

QTextStream &operator>>(QTextStream &os,  deflection_sensor &sensor)
{
    os    >>sensor.name
            >>sensor.specification
            >>sensor.model
            >>sensor.manufacturer
            >>sensor.DateOfManufacture
            >>sensor.number
            >>sensor.Bound_state;

    return os;
}

const QString &deflection_sensor::getGpsMonitoringValue() const
{
    return GPS_monitoring_value;
}

void deflection_sensor::setGpsMonitoringValue(const QString &gpsMonitoringValue)
{
    GPS_monitoring_value = gpsMonitoringValue;
}
