#include "playscene.h"
#include "ui_playscene.h"
#include "cutter.h"
#include "belt.h"
#include <QStackedWidget>
#include <QboxLayout>
#include "upgradedialog.h"
#include "QFile"
#include "QMessageBox"
#include <QSoundEffect>
#include "rotater.h"
int PlayScene::upgrade1=0;
int PlayScene::upgrade2=0;
int PlayScene::upgrade3=0;
int PlayScene::timeOfCutter=60;
int PlayScene::timeOfBelt=30;
int PlayScene::timeOfMiner=45;
int PlayScene::typeNeeded = cuttable;
int PlayScene::score=0;
int PlayScene::phase=0;
QMap<QString, int> deviceMap={{"belt",1},{"cutter",2},{"miner",3},{"trashcan",4},{"rotator",5}};
int PlayScene::money = 500;
bool PlayScene::isDragging=false;
int PlayScene::dragAngle = 0;
QString PlayScene::dragText = "";
PlayScene::PlayScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PlayScene)
{
    ui->setupUi(this);
    this->setWindowTitle("shapez");
    this->setFixedSize(800,640);
    scen = new MyScene();
    cs = new CardScene();
    connect(scen,&MyScene::press,this,&PlayScene::addD);
    scen->setSceneRect(QRect(0,0,2*this->width(),2*this->height()));
    cs->setSceneRect(QRect(0,600,this->width(),gridSize));
    view1.setFixedHeight(600);
    view2.setFixedHeight(40);
    view1.setFixedWidth(800);
    view2.setFixedWidth(800);
    view1.setScene(scen);
    view2.setScene(cs);
    view1.setParent(this);
    view2.setParent(this);
    view1.show();
    view2.show();
    view2.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view2.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    textItem = new QGraphicsTextItem("0");
    moneyItem = new QGraphicsTextItem(QString::number(money));
    textItem->setZValue(6);
    moneyItem->setZValue(6);
    moneyItem->setPos(830,570);
    textItem->setPos(840,640);
    QFont font("Arial", 15, QFont::Bold);
    textItem->setFont(font);
    moneyItem->setFont(font);
    scen->addItem(textItem);
    scen->addItem(moneyItem);
    for (int j = 0; j <= 32; j++) {
        for (int i = 0; i <= 40; i++) {
            grid* g;
            if((i >= 18 && i <= 21) && (j >= 14 && j <= 17)){
                //centre
                g= new grid(i * gridSize,j * gridSize,0,1);//a centre lies on here
            }
            else if((i==16&&j==10)||(i==15&&j==10))
                g= new grid(i * gridSize,j * gridSize,1,0);
            else if((i>=16&&i<=20)&&j==23){
                 g= new grid(i * gridSize,j * gridSize,2,0);
            }
            else g=new grid(i*gridSize,j*gridSize,0,0);
            gridVector[j][i]=g;
            deviceVector[j][i]=nullptr;
            mineVector[j][i]=nullptr;
            scen->addItem(g);
        }
    }//初始化网格
    centre=new Centre(phase,0);
    Card* card_r = new Card(260,600,"rotator",QPixmap(":/gk/rotater.png"));
    Card* card_cutter=new Card(300,600,"cutter",QPixmap(":/image/cutter.png"));
    Card* card_miner=new Card(340,600,"miner",QPixmap(":/image/miner.png"));
    Card* card_belt=new Card(380,600,"belt",QPixmap(":/image/belt.png"));//初始化下方卡片
    Card* card_trashcan=new Card(420,600,"trashcan",QPixmap(":/Trash.png"));
    cs->addItem(card_r);
    cs->addItem(card_trashcan);
    cs->addItem(card_miner);
    cs->addItem(card_cutter);
    cs->addItem(card_belt);
    connect(card_r,&Card::pressLeft,this,&PlayScene::handleLeftButtonClicked);
    connect(card_trashcan,&Card::pressLeft,this,&PlayScene::handleLeftButtonClicked);
    connect(card_cutter,&Card::pressLeft,this,&PlayScene::handleLeftButtonClicked);
    connect(card_miner,&Card::pressLeft,this,&PlayScene::handleLeftButtonClicked);//连接底部的卡片和playscene的左键
    connect(card_belt,&Card::pressLeft,this,&PlayScene::handleLeftButtonClicked);
    scen->addItem(centre);//因为加入了centre，所以这一块不能加入东西
    QTimer * timer = new QTimer(this);//设置一个定时器
    hideButton = new RetButton();
    saveButton = new SaveButton();
    cs->addItem(saveButton);
    cs->addItem(hideButton);
    connect(hideButton,&RetButton::backM,this,[=](){
        hide();
        emit backMainScene();
    });//连接返回按钮和返回主页面
    connect(saveButton,&SaveButton::saveFile,this,[=](){
        QFile file("save.txt");
        QString content = "";

        content +=QString::number(money);
        content+=" ";
        content +=QString::number(timeOfCutter);
        content+=" ";
        content +=QString::number(timeOfBelt);
        content+=" ";
        content +=QString::number(timeOfMiner);
        content+=" ";
        content +=QString::number(typeNeeded);
        content+=" ";
        content +=QString::number(score);
        content+=" ";
        content +=QString::number(phase);
        content+=" ";
        content +=QString::number(upgrade1);
        content+=" ";
        content +=QString::number(upgrade2);
        content+=" ";
        content +=QString::number(upgrade3);
        content+=" ";
        // for (int i = 0; i <= 32; ++i) {
        //     for (int j = 0; j <= 40; ++j) {

        //         if(deviceVector[i][j]==nullptr){
        //             content += "1";
        //             content+=" ";
        //             content+="null";
        //             content+=" ";
        //         }
        //         else{
        //             content += QString::number(deviceVector[i][j]->direct);
        //             content+=" ";
        //             content+=deviceVector[i][j]->GetClassType();
        //             content+=" ";
        //         }
        //     }
        // }
        if (file.open(QIODevice::WriteOnly)) {
            QTextStream out(&file);
            // 将数据写入文件
            out << content;
            file.close();
            QMessageBox::information(this, "存档成功", "存档成功！");
        }
    });//连接存档按钮和存档操作，然后还要加入一个对话框提示存档操作
    buttonText = new QGraphicsTextItem("返回");
    saveText = new QGraphicsTextItem("存档");
    saveText->setFont(QFont("Arial", 12));
    buttonText->setFont(QFont("Arial", 12));  // 设置字体大小
    buttonText->setPos(745,605);  // 调整文本位置
    saveText->setPos(695,605);
    cs->addItem(saveText);
    cs->addItem(buttonText);
    //添加音频
    //播放音频
    QSoundEffect *music = new QSoundEffect();
    music->setSource(QUrl::fromLocalFile(":/music.wav"));
    music->setLoopCount(QSoundEffect::Infinite);  //设置无限循环
    music->setVolume(0.5f);  //设置音量，在0到1之间
    //music->play();
    connect(timer, &QTimer::timeout, this,[=](){
        for(int i=0;i<=32;i++){
            for(int j=0;j<=40;j++){//遍历所有方格，如果是有矿物在传递，就传递给下一个方向
                moneyItem->setPlainText(QString::number(money));
                auto a = deviceVector[i][j];
                if(gridVector[i][j]->mineType>0){//当前格有矿物，且有一个开采器，那么在这里添加一个mine
                    if(a!=nullptr&&a->GetClassType()=="Miner"){
                        deviceVector[i][j]->timeToDo=(deviceVector[i][j]->timeToDo+1)%timeOfMiner;
                        if(deviceVector[i][j]->timeToDo!=0)
                            continue;
                        //qDebug() << "yessssssss";
                        int c=gridVector[i][j]->mineType==2?0:1;
                        switch(a->direct){
                        case 0:{//向上,把矿物传到上面一格
                            if(deviceVector[i-1][j]!=nullptr&&deviceVector[i-1][j]->GetClassType()=="Belt"&&mineVector[i-1][j]==nullptr){
                                mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,c);//////////////////////////////////
                                scen->addItem(mineVector[i-1][j]);
                            }
                        }break;
                        case 1:{//向右,把矿物传到右边一格
                            if(deviceVector[i][j+1]!=nullptr&&deviceVector[i][j+1]->GetClassType()=="Belt"&&mineVector[i][j+1]==nullptr){
                                mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,c);
                                scen->addItem(mineVector[i][j+1]);
                            }
                        }break;
                        case 2:{//向下,把矿物传到下面一格
                            if(deviceVector[i+1][j]!=nullptr&&deviceVector[i+1][j]->GetClassType()=="Belt"&&mineVector[i+1][j]==nullptr){
                                mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,c);
                                scen->addItem(mineVector[i+1][j]);
                            }

                        }break;
                        case 3:{//向左,把矿物传到左边一格
                            if(deviceVector[i][j-1]!=nullptr&&deviceVector[i][j-1]->GetClassType()=="Belt"&&mineVector[i][j-1]==nullptr){
                                mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,c);
                                scen->addItem(mineVector[i][j-1]);
                            }
                        }break;
                        default:
                            break;
                        }
                    }
                }
                if(a){if(a->GetClassType()=="rotator")
                        if(mineVector[i][j]!=nullptr){
                            deviceVector[i][j]->timeToDo=(deviceVector[i][j]->timeToDo+1)%timeOfBelt;
                            if(deviceVector[i][j]->timeToDo!=0)
                                continue;
                            switch(a->direct){
                            case 0:{//向上,把矿物传到上面一格,如果是交付中心，那么money+=mine->value
                                if(mineVector[i-1][j]==nullptr){
                                    if(mineVector[i][j]->mineType==LeftHalf){
                                        qDebug() << "dhawdiawdi";
                                        mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,RightHalf);
                                    }

                                    else if(mineVector[i][j]->mineType==RightHalf)
                                        mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,LeftHalf);
                                    else
                                        mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i-1][j]);
                                }
                            }break;
                            case 1:{//向右,把矿物传到右边一格
                                if(mineVector[i][j+1]==nullptr){
                                    if(mineVector[i][j]->mineType==2)
                                        mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,3);
                                    else if(mineVector[i][j]->mineType==3)
                                        mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,2);
                                    else
                                        mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i][j+1]);
                                }
                            }break;
                            case 2:{//向下,把矿物传到下面一格
                                if(mineVector[i+1][j]==nullptr){
                                    if(mineVector[i][j]->mineType==2)
                                        mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,3);
                                    else if(mineVector[i][j]->mineType==3)
                                        mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,2);
                                    else
                                        mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i+1][j]);
                                }
                            }break;
                            case 3:{//向左,把矿物传到左边一格
                                if(mineVector[i][j-1]==nullptr){
                                    if(mineVector[i][j]->mineType==2)
                                        mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,3);
                                    else if(mineVector[i][j]->mineType==3)
                                        mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,2);
                                    else
                                        mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i][j-1]);
                                }
                            }break;
                            default:
                                break;
                            }
                            scen->removeItem(mineVector[i][j]);
                            delete mineVector[i][j];
                            mineVector[i][j]=nullptr;
                        }
                    if(a->GetClassType()=="Belt")
                        if(mineVector[i][j]!=nullptr){
                            deviceVector[i][j]->timeToDo=(deviceVector[i][j]->timeToDo+1)%timeOfBelt;
                            if(deviceVector[i][j]->timeToDo!=0)
                                continue;
                            switch(a->direct){
                            case 0:{//向上,把矿物传到上面一格,如果是交付中心，那么money+=mine->value
                                if(gridVector[i-1][j]->hasCentre==1){
                                    if(mineVector[i][j]->mineType==typeNeeded){
                                        score++;
                                        textItem->setPlainText(QString::number(score));
                                    }
                                    money+=mineVector[i][j]->value;
                                    emit updateMoneyRequested();
                                    moneyItem->setPlainText(QString::number(money));
                                    break;
                                }
                                if(mineVector[i-1][j]==nullptr){
                                    mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i-1][j]);
                                }
                            }break;
                            case 1:{//向右,把矿物传到右边一格
                                if(gridVector[i][j+1]->hasCentre==1){
                                    if(mineVector[i][j]->mineType==typeNeeded){
                                        score++;
                                        textItem->setPlainText(QString::number(score));
                                    }
                                    money+=mineVector[i][j]->value;
                                    emit updateMoneyRequested();
                                    moneyItem->setPlainText(QString::number(money));
                                    break;
                                }
                                qDebug() << " no score and 1";
                                if(mineVector[i][j+1]==nullptr){
                                    mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i][j+1]);
                                }

                            }break;
                            case 2:{//向下,把矿物传到下面一格
                                if(gridVector[i+1][j]->hasCentre==1){
                                    if(mineVector[i][j]->mineType==typeNeeded){
                                        score++;
                                        textItem->setPlainText(QString::number(score));
                                    }
                                    money+=mineVector[i][j]->value;
                                    emit updateMoneyRequested();
                                    moneyItem->setPlainText(QString::number(money));
                                    break;
                                }
                                qDebug() << "7777777777777wangxiasong";
                                if(mineVector[i+1][j]==nullptr){
                                    qDebug() << "wangxiasong";
                                    mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i+1][j]);
                                }
                            }break;
                            case 3:{//向左,把矿物传到左边一格
                                if(gridVector[i][j-1]->hasCentre==1){
                                    if(mineVector[i][j]->mineType==typeNeeded){
                                        score++;
                                        textItem->setPlainText(QString::number(score));
                                    }
                                    money+=mineVector[i][j]->value;
                                    emit updateMoneyRequested();
                                    moneyItem->setPlainText(QString::number(money));
                                    break;
                                }
                                if(mineVector[i][j-1]==nullptr){
                                    mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,mineVector[i][j]->mineType);
                                    scen->addItem(mineVector[i][j-1]);
                                }
                            }break;
                            default:
                                break;
                            }
                            scen->removeItem(mineVector[i][j]);
                            delete mineVector[i][j];
                            mineVector[i][j]=nullptr;
                            //qDebug() << " 在第" << i  << "格第" << j << "列" <<(mineVector[i][j] == nullptr);
                        }
                    if(a->GetClassType()=="cutter"){
                        if(mineVector[i][j]!=nullptr&&mineVector[i][j]->mineType==cuttable){
                            deviceVector[i][j]->timeToDo=(deviceVector[i][j]->timeToDo+1)%timeOfCutter;
                            if(deviceVector[i][j]->timeToDo!=0)
                                continue;
                            switch(a->direct){
                            case 0:{//向上,把矿物传到上面一格
                                if(deviceVector[i][j+1]==a&&(deviceVector[i-1][j]->GetClassType()=="Belt"||deviceVector[i-1][j]->GetClassType()=="trashcan")){//右边也是剪刀
                                    if(deviceVector[i-1][j+1]->GetClassType()=="Belt"||deviceVector[i-1][j+1]->GetClassType()=="trashcan"){
                                    mineVector[i-1][j]=new Mine((j)*gridSize,(i-1)*gridSize,LeftHalf);//新建cut之后的矿物//////////ing
                                    mineVector[i-1][j+1]=new Mine((j+1)*gridSize,(i-1)*gridSize,RightHalf);//不能再被切割了，所以cuttable==0
                                    scen->addItem(mineVector[i-1][j]);
                                    scen->addItem(mineVector[i-1][j+1]);
                                    }
                                }
                            }break;
                            case 1:{//向右,把矿物传到右边一格
                                if(deviceVector[i+1][j]==a&&(deviceVector[i+1][j+1]->GetClassType()=="Belt"||deviceVector[i+1][j+1]->GetClassType()=="trashcan")){
                                    if(deviceVector[i][j+1]->GetClassType()=="Belt"||deviceVector[i][j+1]->GetClassType()=="trashcan"){
                                        mineVector[i+1][j+1]=new Mine((j+1)*gridSize,(i+1)*gridSize,RightHalf);//
                                        scen->addItem(mineVector[i+1][j+1]);
                                        mineVector[i][j+1]=new Mine((j+1)*gridSize,(i)*gridSize,LeftHalf);
                                        scen->addItem(mineVector[i][j+1]);
                                    }
                                }
                            }break;
                            case 2:{//向下,把矿物传到下面一格
                                if(deviceVector[i][j-1]==a&&(deviceVector[i+1][j]->GetClassType()=="Belt"||deviceVector[i+1][j]->GetClassType()=="trashcan")){//左边也是剪刀
                                    if(deviceVector[i+1][j-1]->GetClassType()=="Belt"||deviceVector[i+1][j-1]->GetClassType()=="trashcan"){
                                        mineVector[i+1][j-1]=new Mine((j-1)*gridSize,(i+1)*gridSize,LeftHalf);//
                                        mineVector[i+1][j]=new Mine((j)*gridSize,(i+1)*gridSize,RightHalf);//
                                        scen->addItem(mineVector[i+1][j]);
                                        scen->addItem(mineVector[i+1][j-1]);
                                    }
                                }
                            }break;
                            case 3:{//向左,把矿物传到左边一格
                                if(deviceVector[i-1][j]==a&&(deviceVector[i][j-1]->GetClassType()=="Belt"||deviceVector[i][j-1]->GetClassType()=="trashcan")){//上边也是剪刀
                                    if(deviceVector[i+1][j-1]->GetClassType()=="Belt"||deviceVector[i+1][j-1]->GetClassType()=="trashcan"){
                                        mineVector[i][j-1]=new Mine((j-1)*gridSize,(i)*gridSize,LeftHalf);//新建cut之后的矿物//////////ing
                                        mineVector[i-1][j-1]=new Mine((j-1)*gridSize,(i+1)*gridSize,RightHalf);//
                                        scen->addItem(mineVector[i][j-1]);
                                        scen->addItem(mineVector[i-1][j-1]);
                                    }
                                }
                            }break;
                            default:
                                break;
                            }
                            scen->removeItem(mineVector[i][j]);
                            delete mineVector[i][j];
                            mineVector[i][j]=nullptr;
                            //qDebug() << " 在第" << i  << "格第" << j << "列" <<(mineVector[i][j] == nullptr);
                        }
                    }
                    if(a->GetClassType()=="trashcan"){
                        if(mineVector[i][j]!=nullptr){
                            scen->removeItem(mineVector[i][j]);
                            delete mineVector[i][j];
                            mineVector[i][j]=nullptr;
                        }
                    }
                }
                if(score==5 && centre->phase==0){
                    //进入阶段二
                    phase=1;
                    score=0;
                    textItem->setPlainText(QString::number(score));
                    typeNeeded++;
                    int u=centre->upgraded;
                    scen->removeItem(centre);
                    delete centre;
                    centre =new Centre(1,u);
                    scen->addItem(centre);
                    UpgradeDialog *upgradeDialog = new UpgradeDialog(this,1);
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption1, this, [=](){
                        timeOfMiner=(double)timeOfMiner/2;//加速开采器
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption2, this, [=](){
                        timeOfBelt=(double)timeOfBelt/2;//加速传送带
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption3, this,[=](){
                        timeOfCutter=(double)timeOfCutter/2;//加速切割机
                        upgradeDialog->accept();
                    });
                    upgradeDialog->exec();
                    delete upgradeDialog;
                }
                else if(score==5 &&centre->phase==1){
                    phase=2;
                    score=0;
                    textItem->setPlainText(QString::number(score));
                    typeNeeded++;
                    int u=centre->upgraded;
                    scen->removeItem(centre);
                    delete centre;
                    centre =new Centre(2,u);
                    scen->addItem(centre);
                    UpgradeDialog *upgradeDialog = new UpgradeDialog(this,2);
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption1, this, [=](){
                        timeOfMiner=(double)timeOfMiner/2;//加速开采器
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption2, this, [=](){
                        timeOfBelt=(double)timeOfBelt/2;//加速传送带
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption3, this,[=](){
                        timeOfCutter=(double)timeOfCutter/2;//加速切割机
                        upgradeDialog->accept();
                    });
                    upgradeDialog->exec();
                    delete upgradeDialog;
                }
                else if(score==5 &&centre->phase==2){
                    phase=3;
                    score=0;
                    textItem->setPlainText(QString::number(score));
                    typeNeeded++;
                    UpgradeDialog *upgradeDialog = new UpgradeDialog(this,3);
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption1, this, [=](){
                        timeOfMiner=(double)timeOfMiner/2;//加速开采器
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption2, this, [=](){
                        timeOfBelt=(double)timeOfBelt/2;//加速传送带
                        upgradeDialog->accept();
                    });
                    connect(upgradeDialog, &UpgradeDialog::upgradeOption3, this,[=](){
                        timeOfCutter=(double)timeOfCutter/2;//加速切割机
                        upgradeDialog->accept();
                    });
                    upgradeDialog->exec();
                }
                update();
            }
        }
    });
    timer->start(100);//启动定时器
    //connect(timer,&QTimer::timeout,&scene,&QGraphicsScene::advance);
    // connect(ui->pushButton,&QPushButton::clicked,[=](){//时间暂停功能
    //     timer->stop();
    // });

}

