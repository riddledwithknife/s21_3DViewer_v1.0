#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#define GL_SILENCE_DEPRECATION
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#if defined(__APPLE__)
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "settings.h"

extern "C" {
#include "../Model/vector.h"
}

class MyGLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  MyGLWidget(QWidget *parent = nullptr) : QOpenGLWidget(parent) {}

 protected:
  void initializeGL() override;
  void paintGL() override;
  void setVertices();
  void setEdges();

 public:
  vector vector_v{};
  vector_int vector_f{};
  Settings settings;
};

#endif  // MYGLWIDGET_H
