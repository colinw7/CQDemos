#include <CQBox2D.h>
#include <CArgs.h>
#include <CQApp.h>
#include <CQUtil.h>
#include <CQMenu.h>

#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QHBoxLayout>
#include <QVBoxLayout>

//--------------

enum ShapeType {
  NO_SHAPE,
  BOX_SHAPE,
  CIRCLE_SHAPE,
  POLYGON_SHAPE
};

class Shape {
 public:
  Shape(ShapeType type, bool dynamic) :
   type_(type), dynamic_(dynamic) {
  }

  virtual ~Shape() { }

  virtual void draw(CQBox2D *box, double x, double y, double a) = 0;

  QColor getColor() {
    if (dynamic_) return QColor(255,   0, 0);
    else          return QColor(  0, 255, 0);
  }

 protected:
  ShapeType type_;
  bool      dynamic_;
};

class BoxShape : public Shape {
 public:
  BoxShape(double w, double h, bool dynamic=false) :
   Shape(BOX_SHAPE, dynamic), w_(w), h_(h) {
  }

  void draw(CQBox2D *box, double x, double y, double a);

 private:
  double w_, h_;
};

class CircleShape : public Shape {
 public:
  CircleShape(double x, double y, double r, bool dynamic=false) :
   Shape(CIRCLE_SHAPE, dynamic), x_(x), y_(y), r_(r) {
  }

  void draw(CQBox2D *box, double x, double y, double a);

 private:
  double x_, y_, r_;
};

class PolygonShape : public Shape {
 public:
  PolygonShape(const QPolygonF polygon, bool dynamic=false) :
   Shape(POLYGON_SHAPE, dynamic), polygon_(polygon) {
  }

  void draw(CQBox2D *box, double x, double y, double a);

 private:
  QPolygonF polygon_;
};

//--------------

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQBox2DTest box;

  if (argc > 1)
    box.readFile(argv[1]);
  else
    box.defineWorld();

  box.show();

  return app.exec();
}

//--------------

