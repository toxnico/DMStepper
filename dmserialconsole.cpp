#include "dmserialconsole.h"

String DMSerialConsole::update(){
  if(_stream->available() > 0)
  {
    int c = _stream->read();
    if(c < 0) //never, in theory!
      return NULL;

    if(c == 10) //EOL?
    {
      String s = this->_currentLine;
      this->_currentLine = "";
      return s;
    }

    this->_currentLine += (char)c;
  }

  return NULL;
}
