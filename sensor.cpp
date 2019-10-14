#include "sensor.h"

sensor::sensor(const QString& name, const QString& specification, const QString& model, const QString& manufacturer,
               const QString &dateOfManufacture, const QString& number) :
    name(name), specification(specification),
    model(model), manufacturer(manufacturer),
    DateOfManufacture(dateOfManufacture),
    number(number) {}

const QString& sensor::getName() const {
    return name;
}

const QString& sensor::getSpecifications() const {
    return specification;
}

const QString& sensor::getModel() const {
    return model;
}

const QString& sensor::getManufacturer() const {
    return manufacturer;
}

const QString &sensor::getDateOfManufacture() const {
    return DateOfManufacture;
}

const QString& sensor::getNumber() const {
    return number;
}

void sensor::setName(const QString &name) {
    sensor::name = name;
}

void sensor::setSpecifications(const QString &specifications) {
    sensor::specification = specifications;
}

void sensor::setModel(const QString &model) {
    sensor::model = model;
}

void sensor::setManufacturer(const QString &manufacturer) {
    sensor::manufacturer = manufacturer;
}

void sensor::setDateOfManufacture(const QString &dateOfManufacture) {
    DateOfManufacture = dateOfManufacture;
}

void sensor::setNumber(const QString &number) {
    sensor::number = number;
}

const int &sensor::is_bound() const
{
    return Bound_state;
}

void sensor::set_bound_state(const int Bound_point)
{
    this->Bound_state=Bound_point;
}
