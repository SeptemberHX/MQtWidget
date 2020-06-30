#ifndef MQSWITCH_H
#define MQSWITCH_H

#include <QWidget>
#include <QColor>
#include <QVariantAnimation>

class MQSwitch : public QWidget
{
    Q_OBJECT
public:
    explicit MQSwitch(QWidget *parent = nullptr);
    bool isChecked() const;
    void setChecked(int checked);

signals:
    void toggled(bool checked);
    void stateChanged(bool state);

public slots:

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void redrawWithAnim();

private:
    bool checked;

    int slideRadius;
    int slideHeight;

    int slidePenSize;

    QColor offSlideColor;
    QColor offCircleColor;
    QColor onSlideColor;
    QColor onCircleColor;

    QVariantAnimation *m_animation;
    int circleXOffset;
};

#endif // MQSWITCH_H
