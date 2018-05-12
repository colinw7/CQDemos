class CTclFireworks;

class CTclFireworksCanvas : public CTclCanvas {
 private:
  CTclFireworks *particle_;

 public:
  CTclFireworksCanvas(CTclApp *app);
 ~CTclFireworksCanvas();

  bool instanceCommand(int argc, const char **argv);
  bool instanceConfigure(int argc, const char **argv);

  void draw();
  void tick();
};
