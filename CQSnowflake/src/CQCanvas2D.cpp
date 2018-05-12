#include <CQCanvas2D.h>
#include <CQUtil.h>

#include <QPainter>

CQCanvas2D::
CQCanvas2D(QWidget *parent) :
 QWidget(parent), image_(0), ipainter_(0), w_(0), h_(0),
 changed_(true), bg_(255, 255, 255), rangeSet_(false), pressed_(false)
{
  setFocusPolicy(Qt::StrongFocus);
}

CQCanvas2D::
~CQCanvas2D()
{
  delete ipainter_;
  delete image_;
}

void
CQCanvas2D::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  if (changed_) {
    if (rangeSet_)
      ipainter_->setWorldMatrix(CQUtil::toQMatrix(range_.getMatrix()));

    drawContents(ipainter_);

    changed_ = false;
  }

  painter.drawImage(0, 0, *image_);
}

void
CQCanvas2D::
resizeEvent(QResizeEvent *)
{
  delete ipainter_;
  delete image_;

  w_ = std::max(width (), 16);
  h_ = std::max(height(), 16);

  image_ = new QImage(QSize(w_, h_), QImage::Format_ARGB32);

  clear();

  ipainter_ = new QPainter(image_);

  range_.setPixelRange(0, 0, w_ - 1, h_ - 1);

  updateSize(w_, h_);

  changed_ = true;
}

void
CQCanvas2D::
mousePressEvent(QMouseEvent *event)
{
  pressed_ = true;

  mousePressEvent(*CQUtil::convertEvent(event));
}

void
CQCanvas2D::
mouseReleaseEvent(QMouseEvent *event)
{
  mouseReleaseEvent(*CQUtil::convertEvent(event));

  pressed_ = false;
}

void
CQCanvas2D::
mouseDoubleClickEvent(QMouseEvent *event)
{
  CMouseEvent *e = CQUtil::convertEvent(event);

  e->setCount(2);

  mouseReleaseEvent(*e);
}

void
CQCanvas2D::
mouseMoveEvent(QMouseEvent *event)
{
  if (! pressed_)
    mouseMotionEvent(*CQUtil::convertEvent(event));
  else
    mouseMoveEvent(*CQUtil::convertEvent(event));
}

void
CQCanvas2D::
keyPressEvent(QKeyEvent *event)
{
  keyPressEvent(*CQUtil::convertEvent(event));
}

void
CQCanvas2D::
keyReleaseEvent(QKeyEvent *event)
{
  keyReleaseEvent(*CQUtil::convertEvent(event));
}

void
CQCanvas2D::
setDisplayRange(double xmin, double ymin, double xmax, double ymax)
{
  range_.setWindowRange(xmin, ymin, xmax, ymax);

  rangeSet_ = true;
}

void
CQCanvas2D::
setChanged()
{
  changed_ = true;

  update();
}

void
CQCanvas2D::
pixelToWindow(double px, double py, double *x, double *y)
{
  range_.pixelToWindow(px, py, x, y);
}

void
CQCanvas2D::
windowToPixel(double x, double y, double *px, double *py)
{
  range_.windowToPixel(x, y, px, py);
}

void
CQCanvas2D::
pixelLengthToWindow(double px, double py, double *x, double *y)
{
  double x1, y1;

  pixelToWindow(0, 0, &x1, &y1);

  pixelToWindow(px, py, x, y);

  *x -= x1;
  *y -= y1;
}

void
CQCanvas2D::
windowLengthToPixel(double x, double y, double *px, double *py)
{
  double px1, py1;

  windowToPixel(0, 0, &px1, &py1);

  windowToPixel(x, y, px, py);

  *px -= px1;
  *py -= py1;
}

void
CQCanvas2D::
clear()
{
  fill(bg_);
}

void
CQCanvas2D::
fill(const QColor &c)
{
  if (image_)
    image_->fill(c.rgba());
}

void
CQCanvas2D::
setChangedSlot()
{
  setChanged();
}
