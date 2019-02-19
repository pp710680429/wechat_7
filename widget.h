#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "filepath.h"
#include <QProcess>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    //程序初始化
    void Init();
    //检查某个文件是否存在
    bool isFileOk(QString fileName);
    //安装微信开发者工具
    void installWechatTools();
    //运行微信开发者工具
    void openWechatTools();

private:
    Ui::Widget *ui;

    //文件路径
    filePath path;

    QProcess* caller;

public slots:
    //把安装过程中得到的信息输出到lable上
    void getInstallInfoToLabel();
    //当微信开发工具退出时，本程序也要退出
    void goodBye(int);

};

#endif // WIDGET_H
