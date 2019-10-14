#include "modify_sensor_dialog.h"
#include "ui_modify_sensor_dialog.h"

modify_sensor_dialog::modify_sensor_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modify_sensor_dialog)
{
    ui->setupUi(this);

    QRegExp number_RegExp("[0-9]{6}");   //0-6位 0-9的数字
    ui->numberLineEdit->setValidator(new QRegExpValidator(number_RegExp,ui->numberLineEdit));
}

modify_sensor_dialog::~modify_sensor_dialog()
{
    delete ui;
}

void modify_sensor_dialog::set_number(QString number)
{
    ui->numberLineEdit->setText(number);
}

void modify_sensor_dialog::set_Model(QString Model)
{
    ui->modelLineEdit->setText(Model);
}

void modify_sensor_dialog::set_Specification(QString Specification)
{
    ui->specificationLineEdit->setText(Specification);
}

void modify_sensor_dialog::set_Manufacturer(QString Manufacturer)
{
    ui->manufacturerLineEdit->setText(Manufacturer);
}

void modify_sensor_dialog::set_Date_of_manufacture(QDate Date_of_manufacture)
{
    ui->dateOfManufactureDateEdit->setDate(Date_of_manufacture);
}

void modify_sensor_dialog::set_Central_wavelength(QString Central_wavelength)
{
    ui->centralWavelengthLineEdit->setText(Central_wavelength);
}

void modify_sensor_dialog::hide_the_Central_wavelength()
{
    ui->centralWavelengthLabel->hide();
    ui->centralWavelengthLineEdit->hide();
}

void modify_sensor_dialog::on_Confirm_revision_pushButton_clicked()
{
    emit send_data(ui->numberLineEdit->text(),
                   ui->modelLineEdit->text(),
                   ui->specificationLineEdit->text(),
                   ui->manufacturerLineEdit->text(),
                   ui->dateOfManufactureDateEdit->text(),
                   ui->centralWavelengthLineEdit->text());

    close();
}
