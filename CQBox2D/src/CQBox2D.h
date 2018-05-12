#include <Box2D/Box2D.h>
#include <CQMainWindow.h>
#include <QDialog>

class CQBox2D;

class CQBox2DTest : public QMainWindow {
  Q_OBJECT

 public:
  CQBox2DTest();

  QWidget *createCentralWidget();

  void defineWorld();
  void readFile(const char *filename);

 private slots:
  void quit();
  void help();

 private:
  CQBox2D *box_;
};

class QTimer;

class CQBox2D : public QWidget {
  Q_OBJECT

 public:
  CQBox2D(QWidget *parent=NULL);

  void defineWorld();
  void readFile(const char *filename);

  b2Body *createStaticBox    (double x, double y, double hw, double hh, double a);
  b2Body *createStaticCircle (double x, double y, double r);
  b2Body *createStaticPolygon(double x, double y, double angle, const QPolygonF &points);

  b2Body *createDynamicBox    (double x, double y, double hw, double hh, double a,
                               double density, double friction);
  b2Body *createDynamicCircle (double x, double y, double r,
                               double density, double friction);
  b2Body *createDynamicPolygon(double x, double y, double angle, const QPolygonF &points,
                               double density, double friction);

  void draw();

  void mapPoint(double x, double y, int *px, int *py);

  static void rotatePoint(double ix, double iy, double a, double *ox, double *oy);

  QPainter *getIPainter() const { return ipainter_; }

 private:
  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

 private slots:
  void stepSlot();
  void updateSlot();

 private:
  QTimer                *timer1_;
  QTimer                *timer2_;
  int                    w_, h_;
  QImage                 image_;
  b2World               *world_;
  double                 xmin_, ymin_;
  double                 xmax_, ymax_;
  std::vector<b2Body *>  static_bodies_;
  std::vector<b2Body *>  dynamic_bodies_;
  QPainter              *ipainter_;
};
