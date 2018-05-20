#include <CQCountdown.h>

#include <CQApp.h>
#include <CEval.h>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsProxyWidget>
#include <QStatusBar>
#include <QLabel>
#include <QPushButton>
#include <QKeyEvent>

#include <cmath>
#include <set>
#include <map>

#define FONT_NAME1 "Helvetica"
#define FONT_NAME2 "Courier New"

namespace {
  double RandIn(int min_val, int max_val) {
    int number = (rand() % (max_val - min_val + 1)) + min_val;

    return std::min(std::max(number, min_val), max_val);
  }
};

static int numbers[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                         1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                         25, 50, 75, 100 };

class AnswerItem : public QGraphicsTextItem {
 public:
  AnswerItem(CQCountdown *countdown, const QPointF &pos);

  CQCountdown *getCountDown() const { return countdown_; }

  int getAnswer() { return answer_; }

 private:
  CQCountdown *countdown_;
  int          answer_;
};

class GuessItem : public QGraphicsTextItem {
 public:
  GuessItem(CQCountdown *countdown, const QPointF &pos);

  CQCountdown *getCountDown() const { return countdown_; }

  void setGuess(int guess);

 private:
  CQCountdown *countdown_;
  int          guess_;
};

class NumberItem : public QGraphicsTextItem {
 public:
  NumberItem(NumbersItem *numbers, const QString &str);

  bool getUsed() const { return used_; }

  void setUsed(bool used);

  void mousePressEvent  (QGraphicsSceneMouseEvent *);
  void mouseMoveEvent   (QGraphicsSceneMouseEvent *);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

 private:
  NumbersItem       *numbersItem_;
  QGraphicsTextItem *newItem_;
  QPointF            delta_;
  bool               used_;
};

class NumbersItem {
 public:
  enum { NUM_ITEMS = 6 };

 public:
  NumbersItem(CQCountdown *countdown, const QPointF &pos);

  CQCountdown *getCountDown() const { return countdown_; }

  NumberItem *getItem(uint i) const { return items_[i]; }

  void revert(const QString &str);

 private:
  CQCountdown *  countdown_;
  std::set<uint> used_;
  NumberItem *   items_[NUM_ITEMS];
};

class WorkAreaItem;

class WorkItem : public QGraphicsTextItem {
 public:
  WorkItem(WorkAreaItem *workArea, const QString &str, bool isNumber);

  bool isNumber() const { return isNumber_; }
  bool isHidden() const { return isHidden_; }
  bool isDummy () const { return isDummy_ ; }

  void setIsHidden(bool isHidden);
  void setIsDummy (bool isDummy);

  void mousePressEvent  (QGraphicsSceneMouseEvent *);
  void mouseMoveEvent   (QGraphicsSceneMouseEvent *);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

 private:
  WorkAreaItem      *workArea_;
  bool               isNumber_;
  bool               isHidden_;
  bool               isDummy_;
  QGraphicsTextItem *newItem_;
  QPointF            delta_;
};

class WorkAreaItem : public QGraphicsRectItem {
 public:
  typedef std::list<WorkItem *> WorkItemList;

 public:
  WorkAreaItem(CQCountdown *countdown, const QPointF &pos);

  CQCountdown *getCountDown() const { return countdown_; }

  void addNumberItem(const QString &item, const QPointF &pos, bool isDummy=false);
  void addOpItem    (const QString &item, const QPointF &pos, bool isDummy=false);

  void moveItem(const QString &str, const QPointF &pos);
  void removeItem(const QString &str);
  void removeDummyItems();

  void layout();

  void setActive(bool active);

 private:
  CQCountdown  *countdown_;
  WorkItemList  items_;
  bool          active_;
};

class OpsItem;

class OpItem : public QGraphicsTextItem {
 public:
  OpItem(OpsItem *ops, const QString &str);

  void mousePressEvent  (QGraphicsSceneMouseEvent *);
  void mouseMoveEvent   (QGraphicsSceneMouseEvent *);
  void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

