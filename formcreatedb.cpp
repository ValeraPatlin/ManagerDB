#include "formcreatedb.h"
#include "ui_formcreatedb.h"

FormCreateDB::FormCreateDB(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormCreateDB)
{
    ui->setupUi(this);

    readingConfig();

    ui->cb_typeDatabase->setCurrentIndex(m_type_db);

    ui->cb_nameDb->setEditable(true);
    ui->cb_nameDb->setInsertPolicy(QComboBox::InsertAtTop);
    ui->cb_nameDb->setMinimumWidth(250);
    ui->cb_nameDb->addItems(m_name_db);

    ui->cb_ipDb->setEditable(true);
    ui->cb_ipDb->setInsertPolicy(QComboBox::InsertAtTop);
    ui->cb_ipDb->setMinimumWidth(250);
    ui->cb_ipDb->addItems(m_hostName);

    QStringList list;
    list << "127.0.0.1";
    QCompleter completer(list, this);
    completer.setCaseSensitivity(Qt::CaseInsensitive);
    ui->cb_ipDb->setCompleter(&completer);

    ui->cb_portDb->setEditable(true);
    ui->cb_portDb->setInsertPolicy(QComboBox::InsertAtTop);
    ui->cb_portDb->setMinimumWidth(250);
    ui->cb_portDb->addItems(m_port);

    ui->cb_nameUserDb->setEditable(true);
    ui->cb_nameUserDb->setInsertPolicy(QComboBox::InsertAtTop);
    ui->cb_nameUserDb->setMinimumWidth(250);
    ui->cb_nameUserDb->addItems(m_userName);

    ui->le_passwdDb->setMinimumWidth(250);
    ui->le_passwdDb->setEchoMode(QLineEdit::Password);
    ui->le_passwdDb->setClearButtonEnabled(true);

    // -------
    ui->te_info->setReadOnly(true);
    ui->te_info->setLineWrapMode(QTextEdit::WidgetWidth);
    ui->te_info->setWordWrapMode(QTextOption::WordWrap);
}

FormCreateDB::~FormCreateDB()
{
    delete ui;
}

void FormCreateDB::dataInfo(const QString &strInfo)
{
    ui->te_info->append(strInfo);
}

void FormCreateDB::on_pb_openAndCloseDb_clicked()
{
    bool ok_toInt{};
    int port = ui->cb_portDb->currentText().toInt(&ok_toInt);

    if (!ok_toInt || port <= 0 || port > 65535)
    {
        dataInfo("Внимание!\n Порт для подключения указан не верно!");
        return;
    }

    if (!checkIpAddress(ui->cb_ipDb->currentText()))
    {
        dataInfo("Внимание!\n Ip адрес указан не верно!");
        return;
    }

    QString str_typeDB;

    if (ui->cb_typeDatabase->currentText() == "SQLite")
    {
        str_typeDB = "QSQLITE";
    }
    else if (ui->cb_typeDatabase->currentText() == "PosgreSQL")
    {
        str_typeDB = "QPSQL";
    }
    else if (ui->cb_typeDatabase->currentText() == "MySQL")
    {
        str_typeDB = "QMYSQL";
    }

    if (ui->cb_saveData->isChecked())
    {
        m_type_db = ui->cb_typeDatabase->currentIndex();

        if (!m_name_db.contains(ui->cb_nameDb->currentText()))
        {
            m_name_db << ui->cb_nameDb->currentText();
        }

        if (!m_hostName.contains(ui->cb_ipDb->currentText()))
        {
            m_hostName << ui->cb_ipDb->currentText();
        }

        if (!m_userName.contains(ui->cb_nameUserDb->currentText()))
        {
            m_userName << ui->cb_nameUserDb->currentText();
        }

        if (!m_port.contains(ui->cb_portDb->currentText()))
        {
            m_port << ui->cb_portDb->currentText();
        }

        writeConfig();
    }

    emit signal_openDb(str_typeDB, ui->cb_nameDb->currentText(), port, ui->cb_ipDb->currentText(),
                       ui->cb_nameUserDb->currentText(), ui->le_passwdDb->text());
    emit signal_clearNameListTableDb();
}


// проверка ip адреса
bool FormCreateDB::checkIpAddress(const QString &strIp)
{
    if (strIp == "")
    {
        return false;
    }
    else
    {
        QString strReg = "^(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])\\.)"
                         "{3}([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5])$";
        QRegExp reg(strReg);

        if (reg.exactMatch(strIp))
        {
            return true;
        }
    }
    return false;
}

void FormCreateDB::readingConfig(const QString &path)
{
    QSettings m_settings(path, QSettings::IniFormat);
    m_settings.beginGroup("Settings");

    m_type_db = m_settings.value("addDataBase", 0).toInt();
    m_name_db = m_settings.value("name_db", QStringList({""})).toStringList();
    m_hostName = m_settings.value("hostName", QStringList({"", "127.0.0.1"})).toStringList();
    m_userName = m_settings.value("userName", QStringList({"", "postgres"})).toStringList();
    m_port = m_settings.value("port", QStringList({"", "5432"})).toStringList();

    m_settings.endGroup();
    m_settings.sync();
}

void FormCreateDB::writeConfig(const QString &path)
{
    QSettings m_settings(path, QSettings::IniFormat);
    m_settings.beginGroup("Settings");

    m_settings.setValue("addDataBase", m_type_db);
    m_settings.setValue("name_db", m_name_db);
    m_settings.setValue("hostName", m_hostName);
    m_settings.setValue("userName", m_userName);
    m_settings.setValue("post", m_port);

    m_settings.endGroup();
    m_settings.sync();
}

void FormCreateDB::on_pb_clear_NameDb_clicked()
{
    m_name_db.removeAll(ui->cb_nameDb->currentText());
    ui->cb_nameDb->clearEditText();
    writeConfig();
}

void FormCreateDB::on_pb_clear_idDb_clicked()
{
    m_hostName.removeAll(ui->cb_ipDb->currentText());
    ui->cb_ipDb->clearEditText();
    writeConfig();
}

void FormCreateDB::on_pb_clear_portDb_clicked()
{
    m_port.removeAll(ui->cb_portDb->currentText());
    ui->cb_portDb->clearEditText();
    writeConfig();
}

void FormCreateDB::on_pb_clear_nameUser_clicked()
{
    m_userName.removeAll(ui->cb_nameUserDb->currentText());
    ui->cb_nameUserDb->clearEditText();
    writeConfig();
}

void FormCreateDB::on_cb_showPasswd_clicked(bool checked)
{
    if (checked)
    {
        ui->le_passwdDb->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        ui->le_passwdDb->setEchoMode(QLineEdit::Password);
    }
}
