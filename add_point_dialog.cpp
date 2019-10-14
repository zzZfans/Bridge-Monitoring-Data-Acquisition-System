#include<QRegExpValidator>

#include "add_point_dialog.h"
#include "ui_add_point_dialog.h"

add_point_dialog::add_point_dialog(QWidget *parent) :QDialog(parent),ui(new Ui::add_point_dialog)
{
    ui->setupUi(this);

    QRegExp number_RegExp("[0-9]{6}");   //0-6位 0-9的数字
    ui->number_lineEdit->setValidator(new QRegExpValidator(number_RegExp,ui->number_lineEdit));
}

add_point_dialog::~add_point_dialog()
{
    delete ui;
}

void add_point_dialog::on_ok_pushButton_clicked()
{
    if(point_Type_temp=="Strain monitoring point")
        add_strain_point();

    if (point_Type_temp=="Deflection monitoring point")
        add_deflection_point();

    if (point_Type_temp=="Displacement monitoring point")
        add_displacement_point();
}

void add_point_dialog::add_strain_point()
{
    if(ui->number_lineEdit->text().isEmpty()||ui->position_lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);
        return;
    }

    std::list<strain_measuring_point> list_of_smp;
    Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

    for(auto& smp:list_of_smp)
    {
        if(smp.getNumber()==ui->number_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
            return;
        }

        if(smp.getPosition()==ui->position_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);
            return;
        }
    }

    strain_measuring_point smp("Str_point_"+ui->number_lineEdit->text(),
                               ui->number_lineEdit->text(),
                               ui->position_lineEdit->text() );

    list_of_smp.push_back(smp);

    list_of_smp.sort(strain_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_smp,"strain_measuring_points.txt");

    close();
}

void add_point_dialog::add_deflection_point()
{
    if(ui->number_lineEdit->text().isEmpty()||ui->position_lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);

        return;
    }

    std::list<deflection_monitoring_point> list_of_de_mp;

    Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

    for(auto& de_mp:list_of_de_mp)
    {
        if(de_mp.getNumber()==ui->number_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);

            return;
        }

        if(de_mp.getPosition()==ui->position_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);

            return;
        }
    }

    deflection_monitoring_point de_mp("Def_point_"+ui->number_lineEdit->text(),
                                      ui->number_lineEdit->text(),
                                      ui->position_lineEdit->text() );

    list_of_de_mp.push_back(de_mp);

    list_of_de_mp.sort(deflection_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

    close();
}

void add_point_dialog::add_displacement_point()
{
    if(ui->number_lineEdit->text().isEmpty()||ui->position_lineEdit->text().isEmpty())
    {
        QMessageBox::critical(this,"error!","Incomplete information!",QMessageBox::Ok);
        return;
    }

    std::list<displacement_monitoring_point>list_of_di_mp;

    Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

    for(auto& di_mp:list_of_di_mp)
    {
        if(di_mp.getNumber()==ui->number_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
            return;
        }

        if(di_mp.getPosition()==ui->position_lineEdit->text())
        {
            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);
            return;
        }
    }

    displacement_monitoring_point di_mp("Dis_point_"+ui->number_lineEdit->text(),
                                        ui->number_lineEdit->text(),
                                        ui->position_lineEdit->text());

    list_of_di_mp.push_back(di_mp);

    list_of_di_mp.sort(displacement_Number_from_small_to_large);

    Write_data_to_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

    close();
}

bool add_point_dialog::strain_Number_from_small_to_large(const strain_measuring_point &a, const strain_measuring_point &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

bool add_point_dialog::deflection_Number_from_small_to_large(const deflection_monitoring_point &a, const deflection_monitoring_point &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

bool add_point_dialog::displacement_Number_from_small_to_large(const displacement_monitoring_point &a, const displacement_monitoring_point &b)
{
    return a.getNumber().toInt()<b.getNumber().toInt();
}

void add_point_dialog::set_point_Type_temp(const QString &point_Type)
{
    point_Type_temp=point_Type;
}
