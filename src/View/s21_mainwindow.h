#ifndef S21_MAINWINDOW_H
#define S21_MAINWINDOW_H

#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QMainWindow>
#include <QTabBar>
#include <QTimer>
#include <QtWidgets>
#include <cmath>

#include "QtGifImage/gifimage/qgifimage.h"
#include "joystick.h"
#include "myglwidget.h"

extern "C" {
#include "../Model/parser.h"
#include "../Model/transformation.h"
#include "QtGifImage/gifimage/qgifimage.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class s21_MainWindow;
}
QT_END_NAMESPACE

class s21_MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  s21_MainWindow(QWidget* parent = nullptr);
  ~s21_MainWindow();

 private slots:
  void on_BackgroundColor_clicked();
  void on_ProjectionButton_clicked();
  void on_VertexButton_clicked();
  void on_EdgeButton_clicked();
  void on_LittleProjection_clicked();
  void on_VertexColor_clicked();
  void on_VertexSize_textChanged();
  void on_TopVertex_clicked();
  void on_BottomVertex_clicked();
  void on_EdgeColor_clicked();
  void on_EdgeThickness_textChanged();
  void on_LittleEdge_clicked();
  void on_Open_clicked();
  void on_Increase_clicked();
  void on_Decrease_clicked();
  void on_Reset_clicked();
  void on_ShowMenu_clicked();
  void on_Screenshot_clicked();
  void on_Gif_clicked();
  void saveGif();
  void mouseMoveEvent(QMouseEvent* cursor_position) override;
  void mousePressEvent(QMouseEvent* event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void mouseReleaseEvent(QMouseEvent* cursor_position) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void wheelEvent(QWheelEvent* event) override;
  void updateUi();

 private:
  Ui::s21_MainWindow* ui;
  JoyStick* joyStick;
  MyGLWidget* model;
  QGifImage* gif;
  QTimer* timer;
  int frames;

  vector* vector_v{};
  vector_int* vector_f{};

  QPoint click_pos;
  bool leftButtonPressed;
  bool rightButtonPressed;
  bool zPressed;
};

#endif  // S21_MAINWINDOW_H
