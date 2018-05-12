#include <CQGLFlag.h>
#include <CFlag.h>
#include <CQApp.h>

#include <QTimer>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQGLFlag *flag = new CQGLFlag;

  flag->show();

  return app.exec();
}

//------

CQGLFlag::
CQGLFlag() :
 QMainWindow()
{
  setObjectName("flag");

  flag_ = new CFlag(-4, -4, 8, 8);

  canvas_ = new CQGLFlagCanvas(this);

  setCentralWidget(canvas_);

  timer_ = new QTimer;

  connect(timer_, SIGNAL(timeout()), this, SLOT(stepFlag()));

  timer_->start(20);
}

void
CQGLFlag::
stepFlag()
{
  flag_->step(0.0005);

  canvas_->update();
}

//------

CQGLFlagCanvas::
CQGLFlagCanvas(CQGLFlag *flag) :
 QGLWidget(flag), flag_(flag)
{
  setObjectName("canvas");

  setFocusPolicy(Qt::StrongFocus);
}

void
CQGLFlagCanvas::
paintGL()
{
  //static GLfloat red [4] = {0.8, 0.1, 0.1, 1.0};
  static GLfloat blue[4] = {0.1, 0.8, 0.1, 1.0};

  glClear(GL_COLOR_BUFFER_BIT);

  CFlag *flag = flag_->getFlag();

#if 0
  int num_rows, num_cols;

  flag->getGridDimensions(&num_rows, &num_cols);

  CFlagParticle **particles = flag->getParticles();

  glBegin(GL_POINTS);

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, red);

  for (int r = 0; r < num_rows; ++r) {
    for (int c = 0; c < num_cols; ++c) {
      const CFlagParticle &particle = particles[r][c];

      const CVector3D &pos = particle.getPosition();

      glVertex3d(pos.getX(), pos.getY(), pos.getZ());
    }
  }

  glEnd();
#endif

  CFlagParticleSpring *springs = flag->getSprings();

  int num_springs = flag->getNumSprings();

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, blue);

  for (int s = 0; s < num_springs; ++s) {
    const CFlagParticleSpring &spring = springs[s];

    CFlagParticle *particle1 = spring.getParticle1();
    CFlagParticle *particle2 = spring.getParticle2();

    const CVector3D &pos1 = particle1->getPosition();
    const CVector3D &pos2 = particle2->getPosition();

    glBegin(GL_LINES);

    glVertex3d(pos1.getX(), pos1.getY(), pos1.getZ());
    glVertex3d(pos2.getX(), pos2.getY(), pos2.getZ());

    glEnd();
  }
}

void
CQGLFlagCanvas::
resizeGL(int width, int height)
{
  GLfloat h = (GLfloat) height / (GLfloat) width;

  glViewport(0, 0, (GLint) width, (GLint) height);

  glMatrixMode(GL_PROJECTION);

  glLoadIdentity();

  glFrustum(-1.0, 1.0, -h, h, 5.0, 60.0);

  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();

  glTranslatef(0.0, 0.0, -40.0);
}
