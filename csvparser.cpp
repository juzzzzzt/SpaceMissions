#include "csvparser.h"

std::vector<std::vector<QString>> parseCSV(const QString &filename) {
    std::vector<std::vector<QString>> data;
    QFile file(filename);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning("Couldn't open the file.");
        return data;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(";");
        std::vector<QString> row;
        for (const QString &field : fields) {
            row.push_back(field);
        }
        data.push_back(row);
    }

    file.close();
    return data;
}
