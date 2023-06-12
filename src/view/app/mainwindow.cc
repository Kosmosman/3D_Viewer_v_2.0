#include "mainwindow.h"

#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui_(new Ui::MainWindow) {
  ui_->setupUi(this);
  initSetup();
  defaultSettings();
}

MainWindow::~MainWindow() {
  saveSettings();
  delete timer_;
  delete[] gifImage_;
  delete ui_;
}

void MainWindow::initSetup() {
  setWindowTitle("3DViewer_v2.0");
  this->settingFile_ = QApplication::applicationDirPath() + "/settings.conf";

  timer_ = new QTimer;
  gifImage_ = new QImage[50]{};
  connect(timer_, SIGNAL(timeout()), this, SLOT(slotTimer()));

  translateScrollbarSetup();
  rotateScrollbarSetup();
  scaleScrollbarSetup();
  projectionTypeSetup();
  verticiesParametersSetup();
  edgesParametersSetup();
  colorSetup();

  connect(ui_->open_button, &QPushButton::pressed, (this),
          &MainWindow::fileHandling);
  connect(ui_->screenshot_button, &QPushButton::pressed, (this),
          &MainWindow::screenshotMaking);
  connect(ui_->gif_button, &QPushButton::pressed, (this),
          &MainWindow::gifMaking);
  connect(ui_->reset_values_button, SIGNAL(released()), (this),
          SLOT(resetValue()));
}

void MainWindow::translateScrollbarSetup() {
  this->translateScrollbars_ = {ui_->scrollbar_translate_x,
                                ui_->scrollbar_translate_y,
                                ui_->scrollbar_translate_z};
  this->translateLineEdits_ = {ui_->line_edit_translate_x,
                               ui_->line_edit_translate_y,
                               ui_->line_edit_translate_z};

  for (auto &iterTranslate : this->translateScrollbars_) {
    iterTranslate->setRange(0, 100);
    iterTranslate->setSingleStep(1);
    connect(iterTranslate, &QScrollBar::valueChanged, (this),
            &MainWindow::translateScrollbarValueChanged);
  }
  for (auto &iterTranslateLineEdits : this->translateLineEdits_) {
    connect(iterTranslateLineEdits, SIGNAL(editingFinished()), (this),
            SLOT(translateTextEdit()));
  }

  connect(ui_->scrollbar_translate_x, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setXTranslate);
  connect(ui_->scrollbar_translate_y, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setYTranslate);
  connect(ui_->scrollbar_translate_z, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setZTranslate);
}
void MainWindow::translateScrollbarValueChanged(int value) {
  value -= 50;
  QScrollBar *scrollbar = (QScrollBar *)sender();
  if (scrollbar == ui_->scrollbar_translate_x) {
    ui_->line_edit_translate_x->setText(QString::number(value));
  } else if (scrollbar == ui_->scrollbar_translate_y) {
    ui_->line_edit_translate_y->setText(QString::number(value));
  } else if (scrollbar == ui_->scrollbar_translate_z) {
    ui_->line_edit_translate_z->setText(QString::number(value));
  }
}
void MainWindow::translateTextEdit() {
  QLineEdit *line_edit = (QLineEdit *)sender();
  int value = line_edit->text().toInt() + 50;

  if (line_edit == ui_->line_edit_translate_x) {
    ui_->scrollbar_translate_x->setValue(value);
  } else if (line_edit == ui_->line_edit_translate_y) {
    ui_->scrollbar_translate_y->setValue(value);
  } else if (line_edit == ui_->line_edit_translate_z) {
    ui_->scrollbar_translate_z->setValue(value);
  }
}

