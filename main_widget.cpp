#include<QFile>
#include<QTextStream>
#include<QDateTime>
#include<QTimer>
#include<QMenu>
#include<QProcess>
#include<QDebug>
#include<QMessageBox>

#include "main_widget.h"
#include "ui_main_widget.h"

#include"view_of_monitoring_point_information_widget.h"
#include"modify_point_dialog.h"
#include"sensor_selection_dialog.h"

#include"modify_sensor_dialog.h"

#include"strain_measuring_point.h"
#include"deflection_monitoring_point.h"
#include"displacement_monitoring_point.h"

#include"strain_sensor.h"
#include"deflection_sensor.h"
#include"displacement_sensor.h"

#include"add_point_dialog.h"
#include"add_sensor_dialog.h"

#include"sensor_information_widget.h"

main_widget::main_widget(QWidget *parent) :QWidget(parent),ui(new Ui::main_widget)
{
    ui->setupUi(this);

    timeShow();

    show_measuring_point_on_tableWidget();

    show_sensor_on_tableWidget();

    //双击鼠标信号槽连接
    connect (ui->point_tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(point_tableWidget_double_click_action(int)));
    connect (ui->sensor_tableWidget,SIGNAL(cellDoubleClicked(int,int)),this,SLOT(sensor_tableWidget_double_click_action(int)));
}

void main_widget::on_ensure_point_pushButton_clicked()
{
    add_point_dialog apd;

    apd.setWindowOpacity(0.9);

    apd.setWindowFlags(Qt::Widget);

    apd.setWindowTitle("Adding "+ui->op_point_comboBox->currentText());

    apd.set_point_Type_temp(ui->op_point_comboBox->currentText());

    apd.exec();

    show_measuring_point_on_tableWidget();
}

void main_widget::show_measuring_point_on_tableWidget()
{
    int RowCount=0;
    //---------------------------------------------------------------------------------------读入应变测点数据

    std::list<strain_measuring_point> list_of_smp;

    RowCount=Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt",RowCount);

    //---------------------------------------------------------------------------------------读入挠度测点数据

    std::list<deflection_monitoring_point> list_of_de_mp;

    RowCount=Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt",RowCount);

    //---------------------------------------------------------------------------------------读入位移测点数据

    std::list<displacement_monitoring_point> list_of_di_mp;

    RowCount=Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt",RowCount);

    //---------------------------------------------------------------------------------------设置行数
    ui->point_tableWidget->setRowCount(RowCount);

    int Rows=0,Columns=0;
    //---------------------------------------------------------------------------------------显示应变测点数据
    for(auto& smp:list_of_smp)
    {
        QTableWidgetItem *name=new QTableWidgetItem(smp.getName());
        name->setToolTip(smp.getName());

        QTableWidgetItem *number=new QTableWidgetItem(smp.getNumber());
        number->setToolTip(smp.getNumber());

        QTableWidgetItem *position=new QTableWidgetItem(smp.getPosition());
        position->setToolTip(smp.getPosition());

        ui->point_tableWidget->setItem(Rows,Columns++,name);
        ui->point_tableWidget->setItem(Rows,Columns++,number);
        ui->point_tableWidget->setItem(Rows,Columns++,position);

        if(!smp.is_Bound_sensor())
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem("Not Bound");
            sensor_name->setToolTip("Not Bound");

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }
        else
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem(smp.getTheSensor().getName());
            sensor_name->setToolTip(smp.getTheSensor().getName());

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }

        //ui->point_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------显示挠度测点数据
    for(auto& de_mp:list_of_de_mp)
    {
        QTableWidgetItem *name=new QTableWidgetItem(de_mp.getName());
        name->setToolTip(de_mp.getName());

        QTableWidgetItem *number=new QTableWidgetItem(de_mp.getNumber());
        number->setToolTip(de_mp.getNumber());

        QTableWidgetItem *position=new QTableWidgetItem(de_mp.getPosition());
        position->setToolTip(de_mp.getPosition());

        ui->point_tableWidget->setItem(Rows,Columns++,name);
        ui->point_tableWidget->setItem(Rows,Columns++,number);
        ui->point_tableWidget->setItem(Rows,Columns++,position);

        if(!de_mp.is_Bound_sensor())
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem("Not Bound");
            sensor_name->setToolTip("Not Bound");

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }
        else
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem(de_mp.getTheSensor().getName());
            sensor_name->setToolTip(de_mp.getTheSensor().getName());

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }

        //ui->point_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------显示位移测点数据
    for(auto& di_mp:list_of_di_mp)
    {
        QTableWidgetItem *name=new QTableWidgetItem(di_mp.getName());
        name->setToolTip(di_mp.getName());

        QTableWidgetItem *number=new QTableWidgetItem(di_mp.getNumber());
        number->setToolTip(di_mp.getNumber());

        QTableWidgetItem *position=new QTableWidgetItem(di_mp.getPosition());
        position->setToolTip(di_mp.getPosition());

        ui->point_tableWidget->setItem(Rows,Columns++,name);
        ui->point_tableWidget->setItem(Rows,Columns++,number);
        ui->point_tableWidget->setItem(Rows,Columns++,position);

        if(!di_mp.is_Bound_sensor())
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem("Not Bound");
            sensor_name->setToolTip("Not Bound");

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }
        else
        {
            QTableWidgetItem *sensor_name=new QTableWidgetItem(di_mp.getTheSensor().getName());
            sensor_name->setToolTip(di_mp.getTheSensor().getName());

            ui->point_tableWidget->setItem(Rows,Columns,sensor_name);
        }

        //ui->point_tableWidget->setItem(Rows,Columns,new QTableWidgetItem("···"));

        Rows++;
        Columns=0;
    }
    //---------------------------------------------------------------------------------------QT tableWidget 内容居中显示
    for(int row=0;row<Rows;row++)
        for(int column=0;column<4;column++)
            ui->point_tableWidget->item(row,column)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    //---------------------------------------------------------------------------------------
    ui->point_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置列宽度均分窗口宽度
    ui->point_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置行高度均分窗口高度

    ui->point_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置表格对用户只读

    ui->point_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式

    ui->point_tableWidget->setItemDelegate(new NoFocusDelegate());//设置无虚线

    // ui->point_tableWidget->horizontalHeader()->setFocusPolicy(Qt::NoFocus);//设置表头不可选
    //  ui->point_tableWidget->verticalHeader()->setFocusPolicy(Qt::NoFocus);

    //将行和列的大小设为与内容相匹配
    //ui->point_tableWidget->resizeColumnsToContents();
    //ui->point_tableWidget->resizeRowsToContents();

    //可以指定某个行或者列的大小
    //ui->point_tableWidget->setRowHeight(3,32);
    //ui->point_tableWidget->setColumnWidth(4,100);

    //ui->point_tableWidget->horizontalHeader()->setHighlightSections(false);//点击表时不对（列）表头行光亮（获取焦点）
    //ui->point_tableWidget->verticalHeader()->setHighlightSections(false);//点击表时不对（行）表头行光亮（获取焦点）

    //ui->point_tableWidget->verticalHeader()->setDefaultSectionSize(30);//设置所有行的默认行高

    //ui->point_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);  // 设置所有的列不可改变列宽
    // ui->point_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);  // 设置所有的行不可改变行高

    //ui->point_tableWidget->horizontalHeader()->setStretchLastSection(true);//列最后一览自适应宽度

    //ui->point_tableWidget->setSelectionMode(QAbstractItemView::ExtendedSelection); //设置为可以选中多个目标(默认如此)

    //QTableWidgetItem *columnHeaderItem0 =ui->point_tableWidget->horizontalHeaderItem(0); //获得水平方向表头的Item对象
    //columnHeaderItem0->setFont(QFont("Helvetica")); //设置字体
    //columnHeaderItem0->setBackgroundColor(QColor(0,60,10)); //设置单元格背景颜色
    // columnHeaderItem0->setTextColor(QColor(200,111,30)); //设置文字颜色

    //单元格设置字体颜色和背景颜色 及字体字符
    // QTableWidgetItem *item = new QTableWidgetItem("Apple");
    // item->setBackgroundColor(QColor(0,60,10));
    //    item->setTextColor(QColor(200,111,100));
    //item->setFont(QFont("Helvetica"));
    //ui->point_tableWidget->setItem(0,3,item);

    //对所有的单元格设置字体
    //ui->point_tableWidget->setFont(QFont("Helvetica"));

    //QComboBox *comBox = new QComboBox(); 把一个下拉框加入单元格
    //comBox->addItem("Y");
    //comBox->addItem("N");
    //ui->point_tableWidget->setCellWidget(0,2,comBox);

    //ui->point_tableWidget->horizontalHeader()->setVisible(false);//隐藏行表头
    //ui->point_tableWidget->verticalHeader()->setVisible(false);//隐藏列表头
}

