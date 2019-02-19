#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QFileInfo>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    Init();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::Init()
{
    /*
        检查dist文件夹，如果这个文件夹存在，则直接打开微信开发者工具，
        如果这个文件夹不存在，则说明微信开发者工具是才装的，没有安装好nwjs,
        所以要进行安装nwjs
    */
    bool isOk = isFileOk("dist");
    qDebug() <<  isOk;
    if (!isOk){
        qDebug() <<  "正在进行安装相关依赖，如果网络不好请连接网络后再试！";
        installWechatTools();
    } else {
        qDebug() <<  "程序正在运行";

        /*
            this->setWindowFlags(Qt::Popup);
            有问题：
                使用Qt::Popup之后程序没法真正关闭，
                不使用程序能够关闭
            这个的目的是不让本程序在状态栏中显示，只要启动的微信开发工具在状态栏上显示就可以了

            上面那个办法不行，直接把窗口设成最小的就可以了，反正也看不出来，
            而且微信开发工具关闭了之后，这个程序也是要关闭的
        */
        //this->setWindowFlag(Qt::Popup);
        this->setWindowFlags( Qt::X11BypassWindowManagerHint);
        this->setMaximumSize(1,1);
        this->setMinimumSize(1,1);
        openWechatTools();
    }



    this->setWindowTitle(tr("微信开发工具---Linux平台辅助程序"));
}

//用来检查微信开发工具安装目录下是否存在fileName的文件
bool Widget::isFileOk(QString fileName)
{
    QString newPath = path.getRootPath().append(fileName);
    QFileInfo fileInfo(newPath);
    if(fileInfo.isDir())  {
          return true;
        }
    else {
           return false;
    }
}

void Widget::installWechatTools()
{
    QString wxdt = path.getBinPath().append("wxdt");
    caller = new QProcess(this);//创建对象，指定父类指针
    caller->start(wxdt,QStringList()<<"install");//启动wxdt install 进行安装
    connect(this->caller,SIGNAL(readyReadStandardOutput()),this,SLOT(getInstallInfoToLabel()));
    connect(this->caller,SIGNAL(finished(int)),this,SLOT(goodBye(int)));
}

void Widget::openWechatTools()
{
    QString wxdt = path.getBinPath().append("wxdt");
    qDebug() << wxdt;
    caller = new QProcess(this);//创建对象，指定父类指针
    caller->start(wxdt);//启动wxdt打开微信开发工具！
    connect(this->caller,SIGNAL(finished(int)),this,SLOT(goodBye(int)));
}

void Widget::getInstallInfoToLabel()
{
    ui->label->setText("");
    QString info ="";
    info = info.append( caller->readAllStandardOutput());
    qDebug() << info;
    info.append("\n安装完成后会自动关闭，再重新启动程序就可以了"
                "\n注意看网速，依赖只有一百多M！\n"
                "如果你没有安装完成就退出，那么在打开前，请先在终端中先运行：\n"
                "rm -rf /tmp/wxdt_xsp");
    ui->label->setText(info);
}

void Widget::goodBye(int INT)
{
    this->close();
    qDebug()<<"已经关闭";
}

