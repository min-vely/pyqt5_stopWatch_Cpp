// Stopwatch.h
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <QWidget>      // QWidget Ŭ���� ����
#include <QTimer>       // QTimer Ŭ���� ���� (Ÿ�̸� ���)
#include <QLabel>       // QLabel Ŭ���� ���� (�ð� ǥ��)
#include <QPushButton>  // QPushButton Ŭ���� ���� (��ư)
#include <QVBoxLayout>  // QVBoxLayout Ŭ���� ���� (���� ���̾ƿ�)
#include <QHBoxLayout>  // QHBoxLayout Ŭ���� ���� (���� ���̾ƿ�)
#include <QFont>        // QFont Ŭ���� ���� (��Ʈ ����)
#include <QTime>        // QTime Ŭ���� ���� (�ð� ���, ���� ���� - ���⼭�� ���� ms ���)

class Stopwatch : public QWidget {
    Q_OBJECT // Qt�� �ñ׳�/���� ��Ŀ������ ����ϱ� ���� ��ũ��

public:
    // ������: �θ� ������ ���ڷ� ���� (�⺻�� nullptr)
    explicit Stopwatch(QWidget* parent = nullptr);

private slots:
    // Ÿ�̸Ӱ� Ÿ�Ӿƿ��� ������ ȣ��� ����
    void updateTime();
    // ���� ��ư Ŭ�� �� ȣ��� ����
    void startTimer();
    // ���� ��ư Ŭ�� �� ȣ��� ����
    void stopTimer();

private:
    // UI �ʱ�ȭ �޼���
    void initUI();

    QTimer* timer;          // �����ġ Ÿ�̸�
    qint64 elapsedTime;     // ��� �ð� (�и��� ����)

    QLabel* timeLabel;      // �ð��� ǥ���� ��
    QPushButton* startButton; // ���� ��ư
    QPushButton* stopButton;  // ���� ��ư
};

#endif // STOPWATCH_H