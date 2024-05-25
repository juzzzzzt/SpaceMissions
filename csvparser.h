#ifndef CSV_PARSER_H
#define CSV_PARSER_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

std::vector<std::vector<QString>> parseCSV(const QString &filename);

#endif // CSV_PARSER_H
