// main.cpp
#include <QApplication>
#include "StopwatchCpp.h" // Stopwatch 클래스 헤더 포함

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // QApplication 객체 생성
    Stopwatch stopwatch;          // Stopwatch 위젯 객체 생성
    stopwatch.show();             // 스톱워치 위젯 표시
    return app.exec();            // 이벤트 루프 시작
}