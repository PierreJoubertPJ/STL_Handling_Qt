#include <QApplication>
#include <QPushButton>
#include <QTextEdit>
#include <QFile>
#include <QWidget>
#include <QFont>
#include <QString>
#include <qlabel.h>
#include <vector>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

#include "stlfileobject.h"
#include "datatypes.h"
#include "segment.h"
#include "layer.h"
#include "printer.h"

std::ostream& operator<<(std::ostream& str, const segment& seg){
    str << "p1: x " << seg.p1.x << "\t y " << seg.p1.y << "\t z " << seg.p1.z << std::endl;
    str << "p2: x " << seg.p2.x << "\t y " << seg.p2.y << "\t z " << seg.p2.z << std::endl;
    return (str);
}

std::ostream& operator<<(std::ostream& str, const point& point){
    str << "x " << point.x << "\t y " << point.y << "\t z " << point.z << std::endl;
    return (str);
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    std::vector<triangle> triangles;
    StlFileObject StlFileObj;
    QString stl_raw_data_data;

    printer window;

    //QFile input("../STL_Handler/cube10.stl");
    QFile input("../STL_Handler/test.stl");
    if (!input.open(QIODevice::ReadOnly))
        std::cerr << "Can't open file" << std::endl;
    if (input.isOpen())
    {
        std::cout << "file open" << std::endl;
        stl_raw_data_data = input.readAll();
        triangles =  StlFileObj.decodeFile(stl_raw_data_data);
        input.close();

        layer lay;
        lay.width =  0.01;

        for(lay.height = 0; lay.height < 100; lay.height += lay.width) {
            lay.contours.clear();
            printf("\n##########################\nLayer %f\n", lay.height);
            //std::cout << window.part.data()->contours.size() << std::endl;
            lay.getContour(triangles);
            window.part.push_back(lay);
            //std::cout << window.part.data()->contours.size() << std::endl;
        }
        window.show();
    }
   return app.exec();
}