void MainWindow::rotateScrollbarSetup() {
  this->rotateScrollbars_ = {ui_->scrollbar_rotate_x, ui_->scrollbar_rotate_y,
                             ui_->scrollbar_rotate_z};
  this->rotateLineEdits_ = {ui_->line_edit_rotate_x, ui_->line_edit_rotate_y,
                            ui_->line_edit_rotate_z};

  for (auto &iterRotate : this->rotateScrollbars_) {
    iterRotate->setRange(0, 360 * 16);
    iterRotate->setSingleStep(16);
    iterRotate->setPageStep(15 * 16);
    connect(iterRotate, &QScrollBar::valueChanged, (this),
            &MainWindow::rotateScrollbarValueChanged);
  }
  for (auto &iterRotateLineEdits : this->rotateLineEdits_) {
    connect(iterRotateLineEdits, SIGNAL(editingFinished()), (this),
            SLOT(rotateTextEdit()));
  }

  connect(ui_->scrollbar_rotate_x, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setXRotation);
  connect(ui_->scrollbar_rotate_y, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setYRotation);
  connect(ui_->scrollbar_rotate_z, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setZRotation);
}
void MainWindow::rotateScrollbarValueChanged(int value) {
  value = value / 16 - 180;
  QScrollBar *scrollbar = (QScrollBar *)sender();
  if (scrollbar == ui_->scrollbar_rotate_x) {
    ui_->line_edit_rotate_x->setText(QString::number(value));
  } else if (scrollbar == ui_->scrollbar_rotate_y) {
    ui_->line_edit_rotate_y->setText(QString::number(value));
  } else if (scrollbar == ui_->scrollbar_rotate_z) {
    ui_->line_edit_rotate_z->setText(QString::number(value));
  }
}
int valueNormalize(int val) {
  while (val > 180) {
    val -= 360;
  }
  while (val < -180) {
    val += 360;
  }
  return val;
}
void MainWindow::rotateTextEdit() {
  QLineEdit *line_edit = (QLineEdit *)sender();
  int val = (line_edit->text().toInt() + 180) * 16;

  if (line_edit == ui_->line_edit_rotate_x) {
    ui_->scrollbar_rotate_x->setValue(val);
  } else if (line_edit == ui_->line_edit_rotate_y) {
    ui_->scrollbar_rotate_y->setValue(val);
  } else if (line_edit == ui_->line_edit_rotate_z) {
    ui_->scrollbar_rotate_z->setValue(val);
  }
  // valueNormalize(val);
  // ui_->OGLWidget->setXRotation(val * 16);
}

void MainWindow::scaleScrollbarSetup() {
  ui_->scrollbar_scale->setRange(1, 100);
  ui_->scrollbar_scale->setSingleStep(1);

  connect(ui_->scrollbar_scale, &QScrollBar::valueChanged, ui_->OGLWidget,
          &GLWidget::setScale);
  connect(ui_->scale_text, SIGNAL(editingFinished()), (this),
          SLOT(scaleTextEdit()));
  // Connecting scrollbar scale to text
  connect(ui_->scrollbar_scale, &QScrollBar::valueChanged, (this),
          &MainWindow::scaleScrollbarValueChanged);
}
void MainWindow::scaleScrollbarValueChanged(int value) {
  ui_->scale_text->setText(QString::number(value));
}
void MainWindow::scaleTextEdit() {
  int val = ui_->scale_text->text().toInt();
  ui_->scrollbar_scale->setValue(val);
}

void MainWindow::projectionTypeSetup() {
  connect(ui_->type_of_projection_parallel_button, &QRadioButton::pressed,
          (this), &MainWindow::projectionType);
  connect(ui_->type_of_projection_central_button, &QRadioButton::pressed,
          (this), &MainWindow::projectionType);
}
void MainWindow::projectionType() {
  QRadioButton *radiobutton = (QRadioButton *)sender();
  if (radiobutton == ui_->type_of_projection_central_button) {
    ui_->OGLWidget->projectionMode = 0;
  } else {
    ui_->OGLWidget->projectionMode = 1;
  }
  ui_->OGLWidget->update();
}

