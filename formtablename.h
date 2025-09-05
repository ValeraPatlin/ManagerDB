#ifndef FORMTABLENAME_H
#define FORMTABLENAME_H

#include <QWidget>
#include <QStringList>
#include <QDebug>

namespace Ui {
class FormTableName;
}


/*!
 * \brief The FormTableName class - для отображения списка таблик базы данных
 */
class FormTableName : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \brief FormTableName - конструктор
     * \param parent
     */
    explicit FormTableName(QWidget *parent = 0);
    ~FormTableName();

    /*!
     * \brief redrawListTableName - заполнение widget списком таблиц
     * \param tableName - список таблиц
     */
    void redrawListTableName(const QStringList& tableName);

    /*!
     * \brief clearListNameTable - очистка списка таблиц
     */
    void clearListNameTable();

signals:
    /*!
     * \brief signal_selectTable - сигналь для отправки названия таблицы
     * \param tableName - название таблицы
     */
    void signal_selectTable(const QString& tableName);

private slots:
    /*!
     * \brief on_lw_tableName_doubleClicked - для выбора таблицы
     * \param index
     */
    void on_lw_tableName_doubleClicked(const QModelIndex &index);

private:
    Ui::FormTableName *ui;
};

#endif // FORMTABLENAME_H
