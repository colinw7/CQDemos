class CTclFireworksCanvasCmd;

class CTclFireworksApp : public CTclApp {
 private:
  class Tick : public CTick {
   private:
    CTclFireworksApp *app_;

   public:
    Tick(CTclFireworksApp *app) :
     CTick(10000), app_(app) {
    }

    void exec();
  };

  CTclFireworksCanvasCmd *cmd_;
  Tick                   tick_;

 public:
  CTclFireworksApp(int argc, char **argv);
 ~CTclFireworksApp();

 protected:
  void addCommands();

  string getTclStr() {
    return CTclFireworks_TK;
  }

  void mainLoop();
  void idle();
  void tick();
};
