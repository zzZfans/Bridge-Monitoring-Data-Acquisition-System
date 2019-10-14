#include "strain_sensor.h"

strain_sensor::strain_sensor(const QString& name,
                             const QString& specification,
                             const QString& model,
                             const QString& manufacturer,
                             const QString& dateOfManufacture,
                             const QString& number,
                             const QString& centralWavelength ) :
    sensor(name, specification,
           model, manufacturer,
           dateOfManufacture, number ),
    Central_wavelength(centralWavelength) {}

QTextStream &operator<<(QTextStream &os, const strain_sensor &sensor)
{
    os  <<sensor.name<<" "
       <<sensor.specification<<" "
      <<sensor.model<<" "
     <<sensor.manufacturer<<" "
    <<sensor.DateOfManufacture<<" "
    <<sensor.number<<" "
    <<sensor.Central_wavelength<<" "
    <<sensor.Bound_state<<endl;

    return os;
}

QTextStream &operator>>(QTextStream &os,  strain_sensor &sensor)
{
    os    >>sensor.name
            >>sensor.specification
            >>sensor.model
            >>sensor.manufacturer
            >>sensor.DateOfManufacture
            >>sensor.number
            >>sensor.Central_wavelength
            >>sensor.Bound_state;

    return os;
}

const QString &strain_sensor::getActualWavelength() const
{
    return Actual_wavelength;
}

void strain_sensor::setActualWavelength(const QString & actualWavelength)
{
    Actual_wavelength = actualWavelength;
}

const QString &strain_sensor::getCentralWavelength() const
{
    return Central_wavelength;
}

void strain_sensor::setCentralWavelength(const QString & centralWavelength)
{
    Central_wavelength = centralWavelength;
}
