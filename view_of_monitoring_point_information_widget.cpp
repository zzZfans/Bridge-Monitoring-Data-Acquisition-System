#include "view_of_monitoring_point_information_widget.h"
#include "ui_view_of_monitoring_point_information_widget.h"

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>

#include<QDateTime>
#include<QDateTimeAxis>

#include"strain_measuring_point.h"

#include"QDebug"
#include"QValueAxis"
#include<QSplineSeries>

#include<QMessageBox>

#include<QFileInfo>

view_of_monitoring_point_information_widget::view_of_monitoring_point_information_widget(QWidget *parent) :QWidget(parent),ui(new Ui::view_of_monitoring_point_information_widget)
{
    ui->setupUi(this);
}

view_of_monitoring_point_information_widget::~view_of_monitoring_point_information_widget()
{
    delete ui;
}

void view_of_monitoring_point_information_widget::Read_in_the_historical_data_of_strain_monitoring_points(std::list<strain_measuring_point>& list_of_smp)
{
    if(list_of_smp.size()!=10)
        return;

    QFileInfo file ("应变监测数据.txt");

    if(file.exists()==false)
        return;

    QFile historical_data("应变监测数据.txt");

    if ( historical_data.open(QFile::ReadOnly) ){

        QTextStream in(& historical_data);

        QString date,time;

        QPair<QPair<QString,QString>,QString> temp;

        while (!in.atEnd()){

            in>>date>>time;

            temp.first.first=date;

            temp.first.second=time;

            for (auto & smp:list_of_smp) {
                in>>temp.second;
                smp.get_historical_data_list().push_back(temp);
            }
        }
    }
    for (auto & smp:list_of_smp) {
        if(!smp.get_historical_data_list().isEmpty())
            smp.get_historical_data_list().pop_back();
    }
    historical_data.close();
}

void view_of_monitoring_point_information_widget::Read_in_the_historical_data_of_deflection_monitoring_points(std::list<deflection_monitoring_point> &list_of_de_mp)
{
    if(list_of_de_mp.size()!=14)
        return;

    QFileInfo file ("挠度监测数据.txt");

    if(file.exists()==false)
        return;

    QFile historical_data("挠度监测数据.txt");

    if ( historical_data.open(QFile::ReadOnly) ){
        QTextStream in(& historical_data);

        QString number;

        QPair<QPair<QString,QString>,QPair<QString,QString>> temp;

        while (!in.atEnd()){
            in>>temp.first.first
                    >>temp.first.second
                    >>number
                    >>temp.second.first
                    >>temp.second.second;

            for (auto & de_mp:list_of_de_mp) {
                if(de_mp.getNumber()==number){
                    de_mp.get_historical_data_list().push_back(temp);
                    break;
                }
            }
        }
    }
    historical_data.close();
}

void view_of_monitoring_point_information_widget::Read_in_the_historical_data_of_displacement_monitoring_points(std::list<displacement_monitoring_point> &list_of_di_mp)
{
    if(list_of_di_mp.size()!=2)
        return;

    QFileInfo file ("位移监测数据.txt");

    if(file.exists()==false)
        return;

    QFile historical_data("位移监测数据.txt");

    if ( historical_data.open(QFile::ReadOnly) ){
        QTextStream in(& historical_data);

        QString number;

        QPair<QPair<QString,QString>,QPair<QString,QString>> temp;

        while (!in.atEnd()){
            in>>temp.first.first
                    >>temp.first.second
                    >>number
                    >>temp.second.first
                    >>temp.second.second;

            for (auto & di_mp:list_of_di_mp) {
                if(di_mp.getNumber()==number){
                    di_mp.get_historical_data_list().push_back(temp);
                    break;
                }
            }
        }
    }
    historical_data.close();
}

void view_of_monitoring_point_information_widget::set_point_name_temp(const QString &point_name)
{
    point_name_temp=point_name;

    if(point_name_temp.mid(0,3)=="Str")
    {
        show_strain_historical_data();
        show_strain_historical_monitoring_data();
        return;
    }

    if(point_name_temp.mid(0,3)=="Def")
    {
        show_deflection_historical_data();
        show_deflection_historical_monitoring_data();
        return;
    }

    if(point_name_temp.mid(0,3)=="Dis")
    {
        show_displacement_historical_data();
        show_displacement_historical_monitoring_data();
    }
}

