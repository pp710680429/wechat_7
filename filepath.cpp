#include "filepath.h"

filePath::filePath()
{

}

//获得微信开发工具的安装目录路径
QString filePath::getRootPath()
{
    QString path = "";
    path = "/opt/wechat_web_devtools-master/";
    return path;
}

//获得微信开发工具的bin路径
QString filePath::getBinPath()
{
    QString path = "";
    path = "/opt/wechat_web_devtools-master/bin/";
    return path;
}

//获得微信开发工具的桌面图标路径
QString filePath::getIcoPath()
{
    QString path = "";
    path = "/opt/wechat_web_devtools-master/bin/wechat_dev_tools.desktop";
    return path;
}
