// main.cpp
#include <QApplication>
#include "StopwatchCpp.h" // Stopwatch Ŭ���� ��� ����

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // QApplication ��ü ����
    Stopwatch stopwatch;          // Stopwatch ���� ��ü ����
    stopwatch.show();             // �����ġ ���� ǥ��
    return app.exec();            // �̺�Ʈ ���� ����
}