#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPushButton>
#include <algorithm>
#include <cstring>

using namespace std;
extern "C" {
#include "../../model/s21_3DViewer_v1.h"
}

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  data_t data = {0, 0, NULL, 0.0, {0, 0, 0}, NULL, NULL, 0, NULL};

  QColor getBackgroundColor() { return backgroundColor_; }
  QColor getEdgeColor() { return edgeColor_; }
  QColor getDotColor() { return dotColor_; }

  void setBackgroundColor(QColor color) { backgroundColor_ = color; }
  void setEdgeColor(QColor color) { edgeColor_ = color; }
  void setDotColor(QColor color) { dotColor_ = color; }

  void setProjectionMode(int mode) { projectionMode_ = mode; }
  void setPointMode(int mode) { pointMode_ = mode; }
  void setPointSize(int size) { pointSize_ = size; }
  void setEdgeMode(int mode) { edgeMode_ = mode; }
  void setEdgeSize(int size) { edgeSize_ = size; }

  void initSettings();

 public slots:
  void setXTranslate(int step);
  void setYTranslate(int step);
  void setZTranslate(int step);

  void setXRotation(int angle);
  void setYRotation(int angle);
  void setZRotation(int angle);

  void setScale(int scale);

 private:
  QColor backgroundColor_;
  QColor edgeColor_;
  QColor dotColor_;

  int projectionMode_;
  int pointMode_;
  int pointSize_;
  int edgeMode_;
  int edgeSize_;

  int m_xRot = 360 * 8;
  int m_yRot = 360 * 8;
  int m_zRot = 360 * 8;
  int m_xMove = 0;
  int m_yMove = 0;
  int m_zMove = 0;
  int scaleVal = 1;

  int a_prev_x = 0;
  int a_prev_y = 0;
  int a_prev_z = 0;

  int angle_prev_x = 360 * 8;
  int angle_prev_y = 360 * 8;
  int angle_prev_z = 360 * 8;

  int prev_scale = 1;

  QPoint m_mousePosition_;
  GLfloat angle_x_, angle_y_;

  void setupPerspective();
  void Drawing();
  void pointDrawing();
  void edgeDrawing();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;

  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
};

#endif  // GLWIDGET_H
