#include <CQSnowflake.h>
#include <CQApp.h>
#include <CQMenu.h>
#include <CQUtil.h>
#include <CQImage.h>

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

  CQSnowflakeTest snowflake;

  snowflake.show();

  return app.exec();
}

CQSnowflakeTest::
CQSnowflakeTest() :
 dialog_(0)
{
  snowflake_ = new CQSnowflake;

  setCentralWidget(snowflake_);

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

  //----

  resize(940, 670);
}

void
CQSnowflakeTest::
config()
{
  if (! dialog_)
    dialog_ = new CQSnowflakeConfig(snowflake_);

  dialog_->exec();
}

void
CQSnowflakeTest::
quit()
{
  exit(0);
}

void
CQSnowflakeTest::
help()
{
}

//------

CQSnowflake::
CQSnowflake(QWidget *parent) :
 CQCanvas2D(parent)
{
  CImageFileSrc src("snowman.png");

  image_ = CImageMgrInst->createImage(src);

  timer1_ = new QTimer(this);
  timer2_ = new QTimer(this);

  connect(timer1_, SIGNAL(timeout()), this, SLOT(stepSlot  ()));
  connect(timer2_, SIGNAL(timeout()), this, SLOT(updateSlot()));

  timer1_->start(25);
  timer2_->start(50);

  CSnowflake::draw(100, 100);
}

void
CQSnowflake::
stepSlot()
{
  step();

  updateImage();
}

void
CQSnowflake::
updateSlot()
{
  update();
}

void
CQSnowflake::
updateImage()
{
  CSnowflake::draw(width(), height());
}

void
CQSnowflake::
drawContents(QPainter *)
{
}

void
CQSnowflake::
updateSize(int, int)
{
}

void
CQSnowflake::
clear(const CRGBA &bg)
{
  QPainter *painter = getPainter();

  if (! painter) return;

  painter->setRenderHint(QPainter::Antialiasing, true);

  fill(CQUtil::rgbaToColor(bg));

  QImage &qimage = image_.cast<CQImage>()->getQImage();

  painter->drawImage(0, 0, qimage);
}

void
CQSnowflake::
setForeground(const CRGBA &fg)
{
  fg_ = CQUtil::rgbaToColor(fg);

  QPainter *painter = getPainter();

  if (painter)
    painter->setPen(fg_);
}

void
CQSnowflake::
drawLine(int x1, int y1, int x2, int y2)
{
  QPainter *painter = getPainter();

  if (painter)
    painter->drawLine(x1, y1, x2, y2);
}

void
CQSnowflake::
drawPoint(int x, int y)
{
  QPainter *painter = getPainter();

  if (painter)
    painter->drawPoint(x, y);
}

//------------

CQSnowflakeConfig::
CQSnowflakeConfig(CQSnowflake *snowflake) :
 QDialog(), snowflake_(snowflake)
{
  QVBoxLayout *layout = new QVBoxLayout(this);

  QGridLayout *grid = new QGridLayout;

  grid->addWidget(new QLabel("Inject Min X Velocity"), 0, 0);
  grid->addWidget(new QLabel("Inject Min Y Velocity"), 1, 0);
  grid->addWidget(new QLabel("Inject Max X Velocity"), 2, 0);
  grid->addWidget(new QLabel("Inject Max Y Velocity"), 3, 0);

  injectMinXVel_ = new QSpinBox;
  injectMinYVel_ = new QSpinBox;
  injectMaxXVel_ = new QSpinBox;
  injectMaxYVel_ = new QSpinBox;

  injectMinXVel_->setRange(-500, 500);
  injectMinYVel_->setRange(   0, 500);
  injectMaxXVel_->setRange(-500, 500);
  injectMaxYVel_->setRange(   0, 500);

  grid->addWidget(injectMinXVel_, 0, 1);
  grid->addWidget(injectMinYVel_, 1, 1);
  grid->addWidget(injectMaxXVel_, 2, 1);
  grid->addWidget(injectMaxYVel_, 3, 1);

  injectMinXVel_->setValue(snowflake_->getInjectXVelMin ());
  injectMinYVel_->setValue(snowflake_->getInjectYVelMin ());
  injectMaxXVel_->setValue(snowflake_->getInjectXVelMax ());
  injectMaxYVel_->setValue(snowflake_->getInjectYVelMax ());

  connect(injectMinXVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMinYVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMaxXVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));
  connect(injectMaxYVel_, SIGNAL(valueChanged(int)), this, SLOT(updateValues()));

  layout->addLayout(grid);
}

void
CQSnowflakeConfig::
updateValues()
{
  snowflake_->setInjectXVelMin (injectMinXVel_->value());
  snowflake_->setInjectYVelMin (injectMinYVel_->value());
  snowflake_->setInjectXVelMax (injectMaxXVel_->value());
  snowflake_->setInjectYVelMax (injectMaxYVel_->value());
}
