#ifndef MODIFY_SENSOR_DIALOG_H
#define MODIFY_SENSOR_DIALOG_H

#include <QDialog>

namespace Ui {
class modify_sensor_dialog;
}

class modify_sensor_dialog : public QDialog
{
    Q_OBJECT

signals:

    void send_data(QString number,
                   QString Model,
                   QString Specification,
                   QString Manufacturer,
                   QString Date_of_manufacture,
                   QString Central_wavelength);

public:
    explicit modify_sensor_dialog(QWidget *parent = nullptr);
    ~modify_sensor_dialog();

    void set_number(QString number);

    void set_Model(QString Model);

    void set_Specification(QString Specification);

    void set_Manufacturer(QString Manufacturer);

    void set_Date_of_manufacture(QDate Date_of_manufacture);

    void set_Central_wavelength(QString Central_wavelength);

    void hide_the_Central_wavelength();

private slots:

    void on_Confirm_revision_pushButton_clicked();

private:

    Ui::modify_sensor_dialog *ui;

};

#endif // MODIFY_SENSOR_DIALOG_H
