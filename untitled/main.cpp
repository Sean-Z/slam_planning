#include <QCoreApplication>
#include <iostream>
#define PI 3.1415926
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    int width = 360;
    int height = 180;

    int x1 = 10;
    int y1 = 10;

    int x2 = 11;
    int y2 = 10;

    double azimuth_curr = 360 / width * x1 * PI /180;
    double elevation_curr = (90 - 180 / height * y1) * PI / 180;

    double x_curr = cos(elevation_curr) * cos(azimuth_curr);
    double y_curr = cos(elevation_curr) * sin(azimuth_curr);
    double z_curr = sin(elevation_curr);

    double azimuth_pre = 360 / width * x2 * PI /180;
    double elevation_pre = (90 - 180 / height * y2) * PI /180;

    double x_pre = cos(elevation_pre) * cos(azimuth_pre);
    double y_pre = cos(elevation_pre) * sin(azimuth_pre);
    double z_pre = sin(elevation_pre);

    double up = x_curr * x_pre + y_curr * y_pre + z_curr * z_pre;
    double down = sqrt(x_curr * x_curr + y_curr * y_curr + z_curr * z_curr) * sqrt(x_pre * x_pre + y_pre * y_pre + z_pre * z_pre);


    std::cout << fabs(acos((up) / (down)))*180/PI << std::endl ;



    return a.exec();
}
