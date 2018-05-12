class CTclFireworksCanvas;

class CTclFireworksCanvasCmd : public CTclAppCanvasCmd {
 private:
  CTclFireworksCanvas *particle_canvas_;

 public:
  CTclFireworksCanvasCmd(CTclApp *app);
 ~CTclFireworksCanvasCmd();

  string getCommandName () const { return "CTclFireworksCanvas"; }
  string getCommandClass() const { return "CTclFireworksCanvas"; }

  CTclAppCanvas *createInstance(CTclApp *app);

  void initInstance(CTclApp *app);

  void tick();
};
