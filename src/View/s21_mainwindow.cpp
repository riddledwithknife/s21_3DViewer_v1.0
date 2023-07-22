#include "s21_mainwindow.h"

#include "./ui_s21_mainwindow.h"

s21_MainWindow::s21_MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::s21_MainWindow) {
  ui->setupUi(this);
  ui->Screenshot->hide();
  ui->Gif->hide();
  ui->SettingsTab->tabBar()->hide();

  joyStick = new JoyStick(this);
  joyStick->resize(112, 112);
  joyStick->move(870, 40);
  joyStick->setStyleSheet(
      "background-color: rgb(64, 64, 64);\n border-radius: 55px");

  model = new MyGLWidget(ui->openGLWidget);
  model->resize(800, 800);

  updateUi();
  model->update();
}

s21_MainWindow::~s21_MainWindow() {
  if (model->vector_v.data != nullptr) {
    free(model->vector_v.data);
    free(model->vector_f.data);
  }

  delete model;
  delete joyStick;
  delete ui;
}

void s21_MainWindow::on_BackgroundColor_clicked() {
  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss = QString(
                        "background-color: %1;\n border:1px solid;\n "
                        "border-color: black;")
                        .arg(color.name());
      ui->BackgroundColor->setStyleSheet(qss);

      model->settings.backgroundColor = color;
      model->settings.saveFileSettings();
      model->update();
    }
  }
}

void s21_MainWindow::on_ProjectionButton_clicked() {
  ui->SettingsTab->setCurrentIndex(0);
}

void s21_MainWindow::on_VertexButton_clicked() {
  ui->SettingsTab->setCurrentIndex(1);
}

void s21_MainWindow::on_EdgeButton_clicked() {
  ui->SettingsTab->setCurrentIndex(2);
}

void s21_MainWindow::on_LittleProjection_clicked() {
  QString tempString = ui->LittleProjection->text();

  ui->LittleProjection->setText(ui->BigProjection->text());
  ui->BigProjection->setText(tempString);

  model->settings.projection = tempString;
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_VertexColor_clicked() {
  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss = QString(
                        "background-color: %1;\n border:1px solid;\n "
                        "border-color: black;")
                        .arg(color.name());
      ui->VertexColor->setStyleSheet(qss);

      model->settings.vertexColor = color;
      model->settings.saveFileSettings();
      model->update();
    }
  }
}

