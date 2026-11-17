#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH,SCREEN_HEIGHT,&Wire,OLED_RESET);
const int RED_PIN=9,GREEN_PIN=10,BLUE_PIN=11;
unsigned long lastPacketTime=0;
const unsigned long TIMEOUT_MS=3000;
bool isConnected=false;
const unsigned char PROGMEM monitor_logo_bmp[]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0f,0xff,0xff,0xf0,0x1f,0xff,0xff,0xf8,
0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x18,0x06,0x00,0x18,
0x18,0x0f,0x00,0x18,0x18,0x19,0x80,0x18,0x18,0x30,0xc3,0x18,0x18,0x60,0x67,0x98,
0x18,0xc0,0x3c,0xd8,0x18,0x00,0x18,0x18,0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x18,
0x18,0x00,0x00,0x18,0x18,0x00,0x00,0x18,0x1f,0xff,0xff,0xf8,0x0f,0xff,0xff,0xf0,
0x00,0x03,0xc0,0x00,0x00,0x03,0xc0,0x00,0x00,0x03,0xc0,0x00,0x00,0x1f,0xf8,0x00,
0x00,0x3f,0xfc,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
void setup(){
Serial.begin(115200);
pinMode(RED_PIN,OUTPUT);
pinMode(GREEN_PIN,OUTPUT);
pinMode(BLUE_PIN,OUTPUT);
if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){for(;;);}
showStandbyLogo();
}
void loop(){
if(Serial.available()>0){
int gt=Serial.parseInt(),gu=Serial.parseInt(),gw=Serial.parseInt(),cu=Serial.parseInt(),ram=Serial.parseInt(),bat=Serial.parseInt();
if(Serial.read()=='\n'){
lastPacketTime=millis();
isConnected=true;
updateDisplay(gt,gu,gw,cu,ram,bat);
updateLED(gt);
}
}
if(isConnected&&(millis()-lastPacketTime>TIMEOUT_MS)){
isConnected=false;
showStandbyLogo();
}
}
void showStandbyLogo(){
display.clearDisplay();
display.drawBitmap(48,12,monitor_logo_bmp,32,32,WHITE);
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(34,48);
display.println("STANDBY...");
display.display();
setColor(0,0,0);
}
void updateDisplay(int gt,int gu,int gw,int cu,int ram,int bat){
display.clearDisplay();
display.setTextColor(WHITE);
display.setTextSize(1);
display.setCursor(0,4);
display.print("GPU: ");display.print(gt);display.print("C | %");display.print(gu);display.print(" | ");display.print(gw);display.println("W");
display.drawLine(0,18,128,18,WHITE);
display.setCursor(0,26);
display.print("CPU: %");display.print(cu);
display.setCursor(66,26);
display.print("RAM: %");display.println(ram);
display.setCursor(0,46);
display.print("BATARYA: %");display.println(bat);
display.display();
}
void updateLED(int gt){
if(gt>75)setColor(255,0,0);
else if(gt<50)setColor(0,255,0);
else setColor(0,0,255);
}
void setColor(int r,int g,int b){
analogWrite(RED_PIN,r);
analogWrite(GREEN_PIN,g);
analogWrite(BLUE_PIN,b);
}