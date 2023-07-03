#ifndef GLWIDGET_H
#define GLWIDGET_H

#define GL_SILENCE_DEPRECATION

#include <QColor>
#include <QColorDialog>
#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QPushButton>
#include <QWheelEvent>
#include <algorithm>
#include <cstring>

#include "../../Model/basic_model/model.h"

using namespace std;
// extern "C" {
// #include "../../model/s21_3DViewer_v1.h"
// }

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();
  s21::Model model_;
  void initModel(std::string &filename);

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

  int a_prev_x = 0;
  int a_prev_y = 0;
  int a_prev_z = 0;

  int angle_prev_x = 0;
  int angle_prev_y = 0;
  int angle_prev_z = 0;

  long double prev_scale = 50.0;

  QPoint m_mousePosition_;
  GLfloat shift_x, shift_y;
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
