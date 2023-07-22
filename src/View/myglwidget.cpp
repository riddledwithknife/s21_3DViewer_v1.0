#include "myglwidget.h"

void MyGLWidget::initializeGL() { glEnable(GL_DEPTH_TEST); }

void MyGLWidget::paintGL() {
  glClearColor(settings.backgroundColor.redF(),
               settings.backgroundColor.greenF(),
               settings.backgroundColor.blueF(), 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  glVertexPointer(3, GL_DOUBLE, 0, vector_v.data);
  glEnableClientState(GL_VERTEX_ARRAY);

  if (settings.projection == "Central") {
    glFrustum(-1, 2.55, -1, 1, 1, 15);
    glTranslated(0, 0, -10);
  } else if (settings.projection == "Parallel") {
    glOrtho(-1.0, 1.0, -1.0, 1.0, -10.0, 10.0);
  }

  setEdges();
  setVertices();

  glDisableClientState(GL_VERTEX_ARRAY);
}

void MyGLWidget::setVertices() {
  glPointSize((float)settings.vertexSize);
  glColor3f(settings.vertexColor.redF(), settings.vertexColor.greenF(),
            settings.vertexColor.blueF());

  if (settings.vertexType == "Circle") {
    glEnable(GL_POINT_SMOOTH);
    glDrawArrays(GL_POINTS, 0, (int)vector_v.index / 3);
    glDisable(GL_POINT_SMOOTH);
  } else if (settings.vertexType == "Square") {
    glDrawArrays(GL_POINTS, 0, (int)vector_v.index / 3);
  }
}

void MyGLWidget::setEdges() {
  if (settings.edgeType == "Solid") {
    glDisable(GL_LINE_STIPPLE);
  } else if (settings.edgeType == "Dashed") {
    glLineStipple(1, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  }

  glLineWidth((float)settings.edgeThickness);
  glColor3f(settings.edgeColor.redF(), settings.edgeColor.greenF(),
            settings.edgeColor.blueF());

  glDrawElements(GL_LINES, (int)vector_f.index, GL_UNSIGNED_INT, vector_f.data);
}
