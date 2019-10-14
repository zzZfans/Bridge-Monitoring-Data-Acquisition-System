#include "displacement_sensor.h"

displacement_sensor::displacement_sensor(const QString& name, const QString& specifications, const QString& model,
                                         const QString& manufacturer, const QString& dateOfManufacture,
                                         const QString& number,const QString& initial_value_of_expansion_joint) :
    sensor(name, specifications, model, manufacturer,
           dateOfManufacture, number), Initial_value_of_expansion_joint(initial_value_of_expansion_joint) {}

QTextStream &operator<<(QTextStream &os, const displacement_sensor &sensor)
{
    os  <<sensor.name<<" "
       <<sensor.specification<<" "
      <<sensor.model<<" "
     <<sensor.manufacturer<<" "
    <<sensor.DateOfManufacture<<" "
    <<sensor.number<<" "
    <<sensor.Initial_value_of_expansion_joint<<" "
    <<sensor.Bound_state<<endl;

    return os;
}

QTextStream &operator>>(QTextStream &os,  displacement_sensor &sensor)
{
    os    >>sensor.name
            >>sensor.specification
            >>sensor.model
            >>sensor.manufacturer
            >>sensor.DateOfManufacture
            >>sensor.number
            >>sensor.Initial_value_of_expansion_joint
            >>sensor.Bound_state;

    return os;
}

const QString &displacement_sensor::getDisplacementMonitoringValue() const
{
    return Displacement_monitoring_value;
}

const QString &displacement_sensor::getInitial_value_of_expansion_joint() const
{
    return  Initial_value_of_expansion_joint;
}

void displacement_sensor::set_Initial_value_of_expansion_joint(const QString &initial_value_of_expansion_joint)
{
    Initial_value_of_expansion_joint=initial_value_of_expansion_joint;
}

void displacement_sensor::set_Displacement_Monitoring_Value(const QString &displacementMonitoringValue)
{
    Displacement_monitoring_value = displacementMonitoringValue;
}
