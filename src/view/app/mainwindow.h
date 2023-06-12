#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <stdlib.h>

#include <QColor>
#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QRadioButton>
#include <QScrollBar>
#include <QSettings>
#include <QTimer>
#include <cstring>

#include "glwidget.h"
#include "qgifimage.h"

extern "C" {
#include "../../model/s21_3DViewer_v1.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:

  void translateScrollbarValueChanged(int value);
  void translateTextEdit();

  void rotateScrollbarValueChanged(int value);
  void rotateTextEdit();

  void scaleScrollbarValueChanged(int value);
  void scaleTextEdit();

  void projectionType();

  void verticeType();
  void verticeSize(int value);

  void edgeType();
  void edgeSizeScrollbarChanged(int value);

  void onChangeColor();

  void resetValue();
  void fileHandling();
  void screenshotMaking();
  void gifMaking();
  void slotTimer();

 private:
  Ui::MainWindow *ui_;
  QString settingFile_;

  int gifTime_ = 0;
  QTimer *timer_;
  QGifImage *gif_;
  QImage *gifImage_;

  QList<QScrollBar *> translateScrollbars_;
  QList<QLineEdit *> translateLineEdits_;

  QList<QScrollBar *> rotateScrollbars_;
  QList<QLineEdit *> rotateLineEdits_;

  void initSetup();

  void translateScrollbarSetup();
  void rotateScrollbarSetup();
  void scaleScrollbarSetup();
  void projectionTypeSetup();
  void verticiesParametersSetup();
  void edgesParametersSetup();
  void colorSetup();
  void updateUiColors();

  void defaultScrollbars();
  void defaultSettings();
  void checkSettingsFile();
  void saveSettings();
};
#endif  // MAINWINDOW_H
