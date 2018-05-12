#include <CQGLWaterSurface.h>
#include <CWaterSurface.h>
#include <CQMenu.h>
#include <CQGLControl.h>

#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQGLWaterSurface *surface = new CQGLWaterSurface;

  surface->init();

  surface->show();

  return app.exec();
}

//------

CQGLWaterSurface::
CQGLWaterSurface() :
 CQMainWindow("CQGLWaterSurface")
{
  surface_ = new CWaterSurface;

  initWaterSurface();
}

QWidget *
CQGLWaterSurface::
createCentralWidget()
{
  QWidget *frame = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout(frame);

  canvas_  = new CQGLWaterSurfaceCanvas(this);
  control_ = new CQGLControl(canvas_);

  toolbar_ = control_->createToolBar();

  connect(control_, SIGNAL(stateChanged()), this, SLOT(controlSlot()));

  layout->addWidget(toolbar_);
  layout->addWidget(canvas_);

  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(stepWaterSurface()));

  timer_->start(10);

  return frame;
}

void
CQGLWaterSurface::
createWorkspace()
{
}

void
CQGLWaterSurface::
createMenus()
{
  fileMenu_ = new CQMenu(this, "&File");

  CQMenuItem *quitItem = new CQMenuItem(fileMenu_, "&Quit");

  quitItem->setShortcut("Ctrl+Q");
  quitItem->setStatusTip("Quit the application");

  connect(quitItem->getAction(), SIGNAL(triggered()), this, SLOT(close()));

  //----

  helpMenu_ = new CQMenu(this, "&Help");

  //----

  CQMenuItem *aboutItem = new CQMenuItem(helpMenu_, "&About");

  aboutItem->setStatusTip("Show the application's About box");

  //connect(aboutItem->getAction(), SIGNAL(triggered()), this, SLOT(aboutSlot()));
}

void
CQGLWaterSurface::
createToolBars()
{
}

void
CQGLWaterSurface::
createStatusBar()
{
}

void
CQGLWaterSurface::
createDockWindows()
{
}

void
CQGLWaterSurface::
controlSlot()
{
  canvas_->update();
}

void
CQGLWaterSurface::
initWaterSurface()
{
  int n = surface_->getSize();

  for (int y = 1; y < n - 1; y++) {
    for (int x = 1; x < n - 1; x++) {
      //double xx = surface_->getX(x, y);
      //double yy = surface_->getY(x, y);

      //if ((xx*xx + yy*yy) <= 10) surface_->setDampening(x, y, 0);

      surface_->setDampening(x, y, 1.0);

      surface_->setZ(x, y, 0.0);
    }
  }

  surface_->setZ((int) (    n/4.0), (int) (    n/4.0), 4.0);
  surface_->setZ((int) (3.0*n/4.0), (int) (3.0*n/4.0), 4.0);
}

void
CQGLWaterSurface::
stepWaterSurface()
{
  surface_->step(0.001);

  canvas_->update();
}

//------

CQGLWaterSurfaceCanvas::
CQGLWaterSurfaceCanvas(CQGLWaterSurface *surface) :
 QGLWidget(surface), surface_(surface)
{
  setFocusPolicy(Qt::StrongFocus);
}

void
CQGLWaterSurfaceCanvas::
paintGL()
{
  static GLfloat blue[4] = {0.2, 0.2, 0.5, 1.0};

  //static GLfloat mat_specular  [] = { 1.0, 1.0, 1.0, 1.0 };
  //static GLfloat mat_shininess [] = { 50.0 };
  static GLfloat light_position[] = { 5.0, 5.0, -5.0, 0.0 };

  //glEnable(GL_COLOR_MATERIAL);
  glDisable(GL_COLOR_MATERIAL);

  //glColor3d(blue[0], blue[1], blue[2]);

  //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CQGLControl *control = surface_->getControl();

  control->getDepthTest  () ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
  control->getCullFace   () ? glEnable(GL_CULL_FACE)  : glDisable(GL_CULL_FACE);
  control->getLighting   () ? glEnable(GL_LIGHTING)   : glDisable(GL_LIGHTING);
  control->getOutline    () ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
                              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  control->getFrontFace  () ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
  control->getSmoothShade() ? glShadeModel(GL_SMOOTH) : glShadeModel(GL_FLAT);

  glEnable(GL_LIGHT0);

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  static GLfloat ambient[4] = {0.1, 0.1, 0.1, 1.0};

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, blue);
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR , mat_specular );
  //glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);

  CWaterSurface *surface = surface_->getWaterSurface();

  int n = surface->getSize();

  for (int y = 1; y < n; ++y) {
    double y1 = surface->getY(0, y - 1);
    double y2 = surface->getY(0, y    );

    for (int x = 1; x < n; ++x) {
      double x1 = surface->getX(x - 1, 0);
      double x2 = surface->getX(x    , 0);

      double z1 = surface->getZ(x - 1, y - 1);
      double z2 = surface->getZ(x - 1, y    );
      double z3 = surface->getZ(x    , y    );
      double z4 = surface->getZ(x    , y - 1);

      //CVector3D n1 = surface->getNormal(x - 1, y - 1).normalized();
      //CVector3D n2 = surface->getNormal(x - 1, y    ).normalized();
      //CVector3D n3 = surface->getNormal(x    , y    ).normalized();
      //CVector3D n4 = surface->getNormal(x    , y - 1).normalized();

      //CVector3D n = (n1 + n2 + n3 + n4)/4;

      //n.normalize();

      double z;

      CVector3D normal;

      surface->interpolate(x - 0.5, y - 0.5, z, normal);

      glColor3d(blue[0], blue[1], blue[2]);

      glBegin(GL_POLYGON);

      glNormal3f(normal.getX(), normal.getY(), normal.getZ());

      //glNormal3f(n1.getX(), n1.getY(), n1.getZ());
      glVertex3d(x1, y1, z1);

      //glNormal3f(n2.getX(), n2.getY(), n2.getZ());
      glVertex3d(x1, y2, z2);

      //glNormal3f(n3.getX(), n3.getY(), n3.getZ());
      glVertex3d(x2, y2, z3);

      //glNormal3f(n4.getX(), n4.getY(), n4.getZ());
      glVertex3d(x2, y1, z4);

      glEnd();
    }
  }
}

void
CQGLWaterSurfaceCanvas::
resizeGL(int width, int height)
{
  CQGLControl *control = surface_->getControl();

  control->handleResize(width, height);
}

void
CQGLWaterSurfaceCanvas::
mousePressEvent(QMouseEvent *e)
{
  CQGLControl *control = surface_->getControl();

  control->handleMousePress(e);

  update();
}

void
CQGLWaterSurfaceCanvas::
mouseReleaseEvent(QMouseEvent *e)
{
  CQGLControl *control = surface_->getControl();

  control->handleMouseRelease(e);

  update();
}

void
CQGLWaterSurfaceCanvas::
mouseMoveEvent(QMouseEvent *e)
{
  CQGLControl *control = surface_->getControl();

  control->handleMouseMotion(e);

  update();
}

void
CQGLWaterSurfaceCanvas::
keyPressEvent(QKeyEvent *)
{
}
