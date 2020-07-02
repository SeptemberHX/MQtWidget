#include "MQSwitch.h"
#include <QPaintEvent>
#include <QPainter>
#include <QRect>
#include <QMouseEvent>

MQSwitch::MQSwitch(QWidget *parent)
    : QWidget(parent)
    , checked(false)
    , slideRadius(5)
    , slideHeight(10)
    , slidePenSize(3)
{
    this->offSlideColor = QColor(225, 225, 225);
    this->offCircleColor = QColor(196, 196, 196);
    this->onSlideColor = QColor(146, 199, 241);
    this->onCircleColor = QColor(32, 147, 238);
    this->setMinimumHeight(this->slideHeight * 2);
    this->setMinimumWidth(this->slideRadius * 4);

    this->m_animation = new QVariantAnimation(this);
    this->m_animation->setDuration(200);
    connect(this->m_animation, &QVariantAnimation::valueChanged, this, [this](const QVariant& value) {
        this->circleXOffset = value.toInt();
        this->repaint();
    });
}

bool MQSwitch::isChecked() const
{
    return this->checked;
}

void MQSwitch::setChecked(int checked)
{
    if (this->checked == checked) {
        return;
    }
    this->checked = checked;
    Q_EMIT stateChanged(this->checked);
    this->redrawWithAnim();
}

void MQSwitch::paintEvent(QPaintEvent *event)
{
    QRect slideRect(event->rect().topLeft() + QPoint(this->slidePenSize, (event->rect().height() - this->slideHeight) / 2),
                    QSize(event->rect().width() - 2 * this->slidePenSize, this->slideHeight));

    // draw slide part
    QPainter painter(this);
    if (this->isChecked()) {
        painter.setPen(QPen(this->onSlideColor, this->slidePenSize));
    } else {
        painter.setPen(QPen(this->offSlideColor, this->slidePenSize));
    }
    painter.drawRoundedRect(slideRect, this->slideRadius, this->slideRadius);

    // draw circle part
    QPoint circleTopLeft = event->rect().topLeft() + QPoint(this->slidePenSize + this->circleXOffset, (event->rect().height() - this->slideHeight * 2) / 2);
    QRect circleRect(circleTopLeft, QSize(this->slideHeight * 2, this->slideHeight * 2));
    if (this->isChecked()) {
        painter.setPen(this->onCircleColor);
        painter.setBrush(this->onCircleColor);
    } else {
        painter.setPen(this->offCircleColor);
        painter.setBrush(this->offCircleColor);
    }
    painter.drawEllipse(circleRect);
}

void MQSwitch::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->checked = !this->checked;
        Q_EMIT stateChanged(this->checked);
        Q_EMIT toggled(this->checked);
        this->redrawWithAnim();
    }
    QWidget::mousePressEvent(event);
}

void MQSwitch::resizeEvent(QResizeEvent *event)
{
    if (this->isChecked()) {
        this->circleXOffset = this->width() - this->slideRadius * 4;
    }
    QWidget::resizeEvent(event);
    this->repaint();
}

void MQSwitch::redrawWithAnim()
{
    if (this->isChecked()) {
        this->m_animation->setStartValue(0);
        this->m_animation->setEndValue(this->width() - this->slideRadius * 4 - this->slidePenSize);
    } else {
        this->m_animation->setStartValue(this->width() - this->slideRadius * 4 - this->slidePenSize);
        this->m_animation->setEndValue(0);
    }
    this->m_animation->start();
}
