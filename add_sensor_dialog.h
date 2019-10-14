#ifndef ADD_SENSOR_DIALOG_H
#define ADD_SENSOR_DIALOG_H

#include <QDialog>

#include<QFile>
#include<QTextStream>
#include<QMessageBox>

#include"strain_sensor.h"
#include"deflection_sensor.h"
#include"displacement_sensor.h"

namespace Ui {
class add_sensor_dialog;
}

class add_sensor_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_sensor_dialog(QWidget *parent = nullptr);
    ~add_sensor_dialog();

    void add_strain_sensor();
    void add_deflection_sensor();
    void add_displacement_sensor();

    void set_sensor_Type_temp(const QString &  sensor_Type);

    static bool strain_Number_from_small_to_large(const strain_sensor & a, const strain_sensor & b);

    static bool deflection_Number_from_small_to_large(const deflection_sensor& a, const deflection_sensor& b);

    static bool displacement_Number_from_small_to_large(const displacement_sensor & a, const displacement_sensor& b);

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

    template<class T>
    void Write_data_to_TXT_file(const std::list<T> &list_of_data,const QString& file_name)
    {
        QFile data(file_name);

        if ( data.open(QFile::WriteOnly) )
        {
            QTextStream out(& data);

            for (auto& data:list_of_data)
                out<<data;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting strain monitoring point!",QMessageBox::Ok);

        data.close();
    }

private slots:

    void on_Add_to_pushButton_clicked();

private:

    QString sensor_Type_temp;

    Ui::add_sensor_dialog *ui;
};

#endif // ADD_SENSOR_DIALOG_H
