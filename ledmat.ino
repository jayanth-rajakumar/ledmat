#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>


#define MAX_DEVICES 5
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10


MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

int serial_in = 2,pulse;
long temp;
volatile long duration=0,m1,m2;
volatile int i=0,arr[90],toggle=0;
String packet="",current_time="";

void getbytes(String strbyte);
int twopwr(int);

//Comment
void setup()
{
 P.begin();
  P.setIntensity(0);
  P.setFont(xantofont);

 
  Serial.begin(9600);
  pinMode(serial_in, INPUT);
  digitalWrite(serial_in,HIGH);

  
}

void loop() {

  i=0,toggle=0;
  for(int k=0;k<90;k++)
  arr[k]=0;

   while(1)
   
  {
    temp=pulseIn(serial_in, LOW);
    if(temp>56000 and temp<66000)
    break;
  }
   
  attachInterrupt(digitalPinToInterrupt(serial_in), isr, CHANGE);
  while(toggle==0);
  detachInterrupt(digitalPinToInterrupt(serial_in));

  pulse=1;packet="";current_time="";
  for(int k=1;arr[k]!=0;k++)
  {
    for(int j=0;j<round((float)arr[k]/828);j++)
    {
      packet+=String(!pulse);
    }
    pulse=!pulse;
  }

  for(int k=1;k<=5;k++)
 getbytes(packet.substring(k*10+1,(k+1)*10-1));
 current_time=current_time.substring(0,1)+':'+current_time.substring(1,3)+'.'+current_time.substring(3,5);
  Serial.println(current_time);
  
  char charbuf[10];
  current_time.toCharArray(charbuf,10);
  P.displayText(charbuf, PA_RIGHT, 0, 0, PA_PRINT, PA_NO_EFFECT);
  P.displayAnimate();
}

