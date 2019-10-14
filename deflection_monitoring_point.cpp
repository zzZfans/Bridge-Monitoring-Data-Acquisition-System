#include "deflection_monitoring_point.h"

deflection_monitoring_point::deflection_monitoring_point(const QString& name,
                                                         const QString &number,
                                                         const QString &position,
                                                         const QString &baselineMonitoringValue)
    : measuring_point(name,number, position),Baseline_monitoring_value(baselineMonitoringValue)
{}

QTextStream &operator<<(QTextStream &os, const deflection_monitoring_point &point)
{
    os  <<point.name<<" "
       <<point.number<<" "
      <<point.position<<" "
     <<point.Bound_sensor<<" "
    <<point.Baseline_monitoring_value<<" "
    <<point.The_sensor.getName()<<" "
    <<point.The_sensor.getSpecifications()<<" "
    <<point.The_sensor.getModel()<<" "
    <<point.The_sensor.getManufacturer()<<" "
    <<point.The_sensor.getDateOfManufacture()<<" "
    <<point.The_sensor.getNumber()<<" "
    <<point.The_sensor.is_bound()<<endl;

    return os;
}


QTextStream &operator>>(QTextStream &os,  deflection_monitoring_point &point)
{
    QString   name,   specifications,   model,   manufacturer,
            dateOfManufacture,   number;

    int is_bound_point;

    os  >>point.name
            >>point.number
            >>point.position
            >>point.Bound_sensor
            >>point.Baseline_monitoring_value
            >>name
            >>specifications
            >>   model
            >>manufacturer
            >>dateOfManufacture
            >>  number
            >>is_bound_point;

    point.The_sensor.setName(name);
    point.The_sensor.setSpecifications(specifications);
    point.The_sensor.setModel(model);
    point.The_sensor.setManufacturer(manufacturer);
    point.The_sensor.setDateOfManufacture(dateOfManufacture);
    point.The_sensor.setNumber(number);
    point.The_sensor.set_bound_state(is_bound_point);

    return os;
}

double deflection_monitoring_point::getResult()
{
    result = The_sensor.getGpsMonitoringValue().toDouble() - Baseline_monitoring_value.toDouble();

    return result;
}

void deflection_monitoring_point::setTheSensor(const deflection_sensor &theSensor)
{
    The_sensor = theSensor;

    Bound_sensor=1;

    The_sensor.set_bound_state(1);
}

deflection_sensor &deflection_monitoring_point::getTheSensor()
{
    return The_sensor;
}

void deflection_monitoring_point::setBaselineMonitoringValue(const QString & baselineMonitoringValue)
{
    Baseline_monitoring_value = baselineMonitoringValue;
}

QList<QPair<QPair<QString, QString>, QPair<QString, QString> > > &deflection_monitoring_point::get_historical_data_list()
{
    return historical_data;
}
