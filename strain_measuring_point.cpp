#include "strain_measuring_point.h"

strain_measuring_point::strain_measuring_point(const QString& name,
                                               const QString &number,
                                               const QString &position ) :
    measuring_point(name,
                    number,
                    position ) {}


QTextStream &operator<<(QTextStream &os, const strain_measuring_point &point)
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
    <<point.The_sensor.is_bound()<<" "
    <<point.The_sensor.getCentralWavelength()<<endl;

    return os;
}


QTextStream &operator>>(QTextStream &os,  strain_measuring_point &point)
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
            >>is_bound_point
            >> centralWavelength;

    point.The_sensor.setName(name);
    point.The_sensor.setSpecifications(specifications);
    point.The_sensor.setModel(model);
    point.The_sensor.setManufacturer(manufacturer);
    point.The_sensor.setDateOfManufacture(dateOfManufacture);
    point.The_sensor.setNumber(number);
    point.The_sensor.set_bound_state(is_bound_point);
    point.The_sensor.setCentralWavelength(centralWavelength);

    return os;
}

void strain_measuring_point::setTheSensor(const strain_sensor &theSensor)
{
    The_sensor = theSensor;

    Bound_sensor=1;

    The_sensor.set_bound_state(1);
}

QList<QPair<QPair<QString, QString>, QString> > &strain_measuring_point::get_historical_data_list()
{
    return  historical_data;
}

double strain_measuring_point::getResult()
{
    result = 1000 * (The_sensor.getActualWavelength().toDouble() - The_sensor.getCentralWavelength().toDouble()) + 8 * 0.5;

    return result;
}

strain_sensor &strain_measuring_point::getTheSensor()
{
    return The_sensor;
}
