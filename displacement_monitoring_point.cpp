#include "displacement_monitoring_point.h"

displacement_monitoring_point::displacement_monitoring_point(const QString& name,
                                                             const QString &number,
                                                             const QString &position ) :
    measuring_point(name,
                    number,
                    position ) {}

QTextStream &operator<<(QTextStream &os, const displacement_monitoring_point &point)
{
    os  <<point.name<<" "
       <<point.number<<" "
      <<point.position<<" "
     <<point.Bound_sensor<<" "
    <<point.The_sensor.getName()<<" "
    <<point.The_sensor.getSpecifications()<<" "
    <<point.The_sensor.getModel()<<" "
    <<point.The_sensor.getManufacturer()<<" "
    <<point.The_sensor.getDateOfManufacture()<<" "
    <<point.The_sensor.getNumber()<<" "
    <<point.The_sensor.is_bound()<<endl;

    return os;
}

QTextStream &operator>>(QTextStream &os,  displacement_monitoring_point &point)
{
    QString   name,   specifications,   model,   manufacturer,
            dateOfManufacture,   number, centralWavelength;

    int is_bound_point;

    os  >>point.name
            >>point.number
            >>point.position
            >>point.Bound_sensor
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

double displacement_monitoring_point::getResult()
{
    result = The_sensor.getDisplacementMonitoringValue().toDouble() - The_sensor.getInitial_value_of_expansion_joint().toDouble();

    return result;
}

void displacement_monitoring_point::setTheSensor(const displacement_sensor &theSensor)
{
    The_sensor = theSensor;

    Bound_sensor=1;

    The_sensor.set_bound_state(1);
}

displacement_sensor &displacement_monitoring_point::getTheSensor()
{
    return The_sensor;
}

QList<QPair<QPair<QString, QString>, QPair<QString, QString> > > &displacement_monitoring_point::get_historical_data_list()
{
    return  historical_data;
}
