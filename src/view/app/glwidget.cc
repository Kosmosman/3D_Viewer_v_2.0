#include "glwidget.h"

#include <iostream>

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() {}

void GLWidget::initSettings() {
  angle_x_ = angle_y_ = 0;
  shift_x = shift_y = 0;
  projectionMode_ = 0;
  pointSize_ = 3;
  pointMode_ = 1;
  edgeSize_ = 1;
  edgeMode_ = 0;
  backgroundColor_.setRgb(0, 0, 0);
  edgeColor_.setRgb(255, 255, 255);
  dotColor_.setRgb(255, 255, 255);
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
  glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(),
               backgroundColor_.blueF(), backgroundColor_.alphaF());
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  setupPerspective();
  Drawing();
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::RightButton) {
    m_mousePosition_ = event->pos();
  }
}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::RightButton) {
    QPoint diff = event->pos() - m_mousePosition_;
    angle_x_ += (1 / M_PI * (diff.y()));
    angle_y_ += (1 / M_PI * (diff.x()));
    m_mousePosition_ = event->pos();
    setXRotation(angle_x_ + 180);
    setYRotation(angle_y_ + 180);
  } else if (event->buttons() == Qt::LeftButton) {
    QPoint diff = event->pos() - m_mousePosition_;
    shift_x += diff.x();
    shift_y += diff.y();
    m_mousePosition_ = event->pos();
    setXTranslate(shift_x);
    setYTranslate(-shift_y);
  } else {
    return;
  }
}

void GLWidget::Drawing() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_.Vertexes());
  glEnableClientState(GL_VERTEX_ARRAY);
  pointDrawing();
  edgeDrawing();
  glDisableClientState(GL_VERTEX_ARRAY);
}
void GLWidget::pointDrawing() {
  if (pointMode_ != 0) {
    glColor3d(dotColor_.redF(), dotColor_.greenF(), dotColor_.blueF());
    glPointSize(pointSize_);
    if (pointMode_ == 1) {
      glEnable(GL_POINT_SMOOTH);
    }
    glDrawArrays(GL_POINTS, 1, controller_.CountOfVertexes());
    if (pointMode_ == 1) {
      glDisable(GL_POINT_SMOOTH);
    }
  }
}
void GLWidget::edgeDrawing() {
  glColor3d(edgeColor_.redF(), edgeColor_.greenF(), edgeColor_.blueF());
  glLineWidth(edgeSize_);
  if (edgeMode_ == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(2, 0x00F0);
  }
  glDrawElements(GL_LINES, controller_.CountOfFacets(), GL_UNSIGNED_INT,
                 controller_.Facets());
  if (edgeMode_ == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::setupPerspective() {
  if (max_coordinate_ < 1) {
    max_coordinate_ = 2;
  }
  GLdouble zNear = 0.001;  // Ближнее расстояние отсечения
  GLdouble zFar = max_coordinate_ * 5;  // Дальнее расстояние отсечения

  if (projectionMode_ == 0) {  // Central/Perspective projection

    GLdouble fovY = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, zNear,
              zFar);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -max_coordinate_);
  } else {  // Parallel/Orthographic projection
    glOrtho(-max_coordinate_, max_coordinate_, -max_coordinate_,
            max_coordinate_, -max_coordinate_, zFar);
  }
  glTranslated(0, 0, -3);
}

void GLWidget::setScale(int scale) {
  controller_.MakeScaling(scale);
  update();
}

void GLWidget::setXTranslate(int value) {
  value -= 50;
  controller_.MakeMoveX(value - a_prev_x);
  a_prev_x = value;
  update();
}
void GLWidget::setYTranslate(int value) {
  value -= 50;
  controller_.MakeMoveY(value - a_prev_y);
  a_prev_y = value;
  update();
}
void GLWidget::setZTranslate(int value) {
  value -= 50;
  controller_.MakeMoveZ(value - a_prev_z);
  a_prev_z = value;
  update();
}

void GLWidget::setXRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateX(angle - angle_prev_x);
  angle_prev_x = angle;
  update();
}
void GLWidget::setYRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateY(angle - angle_prev_y);
  angle_prev_y = angle;
  update();
}
void GLWidget::setZRotation(int angle) {
  angle -= 180;
  controller_.MakeRotateZ(angle - angle_prev_z);
  angle_prev_z = angle;
  update();
}
