#include <MIDI.h>
#include <Adafruit_BMP085.h>
MIDI_CREATE_DEFAULT_INSTANCE();

unsigned long t1,t2;
bool b11, b12, b13, b14,b21,b22,b23,b24;
bool s11, s12, s13, s14,s21,s22,s23,s24,s112,s212,s221;
int botonera;
long mordida;
int mordidamax;
int mordidabase;
byte prevMordida;
byte transpose;
byte ntranspose;
bool notas[12];
bool notasOn[127];
byte canal;
long prevPitch;
long pitch;
long presionbase;
long presionmax;
long presion;
int umbral=10;
bool sonando;
byte programa;
bool rueda;

Adafruit_BMP085 bmp;

void setup()
{
  // put your setup code here, to run once:


 if (!bmp.begin()) {
  Serial.println("No se puede iniciar el sensor de presión");
  while (1) {}
  }
 MIDI.begin(1);

  mordidamax=500;
  mordidabase=325;
  presionmax=97360;

  presionbase=bmp.readPressure();
  presionmax=presionmax-presionbase;
  t1=0;
  for (byte a=2; a<=13;a++)
  {
  pinMode(a,INPUT_PULLUP);
  }
  canal=1;
  sonando=0;
  transpose=5;
  ntranspose=11;
}
void loop()
{
//almacena las notas que están pulsadas.

for (int a=0; a<12;a++)
{
  notas[a]=!digitalRead(a+2);
}
//Comprueba el estado de la botonera 1
botonera=analogRead(1);
 
if (botonera<=368)
{
  b11=true;
  b12=true;
  b13=true;
  b14=true;
}
else if (botonera<=514)
{
b11=true;
  if (botonera<=411)
  {
  b12=true;
    if (botonera<=381)
    {
    b13=true;
    }
    else if (botonera<=395)
    {
    b14=true;
        b13=false;
    }
        else
        {
        b13=false;
      b14=false;
        }
  }
  else if (botonera<=468)
  {
  b13=true;
    b12=false;
    if (botonera<=448)
    {
    b14=true;
    }
        else
        {
        b14=false; 
        }
  }
  else if (botonera<=489)
  {
  b14=true; 
    b12=false;
    b13=false;
  }
    else
    { 
    b12=false;
    b13=false;
    b14=false;
    }
}
else if (botonera<=684)
{
  b12=true;
    b11=false;
  if (botonera<=605)
  {
  b13=true;
    if (botonera<=572)
    {
    b14=true;
    }
        else
        {
        b14=false;
        }
  }
  else if (botonera<=641)
  {
  b14=true;
    b13=false;
  }
    else
    {
    b13=false;
    b14=false;
    }
}
else if (botonera<=857)
{
  b13=true;
    b11=false;
    b12=false;
  if (botonera<=791)
  {
  b14=true;
  }
    else
    {
    b14=false;
    }

}
else if (botonera<=932)
{
  b14=true;
    b11=false;
    b12=false;
    b13=false;
  
}
else
{
    b11=false;
    b12=false;
    b13=false;
    b14=false;
}

//Comprueaba el estado de la botonera 2
botonera=analogRead(2);

if (botonera<=368)
{
  b21=true;
  b22=true;
  b23=true;
  b24=true;
}
else if (botonera<=514)
{
b21=true;
  if (botonera<=411)
  {
  b22=true;
    if (botonera<=381)
    {
    b23=true;
    }
    else if (botonera<=395)
    {
    b24=true;
        b23=false;
    }
        else
        {
        b23=false;
      b24=false;
        }
  }
  else if (botonera<=468)
  {
  b23=true;
    b22=false;
    if (botonera<=448)
    {
    b24=true;
    }
        else
        {
        b24=false; 
        }
  }
  else if (botonera<=491)
  {
  b24=true; 
    b22=false;
    b23=false;
  }
    else
    { 
    b22=false;
    b23=false;
    b24=false;
    }
}
else if (botonera<=684)
{
  b22=true;
    b21=false;
  if (botonera<=605)
  {
  b23=true;
    if (botonera<=572)
    {
    b24=true;
    }
        else
        {
        b24=false;
        }
  }
  else if (botonera<=641)
  {
  b24=true;
    b23=false;
  }
    else
    {
    b23=false;
    b24=false;
    }
}
else if (botonera<=857)
{
  b23=true;
    b21=false;
    b22=false;
  if (botonera<=791)
  {
  b24=true;
  }
    else
    {
    b24=false;
    }

}
else if (botonera<=932)
{
  b24=true;
    b21=false;
    b22=false;
    b23=false;
  
}
else
{
    b21=false;
    b22=false;
    b23=false;
    b24=false;
}

//calcula y envía el pitch bend y la modulacion en funcion del modo de rueda


  pitch=analogRead(0)-525;
  if (pitch<-512)
  {
  pitch=-512;
  }
  if (pitch>0)
  {
  pitch=(pitch*512)/498;
  }
  pitch=16*pitch;
  if (pitch>8191)
  {
  pitch=8191; 
  }
  
 if (abs(pitch-prevPitch)>16)
 {
  prevPitch=pitch;
    if ((b24==0 && rueda==0) || (rueda==1 && (b23==1 || b24==1)))
    {
   MIDI.sendPitchBend(int(pitch),canal);
    }
    if ((rueda==0 && (b24==1 || b23==1)) || (b23==0 && rueda==1) )
    {
   MIDI.sendControlChange(1,abs(pitch/64),canal);
    }
 }
  
 
// Calcula y envía los datos de mordida

mordida=analogRead(3)-mordidabase;
if (mordida<0)
{
  mordida=0;
}
mordida=(mordida*127)/(mordidamax-mordidabase);
if (mordida>127)
{
    mordida=127;
}

if (abs(mordida-prevMordida)>5)
{

  prevMordida=mordida;
 MIDI.sendControlChange(73,mordida,canal);
 MIDI.sendControlChange(1,mordida/2,canal);

}

//Controlar transposición de octavas y notas 
if (b11==1)
{

    if (b14==1 && s14==0 && s112==0)
    {
      s14=1;
      if (transpose<10)
      {
      transpose++;
      }
    }
    if (b13==1 && s13==0 && s112==0)
    {
      s13=1;
      if (transpose>0)
      {
      transpose--;
      }
    }
    if (b24==1 && s24==0 && s112==0)
    {
      s24=1;
      if (ntranspose<22)
      {
      ntranspose++;
      }
      else
      {
              if (transpose<10)
              {
              ntranspose=11;
              transpose++;
              }
      }

      
    }
    if (b23==1 && s23==0 && s112==0)
    {
      s23=1;
      if (ntranspose>0)
      {
      ntranspose--;
      }
      else
      {
              if (transpose>0)
               {
               ntranspose=11;
               transpose--;
               }
      }     
    }
    if (b12==0)
    {
    s11=1;
    }
  if (b12==1 && s11==1 && s12==0)
  {
    s112=1;   
  }
  if (s112==1 && b14==1 && s14==0)
  {
     programa=programa+10;
     if (programa>127)
     {
      programa=127;
     }
      MIDI.sendProgramChange(programa,canal);
    s14=1;
  }
  if (s112==1 && b13==1 && s13==0)
  {
     if (programa>10)
     {
      programa-=10;
     }
     else
     {
      programa=0;
     }
      MIDI.sendProgramChange(programa,canal);
    s13=1;    
  }
  if (s112==1 && b24==1 && s24==0)
  {

     programa++;
         Serial.println(programa);
     if (programa>127)
     {
      programa=127;
     }
      MIDI.sendProgramChange(programa,canal);
    s24=1;
  }
 if (s112==1 && b23==1 && s23==0)
  {
     if (programa>0)
     {
      programa--;
     }
      MIDI.sendProgramChange(programa,canal);
    s23=1;    
  }
   if (s112==1 && b22==1 && s22==0)
  {
     if (canal<16)
     {
       for (byte a=0; a<12;a++)
        {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
        }
      canal++;
     }
  
    s22=1;    
  }
     if (s112==1 && b21==1 && s21==0)
  {
     if (canal>1)
     {
       for (byte a=0; a<12;a++)
        {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
        }
      canal--;
     }
  
    s21=1;    
  }
  

}
else
{
    if (b14==1 && s14==0)
    {
      if (transpose<10)
      {
        for (byte a=0; a<12;a++)
        {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
        }
        transpose++;
      }
      s14=1;
    }
    if (b14==0 && s14==1)
    {

      if (transpose>0)
      {
        for (byte a=0; a<12;a++)
        {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
        }
        transpose--;
      }

    }
    if (b13==1 && s13==0)
    {
      if (transpose>0)
      {
        for (byte a=0; a<12;a++)
        {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
        }
        transpose--;
      }
      s13=1;
    }
        if (b13==0 && s13==1)
    {
      
      if (transpose<10)
      {
        for (byte a=0; a<12;a++)
         {
        notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
      MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
         }
        transpose++;
      }
    }

}

if (b21==1 && s21==0 && s22==0)
{
    s21=1;

}
if (b22==1 && s21==1 && s22==0)
{
  s22=1;
  s212=1;
   presionbase=bmp.readPressure();
}

if (b22==1 && s22==0 && s21==0)
{
    s22=1;
    
}
if (b21==1 && s22==1 && s21==0)
{
  s21=1;
  s221=1;
  mordidabase=analogRead(3);
}

if (s212==1)
{
 presionmax=bmp.readPressure()-presionbase;
}

if (s221==1)
{
  mordidamax=analogRead(3);
}

if (b12==1 && s12==0 && s112==0)
{
  rueda=!rueda;
  s12=1;
}

if (b11==0)
{
  s11=0;
  s112=0;
}
if (b12==0 && s112==0)
{
  s12=0;
  s112=0;
}
if (b13==0)
{
  s13=0;
}
if (b14==0)
{
  s14=0;
}
if (b23==0)
{
  s23=0;
}
if (b24==0)
{
  s24=0;
}
if (b21==0)
{
  s21=0;
  s212=0;
  s221=0;
}
if (b22==0)
{
  s22=0;
  s212=0;
  s221=0;
}

presion=bmp.readPressure()-presionbase;
presion=(presion*127)/presionmax;
if (presion<0)
{
  presion=0;
}
if (presion>127)
{
  presion=127;
}


//lee el sensor de presión y envía las notas
if ((presion>=umbral))
{ 
  sonando=1;
  for (int a=0; a<12; a++)
  {
    if (notasOn[((transpose*12)+(ntranspose-11)+a)]==0 && notas[a]==1)
   { 
   MIDI.sendNoteOn(((transpose*12)+(ntranspose-11)+a),127,canal);

    notasOn[((transpose*12)+(ntranspose-11)+a)]=1;
   }
 //  MIDI.sendControlChange(64,127,canal); 
   MIDI.sendControlChange(7,presion,canal);
  }
}
else if (presion<umbral && sonando==1)
{
    MIDI.sendControlChange(64,0,canal); 
  for (int a=0; a<12; a++)
  {

    if (notasOn[((transpose*12)+(ntranspose-11)+a)])
    {
    MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
    
    notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
    }
  }
 sonando=0;
}

for (byte a=0; a<12; a++)
{
  
if (notas[a]==0 && notasOn[((transpose*12)+(ntranspose-11)+a)]==1)
  {
    notasOn[((transpose*12)+(ntranspose-11)+a)]=0;
   MIDI.sendNoteOff(((transpose*12)+(ntranspose-11)+a),0,canal);
  }
}
}
