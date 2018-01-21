#include "focuser.h"
#import <Cocoa/Cocoa.h>

// https://stackoverflow.com/questions/17403511/qwidget-on-mac-os-x-not-focusing-in-qt-5-x

Focuser::Focuser(QWidget *w) {
  this->widget = w;
}

void Focuser::show() {
  this->widget->show();
  this->focus();
}

void Focuser::focus() {
  [NSApp activateIgnoringOtherApps:YES];
  this->widget->activateWindow();
  this->widget->raise();
}
