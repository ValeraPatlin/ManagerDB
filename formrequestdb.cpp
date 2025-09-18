#include "formrequestdb.h"
#include "ui_formrequestdb.h"

FormRequestDb::FormRequestDb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormRequestDb)
{
    ui->setupUi(this);

    enabledButton(false);

    ui->te_result->setTextInteractionFlags(Qt::TextSelectableByMouse);

    // ----------------
    // установка QSplitter
    splitter = new QSplitter(Qt::Vertical, this);
    splitter->addWidget(ui->gb_requestDb);
    splitter->addWidget(ui->gb_answerDb);
    splitter->setOpaqueResize(false);
    splitter->setHandleWidth(10);
    ui->vl_box_forSplitter->addWidget(splitter);
}

FormRequestDb::~FormRequestDb()
{
    delete ui;
}




void FormRequestDb::clearTable()
{
    ui->tw_infoDb->clear();
    ui->tw_infoDb->setColumnCount(0);
    ui->tw_infoDb->setRowCount(0);
}

void FormRequestDb::setColumnName(const QStringList &column)
{
    m_columnName = column;
}

void FormRequestDb::setDataTable(const QStringList &data)
{
    m_dataTable = data;
}

void FormRequestDb::setCountRow(const unsigned int count)
{
    m_countRow = count;
}

void FormRequestDb::setTableName(const QString &tableName)
{
    m_tableName = tableName;
}

bool FormRequestDb::selectTable()
{
    ui->tw_infoDb->clear();
    ui->tw_infoDb->setColumnCount(m_columnName.size());
    ui->tw_infoDb->setHorizontalHeaderLabels(m_columnName);
    ui->tw_infoDb->setRowCount(m_countRow);

    for (int i = 0; i < m_countRow; ++ i)
    {
        QStringList list;
        list = m_dataTable.at(i).split(", ");

        for (int j = 0; j < m_columnName.size(); ++j)
        {
            QTableWidgetItem* item;
            item = new QTableWidgetItem(list.at(j));
            ui->tw_infoDb->setItem(i, j, item);
        }
    }
    return true;
}

bool FormRequestDb::resultData(const QStringList &data)
{
    ui->te_result->append("Получены данные:\n");
    for (const QString& elem : data)
    {
        ui->te_result->append(elem);
    }
    ui->te_result->append("\n Данные выведены.");
    return true;
}


void FormRequestDb::on_pb_startRequestDb_clicked()
{
    QStringList request = ui->te_requestDb->toPlainText().split(" ");

    if (request.contains("SELECT"))
    {
        emit signal_requestDb(ui->te_requestDb->toPlainText(), true);
    }
    else
    {
        emit signal_requestDb(ui->te_requestDb->toPlainText(), false);
    }
}


void FormRequestDb::on_pb_update_clicked()
{
    QString strQuery;
    QString strWhere;
    int column = 0;

    QStringList list;

    for (int row = 0; row < ui->tw_infoDb->rowCount(); ++row)
    {
        strQuery = "UPDATE " + m_tableName + " SET ";
        strWhere = "WHERE ";
        int i = 0;
        list = m_dataTable.at(column).split(", ");

        for (int col = 0; col < ui->tw_infoDb->columnCount(); ++col)
        {
            QTableWidgetItem* item = ui->tw_infoDb->item(row, col);

            if (item)
            {
                strQuery += m_columnName.at(i) + "='" + item->text();
                strWhere += m_columnName.at(i) + "='" + list.at(i++);

                if (i != ui->tw_infoDb->columnCount())
                {
                    strQuery += "', ";
                    strWhere += "' and ";
                }
                else
                {
                    strQuery += "' ";
                    strWhere += "'";
                }
            }
        }
        ++column;
        strQuery += strWhere + ";";

        emit signal_updateDb(strQuery);
        strQuery.clear();
        strWhere.clear();
    }
    emit signal_updateTable(m_tableName);
}


void FormRequestDb::enabledButton(bool flag)
{
    ui->pb_update->setEnabled(flag);
    ui->pb_startRequestDb->setEnabled(flag);
    ui->cb_comSQL->setEnabled(flag);
}



void FormRequestDb::on_cb_comSQL_activated(const QString &arg1)
{
    QString strQuery;

    if (arg1 == "CREATE")
    {
        strQuery = "CREATE TABLE <name_table> (<name_field> <type_data> NOT NULL,"
                   "PRIMARY KEY (<name>));";
    }
    else if (arg1 == "SELECT")
    {
        strQuery = "SELECT <name_attribute> FROM <name_table>;";
    }
    else if (arg1 == "INSERT")
    {
        strQuery = "INSERT INTO <name_table> (<name_attribute>) VALUES (<value>);";
    }
    else if (arg1 == "UPDATE")
    {
        strQuery = "UPDATE <name_table> SET <name_attribute> = <value> WHERE <criterion>;";
    }
    else if (arg1 == "DELETE")
    {
        strQuery = "DELETE FROM <name_table> WHERE <criterion>;";
    }
    else
    {
        strQuery.clear();
    }
    ui->te_requestDb->clear();
    ui->te_requestDb->append(strQuery);
}
