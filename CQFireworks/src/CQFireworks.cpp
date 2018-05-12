#include <CQFireworks.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQUtil.h>

#include <QPainter>
#include <QTimer>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSpinBox>

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQFireworksTest fireworks;

  fireworks.setGeometry(10, 10, 400, 400);

  fireworks.show();

  return app.exec();
}

CQFireworksTest::
CQFireworksTest() :
 dialog_(NULL)
{
  setObjectName("test");

  fireworks_ = new CQFireworks;

  setCentralWidget(fireworks_);

  //----

  CQMenu *file_menu = new CQMenu(this, "&File");

  CQMenuItem *config_item = new CQMenuItem(file_menu, "&Config");

  QObject::connect(config_item->getAction(), SIGNAL(triggered()), this, SLOT(config()));

  CQMenuItem *quit_item = new CQMenuItem(file_menu, "&Quit");

  QObject::connect(quit_item->getAction(), SIGNAL(triggered()), this, SLOT(quit()));

  //----

  CQMenu *help_menu = new CQMenu(this, "&Help");

  CQMenuItem *help_item = new CQMenuItem(help_menu, "&Help");

  QObject::connect(help_item->getAction(), SIGNAL(triggered()), this, SLOT(help()));
}

void
CQFireworksTest::
config()
{
  if (! dialog_)
    dialog_ = new CQFireworksConfig(fireworks_);

  dialog_->exec();
}

void
CQFireworksTest::
quit()
{
  exit(0);
}

void
CQFireworksTest::
help()
{
}

//------

CQFireworks::
CQFireworks(QWidget *parent) :
 QWidget(parent)
{
  setObjectName("fireworks");

  timer1_ = new QTimer(this);
  timer2_ = new QTimer(this);

  connect(timer1_, SIGNAL(timeout()), this, SLOT(stepSlot  ()));
  connect(timer2_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer1_->start(25);
  timer2_->start(50);
}

void
CQFireworks::
stepSlot()
{
  step();

  updateImage();
}

void
CQFireworks::
updateSlot()
{
  update();
}

void
CQFireworks::
updateImage()
{
  CFireworks::draw(w_, h_);

  for (int y = 0; y < h_; ++y) {
    for (int x = 0; x < w_; ++x) {
      QRgb pixel1 = image1_.pixel(x, y);
      QRgb pixel2 = image2_.pixel(x, y);

      QRgb pixel3 = qRgb(std::min(int(qRed  (pixel1) * 0.95) + qRed  (pixel2), 255),
                         std::min(int(qGreen(pixel1) * 0.95) + qGreen(pixel2), 255),
                         std::min(int(qBlue (pixel1) * 0.95) + qBlue (pixel2), 255));

      if (pixel3 != pixel1)
        image1_.setPixel(x, y, pixel3);
    }
  }
}

void
CQFireworks::
paintEvent(QPaintEvent *)
{
  QPainter painter(this);

  painter.drawImage(0, 0, image1_);
}

void
CQFireworks::
resizeEvent(QResizeEvent *)
{
  w_ = width ();
  h_ = height();

  image1_ = QImage(QSize(w_, h_), QImage::Format_ARGB32);
  image2_ = QImage(QSize(w_, h_), QImage::Format_ARGB32);

  image1_.fill(QColor(0,0,0).rgba());
}

void
CQFireworks::
clear(const CRGBA &bg)
{
  image2_.fill(CQUtil::rgbaToColor(bg).rgba());
}

void
CQFireworks::
setForeground(const CRGBA &fg)
{
  fg_ = CQUtil::rgbaToColor(fg);
}

void
CQFireworks::
drawPoint(int x, int y)
{
  if (x >= 0 && x < w_ && y >= 0 && y < h_)
    image2_.setPixel(x, y, fg_.rgba());
}

//------------

CQFireworksConfig::
CQFireworksConfig(CQFireworks *fireworks) :
 QDialog(), fireworks_(fireworks)
{
  setObjectName("config");

  QVBoxLayout *layout = new QVBoxLayout(this);

  QGridLayout *grid = new QGridLayout;

  grid->addWidget(new QLabel("Inject Min X Velocity"), 0, 0);
  grid->addWidget(new QLabel("Inject Min Y Velocity"), 1, 0);
  grid->addWidget(new QLabel("Inject Max X Velocity"), 2, 0);
  grid->addWidget(new QLabel("Inject Max Y Velocity"), 3, 0);
  grid->addWidget(new QLabel("Time to Explode"      ), 4, 0);
  grid->addWidget(new QLabel("Explosion Length"     ), 5, 0);

  injectMinXVel_ = new QSpinBox;
  injectMinYVel_ = new QSpinBox;
  injectMaxXVel_ = new QSpinBox;
  injectMaxYVel_ = new QSpinBox;
  timeExplode_   = new QSpinBox;
  explosionLen_  = new QSpinBox;

  injectMinXVel_->setRange(-500, 500);
  injectMinYVel_->setRange(   0, 500);
  injectMaxXVel_->setRange(-500, 500);
  injectMaxYVel_->setRange(   0, 500);
  timeExplode_  ->setRange(   0, 500);
  explosionLen_ ->setRange(   0, 500);

  grid->addWidget(injectMinXVel_, 0, 1);
  grid->addWidget(injectMinYVel_, 1, 1);
  grid->addWidget(injectMaxXVel_, 2, 1);
  grid->addWidget(injectMaxYVel_, 3, 1);
  grid->addWidget(timeExplode_  , 4, 1);
  grid->addWidget(explosionLen_ , 5, 1);

  injectMinXVel_->setValue(fireworks_->getInjectXVelMin ());
  injectMinYVel_->setValue(fireworks_->getInjectYVelMin ());
  injectMaxXVel_->setValue(fireworks_->getInjectXVelMax ());
  injectMaxYVel_->setValue(fireworks_->getInjectYVelMax ());
  timeExplode_  ->setValue(fireworks_->getExplodeTicks  ());
  explosionLen_ ->setValue(fireworks_->getExplosionTicks());

  connect(injectMinXVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMinYVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMaxXVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMaxYVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(timeExplode_  , SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(explosionLen_ , SIGNAL(valueChanged(int)), this, SLOT(updateValues()));

  layout->addLayout(grid);
}

void
CQFireworksConfig::
updateValues()
{
  fireworks_->setInjectXVelMin (injectMinXVel_->value());
  fireworks_->setInjectYVelMin (injectMinYVel_->value());
  fireworks_->setInjectXVelMax (injectMaxXVel_->value());
  fireworks_->setInjectYVelMax (injectMaxYVel_->value());
  fireworks_->setExplodeTicks  (timeExplode_  ->value());
  fireworks_->setExplosionTicks(explosionLen_ ->value());
}
