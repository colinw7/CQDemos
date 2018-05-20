#include <CQCharon.h>

#include <QPainter>
#include <QKeyEvent>
#include <cassert>

static const char *
page1[] = {
 "<C><B>CHARON<b> \n "
 "by LORD DUNSANY 1925<c>"
};

static const char *
page2[] = {
"<B>C<b>haron leaned forward and rowed. "
"All things were one with his "
"weariness."
};

static const char *
page3[] = {
"<B>I<b>t was not with him a matter of "
"years or of centuries, but of wide "
"floods of time, and an old heaviness "
"and a pain in the arms that had "
"become for him part of the scheme "
"that the Gods had made and was of "
"a piece with Eternity."
};

static const char *
page4[] = {
"<B>I<b>f the gods had even sent him a "
"contrary wind it would have "
"divided all time in his memory "
"into two equal slabs."
};

static const char *
page5[] = {
"<B>S<b>o grey were all things always "
"where he was that if any "
"radiance lingered a moment "
"among the dead, on the face of such a "
"queen perhaps as Cleopatra, his eyes "
"could not have perceived it."
};

static const char *
page6[] = {
"<B>I<b>t was strange that the dead "
"nowadays were coming in such numbers. "
"They were coming in thousands where "
"they used to come in fifties. It was "
"neither Charon's duty nor his wont to "
"ponder in his grey soul why these things "
"might be. Charon leaned forward and "
"rowed."
};

static const char *
page7[] = {
"<B>T<b>hen no one came for a while. "
"It was not unusual for the Gods "
"to send no one down from "
"Earth for such a space. But the Gods "
"knew best."
};

static const char *
page8[] = {
"<B>T<b>hen one man "
"came alone. And "
"the little shade sat shivering "
"on a lonely bench "
"and the great boat pushed "
"off. Only one passenger; "
"the Gods knew best. And "
"great and weary Charon "
"rowed on and on beside "
"the little, silent, shivering "
"ghost."
};

static const char *
page9[] = {
"<B>AND<b> the sound of the "
"river was like a mighty "
"sigh that Grief in the "
"beginning had sighed "
"among her sisters, and "
"that could not die like "
"the echoes of human "
"sorrow failing on "
"earthly hills, but was "
"as old as time and the "
"pain in Charon's arms."
};

static const char *
page10[] = {
"<B>T<b>hen the boat from the slow, "
"grey river loomed up to the "
"coast of Dis and the little, "
"silent shade still shivering stepped "
"ashore, and Charon turned the boat "
"to go wearily back to the world. Then "
"the little shadow spoke, that had been "
"a man."
};

static const char *
page10a[] = {
"\"I am the last,\" he said. "
};

static const char *
page10b[] = {
"No one had ever made Charon "
"smile before, no one before had ever "
"made him weep."
};

static const char *
page11[] = {
"<B><C>THE END<c><b>"
};

//------

Word::
Word()
{
}

void
Word::
addChar(char c, const CharStyle &style)
{
  chars_.push_back(Char(c, style));
}

uint
Word::
length() const
{
  return chars_.size();
}

const Char &
Word::
getChar(uint i) const
{
  return chars_[i];
}

//------

Page::
Page(const char *str, const Rect &textArea, uint bgNum) :
 textArea_(textArea), bgNum_(bgNum)
{
  addWords(str);
}

void
Page::
addWords(const char *str)
{
  CharStyle style;

  bool in_modifier = false;

  uint pos = 0;
  uint len = strlen(str);

  while (pos < len) {
    while (pos < len && str[pos] == ' ')
      ++pos;

    Word word;

    while (pos < len && str[pos] != ' ') {
      char c = str[pos++];

      if (! in_modifier) {
        if (c == '<')
          in_modifier = true;
        else
          word.addChar(c, style);
      }
      else {
        if      (c == '>')
          in_modifier = false;
        else if (c == 'B')
          style.bold = true;
        else if (c == 'b')
          style.bold = false;
        else if (c == 'I')
          style.italic = true;
        else if (c == 'i')
          style.italic = false;
        else if (c == 'C')
          style.center = true;
        else if (c == 'c')
          style.center = false;
      }
    }

    if (word.length() > 0)
      addWord(word);
  }
}

void
Page::
addWord(const Word &word)
{
  words_.push_back(word);
}

void
Page::
setTextArea(const Rect &rect)
{
  textArea_ = rect;
}

//------

Book::
Book() :
 pageNum_(0)
{
}

