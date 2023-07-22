#ifndef SETTINGS_H
#define SETTINGS_H

#include <QColor>
#include <QDir>
#include <QFileDialog>
#include <QSettings>

class Settings {
 public:
  Settings();
  void saveFileSettings();
  void loadFileSettings();
  void clearFileSettings();

  QColor backgroundColor;
  QString projection;

  QColor vertexColor;
  int vertexSize;
  QString vertexType;

  QColor edgeColor;
  int edgeThickness;
  QString edgeType;
};

#endif  // SETTINGS_H
