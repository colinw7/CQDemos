#include <QMainWindow>

class QGraphicsScene;
class QGraphicsView;

class CQEduTimes : public QMainWindow {
  Q_OBJECT

 public:
  CQEduTimes();

 private:
  QGraphicsScene *scene_;
  QGraphicsView  *view_;
};
