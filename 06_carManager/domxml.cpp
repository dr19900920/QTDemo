#include "domxml.h"
#include <QFile>
#include <QDomDocument> //文件
#include <QDomProcessingInstruction> //格式头部
#include <QDomElement> //元素
#include <QDebug>
#include <QTextStream> //文本流
#include <QDateTime>

DomXML::DomXML()
{

}

void DomXML::createXML(QString filePath) {

    QFile file(filePath);
    if (file.exists()) {
        qDebug() << "file exists";
        return;
    }

    bool isOK = file.open(QIODevice::WriteOnly);
    if (isOK == false) {
        qDebug() << "writeonly error";
        return;
    }

    QDomDocument doc;
    QDomProcessingInstruction ins;
    ins = doc.createProcessingInstruction("xml", "version=\'1.0\' encoding=\'utf-8\'");
    doc.appendChild(ins);

    // 根节点元素
    QDomElement root = doc.createElement("日销售清单");
    doc.appendChild(root);
    // 保存
    QTextStream stream(&file);
    doc.save(stream, 4); // 4 缩进字符
    file.close();
}

void DomXML::appendXML(QString filePath, QStringList list) {

    QFile file(filePath);
    bool isOK = file.open(QIODevice::ReadOnly);
    if (isOK == false) {
        qDebug() << "read only failed";
        return;
    }

    QDomDocument doc;
    isOK = doc.setContent(&file);
    if (isOK == false) {
        qDebug() << "关联失败";
        return;
    }
    file.close();
    QDomElement root = doc.documentElement();
    QDateTime currentDate = QDateTime::currentDateTime();
    QString dateStr = currentDate.toString("yyyy-MM-dd");
    if (root.hasChildNodes()) {
        qDebug() << "root.hasChildNodes";
        QDomElement lastEmt = root.lastChildElement();
        if (lastEmt.attribute("date") == dateStr) {
            writeXML(doc, lastEmt, list);
        } else {
            QDomElement dateEmt = doc.createElement("日期");
            QDomAttr dateAttr = doc.createAttribute("date");
            dateAttr.setNodeValue(dateStr);
            dateEmt.setAttributeNode(dateAttr);
            root.appendChild(dateEmt);
            writeXML(doc, dateEmt, list);
        }
    } else {
        QDomElement dateEmt = doc.createElement("日期");
        QDomAttr dateAttr = doc.createAttribute("date");
        dateAttr.setNodeValue(dateStr);
        dateEmt.setAttributeNode(dateAttr);
        root.appendChild(dateEmt);
        writeXML(doc, dateEmt, list);
    }

    isOK = file.open(QIODevice::WriteOnly);
    if (isOK) {
        // 保存
        QTextStream stream(&file);
        doc.save(stream, 4); // 4 缩进字符
        file.close();
    }

}

void DomXML::writeXML(QDomDocument &doc, QDomElement &root, QStringList &list) {

    QDateTime currentDate = QDateTime::currentDateTime();
    QString dateStr = currentDate.toString("hh:mm:ss");

    QDomElement timeEmt = doc.createElement("时间");
    QDomAttr attr = doc.createAttribute("time");
    attr.setNodeValue(dateStr);
    timeEmt.setAttributeNode(attr);
    root.appendChild(timeEmt);

    QStringList emtList = {"厂家", "品牌", "报价", "数量", "金额"};

    for (int i=0; i<emtList.size(); i++) {
        QDomElement a = doc.createElement(emtList.at(i));
        QDomText text = doc.createTextNode(list.at(i));
        a.appendChild(text);
        timeEmt.appendChild(a);
    }
}

void DomXML::readXML(QString filePath, QStringList &fList, QStringList &bList, QStringList &pList, QStringList &nList, QStringList &tList) {
    QFile file(filePath);
    bool isOK = file.open(QIODevice::ReadOnly);
    if (isOK == false) {
        qDebug() << "read only failed";
        return;
    }

    QDomDocument doc;
    isOK = doc.setContent(&file);
    if (isOK == false) {
        qDebug() << "关联失败";
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    QDateTime date = QDateTime::currentDateTime();
    QString dateStr = date.toString("yyyy-MM-dd");
    if (root.hasChildNodes() == false) {
        qDebug() << "没有子节点";
        return;
    }

    QDomElement lastEmt = root.lastChildElement();
    if (lastEmt.hasAttribute("date") == false) {
        qDebug() << "没有日期属性";
        return;
    }

    if (lastEmt.attribute("date") != dateStr) {
        qDebug() << "不是当天日期" << lastEmt.attribute("date");
        return;
    }

    QDomNodeList nodeList = lastEmt.childNodes();
    for (int i=0; i<nodeList.size(); i++) {
        QDomNodeList subList = nodeList.at(i).childNodes();
        QString f = subList.at(0).toElement().text();
        fList.append(f);

        QString b = subList.at(1).toElement().text();
        bList.append(b);

        QString p = subList.at(2).toElement().text();
        pList.append(p);

        QString n = subList.at(3).toElement().text();
        nList.append(n);

        QString t = subList.at(4).toElement().text();
        tList.append(t);

    }

}

