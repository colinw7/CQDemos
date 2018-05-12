#include <QGLWidget>
#include <CQMainWindow.h>

class CQMenu;
class CQMenuItem;
class CQGLControl;
class CQGLControlToolBar;
class CQGLFlockingCanvas;
class CGLTexture;
class CFlocking;
class QTimer;

class CQGLFlocking : public CQMainWindow {
  Q_OBJECT

 public:
  CQGLFlocking();

  CQGLControl *getControl() const { return control_; }

  CFlocking *getFlocking() const { return flocking_; }

  QWidget *createCentralWidget();

  void createWorkspace();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  void initFlocking();

 private slots:
  void controlSlot();
  void updateFlocking();

 private:
  CQGLFlockingCanvas *canvas_;
  CQGLControl        *control_;
  CQGLControlToolBar *toolbar_;
  CFlocking          *flocking_;
  QTimer             *timer_;

  CQMenu *fileMenu_;
  CQMenu *helpMenu_;
};

class CQGLFlockingCanvas : public  QGLWidget {
  Q_OBJECT

 public:
  CQGLFlockingCanvas(CQGLFlocking *flocking);

 private:
  void paintGL();

  void resizeGL(int width, int height);

  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);

 private:
  CQGLFlocking *flocking_;
  CGLTexture   *textures_[4];
};