void MainWindow::verticiesParametersSetup() {
  ui_->scrollbar_vertices->setRange(1, 10);
  ui_->scrollbar_vertices->setSingleStep(1);
  connect(ui_->scrollbar_vertices, &QScrollBar::valueChanged, (this),
          &MainWindow::verticeSize);

  connect(ui_->verticies_disable_button, &QRadioButton::pressed, (this),
          &MainWindow::verticeType);
  connect(ui_->verticies_circle_button, &QRadioButton::pressed, (this),
          &MainWindow::verticeType);
  connect(ui_->verticies_square_button, &QRadioButton::pressed, (this),
          &MainWindow::verticeType);
}
void MainWindow::verticeType() {
  QRadioButton *radiobutton = (QRadioButton *)sender();
  if (radiobutton == ui_->verticies_disable_button) {
    ui_->OGLWidget->pointMode = 0;
    ui_->scrollbar_vertices->setValue(0);
    ui_->scrollbar_vertices->setEnabled(false);
  } else if (radiobutton == ui_->verticies_circle_button) {
    ui_->OGLWidget->pointMode = 1;
    ui_->scrollbar_vertices->setEnabled(true);
  } else {
    ui_->OGLWidget->pointMode = 2;
    ui_->scrollbar_vertices->setEnabled(true);
  }
  ui_->OGLWidget->update();
}
void MainWindow::verticeSize(int value) {
  ui_->OGLWidget->pointSize = value;
  ui_->OGLWidget->update();
}

void MainWindow::edgesParametersSetup() {
  ui_->scrollbar_edges->setRange(1, 10);
  ui_->scrollbar_edges->setSingleStep(1);
  connect(ui_->scrollbar_edges, &QScrollBar::valueChanged, (this),
          &MainWindow::edgeSizeScrollbarChanged);

  connect(ui_->edges_solid_button, &QRadioButton::pressed, (this),
          &MainWindow::edgeType);
  connect(ui_->dashed_solid_button, &QRadioButton::pressed, (this),
          &MainWindow::edgeType);
}
void MainWindow::edgeType() {
  QRadioButton *radiobutton = (QRadioButton *)sender();
  if (radiobutton == ui_->edges_solid_button) {
    ui_->OGLWidget->edgeMode = 0;
  } else {
    ui_->OGLWidget->edgeMode = 1;
  }
  ui_->OGLWidget->update();
}
void MainWindow::edgeSizeScrollbarChanged(int value) {
  ui_->OGLWidget->edgeSize = value;
  ui_->OGLWidget->update();
}

void MainWindow::colorSetup() {
  connect(ui_->background_color_button, SIGNAL(released()), (this),
          SLOT(onChangeColor()));
  connect(ui_->color_verticies_button, SIGNAL(released()), (this),
          SLOT(onChangeColor()));
  connect(ui_->color_edges_button, SIGNAL(released()), (this),
          SLOT(onChangeColor()));
}
void MainWindow::onChangeColor() {
  QColor color = QColorDialog::getColor(Qt::white, this, "Select Color",
                                        QColorDialog::DontUseNativeDialog);
  QPushButton *button = (QPushButton *)sender();
  if (button == ui_->background_color_button) {
    ui_->OGLWidget->backgroundColor = color;
  } else if (button == ui_->color_edges_button) {
    ui_->OGLWidget->edgeColor = color;
  } else {
    ui_->OGLWidget->dotColor = color;
  }
  updateUiColors();
}
void MainWindow::updateUiColors() {
  ui_->graphics_background_color->setAutoFillBackground(true);
  ui_->graphics_background_color->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui_->OGLWidget->backgroundColor.red())
          .arg(ui_->OGLWidget->backgroundColor.green())
          .arg(ui_->OGLWidget->backgroundColor.blue()));
  ui_->graphics_color_edges->setAutoFillBackground(true);
  ui_->graphics_color_edges->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui_->OGLWidget->edgeColor.red())
          .arg(ui_->OGLWidget->edgeColor.green())
          .arg(ui_->OGLWidget->edgeColor.blue()));
  ui_->graphics_verticies_color->setAutoFillBackground(true);
  ui_->graphics_verticies_color->setStyleSheet(
      QString("border-style: solid; border-width: 1px; border-color: black; "
              "padding-top: 3px; background-color: rgb(%1, %2, %3);")
          .arg(ui_->OGLWidget->dotColor.red())
          .arg(ui_->OGLWidget->dotColor.green())
          .arg(ui_->OGLWidget->dotColor.blue()));
  ui_->OGLWidget->update();
}

