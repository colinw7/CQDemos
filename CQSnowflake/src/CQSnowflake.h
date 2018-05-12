#include <CQCanvas2D.h>
#include <CImageLib.h>
#include <QMainWindow>
#include <QDialog>

class CQSnowflake;
class CQSnowflakeConfig;

class CQSnowflakeTest : public QMainWindow {
  Q_OBJECT

 public:
  CQSnowflakeTest();

 private slots:
  void config();
  void quit();
  void help();

 private:
  CQSnowflake       *snowflake_;
  CQSnowflakeConfig *dialog_;
};

#include <CSnowflake.h>

class QTimer;
class QSpinBox;

class CQSnowflake : public CQCanvas2D, public CSnowflake {
  Q_OBJECT

 public:
  CQSnowflake(QWidget *parent=NULL);

 private:
  void drawContents(QPainter *);

  void updateSize(int, int);

 public:
  void clear(const CRGBA&);

  void setForeground(const CRGBA&);

  void drawLine(int x1, int y1, int x2, int y2);

  void drawPoint(int x, int y);

  void updateImage();

 private slots:
  void stepSlot();
  void updateSlot();

 private:
  QTimer    *timer1_;
  QTimer    *timer2_;
  CImagePtr  image_;
  QColor     fg_;
};

class CQSnowflakeConfig : public QDialog {
  Q_OBJECT

 public:
  CQSnowflakeConfig(CQSnowflake *snowflake);

 private slots:
  void updateValues();

 private:
  CQSnowflake *snowflake_;
  QSpinBox    *injectMinXVel_;
  QSpinBox    *injectMinYVel_;
  QSpinBox    *injectMaxXVel_;
  QSpinBox    *injectMaxYVel_;
};
