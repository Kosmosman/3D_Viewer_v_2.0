#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent) : QOpenGLWidget(parent) { initSettings(); }

GLWidget::~GLWidget() { s21_remove_data(&data); }

void GLWidget::initSettings() {
  angle_x_ = angle_y_ = 0;
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
  if (data.massiv) {
    glClearColor(backgroundColor_.redF(), backgroundColor_.greenF(),
                 backgroundColor_.blueF(), backgroundColor_.alphaF());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setupPerspective();
    Drawing();
  } else {
    s21_remove_data(&data);
  }
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
  if (event->buttons() == Qt::RightButton) {
    m_mousePosition_ = event->pos();
  }
}
void GLWidget::mouseMoveEvent(QMouseEvent *event) {
  if (event->buttons() != Qt::RightButton) return;
  QPoint diff = event->pos() - m_mousePosition_;
  angle_x_ += (1 / M_PI * (diff.y()));
  angle_y_ += (1 / M_PI * (diff.x()));
  m_mousePosition_ = event->pos();
  setXRotation((angle_x_ + 180) * 16);
  setYRotation((angle_y_ + 180) * 16);
}

void GLWidget::Drawing() {
  glVertexPointer(3, GL_DOUBLE, 0, data.massiv);
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
    glDrawArrays(GL_POINTS, 1, data.count_of_vertexes);
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
  glDrawElements(GL_LINES, data.sizePolygons, GL_UNSIGNED_INT,
                 data.massivPolygons);
  if (edgeMode_ == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void GLWidget::setupPerspective() {
  if (data.max_coord < 1) {
    data.max_coord = 2;
  }
  GLdouble zNear = 0.001;  // Ближнее расстояние отсечения
  GLdouble zFar = data.max_coord * 5;  // Дальнее расстояние отсечения

  if (projectionMode_ == 0) {  // Central/Perspective projection

    GLdouble fovY = 90;  // Поле зрения в градусах по оси y
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, zNear,
              zFar);  // Устанавливает усеченный конус в режим перспективы
    glTranslatef(0, 0, -data.max_coord);
  } else {  // Parallel/Orthographic projection
    glOrtho(-data.max_coord, data.max_coord, -data.max_coord, data.max_coord,
            -data.max_coord, zFar);
  }
  glTranslated(0, 0, -3);
}

void GLWidget::setScale(int scale) {
  if (scale != scaleVal) {
    scaleVal = scale;
    s21_scale(&data, fabs(scaleVal / 1000.0f), fabs(prev_scale / 1000.0f));
    prev_scale = scaleVal;
    update();
  }
}

void GLWidget::setXTranslate(int step) {
  if (step != m_xMove) {
    m_xMove = step;
    s21_move_x(&data, 0.05 * (50 - m_xMove), 0.05 * (50 - (a_prev_x)));
    a_prev_x = m_xMove;
    update();
  }
}
void GLWidget::setYTranslate(int step) {
  if (step != m_yMove) {
    m_yMove = step;
    s21_move_y(&data, 0.05 * (50 - m_yMove), 0.05 * (50 - (a_prev_y)));
    a_prev_y = m_yMove;
    update();
  }
}
void GLWidget::setZTranslate(int step) {
  if (step != m_zMove) {
    m_zMove = step;
    s21_move_z(&data, 0.05 * (50 - m_zMove), 0.05 * (50 - (a_prev_z)));
    a_prev_z = m_zMove;
    update();
  }
}

static void qNormalizeAngle(int &angle) {
  while (angle < 0) angle += 360 * 16;
  while (angle > 360 * 16) angle -= 360 * 16;
}
void GLWidget::setXRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_xRot) {
    m_xRot = angle;
    s21_rotate_x(&data, -(180.0 - m_xRot / 16.0),
                 -(180.0 - angle_prev_x / 16.0));
    angle_prev_x = m_xRot;
    update();
  }
}
void GLWidget::setYRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_yRot) {
    m_yRot = angle;
    s21_rotate_y(&data, -(180.0 - m_yRot / 16.0),
                 -(180.0 - angle_prev_y / 16.0));
    angle_prev_y = m_yRot;
    update();
  }
}
void GLWidget::setZRotation(int angle) {
  qNormalizeAngle(angle);
  if (angle != m_zRot) {
    m_zRot = angle;
    s21_rotate_z(&data, -(180.0 - m_zRot / 16.0),
                 -(180.0 - angle_prev_z / 16.0));
    angle_prev_z = m_zRot;
    update();
  }
}