void isr()
{
  m1=micros();
  if((m1-m2)>56000 and (m1-m2)<66000)
  {toggle=1;
  return;
  }
arr[i]=m1-m2;
i++;
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

MD_MAX72XX::fontType_t xantofont[] PROGMEM = {
  0,    // 0 - 'Empty Cell'
  5, 62, 91, 79, 91, 62,    // 1 - 'Sad Smiley'
  5, 62, 107, 79, 107, 62,    // 2 - 'Happy Smiley'
  5, 28, 62, 124, 62, 28,   // 3 - 'Heart'
  5, 24, 60, 126, 60, 24,   // 4 - 'Diamond'
  5, 28, 87, 125, 87, 28,   // 5 - 'Clubs'
  5, 28, 94, 127, 94, 28,   // 6 - 'Spades'
  4, 0, 24, 60, 24,   // 7 - 'Bullet Point'
  5, 255, 231, 195, 231, 255,   // 8 - 'Rev Bullet Point'
  4, 0, 24, 36, 24,   // 9 - 'Hollow Bullet Point'
  5, 255, 231, 219, 231, 255,   // 10 - 'Rev Hollow BP'
  5, 48, 72, 58, 6, 14,   // 11 - 'Male'
  5, 38, 41, 121, 41, 38,   // 12 - 'Female'
  5, 64, 127, 5, 5, 7,    // 13 - 'Music Note 1'
  5, 64, 127, 5, 37, 63,    // 14 - 'Music Note 2'
  5, 90, 60, 231, 60, 90,   // 15 - 'Snowflake'
  5, 127, 62, 28, 28, 8,    // 16 - 'Right Pointer'
  5, 8, 28, 28, 62, 127,    // 17 - 'Left Pointer'
  5, 20, 34, 127, 34, 20,   // 18 - 'UpDown Arrows'
  5, 95, 95, 0, 95, 95,   // 19 - 'Double Exclamation'
  5, 6, 9, 127, 1, 127,   // 20 - 'Paragraph Mark'
  4, 102, 137, 149, 106,    // 21 - 'Section Mark'
  5, 96, 96, 96, 96, 96,    // 22 - 'Double Underline'
  5, 148, 162, 255, 162, 148,   // 23 - 'UpDown Underlined'
  5, 8, 4, 126, 4, 8,   // 24 - 'Up Arrow'
  5, 16, 32, 126, 32, 16,   // 25 - 'Down Arrow'
  5, 8, 8, 42, 28, 8,   // 26 - 'Right Arrow'
  5, 8, 28, 42, 8, 8,   // 27 - 'Left Arrow'
  5, 30, 16, 16, 16, 16,    // 28 - 'Angled'
  5, 12, 30, 12, 30, 12,    // 29 - 'Squashed #'
  5, 48, 56, 62, 56, 48,    // 30 - 'Up Pointer'
  5, 6, 14, 62, 14, 6,    // 31 - 'Down Pointer'
  2, 0, 0,    // 32 - 'Space'
  1, 95,    // 33 - '!'
  3, 7, 0, 7,   // 34 - '"'
  5, 20, 127, 20, 127, 20,    // 35 - '#'
  5, 36, 42, 127, 42, 18,   // 36 - '$'
  5, 35, 19, 8, 100, 98,    // 37 - '%'
  5, 54, 73, 86, 32, 80,    // 38 - '&'
  3, 8, 7, 3,   // 39 - '''
  3, 28, 34, 65,    // 40 - '('
  3, 65, 34, 28,    // 41 - ')'
  5, 42, 28, 127, 28, 42,   // 42 - '*'
  5, 8, 8, 62, 8, 8,    // 43 - '+'
  3, 128, 112, 48,    // 44 - ','
  5, 8, 8, 8, 8, 8,   // 45 - '-'
  2, 96, 96,    // 46 - '.'
  5, 32, 16, 8, 4, 2,   // 47 - '/'
  6, 0, 126, 129, 129, 129, 126,    // 48 - '0'
  6, 0, 0, 130, 255, 128,0,   // 49 - '1'
  6, 0, 130, 193, 161, 145, 142,    // 50 - '2'
  6, 0, 66, 129, 137, 137, 118,   // 51 - '3'
  6, 0, 48, 40, 36, 34, 255,    // 52 - '4'
  6, 0, 79, 137, 137, 137, 113,   // 53 - '5'
  6, 0, 126, 137, 137, 137, 114,    // 54 - '6'
  6, 0, 1, 225, 17, 9, 7,   // 55 - '7'
  6, 0, 118, 137, 137, 137, 118,    // 56 - '8'
  6, 0, 78, 145, 145, 145, 126,   // 57 - '9'
  1, 36,    // 58 - ':'
  2, 128, 104,    // 59 - ';'
  4, 8, 20, 34, 65,   // 60 - '<'
  5, 20, 20, 20, 20, 20,    // 61 - '='
  4, 65, 34, 20, 8,   // 62 - '>'
  5, 2, 1, 89, 9, 6,    // 63 - '?'
  5, 62, 65, 93, 89, 78,    // 64 - '@'
  5, 124, 18, 17, 18, 124,    // 65 - 'A'
  5, 127, 73, 73, 73, 54,   // 66 - 'B'
  5, 62, 65, 65, 65, 34,    // 67 - 'C'
  5, 127, 65, 65, 65, 62,   // 68 - 'D'
  5, 127, 73, 73, 73, 65,   // 69 - 'E'
  5, 127, 9, 9, 9, 1,   // 70 - 'F'
  5, 62, 65, 65, 81, 115,   // 71 - 'G'
  5, 127, 8, 8, 8, 127,   // 72 - 'H'
  3, 65, 127, 65,   // 73 - 'I'
  5, 32, 64, 65, 63, 1,   // 74 - 'J'
  5, 127, 8, 20, 34, 65,    // 75 - 'K'
  5, 127, 64, 64, 64, 64,   // 76 - 'L'
  5, 127, 2, 28, 2, 127,    // 77 - 'M'
  5, 127, 4, 8, 16, 127,    // 78 - 'N'
  5, 62, 65, 65, 65, 62,    // 79 - 'O'
  5, 127, 9, 9, 9, 6,   // 80 - 'P'
  5, 62, 65, 81, 33, 94,    // 81 - 'Q'
  5, 127, 9, 25, 41, 70,    // 82 - 'R'
  5, 38, 73, 73, 73, 50,    // 83 - 'S'
  5, 3, 1, 127, 1, 3,   // 84 - 'T'
  5, 63, 64, 64, 64, 63,    // 85 - 'U'
  5, 31, 32, 64, 32, 31,    // 86 - 'V'
  5, 63, 64, 56, 64, 63,    // 87 - 'W'
  5, 99, 20, 8, 20, 99,   // 88 - 'X'
  5, 3, 4, 120, 4, 3,   // 89 - 'Y'
  5, 97, 89, 73, 77, 67,    // 90 - 'Z'
  3, 127, 65, 65,   // 91 - '['
  5, 2, 4, 8, 16, 32,   // 92 - '\'
  3, 65, 65, 127,   // 93 - ']'
  5, 4, 2, 1, 2, 4,   // 94 - '^'
  5, 64, 64, 64, 64, 64,    // 95 - '_'
  3, 3, 7, 8,   // 96 - '`'
  5, 32, 84, 84, 120, 64,   // 97 - 'a'
  5, 127, 40, 68, 68, 56,   // 98 - 'b'
  5, 56, 68, 68, 68, 40,    // 99 - 'c'
  5, 56, 68, 68, 40, 127,   // 100 - 'd'
  5, 56, 84, 84, 84, 24,    // 101 - 'e'
  4, 8, 126, 9, 2,    // 102 - 'f'
  5, 24, 164, 164, 156, 120,    // 103 - 'g'
  5, 127, 8, 4, 4, 120,   // 104 - 'h'
  3, 68, 125, 64,   // 105 - 'i'
  4, 64, 128, 128, 122,   // 106 - 'j'
  4, 127, 16, 40, 68,   // 107 - 'k'
  3, 65, 127, 64,   // 108 - 'l'
  5, 124, 4, 120, 4, 120,   // 109 - 'm'
  5, 124, 8, 4, 4, 120,   // 110 - 'n'
  5, 56, 68, 68, 68, 56,    // 111 - 'o'
  5, 252, 24, 36, 36, 24,   // 112 - 'p'
  5, 24, 36, 36, 24, 252,   // 113 - 'q'
  5, 124, 8, 4, 4, 8,   // 114 - 'r'
  5, 72, 84, 84, 84, 36,    // 115 - 's'
  4, 4, 63, 68, 36,   // 116 - 't'
  5, 60, 64, 64, 32, 124,   // 117 - 'u'
  5, 28, 32, 64, 32, 28,    // 118 - 'v'
  5, 60, 64, 48, 64, 60,    // 119 - 'w'
  5, 68, 40, 16, 40, 68,    // 120 - 'x'
  5, 76, 144, 144, 144, 124,    // 121 - 'y'
  5, 68, 100, 84, 76, 68,   // 122 - 'z'

};
