#include "sensor_selection_dialog.h"
#include "ui_sensor_selection_dialog.h"

#include"strain_sensor.h"
#include"deflection_sensor.h"
#include"displacement_sensor.h"

#include"main_widget.h"

#include"strain_measuring_point.h"
#include"deflection_monitoring_point.h"
#include"displacement_monitoring_point.h"

#include<QDebug>
#include<QMessageBox>
#include<QFile>

sensor_selection_dialog::sensor_selection_dialog(QWidget *parent) :QDialog(parent),ui(new Ui::sensor_selection_dialog)
{
    ui->setupUi(this);

    show_sensor_on_tableWidget();

    //双击鼠标信号槽连接
    connect (ui->sensor_tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(sensor_tableWidget_double_click_action(int)));
}

sensor_selection_dialog::~sensor_selection_dialog()
{
    delete ui;
}

const QString &sensor_selection_dialog::getName_of_monitoring_point() const
{
    return Name_of_monitoring_point;
}

void sensor_selection_dialog::setName_of_monitoring_point(const QString &name)
{
    Name_of_monitoring_point=name;
}

void sensor_selection_dialog::show_sensor_on_tableWidget()
{
    int RowCount=0;

    //---------------------------------------------------------------------------------------读入应变传感器数据
    std::list<strain_sensor> list_of_ss;

    RowCount=Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt",RowCount);

    //---------------------------------------------------------------------------------------读入挠度传感器数据
    std::list<deflection_sensor> list_of_de_s;

    RowCount=Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt",RowCount);

    //---------------------------------------------------------------------------------------读入位移传感器数据
    std::list<displacement_sensor> list_of_di_s;

    RowCount=Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt",RowCount);

    //---------------------------------------------------------------------------------------设置行数
    ui->sensor_tableWidget->setRowCount(RowCount);

    int Rows=0,Columns=0;
    //---------------------------------------------------------------------------------------显示应变传感器数据
    for(auto& ss:list_of_ss)
    {
        QTableWidgetItem *name=new QTableWidgetItem(ss.getName());
        name->setToolTip(ss.getName());

        QTableWidgetItem *number=new QTableWidgetItem(ss.getNumber());
        number->setToolTip(ss.getNumber());

        QTableWidgetItem *specification=new QTableWidgetItem(ss.getSpecifications());
        specification->setToolTip(ss.getSpecifications());

        QTableWidgetItem *model=new QTableWidgetItem(ss.getModel());
        model->setToolTip(ss.getModel());

        QTableWidgetItem *manuf=new QTableWidgetItem(ss.getManufacturer());
        manuf->setToolTip(ss.getManufacturer());

        QTableWidgetItem *date_of_manuf=new QTableWidgetItem(ss.getDateOfManufacture());
        date_of_manuf->setToolTip(ss.getDateOfManufacture());

        ui->sensor_tableWidget->setItem(Rows,Columns++,name);
        ui->sensor_tableWidget->setItem(Rows,Columns++,number);
        ui->sensor_tableWidget->setItem(Rows,Columns++,specification);
        ui->sensor_tableWidget->setItem(Rows,Columns++,model);
        ui->sensor_tableWidget->setItem(Rows,Columns++,manuf);
        ui->sensor_tableWidget->setItem(Rows,Columns++,date_of_manuf);

        if(!ss.is_bound())
        {
            QTableWidgetItem *state=new QTableWidgetItem("free");
            state->setToolTip("free");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }
        else
        {
            QTableWidgetItem *state=new QTableWidgetItem("in use");
            state->setToolTip("in use");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }

        //ui->sensor_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------显示挠度传感器数据
    for(auto& de_s:list_of_de_s)
    {
        QTableWidgetItem *name=new QTableWidgetItem(de_s.getName());
        name->setToolTip(de_s.getName());

        QTableWidgetItem *number=new QTableWidgetItem(de_s.getNumber());
        number->setToolTip(de_s.getNumber());

        QTableWidgetItem *specification=new QTableWidgetItem(de_s.getSpecifications());
        specification->setToolTip(de_s.getSpecifications());

        QTableWidgetItem *model=new QTableWidgetItem(de_s.getModel());
        model->setToolTip(de_s.getModel());

        QTableWidgetItem *manuf=new QTableWidgetItem(de_s.getManufacturer());
        manuf->setToolTip(de_s.getManufacturer());

        QTableWidgetItem *date_of_manuf=new QTableWidgetItem(de_s.getDateOfManufacture());
        date_of_manuf->setToolTip(de_s.getDateOfManufacture());

        ui->sensor_tableWidget->setItem(Rows,Columns++,name);
        ui->sensor_tableWidget->setItem(Rows,Columns++,number);
        ui->sensor_tableWidget->setItem(Rows,Columns++,specification);
        ui->sensor_tableWidget->setItem(Rows,Columns++,model);
        ui->sensor_tableWidget->setItem(Rows,Columns++,manuf);
        ui->sensor_tableWidget->setItem(Rows,Columns++,date_of_manuf);

        if(!de_s.is_bound())
        {
            QTableWidgetItem *state=new QTableWidgetItem("free");
            state->setToolTip("free");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }
        else
        {
            QTableWidgetItem *state=new QTableWidgetItem("in use");
            state->setToolTip("in use");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }

        //ui->sensor_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------显示位移传感器数据
    for(auto& di_s:list_of_di_s)
    {
        QTableWidgetItem *name=new QTableWidgetItem(di_s.getName());
        name->setToolTip(di_s.getName());

        QTableWidgetItem *number=new QTableWidgetItem(di_s.getNumber());
        number->setToolTip(di_s.getNumber());

        QTableWidgetItem *specification=new QTableWidgetItem(di_s.getSpecifications());
        specification->setToolTip(di_s.getSpecifications());

        QTableWidgetItem *model=new QTableWidgetItem(di_s.getModel());
        model->setToolTip(di_s.getModel());

        QTableWidgetItem *manuf=new QTableWidgetItem(di_s.getManufacturer());
        manuf->setToolTip(di_s.getManufacturer());

        QTableWidgetItem *date_of_manuf=new QTableWidgetItem(di_s.getDateOfManufacture());
        date_of_manuf->setToolTip(di_s.getDateOfManufacture());

        ui->sensor_tableWidget->setItem(Rows,Columns++,name);
        ui->sensor_tableWidget->setItem(Rows,Columns++,number);
        ui->sensor_tableWidget->setItem(Rows,Columns++,specification);
        ui->sensor_tableWidget->setItem(Rows,Columns++,model);
        ui->sensor_tableWidget->setItem(Rows,Columns++,manuf);
        ui->sensor_tableWidget->setItem(Rows,Columns++,date_of_manuf);

        if(!di_s.is_bound())
        {
            QTableWidgetItem *state=new QTableWidgetItem("free");
            state->setToolTip("free");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }
        else
        {
            QTableWidgetItem *state=new QTableWidgetItem("in use");
            state->setToolTip("in use");

            ui->sensor_tableWidget->setItem(Rows,Columns,state);
        }

        //ui->point_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------QT tableWidget 内容居中显示
    for(int row=0;row<Rows;row++)
        for(int column=0;column<7;column++)
            ui->sensor_tableWidget->item(row,column)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //---------------------------------------------------------------------------------------
    ui->sensor_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度均分窗口宽度
    ui->sensor_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置行高度均分窗口高度

    ui->sensor_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格对用户只读

    ui->sensor_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式

    ui->sensor_tableWidget->setItemDelegate(new NoFocusDelegate());//设置无虚线
}

void sensor_selection_dialog::sensor_tableWidget_double_click_action(int row)
{
    QTableWidgetItem* double_click_selected_item = ui->sensor_tableWidget->item(row,0) ;	//get right click pos item

    if(double_click_selected_item==nullptr)
        return;

    if(Name_of_monitoring_point.mid(0,3)!=double_click_selected_item->text().mid(0,3))
    {
        QMessageBox::critical(this,"error!","Sensor type mismatch!",QMessageBox::Ok);
        return;
    }

    if(Name_of_monitoring_point.mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        QFile smp_data("strain_measuring_points.txt");

        if ( smp_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& smp_data);

            strain_measuring_point smp;

            while (!in.atEnd())
            {
                in>>smp;

                list_of_smp.push_back(smp);
            }
            list_of_smp.pop_back();
        }
        smp_data.close();
        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;

        QFile ss_data("strain_sensors.txt");

        if ( ss_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& ss_data);

            strain_sensor ss;

            while (!in.atEnd())
            {
                in>>ss;

                list_of_ss.push_back(ss);
            }
            if(!list_of_ss.empty())
                list_of_ss.pop_back();
        }
        ss_data.close();
        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &smp:list_of_smp)
        {
            if(smp.getName()==Name_of_monitoring_point)
            {
                for(auto& ss:list_of_ss)
                {
                    if(ss.getName()==double_click_selected_item->text())
                    {
                        if(ss.is_bound())
                        {
                            QMessageBox::critical(this,"error!","The sensor is in use!",QMessageBox::Ok);
                            return;
                        }

                        ss.set_bound_state(1);

                        smp.setTheSensor(ss);

                        break;
                    }
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储应变测点数据
        if ( smp_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& smp_data);

            for (auto& smp:list_of_smp)
                out<<smp;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting strain monitoring point!",QMessageBox::Ok);

        smp_data.close();
        //---------------------------------------------------------------------------------------存储应变传感器数据
        if ( ss_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& ss_data);

            for (auto& ss:list_of_ss)
                out<<ss;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting strain monitoring point!",QMessageBox::Ok);

        ss_data.close();
    }
    else if (Name_of_monitoring_point.mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据
        std::list<deflection_monitoring_point> list_of_de_mp;

        QFile de_mp_data("deflection_monitoring_points.txt");

        if ( de_mp_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& de_mp_data);

            deflection_monitoring_point de_mp;

            while (!in.atEnd())
            {
                in>>de_mp;

                list_of_de_mp.push_back(de_mp);
            }
            if(!list_of_de_mp.empty())
            {
                list_of_de_mp.pop_back();
            }
        }
        de_mp_data.close();
        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;

        QFile de_s_data("deflection_sensors.txt");

        if ( de_s_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& de_s_data);

            deflection_sensor de_s;

            while (!in.atEnd())
            {
                in>>de_s;

                list_of_de_s.push_back(de_s);
            }
            if(!list_of_de_s.empty())
            {
                list_of_de_s.pop_back();
            }
        }
        de_s_data.close();
        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &de_mp:list_of_de_mp)
        {
            if(de_mp.getName()==Name_of_monitoring_point)
            {
                for(auto& de_s:list_of_de_s)
                {
                    if(de_s.getName()==double_click_selected_item->text())
                    {
                        if(de_s.is_bound())
                        {
                            QMessageBox::critical(this,"error!","The sensor is in use!",QMessageBox::Ok);
                            return;
                        }

                        de_s.set_bound_state(1);

                        de_mp.setTheSensor(de_s);

                        break;
                    }
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储挠度测点数据
        if ( de_mp_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& de_mp_data);

            for (auto& de_mp:list_of_de_mp)
                out<<de_mp;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting deflection monitoring point!",QMessageBox::Ok);

        de_mp_data.close();
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        if ( de_s_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& de_s_data);

            for (auto& de_s:list_of_de_s)
                out<<de_s;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting strain monitoring point!",QMessageBox::Ok);

        de_s_data.close();
    }
    else if (Name_of_monitoring_point.mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据
        std::list<displacement_monitoring_point> list_of_di_mp;

        QFile di_mp_data("displacement_monitoring_points.txt");

        if ( di_mp_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& di_mp_data);

            displacement_monitoring_point di_mp;

            while (!in.atEnd())
            {
                in>>di_mp;

                list_of_di_mp.push_back(di_mp);

            }
            if(!list_of_di_mp.empty())
            {

                list_of_di_mp.pop_back();

            }
        }
        di_mp_data.close();
        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor> list_of_di_s;

        QFile di_s_data("displacement_sensors.txt");

        if ( di_s_data.open(QFile::ReadOnly) )
        {
            QTextStream in(& di_s_data);

            displacement_sensor di_s;

            while (!in.atEnd())
            {
                in>>di_s;

                list_of_di_s.push_back(di_s);

            }
            if(!list_of_di_s.empty())
            {

                list_of_di_s.pop_back();

            }
        }
        di_s_data.close();
        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &di_mp:list_of_di_mp)
        {
            if(di_mp.getName()==Name_of_monitoring_point)
            {
                for(auto& di_s:list_of_di_s)
                {
                    if(di_s.getName()==double_click_selected_item->text())
                    {
                        if(di_s.is_bound())
                        {
                            QMessageBox::critical(this,"error!","The sensor is in use!",QMessageBox::Ok);
                            return;
                        }

                        di_s.set_bound_state(1);

                        di_mp.setTheSensor(di_s);

                        break;
                    }
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储位移测点数据
        if ( di_mp_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& di_mp_data);

            for (auto& di_mp:list_of_di_mp)
                out<<di_mp;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting displacement monitoring point!",QMessageBox::Ok);

        di_mp_data.close();
        //---------------------------------------------------------------------------------------存储位移传感器数据
        if ( di_s_data.open(QFile::WriteOnly) )
        {
            QTextStream out(& di_s_data);

            for (auto& di_s:list_of_di_s)
                out<<di_s;
        }
        else
            QMessageBox::critical(this,"error!","Failed to open file when deleting strain monitoring point!",QMessageBox::Ok);

        di_s_data.close();
    }

    QMessageBox::information(this,"Tips","Binding success!",QMessageBox::Ok);

    close();
}
