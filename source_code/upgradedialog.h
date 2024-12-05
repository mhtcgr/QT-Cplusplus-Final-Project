#ifndef UPGRADEDIALOG_H
#define UPGRADEDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
namespace Ui {
class UpgradeDialog;
}
class UpgradeDialog : public QDialog {
    Q_OBJECT

public:
    int phase;
    UpgradeDialog(QWidget *parent = nullptr,int phase=1);
    ~UpgradeDialog();

signals:
    void upgradeOption1();
    void upgradeOption2();
    void upgradeOption3();
private:
    Ui::UpgradeDialog *ui;
};


#endif // UPGRADEDIALOG_H
