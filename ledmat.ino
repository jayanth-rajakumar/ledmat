#include <Arduino.h>
#include <U8g2lib.h>
#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include <Python.h>

#define MAX_DEVICES 4
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); //start oled

MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

MD_MAX72XX::fontType_t xantofont[] PROGMEM = {
  0,    // 0 - 'Empty Cell'
  //5, 62, 91, 79, 91, 62,    // 1 - 'Sad Smiley'
  //5, 62, 107, 79, 107, 62,    // 2 - 'Happy Smiley'
  //5, 28, 62, 124, 62, 28,   // 3 - 'Heart'
  //5, 24, 60, 126, 60, 24,   // 4 - 'Diamond'
  //5, 28, 87, 125, 87, 28,   // 5 - 'Clubs'
  //5, 28, 94, 127, 94, 28,   // 6 - 'Spades'
  //4, 0, 24, 60, 24,   // 7 - 'Bullet Point'
  //5, 255, 231, 195, 231, 255,   // 8 - 'Rev Bullet Point'
  //4, 0, 24, 36, 24,   // 9 - 'Hollow Bullet Point'
  //5, 255, 231, 219, 231, 255,   // 10 - 'Rev Hollow BP'
  //5, 48, 72, 58, 6, 14,   // 11 - 'Male'
  //5, 38, 41, 121, 41, 38,   // 12 - 'Female'
  //5, 64, 127, 5, 5, 7,    // 13 - 'Music Note 1'
  //5, 64, 127, 5, 37, 63,    // 14 - 'Music Note 2'
  //5, 90, 60, 231, 60, 90,   // 15 - 'Snowflake'
  //5, 127, 62, 28, 28, 8,    // 16 - 'Right Pointer'
  //5, 8, 28, 28, 62, 127,    // 17 - 'Left Pointer'
  //5, 20, 34, 127, 34, 20,   // 18 - 'UpDown Arrows'
  //5, 95, 95, 0, 95, 95,   // 19 - 'Double Exclamation'
  //5, 6, 9, 127, 1, 127,   // 20 - 'Paragraph Mark'
  //4, 102, 137, 149, 106,    // 21 - 'Section Mark'
  //5, 96, 96, 96, 96, 96,    // 22 - 'Double Underline'
  //5, 148, 162, 255, 162, 148,   // 23 - 'UpDown Underlined'
  //5, 8, 4, 126, 4, 8,   // 24 - 'Up Arrow'
  //5, 16, 32, 126, 32, 16,   // 25 - 'Down Arrow'
  //5, 8, 8, 42, 28, 8,   // 26 - 'Right Arrow'
  //5, 8, 28, 42, 8, 8,   // 27 - 'Left Arrow'
  //5, 30, 16, 16, 16, 16,    // 28 - 'Angled'
  //5, 12, 30, 12, 30, 12,    // 29 - 'Squashed #'
  //5, 48, 56, 62, 56, 48,    // 30 - 'Up Pointer'
  //5, 6, 14, 62, 14, 6,    // 31 - 'Down Pointer'
  2, 0, 0,    // 32 - 'Space'
  //1, 95,    // 33 - '!'
  //3, 7, 0, 7,   // 34 - '"'
  //5, 20, 127, 20, 127, 20,    // 35 - '#'
  //5, 36, 42, 127, 42, 18,   // 36 - '$'
  //5, 35, 19, 8, 100, 98,    // 37 - '%'
  //5, 54, 73, 86, 32, 80,    // 38 - '&'
  //3, 8, 7, 3,   // 39 - '''
  //3, 28, 34, 65,    // 40 - '('
  //3, 65, 34, 28,    // 41 - ')'
  //5, 42, 28, 127, 28, 42,   // 42 - '*'
  //5, 8, 8, 62, 8, 8,    // 43 - '+'
  //3, 128, 112, 48,    // 44 - ','
  //6, 0, 8, 8, 8, 8, 8,   // 45 - '-'
  1, 64,    // 46 - '.'
  5, 32, 16, 8, 4, 2,   // 47 - '/'
  5, 126, 129, 129, 126, 0,   //6, 0, 126, 129, 129, 129, 126,    // 48 - '0'
  5, 130, 255, 128,0, 0,   //6, 0, 0, 130, 255, 128,0,   // 49 - '1'
  5, 194, 161, 145, 142, 0,   // 6, 0, 130, 193, 161, 145, 142,    // 50 - '2'
  5, 66, 137, 137, 118, 0,   // 6, 0, 66, 129, 137, 137, 118,   // 51 - '3'
  5, 24, 20, 18, 255, 0,  //6, 0, 48, 40, 36, 34, 255,    // 52 - '4'
  5, 79, 137, 137, 113, 0,  // 6, 0, 79, 137, 137, 137, 113,   // 53 - '5'
  5, 126, 137, 137, 114, 0,  // 6, 0, 126, 137, 137, 137, 114,    // 54 - '6'
  5, 225, 17, 9, 7, 0,   // 6, 0, 1, 225, 17, 9, 7,   // 55 - '7'
  5, 118, 137, 137, 118, 0,  // 6, 0, 118, 137, 137, 137, 118,    // 56 - '8'
  5, 78, 145, 145, 126, 0,  //6, 0, 78, 145, 145, 145, 126,   // 57 - '9'
  1, 68,    // 58 - ':'

  5, 38, 41, 41, 47, 40,    // 166
  5, 38, 41, 41, 41, 38,    // 167

  5, 56, 8, 8, 8, 8,    // 169
  5, 8, 8, 8, 8, 56,    // 170

  5, 153, 165, 231, 165, 153,   // 231
  5, 28, 42, 73, 42, 28,    // 232
  5, 76, 114, 1, 114, 76,   // 233
  5, 48, 74, 77, 77, 48,    // 234
  5, 48, 72, 120, 72, 48,   // 235
  //5, 188, 98, 90, 70, 61,   // 236 - 'Zero Slashed'
  4, 62, 73, 73, 73,    // 237
  5, 126, 1, 1, 1, 126,   // 238

};