 private:
  OpsItem           *opsItem_;
  QGraphicsTextItem *newItem_;
  QPointF            delta_;
};

class OpsItem {
 public:
  enum { NUM_OPS = 6 };

 public:
  OpsItem(CQCountdown *countdown, const QPointF &pos);

  QGraphicsTextItem *getItem(uint i) const { return items_[i]; }

  CQCountdown *getCountDown() const { return countdown_; }

 private:
  CQCountdown       *countdown_;
  QGraphicsTextItem *items_[NUM_OPS];
};

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  srand(time(0));

  CQCountdown *window = new CQCountdown;

  window->show();

  app.exec();
}

CQCountdown::
CQCountdown() :
 QMainWindow(), w_(600), h_(600)
{
  QPointF pos(0, 0);

  scene_ = new QGraphicsScene;

  answer_ = new AnswerItem(this, pos);

  pos.ry() += answer_->boundingRect().height();

  addItem(answer_);

  numbers_ = new NumbersItem(this, pos);

  for (uint i = 0; i < NumbersItem::NUM_ITEMS; ++i)
    addItem(numbers_->getItem(i));

  pos.ry() += 80;

  OpsItem *ops = new OpsItem(this, pos);

  for (uint i = 0; i < OpsItem::NUM_OPS; ++i)
    addItem(ops->getItem(i));

  pos.ry() = h_ - 300;

  workArea_ = new WorkAreaItem(this, pos);

  addItem(workArea_);

  pos.ry() += 100;

  guess_ = new GuessItem(this, pos);

  addItem(guess_);

  pos.ry() += 100;

  //------

  QPushButton *newGameButton = new QPushButton("New Game");

  QGraphicsProxyWidget *newGameProxy = new QGraphicsProxyWidget;

  newGameProxy->setWidget(newGameButton);

  addItem(newGameProxy);

  newGameProxy->setPos(pos);

  //------

  view_ = new QGraphicsView(scene_);

  view_->setSceneRect(0, 0, getWidth(), getHeight());

  setCentralWidget(view_);

  //------

  posLabel_ = new QLabel;

  //statusBar()->addPermanentWidget(posLabel_);
}

void
CQCountdown::
addItem(QGraphicsItem *item)
{
  scene_->addItem(item);
}

void
CQCountdown::
setPosLabel(const QPointF &pos)
{
  posLabel_->setText(QString("%1,%2").arg(pos.x()).arg(pos.y()));
}

//------

AnswerItem::
AnswerItem(CQCountdown *countdown, const QPointF &pos) :
 QGraphicsTextItem(""), countdown_(countdown)
{
  QFont font(FONT_NAME1, 80);

  setFont(font);

  answer_ = RandIn(100, 999);

  setPlainText(QString("%1").arg(answer_));

  int dx = (countdown->getWidth() - boundingRect().width())/2;

  setPos(QPointF(dx, pos.y()));
}

//------

GuessItem::
GuessItem(CQCountdown *countdown, const QPointF &pos) :
 QGraphicsTextItem(""), countdown_(countdown), guess_(0)
{
  QFont font(FONT_NAME1, 30);

  setFont(font);

  setPos(pos);

  setGuess(guess_);
}

void
GuessItem::
setGuess(int guess)
{
  guess_ = guess;

  int answer = countdown_->getAnswer()->getAnswer();

  if      (guess_ < answer)
    setHtml(QString("%1 <font color=\"red\">(%2)</font>").arg(guess_).arg(guess_ - answer));
  else if (guess_ > answer)
    setHtml(QString("%1 <font color=\"green\">(%2)</font>").arg(guess_).arg(guess_ - answer));
  else
    setHtml(QString("%1 (Correct)").arg(guess_));

  int dx = (countdown_->getWidth() - boundingRect().width())/2;

  setPos(QPointF(dx, pos().y()));
}

//------

