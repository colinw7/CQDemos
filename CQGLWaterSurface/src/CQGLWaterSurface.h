#include <CQMainWindow.h>
#include <QGLWidget>

class CQMenu;
class CQMenuItem;
class CQGLControl;
class CQGLControlToolBar;
class CQGLWaterSurfaceCanvas;
class CWaterSurface;
class QTimer;

class CQGLWaterSurface : public CQMainWindow {
  Q_OBJECT

 public:
  CQGLWaterSurface();

  CQGLControl *getControl() const { return control_; }

  CWaterSurface *getWaterSurface() const { return surface_; }

  QWidget *createCentralWidget();

  void createWorkspace();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  void initWaterSurface();

 private slots:
  void controlSlot();
  void stepWaterSurface();

 private:
  CQGLWaterSurfaceCanvas *canvas_;
  CQGLControl            *control_;
  CQGLControlToolBar     *toolbar_;
  CWaterSurface          *surface_;
  QTimer                 *timer_;

  CQMenu *fileMenu_;
  CQMenu *helpMenu_;
};

class CQGLWaterSurfaceCanvas : public  QGLWidget {
  Q_OBJECT

 public:
  CQGLWaterSurfaceCanvas(CQGLWaterSurface *surface);

 private:
  void paintGL();

  void resizeGL(int width, int height);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);

 private:
  CQGLWaterSurface *surface_;
};
