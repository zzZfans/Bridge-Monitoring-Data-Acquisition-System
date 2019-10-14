#ifndef SENSOR_SELECTION_DIALOG_H
#define SENSOR_SELECTION_DIALOG_H

#include <QDialog>

#include<QFile>
#include<QTextStream>
#include<QMessageBox>

namespace Ui {
class sensor_selection_dialog;
}

class sensor_selection_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit sensor_selection_dialog(QWidget *parent = nullptr);
    ~sensor_selection_dialog();

    const QString& getName_of_monitoring_point() const;

    void setName_of_monitoring_point(const QString &name);

    void show_sensor_on_tableWidget();

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

private:
    QString Name_of_monitoring_point;

    Ui::sensor_selection_dialog *ui;

private slots:
    void sensor_tableWidget_double_click_action(int row);
};

#endif // SENSOR_SELECTION_DIALOG_H
