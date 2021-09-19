/*

  Example of BH1750 library usage.

  This example initalises the BH1750 object using the default
  high resolution mode and then makes a light level reading every second.

  Connection:
  VCC-5v
  GND-GND
  SCL-SCL(analog pin 5)
  SDA-SDA(analog pin 4)
  ADD-NC or GND

Ver.30  Add Volume on A7 input
*/

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
int SampleColors[28][3]={36,48,14,35,70,30,42,181,95,49,181,29,46,301,71,37,270,137,74,298,39,67,285,39,57,348,119,86,59,16,109,67,38,49,103,57,90,119,19,92,124,41,73,270,129,77,295,36,146,402,65,165,479,175,406,94,23,408,77,33,396,72,41,419,155,24,424,148,51,391,117,59,477,536,46,464,569,80,469,645,214,44,58,19};

const char *Names[]={"Black","Navy Blue","Blue","Green","Teal","Azure","Electric green","Guppie green","Aqua","Maroon","Patriarch","Violet","Heart gold","Trolley gray","Medium slate blue","Chartreuse","Light green","Aquamarine","Red","Bright pink","Fuchsia","Dark orange","Salmon","Light magenta","Yellow","Pastel yellow","White","Gray2"," ","NO PICKED"};

byte NofSound,SongMode;


#include <Wire.h>
#include <BH1750.h>
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            4
#define BRIGHTNESS 255
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      3
#define NOFMEASUREMENTS 1
#define NUMBEROFONECOLOR 5
#define NUMBERPAUSE 1
#define NUMBEROFSET 0
#define NOLUXLIMIT 10
#define NOSUMMCOLORS 20L  // 1/%
#define VOLUME 24
#define NOFMUSICGO 2
#define NUMBEROFSONGS 122
#define BEGINOFSONG 201


// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 250; // delay for half a second
byte j;
#define LEDDELAYTIME 300
#define INTERCOLORTIME 50

int RedRGB,GreenRGB,BlueRGB;
BH1750 lightMeter;
void _test(void);

int luxWhite;
int luxRed;
int luxGreen;
int luxBlue;
int noLux;

float redNorm;
float greenNorm;
float blueNorm;

byte ComWr = 0;
byte ColorNumber,jColor;
byte ColorCode;
byte Mode=0;
byte Go2MusicCounter;
int NOfSong2Play;
int t_int;
 long t_Diff;
byte Volume = VOLUME;
void PlayText(byte NofSound);

void PlayMusic(unsigned int NofSound);
void SetVolume(byte Volume);

byte text[]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,
50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,
100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,121,122,123,124,125,126,127,128,129,130,131,132,133,134,135,136,137,138,139,140,141,142,143,144,145,146,147,148,149,
150,151,152,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,171,172,173,174,175,176,177,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,194,195,196,197,198,199
};

void setup() {
pinMode(8,INPUT_PULLUP);
pinMode(9,INPUT_PULLUP);
pinMode(10,INPUT_PULLUP);
pinMode(11,INPUT_PULLUP);
pinMode(13, OUTPUT);
pinMode(A7, INPUT);

  EICRA = 0x00; //  INT0 INT1 Type didn't matter
  EIMSK = 0x00; //       INT0 INT1 disabled

  PCMSK0 = 0x08;
  PCMSK1 = 0x00; // Pin change mask pins C0 C1 C2 ENABLE any change
  PCMSK2 = 0x00;
  PCIFR = 0x01; //PCINT 0-7 Flag   clear
  PCICR = 0x01; //Pins B interruptions enable
 
  









  
  Serial.begin(9600);
  lightMeter.begin();
  Serial.println("Running.. Gy_302_31 20210905");

  pixels.begin(); // This initializes the NeoPixel library.



  _test();


      delay(100); // delay 1s
 
Serial.write(0x7E);
Serial.write(0xFF);
Serial.write(0x06);
Serial.write(0x0C);
Serial.write(0x00);
Serial.write(0x00);
Serial.write(0x00);
Serial.write(0xFE);
Serial.write(0xEF);
Serial.write(0xEF);

 
delay (100);
 
 
delayMicroseconds(10);
Serial.write(0x7E);
Serial.write(0xFF);
Serial.write(0x06);
Serial.write(0x06);
Serial.write(0x01);
Serial.write(0x00);
Serial.write(VOLUME);
Serial.write(0xFE);
Serial.write(0xF4-VOLUME);

Serial.write(0xEF);

randomSeed(analogRead(0));

}


