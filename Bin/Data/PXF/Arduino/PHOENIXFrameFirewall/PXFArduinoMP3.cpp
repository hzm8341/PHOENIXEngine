// PXFArduinoMP3.cpp

#include "PXFArduino.h"

//----------------------------------------------------------------------------
void PXFArduino::_MP3Init_(int pinR, int pinT)
{
#if defined PXF_MP3
  if (mMP3Serial)
  {
    delete mMP3Serial;
    mMP3Serial = 0;
  }
  mMP3Serial = new SoftwareSerial(pinR, pinT);
  mMP3Serial->begin(9600);
  mp3_set_serial (*mMP3Serial); //set Serial for DFPlayer-mini mp3 module 
#endif
}
//----------------------------------------------------------------------------
void PXFArduino::_MP3Play()
{
#if defined PXF_MP3
    mp3_play();
#endif
}
//----------------------------------------------------------------------------
void PXFArduino::_MP3PlayStop()
{
#if defined PXF_MP3
    mp3_stop();
#endif
}
//----------------------------------------------------------------------------
void PXFArduino::_MP3PlayIndex(int index)
{
#if defined PXF_MP3
    mp3_play(index);
#endif
}
//----------------------------------------------------------------------------
void PXFArduino::_MP3SetVolume(int volume)
{
#if defined PXF_MP3
    mp3_set_volume(volume);
    delay(100);
#endif
}
//----------------------------------------------------------------------------
void PXFArduino::_MP3Next()
{
#if defined PXF_MP3
    mp3_next();
#endif
}
//----------------------------------------------------------------------------
