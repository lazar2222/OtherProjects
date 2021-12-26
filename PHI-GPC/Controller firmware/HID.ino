#include <LiquidCrystal.h>
#include "define.h"
#include "lib.h"
#include "GHP.h"
#include "Persistence.h"

void SnLInit();
void PinModeInit();
void MuxA();
void MatrixB(byte mux);
void MuxB();
void MatrixD(byte mux);
void Enc();
void ENC0ISR();
void Joy();
void Pedal();
void LcdUpdate();
void CheckReset();

void setup() 
{
  SnLInit();
  PinModeInit();
  RefreshPersistence();
}

void loop() 
{
  ReadSerial();
  MuxA();
  MuxB();
  Enc();
  Joy();
  if(KRAFTWERK)
  {
    Pedal();
  }
  LcdUpdate();
  CheckReset();
}

void SnLInit()
{
  Serial.begin(115200);
  Lcd.begin(20,4);
  Lcd.clear();
}

void PinModeInit()
{
  DoPinMode(MUXE,3,OUTPUT);
  DoPinMode(MUXQ,2,OUTPUT);
  DoPinMode(MUXAR,2,INPUT);
  DoPinMode(MUXDR,2,INPUT);
  DoPinMode(MUXDW,3,OUTPUT);
  for(byte i=0;i<5;i++)
  {
    DoPinMode(ENC[i],2,INPUT_PULLUP);
  }
  attachInterrupt(digitalPinToInterrupt(ENC[0][0]), ENC0ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC[1][0]), ENC1ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC[2][0]), ENC2ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC[3][0]), ENC3ISR, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC[4][0]), ENC4ISR, RISING);
  DoPinMode(MATRIXB,4,OUTPUT);
  DoPinMode(MATRIXD,4,OUTPUT);
  pinMode(JOYX,INPUT);
  pinMode(JOYY,INPUT);
  pinMode(JOYS,INPUT_PULLUP);
  pinMode(PEDALA,INPUT);
  pinMode(PEDALO,INPUT_PULLUP);
  pinMode(PEDALT,INPUT_PULLUP);
}

void MuxA()
{
  for(byte i=0;i<8;i++)
  {
    SetMux(MUXE,3,i);

    short val = analogRead(MUXAR[0]);
    short avg;
    if(AnalogAlias[i]==8 || AnalogAlias[i]==11)
    { 
      avg = (val+AnalogAvg[i])/2;
      AnalogAvg[i]=val;
      if(abs(avg-AnalogPre[i])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[i],constrain(map(logToLin(avg),0,1005,0,1023),0,1023),true);AnalogPre[i]=avg;}
    }
    else
    {
      val = constrain(map(val,0,1005,0,1023),0,1023);
      avg = (val+AnalogAvg[i])/2;
      AnalogAvg[i]=val;
      if(abs(avg-AnalogPre[i])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[i],avg,true);AnalogPre[i]=avg;}
    }

    val = analogRead(MUXAR[1]);
    if(AnalogAlias[i+8]==8 || AnalogAlias[i+8]==11)
    {
      avg = (val+AnalogAvg[i+8])/2;
      AnalogAvg[i+8]=val;
      if(abs(avg-AnalogPre[i+8])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[i+8],constrain(map(logToLin(avg),0,1005,0,1023),0,1023),true);AnalogPre[i+8]=avg;}
    }else
    {
      val = constrain(map(val,0,1005,0,1023),0,1023);
      avg = (val+AnalogAvg[i+8])/2;
      AnalogAvg[i+8]=val;
      if(abs(avg-AnalogPre[i+8])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[i+8],avg,true);AnalogPre[i+8]=avg;}
    }

    MatrixB(i);
  }
}

