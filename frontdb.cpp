#include "frontdb.h"

FrontDB::FrontDB()
{
    // SELECT tablename FROM pg_catalog.pg_tables WHERE schemaname = 'public';

    // SELECT column_name FROM information_schema.columns WHERE table_name='vs_node';
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
        if (!m_query->exec("SELECT tablename FROM pg_catalog.pg_tables"
                           " WHERE schemaname = 'public';"))
        {
            qDebug() << "\n  ERROR:  " << m_query->lastError().text();
        }
        else
        {
            while (m_query->next())
            {
                result << m_query->value("tablename").toString();
            }
        }
    }
    return result;
}

QStringList FrontDB::selectColumnName(const QString &tebleName)
{
    QStringList result;
    m_query->clear();
    m_query->prepare("SELECT column_name FROM information_schema.columns WHERE"
                         " table_name=:tebleName ORDER BY ordinal_position;");
    m_query->bindValue(":tebleName", tebleName);

    if (!m_query->exec())
    {
        qDebug() << "\n  ERROR: " << m_query->lastError().text();
    }
    else
    {
        while (m_query->next())
        {
            QString elem = m_query->value(0).toString();

            if (!result.contains(elem))
            {
                result << elem;
            }
        }
        m_query->clear();
    }
    return result;
}

QStringList FrontDB::selectTable(const QString &tebleName)
{
    return requestDb_select("SELECT * FROM " + tebleName +";");
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
