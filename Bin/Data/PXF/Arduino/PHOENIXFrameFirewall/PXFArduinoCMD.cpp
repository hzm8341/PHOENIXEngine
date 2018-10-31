// PXFArduinoCMD.cpp
#include "PXFArduino.h"

//----------------------------------------------------------------------------
void PXFArduino::OnCMD(String &cmdStr)
{
  int i=0;
  for (; i<NumCMDParams; i++)
  {
    mCmdParams[i] = "";
  }

  String strs = cmdStr;
  mCMDIndexTemp = 0;
  mpCMDParam = strtok((char *)cmdStr.c_str(), " ");
  while (mpCMDParam)
  {
    mCmdParams[mCMDIndexTemp] = String(mpCMDParam);
    mCMDIndexTemp++;
    mpCMDParam = strtok(NULL, " ");

    if (mCMDIndexTemp > NumCMDParams)
      break;
  }

  if (mCMDIndexTemp > 0)
  {
    char cmdCH = atoi(mCmdParams[0].c_str());
    if (sOptTypeVal[OT_TOGET_NETID] == cmdCH)
    {
      _SendNetID();
    }
    else if (sOptTypeVal[OT_SET_TIME] == cmdCH)
    {
      _SetTime();
    }
    else if (sOptTypeVal[OT_SET_BABYROBOT] == cmdCH)
    {
      bool moto = _Str2Bool(mCmdParams[1]);
      bool distance = _Str2Bool(mCmdParams[2]);
      int buzzer = _Str2Bool(mCmdParams[3]);
      int light = _Str2Bool(mCmdParams[4]);
      _SetBabyRobot(moto, diance, buzzer,light );
    }
    else if (sOptTypeVal[OT_PM] == cmdCH)
    {
      int pin = _Str2Pin(mCmdParams[1]);
      int val = _Str2IO(mCmdParams[2]);
      int i = _Str2PXFPin(mCmdParams[1]);
      PinModes[i] = val;
      pinMode(pin, val);
    }
    else if(sOptTypeVal[OT_DW]==cmdCH)
    {
      int pin = _Str2Pin(mCmdParams[1]);
      bool isHigh = _Str2Bool(mCmdParams[2]);
      digitalWrite(pin, isHigh?HIGH:LOW);
    }
    else if (sOptTypeVal[OT_AW]==cmdCH)
    {
      int pin = _Str2Pin(mCmdParams[1]);
      int val = _Str2Int(mCmdParams[2]);
      analogWrite(pin, val);
    }
    else if (sOptTypeVal[OT_RETURN_DR]==cmdCH)
    {
      int pin = _Str2Pin(mCmdParams[1]);
      int val = digitalRead(pin);

      int index = pin - P_0;
      
      char cmdCh = sOptTypeVal[OT_RETURN_DR];
      char strCMDCh[32];
      memset(strCMDCh, 0, 32);
      itoa(cmdCh, strCMDCh, 10);
        
      Serial.print("0000");
      Serial.print(String(strCMDCh)); 
      Serial.print(" ");
      Serial.print(index);
      Serial.print(" ");
      Serial.println(val);
    }
    else if (sOptTypeVal[OT_RETURN_AR]==cmdCH)
    {
      int pin = _Str2Pin(mCmdParams[1]);
      int val = analogRead(pin);
      
      int index = pin - P_0;
      
      char cmdCh = sOptTypeVal[OT_RETURN_AR];
      char strCMDCh[32];
      memset(strCMDCh, 0, 32);
      itoa(cmdCh, strCMDCh, 10);
        
      Serial.print("0000");
      Serial.print(String(strCMDCh)); 
      Serial.print(" ");
      Serial.print(index);
      Serial.print(" ");
      Serial.println(val);
    }
    else if (sOptTypeVal[OT_SVR_I]==cmdCH)
    {
#if defined PXF_SERVER
      int index = _Str2Int(mCmdParams[1]);
      int pin = _Str2Pin(mCmdParams[2]);
      if (0 <= index && index < NumMaxServer)
        mServo[index].attach(pin);
#endif
    }
    else if (sOptTypeVal[OT_SVR_W]==cmdCH)
    {
#if defined PXF_SERVER
      int index = _Str2Int(mCmdParams[1]);
      int val = _Str2Int(mCmdParams[2]);
      if (0 <= index && index < NumMaxServer)
        mServo[index].write(val);
#endif
    }
    else if (sOptTypeVal[OT_DST_I]==cmdCH)
    {
      int pinTrigger = _Str2Pin(mCmdParams[1]);
      int pinEcho = _Str2Pin(mCmdParams[2]);
      _DistInit_(pinTrigger, pinEcho);
    }
    else if (sOptTypeVal[OT_DST_T]==cmdCH)
    {
      long mDurationL;
      if(millis() - mDistCheckLastTime > 25)
      {
         mDistCheckLastTime = millis();
         _DistTest(); 
      }

      char cmdCh = sOptTypeVal[OT_RETURN_DIST];
      char strCMDCh[32];
      memset(strCMDCh, 0, 32);
      itoa(cmdCh, strCMDCh, 10);
      
      Serial.print("0000");
      Serial.print(String(strCMDCh)); 
      Serial.print(" ");
      Serial.println(mDist);
    }
    else if (sOptTypeVal[OT_MOTO_I]==cmdCH)
    {
      _MotoInit10111213();
    }
    else if (sOptTypeVal[OT_MOTO_I_DRIVER4567] == cmdCH)
    {
      _MotoInit4567();
    }
    else if (sOptTypeVal[OT_MOTO_I_DRIVER298N] == cmdCH)
    {
      int pinL = _Str2Pin(mCmdParams[1]);
      int pinL1 = _Str2Pin(mCmdParams[2]);
      int pinLS = _Str2Pin(mCmdParams[3]);
      int pinR = _Str2Pin(mCmdParams[4]);
      int pinR1 = _Str2Pin(mCmdParams[5]);
      int pinRS = _Str2Pin(mCmdParams[6]);      
      _MotoInit298N(pinL, pinL1, pinLS, pinR, pinR1, pinRS);
    }   
    else if (sOptTypeVal[OT_MOTO_RUN]==cmdCH)
    {
      int motoIndex = _Str2Int(mCmdParams[1]);
      int dir = _Str2DirType(mCmdParams[2]);
      int spd = _Str2Int(mCmdParams[3]);

      if (0 == dir)
        spd = 0;

      if (0 == motoIndex)
        _LeftRun(dir, spd);
      else if (1 == motoIndex)
        _RightRun(dir, spd);
    }
    else if (sOptTypeVal[OT_MOTO_RUNSIMPLE]==cmdCH)
    {
      int dir = _Str2SimpleDirType(mCmdParams[1]);
      int spd = _Str2Int(mCmdParams[2]);
      if (0 == dir)
      {
        spd = 0;
        _LeftRun(0, spd);
        _RightRun(0, spd);
      }
      else if (1 == dir)
      {
        _LeftRun(1, spd);
        _RightRun(1, spd);
      }
      else if (2 == dir)
      {
        _LeftRun(2, spd);
        _RightRun(2, spd);
      }
      else if (3 == dir)
      {
        _LeftRun(2, spd);
        _RightRun(1, spd);
      }
      else if (4 == dir)
      {
        _LeftRun(1, spd);
        _RightRun(2, spd);
      }
    }
    else if (sOptTypeVal[OT_MOTO_STOP]==cmdCH)
    {
      _LeftRun(0, 0);
      _RightRun(0, 0);
    }
    else if (sOptTypeVal[OT_MP3_INIT]==cmdCH)
    {
      int pinR = _Str2Pin(mCmdParams[1]);
      int pinT = _Str2Pin(mCmdParams[2]);
      _MP3Init(pinR, pinT);
    }
    else if (sOptTypeVal[OT_MP3_PLAY]==cmdCH)
    {
      _MP3Play();
    }
    else if (sOptTypeVal[OT_MP3_STOP]==cmdCH)
    {
      _MP3PlayStop();
    }
    else if (sOptTypeVal[OT_MP3_VOLUME]==cmdCH)
    {
      int volume = _Str2Int(mCmdParams[1]);
      _MP3SetVolume(volume);
    }
    else if (sOptTypeVal[OT_MP3_INDEX]==cmdCH)
    {
      int index = _Str2Int(mCmdParams[1]);
      _MP3PlayIndex(index);
    }
    else if (sOptTypeVal[OT_MP3_NEXT]==cmdCH)
    {
      _MP3Next();
    }
    else if (sOptTypeVal[OT_IR_INIT]==cmdCH)
    {
      int pinR = _Str2Pin(mCmdParams[1]);
      _IRInit(pinR);      
    }
    else if (sOptTypeVal[OT_IR_SEND]==cmdCH)
    {
      int val = _Str2Int(mCmdParams[1]);
      _IRSend(val);
    }
    else if (sOptTypeVal[OT_MOTO_I_SPD]==cmdCH)
    {
      int pinLA = _Str2Pin(mCmdParams[1]);
      int pinLB = _Str2Pin(mCmdParams[2]);
      int pinRA = _Str2Pin(mCmdParams[3]);
      int pinRB = _Str2Pin(mCmdParams[4]);
      _MotoSpeedInit(pinLA, pinLB, pinRA, pinRB);
    }
    else if (sOptTypeVal[OT_HX711_I]==cmdCH)
    {
      int index = _Str2Int(mCmdParams[1]);
      int pinOut = _Str2Pin(mCmdParams[2]);
      int pinClk = _Str2Pin(mCmdParams[3]);
      _HX711Init(index, pinOut, pinClk);
    }
    else if (sOptTypeVal[OT_HX711_TEST]==cmdCH)
    {
      int index = _Str2Int(mCmdParams[1]);
      float val = _ReadHX711(index);
      _HXSend(index, val);
    }
  }
}
//----------------------------------------------------------------------------
int PXFArduino::_Str2IO(String &str)
{
  char ch = atoi(str.c_str());
  if (0 == ch)
    return INPUT;
  
  return OUTPUT;
}
//----------------------------------------------------------------------------
int PXFArduino::_Str2Pin(String &str)
{
  int pinVal = atoi(str.c_str());
  if (0 <= pinVal && pinVal <= P_13)
    return pinVal;
  else if (PXFA0 <= pinVal)
    return (pinVal - PXFA0) + A0;

  return 0;
}
//----------------------------------------------------------------------------
int PXFArduino::PXFPin2Pin(PXFPin pxfPin)
{
  if (P_0 <= pxfPin && pxfPin <= P_13)
    return pxfPin;
  else if (P_A0 <= pxfPin && pxfPin <= P_A6)
    return (pxfPin - P_A0) + A0;

  return 0;
}
//----------------------------------------------------------------------------
PXFPin PXFArduino::_Str2PXFPin(String &str)
{
  int pinVal = atoi(str.c_str());
  if (0 <= pinVal && pinVal <= P_13)
    return P_0 + pinVal;
  else if (PXFA0 <= pinVal)
    return (pinVal - PXFA0) + P_A0;
}
//----------------------------------------------------------------------------
bool PXFArduino::_Str2Bool(String &str)
{
  if (!String("0").compareTo(str))
    return false;

  return true;
}
//----------------------------------------------------------------------------
int PXFArduino::_Str2Int(String &str)
{
  int iVal = atoi(str.c_str());
  return iVal; 
}
//----------------------------------------------------------------------------
int PXFArduino::_Str2DirType(String &str)
{
  return atoi(str.c_str());
}
//----------------------------------------------------------------------------
int PXFArduino::_Str2SimpleDirType(String &str)
{
  return atoi(str.c_str());
}
//----------------------------------------------------------------------------
