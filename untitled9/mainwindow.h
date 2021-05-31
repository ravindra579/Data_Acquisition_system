#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTableWidget>
#include <QMainWindow>
#include<QTimer>
#include<QKeyEvent>
#include<QHBoxLayout>
#include <QtCharts/QChartGlobal>
#include <vector>
#include <array>
#include "stringlib.h"
#include <messagewindow.h>
#include <field.h>
#include <dataset.h>
#include <fstream>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class QCheckBox;
class QComboBox;
class QDoubleSpinBox;
QT_END_NAMESPACE

class PenTool;
class BrushTool;
class CustomSlice;

QT_BEGIN_NAMESPACE
class QChartView;
class QPieSeries;
class QPieSlice;
QT_END_NAMESPACE

QT_USE_NAMESPACE
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    vector<int> *z[2];
    string file_path;
protected:

signals:
    void rowAdded();
private slots:
    void on_actionOpen_triggered();
    void myfunction();
    void on_pushButton_clicked();
     void addRowIfLast();
    void on_actionSave_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_actionNew_triggered();

    void on_tableWidget_entered(const QModelIndex &index);

    void on_tableWidget_cellEntered(int row, int column);

    void on_pushButton_3_clicked();

    void on_actionLine_triggered();

    void on_actionBar_Chart_triggered();

    void on_actionPie_Chart_triggered();
    Dataset* readCSV(std::string fileName);

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
     QHBoxLayout *horizontalLayout;
     QTimer *timer;
     QString file_name;
     int m=10;
     std::vector<std::string> initHeaderFields;
};
#endif // MAINWINDOW_H
