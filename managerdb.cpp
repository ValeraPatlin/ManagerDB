#include "managerdb.h"
#include "ui_managerdb.h"

ManagerDB::ManagerDB(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ManagerDB)
{
    ui->setupUi(this);

    //this->addToolBar(Qt::TopToolBarArea, createToolBar());

    pdocCreateDb = new QDockWidget("Подключение", this);
    m_formCreateDb = new FormCreateDB(pdocCreateDb);
    pdocCreateDb->setWidget(m_formCreateDb);
    pdocCreateDb->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    this->addDockWidget(Qt::TopDockWidgetArea, pdocCreateDb);

    pdocTableName = new QDockWidget("Таблицы:", this);
    m_formTableName = new FormTableName(pdocTableName);
    pdocTableName->setWidget(m_formTableName);
    pdocTableName->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    this->addDockWidget(Qt::LeftDockWidgetArea, pdocTableName);

    pdocRequestDb = new QDockWidget("Данные:", this);
    m_formRequestDb = new FormRequestDb(pdocRequestDb);
    m_formRequestDb->setMinimumSize(900, 500);
    //m_formRequestDb->setMinimumWidth(800);
    pdocRequestDb->setWidget(m_formRequestDb);
    pdocRequestDb->setFeatures(QDockWidget::DockWidgetMovable | QDockWidget::DockWidgetFloatable);
    this->addDockWidget(Qt::RightDockWidgetArea, pdocRequestDb);

    connect(m_formCreateDb, SIGNAL(signal_openDb(QString,QString,int,QString,QString,QString)),
            SLOT(slot_openDb(QString,QString,int,QString,QString,QString)));
    connect(m_formCreateDb, SIGNAL(signal_openDb(QString,QString)),
            SLOT(slot_openDb(QString,QString)));
    connect(m_formCreateDb, SIGNAL(signal_clearNameListTableDb()),
            SLOT(slot_clearNameListTableDb));

    connect(m_formTableName, SIGNAL(signal_selectTable(QString)),
            SLOT(slot_selectTable(QString)));

    // ---------------------
    connect(m_formRequestDb, SIGNAL(signal_requestDb(QString, bool)),
            SLOT(slot_requestDb(QString, bool)));

    connect(m_formRequestDb, SIGNAL(signal_updateTable(QString)),
            SLOT(slot_selectTable(QString)));

    connect(m_formRequestDb, SIGNAL(signal_updateDb(QString)),
            SLOT(slot_updataDb(QString)));
    // ---------------------
}

ManagerDB::~ManagerDB()
{
    delete ui;
}

QToolBar *ManagerDB::createToolBar()
{
    QToolBar* ptb = new QToolBar("lin");
    ptb->addAction("1", this, SLOT());
    ptb->addAction("2", this, SLOT());
    return ptb;
}

void ManagerDB::slot_openDb(const QString addDataBase, const QString name_db,
                            const int port, const QString hostName,
                            const QString userName, const QString passwd)
{
    try
    {
        if (m_frontDb.openDb(addDataBase, name_db, port, hostName, userName, passwd))
        {
            m_formTableName->redrawListTableName(m_frontDb.tableName());
            m_formCreateDb->dataInfo("База данных: " + name_db + " - открыта!");

            m_formRequestDb->enabledButton(true);
        }
        else
        {
            m_formCreateDb->dataInfo("База данных: " + name_db + " - открыть не удалось!");
        }
    }
    catch (QString strError)
    {
        m_formCreateDb->dataInfo(strError);
    }
}

void ManagerDB::slot_selectTable(const QString &tableName)
{
    try
    {
        m_formRequestDb->setColumnName(m_frontDb.selectColumnName(tableName));
        m_formRequestDb->setDataTable(m_frontDb.selectTable(tableName));
        m_formRequestDb->setTableName(tableName);
        m_formRequestDb->setCountRow(m_frontDb.getNumberRow());
        m_formRequestDb->selectTable();
    }
    catch (QString strError)
    {
        m_formCreateDb->dataInfo("\n При выполнение запроса возникла ошибка: \n" + strError);
    }
}

void ManagerDB::slot_updataDb(const QString &strQuery)
{
    if (m_frontDb.requestDb(strQuery))
    {
        m_formCreateDb->dataInfo("Запрос выполнен!");
    }
}

void ManagerDB::slot_clearNameListTableDb()
{
    m_formTableName->clearListNameTable();
}

void ManagerDB::slot_requestDb(const QString &strQuery, bool flagSelect)
{
    try
    {
        if (flagSelect)
        {
            m_formRequestDb->resultData(m_frontDb.requestDb_select(strQuery));
        }
        else
        {
            m_frontDb.requestDb(strQuery);
        }
    }
    catch (QString strError)
    {
        m_formCreateDb->dataInfo("\n При выполнение запроса возникла ошибка: \n" + strError);
    }
}
