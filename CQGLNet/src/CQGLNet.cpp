#include <CQGLNet.h>
#include <CXML.h>
#include <CXMLToken.h>
#include <CQMenu.h>
#include <CQGLControl.h>
#include <CGLTexture.h>
#include <GL/glu.h>

#include <QApplication>
#include <QVBoxLayout>

int
main(int argc, char **argv)
{
  QApplication app(argc, argv);

  CQGLNet *net = new CQGLNet;

  if (argc > 1)
    net->loadNet(argv[1]);

  net->init();

  net->resize(400, 400);

  net->show();

  return app.exec();
}

//------

CQGLNet::
CQGLNet() :
 CQMainWindow("CQGLNet")
{
}

void
CQGLNet::
loadNet(const char *filename)
{
  xmin_ = 0.0;
  ymin_ = 0.0;
  xmax_ = 1.0;
  ymax_ = 1.0;

  CXML xml;

  CXMLTag *tag;

  if (! xml.read(filename, &tag))
    return;

  const CXMLTag::OptionArray &options = tag->getOptions();

  CXMLTag::OptionArray::const_iterator p1, p2;

  for (p1 = options.begin(), p2 = options.end(); p1 != p2; ++p1) {
    const CXMLTagOption *opt = *p1;

    const std::string &name  = opt->getName ();
    const std::string &value = opt->getValue();

    if (name == "bbox") {
      std::vector<CPoint2D> points;

      std::vector<std::string> words;

      CStrUtil::addWords(value, words, " ,\n\t");

      uint num_xy = words.size()/2;

      points.resize(num_xy);

      for (uint i = 0, j = 0; j < num_xy; i += 2, ++j) {
        std::string x_word = CStrUtil::stripSpaces(words[i    ]);
        std::string y_word = CStrUtil::stripSpaces(words[i + 1]);

        if (! CStrUtil::toReal(x_word, &points[j].x))
          points[j].x = 0.0;

        if (! CStrUtil::toReal(y_word, &points[j].y))
          points[j].y = 0.0;
      }

      xmin_ = points[0].x;
      ymin_ = points[0].y;
      xmax_ = points[2].x;
      ymax_ = points[2].y;
    }
  }

  CXMLTag::TokenArray children = tag->getChildren();

  for (uint i = 0; i < children.size(); ++i) {
    const CXMLToken *child_token = children[i];

    if      (child_token->isTag()) {
      CXMLTag *child_tag = child_token->getTag();

      const std::string &name = child_tag->getName();

      loadShape(name, child_tag);
    }
    else if (child_token->isText()) {
    }
  }

  dz_ = std::max(xmax_ - xmin_, ymax_ - ymin_)/10.0;
}

void
CQGLNet::
loadShape(const std::string &typeName, CXMLTag *tag)
{
  std::string shapeName = typeName;

  const CXMLTag::OptionArray &options = tag->getOptions();

  CXMLTag::OptionArray::const_iterator p1, p2;

  for (p1 = options.begin(), p2 = options.end(); p1 != p2; ++p1) {
    const CXMLTagOption *opt = *p1;

    const std::string &name  = opt->getName ();
    const std::string &value = opt->getValue();

    if (name == "name")
      shapeName = value;
  }

  std::string layerName = "METAL";

  std::vector<CPoint2D> points;

  CXMLTag::TokenArray children = tag->getChildren();

  for (uint i = 0; i < children.size(); ++i) {
    const CXMLToken *child_token = children[i];

    if      (child_token->isTag()) {
      CXMLTag *child_tag = child_token->getTag();

      const std::string &name = child_tag->getName();

      if      (name == "shape") {
        const CXMLTag::OptionArray &options = child_tag->getOptions();

        CXMLTag::OptionArray::const_iterator p1, p2;

        for (p1 = options.begin(), p2 = options.end(); p1 != p2; ++p1) {
          const CXMLTagOption *opt = *p1;

          const std::string &name  = opt->getName ();
          const std::string &value = opt->getValue();

          if      (name == "layer")
            layerName = value;
          else if (name == "points") {
            std::vector<std::string> words;

            CStrUtil::addWords(value, words, " ,\n\t");

            uint num_xy = words.size()/2;

            points.resize(num_xy);

            for (uint i = 0, j = 0; j < num_xy; i += 2, ++j) {
              std::string x_word = CStrUtil::stripSpaces(words[i    ]);
              std::string y_word = CStrUtil::stripSpaces(words[i + 1]);

              if (! CStrUtil::toReal(x_word, &points[j].x))
                points[j].x = 0.0;

              if (! CStrUtil::toReal(y_word, &points[j].y))
                points[j].y = 0.0;
            }
          }
        }
      }
    }
    else if (child_token->isText()) {
    }
  }

  addShape(typeName, shapeName, layerName, points);
}

