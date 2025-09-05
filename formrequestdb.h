#ifndef FORMREQUESTDB_H
#define FORMREQUESTDB_H

#include <QWidget>
#include <QString>
#include <QStringList>
#include <QSplitter>
#include <QTableWidgetItem>
#include <QDebug>
#include "frontdb.h"

namespace Ui {
class FormRequestDb;
}


/*!
 * \brief The FormRequestDb class - для вывода данных и формирования запросов к базе данных
 */
class FormRequestDb : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief FormRequestDb - конструктор по умолчанию
     * \param parent
     */
    explicit FormRequestDb(QWidget *parent = 0);
    ~FormRequestDb();

    /*!
     * \brief setColumnName - принять список имён колонок
     * \param column
     */
    void setColumnName(const QStringList& column);

    /*!
     * \brief setDataTable - принять данные из базы данных
     * \param data
     */
    void setDataTable(const QStringList& data);

    /*!
     * \brief setCountRow - устанавливает количество строк в таблице
     * \param count
     */
    void setCountRow(const unsigned int count);

    /*!
     * \brief selectTable заполняет основную таблицу данными
     * \return true - данные выведены
     */
    bool selectTable();

    /*!
     * \brief resultData вывод данных после запроса пользователя
     * \return true - данные выведены
     */
    bool resultData(const QStringList& data);

    /*!
     * \brief setTableName - принять имя таблицы
     * \param tableName
     */
    void setTableName(const QString& tableName);

    /*!
     * \brief enabledButton делает доступнм кнопки при подключении к базе данных
     * \param flag true - кнопки доступны, false - кнопки не доступны
     */
    void enabledButton(bool flag);

private slots:
    void on_pb_startRequestDb_clicked();
    void on_pb_update_clicked();
    void on_cb_comSQL_activated(const QString &arg1);

private:
    Ui::FormRequestDb *ui;

    QStringList m_columnName;   // название столбцов
    QStringList m_dataTable;
    unsigned int m_countRow{};
    QString m_tableName;

    QSplitter* splitter;

signals:
    /*!
     * \brief signal_requestDb - сигнал для передачи запроса к базе данных
     * \param strQuery - запрос
     * \param flagSelect - является ли запрос SELECT
     */
    void signal_requestDb(const QString& strQuery, bool flagSelect);

    /*!
     * \brief signal_updateDb - обновление таблицы базы данных
     * \param strQuery - запрос на обновление
     */
    void signal_updateDb(const QString& strQuery);

    /*!
     * \brief signal_updateTable
     * \param tableName
     */
    void signal_updateTable(const QString &tableName);
};

#endif // FORMREQUESTDB_H
