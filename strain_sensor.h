#ifndef STRAIN_SENSOR_H
#define STRAIN_SENSOR_H


#include<QTextStream>
#include"sensor.h"

class strain_sensor : public sensor//应变传感器
{

private:

    QString Central_wavelength;//中心波长

    QString Actual_wavelength;//实际波长

public:

    strain_sensor(const QString& name="0",
                  const QString& specification="0",
                  const QString& model="0",
                  const QString& manufacturer="0",
                  const QString& dateOfManufacture="0",
                  const QString& number="0",
                  const QString& centralWavelength="0" );

    friend QTextStream  &operator<<(QTextStream &os, const strain_sensor &sensor);
    friend QTextStream  &operator>>(QTextStream &os,  strain_sensor &sensor);

    const QString& getActualWavelength() const;

    const QString& getCentralWavelength() const;

    void setActualWavelength(const QString &actualWavelength);

    void setCentralWavelength(const QString &centralWavelength);
};

#endif // STRAIN_SENSOR_H
