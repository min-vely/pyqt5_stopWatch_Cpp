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
    void updateTime();
    // 시작 버튼 클릭 시 호출될 슬롯
    void startTimer();
    // 정지 버튼 클릭 시 호출될 슬롯
    void stopTimer();

private:
    // UI 초기화 메서드
    void initUI();

    QTimer* timer;          // 스톱워치 타이머
    qint64 elapsedTime;     // 경과 시간 (밀리초 단위)

    QLabel* timeLabel;      // 시간을 표시할 라벨
    QPushButton* startButton; // 시작 버튼
    QPushButton* stopButton;  // 정지 버튼
};

#endif // STOPWATCH_H