int serial_in = 2,pulse;
long temp;
bool begin_=1;
volatile long duration=0,m1,m2;
volatile int i=0,arr[90],toggle=0;
String packet="",current_time="",packet_="";

void getbytes(String strbyte);
int twopwr(int);



void setup()
{
  u8g2.begin();
 P.begin();
 //Change 0 to any 0-15 integer to fix brightness
  P.setIntensity(0);
  P.setFont(xantofont);

 
  Serial.begin(115200);
  pinMode(serial_in, INPUT);
  digitalWrite(serial_in,HIGH);

     while(1)
   
  {
    temp=pulseIn(serial_in, LOW);
    if(temp>56000 and temp<66000)
    break;
  }

}

void loop() {

  i=0,toggle=0;
  for(int k=0;k<90;k++)
  arr[k]=0;
  long test_=millis();

  /*
  attachInterrupt(digitalPinToInterrupt(serial_in), isr, CHANGE);
  while(toggle==0)
  {
    if(millis()-test_>90)
    {
      P.displayText("-:--.--", PA_LEFT, 0, 0, PA_PRINT, PA_SCROLL_UP);
       P.displayAnimate();
    }
  }
  detachInterrupt(digitalPinToInterrupt(serial_in));
  */

  delayMicroseconds(416);
  
            
            for(int lx=0;lx<30;lx++)
            {
              arr[lx]=digitalRead(serial_in);    
              delayMicroseconds(810);
            }
            
            arr[30]=digitalRead(serial_in);           
            delayMicroseconds(810);
            
            for(int lx=31;lx<90;lx++)
            {
              arr[lx]=digitalRead(serial_in);    
              delayMicroseconds(810);
            }
            
            
            
            
  for(int k=0;k<90;k++)
  {
   Serial.print(String(arr[k]));
  }
  
  
  Serial.print("\n");
  pulse=1;packet="";current_time="";
  /*
  for(int k=1;arr[k]!=0;k++)
  {
    for(int j=0;j<round((float)arr[k]/828);j++)
    {
      packet+=String(!pulse);
    }
    pulse=!pulse;
  }
  */
  packet="";
  for(int k=0;k<90;k++)
  {
    if(arr[k]==0){
      packet+="1";
    }
    else
    packet+="0";
    }
  //  Serial.println(packet);
 for(int k=1;k<=5;k++)
 getbytes(packet.substring(k*10+1,(k+1)*10-1));

 current_time=current_time.substring(0,1)+':'+current_time.substring(1,3)+'.'+current_time.substring(3,5);
  
  char charbuf[10];
  current_time.toCharArray(charbuf,10);

  if(isDigit(charbuf[0]) and isDigit(charbuf[6]) and isDigit(charbuf[2]) and isDigit(charbuf[3]) and isDigit(charbuf[5]))
  {
    P.displayText(charbuf, PA_LEFT, 0, 0, PA_PRINT, PA_SCROLL_UP);
    P.displayAnimate(); 
    
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_logisoso30_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
    u8g2.drawStr(1,32,charbuf);  // write something to the internal memory
    u8g2.sendBuffer();         // transfer internal memory to the display

    
  }
  else
  {
   //Hack to resolve last seconds on QJ Timer. TODO: Improve timing of digitalRead to fix this

   charbuf[5]=qj_fix(charbuf[5]);
   charbuf[6]=qj_fix(charbuf[6]);

        if(isDigit(charbuf[0]) and isDigit(charbuf[6]) and isDigit(charbuf[2]) and isDigit(charbuf[3]) and isDigit(charbuf[5]))
        {
          P.displayText(charbuf, PA_LEFT, 0, 0, PA_PRINT, PA_SCROLL_UP);
          P.displayAnimate(); 

          u8g2.clearBuffer();          // clear the internal memory
          u8g2.setFont(u8g2_font_logisoso32_tn);
//          u8g2.setFont(u8g2_font_logisoso30_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
          u8g2.drawStr(1,32,charbuf);  // write something to the internal memory
          u8g2.sendBuffer();         // transfer internal memory to the display
    
        }
    
   
  }

 
  long test=millis();
  while(digitalRead(serial_in)==0)
  {
    if(millis()-test>90)
    {
       P.displayText("", PA_LEFT, 0, 0, PA_PRINT, PA_SCROLL_UP);
       P.displayAnimate();

       u8g2.clearBuffer();          // clear the internal memory
       u8g2.setFont(u8g2_font_logisoso30_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
       u8g2.drawStr(1,32,"");  // write something to the internal memory
       u8g2.sendBuffer();         // transfer internal memory to the display
    
    }
  }
  
}

void isr()
{
  m1=micros();

 if(m1-m2>58000 and begin_==true)
  {
    Serial.println("Start");begin_=false;
    
  }
  else
  {
     arr[i]=m1-m2;
    if(i>5 and round((float)arr[i]/750)==4 and round((float)arr[i-1]/750)==2 and round((float)arr[i-2]/750)==1 and round((float)arr[i-3]/750)==1 and round((float)arr[i-4]/750)==1 and round((float)arr[i-5]/750)==1)
   {
    
   // Serial.println();
    m2=micros();
    toggle=1;
    return;
   }
   
   // Serial.print(String(arr[i])+"-");
    i++;
  }
  m2=micros();

}

void getbytes(String strbyte)
{

  int digit=0;
  for(int k=0;k<8;k++)
  {
   if(strbyte[k]=='1')
   {
    digit+=twopwr(k);
      
   }
  }

  char c=digit;
 current_time+=String(c);
  
}

//Returns 2 raised to the specified integer. Required because pow() from math.h has rounding errors.
int twopwr(int a)
{
  int out=1;
  for(int l=0;l<a;l++)
  out=out*2;

  return out;
}

char qj_fix(char ch)
{
  switch(ch)
  {
    case '`':
    return '0';
    break;

    case 'b':
    return '1';
    break;

    case 'd':
    return '2';
    break;

    case 'f':
    return '3';
    break;

    case 'h':
    return '4';
    break;

    case 'j':
    return '5';
    break;

    case 'l':
    return '6';
    break;

    case 'n':
    return '7';
    break;

    case 'p':
    return '8';
    break;

    case 'r':
    return '9';
    break;

    
  }
}
