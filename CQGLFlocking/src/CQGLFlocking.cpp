#include <CQGLFlocking.h>
#include <CFlocking.h>
#include <CQMenu.h>
#include <CQGLControl.h>
#include <CGLTexture.h>

#include <QApplication>
#include <QTimer>
#include <QVBoxLayout>

#include "images/bird1.xpm"
#include "images/bird2.xpm"
#include "images/bird3.xpm"
#include "images/bird4.xpm"

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQGLFlocking *flocking = new CQGLFlocking;

  flocking->init();

  flocking->resize(400, 400);

  flocking->show();

  return app.exec();
}

//------

CQGLFlocking::
CQGLFlocking() :
 CQMainWindow("CQGLFlocking")
{
  flocking_ = new CFlocking;
}

QWidget *
CQGLFlocking::
createCentralWidget()
{
  QWidget *frame = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout(frame);

  canvas_  = new CQGLFlockingCanvas(this);
  control_ = new CQGLControl(canvas_);

  toolbar_ = control_->createToolBar();

  connect(control_, SIGNAL(stateChanged()), this, SLOT(controlSlot()));

  layout->addWidget(toolbar_);
  layout->addWidget(canvas_);

  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(updateFlocking()));

  timer_->start(10);

  return frame;
}

void
CQGLFlocking::
createWorkspace()
{
}

void
CQGLFlocking::
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
CQGLFlocking::
createToolBars()
{
}

void
CQGLFlocking::
createStatusBar()
{
}

void
CQGLFlocking::
createDockWindows()
{
}

void
CQGLFlocking::
controlSlot()
{
  canvas_->update();
}

void
CQGLFlocking::
updateFlocking()
{
  flocking_->update(0.01);

  canvas_->update();
}

//------

#define IMAGE_DATA(I) I, sizeof(I)/sizeof(char *)

CQGLFlockingCanvas::
CQGLFlockingCanvas(CQGLFlocking *flocking) :
 QGLWidget(flocking), flocking_(flocking)
{
  textures_[0] = NULL;
  textures_[1] = NULL;
  textures_[2] = NULL;
  textures_[3] = NULL;

  setFocusPolicy(Qt::StrongFocus);
}

void
CQGLFlockingCanvas::
paintGL()
{
  static GLfloat light_position[] = { 50.0, 50.0, 50.0, 0.0 };

  static GLfloat colors[][4] = {
    { 1.0, 0.0, 0.0, 1.0 },
    { 0.0, 1.0, 0.0, 1.0 },
    { 0.0, 0.0, 1.0, 1.0 },
    { 1.0, 1.0, 0.0, 1.0 }
  };

  static bool texture = false;

  if (textures_[0] == NULL) {
    textures_[0] = new CGLTexture;
    textures_[1] = new CGLTexture;
    textures_[2] = new CGLTexture;
    textures_[3] = new CGLTexture;

    textures_[0]->setImage(CImageMgrInst->createImage(CImageXPMSrc(IMAGE_DATA(bird1_data))));
    textures_[1]->setImage(CImageMgrInst->createImage(CImageXPMSrc(IMAGE_DATA(bird2_data))));
    textures_[2]->setImage(CImageMgrInst->createImage(CImageXPMSrc(IMAGE_DATA(bird3_data))));
    textures_[3]->setImage(CImageMgrInst->createImage(CImageXPMSrc(IMAGE_DATA(bird4_data))));
  }

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CQGLControl *control = flocking_->getControl();

  control->getDepthTest  () ? glEnable(GL_DEPTH_TEST) : glDisable(GL_DEPTH_TEST);
  control->getCullFace   () ? glEnable(GL_CULL_FACE)  : glDisable(GL_CULL_FACE);
  control->getLighting   () ? glEnable(GL_LIGHTING)   : glDisable(GL_LIGHTING);
  control->getOutline    () ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) :
                              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  control->getFrontFace  () ? glFrontFace(GL_CW) : glFrontFace(GL_CCW);
  control->getSmoothShade() ? glShadeModel(GL_SMOOTH) : glShadeModel(GL_FLAT);

  CFlocking *flocking = flocking_->getFlocking();

  glEnable(GL_BLEND);

  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  if (texture) {
    glEnable(GL_TEXTURE_2D);

    //glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
  }

  const CFlocking::BoidList &boids = flocking->getBoids();

  CFlocking::BoidList::const_iterator pb1, pb2;

  for (pb1 = boids.begin(), pb2 = boids.end(); pb1 != pb2; ++pb1) {
    const CBoid *boid = *pb1;

    const CVector3D &pos = boid->getPos();

    int id = boid->getFlock()->getId() % 4;

    if (texture)
      textures_[id]->bind();

    CVector3D vel = boid->getVelocity().normalized();

    CVector3D vel1(vel.getY(), -vel.getX(), vel.getZ());

    CVector3D pos1 = pos + vel;
    CVector3D pos2 = pos + vel/2 + vel1/2;
    CVector3D pos3 = pos + vel/2 - vel1/2;

    //CVector3D pvel = vel.perp();

    //CVector3D pos2 = pos + pvel/2;
    //CVector3D pos3 = pos - pvel/2;

    //const CRGBA &rgba = boid->getFlock()->getColor();

    if (texture) {
      glBegin(GL_TRIANGLE_STRIP);

      glTexCoord2d(0,0); glVertex3f(pos .getX(), pos .getY(), pos .getZ()); // Bottom Left
      glTexCoord2d(0,1); glVertex3f(pos2.getX(), pos2.getY(), pos2.getZ()); // Top Left
      glTexCoord2d(1,0); glVertex3f(pos3.getX(), pos3.getY(), pos3.getZ()); // Bottom Right
      glTexCoord2d(1,1); glVertex3f(pos1.getX(), pos1.getY(), pos1.getZ()); // Top Right

      //glVertex3d(pos1.getX(), pos1.getY(), pos1.getZ());
      //glVertex3d(pos2.getX(), pos2.getY(), pos2.getZ());
      //glVertex3d(pos3.getX(), pos3.getY(), pos3.getZ());

      glEnd();
    }
    else {
      glBegin(GL_TRIANGLE_STRIP);

      glColor3fv(colors[id]);

      glTexCoord2d(0,0); glVertex3f(pos .getX(), pos .getY(), pos .getZ()); // Bottom Left
      glTexCoord2d(0,1); glVertex3f(pos2.getX(), pos2.getY(), pos2.getZ()); // Top Left
      glTexCoord2d(1,0); glVertex3f(pos3.getX(), pos3.getY(), pos3.getZ()); // Bottom Right
      glTexCoord2d(1,1); glVertex3f(pos1.getX(), pos1.getY(), pos1.getZ()); // Top Right

      glEnd();
    }
  }
}

void
CQGLFlockingCanvas::
resizeGL(int width, int height)
{
  CQGLControl *control = flocking_->getControl();

  control->handleResize(width, height);
}

void
CQGLFlockingCanvas::
mousePressEvent(QMouseEvent *e)
{
  CQGLControl *control = flocking_->getControl();

  control->handleMousePress(e);

  update();
}

void
CQGLFlockingCanvas::
mouseReleaseEvent(QMouseEvent *e)
{
  CQGLControl *control = flocking_->getControl();

  control->handleMouseRelease(e);

  update();
}

void
CQGLFlockingCanvas::
mouseMoveEvent(QMouseEvent *e)
{
  CQGLControl *control = flocking_->getControl();

  control->handleMouseMotion(e);

  update();
}

void
CQGLFlockingCanvas::
keyPressEvent(QKeyEvent *)
{
}
