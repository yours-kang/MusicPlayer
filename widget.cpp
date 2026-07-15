#include "widget.h"
#include "./ui_widget.h"
#include <QFileDialog>
#include <QDir>
#include <QRandomGenerator>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    //初始化按钮图标
    ui->pushButton_4->setIcon(QIcon(":/file/pause.png"));
    updatePlayModeIcon(); // 初始化播放模式图标

    //设置播放器
    audioOutput = new QAudioOutput(this);
    mediaplayer = new QMediaPlayer(this);
    mediaplayer->setAudioOutput(audioOutput);

    // 连接播放状态变化信号
    connect(mediaplayer, &QMediaPlayer::playbackStateChanged, this, [=](QMediaPlayer::PlaybackState state) {
        switch(state) {
        case QMediaPlayer::PlayingState:
            ui->pushButton_4->setIcon(QIcon(":/file/playing.png"));
            break;
        case QMediaPlayer::PausedState:
            ui->pushButton_4->setIcon(QIcon(":/file/pause.png"));
            break;
        case QMediaPlayer::StoppedState:
            ui->pushButton_4->setIcon(QIcon(":/file/pause.png"));
            break;
        }
    });

    // 连接媒体状态变化信号（处理播放结束）
    connect(mediaplayer, &QMediaPlayer::mediaStatusChanged, this, [=](QMediaPlayer::MediaStatus status) {
        if (status == QMediaPlayer::EndOfMedia) {
            playNext();
        }
    });

    //连接播放结束信号
    connect(mediaplayer, &QMediaPlayer::playbackStateChanged, this, [=](QMediaPlayer::PlaybackState state) {
        if (state == QMediaPlayer::StoppedState && mediaplayer->mediaStatus() == QMediaPlayer::EndOfMedia) {
            playNext();
        }
    });
    //获取当前媒体时长
    connect(mediaplayer, &QMediaPlayer::durationChanged, this, [=](qint64 duration){
        ui->totalLabel->setText(QString("%1:%2").arg(duration / 1000 / 60, 2, 10, QChar('0')).arg((duration / 1000 % 60)));
        ui->playcourseSlider->setRange(0, duration);
    });
    //获取当前媒体播放时间
    connect(mediaplayer, &QMediaPlayer::positionChanged, this, [=](qint64 position){
        ui->curLabel->setText(QString("%1:%2").arg(position / 1000 / 60, 2, 10, QChar('0')).arg((position / 1000 % 60)));
        ui->playcourseSlider->setValue(position);
    });
    //滑动滑块，改变音乐进度
    connect(ui->playcourseSlider, &QSlider::sliderMoved, mediaplayer, &QMediaPlayer::setPosition);
    
    // 设置音量滑块的初始值和范围
    ui->verticalSlider->setRange(0, 100); // 音量范围 0-100
    ui->verticalSlider->setValue(50);     // 初始音量设为 50%
    audioOutput->setVolume(0.5);          // 设置初始音量（0.0 - 1.0）

    // 连接音量滑块的值变化信号到音量设置槽
    connect(ui->verticalSlider, &QSlider::valueChanged, this, [=](int value) {
        float volume = value / 100.0f;    // 将 0-100 转换为 0.0-1.0
        audioOutput->setVolume(volume);
    });
    
    // 初始隐藏音量条
    ui->verticalSlider->setVisible(false);

    // 使用事件过滤器处理悬停和离开
    ui->pushButton_6->installEventFilter(this);
    ui->verticalSlider->installEventFilter(this);


}

Widget::~Widget()
{
    delete ui;
}


//打开音乐目录
void Widget::on_pushButton_clicked()
{
    //打开音乐目录
    auto path = QFileDialog::getExistingDirectory(this, "请选择音乐目录", "D:\\coding\\Qtproject\\MusicPlayer\\file");
    //获取MP3，wav文件
    QDir dir(path);
    auto musiclist = dir.entryList(QStringList() << "*.mp3" << "*.wav");
    //把音乐名字放到窗口展示
    ui->listWidget->addItems(musiclist);
    //默认选择第一个
    ui->listWidget->setCurrentRow(0);
    //把音乐完整路径保存
    for(auto file:musiclist){
        playList.append(QUrl::fromLocalFile(path + "/" + file));
    }
}


