#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <QObject>
class Config;

class XmlParser {
 public:
  XmlParser();
  void Reader(const QString& file_name, QList<Config>& cfg_list, QString& path);
  void Writer(const QList<Config>& cfg_list, const QString& file_name, const QString& exec_path);

};

#endif // XMLPARSER_H
