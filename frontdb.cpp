#include "frontdb.h"

FrontDB::FrontDB()
{
    newNameConnectDb = "connectDb_";
}

FrontDB::~FrontDB()
{
    m_db.close();
}

bool FrontDB::openDb(const QString &addDataBase, const QString &name_db, const int port,
                     const QString &hostName, const QString &userName, const QString &passwd)
{
    m_db.close();

    newNameConnectDb += QString::number(++numConnectDb);

    m_db = QSqlDatabase::addDatabase(addDataBase, newNameConnectDb);
    m_db.setPort(port);
    m_db.setDatabaseName(name_db);
    m_db.setHostName(hostName);
    m_db.setUserName(userName);
    m_db.setPassword(passwd);

    if (!m_db.open())
    {
        throw QString("ERROR!  Возникла ошибка при попытке открыть базу данных: \n"
                      + m_db.lastError().text());
    }
    else
    {
        typeDb = addDataBase;
        m_flagOpenDb = true;
        return true;
    }
    return false;
}


QStringList FrontDB::tableName()
{
    QStringList result;

    if (m_flagOpenDb)
    {
        QString strQuery;
        QString strName;

        if (typeDb == "QSQLITE")
        {
            strQuery = "SELECT name FROM sqlite_master WHERE type = 'table';";
            strName = "name";
        }
        else if (typeDb == "QPSQL")
        {
            strQuery = "SELECT tablename FROM pg_catalog.pg_tables"
                       " WHERE schemaname = 'public';";
            strName = "tablename";
        }
        else if (typeDb == "QMYSQL")
        {
            strQuery = "SHOW TABLES;";
            // "SHOW TABLES FROM "
        }

        QSqlQuery query (m_db);

        if (!query.exec(strQuery))
        {
            throw QString("ERROR!  Возникла ошибка при попытке выполнить запрос: \n"
                          + query.lastError().text());
        }
        else
        {
            while (query.next())
            {
                if (typeDb == "QMYSQL")
                {
                    result << query.value(0).toString();
                }
                else
                {
                    result << query.value(strName).toString();
                }
            }
        }
    }
    return result;
}

QStringList FrontDB::selectColumnName(const QString &tableName)
{
    QStringList result;
    QString strQuery;

    if (typeDb == "QSQLITE")
    {
        strQuery = QString("PRAGMA table_info('%1');").arg(tableName);
    }
    else if (typeDb == "QPSQL")
    {
        strQuery = QString("SELECT column_name FROM information_schema.columns WHERE"
                           " table_name='%1' ORDER BY ordinal_position;").arg(tableName);

//        query.prepare("SELECT column_name FROM information_schema.columns WHERE"
//                             " table_name=:tableName ORDER BY ordinal_position;");
//        query.bindValue(":tableName", tableName);
    }
    else if (typeDb == "QMYSQL")
    {
        strQuery = QString("SELECT COLUMN_NAME FROM INFORMATION_SCHEMA.COLUMNS"
                   " WHERE TABLE_NAME='%1';").arg(tableName);

        // TABLE_SCHEMA='%1' AND TABLE_NAME='%2';
        // "SHOW COLUMNS FROM users;"
    }

    QSqlQuery query(m_db);

    if (!query.exec(strQuery))
    {
        throw QString("\n  ERROR: " + query.lastError().text());
    }
    else
    {
        while (query.next())
        {
            QString elem;

            if (typeDb == "QSQLITE")
            {
                elem = query.value("name").toString();
            }
            else
            {
                elem = query.value(0).toString();
            }

            if (!result.contains(elem))
            {
                result << elem;
            }
        }
    }
    return result;
}

QStringList FrontDB::selectTable(const QString &tableName)
{
    return requestDb_select(QString("SELECT * FROM %1;").arg(tableName));
}

const QStringList FrontDB::requestDb_select(const QString &strQuery)
{
    QStringList result;
    m_numberRow = 0;

    QSqlQuery query(m_db);

    if (!query.exec(strQuery))
    {
        qDebug() << "\n  ERROR: " << query.lastError().text();
        throw query.lastError().text();
    }
    else
    {
        QSqlRecord record = query.record();
        int columns = record.count();

        while (query.next())
        {
            QStringList rowData;
            ++m_numberRow;

            for (int i = 0; i < columns; ++i)
            {
                QString value = query.value(i).toString();
                rowData.append(value);
            }
            result.append(rowData.join(", "));
        }
    }
    return result;
}

const bool FrontDB::requestDb(const QString &strQuery)
{
    QSqlQuery query(m_db);

    if (!query.exec(strQuery))
    {
        qDebug() << "\n  ERROR: " << query.lastError().text();
        return false;
    }
    return true;
}

int FrontDB::getNumberRow()
{
    return m_numberRow;
}