void main_widget::show_sensor_on_tableWidget()
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

void main_widget::timeShow()
{
    QTimer *timer=new QTimer(this);

    timer->start(1000);

    connect(timer,SIGNAL(timeout()),this,SLOT(timeUpdate()));
}

void main_widget::get_modify_point_data(QString number, QString position)
{
    point_number_temp=number;
    point_position_temp=position;
}

void main_widget::get_modify_sensor_data(QString number, QString Model, QString specification, QString Manufacturer, QString Date_of_manufacture, QString Central_wavelength)
{
    sensor_number_temp=number;
    sensor_Model_temp=Model;
    sensor_specification_temp=specification;
    sensor_Manufacturer_temp=Manufacturer;
    sensor_Date_of_manufacture_temp=Date_of_manufacture;
    strain_sensor_Central_wavelength_temp=Central_wavelength;
}

void main_widget::timeUpdate()
{
    QDateTime time=QDateTime::currentDateTime();

    QString timeStr=time.toString("yyyy-MM-dd hh:mm:ss");

    ui->time_label->setText(timeStr);
}

main_widget::~main_widget()
{
    delete ui;
}

void main_widget::set_customer_type(const int &type)
{
    customer_type=type;

    if(customer_type==1)
    {
        ui->add_point_label->hide();
        ui->op_point_comboBox->hide();
        ui->ensure_point_pushButton->hide();

        ui->add_sensor_label->hide();
        ui->op_sensor_comboBox->hide();
        ui->ensure_sensor_pushButton->hide();
    }

    if(customer_type==2)
    {
        //更改控件菜单策略
        ui->point_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        ui->sensor_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

        //右键菜单信号槽连接
        connect (ui->point_tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(point_tableWidget_Right_click_menu(QPoint)));
        connect (ui->sensor_tableWidget,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(sensor_tableWidget_Right_click_menu(QPoint)));
    }
}

int main_widget::get_customer_type()
{
    return customer_type;
}

void main_widget::point_tableWidget_Right_click_menu(QPoint position)
{
    QTableWidgetItem* Right_click_selected_item = ui->point_tableWidget->itemAt(0,position.y()) ;	//get right click pos item

    if(Right_click_selected_item==nullptr)
        return;

    QMenu* menu1 = new QMenu(this);  //主菜单

    QAction* delete_point_action = new QAction("Delete monitoring point", this);
    QAction* modify_point_action = new QAction("Modification of monitoring point", this);

    delete_point_action->setData(Right_click_selected_item->text());// set data, for later in slot, we can get necessary info
    modify_point_action->setData(Right_click_selected_item->text());

    menu1->addAction(delete_point_action);
    menu1->addAction(modify_point_action);

    QMenu* menu2 = menu1->addMenu("Setting up Sensor");//二级菜单

    QAction* Binding_Sensor_action = new QAction("Binding Sensor", this);
    QAction* Delete_Sensor_action = new QAction("Unloading Sensor", this);
    QAction* Modifying_Sensor_action = new QAction("Modifying Sensor", this);

    Binding_Sensor_action->setData(Right_click_selected_item->text());// set data, for later in slot, we can get necessary info
    Delete_Sensor_action->setData(Right_click_selected_item->text());
    Modifying_Sensor_action->setData(Right_click_selected_item->text());

    menu2->addAction(Binding_Sensor_action);
    menu2->addAction(Delete_Sensor_action);
    menu2->addAction(Modifying_Sensor_action);

    menu1->popup(ui->point_tableWidget->viewport()->mapToGlobal(position)) ; 		//show the menu at right click pos

    connect (delete_point_action,SIGNAL(triggered()), this,SLOT(delete_point()));

    connect (modify_point_action,SIGNAL(triggered()),this,SLOT(modify_point()));

    connect (Binding_Sensor_action,SIGNAL(triggered()),this,SLOT(Binding_Sensor()));

    connect (Delete_Sensor_action,SIGNAL(triggered()),this,SLOT(Unloading_Sensor()));

    connect (Modifying_Sensor_action,SIGNAL(triggered()),this,SLOT(Modifying_Sensor()));
}

