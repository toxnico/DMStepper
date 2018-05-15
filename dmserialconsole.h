#ifndef DM_SERIAL_CONSOLE_H
#define DM_SERIAL_CONSOLE_H

#include "Arduino.h"

class DMSerialConsole{

private:
  Stream *_stream = NULL;

  String _currentLine;
  bool   _hasLine = false;

public:

  String update();

};

#endif DM_SERIAL_CONSOLE_H
