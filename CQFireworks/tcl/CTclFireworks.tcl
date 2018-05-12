proc createWidgets { } {
  wm protocol . WM_DELETE_WINDOW exitCB

  #----

  global canvas

  set canvas .canvas

  CTclFireworksCanvas $canvas -width 400 -height 600

  pack $canvas -side left -fill both -expand true

  focus $canvas
}

proc exitCB { } {
  exit
}

createWidgets
