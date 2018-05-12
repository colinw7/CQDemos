#include <CQStarField.h>
#include <CQApp.h>
#include <CQUtil.h>

#include <QPainter>
#include <QTimer>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

int randIn(int l, int h) {
  return (rand() % (h - l)) + l;
}

double randIn(double l, double h) {
  return ((1.0*rand())/RAND_MAX)*(h - l) + l;
}

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQStarField *starfield = new CQStarField;

  starfield->setFixedSize(600, 600);

  starfield->show();

  return app.exec();
}

CQStarField::
CQStarField(QWidget *parent) :
 QWidget(parent)
{
  timer_ = new QTimer(this);

  connect(timer_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer_->start(50);

  stars_.resize(100);
}

void
CQStarField::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.drawImage(0, 0, image_);
}

void
CQStarField::
resizeEvent(QResizeEvent *)
{
  w_ = width ();
  h_ = height();

  image_ = QImage(QSize(w_, h_), QImage::Format_ARGB32);

  uint num_stars = stars_.size();

  for (uint i = 0; i < num_stars; ++i)
    stars_[i] = Star(randIn(0, w_ - 1), randIn(0, h_ - 1));
}

void
CQStarField::
updateSlot()
{
  updateImage();

  update();
}

void
CQStarField::
updateImage()
{
  image_.fill(QColor(0,0,0).rgba());

  uint num_stars = stars_.size();

  for (uint i = 0; i < num_stars; ++i)
    stars_[i].update(w_, h_);

  QPainter p(&image_);

  for (uint i = 0; i < num_stars; ++i)
    stars_[i].draw(&p);
}

//----------------

Star::
Star(double x, double y) :
 x_(x), y_(y)
{
  r_  = randIn(3.0, 12.0);
  dc_ = randIn(-1.0, 1.0);
  c_  = randIn(0.0, 255.0);
}

void
Star::
update(int w, int h)
{
  c_ += dc_;

  if (dc_ >= 0) {
    if (c_ >= 255) {
      c_  = 255;
      dc_ = -dc_;
    }
  }
  else {
    if (c_ <= 0) {
      c_  = 0;
      dc_ = -dc_;

      x_ = randIn(0, w - 1);
      y_ = randIn(0, h - 1);
    }
  }
}

void
Star::
draw(QPainter *p)
{
  drawStar(p, x_, y_);
}

void
Star::
drawStar(QPainter *p, double x, double y)
{
  int ic = int(c_);

  uint c = 0xFF000000 | (ic << 16) | (ic << 8) | ic;

  int px = int(x + 0.5);
  int py = int(y + 0.5);

  drawLine(p, int(px -   r_), int(py       ), int(px +   r_), int(py       ), c);
  drawLine(p, int(px       ), int(py -   r_), int(px       ), int(py +   r_), c);
  drawLine(p, int(px - r_/2), int(py - r_/2), int(px + r_/2), int(py + r_/2), c);
  drawLine(p, int(px - r_/2), int(py + r_/2), int(px + r_/2), int(py - r_/2), c);
}

void
Star::
drawLine(QPainter *p, int x0, int y0, int x1, int y1, uint c)
{
  uint ec = c & 0xFFFFFF; // ignore alpha
  uint tc = ec;

  tc = ec + uint(int(0xFF*0.05) << 24);

  int dy = y1 - y0;
  int dx = x1 - x0;

  int stepx;
  int stepy;

  if ( dy < 0 ) { dy = -dy; stepy = -1; } else { stepy = 1; }
  if ( dx < 0 ) { dx = -dx; stepx = -1; } else { stepx = 1; }

  int adx = abs(dx) + 2;
  int ady = abs(dy) + 2;

  dy <<= 1;
  dx <<= 1;

  drawPoint(p, x0, y0, tc);

  if ( dx > dy) {
    int fraction = dy - (dx >> 1);

    while (x0 != x1) {
      double ratio = 1 - fabs(fabs(x0 - x1)/adx - 0.5)*2;

      if (fraction >= 0) {
        y0       += stepy;
        fraction -= dx;
      }

      x0       += stepx;
      fraction += dy;

      tc = ec + uint(int(0xFF*ratio) << 24);

      drawPoint(p, x0, y0, tc);
    }
  }
  else {
    int fraction = dx - (dy >> 1);

    while (y0 != y1) {
      double ratio = 1 - fabs(fabs(y0 - y1)/ady - 0.5)*2;

      if (fraction >= 0) {
        x0       += stepx;
        fraction -= dy;
      }

      y0 += stepy;

      fraction += dx;

      tc = ec + uint(int(0xFF*ratio) << 24);

      drawPoint(p, x0, y0, tc);
    }
  }
}

void
Star::
drawPoint(QPainter *p, int x, int y, uint argb)
{
  int a = (argb & 0xFF000000) >> 24;
  int r = (argb & 0x00FF0000) >> 16;
  int g = (argb & 0x0000FF00) >> 8;
  int b = (argb & 0x000000FF);

  p->setPen(QColor(r, g, b, a));

  p->drawPoint(QPoint(x, y));
}
