#include <CQEduTimes.h>

#include <CQApp.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QKeyEvent>

class Equation;

class AnswerItem : public QGraphicsTextItem {
 public:
  AnswerItem(Equation *eq);

  void hoverEnterEvent(QGraphicsSceneHoverEvent *);
  void hoverLeaveEvent(QGraphicsSceneHoverEvent *);

  void keyPressEvent(QKeyEvent *e);

 private:
  Equation *eq_;
  int       guess_;
};

class Equation {
 public:
  Equation(int lhs, int rhs) :
   lhs_(lhs), rhs_(rhs), answer_(lhs*rhs) {
    font_ = QFont("helvetica", 50);

    lhsText_    = NULL;
    opText_     = NULL;
    rhsText_    = NULL;
    eqText_     = NULL;
    answerText_ = NULL;
  }

  const QFont &getFont() const { return font_; }

  void addToScene(QGraphicsScene *scene) {
    lhsText_= scene->addText(QString("%1").arg(lhs_));
    opText_ = scene->addText("*");
    rhsText_= scene->addText(QString("%1").arg(rhs_));
    eqText_ = scene->addText("=");

    lhsText_->setFont(font_);
    opText_ ->setFont(font_);
    rhsText_->setFont(font_);
    eqText_ ->setFont(font_);

    answerText_ = new AnswerItem(this);

    scene->addItem(answerText_);

    double x = 0;
    double y = 0;

    lhsText_   ->setPos(QPointF(x, y)); x += lhsText_->boundingRect().width();
    opText_    ->setPos(QPointF(x, y)); x += opText_ ->boundingRect().width();
    rhsText_   ->setPos(QPointF(x, y)); x += rhsText_->boundingRect().width();
    eqText_    ->setPos(QPointF(x, y)); x += eqText_ ->boundingRect().width();
    answerText_->setPos(QPointF(x, y));
  }

 private:
  QFont font_;
  int   lhs_;
  int   rhs_;
  int   answer_;

  QGraphicsTextItem *lhsText_;
  QGraphicsTextItem *opText_;
  QGraphicsTextItem *rhsText_;
  QGraphicsTextItem *eqText_;
  QGraphicsTextItem *answerText_;
};

int
main(int argc, char **argv)
{
  CQApp app(argc, argv);

  CQEduTimes *window = new CQEduTimes;

  window->show();

  app.exec();
}

CQEduTimes::
CQEduTimes() :
 QMainWindow()
{
  Equation eq(5, 4);

  scene_ = new QGraphicsScene;

  eq.addToScene(scene_);

  view_ = new QGraphicsView(scene_);

  setCentralWidget(view_);
}

//------

AnswerItem::
AnswerItem(Equation *eq) :
 QGraphicsTextItem("?"), eq_(eq), guess_(-1)
{
  setFont(eq_->getFont());

  setFlags(QGraphicsItem::ItemIsFocusable);

  //setTextInteractionFlags(Qt::TextEditable);
}

void
AnswerItem::
hoverEnterEvent(QGraphicsSceneHoverEvent *)
{
  setDefaultTextColor(Qt::red);
}

void
AnswerItem::
hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
  setDefaultTextColor(Qt::black);
}

void
AnswerItem::
keyPressEvent(QKeyEvent *e)
{
  int k = e->key();

  if (k >= Qt::Key_0 && k <= Qt::Key_9) {
    int num = k - Qt::Key_0;

    if (guess_ == -1)
      guess_ = num;
    else
      guess_ = 10*guess_ + num;
  }
  else
    guess_ = -1;

  if (guess_ < 0)
    setPlainText("?");
  else
    setPlainText(QString("%1").arg(guess_));
}
