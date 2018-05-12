#include <CQMainWindow.h>
#include <CPoint2D.h>
#include <QGLWidget>

class CQMenu;
class CQMenuItem;
class CQGLControl;
class CQGLControlToolBar;
class CQGLNetCanvas;
class CXMLTag;

class CQGLNet : public CQMainWindow {
  Q_OBJECT

 private:
  class Shape {
   public:
    Shape(CQGLNet *net, const std::string &type, const std::string &name,
          const std::string &layer, const std::vector<CPoint2D> &points);

    void draw();

    void drawCube(double x1, double y1, double z1, double x2, double y2, double z2);

   private:
    typedef std::vector<CPoint2D> PointArray;

    CQGLNet     *net_;
    std::string  type_;
    std::string  name_;
    std::string  layer_;
    PointArray   points_;
  };

 public:
  CQGLNet();

  void loadNet(const char *filename);

  void loadShape(const std::string &name, CXMLTag *tag);

  CQGLControl *getControl() const { return control_; }

  QWidget *createCentralWidget();

  void createWorkspace();
  void createMenus();
  void createToolBars();
  void createStatusBar();
  void createDockWindows();

  void initNet();

  void addShape(const std::string &type, const std::string &name, const std::string &layer,
                const std::vector<CPoint2D> &points);

  void drawShapes();

  double getDz() const { return dz_; }

 private slots:
  void controlSlot();

 private:
  typedef std::vector<Shape *> ShapeArray;

  CQGLNetCanvas      *canvas_;
  CQGLControl        *control_;
  CQGLControlToolBar *toolbar_;

  CQMenu *fileMenu_;
  CQMenu *helpMenu_;

  double     xmin_, ymin_, xmax_, ymax_, dz_;
  ShapeArray shapes_;
};

class CQGLNetCanvas : public  QGLWidget {
  Q_OBJECT

 public:
  CQGLNetCanvas(CQGLNet *net);

 private:
  void paintGL();

  void resizeGL(int width, int height);

  void mousePressEvent  (QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent   (QMouseEvent *event);

  void keyPressEvent(QKeyEvent *event);

 private:
  CQGLNet *net_;
};
