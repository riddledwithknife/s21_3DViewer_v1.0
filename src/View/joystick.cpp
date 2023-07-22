#include "joystick.h"

void JoyStick::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setPen(Qt::NoPen);
  painter.setBrush(Qt::gray);

  painter.drawEllipse(circlePosition, circleRadius, circleRadius);
}

void JoyStick::mouseMoveEvent(QMouseEvent *event) {
  double value = pow(event->pos().x() - 56, 2) + pow(event->pos().y() - 56, 2);
  double radius = 50 * 50;
  if (value < radius) {
    circlePosition = event->pos();
    update();
  }
}

void JoyStick::mouseReleaseEvent(QMouseEvent *event) {
  (void)event;
  circlePosition = circleStartPosition;
  update();
}