//循环状态切换
void Widget::on_pushButton_2_clicked()
{
    playMode = static_cast<PlayMode>((playMode + 1) % 3);
    updatePlayModeIcon();
}


//上一曲
void Widget::on_pushButton_3_clicked()
{   
    playPrevious();
}


//播放/暂停
void Widget::on_pushButton_4_clicked()
{
    if(playList.isEmpty()){
        //如果没有音乐，则返回
        return;
    }
    switch(mediaplayer->playbackState()){
        case QMediaPlayer::PlaybackState::StoppedState:{
            //获取选择的行号
            currentIndex = ui->listWidget->currentRow();
            //如果没有播放，则播放当前选择的音乐
            //播放音乐
            mediaplayer->setSource(playList[currentIndex]);
            //开始播放
            mediaplayer->play();
            //更新播放按钮图标
            ui->pushButton_4->setIcon(QIcon(":/file/playing.png"));
            break;
        }

        case QMediaPlayer::PlaybackState::PlayingState:
            //如果正在播放，则暂停音乐
            mediaplayer->pause();
            //更新播放按钮图标
            ui->pushButton_4->setIcon(QIcon(":/file/pause.png"));
            break;
        case QMediaPlayer::PlaybackState::PausedState:
            //如果暂停，则继续播放
            mediaplayer->play();
            //更新播放按钮图标
            ui->pushButton_4->setIcon(QIcon(":/file/playing.png"));
            break;
    }
}


//下一曲
void Widget::on_pushButton_5_clicked()
{
    playNext();
}

//调节音量
void Widget::on_pushButton_6_clicked()
{
     // 切换音量滑块的可见性
    ui->verticalSlider->setVisible(!ui->verticalSlider->isVisible());
}

void Widget::on_listWidget_doubleClicked(const QModelIndex &index)
{
    currentIndex = index.row();
    mediaplayer->setSource(playList[currentIndex]);
    mediaplayer->play();
}

// 事件过滤器实现
bool Widget::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == ui->pushButton_6 || watched == ui->verticalSlider) {
        if (event->type() == QEvent::Enter) {
            ui->verticalSlider->setVisible(true);
            return true;
        } 
        else if (event->type() == QEvent::Leave) {
            // 检查鼠标是否真的离开了控件
            QPoint globalPos = QCursor::pos();
            QPoint localPos = ui->verticalSlider->mapFromGlobal(globalPos);
            if (!ui->verticalSlider->rect().contains(localPos)) {
                ui->verticalSlider->setVisible(false);
            }
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void Widget::updatePlayModeIcon()
{
    switch (playMode) {
    case Sequence:
        ui->pushButton_2->setIcon(QIcon(":/file/one.png"));
        break;
    case Loop:
        ui->pushButton_2->setIcon(QIcon(":/file/repeat.png"));
        break;
    case Random:
        ui->pushButton_2->setIcon(QIcon(":/file/random.png"));
        break;
    }
}

void Widget::playNext()
{
    if (playList.isEmpty()) return;

    switch (playMode) {
    case Sequence:
        currentIndex = (currentIndex + 1) % playList.size();
        break;
    case Loop:
        // 单曲循环不需要改变currentIndex
        break;
    case Random:
        currentIndex = QRandomGenerator::global()->bounded(playList.size());
        break;
    }

    ui->listWidget->setCurrentRow(currentIndex);
    mediaplayer->setSource(playList[currentIndex]);
    mediaplayer->play();
}

void Widget::playPrevious()
{
    if (playList.isEmpty()) return;

    switch (playMode) {
    case Sequence:
        currentIndex = (currentIndex == 0) ? playList.size() - 1 : currentIndex - 1;
        break;
    case Loop:
        // 单曲循环不需要改变currentIndex
        break;
    case Random:
        currentIndex = QRandomGenerator::global()->bounded(playList.size());
        break;
    }

    ui->listWidget->setCurrentRow(currentIndex);
    mediaplayer->setSource(playList[currentIndex]);
    mediaplayer->play();
    ui->pushButton_4->setIcon(QIcon(":/file/playing.png"));
}
