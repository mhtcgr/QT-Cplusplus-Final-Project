#ifndef SHOP_H
#define SHOP_H

#include <QMainWindow>

namespace Ui {
class Shop;
}

class Shop : public QMainWindow
{
    Q_OBJECT

public:
    explicit Shop(QWidget *parent = nullptr);
    ~Shop();
    void updateCoinLabel();
signals:
    void addMoreMineRequested();
    void doubleValueRequested();
    void backM();
    void makeCentreBigger();
public slots:
    void updateM();
private:
    Ui::Shop *ui;
};

#endif // SHOP_H
