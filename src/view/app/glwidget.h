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

  QColor getBackgroundColor() { return background_color_; }
  QColor getEdgeColor() { return edge_color_; }
  QColor getDotColor() { return dot_color_; }

  void setBackgroundColor(QColor color) { background_color_ = color; }
  void setEdgeColor(QColor color) { edge_color_ = color; }
  void setDotColor(QColor color) { dot_color_ = color; }

  void setProjectionMode(int mode) { projection_mode_ = mode; }
  void setPointMode(int mode) { point_mode_ = mode; }
  void setPointSize(int size) { point_size_ = size; }
  void setEdgeMode(int mode) { edge_mode_ = mode; }
  void setEdgeSize(int size) { edge_size_ = size; }

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

  QColor background_color_{};
  QColor edge_color_{};
  QColor dot_color_{};

  double max_coordinate_{};

  int projection_mode_{};
  int point_mode_{};
  int point_size_{};
  int edge_mode_{};
  int edge_size_{};

  int shift_prev_x_{};
  int shift_prev_y_{};
  int shift_prev_z_{};

  int angle_prev_x_{};
  int angle_prev_y_{};
  int angle_prev_z_{};

  long double prev_scale_ = 50.0;

  void setupPerspective();
  void Drawing();
  void pointDrawing();
  void edgeDrawing();

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // GLWIDGET_H