void
CQGLNet::
addShape(const std::string &typeName, const std::string &shapeName,
         const std::string &layerName, const std::vector<CPoint2D> &points)
{
  shapes_.push_back(new Shape(this, typeName, shapeName, layerName, points));
}

void
CQGLNet::
drawShapes()
{
  glPushMatrix();

  double xs = 1.0/(xmax_ - xmin_);
  double ys = 1.0/(ymax_ - ymin_);

  double s = std::min(xs, ys);

  glScalef(s, s, s);

  glTranslatef(- (xmin_ + xmax_)/2, - (ymin_ + ymax_)/2, 0.0);

  uint numShapes = shapes_.size();

  for (uint i = 0; i < numShapes; ++i)
    shapes_[i]->draw();

  glPopMatrix();
}

void
CQGLNet::Shape::
draw()
{
  uint numPoints = points_.size();

  double z = 0.0;

  double dz = net_->getDz()/2.0;

  if      (layer_ == "METAL" || layer_ == "METAL1") {
    glColor3d(0.0, 0.0, 1.0); z = 1.0*dz;
  }
  else if (layer_ == "VIA") {
    glColor3d(0.0, 0.0, 1.0); z = 1.5*dz;
  }
  else if (layer_ == "METAL2") {
    glColor3d(1.0, 0.0, 0.0); z = 2.0*dz;
  }
  else if (layer_ == "VIA2") {
    glColor3d(1.0, 0.0, 0.0); z = 2.5*dz;
  }
  else if (layer_ == "METAL3") {
    glColor3d(0.0, 1.0, 0.0); z = 3.0*dz;
  }
  else if (layer_ == "VIA3") {
    glColor3d(0.0, 1.0, 0.0); z = 3.5*dz;
  }
  else if (layer_ == "METAL4") {
    glColor3d(1.0, 1.0, 0.0); z = 4.0*dz;
  }
  else if (layer_ == "VIA4") {
    glColor3d(1.0, 1.0, 0.0); z = 4.5*dz;
  }
  else if (layer_ == "METAL5") {
    glColor3d(0.0, 1.0, 1.0); z = 5.0*dz;
  }
  else if (layer_ == "VIA5") {
    glColor3d(0.0, 1.0, 1.0); z = 5.5*dz;
  }
  else if (layer_ == "METAL6") {
    glColor3d(1.0, 0.0, 1.0); z = 6.0*dz;
  }
  else if (layer_ == "VIA6") {
    glColor3d(1.0, 0.0, 1.0); z = 6.5*dz;
  }
  else {
    glColor3d(1.0, 1.0, 1.0); z = 0.5*dz;
  }

  //z = -z;

  if (type_ == "wire") {
    double dx = points_[2].x - points_[0].x;
    double dy = points_[2].y - points_[0].y;

    GLUquadricObj *quadratic = gluNewQuadric();

    gluQuadricNormals(quadratic, GLU_SMOOTH);
//  gluQuadricTexture(quadratic, GL_TRUE);

    double r, h, rx, ry;

    if (dx > dy) {
      r  = dy/2;
      h  = dx;
      rx = 0;
      ry = 90;
    }
    else {
      r  = dx/2;
      h  = dy;
      rx = -90;
      ry = 0;
    }

    glPushMatrix();

    glTranslatef(points_[0].x, points_[0].y, z);

    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);

    gluCylinder(quadratic, r, r, h, 32, 32);

    gluDeleteQuadric(quadratic);

    glPopMatrix();
  }
  else if (type_ == "contact") {
    drawCube(points_[0].x, points_[0].y, z - 0.5*dz, points_[2].x, points_[2].y, z + 0.5*dz);
  }
  else if (type_ == "cell") {
    drawCube(points_[0].x, points_[0].y, z - 0.5*dz, points_[2].x, points_[2].y, z + 0.5*dz);
  }
  else {
    glBegin(GL_QUADS);

    for (uint i = 0; i < numPoints; ++i)
      glVertex3f(points_[i].x, points_[i].y, z);

    glEnd();
  }
}

