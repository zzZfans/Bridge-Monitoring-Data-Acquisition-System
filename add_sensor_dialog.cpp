#include "add_sensor_dialog.h"
#include "ui_add_sensor_dialog.h"

add_sensor_dialog::add_sensor_dialog(QWidget *parent) :QDialog(parent),ui(new Ui::add_sensor_dialog)
{
    ui->setupUi(this);

    QRegExp number_RegExp("[0-9]{6}");   //0-6位 0-9的数字
    ui->numberLineEdit->setValidator(new QRegExpValidator(number_RegExp,ui->numberLineEdit));

    ui->centralWavelengthLabel->hide();
    ui->centralWavelengthLineEdit->hide();
}

add_sensor_dialog::~add_sensor_dialog()
{
    delete ui;
}

void add_sensor_dialog::add_strain_sensor()
{
    if(     ui->specificationLineEdit->text().isEmpty()||
            ui->modelLineEdit->text().isEmpty()||
            ui->manufacturerLineEdit->text().isEmpty()||
            ui->numberLineEdit->text().isEmpty() ||
            ui->centralWavelengthLineEdit->text().isEmpty() )
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);
        return;
    }

    if (ui->dateOfManufactureDateEdit->text()=="2000/01/01")
    {
        if( QMessageBox::question(this, "Tips!", "Is the date correct?",QMessageBox::Yes|QMessageBox::No)
                ==QMessageBox::Yes )
            ;
        else
            return ;
    }
    //---------------------------------------------------------------------------------------读入应变传感器数据

    std::list<strain_sensor> list_of_ss;
    Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");
    //---------------------------------------------------------------------------------------查重

    for (auto& ss:list_of_ss)
    {
        if(ss.getNumber()==ui->numberLineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);

            return;
        }
    }
    //---------------------------------------------------------------------------------------创建并存储strain_sensor
    strain_sensor ss("Str_sensor_"+ui->numberLineEdit->text(),
                     ui->specificationLineEdit->text(),
                     ui->modelLineEdit->text(),
                     ui->manufacturerLineEdit->text(),
                     ui->dateOfManufactureDateEdit->text(),
                     ui->numberLineEdit->text(),
                     ui->centralWavelengthLineEdit->text());

    list_of_ss.push_back(ss);
    //---------------------------------------------------------------------------------------存储应变传感器数据
    list_of_ss.sort(strain_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");

    close();
}

void add_sensor_dialog::add_deflection_sensor()
{
    if(     ui->specificationLineEdit->text().isEmpty()||
            ui->modelLineEdit->text().isEmpty()||
            ui->manufacturerLineEdit->text().isEmpty()||
            ui->numberLineEdit->text().isEmpty() )
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);
        return;
    }

    if (ui->dateOfManufactureDateEdit->text()=="2000/01/01")
    {
        if( QMessageBox::question(this, "Tips!", "Is the date correct?",QMessageBox::Yes|QMessageBox::No)
                ==QMessageBox::Yes )
            ;
        else
            return ;
    }
    //---------------------------------------------------------------------------------------读入挠度传感器数据
    std::list<deflection_sensor> list_of_de_s;
    Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");
    //---------------------------------------------------------------------------------------查重

    for (auto& de_s:list_of_de_s)
    {
        if(de_s.getNumber()==ui->numberLineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);

            return;
        }
    }
    //---------------------------------------------------------------------------------------创建并存储deflection_sensor
    deflection_sensor de_s("Def_sensor_"+ui->numberLineEdit->text(),
                           ui->specificationLineEdit->text(),
                           ui->modelLineEdit->text(),
                           ui->manufacturerLineEdit->text(),
                           ui->dateOfManufactureDateEdit->text(),
                           ui->numberLineEdit->text());

    list_of_de_s.push_back(de_s);
    //---------------------------------------------------------------------------------------存储挠度传感器数据
    list_of_de_s.sort(deflection_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");

    close();
}

void add_sensor_dialog::add_displacement_sensor()
{
    if(     ui->specificationLineEdit->text().isEmpty()||
            ui->modelLineEdit->text().isEmpty()||
            ui->manufacturerLineEdit->text().isEmpty()||
            ui->numberLineEdit->text().isEmpty() )
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);
        return;
    }

    if (ui->dateOfManufactureDateEdit->text()=="2000/01/01")
    {
        if( QMessageBox::question(this, "Tips!", "Is the date correct?",QMessageBox::Yes|QMessageBox::No)
                ==QMessageBox::Yes )
            ;
        else
            return ;
    }
    //---------------------------------------------------------------------------------------读入位移传感器数据
    std::list<displacement_sensor> list_of_di_s;
    Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");
    //---------------------------------------------------------------------------------------查重

    for (auto di_s:list_of_di_s)
    {
        if(di_s.getNumber()==ui->numberLineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);

            return;
        }
    }
    //---------------------------------------------------------------------------------------创建并存储displacement_sensor
    displacement_sensor di_s("Dis_sensor_"+ui->numberLineEdit->text(),
                             ui->specificationLineEdit->text(),
                             ui->modelLineEdit->text(),
                             ui->manufacturerLineEdit->text(),
                             ui->dateOfManufactureDateEdit->text(),
                             ui->numberLineEdit->text());

    list_of_di_s.push_back(di_s);
    //---------------------------------------------------------------------------------------存储位移传感器数据
    list_of_di_s.sort(displacement_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");

    close();
}

void add_sensor_dialog::set_sensor_Type_temp(const QString &sensor_Type)
{
    sensor_Type_temp=sensor_Type;

    if(sensor_Type_temp=="Strain sensor")
    {
        QRegExp central_RegExp("[0-9]{4}[.][0-9]{5}");    //0000.00000
        ui->centralWavelengthLineEdit->setValidator(new QRegExpValidator(central_RegExp,ui->centralWavelengthLineEdit));

        ui->centralWavelengthLabel->show();
        ui->centralWavelengthLineEdit->show();
    }
}

bool add_sensor_dialog::strain_Number_from_small_to_large(const strain_sensor &a, const strain_sensor &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

bool add_sensor_dialog::deflection_Number_from_small_to_large(const deflection_sensor &a, const deflection_sensor &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

bool add_sensor_dialog::displacement_Number_from_small_to_large(const displacement_sensor &a, const displacement_sensor &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

void add_sensor_dialog::on_Add_to_pushButton_clicked()
{
    if(sensor_Type_temp=="Strain sensor")
    {
        add_strain_sensor();
        return;
    }

    if (sensor_Type_temp=="Deflection sensor")
    {
        add_deflection_sensor();
        return;
    }

    if (sensor_Type_temp=="Displacement sensor")
        add_displacement_sensor();
}
