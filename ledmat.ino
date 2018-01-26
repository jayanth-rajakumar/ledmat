#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>
#include<SoftwareSerial.h>

#define MAX_DEVICES 5
#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10
SoftwareSerial S(8,9);

MD_Parola P = MD_Parola(CS_PIN, MAX_DEVICES);

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
  6, 0, 8, 8, 8, 8, 8,   // 45 - '-'
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
  3, 8, 54, 65,   // 123 - '{'
  1, 119,   // 124 - '|'
  3, 65, 54, 8,   // 125 - '}'
  5, 2, 1, 2, 4, 2,   // 126 - '~'
  5, 60, 38, 35, 38, 60,    // 127 - 'Hollow Up Arrow'
  5, 30, 161, 161, 97, 18,    // 128 - 'C sedilla'
  5, 56, 66, 64, 34, 120,   // 129 - 'u umlaut'
  5, 56, 84, 84, 85, 89,    // 130 - 'e acute'
  5, 33, 85, 85, 121, 65,   // 131 - 'a accent'
  5, 33, 84, 84, 120, 65,   // 132 - 'a umlaut'
  5, 33, 85, 84, 120, 64,   // 133 - 'a grave'
  5, 32, 84, 85, 121, 64,   // 134 - 'a acute'
  5, 24, 60, 164, 228, 36,    // 135 - 'c sedilla'
  5, 57, 85, 85, 85, 89,    // 136 - 'e accent'
  5, 56, 85, 84, 85, 88,    // 137 - 'e umlaut'
  5, 57, 85, 84, 84, 88,    // 138 - 'e grave'
  3, 69, 124, 65,   // 139 - 'i umlaut'
  4, 2, 69, 125, 66,    // 140 - 'i hat'
  4, 1, 69, 124, 64,    // 141 - 'i grave'
  5, 240, 41, 36, 41, 240,    // 142 - 'A umlaut'
  5, 240, 40, 37, 40, 240,    // 143 - 'A dot'
  4, 124, 84, 85, 69,   // 144 - 'E grave'
  7, 32, 84, 84, 124, 84, 84, 8,    // 145 - 'ae'
  6, 124, 10, 9, 127, 73, 73,   // 146 - 'AE'
  5, 50, 73, 73, 73, 50,    // 147 - 'o hat'
  5, 48, 74, 72, 74, 48,    // 148 - 'o umlaut'
  5, 50, 74, 72, 72, 48,    // 149 - 'o grave'
  5, 58, 65, 65, 33, 122,   // 150 - 'u hat'
  5, 58, 66, 64, 32, 120,   // 151 - 'u grave'
  4, 157, 160, 160, 125,    // 152 - 'y umlaut'
  5, 56, 69, 68, 69, 56,    // 153 - 'O umlaut'
  5, 60, 65, 64, 65, 60,    // 154 - 'U umlaut'
  5, 60, 36, 255, 36, 36,   // 155 - 'Cents'
  5, 72, 126, 73, 67, 102,    // 156 - 'Pounds'
  5, 43, 47, 252, 47, 43,   // 157 - 'Yen'
  5, 255, 9, 41, 246, 32,   // 158 - 'R +'
  5, 192, 136, 126, 9, 3,   // 159 - 'f notation'
  5, 32, 84, 84, 121, 65,   // 160 - 'a acute'
  3, 68, 125, 65,   // 161 - 'i acute'
  5, 48, 72, 72, 74, 50,    // 162 - 'o acute'
  5, 56, 64, 64, 34, 122,   // 163 - 'u acute'
  4, 122, 10, 10, 114,    // 164 - 'n accent'
  5, 125, 13, 25, 49, 125,    // 165 - 'N accent'
  5, 38, 41, 41, 47, 40,    // 166
  5, 38, 41, 41, 41, 38,    // 167
  5, 48, 72, 77, 64, 32,    // 168 - 'Inverted ?'
  5, 56, 8, 8, 8, 8,    // 169
  5, 8, 8, 8, 8, 56,    // 170
  5, 47, 16, 200, 172, 186,   // 171 - '1/2'
  5, 47, 16, 40, 52, 250,   // 172 - '1/4'
  1, 123,   // 173 - '| split'
  5, 8, 20, 42, 20, 34,   // 174 - '<<'
  5, 34, 20, 42, 20, 8,   // 175 - '>>'
  5, 170, 0, 85, 0, 170,    // 176 - '30% shading'
  5, 170, 85, 170, 85, 170,   // 177 - '50% shading'
  5, 0, 0, 0, 0, 255,   // 178 - 'Right side'
  5, 16, 16, 16, 16, 255,   // 179 - 'Right T'
  5, 20, 20, 20, 20, 255,   // 180 - 'Right T double H'
  5, 16, 16, 255, 0, 255,   // 181 - 'Right T double V'
  5, 16, 16, 240, 16, 240,    // 182 - 'Top Right double V'
  5, 20, 20, 20, 20, 252,   // 183 - 'Top Right double H'
  5, 20, 20, 247, 0, 255,   // 184 - 'Right T double all'
  5, 0, 0, 255, 0, 255,   // 185 - 'Right side double'
  5, 20, 20, 244, 4, 252,   // 186 - 'Top Right double'
  5, 20, 20, 23, 16, 31,    // 187 - 'Bot Right double'
  5, 16, 16, 31, 16, 31,    // 188 - 'Bot Right double V'
  5, 20, 20, 20, 20, 31,    // 189 - 'Bot Right double H'
  5, 16, 16, 16, 16, 240,   // 190 - 'Top Right'
  5, 0, 0, 0, 31, 16,   // 191 - 'Bot Left'
  5, 16, 16, 16, 31, 16,    // 192 - 'Bot T'
  5, 16, 16, 16, 240, 16,   // 193 - 'Top T'
  5, 0, 0, 0, 255, 16,    // 194 - 'Left T'
  5, 16, 16, 16, 16, 16,    // 195 - 'Top side'
  5, 16, 16, 16, 255, 16,   // 196 - 'Center +'
  5, 0, 0, 0, 255, 20,    // 197 - 'Left side double H'
  5, 0, 0, 255, 0, 255,   // 198 - 'Left side double'
  5, 0, 0, 31, 16, 23,    // 199 - 'Bot Left double V'
  5, 0, 0, 252, 4, 244,   // 200 - 'Top Left double V'
  5, 20, 20, 23, 16, 23,    // 201 - 'Bot T double'
  5, 20, 20, 244, 4, 244,   // 202 - 'Top T double'
  5, 0, 0, 255, 0, 247,   // 203 - 'Left Side double spl'
  5, 20, 20, 20, 20, 20,    // 204 - 'Center double'
  5, 20, 20, 247, 0, 247,   // 205 - 'Center + double'
  5, 20, 20, 20, 23, 20,    // 206 - 'Bot T double H'
  5, 16, 16, 31, 16, 31,    // 207 - 'Bot Right double V'
  5, 20, 20, 20, 244, 20,   // 208 - 'Top T double H'
  5, 16, 16, 240, 16, 240,    // 209 - 'Top Right double V'
  5, 0, 0, 31, 16, 31,    // 210 - 'Bot Left double V'
  5, 0, 0, 0, 31, 20,   // 211 - 'Bot Right double H'
  5, 0, 0, 0, 252, 20,    // 212 - 'Top Right double H'
  5, 0, 0, 240, 16, 240,    // 213 - 'Top Right double V'
  5, 16, 16, 255, 16, 255,    // 214 - 'Center + double V'
  5, 20, 20, 20, 255, 20,   // 215 - 'Center + double H'
  5, 16, 16, 16, 16, 31,    // 216 - 'Bot Right'
  5, 0, 0, 0, 240, 16,    // 217 - 'Top Left'
  5, 255, 255, 255, 255, 255,   // 218 - 'Full Block'
  5, 240, 240, 240, 240, 240,   // 219 - 'Half Block Bottom'
  3, 255, 255, 255,   // 220 - 'Half Block LHS'
  5, 0, 0, 0, 255, 255,   // 221 - 'Half Block RHS'
  5, 15, 15, 15, 15, 15,    // 222 - 'Half Block Top'
  5, 56, 68, 68, 56, 68,    // 223 - 'Alpha'
  5, 124, 42, 42, 62, 20,   // 224 - 'Beta'
  5, 126, 2, 2, 6, 6,   // 225 - 'Gamma'
  5, 2, 126, 2, 126, 2,   // 226 - 'Pi'
  5, 99, 85, 73, 65, 99,    // 227 - 'Sigma'
  5, 56, 68, 68, 60, 4,   // 228 - 'Theta'
  5, 64, 126, 32, 30, 32,   // 229 - 'mu'
  5, 6, 2, 126, 2, 2,   // 230 - 'Tau'
  5, 153, 165, 231, 165, 153,   // 231
  5, 28, 42, 73, 42, 28,    // 232
  5, 76, 114, 1, 114, 76,   // 233
  5, 48, 74, 77, 77, 48,    // 234
  5, 48, 72, 120, 72, 48,   // 235
  5, 188, 98, 90, 70, 61,   // 236 - 'Zero Slashed'
  4, 62, 73, 73, 73,    // 237
  5, 126, 1, 1, 1, 126,   // 238
  5, 42, 42, 42, 42, 42,    // 239 - '3 Bar Equals'
  5, 68, 68, 95, 68, 68,    // 240 - '+/-'
  5, 64, 81, 74, 68, 64,    // 241 - '>='
  5, 64, 68, 74, 81, 64,    // 242 - '<='
  5, 0, 0, 255, 1, 3,   // 243 - 'Top of Integral'
  3, 224, 128, 255,   // 244 - 'Bot of Integral'
  5, 8, 8, 107, 107, 8,   // 245 - 'Divide'
  5, 54, 18, 54, 36, 54,    // 246 - 'Wavy ='
  5, 6, 15, 9, 15, 6,   // 247 - 'Degree'
  4, 0, 0, 24, 24,    // 248 - 'Math Product'
  4, 0, 0, 16, 16,    // 249 - 'Short Dash'
  5, 48, 64, 255, 1, 1,   // 250 - 'Square Root'
  5, 0, 31, 1, 1, 30,   // 251 - 'Superscript n'
  5, 0, 25, 29, 23, 18,   // 252 - 'Superscript 2'
  5, 0, 60, 60, 60, 60,   // 253 - 'Centered Square'
  5, 255, 129, 129, 129, 255,   // 254 - 'Full Frame'
  5, 255, 255, 255, 255, 255,   // 255 - 'Full Block'
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
 P.begin();
  P.setIntensity(0);
  P.setFont(xantofont);

 
  S.begin(9600);
  pinMode(serial_in, INPUT);
  digitalWrite(serial_in,HIGH);

