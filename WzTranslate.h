#ifndef WZTRANSLATE_H
#define WZTRANSLATE_H

#include <QString>
#include <QSettings>

/*
 *  类：WzTranslate
 *  用途：Qt多国语言翻译（基于INI文件）
 *  作者：欧阳伟
 *  日期：2018-8-1
 *  示例：
 *      ①创建语言库文件（INI文件），如：
 *          [chinese]
 *          begin=开始
 *          back=返回
 *          end=结束
 *      ②示例代码：
 *          1.简单场景（无需复用，无需close）：
 *          WzTranslate w("D:/translate.ini");
 *          if(w.load())
 *          {
 *              w.setCurrentLanguage("chinese");
 *              qDebug()<<w.tr("begin");
 *              qDebug()<<w.tr("back");
 *              qDebug()<<w.tr("end");
 *          }
 *
 *          2.较复杂场景（复用，需close）：
 *          WzTranslate w;
 *          w.setFileName("D:/translate.ini");
 *          if(w.load())
 *          {
 *              w.setCurrentLanguage("chinese");
 *              qDebug()<<w.tr("begin");
 *              qDebug()<<w.tr("back");
 *              qDebug()<<w.tr("end");
 *              w.close();
 *          }
 *          //重新从设置文件名开始
 *          w.setFileName("D:/translate.ini");
 *          if(w.load())
 *          {
 *              w.setCurrentLanguage("chinese");
 *              qDebug()<<w.tr("begin");
 *              qDebug()<<w.tr("back");
 *              qDebug()<<w.tr("end");
 *          }
 *
 *  说明：currentLanguage、fileName应为全英文字符串，避免不必要的bug
 */

class WzTranslate
{
public:
    WzTranslate();
    WzTranslate(const QString &fileName);
    ~WzTranslate();

    //设置文件名，即：语言库的文件名，搭配无参构造函数使用
    void setFileName(const QString &fileName);
    //设置当前语言
    void setCurrentLanguage(const QString &language);
    //加载语言库
    bool load(const char* encode = "UTF-8");
    //更新语言库，deprecated（不推荐使用），如果没有必要插入，则不需要调用这个函数
    bool updatelibrary(const QString &key,const QString &value);
    //翻译函数，tr为translate缩写，减少使用过程中的代码复杂度
    //成功返回实际值，失败返回"translate failed"或者"key: 'xxx' translate failed"
    QString tr(const QString &key);
    //关闭并释放内存
    void close();
    //测试当前语言库的所有输出
    void test();

private:
    //释放内存
    void release();

private:
    QString fileName;
    QString currentLanguage;
    bool isLoaded;

    QSettings *library;
};

#endif // WZTRANSLATE_H
