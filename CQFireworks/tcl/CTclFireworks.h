class CTclFireworksCanvas;

class CTclFireworks : public CFireworks {
 private:
  CTclFireworksCanvas *canvas_;

 public:
  CTclFireworks(CTclFireworksCanvas *canvas);

  void tick();

  void drawInit() const;
  void drawTerm() const;

  void clear(const CRGBA &rgba);
  void setForeground(const CRGBA &rgba);
  void drawPoint(int x, int y);
};