void PlayScene::handleLeftButtonClicked(QString s,QPixmap dragP)
{
    isDragging = true;
    dragText=s;
    dragPic = dragP;
}

void PlayScene::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
    case Qt::Key_R://旋转拖拽的图片
        if(isDragging)
    {
        QTransform transform;
        dragAngle=(dragAngle+90) % 360;
        transform.rotate(dragAngle);  // 逆时针旋转90度
        QCursor customCursor(dragPic.transformed(transform, Qt::SmoothTransformation), 0, 0);// 设置整个应用程序的鼠标图标
        qApp->setOverrideCursor(customCursor);
    }break;
    default:
        break;
    }
}
void PlayScene::deleteDev(int posx,int posy){
    if(dynamic_cast<cutter*>(deviceVector[posy][posx])){
        if(deviceVector[posy-1][posx]==deviceVector[posy][posx]){
            deviceVector[posy-1][posx] = nullptr;
        }//上下左右如果和当前坐标指向的是同一个地址，那么说明这是同一个剪刀，一起删除即可
        else if(deviceVector[posy+1][posx]==deviceVector[posy][posx]){
            deviceVector[posy+1][posx] = nullptr;
        }
        else if(deviceVector[posy][posx-1]==deviceVector[posy][posx]){
            deviceVector[posy+1][posx] = nullptr;
        }
        else if(deviceVector[posy][posx+1]==deviceVector[posy][posx]){
            deviceVector[posy][posx+1] = nullptr;
        }
    }
    qDebug() << "delete device in" << posy << ", " << posx;
    scen->removeItem(deviceVector[posy][posx]);
    delete deviceVector[posy][posx];
    deviceVector[posy][posx] = nullptr;
    if(mineVector[posy][posx]!=nullptr){
        scen->removeItem(mineVector[posy][posx]);
        delete mineVector[posy][posx];
        mineVector[posy][posx] = nullptr;
    }
}
void PlayScene::addD(QGraphicsSceneMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        if(PlayScene::isDragging){
            qDebug() << PlayScene::dragAngle;
            QApplication::setOverrideCursor(Qt::ArrowCursor);
            if (!PlayScene::dragText.isEmpty())
            {
                QPointF pos = event->scenePos();
                int posx=(int)pos.x()-(int)pos.x() % gridSize;
                int posy=(int)pos.y()-(int)pos.y() % gridSize;
                int number=deviceMap[PlayScene::dragText];
                qDebug() << "this is" << number;

                if(deviceVector[posx/40][posy/40]!=nullptr){
                    deleteDev(posx/40,posy/40);
                }//删除当前的设备
                if(posx/gridSize>=40||posx/gridSize<=0||posy/gridSize>=32||posy/gridSize<=0)
                    return;
                switch(number){
                case 1:{
                    Belt* belt = new Belt(posx,posy,PlayScene::dragAngle);
                    addDevice(belt,posx,posy);
                }break;
                case 2:{
                    cutter* cut = new cutter(posx,posy,PlayScene::dragAngle);
                    addDevice(cut,posx,posy);
                }break;
                case 3:{
                    qDebug() << "Miner";
                    Miner* miner = new Miner(posx,posy,PlayScene::dragAngle);
                    addDevice(miner,posx,posy);
                }break;
                case 4:{
                    TrashCan* trashcan = new TrashCan(posx,posy,PlayScene::dragAngle);
                    addDevice(trashcan,posx,posy);
                }break;
                case 5:{
                    Rotater *rotator = new  Rotater(posx,posy,PlayScene::dragAngle);
                     addDevice(rotator,posx,posy);
                }
                default:
                    break;
                }
                PlayScene::dragText="";
                PlayScene::dragAngle=0;
            }
            PlayScene::isDragging = false;
        }
        qDebug() << "Mouse Pressed at: " << event->scenePos();
    }
}

