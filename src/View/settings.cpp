#include "settings.h"

Settings::Settings() { loadFileSettings(); }

void Settings::saveFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  settingsFile.setValue("backgroundColor", backgroundColor.name());
  settingsFile.setValue("projection", projection);

  settingsFile.setValue("vertexColor", vertexColor.name());
  settingsFile.setValue("vertexSize", vertexSize);
  settingsFile.setValue("vertexType", vertexType);

  settingsFile.setValue("edgeColor", edgeColor.name());
  settingsFile.setValue("edgeThickness", edgeThickness);
  settingsFile.setValue("edgeType", edgeType);
}

void Settings::loadFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  backgroundColor =
      settingsFile.value("backgroundColor", QColor(30, 30, 30)).toString();
  projection = settingsFile.value("projection", "Parallel").toString();

  vertexColor =
      settingsFile.value("vertexColor", QColor(255, 255, 255)).toString();
  vertexSize = settingsFile.value("vertexSize", 10).toInt();
  vertexType = settingsFile.value("vertexType", "Circle").toString();

  edgeColor = settingsFile.value("edgeColor", QColor(255, 255, 255)).toString();
  edgeThickness = settingsFile.value("edgeThickness", 5).toInt();
  edgeType = settingsFile.value("edgeType", "Solid").toString();
}

void Settings::clearFileSettings() {
  QSettings settingsFile("s21", "3DViewer");

  settingsFile.clear();
}