void loop() {

if(analogRead(A7)/32 +1 != Volume)
{
  Volume=analogRead(A7)/32 +1;
SetVolume(byte ( Volume));

}



  

 if (Mode == 4)
  {

Serial.println("in 4ht mode");
    
 if(digitalRead(9)== HIGH)
// PlayMusic(260);//240+t_int++);
PlayMusic( int( random(  BEGINOFSONG, NUMBEROFSONGS +   BEGINOFSONG    )  ));

 //delay(3000);

    
  }


  
 if(Mode==3)
 Mode=1;
 

  for (int i = 0; i < NUMPIXELS; i++)
    pixels.setPixelColor(i, pixels.Color(BRIGHTNESS, BRIGHTNESS, BRIGHTNESS)); // White
  pixels.show();

  delay(LEDDELAYTIME);

for(byte itt=0;itt<NOFMEASUREMENTS;itt++)
{
  luxWhite = lightMeter.readLightLevel();
  delay(INTERCOLORTIME);
 

  
 
 
}
 
  for (int i = 0; i < NUMPIXELS; i++)
   // pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.setPixelColor(i, pixels.Color(BRIGHTNESS, 0, 0)); // Red
   pixels.show();
  
  delay(LEDDELAYTIME);

for(byte itt=0;itt<NOFMEASUREMENTS;itt++)
{
  luxRed = lightMeter.readLightLevel();
RedRGB = int((float(luxRed)+17.445)*0.7437);
  delay(INTERCOLORTIME);

 
}

  for (int i = 0; i < NUMPIXELS; i++)
  //     pixels.setPixelColor(i, pixels.Color(0, 0, 0));
   pixels.setPixelColor(i, pixels.Color(0, BRIGHTNESS, 0)); // Green
   pixels.show();
 
  delay(LEDDELAYTIME);

  for(byte itt=0;itt<NOFMEASUREMENTS;itt++)
{
  luxGreen = lightMeter.readLightLevel();
  delay(INTERCOLORTIME);
 
   
}
  for (int i = 0; i < NUMPIXELS; i++)
  //    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    pixels.setPixelColor(i, pixels.Color(0, 0, BRIGHTNESS)); // Blue
  pixels.show();
  delay(LEDDELAYTIME);

for(byte itt=0;itt<NOFMEASUREMENTS;itt++)
{
  luxBlue = lightMeter.readLightLevel();
  delay(INTERCOLORTIME);

   
}
  for (int i = 0; i < NUMPIXELS; i++)

        pixels.setPixelColor(i, pixels.Color(0, 0, 0));
//    pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Nothing
   pixels.show();
  delay(LEDDELAYTIME);
  for(byte itt=0;itt<NOFMEASUREMENTS;itt++)
{
  noLux = lightMeter.readLightLevel();
  delay(INTERCOLORTIME);


 
}
    // Calc color here

    if(( noLux<NOLUXLIMIT)&&  (( NOSUMMCOLORS*sqrt( (long(luxWhite)-luxBlue-luxGreen-luxRed   )*    (long(luxWhite)-luxBlue-luxGreen-luxRed   )       )    )/luxWhite)<1                  )
    {
     t_Diff=10000;
    ColorCode=29;
    for(  byte jt=0;jt<28;jt++)
    {
  //   Serial.println("\t");
  //Serial.print( (long(luxRed-   SampleColors[jt][0])* long(luxRed-   SampleColors[jt][0])   + long(luxGreen-   SampleColors[jt][1])* long(luxGreen-   SampleColors[jt][1]) + long(luxBlue-   SampleColors[jt][2])* long(luxBlue-   SampleColors[jt][2]) ));
  if(  ( sqrt(long(luxRed-   SampleColors[jt][0])* long(luxRed-   SampleColors[jt][0])   + long(luxGreen-   SampleColors[jt][1])* long(luxGreen-   SampleColors[jt][1]) + long(luxBlue-   SampleColors[jt][2])* long(luxBlue-   SampleColors[jt][2]) ) )< t_Diff       )

  {
 t_Diff = sqrt(long(luxRed-   SampleColors[jt][0])* long(luxRed-   SampleColors[jt][0])   + long(luxGreen-   SampleColors[jt][1])* long(luxGreen-   SampleColors[jt][1]) + long(luxBlue-   SampleColors[jt][2])* long(luxBlue-   SampleColors[jt][2]) );
ColorCode=jt;
 

  }   
    }
  
    }
    else
    ColorCode=29;
Serial.begin(9600);
 if (ComWr)
    Serial.print("\tLight:white \t");
  //Serial.print("\t");
  Serial.print(luxWhite);
 
  if (ComWr)
    Serial.print("Light:red");
  Serial.print("\t");
  Serial.print(luxRed);
 if (ComWr)
    Serial.print("Light:green ");
  Serial.print("\t");
  Serial.print(luxGreen);
  if (ComWr)
    Serial.print("Light:blue ");
  Serial.print("\t");
  Serial.print(luxBlue);
     if (ComWr)
    Serial.print("Light:nothing ");
  Serial.print("\t");
  Serial.print(noLux);
    Serial.print("\t");
  Serial.print(t_Diff);
   Serial.print("\t");
  Serial.print(ColorCode);
  
     Serial.print("\t");
  Serial.print(Names[ColorCode]);
  Serial.println("");
Serial.end();

if (Mode == 1)
{
  if(digitalRead(10)== HIGH)
PlayText(ColorCode);
else
PlayText(ColorCode+50);
delay(100);
while(digitalRead(9)==LOW)
{
;
}
 delay(200);
 if(digitalRead(8)== HIGH)
 {
if(digitalRead(10)== HIGH)
PlayText(ColorCode+100);
else
PlayText(ColorCode+150);
 }
 Mode=0;

if(ColorCode==29)
{
  Serial.print(" 29  ");
  Serial.println(Go2MusicCounter);
if( Go2MusicCounter++>NOFMUSICGO)
{
  Mode=4;
// Go2MusicCounter=0;
  Serial.print(" Mode =4  ");
  
}
else
Mode=0;

}
else
Go2MusicCounter=0;
 
  
}




}