void MainWindow::defaultScrollbars() {
  for (auto &iterTranslate : this->translateScrollbars_) {
    iterTranslate->setValue(50);
  }
  for (auto &iterTranslateLineEdits : this->translateLineEdits_) {
    iterTranslateLineEdits->setText(QString::number(0));
  }

  for (auto &iterRotate : this->rotateScrollbars_) {
    iterRotate->setValue(360 * 8);
  }
  for (auto &iterRotateLineEdits : this->rotateLineEdits_) {
    iterRotateLineEdits->setText(QString::number(0));
  }

  ui_->scrollbar_scale->setValue(1);
  ui_->scale_text->setText(QString::number(1));

  ui_->scrollbar_vertices->setEnabled(true);
  ui_->scrollbar_vertices->setValue(5);

  ui_->scrollbar_edges->setValue(1);
}
void MainWindow::defaultSettings() {
  defaultScrollbars();

  for (int i = 0; ui_->OGLWidget->data.massiv &&
                  i < (ui_->OGLWidget->data.count_of_vertexes + 1) * 3;
       ++i) {
    ui_->OGLWidget->data.massiv[i] = ui_->OGLWidget->data.massiv_const[i];
  }

  ui_->type_of_projection_central_button->setChecked(true);
  ui_->verticies_circle_button->setChecked(true);
  ui_->edges_solid_button->setChecked(true);

  ui_->OGLWidget->initSettings();

  checkSettingsFile();
  updateUiColors();
}
void MainWindow::checkSettingsFile() {
  if (QFile::exists(settingFile_)) {
    QSettings settings(settingFile_, QSettings::IniFormat);

    settings.beginGroup("LineSet");
    if (settings.value("solid").toBool()) {
      ui_->edges_solid_button->setChecked(true);
      ui_->OGLWidget->edgeMode = 0;
    } else if (settings.value("dashed").toBool()) {
      ui_->dashed_solid_button->setChecked(true);
      ui_->OGLWidget->edgeMode = 1;
    }
    if (settings.value("LineColor").toString().length() > 0) {
      ui_->OGLWidget->edgeColor = settings.value("LineColor").toString();
    }
    ui_->scrollbar_edges->setValue(settings.value("value").toInt());
    settings.endGroup();

    settings.beginGroup("VerticeSet");
    if (settings.value("disable").toBool()) {
      ui_->verticies_disable_button->setChecked(true);
      ui_->OGLWidget->pointMode = 0;

    } else if (settings.value("circle").toBool()) {
      ui_->verticies_circle_button->setChecked(true);
      ui_->OGLWidget->pointMode = 1;

    } else if (settings.value("square").toBool()) {
      ui_->verticies_square_button->setChecked(true);
      ui_->OGLWidget->pointMode = 2;
    }
    ui_->OGLWidget->dotColor = settings.value("color").toString();
    ui_->scrollbar_vertices->setValue(settings.value("size").toInt());
    settings.endGroup();

    settings.beginGroup("Background");
    if (settings.value("color").toString().length() > 0) {
      ui_->OGLWidget->backgroundColor = settings.value("color").toString();
    }
    settings.endGroup();
  }
}
void MainWindow::saveSettings() {
  QSettings settings(settingFile_, QSettings::IniFormat);

  settings.beginGroup("LineSet");
  settings.setValue("solid", ui_->edges_solid_button->isChecked());
  settings.setValue("dashed", ui_->dashed_solid_button->isChecked());
  settings.setValue("LineColor", ui_->OGLWidget->edgeColor);
  settings.setValue("value", ui_->scrollbar_edges->value());
  settings.endGroup();

  settings.beginGroup("VerticeSet");
  settings.setValue("disable", ui_->verticies_disable_button->isChecked());
  settings.setValue("circle", ui_->verticies_circle_button->isChecked());
  settings.setValue("square", ui_->verticies_square_button->isChecked());
  settings.setValue("color", ui_->OGLWidget->dotColor);
  settings.setValue("size", ui_->scrollbar_vertices->value());
  settings.endGroup();

  settings.beginGroup("Background");
  settings.setValue("color", ui_->OGLWidget->backgroundColor);
  settings.endGroup();
}

