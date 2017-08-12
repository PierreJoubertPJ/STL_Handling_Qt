#include <QApplication>

#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "stlfileobject.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
StlFileObject StlFileObj;
    QWidget fenetre;
    fenetre.setFixedSize(1920/2, 1080/2);
    QFile input("../STL_Handler/test.stl");

    QPushButton buttonTest("test", &fenetre);
    buttonTest.move(500,50);
    QLabel TxtBlock(&fenetre);
    QString stl_raw_data_data;

    if (!input.open(QIODevice::ReadOnly))
        std::cerr << "Can't open file" << std::endl;
    if (input.isOpen())
    {
        std::cout << "file open" << std::endl;
        stl_raw_data_data = input.readAll();
        std::cout << StlFileObj.decodeFile(stl_raw_data_data);
        TxtBlock.setText(stl_raw_data_data);
        input.close();
    }
    fenetre.show();
    return app.exec();
}
