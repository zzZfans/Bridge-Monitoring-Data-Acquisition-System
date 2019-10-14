#ifndef SENSOR_INFORMATION_WIDGET_H
#define SENSOR_INFORMATION_WIDGET_H

#include <QWidget>

#include<QFile>
#include<QTextStream>

namespace Ui {
class Sensor_information_widget;
}

class Sensor_information_widget : public QWidget
{
    Q_OBJECT

public:
    explicit Sensor_information_widget(QWidget *parent = nullptr);
    ~Sensor_information_widget();

    void set_sensor_name_temp(const QString &  sensor_name);

    void show_strain_sensor_information();

    void show_deflection_sensor_information();

    void show_displacement_sensor_information();

    template<class T>
    int Read_data_from_TXT_file(std::list<T> &list_of_data,const QString& file_name,int Count=-1)
    {
        QFile data(file_name);

        if ( data.open(QFile::ReadOnly) )
        {
            T temp;

            QTextStream in(& data);

            while (!in.atEnd())
            {
                in>>temp;

                list_of_data.push_back(temp);

                if(Count!=-1)
                    Count++;
            }
            if(!list_of_data.empty())
            {
                list_of_data.pop_back();

                if(Count!=-1)
                    Count--;
            }
        }
        data.close();

        return Count;
    }

private:
    QString sensor_name_temp;

    Ui::Sensor_information_widget *ui;
};

#endif // SENSOR_INFORMATION_WIDGET_H