void PlayScene::addDevice(device* dev,int posx,int posy){
    int py = posy/gridSize;
    int px = posx/gridSize;
    deviceVector[py][px]=dev;
    scen->addItem(dev);
    connect(dev,&device::deleteDevice,this,[=](int x,int y){
        deleteDev(x,y);
    });//让每个设备都加上再次点击就会删除的功能
    if (dynamic_cast<cutter*>(dev)) {
        if(dragAngle==0){
            deviceVector[py][px+1]=dev;
        }
        else if(dragAngle==90){
            deviceVector[py+1][px]=dev;
        }
        else if(dragAngle==180){
            deviceVector[py][px-1]=dev;
        }
        else if(dragAngle==270){
            deviceVector[py-1][px]=dev;
        }
    }
}//在某个place加入device，使这个grid的hasDevice为真，grid上的设备变为这个设备。
PlayScene::~PlayScene()
{
    delete ui;
}
void PlayScene::addMoreMine() {
    upgrade1=1;
    // 处理添加更多矿场的逻辑
    for(int i=10;i<=14;i++){
        scen->removeItem(gridVector[i][13]);
        gridVector[i][13]= new grid(13 * gridSize,i * gridSize,1,0);
        scen->addItem(gridVector[i][13]);
    }
    //
    for(int i=17;i<=22;i++){
        for(int j=26;j<=27;j++){
            scen->removeItem(gridVector[i][j]);
            gridVector[i][j]= new grid(j * gridSize,i * gridSize,2,0);
            scen->addItem(gridVector[i][j]);
        }
    }
    //
    update();
}

void PlayScene::doubleValue(){
    upgrade2=1;
    Mine::value*=2;
}
void PlayScene::centreBigger(){
    upgrade3=1;
    for(int j=18;j<=22;j++){
        gridVector[j][22] = new grid(22 * gridSize,j * gridSize,0,1);//a centre lies on here
    }
    for(int j=18;j<=22;j++){
        gridVector[18][j] = new grid(j * gridSize,18 * gridSize,0,1);//a centre lies on here
    }
    scen->removeItem(centre);
    int p=centre->phase;
    delete centre;
    centre = new Centre(p,1);
    scen->addItem(centre);
    textItem->setPos(860,670);
    moneyItem->setPos(850,580);
    update();
}
