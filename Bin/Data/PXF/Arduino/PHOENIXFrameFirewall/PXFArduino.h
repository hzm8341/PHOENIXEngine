// PXFArduino.h

#ifndef PXFARDUINO_H
#define PXFARDUINO_H

#include <Arduino.h>
#include "PXFTimer.h"

// server
#define PXF_SERVER 1
#if defined PXF_SERVER
#include <Servo.h>
#endif

// display
//#define PXF_SSD1306 1
#if defined PXF_SSD1306
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "PXFAdafruit_SSD1306.h"
#endif

//#define PXF_MP3 1
#if defined PXF_MP3
#include "PXFDFPlayer_Mini_Mp3.h"
#include <SoftwareSerial.h>
#endif

//#define PXF_IR 1
#if defined PXF_IR
#include "PXFIRremote.h"
#endif

//#define PXF_XH711 1
#if defined PXF_XH711
#include "PXFHX711.h"
#endif

//#define PX2_POLOLUBUZZER 1
#if defined PX2_POLOLUBUZZER
#include "PXFPololuBuzzer.h"
#endif

//#define PXF_AXIS 1
#if defined PXF_AXIS
#include <Wire.h>
#include "PXMPU6050.h"
#endif

#define PXF_PID
#if defined PXF_PID
#include "PXFPID_v1.h"
#endif

enum PXFPin
{
    P_0 = 0,
    P_1,
    P_2,
    P_3,
    P_4,
    P_5,
    P_6,
    P_7,
    P_8,
    P_9,
    P_10,
    P_11,
    P_12,
    P_13,
    P_A0,
    P_A1,
    P_A2,
    P_A3,
    P_A4,
    P_A5,
    P_A6,
    P_MAX_TYPE
};
#define PXFA0 30

enum PXFPMode
{
    PM_INPUT = 0,
    PM_OUTPUT,
    PM_MAX_TYPE
};

#define NumMaxCMDs 10
#define GeneralServerMsgID 2

enum PXFMotoType
{
  MT_0,
  MT_1,
  MT_MAX_TYPE,
};

enum PXFDirectionType
{
  DT_NONE,
  DT_FORWORD,
  DT_BACKWORD,
  DT_MAX_TYPE
};

enum PXFSimpleDirectionType
{
  SDT_NONE,
  SDT_FORWORD,
  SDT_BACKWORD,
  SDT_LEFT,
  SDT_RIGHT,
  SDT_MAX_TYPE
};

enum OptionType
{
  OT_TOGET_NETID,
  OT_RETURN_NETID,
  OT_PM,
  OT_DW,
  OT_AW,
  OT_RETURN_DR,
  OT_RETURN_AR,
  OT_SVR_I,
  OT_SVR_W,
  OT_DST_I,
  OT_DST_T,
  OT_RETURN_DIST,
  OT_MOTO_I,
  OT_MOTO_RUN,
  OT_MOTO_RUNSIMPLE,
  OT_MOTO_STOP,
  OT_MOTO_I_SPD,
  OT_RETURN_MOTOSPD,
  OT_MOTO_I_DRIVER4567,
  OT_MOTO_I_DRIVER298N,
  OT_MP3_INIT,
  OT_MP3_PLAY,
  OT_MP3_INDEX,
  OT_MP3_NEXT,
  OT_MP3_STOP,
  OT_MP3_VOLUME,
  OT_IR_INIT,
  OT_IR_SEND,
  OT_RETURN_IR,
  OT_HX711_I,
  OT_HX711_TEST,
  OT_RETURN_HX711,
  OT_DSTMAT_I,
	OT_RETURN_DSTMAT,
  OT_AXIS_I,
  OT_RETURN_AXIS,
  OT_SET_TIME,
  OT_MC_INTERNAL_LIGHT, // makerclock
  OT_MC_LIGHT,
  OT_MC_SEGMENT,
  OT_MC_MOTO,
  OT_MC_DISTTEST,
  OT_MB_MOTO,	// mbot
  OT_MB_SEND,
  OT_MB_BUZZER,
  OT_MAX_TYPE
};

class PXFArduino
{
public:
  PXFArduino();

  static PXFArduino *pxfarduino;

  static char PinStr[P_MAX_TYPE];
  static char sOptTypeVal[OT_MAX_TYPE];

  // cmds process
  void OnCMDGroup(String &cmdStr);
  void OnCMD(String &cmdStr);

  // to get pin values by timer
  void CalPinVals();

