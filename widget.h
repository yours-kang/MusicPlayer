#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QUrl>
#include <QMediaPlayer>
#include <QAudioOutput>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    enum PlayMode {
        Sequence,    // 顺序播放
        Loop,        // 单曲循环
        Random       // 随机播放
    };
    Q_ENUM(PlayMode)

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

    bool eventFilter(QObject *watched, QEvent *event);

private:
    Ui::Widget *ui;
    QList<QUrl>playList;
    QAudioOutput *audioOutput;
    QMediaPlayer *mediaplayer;
    int currentIndex = 0; 
    PlayMode playMode = Sequence; // 默认顺序播放
    void updatePlayModeIcon();    // 更新播放模式图标
    void playNext();             // 处理下一曲逻辑
    void playPrevious();         // 处理上一曲逻辑
};
#endif // WIDGET_H