void
CQGLNet::Shape::
drawCube(double x1, double y1, double z1, double x2, double y2, double z2)
{
  static GLfloat cube_normal[6][3] = {
    {-1.0,  0.0,  0.0},
    { 0.0,  1.0,  0.0},
    { 1.0,  0.0,  0.0},
    { 0.0, -1.0,  0.0},
    { 0.0,  0.0,  1.0},
    { 0.0,  0.0, -1.0}
  };

  static GLint cube_faces[6][4] = {
    {0, 1, 2, 3},
    {3, 2, 6, 7},
    {7, 6, 5, 4},
    {4, 5, 1, 0},
    {5, 6, 2, 1},
    {7, 4, 0, 3}
  };

  GLfloat v[8][3];

  double x_size = x2 - x1;
  double y_size = y2 - y1;
  double z_size = z2 - z1;

  v[0][0] = v[1][0] = v[2][0] = v[3][0] = -x_size / 2;
  v[4][0] = v[5][0] = v[6][0] = v[7][0] =  x_size / 2;
  v[0][1] = v[1][1] = v[4][1] = v[5][1] = -y_size / 2;
  v[2][1] = v[3][1] = v[6][1] = v[7][1] =  y_size / 2;
  v[0][2] = v[3][2] = v[4][2] = v[7][2] = -z_size / 2;
  v[1][2] = v[2][2] = v[5][2] = v[6][2] =  z_size / 2;

  glPushMatrix();

  glTranslatef((x1 + x2)/2, (y1 + y2)/2, (z1 + z2)/2);

  for (GLint i = 5; i >= 0; i--) {
    glBegin(GL_POLYGON);

    glNormal3fv(&cube_normal[i][0]);

    glVertex3fv(&v[cube_faces[i][0]][0]);
    glVertex3fv(&v[cube_faces[i][1]][0]);
    glVertex3fv(&v[cube_faces[i][2]][0]);
    glVertex3fv(&v[cube_faces[i][3]][0]);

    glEnd();
  }

  glPopMatrix();
}

QWidget *
CQGLNet::
createCentralWidget()
{
  QWidget *frame = new QWidget;

  QVBoxLayout *layout = new QVBoxLayout(frame);

  canvas_  = new CQGLNetCanvas(this);
  control_ = new CQGLControl(canvas_);

  toolbar_ = control_->createToolBar();

  connect(control_, SIGNAL(stateChanged()), this, SLOT(controlSlot()));

  layout->addWidget(toolbar_);
  layout->addWidget(canvas_);

  return frame;
}

void
CQGLNet::
createWorkspace()
{
}

void
CQGLNet::
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
CQGLNet::
createToolBars()
{
}

void
CQGLNet::
createStatusBar()
{
}

void
CQGLNet::
createDockWindows()
{
}

void
CQGLNet::
controlSlot()
{
  canvas_->update();
}

//------

CQGLNetCanvas::
CQGLNetCanvas(CQGLNet *net) :
 QGLWidget(net), net_(net)
{
  setFocusPolicy(Qt::StrongFocus);
}

void
CQGLNetCanvas::
paintGL()
{
  static GLfloat light_position[] = { 50.0, 50.0, 50.0, 0.0 };

  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glEnable(GL_LIGHT0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  CQGLControl *control = net_->getControl();

  control->updateGL();

//glEnable(GL_BLEND);

//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

//glEnable(GL_TEXTURE_2D);

//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  net_->drawShapes();
}

void
CQGLNetCanvas::
resizeGL(int width, int height)
{
  CQGLControl *control = net_->getControl();

  control->handleResize(width, height);
}

void
CQGLNetCanvas::
mousePressEvent(QMouseEvent *e)
{
  CQGLControl *control = net_->getControl();

  control->handleMousePress(e);

  update();
}

void
CQGLNetCanvas::
mouseReleaseEvent(QMouseEvent *e)
{
  CQGLControl *control = net_->getControl();

  control->handleMouseRelease(e);

  update();
}

void
CQGLNetCanvas::
mouseMoveEvent(QMouseEvent *e)
{
  CQGLControl *control = net_->getControl();

  control->handleMouseMotion(e);

  update();
}

void
CQGLNetCanvas::
keyPressEvent(QKeyEvent *)
{
}

//------

CQGLNet::Shape::
Shape(CQGLNet *net, const std::string &typeName, const std::string &shapeName,
      const std::string &layerName, const std::vector<CPoint2D> &points) :
 net_(net), type_(typeName), name_(shapeName), layer_(layerName), points_(points)
{
}
