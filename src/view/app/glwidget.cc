#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() {}

void GLWidget::initSettings() {
  projection_mode_ = 0;
  point_size_ = 3;
  point_mode_ = 1;
  edge_size_ = 1;
  edge_mode_ = 0;
  background_color_.setRgb(0, 0, 0);
  edge_color_.setRgb(255, 255, 255);
  dot_color_.setRgb(255, 255, 255);
}

void GLWidget::initializeGL() {
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glEnable(GL_DEPTH_TEST);
}

void GLWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
}

void GLWidget::paintGL() {
  glClearColor(background_color_.redF(), background_color_.greenF(),
               background_color_.blueF(), background_color_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setupPerspective();
  Drawing();
}

void GLWidget::Drawing() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_.Vertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  pointDrawing();
  edgeDrawing();
  glDisableClientState(GL_VERTEX_ARRAY);
}
void GLWidget::pointDrawing() {
  if (point_mode_ != 0) {
    glColor3d(dot_color_.redF(), dot_color_.greenF(), dot_color_.blueF());
    glPointSize(point_size_);
    if (point_mode_ == 1) {
      glEnable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, 0, controller_.CountOfVertexes());
    if (point_mode_ == 1) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}
void GLWidget::edgeDrawing() {
  glColor3d(edge_color_.redF(), edge_color_.greenF(), edge_color_.blueF());
  glLineWidth(edge_size_);
  if (edge_mode_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }

  glDrawElements(GL_LINES, controller_.PolygonSize(), GL_UNSIGNED_INT,
                 controller_.Facets());
  if (edge_mode_ == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::setupPerspective() {
  if (max_coordinate_ < 1) {
    max_coordinate_ = 2;
  }
  GLdouble z_near = 0.001;  // Ближнее расстояние отсечения
  GLdouble z_far = max_coordinate_ * 10;  // Дальнее расстояние отсечения

  if (projection_mode_ == 0) {  // Central/Perspective projection

    GLdouble fov_y = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fov_y / 360 * M_PI) * z_near;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, z_near,
              z_far);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -max_coordinate_);
  } else {  // Parallel/Orthographic projection
    glOrtho(-max_coordinate_, max_coordinate_, -max_coordinate_,
            max_coordinate_, -max_coordinate_, z_far);
  }
  glTranslated(0, 0, -3);
}

void GLWidget::setScale(int scale) {
  controller_.MakeScaling(static_cast<long double>(scale) / prev_scale_);
  prev_scale_ = scale;
  update();
}

void GLWidget::setXTranslate(int value) {
  value -= 50;
  controller_.MakeMoveX(value - shift_prev_x_);
  shift_prev_x_ = value;
  update();
}

void GLWidget::setYTranslate(int value) {
  value -= 50;
  controller_.MakeMoveY(value - shift_prev_y_);
  shift_prev_y_ = value;
  update();
}

void GLWidget::setZTranslate(int value) {
  value -= 50;
  controller_.MakeMoveZ(value - shift_prev_z_);
  shift_prev_z_ = value;
  update();
}

void GLWidget::setXRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateX(angle - angle_prev_x_);
  angle_prev_x_ = angle;
  update();
}

void GLWidget::setYRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateY(angle - angle_prev_y_);
  angle_prev_y_ = angle;
  update();
}

void GLWidget::setZRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateZ(angle - angle_prev_z_);
  angle_prev_z_ = angle;
  update();
}
