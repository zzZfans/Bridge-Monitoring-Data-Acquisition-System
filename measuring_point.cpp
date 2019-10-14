#include "measuring_point.h"

measuring_point::measuring_point(const QString& name,const QString& number, const QString& position) :name(name) ,number(number), position(position) {}

const QString& measuring_point::getNumber() const
{
    return number;
}

const QString& measuring_point::getPosition() const
{
    return position;
}

void measuring_point::set_name(QString name)
{
    this->name=name;
}

void measuring_point::set_number(QString number)
{
    this->number=number;
}

void measuring_point::set_position(QString position)
{
    this->position=position;
}

const int &measuring_point::is_Bound_sensor() const
{
    return Bound_sensor;
}

void measuring_point::set_Bound_sensor(int y)
{
    Bound_sensor=y;
}

const QString &measuring_point::getName() const {
    return name;
}