  void _PinMode(PXFPin pin, PXFPMode mode);
  void _DigitalWrite(PXFPin pin, bool isHigh);
  int _DigitalRead(PXFPin pin);
  void _PwmWrite(PXFPin pin, int val);
  void _AnalogWrite(PXFPin pin, int val);
  int _AnalogRead(PXFPin pin);
  void _ServerInit(int index, PXFPin pin);
  void _ServerWrite(int index, int val);
  void _DistInit(PXFPin trigger, PXFPin echo);
  float _GetDist();
  void _VehicleSpeedEncorderInit(PXFPin encorderLA, PXFPin encorderLB, PXFPin encorderRA, PXFPin encorderRB);
  void _VehicleRun(int index, PXFDirectionType dir, int speed);
  void _VehicleSimpleRun(PXFSimpleDirectionType dir, int speed);
  float _VehicleGetSpeed(int index);
  void _VehicleStop();
  void _WeightInit(int index, PXFPin pinR, PXFPin pinT);
  void _WeightTest(int index);
  float _GetWeight(int index);
  void _MP3Init(PXFPin pinR, PXFPin pinT);
  void _IRInit(PXFPin pinR);

  PXFPMode PinModes[P_MAX_TYPE];

private:
  String I2Str(int val);
  int _Str2IO(String &str);
  int _Str2Pin(String &str);
  PXFPin _Str2PXFPin(String &str);
  int PXFPin2Pin(PXFPin pxfPin);
  bool _Str2Bool(String &str);
  int _Str2Int(String &str);
  int _Str2DirType(String &str);
  int _Str2SimpleDirType(String &str);

  char *mpCMD;

#define NumCMDParams 7
  String mCmdParams[NumCMDParams];
  int mCMDIndexTemp;
  char *mpCMDParam;

public:
  void Init(bool isReset=false);
  void Reset();
  void Tick();

public:
  void _SendNetID();
  void _DistInit_(int pinTrig, int pinEcho);
  void _DistTest();
  enum MotoMode
  {
    MM_BOARD,
    MM_298N,
    MM_MAX_TYPE
  };
  void _MotoInit4567();
  void _MotoInit10111213();
  void _MotoInit298N(int pinL, int pinL1, int pinLS, int pinR, int pinR1, int pinRS);
  void _MotoSpeedInit(int encorderLA, int encorderLB, int encorderRA, int encorderRB);
  void _LeftRun(int val, int spd);
  void _RightRun(int val, int spd);
#if defined PXF_SSD1306
  void _ScreenInit();
#endif
  void _MP3Init_(int pinR, int pinT);
  void _MP3Play();
  void _MP3PlayStop();
  void _MP3SetVolume(int volume);
  void _MP3PlayIndex(int index);
  void _MP3Next();
  void _IRInit_(int pinR);
  void _IRSend(int val);
  void _IRRecv(int val);
  void _Delay(float seconds);
  void _Loop();
  void _SendCMD(String &cmdStr);
  void _HX711Init(int index, int pinOut, int pinClk);
  float _ReadHX711(int index);
  void _HXSend(int index, float val);
  void _SetTime();

public:
  int mPinEncroderLA;
  int mPinEncroderLB;
  int mPinEncroderRA;
  int mPinEncroderRB;
  double mSetPoint_L;
  double mSetPoint_R;

#if defined PXF_PID
  PID *mPID;
  PID *mPID1;
  byte mEncoder0PinALastL;
  byte mEncoder0PinALastR;
  double mDurationL;
  double mDurationR;
  double mAbsDurationL;
  double mAbsDurationR;
  double mValOutputL;
  double mValOutputR;
  bool mDirectionL;
  bool mDirectionR;
  bool mIsStopL;
  bool mIsStopR;
#endif

  unsigned long mSettedTimeMe;

private:
  int mNetID;
  Timer mTimer;

#if defined PXF_SERVER
  #define NumMaxServer 5
  Servo mServo[NumMaxServer];
#endif

  int mPinDistTrigger;
  int mPinDistEcho;
  float mDist;
  int mDistCheckLastTime;

  int mPinL0;
  int mPinL1;
  int mPinLSpeed;
  int mPinR0;
  int mPinR1;
  int mPinRSpeed;

  bool mIsUseSpeedEncorder;

  MotoMode mMotoMode;

#if defined PXF_SSD1306
  Adafruit_SSD1306 *mDisplay;
#endif

#if defined PXF_MP3
  SoftwareSerial *mMP3Serial;
#endif

#if defined PXF_IR
  IRrecv *mIRrecv;
  IRsend mIRsend;
#endif

#if defined PXF_XH711
  HX711 mXH711_0;
  HX711 mXH711_1;
  HX711 mXH711_2;
  HX711 mXH711_3;
#endif

public:
  void _InitAxis();

#if defined PXF_AXIS
  unsigned long mAxisLastTick;
  float mPitch;
  float mRoll;
  float mYaw;
  MPU6050 mMPU;
  int mAxisTickEvent;
#endif
};

#endif
