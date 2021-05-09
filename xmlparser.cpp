#include "xmlparser.h"

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <mainwindow.h>
XmlParser::XmlParser() {

}

void XmlParser::Writer(const QList<Config>& cfg_list, const QString& file_name, const QString& exec_path) {
  QFile file(file_name);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
    qDebug() << "open error !";
    return;
  }

  QXmlStreamWriter writer(&file);
  writer.setAutoFormatting(true);
  writer.writeStartDocument();
  writer.writeStartElement("cfg");
  writer.writeAttribute("exec_path", exec_path);
  for (auto it : cfg_list) {
    writer.writeStartElement("instance");
    writer.writeAttribute("id", QString::number(it.id_));
    writer.writeAttribute("username", it.username_);
    writer.writeAttribute("password", it.password_);
    writer.writeAttribute("path", it.path_);
    writer.writeEndElement();
  }
  writer.writeEndElement();
  writer.writeEndDocument();
  file.close();


}

void XmlParser::Reader(const QString& file_name, QList<Config>& cfg_list, QString& exec_path) {
  QFile file(file_name);
  if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
    qDebug() << "open error !";
    return;
  }
  QXmlStreamReader reader(&file);
  while (!reader.atEnd()) {
    if (reader.isStartElement() && reader.name().toString() == "cfg") {
      QXmlStreamAttributes attributes = reader.attributes();
      if (attributes.hasAttribute("exec_path")) {
        exec_path = attributes.value("exec_path").toString();
      }
    }
    if (reader.isStartElement() && reader.name().toString() == "instance") {
      Config cfg(0, "", "", "");
      QXmlStreamAttributes attributes = reader.attributes();
      if (attributes.hasAttribute("id")) {
        cfg.id_ = attributes.value("id").toInt();
      }
      if (attributes.hasAttribute("username")) {
        cfg.username_ = attributes.value("username").toString();
      }
      if (attributes.hasAttribute("password")) {
        cfg.password_ = attributes.value("password").toString();
      }
      if (attributes.hasAttribute("path")) {
        cfg.path_ = attributes.value("path").toString();
      }
      cfg_list.push_back(cfg);
    }
    reader.readNext();
  }
  file.close();
}
