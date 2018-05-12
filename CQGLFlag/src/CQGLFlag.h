#include <QGLWidget>
#include <QMainWindow>

class CFlag;
class QTimer;
class CQGLFlagCanvas;

class CQGLFlag : public QMainWindow {
  Q_OBJECT

 public:
  CQGLFlag();

  CFlag *getFlag() const { return flag_; }

 private slots:
  void stepFlag();

 private:
  CQGLFlagCanvas *canvas_;
  CFlag          *flag_;
  QTimer         *timer_;
};

class CQGLFlagCanvas : public  QGLWidget {
  Q_OBJECT

 public:
  CQGLFlagCanvas(CQGLFlag *flag);

 private:
  void paintGL();
  void resizeGL(int width, int height);

 private:
  CQGLFlag *flag_;
};
