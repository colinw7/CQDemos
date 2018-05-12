#include <std_c++.h>
#include <CTclApp/CTclApp.h>
#include <CTclCanvas/CTclCanvas.h>
#include <CTick/CTick.h>
#include <CFireworks/CFireworks.h>

#include "CTclFireworks.k"

#include "CTclFireworksApp.h"
#include "CTclFireworksCanvasCmd.h"
#include "CTclFireworksCanvas.h"
#include "CTclFireworks.h"

int
main(int argc, char **argv)
{
  CTclFireworksApp app(argc, argv);
}

//-------------

CTclFireworksApp::
CTclFireworksApp(int argc, char **argv) :
 CTclApp(argc, argv), cmd_(NULL), tick_(this)
{
  init();
}

CTclFireworksApp::
~CTclFireworksApp()
{
  delete cmd_;
}

void
CTclFireworksApp::
addCommands()
{
  cmd_ = new CTclFireworksCanvasCmd(this);
}

void
CTclFireworksApp::
mainLoop()
{
  tkIdleMainLoop();
}

void
CTclFireworksApp::
idle()
{
  tick_.update();
}

void
CTclFireworksApp::
tick()
{
  cmd_->tick();
}

void
CTclFireworksApp::Tick::
exec()
{
  app_->tick();
}

//-------------

CTclFireworksCanvasCmd::
CTclFireworksCanvasCmd(CTclApp *app) :
 CTclAppCanvasCmd(app), particle_canvas_(NULL)
{
  init();
}

CTclFireworksCanvasCmd::
~CTclFireworksCanvasCmd()
{
  delete particle_canvas_;
}

CTclAppCanvas *
CTclFireworksCanvasCmd::
createInstance(CTclApp *app)
{
  particle_canvas_ = new CTclFireworksCanvas(app);

  return (CTclAppCanvas *) particle_canvas_->getCanvasWidget();
}

void
CTclFireworksCanvasCmd::
initInstance(CTclApp *)
{
}

void
CTclFireworksCanvasCmd::
tick()
{
  if (particle_canvas_ != NULL)
    particle_canvas_->tick();
}

//-------------

CTclFireworksCanvas::
CTclFireworksCanvas(CTclApp *app) :
 CTclCanvas(app)
{
  particle_ = new CTclFireworks(this);
}

CTclFireworksCanvas::
~CTclFireworksCanvas()
{
  delete particle_;
}

bool
CTclFireworksCanvas::
instanceCommand(int, const char **)
{
  return false;
}

bool
CTclFireworksCanvas::
instanceConfigure(int, const char **)
{
  return false;
}

void
CTclFireworksCanvas::
tick()
{
  if (particle_ != NULL)
    particle_->tick();
}

void
CTclFireworksCanvas::
draw()
{
}

//-------------

CTclFireworks::
CTclFireworks(CTclFireworksCanvas *canvas) :
 canvas_(canvas)
{
}

void
CTclFireworks::
drawInit() const
{
  canvas_->setBackground(CRGB(0,0,0));
  canvas_->setForeground(CRGB(1,1,1));

  canvas_->startDoubleBuffer();

  canvas_->clear();
}

void
CTclFireworks::
drawTerm() const
{
  canvas_->endDoubleBuffer();

  canvas_->flush();
}

void
CTclFireworks::
tick()
{
  step();

  drawInit();

  draw(canvas_->getWidth(), canvas_->getHeight());

  drawTerm();
}

void
CTclFireworks::
clear(const CRGBA &)
{
}

void
CTclFireworks::
setForeground(const CRGBA &rgba)
{
  canvas_->setForeground(rgba.getRGB());
}

void
CTclFireworks::
drawPoint(int x, int y)
{
  canvas_->drawPoint(x, y);
}
