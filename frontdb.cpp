#include "frontdb.h"

FrontDB::FrontDB()
{
}

FrontDB::~FrontDB()
{
    delete m_query;
}

bool FrontDB::openDb(const QString &addDataBase, const QString &name_db, const int port,
                     const QString &hostName, const QString &userName, const QString &passwd)
{
    m_query = nullptr;
    m_db.close();
    m_db = QSqlDatabase::addDatabase(addDataBase);
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
        m_query = nullptr;
        m_query = new QSqlQuery(m_db);
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
        else
        {
            strQuery = "SELECT tablename FROM pg_catalog.pg_tables"
                       " WHERE schemaname = 'public';";
            strName = "tablename";
        }

        if (!m_query->exec(strQuery))
        {
            throw QString("ERROR!  Возникла ошибка при попытке выполнить запрос: \n"
                          + m_query->lastError().text());
        }
        else
        {
            while (m_query->next())
            {
                result << m_query->value(strName).toString();
            }
        }
    }
    return result;
}

QStringList FrontDB::selectColumnName(const QString &tableName)
{
    m_query->clear();

    QStringList result;
    QString strQuery;

    if (typeDb == "QSQLITE")
    {
        strQuery = QString("PRAGMA table_info('%1');").arg(tableName);
    }
    else
    {
        strQuery = QString("SELECT column_name FROM information_schema.columns WHERE"
                           " table_name='%1' ORDER BY ordinal_position;").arg(tableName);
//        m_query->prepare("SELECT column_name FROM information_schema.columns WHERE"
//                             " table_name=:tableName ORDER BY ordinal_position;");
//        m_query->bindValue(":tableName", tableName);
    }

    if (!m_query->exec(strQuery))
    {
        throw QString("\n  ERROR: " + m_query->lastError().text());
    }
    else
    {
        while (m_query->next())
        {
            QString elem;

            if (typeDb == "QSQLITE")
            {
                elem = m_query->value("name").toString();
            }
            else
            {
                elem = m_query->value(0).toString();
            }

            if (!result.contains(elem))
            {
                result << elem;
            }
        }
        m_query->clear();
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

    if (!m_query->exec(strQuery))
    {
        qDebug() << "\n  ERROR: " << m_query->lastError().text();
        throw m_query->lastError().text();
    }
    else
    {
        QSqlRecord record = m_query->record();
        int columns = record.count();

        while (m_query->next())
        {
            QStringList rowData;
            ++m_numberRow;

            for (int i = 0; i < columns; ++i)
            {
                QString value = m_query->value(i).toString();
                rowData.append(value);
            }
            result.append(rowData.join(", "));
        }
        m_query->clear();
    }
    return result;
}

const bool FrontDB::requestDb(const QString &strQuery)
{
    if (!m_query->exec(strQuery))
    {
        qDebug() << "\n  ERROR: " << m_query->lastError().text();
        return false;
    }
    return true;
}

int FrontDB::getNumberRow()
{
    return m_numberRow;
}