void _test(void)
{
  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(255, 0 , 0)); // Moderately bright green color.
    if (i > 0)
      pixels.setPixelColor(i - 1, pixels.Color(5, 0 , 0)); // Moderately bright green color.


    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }

  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 0 , 255)); // Moderately bright green color.
    if (i > 0)
      pixels.setPixelColor(i - 1, pixels.Color(0, 0 , 5)); // Moderately bright green color.


    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0, 255 , 0)); // Moderately bright green color.
    if (i > 0)
      pixels.setPixelColor(i - 1, pixels.Color(0, 5 , 0)); // Moderately bright green color.


    pixels.show(); // This sends the updated pixel color to the hardware.

    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  for (int i = 0; i < NUMPIXELS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255

    pixels.setPixelColor(i, pixels.Color(5, 5 , 5)); // Moderately bright green color.




    delay(delayval); // Delay for a period of time (in milliseconds).

  }
  pixels.show(); // This sends the updated pixel color to the hardware.

}


void PlayText(byte NofSound)
{
 
  delay(1);
  
Serial.begin(9600);
Serial.write( 0x7E);
Serial.write( 0xFF);
Serial.write( 0x06);
Serial.write( 0x03);
Serial.write( 0x00);
Serial.write( 0x00);
Serial.write( NofSound+1);
Serial.write( 0xFE );
Serial.write(  byte(0xF8-NofSound-1));
Serial.write( 0xEF);
Serial.println("");
Serial.print("NofS= ");
Serial.println(NofSound);

delay(12);
 
 Serial.end();
 
} 



void PlayMusic(int NOfSong2Play)
{






  
 // digitalWrite(10, LOW);
  delay(1);
 

 // NOfSong2Play=256;
  
Serial.begin(9600);
delay(100);
Serial.write( 0x7E);
Serial.write( 0xFF);
Serial.write( 0x06);
Serial.write( 0x03);
Serial.write( 0x00);
Serial.write( byte( NOfSong2Play/256));
Serial.write( byte ( NOfSong2Play));
if(NOfSong2Play<0x100)
{
Serial.write( 0xFE   -byte( (NOfSong2Play+7)/256));
Serial.write(  byte(0xF8-NOfSong2Play));
  
}

else
{
Serial.write( 0xFF   -byte( (NOfSong2Play+7)/256));
Serial.write(  byte(0xF7-NOfSong2Play));

}
Serial.write( 0xEF );

//Serial.println("");
//Serial.println( byte( (NOfSong2Play+7)/256) , HEX);
//249 250



//Serial.begin(9600);
//Serial.write( 0x7E);
//Serial.write( 0xFF);
//Serial.write( 0x06);
//Serial.write( 0x03);
//Serial.write( 0x00);
//Serial.write( 0x01);
//Serial.write( 0x01);
//Serial.write( 0xFD );
//Serial.write(  0xF7 );
//Serial.write( 0xEF);




Serial.println("");
Serial.print("NofS= ");

Serial.print(NOfSong2Play);

Serial.print("SongMode=00 ");

Serial.println(SongMode);





delay(12);
//return;
 Serial.end();

delay(100);


 

} 

ISR (PCINT0_vect)// pin change interrupt for A0 to A5
{
  
  if((Mode==0)  || (Mode ==4))
Mode=3;
 
}


void SetVolume(byte Volume)
{
  delay(1);
 

  
  
Serial.begin(9600);
delay(100);
delayMicroseconds(10);
Serial.write(0x7E);
Serial.write(0xFF);
Serial.write(0x06);
Serial.write(0x06);
Serial.write(0x01);
Serial.write(0x00);
Serial.write(Volume);
Serial.write(0xFE);
Serial.write(0xF4-Volume);

Serial.write(0xEF);
delay(12);
//return;

Serial.println("");
Serial.print("Volume set=");
Serial.println(Volume );
 Serial.end();

delay(100);

  
}
