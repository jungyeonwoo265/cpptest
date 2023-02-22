#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
// DB관련 include
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlTableModel>
// Qt charts 관련
#include<QtCharts>
#include<QtCharts/QChartView>
// 추가한 include
#include <QDebug>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pbt_input_clicked();

    void on_pbt_start_clicked();

    void on_pbt_view_clicked();

    void on_pbt_input_3_clicked();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pbt_erase_clicked();

private:
    Ui::MainWindow *ui;
    void DB_Record(int row);
};

#endif // MAINWINDOW_H
