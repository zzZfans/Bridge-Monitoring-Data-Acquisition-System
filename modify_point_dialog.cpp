#include<QRegExpValidator>

#include "modify_point_dialog.h"
#include "ui_modify_point_dialog.h"

modify_point_dialog::modify_point_dialog(QWidget *parent) :QDialog(parent),ui(new Ui::modify_point_dialog)
{
    ui->setupUi(this);

    QRegExp number_RegExp("[0-9]{6}");   //0-6位 0-9的数字
    ui->number_lineEdit->setValidator(new QRegExpValidator(number_RegExp,ui->number_lineEdit));
}

modify_point_dialog::~modify_point_dialog()
{
    delete ui;
}

void modify_point_dialog::set_number(QString number)
{
    ui->number_lineEdit->setText(number);
}

void modify_point_dialog::set_position(QString position)
{
    ui->position_lineEdit->setText(position);
}

void modify_point_dialog::on_Confirm_revision_pushButton_clicked()
{
    emit send_data(ui->number_lineEdit->text(),ui->position_lineEdit->text());

    close();
}
