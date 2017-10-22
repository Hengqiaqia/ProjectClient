#include "NetworkConfigurationDialog.h"
#include "ui_NetworkConfigurationDialog.h"

NetworkConfigurationDialog::NetworkConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NetworkConfigurationDialog)
{
    ui->setupUi(this);
}

NetworkConfigurationDialog::~NetworkConfigurationDialog()
{
    delete ui;
}
