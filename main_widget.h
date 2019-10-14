#ifndef MAIN_WIDGET_H
#define MAIN_WIDGET_H

#include <QWidget>
#include<QStyledItemDelegate>
#include<QTableWidgetItem>

#include<QFile>
#include<QTextStream>
#include<QMessageBox>

#include"strain_measuring_point.h"

namespace Ui {
class main_widget;
}

class main_widget : public QWidget
{
    Q_OBJECT

private:

    int customer_type;

    QString point_number_temp="nullptr";
    QString point_position_temp="nullptr";

    QString sensor_number_temp="nullptr";
    QString sensor_Model_temp="nullptr";
    QString sensor_specification_temp="nullptr";
    QString sensor_Manufacturer_temp="nullptr";
    QString sensor_Date_of_manufacture_temp="nullptr";
    QString strain_sensor_Central_wavelength_temp="nullptr";

public:
    explicit main_widget(QWidget *parent = nullptr);
    ~main_widget();

    void set_customer_type(const int& type);

    int get_customer_type();

    void show_measuring_point_on_tableWidget();

    void show_sensor_on_tableWidget();

    void timeShow();

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

    void on_ensure_point_pushButton_clicked();

    void timeUpdate();

    void point_tableWidget_Right_click_menu(QPoint position);

    void point_tableWidget_double_click_action(int row);

    void sensor_tableWidget_Right_click_menu(QPoint position);

    void sensor_tableWidget_double_click_action(int row);

    void delete_point();

    void modify_point();

    void Binding_Sensor();

    void Unloading_Sensor();

    void Modifying_Sensor();

    void delete_this_sensor();

    void modify_this_sensor();

    void get_modify_point_data(QString number,QString position);

    void get_modify_sensor_data(QString number,QString Model,QString specification,QString Manufacturer,
                                QString Date_of_manufacture,QString Central_wavelength);

    void on_ensure_sensor_pushButton_clicked();

    void on_search_point_pushButton_clicked();

    void on_search_sensor_pushButton_clicked();

private:
    Ui::main_widget *ui;
};

















class NoFocusDelegate : public QStyledItemDelegate     //重载QStyledItemDelegate的paint函数，把焦点移除
{

    Q_OBJECT

public:

    NoFocusDelegate(){}

    ~NoFocusDelegate(){}

    void paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const;

};

#endif // MAIN_WIDGET_H