/*
     while(1)
   
  {
    temp=pulseIn(serial_in, LOW);
    if(temp>56000 and temp<66000)
    break;
  }
  */
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
   //Serial.print(String(arr[k]));
  }
  
  
  //Serial.print("\n");
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
    S.println(current_time);
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
          current_time.toCharArray(charbuf,10);
          S.println(current_time);
        }
    
   
  }

  //Read pot and adjust brightness
  {
      int pot=analogRead(A0);   
      if(pot<100)
         P.setIntensity(0);
      else if(pot>150 and pot<250)
         P.setIntensity(3);
      else if(pot>300 and pot<400)
         P.setIntensity(6);
      else if(pot>450 and pot<550)
         P.setIntensity(9);
      else if(pot>600 and pot<700)
         P.setIntensity(12);
      else if(pot>750 and pot<850)
         P.setIntensity(15);
    
  }
  long test=millis();
  while(digitalRead(serial_in)==0)
  {
    if(millis()-test>90)
    {
      P.displayText("-:--.--", PA_LEFT, 0, 0, PA_PRINT, PA_SCROLL_UP);
       P.displayAnimate();
    }
  }
  
}

void isr()
{
  m1=micros();

 if(m1-m2>58000 and begin_==true)
  {
   // Serial.println("Start");
    begin_=false;
    
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

