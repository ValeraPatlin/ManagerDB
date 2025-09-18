#ifndef FRONTDB_H
#define FRONTDB_H

#include <QDebug>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QString>
#include <QStringList>


/*!
 * \brief The FrontDB class - для подключения к базе данных и выполнение запросов
 */
class FrontDB
{
public:
    /*!
     * \brief FrontDB - конструктор
     */
    FrontDB();
    ~FrontDB();

    /*!
     * \brief openDb - подключение к базе данных
     * \param addDataBase - тип бызы данных
     * \param name_db - имя базы данных
     * \param port - порт
     * \param hostName - ip адрес
     * \param userName - имя пользователя
     * \param passwd - пароль
     * \return - удалось ли подключиться к базе данных
     */
    bool openDb(const QString& addDataBase, const QString& name_db, const int port,
                const QString& hostName, const QString& userName, const QString& passwd);

    /*!
     * \brief tableName - запрос для получения списка таблиц из базы данных
     * \return -
     */
    QStringList tableName();

    /*!
     * \brief selectColumnName - получение имён столбцов
     * \param tableName - имя таблицы
     * \return
     */
    QStringList selectColumnName(const QString& tableName);

    /*!
     * \brief selectTable - запрос select
     * \param tableName - имя таблицы
     * \return
     */
    QStringList selectTable(const QString& tableName);

    /*!
     * \brief requestDb_select - запрос select
     * \param strQuery - запрос в базу данных
     * \return
     */
    const QStringList requestDb_select(const QString& strQuery);

    /*!
     * \brief requestDb
     * \param strQuery - запрос в базу данных
     * \return
     */
    const bool requestDb(const QString& strQuery);

    /*!
     * \brief getNumberRow
     * \return возращает количество строк в таблице
     */
    int getNumberRow();

private:
    QSqlDatabase m_db;

    QString typeDb;

    QString newNameConnectDb;   //!< Имя нового подключения к базе данных
    int numConnectDb{};

    bool m_flagOpenDb{};

    int m_numberRow{};
};

#endif // FRONTDB_H