void main_widget::point_tableWidget_double_click_action(int row)
{
    QTableWidgetItem* double_click_selected_item = ui->point_tableWidget->item(row,0) ;	//get right click pos item

    if(double_click_selected_item==nullptr)
        return;

    view_of_monitoring_point_information_widget *vompiw=new view_of_monitoring_point_information_widget;//=new View_of_Monitoring_Point_Information_Widget;

    vompiw->setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除

    vompiw->setWindowOpacity(0.9);//透明度

    vompiw->setWindowTitle(double_click_selected_item->text()+" Historical Data");

    vompiw->set_point_name_temp(double_click_selected_item->text());

    vompiw->show();
}

void main_widget::sensor_tableWidget_Right_click_menu(QPoint position)
{
    QTableWidgetItem* Right_click_selected_item = ui->sensor_tableWidget->itemAt(0,position.y()) ;	//get right click pos item

    if(Right_click_selected_item==nullptr)
        return;

    QMenu* menu = new QMenu(this);  //主菜单

    QAction* delete_sensor_action = new QAction("Delete this sensor", this);
    QAction* modify_sensor_action = new QAction("Modify the sensor", this);

    delete_sensor_action->setData(Right_click_selected_item->text());// set data, for later in slot, we can get necessary info
    modify_sensor_action->setData(Right_click_selected_item->text());

    menu->addAction(delete_sensor_action);
    menu->addAction(modify_sensor_action);

    menu->popup(ui->point_tableWidget->viewport()->mapToGlobal(position)) ; 		//show the menu at right click pos

    connect (delete_sensor_action,SIGNAL(triggered()), this,SLOT(delete_this_sensor()));

    connect (modify_sensor_action,SIGNAL(triggered()),this,SLOT(modify_this_sensor()));
}

void main_widget::sensor_tableWidget_double_click_action(int row)
{
    QTableWidgetItem* double_click_selected_item = ui->sensor_tableWidget->item(row,0) ;	//get right click pos item

    if(double_click_selected_item==nullptr)
        return;

    Sensor_information_widget *Siw=new Sensor_information_widget;//=new View_of_Monitoring_Point_Information_Widget;

    //Siw->setAttribute(Qt::WA_DeleteOnClose);//关闭时自动删除

    Siw->setWindowOpacity(0.9);//透明度

    Siw->setWindowTitle(double_click_selected_item->text()+" Information");

    Siw->set_sensor_name_temp(double_click_selected_item->text());

    Siw->show();
}

