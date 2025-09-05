#include "formtablename.h"
#include "ui_formtablename.h"

FormTableName::FormTableName(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FormTableName)
{
    ui->setupUi(this);

    ui->lw_tableName->setMinimumWidth(150);
}

FormTableName::~FormTableName()
{
    delete ui;
}

void FormTableName::redrawListTableName(const QStringList &tableName)
{
    ui->lw_tableName->clear();
    QListWidgetItem* elem = nullptr;

    for (auto str : tableName)
    {
        elem = new QListWidgetItem(str, ui->lw_tableName);
    }
}

void FormTableName::clearListNameTable()
{
    ui->lw_tableName->clear();
}

void FormTableName::on_lw_tableName_doubleClicked(const QModelIndex &index)
{
    emit signal_selectTable(index.data().toString());
}
