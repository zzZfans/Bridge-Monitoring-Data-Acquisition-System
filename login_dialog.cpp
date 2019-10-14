#include<QMessageBox>

#include "login_dialog.h"
#include "ui_login_dialog.h"

login_dialog::login_dialog(QWidget *parent) :QDialog(parent),ui(new Ui::login_dialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowCloseButtonHint); //只保留关闭按钮

    setWindowTitle("Bridge Monitoring Data Acquisition System");

    // QIcon loginIcon("C:/Users/10944/Desktop/Bridge_Monitoring_Data_Acquisition_System/MyImages/Br01.svg");
    // setWindowIcon( loginIcon);

    //    QPixmap LoginLabel01Pixmap("C:/Users/10944/Desktop/try/MyImages/CQJTDX.png");

    //    ui->LoginLabel01->setPixmap(LoginLabel01Pixmap);

    //setWindowFlags(Qt::FramelessWindowHint);//无边框

    // setAttribute(Qt::WA_TranslucentBackground);//背景透明

    //setStyleSheet("QPushButton{color:blue}");

    //  ui->loginBtn->setToolTip("<font size=12 color=red><i>Test</i></font>\
    //                           <br><font color=blue>abdefg</font>\
    //                           </br><font color=green>abdlkalflakfl</font>\
    //                           <br><font color=red>eeeeeeeeeeeeeeeeee</br></font>");
}

void login_dialog::on_Login_pushButton_clicked()
{
    // 判断用户名和密码是否正确，
    // 如果错误则弹出警告对话框
    if(ui->User_LineEdit->text().trimmed() == "0"
            &&ui->Pow_LineEdit->text().trimmed() == "0"
            &&ui->User_radioButton->isChecked())
    {
        done(1);
    }
    else if (ui->User_LineEdit->text().trimmed() == "1"
             &&ui->Pow_LineEdit->text().trimmed() == "1"
             &&ui->Administrator_radioButton->isChecked())
    {
        done(2);
    }
    else if((ui->User_LineEdit->text().trimmed() == "0"
             &&ui->Pow_LineEdit->text().trimmed() != "0"
             &&ui->User_radioButton->isChecked())
            ||
            (ui->User_LineEdit->text().trimmed() == "1"
             &&ui->Pow_LineEdit->text().trimmed() != "1"
             &&ui->Administrator_radioButton->isChecked()))
    {
        QMessageBox::critical(this, "error!","Password error!",QMessageBox::Ok);

        // 清空内容并定位光标
        ui->Pow_LineEdit->clear();

        ui->Pow_LineEdit->setFocus();
    }
    else if (ui->User_LineEdit->text().trimmed() != "0"||ui->User_LineEdit->text().trimmed() != "1")
    {
        QMessageBox::critical(this, "error!","user name does not exist!",QMessageBox::Ok);

        // 清空内容并定位光标
        ui->User_LineEdit->clear();

        ui->Pow_LineEdit->clear();

        ui->User_LineEdit->setFocus();
    }
}


login_dialog::~login_dialog()
{
    delete ui;
}
