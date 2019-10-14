#ifndef MODIFY_POINT_DIALOG_H
#define MODIFY_POINT_DIALOG_H

#include <QDialog>

namespace Ui {
class modify_point_dialog;
}

class modify_point_dialog : public QDialog
{
    Q_OBJECT

signals:

    void send_data(QString number,QString position);

public:
    explicit modify_point_dialog(QWidget *parent = nullptr);
    ~modify_point_dialog();

    void set_number(QString number);

    void set_position(QString position);

private slots:

    void on_Confirm_revision_pushButton_clicked();

private:

    Ui::modify_point_dialog *ui;

};

#endif // MODIFY_POINT_DIALOG_H