NumbersItem::
NumbersItem(CQCountdown *countdown, const QPointF &pos) :
 countdown_(countdown)
{
  QFont font(FONT_NAME2, 30);

  int ind = 0;

  int numBig   = RandIn(0, 4);
  int numSmall = NUM_ITEMS - numBig;

  for (int i = 0; i < numBig; ++i) {
    int pos = RandIn(20, 23);

    while (used_.find(pos) != used_.end())
      pos = RandIn(20, 23);

    used_.insert(pos);

    items_[ind] = new NumberItem(this, QString("%1").arg(numbers[pos]));

    ++ind;
  }

  for (int i = 0; i < numSmall; ++i) {
    int pos = RandIn(0, 19);

    while (used_.find(pos) != used_.end())
      pos = RandIn(0, 19);

    used_.insert(pos);

    items_[ind] = new NumberItem(this, QString("%1").arg(numbers[pos]));

    ++ind;
  }

  double x = pos.x();
  double y = pos.y();

  for (uint i = 0; i < NUM_ITEMS; ++i) {
    items_[i]->setFont(font);

    items_[i]->setPos(QPointF(x, y));

    x += items_[i]->boundingRect().width() + 10;
  }
}

void
NumbersItem::
revert(const QString &str)
{
  for (uint i = 0; i < NUM_ITEMS; ++i) {
    if (items_[i]->toPlainText() == str && items_[i]->getUsed()) {
      items_[i]->setUsed(false);
      break;
    }
  }
}

//------

NumberItem::
NumberItem(NumbersItem *numbersItem, const QString &str) :
 QGraphicsTextItem(str), numbersItem_(numbersItem), used_(false)
{
  setFlags(QGraphicsItem::ItemIsSelectable);
}

void
NumberItem::
mousePressEvent(QGraphicsSceneMouseEvent *e)
{
  if (used_) return;

  newItem_ = new QGraphicsTextItem(toPlainText());

  newItem_->setFont(font());
  newItem_->setZValue(10);

  numbersItem_->getCountDown()->addItem(newItem_);

  delta_ = pos() - e->pos();

  newItem_->setPos(pos());
}

void
NumberItem::
mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
  if (! newItem_) return;

  newItem_->setPos(e->pos() + delta_);

  WorkAreaItem *workArea = numbersItem_->getCountDown()->getWorkArea();

  QPointF pos1 = mapToItem(workArea, e->pos());

  workArea->removeDummyItems();

  if (workArea->contains(pos1)) {
    workArea->addNumberItem(newItem_->toPlainText(), pos1, true);

    workArea->setActive(true);
  }
  else
    workArea->setActive(false);
}

void
NumberItem::
mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
  if (! newItem_) return;

  newItem_->setPos(e->pos() + delta_);

  WorkAreaItem *workArea = numbersItem_->getCountDown()->getWorkArea();

  QPointF pos1 = mapToItem(workArea, e->pos());

  workArea->removeDummyItems();

  if (workArea->contains(pos1)) {
    workArea->addNumberItem(newItem_->toPlainText(), pos1);

    setUsed(true);
  }

  workArea->setActive(false);

  delete newItem_;

  newItem_ = NULL;
}

void
NumberItem::
setUsed(bool used)
{
  used_ = used;

  if (used_)
    setDefaultTextColor(QColor(200, 200, 200));
  else
    setDefaultTextColor(QColor(0, 0, 0));
}

//------

WorkAreaItem::
WorkAreaItem(CQCountdown *countdown, const QPointF &pos) :
 QGraphicsRectItem(), countdown_(countdown)
{
  setRect(10, pos.y(), 580, 100);
}

void
WorkAreaItem::
addNumberItem(const QString &str, const QPointF &pos, bool isDummy)
{
  QFont font(FONT_NAME2, 25);

  WorkItem *item = new WorkItem(this, str, true);

  item->setIsDummy(isDummy);

  countdown_->addItem(item);

  items_.push_back(item);

  item->setPos(pos);

  item->setFont(font);

  layout();
}

