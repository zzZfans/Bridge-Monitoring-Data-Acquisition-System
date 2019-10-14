#ifndef MEASURING_POINT_H
#define MEASURING_POINT_H


#include<QString>

class measuring_point//测点
{
protected:

    QString name; //名称
    QString number;//编号
    QString position;//位置

    int Bound_sensor=0;

public:

    measuring_point(const QString& name,const QString& number, const QString& position);

    const QString &getName() const;

    const QString& getNumber() const;

    const QString& getPosition() const;

    void set_name(QString name);

    void set_number(QString number);

    void set_position(QString position);

    const  int &  is_Bound_sensor() const;

    void set_Bound_sensor(int y);

};

#endif // MEASURING_POINT_H