void MainWindow::resetValue() {
  if (QFile::exists(settingFile_)) {
    QFile::remove(settingFile_);
  }
  defaultSettings();
  ui_->OGLWidget->update();
}

void MainWindow::fileHandling() {
  QFileDialog *fileDialog = new QFileDialog(this);
  if (fileDialog) {
    fileDialog->setWindowTitle(tr("Choose .obj-file"));
    fileDialog->setNameFilter(tr("(*.obj)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    QStringList fileNames;
    if (fileDialog->exec()) {
      fileNames = fileDialog->selectedFiles();
      if (fileNames.size() > 0) {
        QString fileName = fileNames.at(0);
        QByteArray ba = fileName.toLocal8Bit();
        char *input = ba.data();
        s21_remove_data(&ui_->OGLWidget->data);
        if (s21_parsing(&ui_->OGLWidget->data, input)) {
          printf("ok\n");
          setWindowTitle(fileName);
          ui_->statusBar->showMessage("Path: " + fileName);
          ui_->number_of_facets->setText(
              QString::number(ui_->OGLWidget->data.count_of_facets));
          ui_->number_of_vertices->setText(
              QString::number(ui_->OGLWidget->data.count_of_vertexes));
          defaultScrollbars();
        } else {
          printf("error\n");
          s21_remove_data(&ui_->OGLWidget->data);
        }
      }
    }
    delete fileDialog;
  } else {
    printf("error!\n");
  }
}

void MainWindow::screenshotMaking() {
  saveSettings();
  QFileDialog dialogPhoto(this);
  QDateTime dateTime = dateTime.currentDateTime();
  QString currentDateTime = dateTime.toString("dd_MM_yy_HH_mm_ss_zzz");
  QString name_photo = dialogPhoto.getSaveFileName(
      this, "Save as...", "Screenshot_" + currentDateTime,
      tr("BMP (*.bmp);; JPEG (*.jpeg)"));
  ui_->OGLWidget->grabFramebuffer().save(name_photo);
}

void MainWindow::gifMaking() {
  ui_->gif_button->setEnabled(false);
  saveSettings();
  timer_->start(100);
}

void MainWindow::slotTimer() {
  if (gifTime_ < 50) {
    gifImage_[gifTime_] = ui_->OGLWidget->grab().toImage();
    ++gifTime_;
  } else {
    gif_ = new QGifImage;

    for (int i = 0; i < gifTime_; ++i) {
      gif_->addFrame(gifImage_[i], 0);
    }
    QDateTime dateTime = dateTime.currentDateTime();
    QString currentDateTime = dateTime.toString("dd_MM_yy_HH_mm_ss_zzz");
    QString fileName = QFileDialog::getSaveFileName(
        this, "Save GIF", "GIF_" + currentDateTime, "GIF (*.gif)");
    gif_->save(fileName);
    ui_->gif_button->setEnabled(true);
    timer_->stop();
    delete gif_;
    gifTime_ = 0;
  }
}
