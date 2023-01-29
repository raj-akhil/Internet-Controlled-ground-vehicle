#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial s(2,4); // RX, TX
int x,y,period_1;
long int temparory;
int pre_pos=0,curr_pos=0;
Servo servo_2;
Servo servo_3;
/*Servo servo_z;
Servo servo_x;
Servo servo_y;*/

//new function

/*void point(long int num)
  {
    double x,y,z,h,a1,r2,r1,k2,r3,k1,a3,a2,i,k3,l,chek;
     z=num%100;
     num=num/100;
     y=num%100;
     x=num/100;
     if(x<0)
     {
       x=-1*x;
     }
     if(y<0)
     {
       y=-1*y;  
     }
      Serial.println(x);
      Serial.println(y);
      Serial.println(z);
      chek=sqrt(x*x+y*y+z*z);
    a1=0;
    a2=10;//14.8;
    a3=10;
    double temp1=(a2-a3);
    double temp2=(a2+a3);
    if(temp1<=chek && chek<=temp2 && y>=0 && x<100 && y<100 && z<100)
    {
    if(x==0.0)
      h=0;
    else
    {   
    h=atan(x/y);
    h=h*180/3.14;//angle1      
    }
    r2=z-a1;
    r1=sqrt(x*x+y*y);
    k2=atan(r2/r1);
    r3=sqrt(r1*r1+r2*r2);
    k1=acos((a3*a3-a2*a2-r3*r3)/(-2*a2*r3));
    i=k2-k1;
    i=i*180/3.14;//angle2
    k3=acos((r3*r3-a2*a2-a3*a3)/(-2*a3*a2));
    k3=k3*180/3.14;
    l=180-k3;
    h=round(h);
    i=round(i);
    l=round(l);
    if(i<0)
    {
      i=-1*i;
      l=-1*l;
    }
    Serial.println(2*h);//for servo
    Serial.println(i);
    Serial.println(l+180);
      if(h<=90 && h>=0 && i<=180 && i>=0 && l<=0 && l>=-180)
      {
               Serial.println(2*h);//for servo
               Serial.println(i);
               Serial.println(l+180);
               servo_z.write(2*h);
               servo_x.write(i);
               servo_y.write(l+180);
               
        
      }
    }
    else
    {
      Serial.println("SYSTEM CONSTRAINT FAILURE");
    }
  }
  ///next function
  void line(double x1,double y1,double z1,double x2,double y2,double z2)
  {
    double c1,c2,c3,cv,x,y,z,p=1;
    int j=0;
    boolean flag=false;
    c1=x1-x2;
    c2=y1-y2;
    c3=z1-z2;
    x=x1;
    if(x2<x1)
    {
      p=-p;
    }
    while(true)
    {
      x=x1+j*p;
      if(x2>=x1 && x>=x2)
      {
        x=x2;
        flag=true;
      }
      else if(x2<x1 && x<=x2)
      {
        x=x2;
        flag=true;
      }
      cv=x-x1;
      y=(cv*c2/c1)+y1;
      z=(cv*c3/c1)+z1;
      j=j+1;
      Serial.println();//for servo
     Serial.print(x);
     Serial.print(" ");
     Serial.print(y);
     Serial.print(" ");
     Serial.print(z);
          if(flag)
          {
            break;
          }
          
      
    }
    
  }*/
void Led_Screen(String n,int m,int c,int d)
{
  display.clearDisplay();
  display.setTextSize(d);             
  display.setTextColor(SSD1306_WHITE);       
  display.setCursor(m,c);             
  display.println(n);
  display.display();
}

void setup()
{

  s.begin(9600);
  Serial.begin(9600);
   if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) 
  {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  pinMode(8,INPUT_PULLUP); //switch
  pinMode(13,OUTPUT);//camera linear
  pinMode(12,OUTPUT);//camera linear
  servo_2.attach(9);//rotating camera
  servo_3.attach(6);
  /*servo_z.attach(6);
  servo_x.attach(5);
  servo_y.attach(3);*/
 
 
}

void loop() // run over and over
{
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
  //servo_3.write(0);
  if(Serial.available()>0)
  {
      temparory=Serial.parseFloat();
      Serial.println(temparory);
     
  }
   

  if (s.available())
    {
       int num=s.read();
      Serial.println(num);
      String oled = String(num);
      Led_Screen(oled,60,30,2);
      if(oled==255)
      {
        servo_3.write(0);
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("connected");
        display.display();
        delay(3000);
        display.clearDisplay();
      }
      
      if(num==0)
      {
        Serial.println("front tyre should turn 100");
        servo_3.write(100);
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("left or right");
        display.display();
        delay(1000);
      }

       if(num==1)
      {
        Serial.println("front tyre should turn 0");
        servo_3.write(0);
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("front or back");
        display.display();
        delay(1000);
      }
  
       x=num/10;
       y=num%10;
       if(x==1)
       {
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("camera up");
        display.display();
        delay(1000);
        display.clearDisplay();
       }
       if(x==2)
       {
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("camera down");
        display.display();
        delay(1000);
        display.clearDisplay();
       }
       if(x==3)
       {
        display.clearDisplay();
        display.setTextSize(2);             
        display.setTextColor(SSD1306_WHITE);       
        display.setCursor(0,0);             
        display.println("camera turning");
        display.display();
        delay(1000);
        display.clearDisplay();
       }
      if(x==1)
      {
                    int period = y*1000;
                    unsigned long time_now = 0;
                    time_now = millis();
                    while(millis() < time_now + period)
                          {
                            int a=digitalRead(8);
                            delay(10);
                            int b=digitalRead(8);
                            if(a==0 && b==0)
                               {
                                period_1=1000;
                                time_now=millis();
                                while(millis() < time_now + period_1)
                                  {
                                    digitalWrite(12,LOW);
                                    digitalWrite(13,HIGH);
                                    yield();
                                   }
                                   break;
                               }
                               else{
                                 //wait approx. [period] ms
                                 Serial.println("camera up");
                                 digitalWrite(13,LOW);
                                 digitalWrite(12,HIGH);
                                 yield();
                               }
                           }
        
      }
     else if(x==2)
      {
                    
                     int period = y*1000;
                     unsigned long time_now = 0;
                     time_now = millis();
                     while(millis() < time_now + period)
                           {
                                  int a=digitalRead(8);
                                  delay(10);
                                  int b=digitalRead(8);
                                  if(a==0 && b==0){
                                   period_1=1000;
                                   time_now=millis();
                                    while(millis() < time_now + period_1)
                                      {
                                        digitalWrite(13,LOW);
                                        digitalWrite(12,HIGH);
                                         yield();
                                       }
                                       break;
                                  }
                                       else{
                                  //wait approx. [period] ms
                                   Serial.println("camera down");
                                   digitalWrite(12,LOW);
                                   digitalWrite(13,HIGH);
                                   yield();
                                       }
                           }
      
      }
    else if(x==3)
      {
        
          curr_pos=y*10;
                if(curr_pos>pre_pos)
                {
                  for (int pos = pre_pos; pos <= curr_pos; pos += 1) 
                     { 
                       servo_2.write(pos); 
                       delay(50);                       
                     }
                }
                else
                {
                  for (int pos = pre_pos; pos >= curr_pos; pos -= 1) 
                     { 
                       servo_2.write(pos); 
                       delay(50);                       
                     }
                }
                pre_pos=curr_pos;
               }
       else
               {
                        digitalWrite(14,HIGH);
                        digitalWrite(12,HIGH); 
                       
                       
                        
                }
      }
      

    
}