void view_of_monitoring_point_information_widget::show_strain_historical_data()
{
    //---------------------------------------------------------------------------------------读入应变测点数据
    std::list<strain_measuring_point> list_of_smp;
    Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");
    Read_in_the_historical_data_of_strain_monitoring_points(list_of_smp);
    //---------------------------------------------------------------------------------------

    if(list_of_smp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_smp.size()!=10)
        return;

    for(auto &smp:list_of_smp)
    {
        if(smp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical strain");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointμε");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QLineSeries *CentralWavelength_series = new QtCharts::QLineSeries;//折线图数据系列
            CentralWavelength_series->setName("Strain datum");
            CentralWavelength_series->setPointsVisible();
            CentralWavelength_series->setPointLabelsVisible();
            CentralWavelength_series->setPointLabelsFormat("@yPointμε");
            CentralWavelength_series->setPointLabelsFont(Font12);
            CentralWavelength_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(smp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      smp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      smp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(smp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      smp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      smp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(smp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    smp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    smp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(smp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    smp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    smp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            for(auto & data:smp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                double y_Value =1000 * (data.second.toDouble()- smp.getTheSensor().getCentralWavelength().toDouble()) + 8 * 0.5 ;

                data_series->append(time.toSecsSinceEpoch(), y_Value);
            }

            CentralWavelength_series->append(StartTime.toSecsSinceEpoch(),8 * 0.5);
            CentralWavelength_series->append(EndTime.toSecsSinceEpoch(),8 * 0.5);

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of strain monitoring points");

            chart->addSeries(data_series);
            chart->addSeries(CentralWavelength_series);

            axisX_Time->setTickCount(10);//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTitleText("strain με");
            axisY->setTickCount(data_series->count());
            //axisY->setRange(0, 10);
            //axisY->setLabelFormat("%u");
            //axisY->setGridLineVisible(true);
            //axisY->setMinorTickCount(1);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_Computational->setChart(chart);
            ui->qchartview_Computational->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

void view_of_monitoring_point_information_widget::show_deflection_historical_data()
{
    //---------------------------------------------------------------------------------------读入挠度测点数据
    std::list<deflection_monitoring_point> list_of_de_mp;
    Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
    Read_in_the_historical_data_of_deflection_monitoring_points(list_of_de_mp);
    //---------------------------------------------------------------------------------------

    if(list_of_de_mp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_de_mp.size()!=14)
        return;

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>Baseline_monitoring_value;

    for(auto & de_mp:list_of_de_mp)
    {
        if(de_mp.getNumber()=="700737")
        {
            Baseline_monitoring_value=de_mp.get_historical_data_list();
            break;
        }
    }

    for(auto & de_mp:list_of_de_mp)
    {
        if(de_mp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical deflection");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointmm");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(de_mp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      de_mp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(de_mp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(de_mp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    de_mp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(de_mp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            double Baseline_value = 0.0;

            for(auto & data:de_mp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                for(auto &Base:Baseline_monitoring_value)
                {
                    if(data.first.first==Base.first.first&&data.first.second==Base.first.second)
                    {
                        Baseline_value=Base.second.first.toDouble();
                        break;
                    }
                }

                double y_Value =data.second.first.toDouble()-Baseline_value ;

                data_series->append(time.toSecsSinceEpoch(), y_Value);
            }

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of deflection monitoring points");

            chart->addSeries(data_series);

            axisX_Time->setTickCount(data_series->count());//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTitleText("deflection mm");
            axisY->setTickCount(data_series->count());
            // axisY->setRange(0, 10);
            //  axisY->setLabelFormat("%u");
            //  axisY->setGridLineVisible(true);
            // axisY->setMinorTickCount(10);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_Computational->setChart(chart);
            ui->qchartview_Computational->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

void view_of_monitoring_point_information_widget::show_displacement_historical_data()
{
    //---------------------------------------------------------------------------------------读入位移测点数据
    std::list<displacement_monitoring_point> list_of_di_mp;
    Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
    Read_in_the_historical_data_of_displacement_monitoring_points(list_of_di_mp);
    //---------------------------------------------------------------------------------------

    if(list_of_di_mp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_di_mp.size()!=2)
        return;

    for(auto & di_mp:list_of_di_mp)
    {
        if(di_mp.getNumber()=="800227")
            di_mp.getTheSensor().set_Initial_value_of_expansion_joint("0.98");

        if(di_mp.getNumber()=="800225")
            di_mp.getTheSensor().set_Initial_value_of_expansion_joint("0.23");
    }

    for(auto & di_mp:list_of_di_mp)
    {
        if(di_mp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical displacement");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointcm");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QLineSeries *Ideal_value_series = new QtCharts::QLineSeries;//折线图数据系列
            Ideal_value_series->setName("Ideal value");
            Ideal_value_series->setPointsVisible();
            Ideal_value_series->setPointLabelsVisible();
            Ideal_value_series->setPointLabelsFormat("@yPointcm");
            Ideal_value_series->setPointLabelsFont(Font12);
            Ideal_value_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(di_mp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      di_mp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(di_mp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(di_mp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    di_mp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(di_mp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            for(auto & data:di_mp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                double y_Value =data.second.first.toDouble()-di_mp.getTheSensor().getInitial_value_of_expansion_joint().toDouble();

                data_series->append(time.toSecsSinceEpoch(), y_Value);
            }

            Ideal_value_series->append(StartTime.toSecsSinceEpoch(),0);
            Ideal_value_series->append(EndTime.toSecsSinceEpoch(),0);

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of displacement monitoring points");

            chart->addSeries(data_series);
            chart->addSeries(Ideal_value_series);

            axisX_Time->setTickCount(data_series->count());//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTickCount(data_series->count());
            axisY->setTitleText("displacement cm");
            // axisY->setRange(0, 10);
            //  axisY->setLabelFormat("%u");
            //  axisY->setGridLineVisible(true);

            //axisY->setMinorTickCount(10);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_Computational->setChart(chart);
            ui->qchartview_Computational->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

void view_of_monitoring_point_information_widget::show_strain_historical_monitoring_data()
{
    //---------------------------------------------------------------------------------------读入应变测点数据
    std::list<strain_measuring_point> list_of_smp;
    Read_data_from_TXT_file(list_of_smp,"strain_measuring_points.txt");
    Read_in_the_historical_data_of_strain_monitoring_points(list_of_smp);
    //---------------------------------------------------------------------------------------

    if(list_of_smp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_smp.size()!=10)
        return;

    for(auto &smp:list_of_smp)
    {
        if(smp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical wavelength");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointμε");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QLineSeries *CentralWavelength_series = new QtCharts::QLineSeries;//折线图数据系列
            CentralWavelength_series->setName("Central wavelength");
            CentralWavelength_series->setPointsVisible();
            CentralWavelength_series->setPointLabelsVisible();
            CentralWavelength_series->setPointLabelsFormat("@yPointμε");
            CentralWavelength_series->setPointLabelsFont(Font12);
            CentralWavelength_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(smp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      smp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      smp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(smp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      smp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      smp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(smp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    smp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    smp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(smp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    smp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    smp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            for(auto & data:smp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                data_series->append(time.toSecsSinceEpoch(), data.second.toDouble());
            }

            CentralWavelength_series->append(StartTime.toSecsSinceEpoch(),smp.getTheSensor().getCentralWavelength().toDouble());
            CentralWavelength_series->append(EndTime.toSecsSinceEpoch(),smp.getTheSensor().getCentralWavelength().toDouble());

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of strain monitoring points");

            chart->addSeries(data_series);
            chart->addSeries(CentralWavelength_series);

            axisX_Time->setTickCount(10);//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTitleText("wavelength με");
            axisY->setTickCount(data_series->count());
            //axisY->setRange(0, 10);
            //axisY->setLabelFormat("%u");
            //axisY->setGridLineVisible(true);
            //axisY->setMinorTickCount(1);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_monitoring->setChart(chart);
            ui->qchartview_monitoring->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

void view_of_monitoring_point_information_widget::show_deflection_historical_monitoring_data()
{
    //---------------------------------------------------------------------------------------读入挠度测点数据
    std::list<deflection_monitoring_point> list_of_de_mp;
    Read_data_from_TXT_file(list_of_de_mp,"deflection_monitoring_points.txt");
    Read_in_the_historical_data_of_deflection_monitoring_points(list_of_de_mp);
    //---------------------------------------------------------------------------------------

    if(list_of_de_mp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_de_mp.size()!=14)
        return;

    QList<QPair<QPair<QString,QString>,QPair<QString,QString>>>Baseline_monitoring_value;

    for(auto & de_mp:list_of_de_mp)
    {
        if(de_mp.getNumber()=="700737")
        {
            Baseline_monitoring_value=de_mp.get_historical_data_list();
            break;
        }
    }

    for(auto & de_mp:list_of_de_mp)
    {
        if(de_mp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical monitoring value");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointmm");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(de_mp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      de_mp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(de_mp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      de_mp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(de_mp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    de_mp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(de_mp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    de_mp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            for(auto & data:de_mp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                data_series->append(time.toSecsSinceEpoch(), data.second.first.toDouble());
            }

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of deflection monitoring points");

            chart->addSeries(data_series);

            axisX_Time->setTickCount(data_series->count());//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTitleText("monitoring value mm");
            axisY->setTickCount(data_series->count());
            // axisY->setRange(0, 10);
            //  axisY->setLabelFormat("%u");
            //  axisY->setGridLineVisible(true);
            //axisY->setMinorTickCount(10);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_monitoring->setChart(chart);
            ui->qchartview_monitoring->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

void view_of_monitoring_point_information_widget::show_displacement_historical_monitoring_data()
{
    //---------------------------------------------------------------------------------------读入位移测点数据
    std::list<displacement_monitoring_point> list_of_di_mp;
    Read_data_from_TXT_file(list_of_di_mp,"displacement_monitoring_points.txt");
    Read_in_the_historical_data_of_displacement_monitoring_points(list_of_di_mp);
    //---------------------------------------------------------------------------------------

    if(list_of_di_mp.front().get_historical_data_list().isEmpty())
        return;

    if(list_of_di_mp.size()!=2)
        return;

    for(auto & di_mp:list_of_di_mp)
    {
        if(di_mp.getNumber()=="800227")
            di_mp.getTheSensor().set_Initial_value_of_expansion_joint("0.98");

        if(di_mp.getNumber()=="800225")
            di_mp.getTheSensor().set_Initial_value_of_expansion_joint("0.23");
    }

    for(auto & di_mp:list_of_di_mp)
    {
        if(di_mp.getName()==point_name_temp)
        {
            QFont Font("微软雅黑",16);
            QFont Font12("微软雅黑",12);

            QtCharts::QLineSeries *data_series = new QtCharts::QLineSeries;//折线图数据系列
            data_series->setName("Historical expansion joint data");
            data_series->setPointsVisible();
            data_series->setPointLabelsVisible();
            data_series->setPointLabelsFormat("@yPointcm");
            data_series->setPointLabelsFont(Font12);
            data_series->setPointLabelsClipping(false);

            QtCharts::QLineSeries *initial_value_series = new QtCharts::QLineSeries;//折线图数据系列
            initial_value_series->setName("Initial value of expansion joint");
            initial_value_series->setPointsVisible();
            initial_value_series->setPointLabelsVisible();
            initial_value_series->setPointLabelsFormat("@yPointcm");
            initial_value_series->setPointLabelsFont(Font12);
            initial_value_series->setPointLabelsClipping(false);

            QtCharts::QDateTimeAxis *axisX_Time = new QtCharts::QDateTimeAxis; //时间类型轴(用作X轴)

            axisX_Time->setFormat("yyyy/MM/dd HH:mm:ss");

            axisX_Time->setTitleFont(Font);

            axisX_Time->setTitleText("Date and time");

            QDateTime StartTime(QDate(di_mp.get_historical_data_list().front().first.first.mid(0,4).toInt(),
                                      di_mp.get_historical_data_list().front().first.first.mid(5,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.first.mid(8,2).toInt()),
                                QTime(di_mp.get_historical_data_list().front().first.second.mid(0,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.second.mid(3,2).toInt(),
                                      di_mp.get_historical_data_list().front().first.second.mid(6,2).toInt()));

            QDateTime EndTime(QDate(di_mp.get_historical_data_list().back().first.first.mid(0,4).toInt(),
                                    di_mp.get_historical_data_list().back().first.first.mid(5,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.first.mid(8,2).toInt()),
                              QTime(di_mp.get_historical_data_list().back().first.second.mid(0,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.second.mid(3,2).toInt(),
                                    di_mp.get_historical_data_list().back().first.second.mid(6,2).toInt()));

            axisX_Time->setRange(StartTime, EndTime);//轴 最小值 最大值

            for(auto & data:di_mp.get_historical_data_list())
            {    //设置数据点
                QDateTime time(QDate(data.first.first.mid(0,4).toInt(),
                                     data.first.first.mid(5,2).toInt() ,
                                     data.first.first.mid(8,2).toInt()),
                               QTime(data.first.second.mid(0,2).toInt(),
                                     data.first.second.mid(3,2).toInt(),
                                     data.first.second.mid(6,2).toInt()));

                data_series->append(time.toSecsSinceEpoch(), data.second.first.toDouble());
            }

            initial_value_series->append(StartTime.toSecsSinceEpoch(),di_mp.getTheSensor().getInitial_value_of_expansion_joint().toDouble());
            initial_value_series->append(EndTime.toSecsSinceEpoch(),di_mp.getTheSensor().getInitial_value_of_expansion_joint().toDouble());

            QtCharts::QChart *chart = new QtCharts::QChart;

            chart->setTitleFont(Font);

            chart->setTitle("Historical data of displacement monitoring points");

            chart->addSeries(data_series);
            chart->addSeries(initial_value_series);

            axisX_Time->setTickCount(data_series->count());//设置显示的时间个数

            chart->createDefaultAxes();//根据数据设置坐标

            chart->setAxisX(axisX_Time);//设置X轴样式

            QtCharts::QValueAxis *axisY = new QtCharts::QValueAxis;
            axisY->setTitleFont(Font);
            axisY->setTickCount(data_series->count());
            axisY->setTitleText("Length of expansion joint cm");
            // axisY->setRange(0, 10);
            //  axisY->setLabelFormat("%u");
            //  axisY->setGridLineVisible(true);

            //axisY->setMinorTickCount(10);

            chart->setAxisY(axisY,data_series);//设置Y轴样式

            ui->qchartview_monitoring->setChart(chart);
            ui->qchartview_monitoring->setRenderHint(QPainter::Antialiasing);//线段平滑

            return;
        }
    }
}

