#ifndef VIEW_OF_MONITORING_POINT_INFORMATION_WIDGET_H
#define VIEW_OF_MONITORING_POINT_INFORMATION_WIDGET_H

#include <QWidget>

#include<QFile>
#include<QTextStream>

#include"strain_measuring_point.h"
#include"deflection_monitoring_point.h"
#include"displacement_monitoring_point.h"

#include<QBarSet>

namespace Ui {
class view_of_monitoring_point_information_widget;
}

class view_of_monitoring_point_information_widget : public QWidget
{
    Q_OBJECT

public:
    explicit view_of_monitoring_point_information_widget(QWidget *parent = nullptr);
    ~view_of_monitoring_point_information_widget();

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

    void Read_in_the_historical_data_of_strain_monitoring_points(std::list<strain_measuring_point>& list_of_smp);

    void Read_in_the_historical_data_of_deflection_monitoring_points(std::list<deflection_monitoring_point>& list_of_de_mp);

    void Read_in_the_historical_data_of_displacement_monitoring_points(std::list<displacement_monitoring_point>& list_of_di_mp);

    void set_point_name_temp(const QString &  point_name);

    void show_strain_historical_data();

    void show_deflection_historical_data();

    void show_displacement_historical_data();

    void show_strain_historical_monitoring_data();

    void show_deflection_historical_monitoring_data();

    void show_displacement_historical_monitoring_data();

private:
    QString point_name_temp;

    Ui::view_of_monitoring_point_information_widget *ui;
};

#endif // VIEW_OF_MONITORING_POINT_INFORMATION_WIDGET_H
