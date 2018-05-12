#include <QMainWindow>
#include <QDialog>

class CQFireworks;
class CQFireworksConfig;

class CQFireworksTest : public QMainWindow {
  Q_OBJECT

 public:
  CQFireworksTest();

 private slots:
  void config();
  void quit();
  void help();

 private:
  CQFireworks       *fireworks_;
  CQFireworksConfig *dialog_;
};

#include <CFireworks.h>

class QTimer;
class QSpinBox;

class CQFireworks : public QWidget, public CFireworks {
  Q_OBJECT

 public:
  CQFireworks(QWidget *parent=NULL);

 private:
  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

  void clear(const CRGBA&);

  void setForeground(const CRGBA&);

  void drawPoint(int x, int y);

  void updateImage();

 private slots:
  void stepSlot();
  void updateSlot();

 private:
  QTimer *timer1_;
  QTimer *timer2_;
  int     w_, h_;
  QImage  image1_;
  QImage  image2_;
  QColor  fg_;
};

class CQFireworksConfig : public QDialog {
  Q_OBJECT

 public:
  CQFireworksConfig(CQFireworks *fireworks);

 private slots:
  void updateValues();

 private:
  CQFireworks *fireworks_;
  QSpinBox    *injectMinXVel_;
  QSpinBox    *injectMinYVel_;
  QSpinBox    *injectMaxXVel_;
  QSpinBox    *injectMaxYVel_;
  QSpinBox    *timeExplode_;
  QSpinBox    *explosionLen_;
};
