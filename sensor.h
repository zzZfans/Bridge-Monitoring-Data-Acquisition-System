#ifndef SENSOR_H
#define SENSOR_H


#include<QString>
#include<QDate>

class sensor//传感器
{

protected:

    QString name;
    QString specification;//规格
    QString model;//型号
    QString manufacturer;//生产厂家
    QString DateOfManufacture;//生产日期
    QString number;//编号

    int Bound_state=0; //0空闲 非0使用中

public:
    sensor( const QString& name,
            const QString& specification,
            const QString& model,
            const QString& manufacturer,
            const QString& dateOfManufacture,
            const QString& number );

    const QString& getName() const;

    const QString& getSpecifications() const;

    const QString& getModel() const;

    const QString& getManufacturer() const;

    const QString& getDateOfManufacture() const;

    const QString& getNumber() const;

    void setName(const QString &name);

    void setSpecifications(const QString &specifications);

    void setModel(const QString &model);

    void setManufacturer(const QString &manufacturer);

    void setDateOfManufacture(const QString &dateOfManufacture);

    void setNumber(const QString &number);

    const int & is_bound() const;

    void set_bound_state(const int Bound_point);
};

#endif // SENSOR_H
