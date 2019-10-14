#ifndef ADD_POINT_DIALOG_H
#define ADD_POINT_DIALOG_H

#include <QDialog>

#include<QFile>
#include<QTextStream>
#include<QMessageBox>

#include"strain_measuring_point.h"
#include"deflection_monitoring_point.h"
#include"displacement_monitoring_point.h"

namespace Ui {
class add_point_dialog;
}

class add_point_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit add_point_dialog(QWidget *parent = nullptr);
    ~add_point_dialog();

    void add_strain_point();

    void add_deflection_point();

    void add_displacement_point();

    static bool strain_Number_from_small_to_large(const strain_measuring_point & a, const strain_measuring_point& b);

    static bool deflection_Number_from_small_to_large(const deflection_monitoring_point& a, const deflection_monitoring_point& b);

    static bool displacement_Number_from_small_to_large(const displacement_monitoring_point& a, const displacement_monitoring_point& b);

    template<class T>
    int Read_data_from_TXT_file(std::list<T> &list_of_data,const QString& file_name,int Count=-1){

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
    void Write_data_to_TXT_file(const std::list<T> &list_of_data,const QString& file_name) {

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

    void set_point_Type_temp(const QString &  point_Type);

private slots:

    void on_ok_pushButton_clicked();

private:
    QString point_Type_temp;

    Ui::add_point_dialog *ui;
};

#endif // ADD_POINT_DIALOG_H