void
Book::
initPages()
{
  addPage(new Page(page1  [0], Rect(100, 250, 700, 350), 0));
  addPage(new Page(page2  [0], Rect(100, 200, 700, 400), 0));
  addPage(new Page(page3  [0], Rect(100, 200, 700, 400), 0));
  addPage(new Page(page4  [0], Rect(100, 200, 700, 400), 0));
  addPage(new Page(page5  [0], Rect(100, 200, 700, 400), 0));
  addPage(new Page(page6  [0], Rect(100, 200, 700, 400), 0));
  addPage(new Page(page7  [0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page8  [0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page9  [0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page10 [0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page10a[0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page10b[0], Rect(100, 200, 700, 400), 1));
  addPage(new Page(page11 [0], Rect(100, 280, 700, 320), 1));
}

void
Book::
addPage(Page *page)
{
  pages_.push_back(page);
}

Page *
Book::
getPage() const
{
  assert(pageNum_ < getNumPages());

  return pages_[pageNum_];
}

void
Book::
nextPage()
{
  if (pageNum_ < getNumPages() - 1)
    ++pageNum_;
}

void
Book::
prevPage()
{
  if (pageNum_ > 0)
    --pageNum_;
}

//------

CQCharon::
CQCharon() :
 painter_(NULL), normalFm_(font()), boldFm_(font())
{
  paperImage_   = QImage("images/paper_fit.png");
  bandImage_    = QImage("images/band.png");
  scrollsImage_ = QImage("images/scrolls.png");

  setFixedSize(800, 600);

  normalFont_ = QFont("Garuda", 20);
  boldFont_   = QFont("Garuda", 30); boldFont_.setBold(true);

  normalFm_ = QFontMetrics(normalFont_);
  boldFm_   = QFontMetrics(boldFont_);

  setFont(normalFont_);

  book_.initPages();
}

void
CQCharon::
resizeEvent(QResizeEvent *)
{
  delete painter_;

  image_ = QImage(width(), height(), QImage::Format_ARGB32);

  painter_ = new QPainter(&image_);

  painter_->setFont(normalFont_);

  drawPage();
}

void
CQCharon::
paintEvent(QPaintEvent *)
{
  if (! painter_) return;

  QPainter p(this);

  p.drawImage(0, 0, image_);
}

void
CQCharon::
mousePressEvent(QMouseEvent *)
{
  book_.nextPage();

  drawPage();

  update();
}

void
CQCharon::
keyPressEvent(QKeyEvent *e)
{
  if      (e->key() == Qt::Key_N) {
    book_.nextPage();

    drawPage();

    update();
  }
  else if (e->key() == Qt::Key_P) {
    book_.prevPage();

    drawPage();

    update();
  }
}

void
CQCharon::
drawPage()
{
  //image_.fill(0);

  Page *page = book_.getPage();

  int bgNum = page->getBgNum();

  if (bgNum == 0) {
    painter_->drawImage(0, 0, paperImage_);

    for (uint i = 0; i < 10; ++i) {
      painter_->drawImage(i*147,  40, bandImage_);
      painter_->drawImage(i*147, 480, bandImage_);
    }

    painter_->setPen(QColor(0,0,0));
  }
  else {
    painter_->drawImage(0, 0, scrollsImage_);

    painter_->setPen(QColor(200,200,255));
  }

  drawWordsInRect(page->getWords(), page->getTextArea());
}

void
CQCharon::
drawWordsInRect(const Page::Words &words, const Rect &rect)
{
  int char_height = normalFm_.ascent();
  int space_width = normalFm_.width(" ");

  int x = rect.xmin;
  int y = rect.ymin;

  uint i        = 0;
  uint numWords = words.size();

  while (i < numWords) {
    uint j = i;

    int w = 0;

    bool center = false;

    while (j < numWords) {
      const Word &word = words[j];

      const Char &c = word.getChar(0);

      if (c.style.center) center = true;

      if (w > 0 && c.c == '\n') break;

      int width = wordWidth(word);

      if (rect.xmin + w + width > rect.xmax && w > 0)
        break;

      if (w > 0)
        w += space_width;

      w += width;

      ++j;
    }

    --j;

    int dx = 0;

    if (center)
      dx = (rect.xmax - rect.xmin - w)/2;

    x = rect.xmin + dx;

    for (uint k = i; k <= j; ++k) {
      const Word &word = words[k];

      int width = wordWidth(word);

      drawWord(x, y, word);

      x += width + space_width;
    }

    i = j + 1;

    y += char_height;
    x  = rect.xmin;
  }
}

uint
CQCharon::
wordWidth(const Word &word)
{
  if (word.getChar(0).c == '\n') return 0;

  uint l = word.length();

  uint width = 0;

  for (uint i = 0; i < l; ++i) {
    const Char &c = word.getChar(i);

    if (c.style.bold)
      width += boldFm_.width(c.c);
    else
      width += normalFm_.width(c.c);
  }

  return width;
}

void
CQCharon::
drawWord(int x, int y, const Word &word)
{
  if (word.getChar(0).c == '\n') return;

  char str[2];

  str[1] = '\0';

  uint l = word.length();

  for (uint i = 0; i < l; ++i) {
    const Char &c = word.getChar(i);

    str[0] = c.c;

    if (c.style.bold)
      painter_->setFont(boldFont_);
    else
      painter_->setFont(normalFont_);

    painter_->drawText(x, y, str);

    if (c.style.bold)
      x += boldFm_.width(str[0]);
    else
      x += normalFm_.width(str[0]);
  }
}