void s21_MainWindow::on_VertexSize_textChanged() {
  ui->VertexSize->setMaxLength(3);

  model->settings.vertexSize = ui->VertexSize->text().toInt();
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_TopVertex_clicked() {
  QString tempStringTop = ui->TopVertex->text();
  QString tempStringCentral = ui->CentralVertex->text();

  ui->CentralVertex->setText(tempStringTop);
  ui->TopVertex->setText(ui->BottomVertex->text());
  ui->BottomVertex->setText(tempStringCentral);

  model->settings.vertexType = tempStringTop;
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_BottomVertex_clicked() {
  QString tempStringBottom = ui->BottomVertex->text();
  QString tempStringCentral = ui->CentralVertex->text();

  ui->CentralVertex->setText(tempStringBottom);
  ui->BottomVertex->setText(ui->TopVertex->text());
  ui->TopVertex->setText(tempStringCentral);

  model->settings.vertexType = tempStringBottom;
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_EdgeColor_clicked() {
  QColorDialog dialog;

  dialog.setOption(QColorDialog::ShowAlphaChannel);

  if (dialog.exec() == QDialog::Accepted) {
    QColor color = dialog.selectedColor();
    if (color.isValid()) {
      QString qss =
          QString(
              "background-color: %1;\nborder:1px solid;\n border-color: black;")
              .arg(color.name());
      ui->EdgeColor->setStyleSheet(qss);

      model->settings.edgeColor = color;
      model->settings.saveFileSettings();
      model->update();
    }
  }
}

void s21_MainWindow::on_EdgeThickness_textChanged() {
  ui->EdgeThickness->setMaxLength(3);

  model->settings.edgeThickness = ui->EdgeThickness->text().toInt();
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_LittleEdge_clicked() {
  QString tempString = ui->LittleEdge->text();

  ui->LittleEdge->setText(ui->BigEdge->text());
  ui->BigEdge->setText(tempString);

  model->settings.edgeType = tempString;
  model->settings.saveFileSettings();
  model->update();
}

void s21_MainWindow::on_Open_clicked() {
  QString path = QDir::currentPath();
  QString fileName =
      QFileDialog::getOpenFileName(this, tr("Open obj file"), path + "../../",
                                   tr("Obj Files (*.obj)"))
          .toUtf8()
          .constData();

  if (!fileName.isEmpty() && !fileName.isNull()) {
    QByteArray fileNameArr = fileName.toUtf8();
    const char *fileNameConst = fileNameArr.constData();
    char *fileNameChar = (char *)fileNameConst;
    if (model->vector_v.data != nullptr) {
      free(model->vector_v.data);
      free(model->vector_f.data);
    }
    model->vector_v = s21_create_vector();
    model->vector_f = s21_create_vector_int();

    parser(fileNameChar, &model->vector_v, &model->vector_f);
    centralize(&model->vector_v);

    ui->Filename->setText(fileName.section("/", -1, -1));
    ui->CountOfVertices->setText(QString::number(model->vector_v.index / 3));
    ui->CountOfEdges->setText(QString::number(model->vector_f.index / 4));

    model->update();
  }
}

void s21_MainWindow::on_Increase_clicked() {
  scale(&model->vector_v, 110);

  model->update();
}

void s21_MainWindow::on_Decrease_clicked() {
  scale(&model->vector_v, 90);

  model->update();
}

void s21_MainWindow::on_Reset_clicked() {
  model->settings.clearFileSettings();
  model->settings.loadFileSettings();

  updateUi();
  model->update();
}

void s21_MainWindow::on_ShowMenu_clicked() {
  if (!ui->Screenshot->isVisible() && !ui->Gif->isVisible()) {
    ui->ShowMenu->setText("↓");
    ui->Screenshot->show();
    ui->Gif->show();
  } else if (ui->Screenshot->isVisible() && ui->Gif->isVisible()) {
    ui->ShowMenu->setText("↑");
    ui->Screenshot->hide();
    ui->Gif->hide();
  }
}

void s21_MainWindow::on_Screenshot_clicked() {
  QString saveImage = QFileDialog::getSaveFileName(
      this, nullptr, nullptr, "JPEG (*.jpeg) ;; BMP (*.bmp");

  if (!saveImage.isEmpty() && !saveImage.isNull()) {
    model->grabFramebuffer().save(saveImage, nullptr, 100);
  }
}

void s21_MainWindow::on_Gif_clicked() {
  frames = 0;
  gif = new QGifImage;
  timer = new QTimer(this);

  ui->Gif->setStyleSheet(
      "color: red;\n border-radius: 1px;\n border-bottom: 1px solid grey;\n "
      "background-color: rgb(64, 64, 64);");

  gif->setDefaultDelay(100);
  connect(timer, SIGNAL(timeout()), this, SLOT(saveGif()));
  timer->start(100);
}

void s21_MainWindow::saveGif() {
  QPixmap pix = QPixmap::fromImage(model->grabFramebuffer());
  QPixmap scaledPix = pix.scaled(QSize(640, 480), Qt::IgnoreAspectRatio,
                                 Qt::SmoothTransformation);
  gif->addFrame(scaledPix.toImage());

  if (frames == 50) {
    timer->stop();
    QString pathGIF = QFileDialog::getSaveFileName(
        this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)");

    if (!pathGIF.isEmpty() && !pathGIF.isNull()) {
      gif->save(pathGIF);
      delete timer;
      delete gif;
    } else {
      delete timer;
      delete gif;
    }
  }
  frames++;

  ui->Gif->setStyleSheet(
      "color: rgb(154, 154, 154);\n border-radius: 1px;\n border-bottom: 1px "
      "solid grey;\n background-color: rgb(64, 64, 64);");
}

void s21_MainWindow::mouseMoveEvent(QMouseEvent *cursor_position) {
  if (leftButtonPressed) {
    int rx = (cursor_position->pos().y() - click_pos.y()) / 3;
    int ry = (cursor_position->pos().x() - click_pos.x()) / 3;

    rotate_x(&model->vector_v, (float)rx);
    rotate_y(&model->vector_v, (float)ry);

  } else if (rightButtonPressed) {
    int mx = (cursor_position->pos().x() - click_pos.x()) / 12;
    int my = (click_pos.y() - cursor_position->pos().y()) / 12;

    move_x(&model->vector_v, (float)mx);
    move_y(&model->vector_v, (float)my);
  }

  click_pos.setX(cursor_position->pos().x());
  click_pos.setY(cursor_position->pos().y());

  model->update();
}

void s21_MainWindow::mousePressEvent(QMouseEvent *event) {
  click_pos = event->pos();

  if (event->button() == Qt::LeftButton) {
    leftButtonPressed = true;
  } else if (event->button() == Qt::RightButton) {
    rightButtonPressed = true;
  }
}

void s21_MainWindow::keyPressEvent(QKeyEvent *event) {
  if (event->key() == Qt::Key_Z) {
    zPressed = true;
  }
}

void s21_MainWindow::mouseReleaseEvent(QMouseEvent *cursor_position) {
  leftButtonPressed = false;
  rightButtonPressed = false;

  click_pos = cursor_position->pos();
}

void s21_MainWindow::keyReleaseEvent(QKeyEvent *event) { zPressed = false; }

void s21_MainWindow::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0 && zPressed) {
    move_z(&model->vector_v, event->angleDelta().y() / 12);
  } else if (event->angleDelta().y() < 0 && zPressed) {
    move_z(&model->vector_v, event->angleDelta().y() / 12);
  }

  if (event->angleDelta().y() > 0) {
    on_Increase_clicked();

  } else if (event->angleDelta().y() < 0) {
    on_Decrease_clicked();
  }
}

void s21_MainWindow::updateUi() {
  ui->BackgroundColor->setStyleSheet(
      QString(
          "background-color: %1;\n border:1px solid;\n border-color: black;")
          .arg(model->settings.backgroundColor.name()));
  if (model->settings.projection == "Central" ||
      ui->BigProjection->text() == "Central") {
    QString tempString = ui->LittleProjection->text();

    ui->LittleProjection->setText(ui->BigProjection->text());
    ui->BigProjection->setText(tempString);
  }

  ui->VertexColor->setStyleSheet(
      QString(
          "background-color: %1;\n border:1px solid;\n border-color: black;")
          .arg(model->settings.vertexColor.name()));
  ui->VertexSize->setText(QString::number(model->settings.vertexSize));
  if (model->settings.vertexType == "Absent" ||
      ui->CentralVertex->text() == "Square") {
    QString tempStringTop = ui->TopVertex->text();
    QString tempStringCentral = ui->CentralVertex->text();

    ui->CentralVertex->setText(tempStringTop);
    ui->TopVertex->setText(ui->BottomVertex->text());
    ui->BottomVertex->setText(tempStringCentral);
  } else if (model->settings.vertexType == "Square" ||
             ui->CentralVertex->text() == "Absent") {
    QString tempStringBottom = ui->BottomVertex->text();
    QString tempStringCentral = ui->CentralVertex->text();

    ui->CentralVertex->setText(tempStringBottom);
    ui->BottomVertex->setText(ui->TopVertex->text());
    ui->TopVertex->setText(tempStringCentral);
  }

  ui->EdgeColor->setStyleSheet(
      QString("background-color: %1;\nborder:1px solid;\n border-color: black;")
          .arg(model->settings.edgeColor.name()));
  ui->EdgeThickness->setText(QString::number(model->settings.edgeThickness));
  if (model->settings.edgeType == "Dashed" || ui->BigEdge->text() == "Dashed") {
    QString tempString = ui->LittleEdge->text();

    ui->LittleEdge->setText(ui->BigEdge->text());
    ui->BigEdge->setText(tempString);
  }
}
