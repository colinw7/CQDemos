#include <QWidget>

class QTimer;

class Star {
 public:
  Star(double x=0, double y=0);

  void update(int w, int h);

  void draw(QPainter *p);

  void drawStar(QPainter *p, double x, double y);

  void drawLine(QPainter *p, int x0, int y0, int x1, int y1, uint c);

  void drawPoint(QPainter *p, int x, int y, uint argb);

 private:
  double x_, y_;
  double r_;
  double dc_;
  double c_;
};

class CQStarField : public QWidget {
  Q_OBJECT

 public:
  CQStarField(QWidget *parent=NULL);

 private:
  void paintEvent(QPaintEvent *);

  void resizeEvent(QResizeEvent *);

  void updateImage();

 private slots:
  void updateSlot();

 private:
  typedef std::vector<Star> Stars;

  QTimer *timer_;
  int     w_, h_;
  QImage  image_;
  Stars   stars_;
};
