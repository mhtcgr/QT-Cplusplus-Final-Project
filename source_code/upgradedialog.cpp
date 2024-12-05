#include "upgradedialog.h"
#include "ui_upgradedialog.h"

UpgradeDialog::~UpgradeDialog()
{
    delete ui;
}
#include "upgradedialog.h"

UpgradeDialog::UpgradeDialog(QWidget *parent,int phase) : QDialog(parent),phase(phase), ui(new Ui::UpgradeDialog){
    ui->setupUi(this);
    connect(ui->pushButton, &QPushButton::clicked, this, &UpgradeDialog::upgradeOption1);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &UpgradeDialog::upgradeOption2);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &UpgradeDialog::upgradeOption3);
    setStyleSheet("QDialog { background-image: url(:/gk/Screen05.png); }");
    setFixedSize(800, 600);
}
