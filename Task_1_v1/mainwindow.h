#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QtConcurrent>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QTableView>
#include <QDebug>
#include "database.h"
#include "dbdata.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


public slots:
    void ScreenDataFromDbAllData(QSqlTableModel *tableModel);
    void ScreenDataFromDbCategory(QSqlQueryModel *queryModel);
    void ReceiveStatusConnectionToDB(bool status);


private slots:
    void on_act_addData_triggered();
    void on_act_connect_triggered();
    void on_pb_request_clicked();


    void on_pb_clear_clicked();

signals:
    void sig_RequestToDb(QString request);

private:

    QVector<QString> dataForConnect; //Данные для подключения к БД.

    Ui::MainWindow *ui;
    DbData *dataDb;
    DataBase* dataBase;
    QSqlTableModel *tableModel;
    QSqlQueryModel *queryModel;
    QMessageBox* msg;


    QString request = "SELECT title, description  FROM film f "
                      "JOIN film_category fc on f.film_id = fc.film_id "
                      "JOIN category c on c.category_id  = fc.category_id";

};
#endif // MAINWINDOW_H
