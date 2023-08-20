#include "database.h"

DataBase::DataBase(QObject *parent)
    : QObject{parent}
{

    dataBase = new QSqlDatabase();
    queryModel = new QSqlQueryModel();

}

DataBase::~DataBase()
{
    delete dataBase;
    delete queryModel;
    delete tableModel;
}

/*!
 * \brief Метод добавляет БД к экземпляру класса QSqlDataBase
 * \param driver драйвер БД
 * \param nameDB имя БД (Если отсутствует Qt задает имя по умолчанию)
 */
void DataBase::AddDataBase(QString driver, QString nameDB)
{
    *dataBase = QSqlDatabase::addDatabase(driver, nameDB);
}

/*!
 * \brief Метод подключается к БД
 * \param для удобства передаем контейнер с данными необходимыми для подключения
 * \return возвращает тип ошибки
 */
void DataBase::ConnectToDataBase(QVector<QString> data)
{
    dataBase->setHostName(data[hostName]);
    dataBase->setDatabaseName(data[dbName]);
    dataBase->setUserName(data[login]);
    dataBase->setPassword(data[pass]);
    dataBase->setPort(data[port].toInt());

    ///Тут должен быть код ДЗ

    bool status;
    status = dataBase->open( );
    emit sig_SendStatusConnection(status);
}
/*!
 * \brief Метод производит отключение от БД
 * \param Имя БД
 */
void DataBase::DisconnectFromDataBase(QString nameDb)
{
    *dataBase = QSqlDatabase::database(nameDb);
    dataBase->close();
}
/*!
 * \brief Метод формирует запрос к БД.
 * \param request - SQL запрос
 * \return
 */
void DataBase::RequestToDBdataAll(QString request, uint32_t idCategory)
{

    ///Тут должен быть код ДЗ

    if (idCategory == 0) {
        tableModel = new QSqlTableModel(this, *dataBase);
        tableModel->setTable("film");
        tableModel->select();
        emit sig_SendDataFromDbAllData(tableModel);
    }
    else if (idCategory == 1) {
        queryModel->setQuery(request + " WHERE c.name = 'Comedy'", *dataBase);
        queryModel->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        queryModel->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
        emit sig_SendDataFromDbComedy(queryModel);
    }
    else if (idCategory == 2) {
        queryModel->setQuery(request + " WHERE c.name = 'Horror'", *dataBase);
        queryModel->setHeaderData(0, Qt::Horizontal, tr("Название фильма"));
        queryModel->setHeaderData(1, Qt::Horizontal, tr("Описание фильма"));
        emit sig_SendDataFromDbComedy(queryModel);
    }
}

/*!
 * @brief Метод возвращает последнюю ошибку БД
 */
QSqlError DataBase::GetLastError()
{
    return dataBase->lastError();
}
