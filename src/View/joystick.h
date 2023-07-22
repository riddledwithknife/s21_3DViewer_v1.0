#ifndef S21_JOYSTICK_H
#define S21_JOYSTICK_H

#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class JoyStick : public QWidget {
 public:
  JoyStick(QWidget *parent = nullptr) : QWidget(parent) {}

 protected:
  void paintEvent(QPaintEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;

 private:
  QPoint circleStartPosition = {56, 56};
  QPoint circlePosition = {56, 56};
  int circleRadius = 10;
};

#endif  // S21_JOYSTICK_H
