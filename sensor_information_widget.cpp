#include "sensor_information_widget.h"
#include "ui_sensor_information_widget.h"

#include"strain_sensor.h"
#include"deflection_sensor.h"
#include"displacement_sensor.h"

#include<QDebug>

Sensor_information_widget::Sensor_information_widget(QWidget *parent) :QWidget(parent),ui(new Ui::Sensor_information_widget)
{
    ui->setupUi(this);


}

Sensor_information_widget::~Sensor_information_widget()
{
    delete ui;

    ui->C_label->hide();
    ui->central_wavelength_label->hide();
}

void Sensor_information_widget::set_sensor_name_temp(const QString &sensor_name)
{
    sensor_name_temp=sensor_name;

    if(sensor_name_temp.mid(0,3)=="Str")
    {
        ui->C_label->show();
        ui->central_wavelength_label->show();
        show_strain_sensor_information();
        return;
    }

    if(sensor_name_temp.mid(0,3)=="Def")
    {
        show_deflection_sensor_information();
        return;
    }

    if(sensor_name_temp.mid(0,3)=="Dis")
        show_displacement_sensor_information();
}

void Sensor_information_widget::show_strain_sensor_information()
{
    //---------------------------------------------------------------------------------------读入应变传感器数据
    std::list<strain_sensor> list_of_ss;
    Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");
    //---------------------------------------------------------------------------------------读入应变传感器数据

    for(auto & ss:list_of_ss)
    {
        if(ss.getName()==sensor_name_temp)
        {
            ui->name_label->setText(sensor_name_temp);
            ui->number_label->setText(ss.getNumber());
            ui->model_label->setText(ss.getModel());
            ui->specification_label->setText(ss.getSpecifications());
            ui->manufacture_label->setText(ss.getManufacturer());
            ui->Date_of_manufacture_label->setText(ss.getDateOfManufacture());
            ui->central_wavelength_label->setText(ss.getCentralWavelength());
            return;
        }
    }
}

void Sensor_information_widget::show_deflection_sensor_information()
{
    //---------------------------------------------------------------------------------------读入挠度传感器数据
    std::list<deflection_sensor> list_of_de_s;
    Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");
    //---------------------------------------------------------------------------------------读入挠度传感器数据

    for(auto & de_s:list_of_de_s)
    {
        if(de_s.getName()==sensor_name_temp)
        {
            ui->name_label->setText(sensor_name_temp);
            ui->number_label->setText(de_s.getNumber());
            ui->model_label->setText(de_s.getModel());
            ui->specification_label->setText(de_s.getSpecifications());
            ui->manufacture_label->setText(de_s.getManufacturer());
            ui->Date_of_manufacture_label->setText(de_s.getDateOfManufacture());
            return;
        }
    }
}

void Sensor_information_widget::show_displacement_sensor_information()
{
    //---------------------------------------------------------------------------------------读入位移传感器数据
    std::list<displacement_sensor> list_of_di_s;
    Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");
    //---------------------------------------------------------------------------------------读入位移传感器数据

    for(auto & di_s:list_of_di_s)
    {
        if(di_s.getName()==sensor_name_temp)
        {
            ui->name_label->setText(sensor_name_temp);
            ui->number_label->setText(di_s.getNumber());
            ui->model_label->setText(di_s.getModel());
            ui->specification_label->setText(di_s.getSpecifications());
            ui->manufacture_label->setText(di_s.getManufacturer());
            ui->Date_of_manufacture_label->setText(di_s.getDateOfManufacture());
            return;
        }
    }
}
