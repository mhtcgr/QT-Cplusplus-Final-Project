#include "mainscene.h"
#include "ui_mainscene.h"
#include "playscene.h"
#include <QPainter>
#include <QTimer>
#include <QImage>
#include "QFile"
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    this->setWindowTitle("shapez");


    //设置标题图片this->setWindowIcon();
    this->setFixedSize(800,600);

    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });//绑定到退回到主菜单，还没实现
    connect(ui->actionquit2,&QAction::triggered,[=](){
        this->close();
    });
    gameState = new PlayScene();
    //监听关卡返回按钮的信号
    connect(gameState, &PlayScene::backMainScene,this,[=](){
        this->show();
    });
    shop = new Shop();
    connect(shop,&Shop::backM,this,[=](){
        qDebug() << "backMain";
        this->show();
    });
    connect(ui->pushButton,&QPushButton::clicked,[=](){//新游戏
        PlayScene::money = 500;
        PlayScene::timeOfCutter=60;
        PlayScene::timeOfBelt=30;
        PlayScene::timeOfMiner=20;
        PlayScene::typeNeeded=cuttable;
        PlayScene::score=0;
        PlayScene::phase=0;
        PlayScene::upgrade1=0;
        PlayScene::upgrade2=0;
        Mine::value=1;
        PlayScene::upgrade3=0;
        for(int j=18;j<=22;j++){
            gameState->gridVector[j][22] = new grid(22 * gridSize,j * gridSize,0,0);//a centre lies on here
        }
        for(int j=18;j<=22;j++){
            gameState->gridVector[18][j] = new grid(j * gridSize,18 * gridSize,0,0);//a centre lies on here
        }
        gameState->scen->removeItem(gameState->centre);
        int p=gameState->centre->phase;
        delete gameState->centre;
        gameState->centre = new Centre(p,0);
        gameState->scen->addItem(gameState->centre);
        gameState->textItem->setPos(840,640);
        gameState->moneyItem->setPos(830,570);
        for (int i = 0; i <= 32; ++i) {
            for (int j = 0; j <= 40; ++j) {
                if(gameState->deviceVector[i][j]){
                    gameState->scen->removeItem(gameState->deviceVector[i][j]);
                    gameState->deviceVector[i][j]=nullptr;
                }

            }
        }
        for(int i=10;i<=14;i++){
            gameState->scen->removeItem(gameState->gridVector[i][13]);
            gameState->gridVector[i][13]= new grid(13 * gridSize,i * gridSize,0,0);
            gameState->scen->addItem(gameState->gridVector[i][13]);
        }
        //
        for(int i=17;i<=22;i++){
            for(int j=26;j<=27;j++){
                gameState->scen->removeItem(gameState->gridVector[i][j]);
                gameState->gridVector[i][j]= new grid(j * gridSize,i * gridSize,0,0);
                gameState->scen->addItem(gameState->gridVector[i][j]);
            }
        }
        update();
        this->hide();
        gameState->QMainWindow::show();
    });
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){//继续游戏
        PlayScene::timeOfCutter=60;
        PlayScene::timeOfBelt=30;
        PlayScene::timeOfMiner=20;
        PlayScene::typeNeeded=cuttable;
        PlayScene::score=0;
        PlayScene::phase=0;
        for (int i = 0; i <= 32; ++i) {
            for (int j = 0; j <= 40; ++j) {
                if(gameState->mineVector[i][j]){
                    gameState->scen->removeItem(gameState->mineVector[i][j]);
                    gameState->mineVector[i][j]=nullptr;
                }
                if(gameState->deviceVector[i][j]){
                    gameState->scen->removeItem(gameState->deviceVector[i][j]);
                    gameState->deviceVector[i][j]=nullptr;
                }
            }
        }
        QFile file("save.txt");
        QString content;
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            content=in.readAll();
            file.close();
            qDebug() << "Text read from file: "<< content;

        }
        else{
            qDebug() << "Failed to open file for reading: " <<file.errorString();
        }
        QStringList stringList = content.split(" ");
        if(stringList.size()<1) return;
        //PlayScene::money=stringList[0].toInt();
        PlayScene::timeOfCutter=stringList[1].toInt();
        PlayScene::timeOfBelt=stringList[2].toInt();
        PlayScene::timeOfMiner=stringList[3].toInt();
        PlayScene::typeNeeded=stringList[4].toInt();
        PlayScene::score=stringList[5].toInt();
        PlayScene::phase=stringList[6].toInt();

        if(PlayScene::upgrade1==1)
            gameState->addMoreMine();
        if(PlayScene::upgrade2==1)
            Mine::value=2;
        if(PlayScene::upgrade3==1)
            gameState->centreBigger();
        // int o=10;
        // for (int i = 0; i <= 32; ++i) {
        //     for (int j = 0; j <= 40; ++j) {
        //         int dir = stringList[o].toInt();
        //         o++;
        //         QString name=stringList[o];
        //         o++;
        //         if(name=="miner")
        //             gameState->deviceVector[i][j]=new Miner(j*gridSize,i*gridSize,90*dir);
        //         if(name=="cutter"){
        //             if(dir==UP){
        //                 gameState->deviceVector[i][j]=new Miner(j*gridSize,i*gridSize,90*dir);
        //                 gameState->deviceVector[i][j+1]=gameState->deviceVector[i][j];
        //             }
        //         }
        //         if(name=="trashcan")
        //             gameState->deviceVector[i][j]=new TrashCan(j*gridSize,i*gridSize,90*dir);
        //         if(name=="Belt")
        //             gameState->deviceVector[i][j]=new TrashCan(j*gridSize,i*gridSize,90*dir);

        //     }
        // }
        update();
        this->hide();
        gameState->QMainWindow::show();
    });

    connect(ui->pushButton_3,&QPushButton::clicked,[=](){//升级商店
        this->hide();
        shop->Shop::show();
    });
    connect(ui->pushButton_4,&QPushButton::clicked,[=](){//退出
        this->close();
    });
}




MainScene::~MainScene()
{
    delete ui;
}
