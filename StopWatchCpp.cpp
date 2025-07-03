// main.cpp
#include <QApplication>
#include "Stopwatch.h" // Stopwatch 클래스 헤더 포함

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // QApplication 객체 생성
    Stopwatch stopwatch;          // Stopwatch 위젯 객체 생성
    stopwatch.show();             // 스톱워치 위젯 표시
    return app.exec();            // 이벤트 루프 시작
}

```cpp
// Stopwatch.h
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>      // QWidget 클래스 포함
#include <QTimer>       // QTimer 클래스 포함 (타이머 기능)
#include <QLabel>       // QLabel 클래스 포함 (시간 표시)
#include <QPushButton>  // QPushButton 클래스 포함 (버튼)
#include <QVBoxLayout>  // QVBoxLayout 클래스 포함 (수직 레이아웃)
#include <QHBoxLayout>  // QHBoxLayout 클래스 포함 (수평 레이아웃)
#include <QFont>        // QFont 클래스 포함 (폰트 설정)
#include <QTime>        // QTime 클래스 포함 (시간 계산, 선택 사항 - 여기서는 직접 ms 계산)

class Stopwatch : public QWidget {
    Q_OBJECT // Qt의 시그널/슬롯 메커니즘을 사용하기 위한 매크로

public:
    // 생성자: 부모 위젯을 인자로 받음 (기본값 nullptr)
    explicit Stopwatch(QWidget* parent = nullptr);

private slots:
    // 타이머가 타임아웃될 때마다 호출될 슬롯
    private void updateTime();
    // 시작 버튼 클릭 시 호출될 슬롯
    private void startTimer();
    // 정지 버튼 클릭 시 호출될 슬롯
    private void stopTimer();

private:
    // UI 초기화 메서드
    private void initUI();

    QTimer* timer;          // 스톱워치 타이머
    qint64 elapsedTime;     // 경과 시간 (밀리초 단위)

    QLabel* timeLabel;      // 시간을 표시할 라벨
    QPushButton* startButton; // 시작 버튼
    QPushButton* stopButton;  // 정지 버튼
};

#endif // STOPWATCH_H

```cpp
// Stopwatch.cpp
#include "Stopwatch.h" // Stopwatch 클래스 헤더 포함

// Stopwatch 클래스의 생성자 구현
Stopwatch::Stopwatch(QWidget* parent)
    : QWidget(parent), // QWidget의 생성자 호출
    timer(new QTimer(this)), // QTimer 객체 생성 및 부모 설정
    elapsedTime(0) // 경과 시간 초기화
{
    // QTimer의 timeout 시그널을 updateTime 슬롯에 연결
    // 타이머가 설정된 간격마다 updateTime 함수를 호출하게 됨
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);

    // UI 초기화 메서드 호출
    initUI();
}

// UI 초기화 메서드 구현
private void Stopwatch::initUI() {
    setWindowTitle(tr("스톱워치")); // 윈도우 제목 설정 (tr은 번역을 위한 매크로)
    setGeometry(300, 300, 300, 200); // 윈도우 위치 및 크기 설정

    // 메인 수직 레이아웃 생성 및 위젯에 설정
    QVBoxLayout* vbox = new QVBoxLayout(this);

    // 시간 표시 라벨 생성 및 설정
    timeLabel = new QLabel(tr("00.000"), this); // 초기 시간 텍스트 설정
    timeLabel->setAlignment(Qt::AlignCenter); // 텍스트 중앙 정렬

    // 폰트 설정
    QFont font = timeLabel->font(); // 현재 폰트 가져오기
    font.setPointSize(40);          // 폰트 크기 40으로 설정
    font.setBold(true);             // 폰트 굵게 설정
    timeLabel->setFont(font);       // 설정된 폰트를 라벨에 적용

    vbox->addWidget(timeLabel); // 라벨을 수직 레이아웃에 추가

    // 버튼들을 담을 수평 레이아웃 생성
    QHBoxLayout* hbox = new QHBoxLayout();
    vbox->addLayout(hbox); // 수평 레이아웃을 메인 수직 레이아웃에 추가

    // 시작 버튼 생성 및 설정
    startButton = new QPushButton(tr("Start"), this); // "Start" 텍스트로 버튼 생성
    // 시작 버튼 클릭 시그널을 startTimer 슬롯에 연결
    connect(startButton, &QPushButton::clicked, this, &Stopwatch::startTimer);
    hbox->addWidget(startButton); // 시작 버튼을 수평 레이아웃에 추가

    // 정지 버튼 생성 및 설정
    stopButton = new QPushButton(tr("Stop"), this); // "Stop" 텍스트로 버튼 생성
    // 정지 버튼 클릭 시그널을 stopTimer 슬롯에 연결
    connect(stopButton, &QPushButton::clicked, this, &Stopwatch::stopTimer);
    hbox->addWidget(stopButton); // 정지 버튼을 수평 레이아웃에 추가

    // 초기 실행 시 정지 버튼 비활성화
    stopButton->setEnabled(false);
}

// 타이머 시작 슬롯 구현
private void Stopwatch::startTimer() {
    elapsedTime = 0; // 경과 시간 초기화
    timeLabel->setText(tr("00.000")); // 시간 표시 라벨 초기화
    timer->start(1); // 1밀리초 간격으로 타이머 시작
    stopButton->setEnabled(true); // 정지 버튼 활성화
    startButton->setEnabled(false); // 시작 버튼 비활성화
}

// 타이머 정지 슬롯 구현
private void Stopwatch::stopTimer() {
    timer->stop(); // 타이머 정지
    stopButton->setEnabled(false); // 정지 버튼 비활성화
    startButton->setEnabled(true); // 시작 버튼 활성화
}

// 시간 업데이트 슬롯 구현
private void Stopwatch::updateTime() {
    elapsedTime += 1; // 경과 시간 1밀리초 증가

    // 밀리초를 초와 밀리초로 분리
    qint64 seconds = elapsedTime / 1000;
    qint64 milliseconds = elapsedTime % 1000;

    // 시간을 "초.밀리초" 형식으로 포맷팅하여 라벨에 표시
    // QString::asprintf는 C++의 printf와 유사하게 포맷팅을 지원
    timeLabel->setText(QString::asprintf("%02lld.%03lld", seconds, milliseconds));
}
