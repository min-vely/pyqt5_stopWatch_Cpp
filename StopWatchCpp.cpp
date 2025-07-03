// main.cpp
#include <QApplication>
#include "Stopwatch.h" // Stopwatch Ŭ���� ��� ����

int main(int argc, char* argv[]) {
    QApplication app(argc, argv); // QApplication ��ü ����
    Stopwatch stopwatch;          // Stopwatch ���� ��ü ����
    stopwatch.show();             // �����ġ ���� ǥ��
    return app.exec();            // �̺�Ʈ ���� ����
}

```cpp
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
    private void updateTime();
    // ���� ��ư Ŭ�� �� ȣ��� ����
    private void startTimer();
    // ���� ��ư Ŭ�� �� ȣ��� ����
    private void stopTimer();

private:
    // UI �ʱ�ȭ �޼���
    private void initUI();

    QTimer* timer;          // �����ġ Ÿ�̸�
    qint64 elapsedTime;     // ��� �ð� (�и��� ����)

    QLabel* timeLabel;      // �ð��� ǥ���� ��
    QPushButton* startButton; // ���� ��ư
    QPushButton* stopButton;  // ���� ��ư
};

#endif // STOPWATCH_H

```cpp
// Stopwatch.cpp
#include "Stopwatch.h" // Stopwatch Ŭ���� ��� ����

// Stopwatch Ŭ������ ������ ����
Stopwatch::Stopwatch(QWidget* parent)
    : QWidget(parent), // QWidget�� ������ ȣ��
    timer(new QTimer(this)), // QTimer ��ü ���� �� �θ� ����
    elapsedTime(0) // ��� �ð� �ʱ�ȭ
{
    // QTimer�� timeout �ñ׳��� updateTime ���Կ� ����
    // Ÿ�̸Ӱ� ������ ���ݸ��� updateTime �Լ��� ȣ���ϰ� ��
    connect(timer, &QTimer::timeout, this, &Stopwatch::updateTime);

    // UI �ʱ�ȭ �޼��� ȣ��
    initUI();
}

// UI �ʱ�ȭ �޼��� ����
private void Stopwatch::initUI() {
    setWindowTitle(tr("�����ġ")); // ������ ���� ���� (tr�� ������ ���� ��ũ��)
    setGeometry(300, 300, 300, 200); // ������ ��ġ �� ũ�� ����

    // ���� ���� ���̾ƿ� ���� �� ������ ����
    QVBoxLayout* vbox = new QVBoxLayout(this);

    // �ð� ǥ�� �� ���� �� ����
    timeLabel = new QLabel(tr("00.000"), this); // �ʱ� �ð� �ؽ�Ʈ ����
    timeLabel->setAlignment(Qt::AlignCenter); // �ؽ�Ʈ �߾� ����

    // ��Ʈ ����
    QFont font = timeLabel->font(); // ���� ��Ʈ ��������
    font.setPointSize(40);          // ��Ʈ ũ�� 40���� ����
    font.setBold(true);             // ��Ʈ ���� ����
    timeLabel->setFont(font);       // ������ ��Ʈ�� �󺧿� ����

    vbox->addWidget(timeLabel); // ���� ���� ���̾ƿ��� �߰�

    // ��ư���� ���� ���� ���̾ƿ� ����
    QHBoxLayout* hbox = new QHBoxLayout();
    vbox->addLayout(hbox); // ���� ���̾ƿ��� ���� ���� ���̾ƿ��� �߰�

    // ���� ��ư ���� �� ����
    startButton = new QPushButton(tr("Start"), this); // "Start" �ؽ�Ʈ�� ��ư ����
    // ���� ��ư Ŭ�� �ñ׳��� startTimer ���Կ� ����
    connect(startButton, &QPushButton::clicked, this, &Stopwatch::startTimer);
    hbox->addWidget(startButton); // ���� ��ư�� ���� ���̾ƿ��� �߰�

    // ���� ��ư ���� �� ����
    stopButton = new QPushButton(tr("Stop"), this); // "Stop" �ؽ�Ʈ�� ��ư ����
    // ���� ��ư Ŭ�� �ñ׳��� stopTimer ���Կ� ����
    connect(stopButton, &QPushButton::clicked, this, &Stopwatch::stopTimer);
    hbox->addWidget(stopButton); // ���� ��ư�� ���� ���̾ƿ��� �߰�

    // �ʱ� ���� �� ���� ��ư ��Ȱ��ȭ
    stopButton->setEnabled(false);
}

// Ÿ�̸� ���� ���� ����
private void Stopwatch::startTimer() {
    elapsedTime = 0; // ��� �ð� �ʱ�ȭ
    timeLabel->setText(tr("00.000")); // �ð� ǥ�� �� �ʱ�ȭ
    timer->start(1); // 1�и��� �������� Ÿ�̸� ����
    stopButton->setEnabled(true); // ���� ��ư Ȱ��ȭ
    startButton->setEnabled(false); // ���� ��ư ��Ȱ��ȭ
}

// Ÿ�̸� ���� ���� ����
private void Stopwatch::stopTimer() {
    timer->stop(); // Ÿ�̸� ����
    stopButton->setEnabled(false); // ���� ��ư ��Ȱ��ȭ
    startButton->setEnabled(true); // ���� ��ư Ȱ��ȭ
}

// �ð� ������Ʈ ���� ����
private void Stopwatch::updateTime() {
    elapsedTime += 1; // ��� �ð� 1�и��� ����

    // �и��ʸ� �ʿ� �и��ʷ� �и�
    qint64 seconds = elapsedTime / 1000;
    qint64 milliseconds = elapsedTime % 1000;

    // �ð��� "��.�и���" �������� �������Ͽ� �󺧿� ǥ��
    // QString::asprintf�� C++�� printf�� �����ϰ� �������� ����
    timeLabel->setText(QString::asprintf("%02lld.%03lld", seconds, milliseconds));
}
