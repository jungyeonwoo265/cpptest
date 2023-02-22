#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 화면 초기화
    ui->stackedWidget->setCurrentIndex(0);
    // DB연결
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("step_10");
    db.setUserName("root");
    db.setPassword("0000");
    if (!db.open()){
//        qDebug()<<"Database error occurred";
        cout<<"Database error occurred"<<endl;
    }
    else{
//        qDebug()<<"Database open Success";
        cout<<"Database open Success"<<endl;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 230220
// 투표 목록을 추가하는 메서드
void MainWindow::on_pbt_input_clicked()
{
    QString word = ui->le_input->text();
    int num = word.length();
    int twrow = ui->tw_view->rowCount();
    if(num > 0) {
        ui->tw_view->setRowCount(twrow + 1);
        ui->tw_view->setItem(twrow, 0, new QTableWidgetItem(word));
    }
    ui->le_input->clear();
}

// 투표 집계를 눈으로 확인할수 있게 만든 코드
void MainWindow::on_pbt_start_clicked()
{
    srand(time(NULL));
    int twrow = ui->tw_view->rowCount();
    if (twrow > 0){
        int arr[twrow];
        int i, num;
        for (i = 0; i < twrow; i++){
            arr[i] = 0;
            ui->tw_view->setItem(i, 1, new QTableWidgetItem(QString::number(0)));
        }
        for (i = 0; i < 10000; i++){
            num = rand() % twrow;
            arr[num] += 1;
            ui->tw_view->setItem(num, 1, new QTableWidgetItem(QString::number(arr[num])));
            QApplication::processEvents();
        }
        DB_Record(twrow);
    }
}

// 230221
// DB에 투표 결과 넣기
void MainWindow::DB_Record(int row)
{
    int i, num=0;
    QString querystr;
    QSqlQuery query;
    querystr = QString("select count(distinct num) from record;");
    query.prepare(querystr);
    if(query.exec()){
        while(query.next()){
            num = query.value(0).toInt()+1;
        }
    }

    for(i=0; i<row; i++){
        querystr = QString("insert into record values('%1', '%2', '%3');")
                .arg(num)
                .arg(ui->tw_view->item(i, 0)->text())
                .arg(ui->tw_view->item(i, 1)->text().toInt());
        query.prepare(querystr);
        query.exec();
    }
}

// 기록 확인 페이지로 이동
void MainWindow::on_pbt_view_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    QString querystr;
    QSqlQuery query;
    querystr = QString("select distinct num from record;");
    query.prepare(querystr);
    query.exec();
    while(query.next()){
        if(query.value(0).toInt()>ui->comboBox->count())
            ui->comboBox->addItem(query.value(0).toString());
    }

}

// 홈 화면으로 이동
void MainWindow::on_pbt_input_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

// 투표 목록 제거
void MainWindow::on_pbt_erase_clicked()
{
    ui->tw_view->setRowCount(0);
}

// DB에 저장된 투표 기록 보여주기
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    int row=0;
    QString querystr;
    QSqlQuery query;
    querystr = QString("select candidate, vote from record where num = '%1';")
            .arg(arg1.toInt());
    query.prepare(querystr);
    query.exec();
    ui->tw2_view->setRowCount(row);
    while(query.next()){
        row++;
        ui->tw2_view->setRowCount(row);
        ui->tw2_view->setItem(row-1,0,new QTableWidgetItem(query.value(0).toString()));
        ui->tw2_view->setItem(row-1,1,new QTableWidgetItem(query.value(1).toString()));
    }
}
