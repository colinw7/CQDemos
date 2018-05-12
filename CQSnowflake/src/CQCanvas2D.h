#ifndef CQCANVAS2D_H
#define CQCANVAS2D_H

#include <QWidget>
#include <CDisplayRange2D.h>
#include <CEvent.h>

// add zoom/pan interface support

class CQCanvas2D : public QWidget {
  Q_OBJECT

 public:
  CQCanvas2D(QWidget *parent=NULL);

  virtual ~CQCanvas2D();

  void setBackground(QColor bg) { bg_ = bg; }

  void clear();

  void fill(const QColor &bg);

  virtual void drawContents(QPainter * /*painter*/) { }

  virtual void updateSize(int /*w*/, int /*h*/) { }

  virtual void mousePressEvent  (const CMouseEvent &) { }
  virtual void mouseReleaseEvent(const CMouseEvent &) { }
  virtual void mouseMoveEvent   (const CMouseEvent &) { }
  virtual void mouseMotionEvent (const CMouseEvent &) { }

  virtual void keyPressEvent  (const CKeyEvent &) { }
  virtual void keyReleaseEvent(const CKeyEvent &) { }

  QPainter *getPainter() const { return ipainter_; }

  QImage *getImage() const { return image_; }

  void setDisplayRange(double xmin, double ymin, double xmax, double ymax);

  void setChanged();

  void pixelToWindow(double px, double py, double *x, double *y);
  void windowToPixel(double x, double y, double *px, double *py);

  void pixelLengthToWindow(double px, double py, double *x, double *y);
  void windowLengthToPixel(double x, double y, double *px, double *py);

 protected:
  void paintEvent(QPaintEvent *e);
  void resizeEvent(QResizeEvent *e);

  virtual void mousePressEvent(QMouseEvent *);
  virtual void mouseReleaseEvent(QMouseEvent *);
  virtual void mouseDoubleClickEvent(QMouseEvent *);
  virtual void mouseMoveEvent(QMouseEvent *);

  virtual void keyPressEvent(QKeyEvent *);
  virtual void keyReleaseEvent(QKeyEvent *);

 public slots:
  void setChangedSlot();

 private:
  QImage          *image_;
  QPainter        *ipainter_;
  int              w_, h_;
  bool             changed_;
  QColor           bg_;
  CDisplayRange2D  range_;
  bool             rangeSet_;
  bool             pressed_;
};

#endif
