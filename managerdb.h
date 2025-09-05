#ifndef MANAGERDB_H
#define MANAGERDB_H

#include <QMainWindow>
#include <QToolBar>
#include <QDockWidget>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QDebug>

#include "formcreatedb.h"
#include "formtablename.h"
#include "formrequestdb.h"
#include "frontdb.h"

namespace Ui {
class ManagerDB;
}


/*!
 * \brief The ManagerDB class
 */
class ManagerDB : public QMainWindow
{
    Q_OBJECT

public:
    /*!
     * \brief ManagerDB
     * \param parent
     */
    explicit ManagerDB(QWidget *parent = nullptr);
    ~ManagerDB();

private:
    Ui::ManagerDB *ui;

    QDockWidget* pdocCreateDb;
    FormCreateDB* m_formCreateDb;

    QDockWidget* pdocTableName;
    FormTableName* m_formTableName;

    QDockWidget* pdocRequestDb;
    FormRequestDb* m_formRequestDb;

    QToolBar* createToolBar();

    FrontDB m_frontDb;


private slots:
    /*!
     * \brief slot_openDb открытия базы данных
     * \param addDataBase тип бызы данных
     * \param name_db имя базы данных
     * \param port порт
     * \param hostName ip-адрес
     * \param userName имя пользователя
     * \param passwd пароль
     */
    void slot_openDb(const QString addDataBase, const QString name_db, const int port,
                     const QString hostName, const QString userName, const QString passwd);

    /*!
     * \brief slot_selectTable заполнение
     * \param tableName
     */
    void slot_selectTable(const QString& tableName);

    /*!
     * \brief slot_requestDb
     * \param strQuery
     * \param flagSelect
     */
    void slot_requestDb(const QString& strQuery, bool flagSelect);

    /*!
     * \brief slot_updataDb
     * \param strQuery - запрос на выполнение
     */
    void slot_updataDb(const QString& strQuery);

    /*!
     * \brief slot_clearNameListTableDb - очистеть список таблиц
     */
    void slot_clearNameListTableDb();
};

#endif // MANAGERDB_H