CQBox2DTest::
CQBox2DTest()
{
  box_ = new CQBox2D;

  QWidget *frame = new QWidget;

  QHBoxLayout *layout = new QHBoxLayout(frame);

  layout->addWidget(box_);

  QWidget *control = new QWidget;

  QVBoxLayout *clayout = new QVBoxLayout;

  clayout->addWidget(control);

  layout->addLayout(clayout);

  setCentralWidget(frame);

  //----

  CQMenu *file_menu = new CQMenu(this, "&File");

  CQMenuItem *quit_item = new CQMenuItem(file_menu, "&Quit");

  QObject::connect(quit_item->getAction(), SIGNAL(triggered()), this, SLOT(quit()));

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

void
CQBox2DTest::
readFile(const char *filename)
{
  box_->readFile(filename);
}

void
CQBox2DTest::
defineWorld()
{
  box_->defineWorld();
}

void
CQBox2DTest::
quit()
{
  exit(0);
}

void
CQBox2DTest::
help()
{
}

//------

CQBox2D::
CQBox2D(QWidget *parent) :
 QWidget(parent)
{
  timer1_ = new QTimer(this);
  timer2_ = new QTimer(this);

  connect(timer1_, SIGNAL(timeout()), this, SLOT(stepSlot  ()));
  connect(timer2_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer1_->start(1000 / 60.0);
  timer2_->start(1000 / 20.0);

  ipainter_ = NULL;

  setFixedSize(500, 500);
}

void
CQBox2D::
readFile(const char *filename)
{
  xmin_ = -10.0, ymin_ = -1.0;
  xmax_ =  10.0, ymax_ = 19.0;

  // Define world, gravity
  b2Vec2 gravity(0.0f, -10.0f);
  //bool doSleep = true;

  //world_ = new b2World(gravity, doSleep);
  world_ = new b2World(gravity);

  //world_->SetAllowSleeping(doSleep);

  //------

  CFile file(filename);

  std::string line;

  while (file.readLine(line)) {
    std::vector<std::string> words;

    CStrUtil::addWords(line, words);

    uint num_words = words.size();

    if (num_words == 0) continue;

    if      (words[0] == "set_range") {
      static const char *opts = "-xmin:r=0 -ymin:r=0 -xmax:r=10 -ymax:r=10";

      CArgs args(opts);

      args.parse(words);

      xmin_ = args.getRealArg("-xmin");
      ymin_ = args.getRealArg("-ymin");
      xmax_ = args.getRealArg("-xmax");
      ymax_ = args.getRealArg("-ymax");
    }
    else if (words[0] == "create_rect") {
      static const char *opts = "-x:r=0 -y:r=0 -w:r=10 -h:r=10 -rx:r=0 -ry:r=0 -a:r=0 -name:s";

      CArgs args(opts);

      args.parse(words);

      double x  = args.getRealArg("-x");
      double y  = args.getRealArg("-y");
      double w  = args.getRealArg("-w");
      double h  = args.getRealArg("-h");
      double a  = M_PI*args.getRealArg("-a")/180.0;

      std::string name = args.getStringArg("-name");

      bool dynamic = (name.length() >= 7 && name.substr(0, 7) == "dynamic");

      if (dynamic)
        createDynamicBox(x, y, w, h, a, 1.0, 0.5);
      else
        createStaticBox (x, y, w, h, a);
    }
    else if (words[0] == "create_ellipse") {
      static const char *opts = "-x:r=0 -y:r=0 -xr:r=10 -yr:r=10 -a:r=0 -name:s";

      CArgs args(opts);

      args.parse(words);

      double x = args.getRealArg("-x");
      double y = args.getRealArg("-y");
      double r = args.getRealArg("-xr");

      std::string name = args.getStringArg("-name");

      bool dynamic = (name.length() >= 7 && name.substr(0, 7) == "dynamic");

      if (dynamic)
        createDynamicCircle(x, y, r, 10.0, 0.5);
      else
        createStaticCircle(x, y, r);
    }
  }
}

void
CQBox2D::
defineWorld()
{
  xmin_ = -100.0, ymin_ = -10.0;
  xmax_ =  100.0, ymax_ = 190.0;

  // Define world, gravity
  b2Vec2 gravity(0.0f, -10.0f);
  //bool doSleep = true;

  //world_ = new b2World(gravity, doSleep);
  world_ = new b2World(gravity);

  //world_->SetAllowSleeping(doSleep);

  createStaticBox(-100, -20, 200, 20, 0);

  createStaticBox(-80, 80, 100, 4, -M_PI/6);
  createStaticBox(-20, 40, 100, 4,  M_PI/6);

  QPolygonF poly;
  poly << QPointF(0, 10) << QPointF(-5, 0) << QPointF(5, 0);
  createDynamicPolygon(10, 100, 0, poly, 1.0, 0.5);

  createDynamicCircle(0, 100, 2, 1.0, 0.5);
}

//------

b2Body *
CQBox2D::
createStaticBox(double x, double y, double w, double h, double a)
{
  b2BodyDef bodyDef;

  bodyDef.angle    = a;
  bodyDef.userData = new BoxShape(w, h);

  bodyDef.position.Set(x + w/2, y + h/2);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2PolygonShape polygonShape;

  polygonShape.SetAsBox(w/2, h/2);

  body->CreateFixture(&polygonShape, 0.0);

  static_bodies_.push_back(body);

  return body;
}

b2Body *
CQBox2D::
createStaticCircle(double x, double y, double r)
{
  b2BodyDef bodyDef;

  bodyDef.userData = new CircleShape(0, 0, r);

  bodyDef.position.Set(x, y);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2CircleShape circleShape;

  circleShape.m_radius = r;

  body->CreateFixture(&circleShape, 0.0);

  static_bodies_.push_back(body);

  return body;
}

b2Body *
CQBox2D::
createStaticPolygon(double x, double y, double angle, const QPolygonF &points)
{
  b2BodyDef bodyDef;

  bodyDef.angle    = angle*M_PI/180.0;
  bodyDef.userData = new PolygonShape(points);

  bodyDef.position.Set(x, y);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2PolygonShape polygonShape;

  int n = points.size();

  b2Vec2 *vertices = new b2Vec2 [n];

  for (int i = 0; i < n; ++i) {
    const QPointF &p = points[i];

    vertices[i].Set(p.x(), p.y());
  }

  polygonShape.Set(vertices, n);

  delete [] vertices;

  body->CreateFixture(&polygonShape, 0.0);

  dynamic_bodies_.push_back(body);

  return body;
}

//------

b2Body *
CQBox2D::
createDynamicBox(double x, double y, double w, double h, double a,
                 double density, double friction)
{
  b2BodyDef bodyDef;

  bodyDef.type     = b2_dynamicBody;
  bodyDef.angle    = a;
  bodyDef.userData = new BoxShape(w, h, true);

  bodyDef.position.Set(x + w/2, y + h/2);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2PolygonShape polygonShape;

  polygonShape.SetAsBox(w/2, h/2);

  b2FixtureDef fixtureDef;

  fixtureDef.shape    = &polygonShape;
  fixtureDef.density  = density;
  fixtureDef.friction = friction;

  body->CreateFixture(&fixtureDef);

  static_bodies_.push_back(body);

  return body;
}

b2Body *
CQBox2D::
createDynamicCircle(double x, double y, double r,
                    double density, double friction)
{
  b2BodyDef bodyDef;

  bodyDef.type     = b2_dynamicBody;
  bodyDef.userData = new CircleShape(0, 0, r, true);

  bodyDef.position.Set(x, y);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2CircleShape circleShape;

  circleShape.m_radius = r;

  b2FixtureDef fixtureDef;

  fixtureDef.shape    = &circleShape;
  fixtureDef.density  = density;
  fixtureDef.friction = friction;

  body->CreateFixture(&fixtureDef);

  static_bodies_.push_back(body);

  return body;
}

b2Body *
CQBox2D::
createDynamicPolygon(double x, double y, double angle, const QPolygonF &points,
                     double density, double friction)
{
  b2BodyDef bodyDef;

  bodyDef.type     = b2_dynamicBody;
  bodyDef.angle    = angle*M_PI/180.0;
  bodyDef.userData = new PolygonShape(points, true);

  bodyDef.position.Set(x, y);

  b2Body *body = world_->CreateBody(&bodyDef);

  b2PolygonShape polygonShape;

  int n = points.size();

  b2Vec2 *vertices = new b2Vec2 [n];

  for (int i = 0; i < n; ++i) {
    const QPointF &p = points[i];

    vertices[i].Set(p.x(), p.y());
  }

  polygonShape.Set(vertices, n);

  delete [] vertices;

  b2FixtureDef fixtureDef;

  fixtureDef.shape    = &polygonShape;
  fixtureDef.density  = density;
  fixtureDef.friction = friction;

  body->CreateFixture(&fixtureDef);

  dynamic_bodies_.push_back(body);

  return body;
}

void
CQBox2D::
stepSlot()
{
  double timeStep = 1.0/60.0;

  world_->Step(timeStep, 8, 3);
}

void
CQBox2D::
updateSlot()
{
  draw();

  update();
}

void
CQBox2D::
draw()
{
  image_.fill(0);

  uint ns = static_bodies_.size();

  for (uint i = 0; i < ns; ++i) {
    b2Body *body = static_bodies_[i];

    Shape *shape = (Shape *) body->GetUserData();

    b2Vec2  position = body->GetPosition();
    float32 angle    = body->GetAngle();

    shape->draw(this, position.x, position.y, angle);
  }

  uint nd = dynamic_bodies_.size();

  for (uint i = 0; i < nd; ++i) {
    b2Body *body = dynamic_bodies_[i];

    Shape *shape = (Shape *) body->GetUserData();

    b2Vec2  position = body->GetPosition();
    float32 angle    = body->GetAngle();

    shape->draw(this, position.x, position.y, angle);
  }
}

void
CQBox2D::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.drawImage(0, 0, image_);
}

void
CQBox2D::
resizeEvent(QResizeEvent *)
{
  w_ = width ();
  h_ = height();

  delete ipainter_;

  image_ = QImage(w_, h_, QImage::Format_ARGB32);

  ipainter_ = new QPainter(&image_);
}

void
CQBox2D::
mapPoint(double x, double y, int *px, int *py)
{
  *px = (x - xmin_)/(xmax_ - xmin_)*(w_ - 1);
  *py = (y - ymin_)/(ymax_ - ymin_)*(h_ - 1);
  *py = (h_ - 1 - *py);
}

void
CQBox2D::
rotatePoint(double ix, double iy, double a, double *ox, double *oy)
{
  double s = sin(a);
  double c = cos(a);

  double x1 = ix*c - iy*s;
  double y1 = ix*s + iy*c;

  *ox = x1;
  *oy = y1;
}

//------

void
BoxShape::
draw(CQBox2D *box, double x, double y, double a)
{
  double x1, y1, x2, y2, x3, y3, x4, y4;

  CQBox2D::rotatePoint(-w_/2, -h_/2, a, &x1, &y1);
  CQBox2D::rotatePoint( w_/2, -h_/2, a, &x2, &y2);
  CQBox2D::rotatePoint( w_/2,  h_/2, a, &x3, &y3);
  CQBox2D::rotatePoint(-w_/2,  h_/2, a, &x4, &y4);

  int px1, py1, px2, py2, px3, py3, px4, py4;

  box->mapPoint(x1 + x, y1 + y, &px1, &py1);
  box->mapPoint(x2 + x, y2 + y, &px2, &py2);
  box->mapPoint(x3 + x, y3 + y, &px3, &py3);
  box->mapPoint(x4 + x, y4 + y, &px4, &py4);

  QPainterPath path;

  path.moveTo(QPoint(px1, py1));
  path.lineTo(QPoint(px2, py2));
  path.lineTo(QPoint(px3, py3));
  path.lineTo(QPoint(px4, py4));

  box->getIPainter()->fillPath(path, QBrush(getColor()));
}

void
CircleShape::
draw(CQBox2D *box, double x, double y, double /*a*/)
{
  int px1, py1, px2, py2;

  box->mapPoint(x_ - r_ + x, y_ - r_ + y, &px1, &py1);
  box->mapPoint(x_ + r_ + x, y_ + r_ + y, &px2, &py2);

  QPainterPath path;

  path.addEllipse(QRect(px1, py1, px2 - px1, py2 - py1));

  box->getIPainter()->fillPath(path, QBrush(getColor()));
}

void
PolygonShape::
draw(CQBox2D *box, double x, double y, double a)
{
  QPainterPath path;

  int n = polygon_.size();

  for (int i = 0; i < n; ++i) {
    const QPointF &p = polygon_[i];

    double x1, y1;

    CQBox2D::rotatePoint(p.x(), p.y(), a, &x1, &y1);

    int px, py;

    box->mapPoint(x1 + x, y1 + y, &px, &py);

    if (i == 0)
      path.moveTo(QPoint(px, py));
    else
      path.lineTo(QPoint(px, py));
  }

  path.closeSubpath();

  box->getIPainter()->fillPath(path, QBrush(getColor()));
}
