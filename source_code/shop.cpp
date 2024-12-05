#include "shop.h"
#include "ui_shop.h"
#include "playscene.h"
#include "QMessageBox"
Shop::Shop(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Shop)
{
    ui->setupUi(this);
    ui->moneyLabel->setPixmap(QPixmap(""));
    // 设置主窗口标题
    setWindowTitle("商店");
    updateCoinLabel();
    connect(ui->pushButton,&QPushButton::clicked,this,[=](){
        if (PlayScene::money >= 50) {
            // 触发信号
            emit addMoreMineRequested();
            // 删除按钮
            ui->pushButton->deleteLater();
            PlayScene::money-=50;
            updateCoinLabel();
            QMessageBox::information(this, "购买成功", "购买成功！");
        }else {
            // 弹出错误对话框
            QMessageBox::critical(this, "错误", "你的金币不足", QMessageBox::Ok);
        }
    });
    connect(ui->pushButton_3,&QPushButton::clicked,this,[=](){
        if (PlayScene::money >= 50) {
            // 触发信号
            emit doubleValueRequested();
            // 删除按钮
            ui->pushButton_3->deleteLater();
            PlayScene::money-=50;
            updateCoinLabel();
            QMessageBox::information(this, "购买成功", "购买成功！");
        }else {
            // 弹出错误对话框
            QMessageBox::critical(this, "错误", "你的金币不足", QMessageBox::Ok);
        }
    });
    connect(ui->pushButton_2,&QPushButton::clicked,this,[=](){
        hide();
        emit backM();
    });
    connect(ui->pushButton_4,&QPushButton::clicked,this,[=](){
        if (PlayScene::money >= 50) {
            // 触发信号
            emit makeCentreBigger();
            // 删除按钮
            ui->pushButton_4->deleteLater();
            PlayScene::money-=50;
            updateCoinLabel();
            QMessageBox::information(this, "购买成功", "购买成功！");
        }else {
            // 弹出错误对话框
            QMessageBox::critical(this, "错误", "你的金币不足", QMessageBox::Ok);
        }
    });
}

Shop::~Shop()
{
    delete ui;
}
void Shop::updateM(){
    updateCoinLabel();
}
void Shop::updateCoinLabel() {
    ui->moneyLabel->setText("您的金币数量: " + QString::number(PlayScene::money));
}