void
WorkAreaItem::
addOpItem(const QString &str, const QPointF &pos, bool isDummy)
{
  QFont font(FONT_NAME2, 30);

  WorkItem *item = new WorkItem(this, str, false);

  item->setIsDummy(isDummy);

  countdown_->addItem(item);

  items_.push_back(item);

  item->setPos(pos);

  item->setFont(font);

  layout();
}

void
WorkAreaItem::
moveItem(const QString &str, const QPointF &pos)
{
  WorkItemList::iterator pw1, pw2;

  for (pw1 = items_.begin(), pw2 = items_.end(); pw1 != pw2; ++pw1) {
    WorkItem *item = dynamic_cast<WorkItem *>(*pw1);

    if (item->toPlainText() == str) {
      item->setPos(pos);
      break;
    }
  }

  layout();
}

void
WorkAreaItem::
removeItem(const QString &str)
{
  WorkItemList::iterator pw1, pw2;

  for (pw1 = items_.begin(), pw2 = items_.end(); pw1 != pw2; ++pw1) {
    WorkItem *item = dynamic_cast<WorkItem *>(*pw1);

    if (item->toPlainText() == str) {
      items_.erase(pw1);

      delete item;

      break;
    }
  }

  layout();
}

void
WorkAreaItem::
removeDummyItems()
{
  WorkItemList::iterator pw1, pw2;

  for (pw1 = items_.begin(), pw2 = items_.end(); pw1 != pw2; ++pw1) {
    WorkItem *item = dynamic_cast<WorkItem *>(*pw1);

    if (item->isDummy()) {
      items_.erase(pw1);

      delete item;

      break;
    }
  }

  layout();
}

void
WorkAreaItem::
layout()
{
  typedef std::map<int, WorkItem *> ItemMap;

  double max_h = 0.0;

  ItemMap itemMap;

  WorkItemList::const_iterator pw1, pw2;

  for (pw1 = items_.begin(), pw2 = items_.end(); pw1 != pw2; ++pw1) {
    WorkItem *item = dynamic_cast<WorkItem *>(*pw1);

    if (item->isHidden()) continue;

    int pos = int(item->pos().x());

    while (itemMap.find(pos) != itemMap.end())
      ++pos;

    itemMap[pos] = item;

    max_h = std::max(item->boundingRect().height(), max_h);
  }

  QString str;

  double x = rect().left() + 8;
  double y = rect().top();

  double dy = rect().height() - max_h;

  ItemMap::const_iterator pi1, pi2;

  for (pi1 = itemMap.begin(), pi2 = itemMap.end(); pi1 != pi2; ++pi1) {
    WorkItem *item = (*pi1).second;

    item->setPos(QPointF(x, y + dy/2));

    if (x > 0)
      str += " ";

    str += item->toPlainText();

    x += item->boundingRect().width() + 5;
  }

  CEval eval;

  double result = 0;

  if (eval.eval(str.toStdString(), &result))
    countdown_->getGuess()->setGuess(int(result));
}

void
WorkAreaItem::
setActive(bool active)
{
  active_ = active;

  if (active_)
    setPen(QPen(QColor(150,150,250)));
  else
    setPen(QPen(Qt::NoBrush));

  update();
}

//------

WorkItem::
WorkItem(WorkAreaItem *workArea, const QString &str, bool isNumber) :
 QGraphicsTextItem(str), workArea_(workArea), isNumber_(isNumber), isHidden_(false), isDummy_(false)
{
}

void
WorkItem::
setIsHidden(bool isHidden)
{
  isHidden_ = isHidden;

  if (isHidden_) {
    setDefaultTextColor(QColor(255, 255, 255));

    setZValue(-10);
  }
  else {
    setDefaultTextColor(QColor(0, 0, 0));

    setZValue(0);
  }
}

void
WorkItem::
setIsDummy(bool isDummy)
{
  isDummy_ = isDummy;

  if (isDummy_)
    setDefaultTextColor(QColor(200, 200, 200));
  else
    setDefaultTextColor(QColor(0, 0, 0));
}

