#ifndef FORMCREATEDB_H
#define FORMCREATEDB_H


#include <QWidget>
#include <QString>
#include <QStringList>
#include <QSettings>
#include <QCompleter>
#include <QFileDialog>
#include <QTextCharFormat>
#include <QTextCursor>
#include <QColor>
#include <QDebug>

namespace Ui {
class FormCreateDB;
}

/*!
 * \brief The FormCreateDB class для подключения к базе данных
 */
class FormCreateDB : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief FormCreateDB конструктор по умолчанию
     * \param parent
     */
    explicit FormCreateDB(QWidget *parent = 0);
    ~FormCreateDB();


    /*!
     * \brief dataInfo - для вывода сообщений и ошибок
     * \param strInfo - сообщение для вывода
     * \param flagError - флаг, является ли принятое сообщение ошибкой,
     * false - обычное сообщение
     * true - сообщение с ошибкой
     * по умолчанию всегда false
     */
    void dataInfo(const QString& strInfo, bool flagError = false);

signals:
    /*!
     * \brief signal_openDb - сигнал отправляет данные для подключение к базе данных
     * \param addDataBase - тип базы данных
     * \param name_db - имя базы данных
     * \param port - порт
     * \param hostName - ip адресс
     * \param userName - имя пользователя
     * \param passwd - пароль
     */
    void signal_openDb(const QString addDataBase, const QString name_db, const int port,
                       const QString hostName, const QString userName, const QString passwd);

    /*!
     * \brief signal_openDb - сигнал отправляет данные для подключение к базе данных
     * \param addDataBase - тип базы данных
     */
    void signal_openDb(const QString addDataBase, const QString pathDb);

private slots:
    /*!
     * \brief on_pb_openAndCloseDb_clicked - формирование данных для подключение к базе данных
     */
    void on_pb_openAndCloseDb_clicked();

    /*!
     * \brief on_pb_clear_NameDb_clicked - удаление имяни базы данных из сохранённых
     */
    void on_pb_clear_NameDb_clicked();

    /*!
     * \brief on_pb_clear_idDb_clicked - удаление ip адреса из сохранённых
     */
    void on_pb_clear_idDb_clicked();

    /*!
     * \brief on_pb_clear_portDb_clicked - удаление порта из сохранённых
     */
    void on_pb_clear_portDb_clicked();

    /*!
     * \brief on_pb_clear_nameUser_clicked - удаление имяни пользователя из сохранённых
     */
    void on_pb_clear_nameUser_clicked();

    /*!
     * \brief on_cb_showPasswd_clicked - показ пароля
     * \param checked - нажата ли галочка
     */
    void on_cb_showPasswd_clicked(bool checked);

    /*!
     * \brief on_cb_typeDatabase_currentTextChanged - какая база данных выбрана
     * \param arg1 - тип базы данных
     */
    void on_cb_typeDatabase_currentTextChanged(const QString &arg1);

    /*!
     * \brief on_pb_pathDb_clicked - узазать путь до базы данных sqlite
     */
    void on_pb_pathDb_clicked();

private:
    Ui::FormCreateDB *ui;

    int m_type_db{};          //!< номер типв базы данных
    QStringList m_name_db;    //!< имя базы данных
    QStringList m_hostName;   //!< ip адрес базы данных
    QStringList m_userName;   //!< имяни пользователя
    QStringList m_passwd;     //!< пароль базы данных
    QStringList m_port;       //!< порт базы данных
    QString m_pathSqlite;     //!< путь до базы данных для SQLite

    /*!
     * \brief checkIpAddress проверка ip адреса на корректность
     * \param strIp - ip адресс
     * \return true - ip адресс корректен, false - ip адресс не корректен
     */
    bool checkIpAddress(const QString& strIp);

    /*!
     * \brief readingConfig запись данных в конфиг для базы данных
     * \param path - путь до конфига базы данных
     */
    void readingConfig(const QString& path = "./config.conf");

    /*!
     * \brief writeConfig считывание данных из конфиг для базы данных
     * \param path - путь до конфига базы данных
     */
    void writeConfig(const QString& path = "./config.conf");
};

#endif // FORMCREATEDB_H
