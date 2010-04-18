#include <QtCore/QCoreApplication>
#include <lib/libmoorie.h>
#include <iostream>
#include <QStringList>
#include <QString>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QStringList args = a.arguments();
    if (args.count() != 2) {
        std::cerr << "Usage: moorie nazwa" << std::endl
                << "Example:" << std::endl
                << "    moorie test"
                << std::endl;
        return 1;
    }
    Libmoorie moorie;
    std::cerr << qPrintable(moorie.hello());
    return a.exec();
}
