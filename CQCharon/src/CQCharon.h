#include <QWidget>

#include <vector>
#include <string>

struct Rect {
  Rect(int xmin_, int ymin_, int xmax_, int ymax_) :
   xmin(xmin_), ymin(ymin_), xmax(xmax_), ymax(ymax_) {
  }

  int xmin, ymin, xmax, ymax;
};

struct CharStyle {
  bool bold;
  bool italic;
  bool center;

  CharStyle() :
   bold(false), italic(false), center(false) {
  }
};

struct Char {
  char      c;
  CharStyle style;

  Char(char c_, CharStyle style_=CharStyle()) :
   c(c_), style(style_) {
  }
};

class Word {
 public:
  Word();

  void addChar(char c, const CharStyle &style);

  uint length() const;

  const Char &getChar(uint i) const;

 private:
  typedef std::vector<Char> Chars;

  Chars chars_;
};

class Page {
 public:
  typedef std::vector<Word> Words;

 public:
  Page(const char *str, const Rect &rect, uint bgNum);

  void addWords(const char *str);

  void addWord(const Word &word);

  void setTextArea(const Rect &rect);

  const Words &getWords() const { return words_; }

  const Rect  &getTextArea() const { return textArea_; }

  uint getBgNum() const { return bgNum_; }

 private:
  Words words_;
  Rect  textArea_;
  int   bgNum_;
};

class Book {
 public:
  Book();

  void initPages();

  void addPage(Page *page);

  Page *getPage() const;

  uint getPageNum () const { return pageNum_; }
  uint getNumPages() const { return pages_.size(); }

  void nextPage();
  void prevPage();

 private:
  typedef std::vector<Page *> Pages;

  Pages pages_;
  uint  pageNum_;
};

class CQCharon : public QWidget {
  Q_OBJECT

 public:
  CQCharon();

 private:
  void resizeEvent(QResizeEvent *);
  void paintEvent (QPaintEvent *);

  void mousePressEvent(QMouseEvent *);

  void keyPressEvent(QKeyEvent *);

  void drawPage();

  void drawWordsInRect(const Page::Words &words, const Rect &rect);

  uint wordWidth(const Word &word);

  void drawWord(int x, int y, const Word &word);

 private:
  Book          book_;
  QImage        paperImage_;
  QImage        bandImage_;
  QImage        scrollsImage_;
  QImage        image_;
  QPainter     *painter_;
  QFont         normalFont_;
  QFont         boldFont_;
  QFontMetrics  normalFm_;
  QFontMetrics  boldFm_;
};
