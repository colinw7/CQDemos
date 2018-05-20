#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;
class QGraphicsItem;
class QLabel;
class AnswerItem;
class GuessItem;
class NumbersItem;
class WorkAreaItem;

class CQCountdown : public QMainWindow {
  Q_OBJECT

 public:
  CQCountdown();

  void addItem(QGraphicsItem *item);

  NumbersItem  *getNumbers () const { return numbers_; }
  WorkAreaItem *getWorkArea() const { return workArea_; }
  AnswerItem   *getAnswer  () const { return answer_; }
  GuessItem    *getGuess   () const { return guess_; }

  uint getWidth () const { return w_; }
  uint getHeight() const { return h_; }

  void setPosLabel(const QPointF &pos);

 private:
  uint            w_, h_;
  QGraphicsScene *scene_;
  QGraphicsView  *view_;
  AnswerItem     *answer_;
  GuessItem      *guess_;
  NumbersItem    *numbers_;
  WorkAreaItem   *workArea_;
  QLabel         *posLabel_;
};
