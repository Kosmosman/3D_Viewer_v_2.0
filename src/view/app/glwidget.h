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

#include "../../controller/controller.h"

using namespace std;

class GLWidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  GLWidget(QWidget *parent = nullptr);
  ~GLWidget();

  int GetCountOfFacets() { return controller_.CountOfFacets(); };
  int GetCountOfVertexes() { return controller_.CountOfVertexes(); };
  void Reset() { controller_.Reset(); }
  void InitModel(std::string file) {
    controller_.InitModel(file);
    max_coordinate_ = controller_.MaxCoordinate();
  };

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
  s21::Controller controller_;
  QColor backgroundColor_;
  QColor edgeColor_;
  QColor dotColor_;

  double max_coordinate_;

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