void
WorkItem::
mousePressEvent(QGraphicsSceneMouseEvent *e)
{
  newItem_ = new QGraphicsTextItem(toPlainText());

  newItem_->setFont(font());
  newItem_->setZValue(10);

  workArea_->getCountDown()->addItem(newItem_);

  delta_ = pos() - e->pos();

  newItem_->setPos(pos());
}

void
WorkItem::
mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
  if (! newItem_) return;

  setIsHidden(true);

  workArea_->layout();

  newItem_->setPos(e->pos() + delta_);

  QPointF pos1 = mapToItem(workArea_, e->pos());

  workArea_->removeDummyItems();

  if (workArea_->contains(pos1)) {
    if (isNumber_)
      workArea_->addNumberItem(newItem_->toPlainText(), pos1, true);
    else
      workArea_->addOpItem(newItem_->toPlainText(), pos1, true);

    workArea_->setActive(true);
  }
  else
    workArea_->setActive(false);
}

void
WorkItem::
mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
  if (! newItem_) return;

  newItem_->setPos(e->pos() + delta_);

  QPointF pos1 = mapToItem(workArea_, e->pos());

  if (workArea_->contains(pos1)) {
    setIsHidden(false);

    workArea_->removeDummyItems();

    setPos(pos1);

    workArea_->layout();

    workArea_->setActive(false);

    delete newItem_;

    newItem_ = NULL;
  }
  else {
    if (isNumber_) {
      QString str = newItem_->toPlainText();

      workArea_->getCountDown()->getNumbers()->revert(str);
    }

    workArea_->setActive(false);

    delete newItem_;

    newItem_ = NULL;

    setIsDummy(true);

    workArea_->removeDummyItems();
  }
}

//------

OpsItem::
OpsItem(CQCountdown *countdown, const QPointF &pos) :
 countdown_(countdown)
{
  QFont font(FONT_NAME2, 30);

  items_[0] = new OpItem(this, "+");
  items_[1] = new OpItem(this, "-");
  items_[2] = new OpItem(this, "*");
  items_[3] = new OpItem(this, "/");
  items_[4] = new OpItem(this, "(");
  items_[5] = new OpItem(this, ")");

  double x = pos.x();
  double y = pos.y();

  for (uint i = 0; i < NUM_OPS; ++i) {
    items_[i]->setFont(font);

    items_[i]->setPos(QPointF(x, y));

    x += items_[i]->boundingRect().width() + 10;
  }
}

//------

OpItem::
OpItem(OpsItem *opsItem, const QString &str) :
 QGraphicsTextItem(str), opsItem_(opsItem)
{
  setFlags(QGraphicsItem::ItemIsSelectable);
}

void
OpItem::
mousePressEvent(QGraphicsSceneMouseEvent *e)
{
  newItem_ = new QGraphicsTextItem(toPlainText());

  newItem_->setFont(font());
  newItem_->setZValue(10);

  opsItem_->getCountDown()->addItem(newItem_);

  delta_ = pos() - e->pos();

  newItem_->setPos(pos());
}

void
OpItem::
mouseMoveEvent(QGraphicsSceneMouseEvent *e)
{
  newItem_->setPos(e->pos() + delta_);

  WorkAreaItem *workArea = opsItem_->getCountDown()->getWorkArea();

  QPointF pos1 = mapToItem(workArea, e->pos());

  workArea->removeDummyItems();

  if (workArea->contains(pos1)) {
    workArea->addOpItem(newItem_->toPlainText(), pos1, true);

    workArea->setActive(true);
  }
  else
    workArea->setActive(false);
}

void
OpItem::
mouseReleaseEvent(QGraphicsSceneMouseEvent *e)
{
  newItem_->setPos(e->pos() + delta_);

  WorkAreaItem *workArea = opsItem_->getCountDown()->getWorkArea();

  QPointF pos1 = mapToItem(workArea, e->pos());

  workArea->removeDummyItems();

  if (workArea->contains(pos1))
    workArea->addOpItem(newItem_->toPlainText(), pos1);

  workArea->setActive(false);

  delete newItem_;

  newItem_ = NULL;
}
