#ifndef DATABASE_H
#define DATABASE_H


#include <QTableWidget>
#include <QObject>
#include <QSqlDataBase>
#include <QSqlError>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QDebug>

#define POSTGRE_DRIVER "QPSQL"
#define DB_NAME "myDB_Film"

//Количество полей данных необходимых для подключения к БД
#define NUM_DATA_FOR_CONNECT_TO_DB 5

//Перечисление полей данных
enum fieldsForConnect{
    hostName = 0,
    dbName = 1,
    login = 2,
    pass = 3,
    port = 4
};

//Типы запросов
enum requestType{

    requestAllFilms = 1,
    requestComedy   = 2,
    requestHorrors  = 3

};



class DataBase : public QObject
{
    Q_OBJECT

public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();

    void AddDataBase(QString driver, QString nameDB);
    void DisconnectFromDataBase(QString nameDb = "");
    void RequestToDBdataAll(QString request, uint32_t idCategory);
    QSqlError GetLastError(void);
    void ConnectToDataBase(QVector<QString> dataForConnect);


signals:

   void sig_SendDataFromDbAllData(QSqlTableModel *tableModel);
   void sig_SendDataFromDbComedy(QSqlQueryModel *queryModel);
   void sig_SendStatusConnection(bool);



private:

    QSqlDatabase* dataBase;

    QSqlQueryModel* queryModel;
    QSqlTableModel* tableModel;

};

#endif // DATABASE_H