void main_widget::delete_point()
{
    QAction* dpa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(dpa==nullptr)
        return;

    if(dpa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;

        Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该应变测点数据
        for (auto it=list_of_smp.begin();it!=list_of_smp.end();it++)
        {
            if(it->getName()==dpa->data())
            {
                for(auto &ss:list_of_ss)
                {
                    if(ss.getName()==it->getTheSensor().getName())
                    {
                        ss.set_bound_state(0);

                        break;
                    }
                }
                list_of_smp.erase(it);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储应变测点数据
        Write_data_to_TXT_file(list_of_smp,"strain_measuring_points.txt");
        //---------------------------------------------------------------------------------------存储应变传感器数据
        Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");
    }
    else if (dpa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据
        std::list<deflection_monitoring_point> list_of_de_mp;

        Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;

        Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该应变测点数据
        for (auto it=list_of_de_mp.begin();it!=list_of_de_mp.end();it++)
        {
            if(it->getName()==dpa->data())
            {
                for(auto &de_s:list_of_de_s)
                {
                    if(de_s.getName()==it->getTheSensor().getName())
                    {
                        de_s.set_bound_state(0);

                        break;
                    }
                }
                list_of_de_mp.erase(it);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储挠度测点数据
        Write_data_to_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");
    }
    else if (dpa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据
        std::list<displacement_monitoring_point>list_of_di_mp;

        Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor>list_of_di_s;

        Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该应变测点数据
        for (auto it=list_of_di_mp.begin();it!=list_of_di_mp.end();it++)
        {
            if(it->getName()==dpa->data())
            {
                for(auto &di_s:list_of_di_s)
                {
                    if(di_s.getName()==it->getTheSensor().getName())
                    {
                        di_s.set_bound_state(0);

                        break;
                    }
                }

                list_of_di_mp.erase(it);

                break;
            }
        }

        //---------------------------------------------------------------------------------------存储位移测点数据
        Write_data_to_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储位移传感器数据
        Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");
    }

    show_measuring_point_on_tableWidget();
    show_sensor_on_tableWidget();

    QMessageBox::information(this,"Tips!","Successful deletion!",QMessageBox::Ok);
}

void main_widget::modify_point()
{
    QAction* mpa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(mpa==nullptr)
        return;

    if(mpa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

        //---------------------------------------------------------------------------------------查找该应变测点数据并修改
        for (auto it=list_of_smp.begin();it!=list_of_smp.end();it++)
        {
            if(it->getName()==mpa->data())
            {
                modify_point_dialog mpd;

                mpd.setWindowOpacity(0.9);

                mpd.setWindowFlags(Qt::Widget);

                mpd.setWindowTitle(mpa->data().toString()+" attributes to modify");

                mpd.set_number(it->getNumber());
                mpd.set_position(it->getPosition());

                connect(&mpd,SIGNAL(send_data(QString,QString)),this,SLOT(get_modify_point_data(QString,QString)));

                mpd.exec();

                if(point_number_temp.isEmpty()||point_position_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(point_number_temp=="nullptr"&&point_position_temp=="nullptr")
                    return;

                if(it->getNumber()==point_number_temp&&it->getPosition()==point_position_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto& smp:list_of_smp)
                {
                    if(it->getNumber()!=smp.getNumber())
                        if(smp.getNumber()==point_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }

                    if(it->getPosition()!=smp.getPosition())
                        if(smp.getPosition()==point_position_temp)
                        {
                            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);
                            return;
                        }
                }

                it->set_name("Str_point_"+point_number_temp);
                it->set_number(point_number_temp);
                it->set_position(point_position_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储应变测点数据
        Write_data_to_TXT_file(list_of_smp,"strain_measuring_points.txt");
    }
    else if (mpa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据
        std::list<deflection_monitoring_point> list_of_de_mp;

        Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

        //---------------------------------------------------------------------------------------查找该挠度测点数据并修改
        for (auto it=list_of_de_mp.begin();it!=list_of_de_mp.end();it++)
        {
            if(it->getName()==mpa->data())
            {
                modify_point_dialog mpd;

                mpd.setWindowOpacity(0.9);

                mpd.setWindowFlags(Qt::Widget);

                mpd.setWindowTitle(mpa->data().toString()+" attributes to modify");

                mpd.set_number(it->getNumber());
                mpd.set_position(it->getPosition());

                connect(&mpd,SIGNAL(send_data(QString,QString)),this,SLOT(get_modify_point_data(QString,QString)));

                mpd.exec();

                if(point_number_temp=="nullptr"&&point_position_temp=="nullptr")
                    return;

                if(it->getNumber()==point_number_temp&&it->getPosition()==point_position_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto& smp:list_of_de_mp)
                {
                    if(it->getNumber()!=smp.getNumber())
                        if(smp.getNumber()==point_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }

                    if(it->getPosition()!=smp.getPosition())
                        if(smp.getPosition()==point_position_temp)
                        {
                            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);
                            return;
                        }
                }

                it->set_name("Def_point_"+point_number_temp);
                it->set_number(point_number_temp);
                it->set_position(point_position_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储挠度测点数据
        Write_data_to_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
    }
    else if (mpa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据
        std::list<displacement_monitoring_point>list_of_di_mp;

        Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

        //---------------------------------------------------------------------------------------查找该位移测点数据并修改
        for (auto it=list_of_di_mp.begin();it!=list_of_di_mp.end();it++)
        {
            if(it->getName()==mpa->data())
            {
                modify_point_dialog mpd;

                mpd.setWindowOpacity(0.9);

                mpd.setWindowFlags(Qt::Widget);

                mpd.setWindowTitle(mpa->data().toString()+" attributes to modify");

                mpd.set_number(it->getNumber());
                mpd.set_position(it->getPosition());

                connect(&mpd,SIGNAL(send_data(QString,QString)),this,SLOT(get_modify_point_data(QString,QString)));

                mpd.exec();

                if(point_number_temp=="nullptr"&&point_position_temp=="nullptr")
                    return;

                if(it->getNumber()==point_number_temp&&it->getPosition()==point_position_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto& smp:list_of_di_mp)
                {
                    if(it->getNumber()!=smp.getNumber())
                        if(smp.getNumber()==point_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }

                    if(it->getPosition()!=smp.getPosition())
                        if(smp.getPosition()==point_position_temp)
                        {
                            QMessageBox::critical(this,"error!","This location has been set as a monitoring point!",QMessageBox::Ok);
                            return;
                        }
                }

                it->set_name("Dis_point_"+point_number_temp);
                it->set_number(point_number_temp);
                it->set_position(point_position_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储位移测点数据
        Write_data_to_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
    }

    point_number_temp="nullptr";
    point_position_temp="nullptr";

    show_measuring_point_on_tableWidget();

    QMessageBox::information(this,"Tips!","Successful revision!",QMessageBox::Ok);
}

void main_widget::Binding_Sensor()
{
    QAction* BSa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(BSa==nullptr)
        return;

    if(BSa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &smp:list_of_smp)
        {
            if(smp.getName()==BSa->data())
            {
                if(smp.is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","The sensor is bound to the measuring point!",QMessageBox::Ok);

                    return;
                }
                else
                {
                    sensor_selection_dialog ssd;

                    ssd.setWindowOpacity(0.9);

                    ssd.setWindowFlags(Qt::Widget);

                    ssd.setWindowTitle("Bind sensors to "+BSa->data().toString());

                    ssd.setName_of_monitoring_point(smp.getName());

                    ssd.exec();
                }
                break;
            }
        }
    }
    else if (BSa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据
        std::list<deflection_monitoring_point> list_of_de_mp;

        Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &de_mp:list_of_de_mp)
        {
            if(de_mp.getName()==BSa->data())
            {
                if(de_mp.is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","The sensor is bound to the measuring point!",QMessageBox::Ok);

                    return;
                }
                else
                {
                    sensor_selection_dialog ssd;

                    ssd.setWindowOpacity(0.9);

                    ssd.setWindowFlags(Qt::Widget);

                    ssd.setWindowTitle("Bind sensors to "+BSa->data().toString());

                    ssd.setName_of_monitoring_point(de_mp.getName());

                    ssd.exec();
                }
                break;
            }
        }
    }
    else if (BSa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据
        std::list<displacement_monitoring_point>list_of_di_mp;

        Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

        //---------------------------------------------------------------------------------------查找并绑定传感器

        for (auto &di_mp:list_of_di_mp)
        {
            if(di_mp.getName()==BSa->data())
            {
                if(di_mp.is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","The sensor is bound to the measuring point!",QMessageBox::Ok);

                    return;
                }
                else
                {
                    sensor_selection_dialog ssd;

                    ssd.setWindowOpacity(0.9);

                    ssd.setWindowFlags(Qt::Widget);

                    ssd.setWindowTitle("Bind sensors to "+BSa->data().toString());

                    ssd.setName_of_monitoring_point(di_mp.getName());

                    ssd.exec();
                }
                break;
            }
        }
    }

    show_measuring_point_on_tableWidget();
    show_sensor_on_tableWidget();
}

void main_widget::Unloading_Sensor()
{
    QAction* USa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(USa==nullptr)
        return;

    if(USa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;

        Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该应变测点传感器

        for (auto it=list_of_smp.begin();it!=list_of_smp.end();it++)
        {
            if(it->getName()==USa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }
                else
                {
                    for(auto& ss:list_of_ss)
                        if(ss.getName()==it->getTheSensor().getName())
                        {
                            ss.set_bound_state(0);

                            break;
                        }

                    it->set_Bound_sensor(0);
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储应变测点数据
        Write_data_to_TXT_file(list_of_smp,"strain_measuring_points.txt");
        //---------------------------------------------------------------------------------------存储应变传感器数据
        Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");
    }
    else if (USa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据
        std::list<deflection_monitoring_point> list_of_de_mp;

        Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;

        Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该挠度测点传感器
        for (auto it=list_of_de_mp.begin();it!=list_of_de_mp.end();it++)
        {
            if(it->getName()==USa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }
                else
                {
                    for(auto& de_s:list_of_de_s)
                        if(de_s.getName()==it->getTheSensor().getName())
                        {
                            de_s.set_bound_state(0);

                            break;
                        }

                    it->set_Bound_sensor(0);
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储挠度测点数据
        Write_data_to_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");
    }
    else if (USa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据
        std::list<displacement_monitoring_point>list_of_di_mp;

        Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor> list_of_di_s;

        Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");

        //---------------------------------------------------------------------------------------查找并删除该位移测点传感器
        for (auto it=list_of_di_mp.begin();it!=list_of_di_mp.end();it++)
        {
            if(it->getName()==USa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }
                else
                {
                    for(auto& di_s:list_of_di_s)
                        if(di_s.getName()==it->getTheSensor().getName())
                        {
                            di_s.set_bound_state(0);

                            break;
                        }

                    it->set_Bound_sensor(0);
                }
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储位移测点数据
        Write_data_to_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储位移传感器数据
        Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");
    }

    show_measuring_point_on_tableWidget();
    show_sensor_on_tableWidget();
}

void main_widget::Modifying_Sensor()
{
    QAction* MSa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(MSa==nullptr)
        return;

    if(MSa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变测点数据
        std::list<strain_measuring_point> list_of_smp;

        Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;

        Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");

        //---------------------------------------------------------------------------------------查找该应变测点数据并修改绑定的传感器
        for (auto it=list_of_smp.begin();it!=list_of_smp.end();it++)
        {
            if(it->getName()==MSa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(MSa->data().toString()+" attributes to modify");

                msd.set_number(it->getTheSensor().getNumber());
                msd.set_Model(it->getTheSensor().getModel());
                msd.set_Specification(it->getTheSensor().getSpecifications());
                msd.set_Manufacturer(it->getTheSensor().getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(it->getTheSensor().getDateOfManufacture(),"yyyy/MM/dd"));
                msd.set_Central_wavelength(it->getTheSensor().getCentralWavelength());

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty()
                        ||strain_sensor_Central_wavelength_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr"
                        &&strain_sensor_Central_wavelength_temp=="nullptr")
                    return;

                if(it->getTheSensor().getNumber()==sensor_number_temp
                        &&it->getTheSensor().getModel()==sensor_Model_temp
                        &&it->getTheSensor().getSpecifications()==sensor_specification_temp
                        &&it->getTheSensor().getManufacturer()==sensor_Manufacturer_temp
                        &&it->getTheSensor().getDateOfManufacture()==sensor_Date_of_manufacture_temp
                        &&it->getTheSensor().getCentralWavelength()==strain_sensor_Central_wavelength_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &ss:list_of_ss)
                {
                    if(it->getTheSensor().getNumber()!=ss.getNumber())
                        if(ss.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                for(auto &ss:list_of_ss)
                {
                    if(ss.getName()==it->getTheSensor().getName())
                    {
                        ss.setName("Strain_sensor_"+sensor_number_temp);
                        ss.setNumber(sensor_number_temp);
                        ss.setModel(sensor_Model_temp);
                        ss.setSpecifications(sensor_specification_temp);
                        ss.setManufacturer(sensor_Manufacturer_temp);
                        ss.setDateOfManufacture(sensor_Date_of_manufacture_temp);
                        ss.setCentralWavelength(strain_sensor_Central_wavelength_temp);

                        break;
                    }
                }

                it->getTheSensor().setName("Strain_sensor_"+sensor_number_temp);
                it->getTheSensor().setNumber(sensor_number_temp);
                it->getTheSensor().setModel(sensor_Model_temp);
                it->getTheSensor().setSpecifications(sensor_specification_temp);
                it->getTheSensor().setManufacturer(sensor_Manufacturer_temp);
                it->getTheSensor().setDateOfManufacture(sensor_Date_of_manufacture_temp);
                it->getTheSensor().setCentralWavelength(strain_sensor_Central_wavelength_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储应变测点数据
        Write_data_to_TXT_file(list_of_smp,"strain_measuring_points.txt");
        //---------------------------------------------------------------------------------------存储应变传感器数据
        Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");
    }
    else if(MSa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度测点数据

        std::list<deflection_monitoring_point> list_of_de_mp;

        Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;

        Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");

        //---------------------------------------------------------------------------------------查找该挠度测点数据并修改绑定的传感器
        for (auto it=list_of_de_mp.begin();it!=list_of_de_mp.end();it++)
        {
            if(it->getName()==MSa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(MSa->data().toString()+" attributes to modify");

                msd.hide_the_Central_wavelength();

                msd.set_number(it->getTheSensor().getNumber());
                msd.set_Model(it->getTheSensor().getModel());
                msd.set_Specification(it->getTheSensor().getSpecifications());
                msd.set_Manufacturer(it->getTheSensor().getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(it->getTheSensor().getDateOfManufacture(),"yyyy/MM/dd"));

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr")
                    return;

                if(it->getTheSensor().getNumber()==sensor_number_temp
                        &&it->getTheSensor().getModel()==sensor_Model_temp
                        &&it->getTheSensor().getSpecifications()==sensor_specification_temp
                        &&it->getTheSensor().getManufacturer()==sensor_Manufacturer_temp
                        &&it->getTheSensor().getDateOfManufacture()==sensor_Date_of_manufacture_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &de_s:list_of_de_s)
                {
                    if(it->getTheSensor().getNumber()!=de_s.getNumber())
                        if(de_s.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                for(auto &de_s:list_of_de_s)
                {
                    if(de_s.getName()==it->getTheSensor().getName())
                    {
                        de_s.setName("Deflection_sensor_"+sensor_number_temp);
                        de_s.setNumber(sensor_number_temp);
                        de_s.setModel(sensor_Model_temp);
                        de_s.setSpecifications(sensor_specification_temp);
                        de_s.setManufacturer(sensor_Manufacturer_temp);
                        de_s.setDateOfManufacture(sensor_Date_of_manufacture_temp);

                        break;
                    }
                }

                it->getTheSensor().setName("Deflection_sensor_"+sensor_number_temp);
                it->getTheSensor().setNumber(sensor_number_temp);
                it->getTheSensor().setModel(sensor_Model_temp);
                it->getTheSensor().setSpecifications(sensor_specification_temp);
                it->getTheSensor().setManufacturer(sensor_Manufacturer_temp);
                it->getTheSensor().setDateOfManufacture(sensor_Date_of_manufacture_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储挠度测点数据
        Write_data_to_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");
    }
    else if (MSa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移测点数据

        std::list<displacement_monitoring_point>list_of_di_mp;

        Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor> list_of_di_s;

        Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");

        //---------------------------------------------------------------------------------------查找该挠度测点数据并修改绑定的传感器
        for (auto it=list_of_di_mp.begin();it!=list_of_di_mp.end();it++)
        {
            if(it->getName()==MSa->data())
            {
                if(!it->is_Bound_sensor())
                {
                    QMessageBox::critical(this,"error!","Unbound Sensor!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(MSa->data().toString()+" attributes to modify");

                msd.hide_the_Central_wavelength();

                msd.set_number(it->getTheSensor().getNumber());
                msd.set_Model(it->getTheSensor().getModel());
                msd.set_Specification(it->getTheSensor().getSpecifications());
                msd.set_Manufacturer(it->getTheSensor().getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(it->getTheSensor().getDateOfManufacture(),"yyyy/MM/dd"));

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr")
                    return;

                if(it->getTheSensor().getNumber()==sensor_number_temp
                        &&it->getTheSensor().getModel()==sensor_Model_temp
                        &&it->getTheSensor().getSpecifications()==sensor_specification_temp
                        &&it->getTheSensor().getManufacturer()==sensor_Manufacturer_temp
                        &&it->getTheSensor().getDateOfManufacture()==sensor_Date_of_manufacture_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &di_s:list_of_di_s)
                {
                    if(it->getTheSensor().getNumber()!=di_s.getNumber())
                        if(di_s.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                for(auto &di_s:list_of_di_s)
                {
                    if(di_s.getName()==it->getTheSensor().getName())
                    {
                        di_s.setName("Displacement_sensor_"+sensor_number_temp);
                        di_s.setNumber(sensor_number_temp);
                        di_s.setModel(sensor_Model_temp);
                        di_s.setSpecifications(sensor_specification_temp);
                        di_s.setManufacturer(sensor_Manufacturer_temp);
                        di_s.setDateOfManufacture(sensor_Date_of_manufacture_temp);

                        break;
                    }
                }

                it->getTheSensor().setName("Displacement_sensor_"+sensor_number_temp);
                it->getTheSensor().setNumber(sensor_number_temp);
                it->getTheSensor().setModel(sensor_Model_temp);
                it->getTheSensor().setSpecifications(sensor_specification_temp);
                it->getTheSensor().setManufacturer(sensor_Manufacturer_temp);
                it->getTheSensor().setDateOfManufacture(sensor_Date_of_manufacture_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储位移测点数据
        Write_data_to_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
        //---------------------------------------------------------------------------------------存储位移传感器数据
        Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");
    }

    show_measuring_point_on_tableWidget();
    show_sensor_on_tableWidget();

    QMessageBox::information(this,"Tips!","Successful revision!",QMessageBox::Ok);
}

void main_widget::delete_this_sensor()
{
    QAction* ds=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(ds==nullptr)
        return;

    if(ds->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;

        Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");

        //---------------------------------------------------------------------------------------若已被绑定,则不可删除
        for(auto &ss:list_of_ss)
        {
            if(ss.getName()==ds->data())
            {
                if(ss.is_bound())
                {
                    QMessageBox::critical(this,"error!","Sensors in use cannot be deleted!",QMessageBox::Ok);
                    return;
                }
            }
        }
        //---------------------------------------------------------------------------------------查找并删除该应变传感器

        for (auto it=list_of_ss.begin();it!=list_of_ss.end();it++)
        {
            if(it->getName()==ds->data())
            {
                list_of_ss.erase(it);
                break;
            }
        }

        //---------------------------------------------------------------------------------------存储应变传感器数据
        Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");
    }
    else if (ds->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;

        Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");

        //---------------------------------------------------------------------------------------若已被绑定,则不可删除
        for(auto &de_s:list_of_de_s)
        {
            if(de_s.getName()==ds->data())
            {
                if(de_s.is_bound())
                {
                    QMessageBox::critical(this,"error!","Sensors in use cannot be deleted!",QMessageBox::Ok);
                    return;
                }
            }
        }

        //---------------------------------------------------------------------------------------查找并删除该应变传感器

        for (auto it=list_of_de_s.begin();it!=list_of_de_s.end();it++)
        {
            if(it->getName()==ds->data())
            {
                list_of_de_s.erase(it);
                break;
            }
        }
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");
    }
    else if (ds->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor> list_of_di_s;

        Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");

        //---------------------------------------------------------------------------------------若已被绑定,则不可删除
        for(auto &di_s:list_of_di_s)
        {
            if(di_s.getName()==ds->data())
            {
                if(di_s.is_bound())
                {
                    QMessageBox::critical(this,"error!","Sensors in use cannot be deleted!",QMessageBox::Ok);
                    return;
                }
            }
        }

        //---------------------------------------------------------------------------------------查找并删除该应变传感器

        for (auto it=list_of_di_s.begin();it!=list_of_di_s.end();++it)
        {
            if(it->getName()==ds->data())
            {
                list_of_di_s.erase(it);
                break;
            }
        }
        //---------------------------------------------------------------------------------------存储位移传感器数据
        Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");
    }

    show_sensor_on_tableWidget();

    QMessageBox::information(this,"Tips!","Successful deletion!",QMessageBox::Ok);
}

void main_widget::modify_this_sensor()
{
    QAction* mtsa=qobject_cast<QAction*>(sender());//get previous data saved by us

    if(mtsa==nullptr)
        return;

    if(mtsa->data().toString().mid(0,3)=="Str")
    {
        //---------------------------------------------------------------------------------------读入应变传感器数据
        std::list<strain_sensor> list_of_ss;
        Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");
        //---------------------------------------------------------------------------------------查找该应变传感器数据并修改
        for (auto &ss:list_of_ss)
        {
            if(ss.getName()==mtsa->data())
            {
                if(ss.is_bound())
                {
                    QMessageBox::critical(this,"error!","Binded sensors cannot be modified by this method!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(mtsa->data().toString()+" attributes to modify");

                msd.set_number(ss.getNumber());
                msd.set_Model(ss.getModel());
                msd.set_Specification(ss.getSpecifications());
                msd.set_Manufacturer(ss.getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(ss.getDateOfManufacture(),"yyyy/MM/dd"));
                msd.set_Central_wavelength(ss.getCentralWavelength());

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty()
                        ||strain_sensor_Central_wavelength_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr"
                        &&strain_sensor_Central_wavelength_temp=="nullptr")
                    return;

                if(ss.getNumber()==sensor_number_temp
                        &&ss.getModel()==sensor_Model_temp
                        &&ss.getSpecifications()==sensor_specification_temp
                        &&ss.getManufacturer()==sensor_Manufacturer_temp
                        &&ss.getDateOfManufacture()==sensor_Date_of_manufacture_temp
                        &&ss.getCentralWavelength()==strain_sensor_Central_wavelength_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &ss02:list_of_ss)
                {
                    if(ss.getNumber()!=ss02.getNumber())
                        if(ss02.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                ss.setName("Strain_sensor_"+sensor_number_temp);
                ss.setNumber(sensor_number_temp);
                ss.setModel(sensor_Model_temp);
                ss.setSpecifications(sensor_specification_temp);
                ss.setManufacturer(sensor_Manufacturer_temp);
                ss.setDateOfManufacture(sensor_Date_of_manufacture_temp);
                ss.setCentralWavelength(strain_sensor_Central_wavelength_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储应变传感器数据
        Write_data_to_TXT_file(list_of_ss,"strain_sensors.txt");
    }
    else if(mtsa->data().toString().mid(0,3)=="Def")
    {
        //---------------------------------------------------------------------------------------读入挠度传感器数据
        std::list<deflection_sensor> list_of_de_s;
        Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");
        //---------------------------------------------------------------------------------------查找该挠度传感器数据并修改
        for (auto &de_s:list_of_de_s)
        {
            if(de_s.getName()==mtsa->data())
            {
                if(de_s.is_bound())
                {
                    QMessageBox::critical(this,"error!","Binded sensors cannot be modified by this method!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(mtsa->data().toString()+" attributes to modify");

                msd.hide_the_Central_wavelength();

                msd.set_number(de_s.getNumber());
                msd.set_Model(de_s.getModel());
                msd.set_Specification(de_s.getSpecifications());
                msd.set_Manufacturer(de_s.getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(de_s.getDateOfManufacture(),"yyyy/MM/dd"));

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr"
                        &&strain_sensor_Central_wavelength_temp=="nullptr")
                    return;

                if(de_s.getNumber()==sensor_number_temp
                        &&de_s.getModel()==sensor_Model_temp
                        &&de_s.getSpecifications()==sensor_specification_temp
                        &&de_s.getManufacturer()==sensor_Manufacturer_temp
                        &&de_s.getDateOfManufacture()==sensor_Date_of_manufacture_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &de_s02:list_of_de_s)
                {
                    if(de_s.getNumber()!=de_s02.getNumber())
                        if(de_s02.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                de_s.setName("Deflection_sensor_"+sensor_number_temp);
                de_s.setNumber(sensor_number_temp);
                de_s.setModel(sensor_Model_temp);
                de_s.setSpecifications(sensor_specification_temp);
                de_s.setManufacturer(sensor_Manufacturer_temp);
                de_s.setDateOfManufacture(sensor_Date_of_manufacture_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储挠度传感器数据
        Write_data_to_TXT_file(list_of_de_s,"deflection_sensors.txt");
    }
    else if (mtsa->data().toString().mid(0,3)=="Dis")
    {
        //---------------------------------------------------------------------------------------读入位移传感器数据
        std::list<displacement_sensor> list_of_di_s;
        Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");
        //---------------------------------------------------------------------------------------查找该位移传感器数据并修改
        for (auto &di_s:list_of_di_s)
        {
            if(di_s.getName()==mtsa->data())
            {
                if(di_s.is_bound())
                {
                    QMessageBox::critical(this,"error!","Binded sensors cannot be modified by this method!",QMessageBox::Ok);
                    return;
                }

                modify_sensor_dialog msd;

                msd.setWindowOpacity(0.9);

                msd.setWindowFlags(Qt::Widget);

                msd.setWindowTitle(mtsa->data().toString()+" attributes to modify");

                msd.hide_the_Central_wavelength();

                msd.set_number(di_s.getNumber());
                msd.set_Model(di_s.getModel());
                msd.set_Specification(di_s.getSpecifications());
                msd.set_Manufacturer(di_s.getManufacturer());
                msd.set_Date_of_manufacture(QDate::fromString(di_s.getDateOfManufacture(),"yyyy/MM/dd"));

                connect(&msd,SIGNAL(send_data(QString,QString,QString,QString,QString,QString)),
                        this,SLOT(get_modify_sensor_data(QString,QString,QString,QString,QString,QString)));

                msd.exec();

                if(sensor_number_temp.isEmpty()
                        ||sensor_Model_temp.isEmpty()
                        ||sensor_specification_temp.isEmpty()
                        ||sensor_Manufacturer_temp.isEmpty())
                {
                    QMessageBox::critical(this,"error!","Data cannot be empty!",QMessageBox::Ok);
                    return;
                }

                if(sensor_number_temp=="nullptr"
                        &&sensor_Model_temp=="nullptr"
                        &&sensor_specification_temp=="nullptr"
                        &&sensor_Manufacturer_temp=="nullptr"
                        &&sensor_Date_of_manufacture_temp=="nullptr"
                        &&strain_sensor_Central_wavelength_temp=="nullptr")
                    return;

                if(di_s.getNumber()==sensor_number_temp
                        &&di_s.getModel()==sensor_Model_temp
                        &&di_s.getSpecifications()==sensor_specification_temp
                        &&di_s.getManufacturer()==sensor_Manufacturer_temp
                        &&di_s.getDateOfManufacture()==sensor_Date_of_manufacture_temp)
                {
                    QMessageBox::information(this,"Tips!","No changes were made!",QMessageBox::Yes);
                    return;
                }

                for(auto &di_s02:list_of_di_s)
                {
                    if(di_s.getNumber()!=di_s02.getNumber())
                        if(di_s02.getNumber()==sensor_number_temp)
                        {
                            QMessageBox::critical(this,"error!","The number already exists!",QMessageBox::Ok);
                            return;
                        }
                }

                di_s.setName("Displacement_sensor_"+sensor_number_temp);
                di_s.setNumber(sensor_number_temp);
                di_s.setModel(sensor_Model_temp);
                di_s.setSpecifications(sensor_specification_temp);
                di_s.setManufacturer(sensor_Manufacturer_temp);
                di_s.setDateOfManufacture(sensor_Date_of_manufacture_temp);

                break;
            }
        }
        //---------------------------------------------------------------------------------------存储位移传感器数据
        Write_data_to_TXT_file(list_of_di_s,"displacement_sensors.txt");
    }
    show_sensor_on_tableWidget();

    QMessageBox::information(this,"Tips!","Successful revision!",QMessageBox::Ok);
}

void NoFocusDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyleOptionViewItem itemOption(option);

    if (itemOption.state & QStyle::State_HasFocus)
        itemOption.state = itemOption.state ^ QStyle::State_HasFocus;

    QStyledItemDelegate::paint(painter, itemOption, index);
}

void main_widget::on_ensure_sensor_pushButton_clicked()
{
    add_sensor_dialog asd;

    asd.setWindowOpacity(0.9);

    asd.setWindowFlags(Qt::Widget);

    asd.setWindowTitle("Adding "+ui->op_sensor_comboBox->currentText());

    asd.set_sensor_Type_temp(ui->op_sensor_comboBox->currentText());

    asd.exec();

    show_sensor_on_tableWidget();
}

void main_widget::on_search_point_pushButton_clicked()
{
    int Rows=0;
    //---------------------------------------------------------------------------------------读入应变测点数据

    std::list<strain_measuring_point> list_of_smp;

    Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");

    //---------------------------------------------------------------------------------------读入挠度测点数据

    std::list<deflection_monitoring_point> list_of_de_mp;

    Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");

    //---------------------------------------------------------------------------------------读入位移测点数据

    std::list<displacement_monitoring_point> list_of_di_mp;

    Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");

    for(auto & smp:list_of_smp)
        if(smp.getName()==ui->search_point_lineEdit->text()){
            ui->point_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }

    for(auto & de_mp:list_of_de_mp)
        if(de_mp.getName()==ui->search_point_lineEdit->text()){
            ui->point_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }

    for(auto & di_mp:list_of_di_mp)
        if(di_mp.getName()==ui->search_point_lineEdit->text()){
            ui->point_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }
}

void main_widget::on_search_sensor_pushButton_clicked()
{
    int Rows=0;
    //---------------------------------------------------------------------------------------读入应变传感器数据
    std::list<strain_sensor> list_of_ss;

    Read_data_from_TXT_file(list_of_ss,"strain_sensors.txt");

    //---------------------------------------------------------------------------------------读入挠度传感器数据
    std::list<deflection_sensor> list_of_de_s;

    Read_data_from_TXT_file(list_of_de_s,"deflection_sensors.txt");

    //---------------------------------------------------------------------------------------读入位移传感器数据
    std::list<displacement_sensor> list_of_di_s;

    Read_data_from_TXT_file(list_of_di_s,"displacement_sensors.txt");

    for(auto & ss:list_of_ss)
        if(ss.getName()==ui->search_sensor_lineEdit->text()){
            ui->sensor_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }

    for(auto & de_s:list_of_de_s)
        if(de_s.getName()==ui->search_sensor_lineEdit->text()){
            ui->sensor_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }

    for(auto & di_s:list_of_di_s)
        if(di_s.getName()==ui->search_sensor_lineEdit->text()){
            ui->sensor_tableWidget->selectRow(Rows);
            return;
        }
        else {
            Rows++;
        }
}