void MatrixB(byte mux)
{
    for(byte i=0;i<4;i++)
    {
      SetMatrix(MATRIXB,4,i);

      byte ind=i*8+mux;
      byte val=digitalRead(MUXDR[0]);
      if(val==HIGH && ButtonDebounce[ind]<DEBOUNCE)
      {
        ButtonDebounce[ind]++;
        if(ButtonDebounce[ind]==DEBOUNCE && ButtonBool[ind]==false){SendMessage(BUTTON_PRESS,ButtonAlias[ind]);ButtonBool[ind]=true;}
      }
      else if(val==LOW && ButtonDebounce[ind]>0)
      {
        ButtonDebounce[ind]--;
        if(ButtonDebounce[ind]==0 && ButtonBool[ind]==true){SendMessage(BUTTON_RELEASE,ButtonAlias[ind]);ButtonBool[ind]=false;}
      }

      ind += 32;
      val=digitalRead(MUXDR[1]);
      if(val==HIGH && ButtonDebounce[ind]<DEBOUNCE)
      {
        ButtonDebounce[ind]++;
        if(ButtonDebounce[ind]==DEBOUNCE && ButtonBool[ind]==false){SendMessage(BUTTON_PRESS,ButtonAlias[ind]);ButtonBool[ind]=true;}
      }
      else if(val==LOW && ButtonDebounce[ind]>0)
      {
        ButtonDebounce[ind]--;
        if(ButtonDebounce[ind]==0 && ButtonBool[ind]==true){SendMessage(BUTTON_RELEASE,ButtonAlias[ind]);ButtonBool[ind]=false;}
      }
    }
}

void MuxB()
{
  for(byte i=0;i<4;i++)
  {
    SetMux(MUXQ,2,i);

    MatrixD(i);
  }
}

void MatrixD(byte mux)
{
    for(byte i=0;i<4;i++)
    {
      SetMatrix(MATRIXD,4,i,true);

      analogWrite(MUXDW[0],LedValue[i*4+mux][0]);
      analogWrite(MUXDW[1],LedValue[i*4+mux][1]);
      analogWrite(MUXDW[2],LedValue[i*4+mux][2]);

      delay(1);
    }
}

void Enc()
{
  for(byte i=0;i<5;i++)
  {
    ENCPre[i]=constrain(ENCPre[i],-((short)ENCMS),(short)ENCMS);
    while(ENCPre[i]!=0)
    {
      if(ENCPre[i]>0){if(ENClast[i]==true){SendMessage(ENCODER_INCREMENT,i);}ENCPre[i]--;ENClast[i]=true;}
      else{if(ENClast[i]==false){SendMessage(ENCODER_DECREMENT,i);}ENCPre[i]++;ENClast[i]=false;}
    }
  }
}

void ENC0ISR()
{
  if(digitalRead(ENC[0][0])==HIGH)
  {
    if(digitalRead(ENC[0][1])==LOW)  
      {
        ENCPre[0]++;
      }
      else
      {
        ENCPre[0]--;
      }
  }
}

void ENC1ISR()
{
  if(digitalRead(ENC[1][0])==HIGH)
  {
    if(digitalRead(ENC[1][1])==LOW)  
      {
        ENCPre[1]++;
      }
      else
      {
        ENCPre[1]--;
      }
  }
}

void ENC2ISR()
{
  if(digitalRead(ENC[2][0])==HIGH)
  {
    if(digitalRead(ENC[2][1])==LOW)
      {
        ENCPre[2]++;
      }
      else
      {
        ENCPre[2]--;
      }
  }
}

void ENC3ISR()
{
  if(digitalRead(ENC[3][0])==HIGH)
  {
    if(digitalRead(ENC[3][1])==LOW)  
      {
        ENCPre[3]++;
      }
      else
      {
        ENCPre[3]--;
      }
  }
}

void ENC4ISR()
{
  if(digitalRead(ENC[4][0])==HIGH)
  {
    if(digitalRead(ENC[4][1])==LOW)  
      {
        ENCPre[4]++;
      }
      else
      {
        ENCPre[4]--;
      }
  }
}

