#include "WzTranslate.h"

#include <QDebug>
#include <QFile>

WzTranslate::WzTranslate()
{
    qDebug()<<"WzTranslate: WzTranslate()";

    library = NULL;
    isLoaded = false;
    fileName = "";
    currentLanguage = "";
}

WzTranslate::WzTranslate(const QString &fileName)
{
    qDebug()<<"WzTranslate: WzTranslate(const QString &fileName)";

    library = NULL;
    isLoaded = false;

    this->fileName = fileName;
}

WzTranslate::~WzTranslate()
{
    qDebug()<<"WzTranslate: ~WzTranslate()";

    release();
}

void WzTranslate::setFileName(const QString &fileName)
{
    qDebug()<<"WzTranslate: setFileName(const QString &fileName)";

    this->fileName = fileName;
}

void WzTranslate::setCurrentLanguage(const QString &language)
{
    qDebug()<<"WzTranslate: setCurrentLanguage(const QString &language)";

    this->currentLanguage = language;
}

bool WzTranslate::load(const char* encode)
{
    qDebug()<<"WzTranslate: load(const char* encode)";

    if(fileName.isEmpty())
    {
        qDebug()<<"WzTranslate: 加载失败，文件名不能为空";
        return false;
    }
    QFile file(fileName);
    if(file.exists())
    {
        if(!file.open(QIODevice::ReadWrite))//如果文件存在但不能可写
        {
            qDebug()<< "WzTranslate: 加载失败，文件不可写";
            file.close();
            return false;
        }
        file.close();
    }
    else
    {
        qDebug()<< "WzTranslate: 加载失败，文件不存在";
        return false;
    }

    library = new QSettings(fileName,QSettings::IniFormat);
    library->setIniCodec(encode);
    isLoaded = true;
    return true;
}


bool WzTranslate::updatelibrary(const QString &key, const QString &value)
{
    qDebug()<<"WzTranslate: updatelibrary(const QString &key, const QString &value)";
    if(!isLoaded)
    {
        qDebug()<<"WzTranslate: 更新语言库失败，库未成功加载";
        return false;
    }
    if(currentLanguage.isEmpty())
    {
        qDebug()<<"WzTranslate: 更新语言库失败，当前语言为空，请调用setCurrentLanguage函数设置当前语言";
        return false;
    }

    library->beginGroup(currentLanguage);
    library->setValue(key,value);
    library->endGroup();
    return true;
}

QString WzTranslate::tr(const QString &key)
{
    qDebug()<<"WzTranslate: tr(const QString &key)";

    if(!isLoaded)
    {
        qDebug()<<"WzTranslate: 翻译失败，库未成功加载";
        return "translate failed";
    }
    if(currentLanguage.isEmpty())
    {
        qDebug()<<"WzTranslate: 翻译失败，当前语言为空，请调用setCurrentLanguage函数设置当前语言";
        return "translate failed";
    }

    QString tmp = library->value(currentLanguage + "/" + key).toString();
    if(tmp.isEmpty())
    {
        return "key: \'" + key + "\' translate failed";
    }
    return tmp;
}

void WzTranslate::close()
{
    qDebug()<<"WzTranslate: close()";
    release();
}

void WzTranslate::test()
{
    qDebug()<<library;
}

void WzTranslate::release()
{
    if(library != NULL)
    {
        delete library;
        library = NULL;
    }
    fileName = "";
    currentLanguage = "";
    isLoaded = false;
}