void Joy()
{
  short val = analogRead(JOYX);
  short avg = (val+AnalogAvg[JOYXI])/2;
  AnalogAvg[JOYXI]=val;
  if(abs(avg-AnalogPre[JOYXI])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[JOYXI],avg,true);AnalogPre[JOYXI]=avg;}

  val = analogRead(JOYY);
  avg = (val+AnalogAvg[JOYYI])/2;
  AnalogAvg[JOYYI]=val;
  if(abs(avg-AnalogPre[JOYYI])>TRESHOLD){SendMessage(ANALOG_CHANGE,AnalogAlias[JOYYI],avg,true);AnalogPre[JOYYI]=avg;}

  val=digitalRead(JOYS);
  if(val==LOW && ButtonDebounce[JOYSI]<DEBOUNCE)
  {
    ButtonDebounce[JOYSI]++;
    if(ButtonDebounce[JOYSI]==DEBOUNCE && ButtonBool[JOYSI]==false){SendMessage(BUTTON_PRESS,ButtonAlias[JOYSI]);ButtonBool[JOYSI]=true;}
  }
  else if(val==HIGH && ButtonDebounce[JOYSI]>0)
  {
    ButtonDebounce[JOYSI]--;
    if(ButtonDebounce[JOYSI]==0 && ButtonBool[JOYSI]==true){SendMessage(BUTTON_RELEASE,ButtonAlias[JOYSI]);ButtonBool[JOYSI]=false;}
  }
}

void Pedal()
{
  short val = analogRead(PEDALA);
  short avg = (val*(((double)ERF)/100))+((1-(((double)ERF)/100))*AnalogAvg[PEDALAI]);
  short maped=constrain(map(avg,10*APLL,10*APUL,0,1023),0,1023);
  if(maped!=AnalogPre[PEDALAI]){SendMessage(ANALOG_CHANGE,AnalogAlias[PEDALAI],maped,true);AnalogPre[PEDALAI]=maped;}
  AnalogAvg[PEDALAI]=avg;

  val=digitalRead(PEDALO);
  if(val==LOW && ButtonDebounce[PEDALOI]<DEBOUNCE)
  {
    ButtonDebounce[PEDALOI]++;
    if(ButtonDebounce[PEDALOI]==DEBOUNCE && ButtonBool[PEDALOI]==false){SendMessage(BUTTON_PRESS,ButtonAlias[PEDALOI]);ButtonBool[PEDALOI]=true;}
  }
  else if(val==HIGH && ButtonDebounce[PEDALOI]>0)
  {
    ButtonDebounce[PEDALOI]--;
    if(ButtonDebounce[PEDALOI]==0 && ButtonBool[PEDALOI]==true){SendMessage(BUTTON_RELEASE,ButtonAlias[PEDALOI]);ButtonBool[PEDALOI]=false;}
  }

  val=digitalRead(PEDALT);
  if(val==LOW && ButtonDebounce[PEDALTI]<DEBOUNCE)
  {
    ButtonDebounce[PEDALTI]++;
    if(ButtonDebounce[PEDALTI]==DEBOUNCE && ButtonBool[PEDALTI]==false){SendMessage(BUTTON_PRESS,ButtonAlias[PEDALTI]);ButtonBool[PEDALTI]=true;}
  }
  else if(val==HIGH && ButtonDebounce[PEDALTI]>0)
  {
    ButtonDebounce[PEDALTI]--;
    if(ButtonDebounce[PEDALTI]==0 && ButtonBool[PEDALTI]==true){SendMessage(BUTTON_RELEASE,ButtonAlias[PEDALTI]);ButtonBool[PEDALTI]=false;}
  }
}

void LcdUpdate()
{
  if(DoUpdateLcd){
    for (byte i = 0; i < 4; i++)
    {
      Lcd.setCursor(0,i);
      Lcd.print(LcdBuff[i]);
    }
    DoUpdateLcd=false;
  }
  
}

void CheckReset()
{
  if(ButtonDebounce[33]==DEBOUNCE && ButtonDebounce[35]==DEBOUNCE && ButtonDebounce[59]==DEBOUNCE){SendMessage(SYSTEM,SYSTEM_RESET);Lcd.clear();Lcd.print("RESET");delay(1000);software_Reset();}
}

short logToLin(double val)
{
  if(val<=330)
  {
    val = val * 0.1848;
  }
  else if(val<=880)
  {
    val = val*0.6527 - 154.391;
  }
  else
  {
    val = val *4.8333 - 3833.3;
  }
  return (short)val;
}