// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif
#include "define.h"
#include "ws2812_effect.h"
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <EEPROM.h>
// Declare your global variables here
RF24 radio(PIN_PA1, PIN_PA0); // CE, CSN
//const byte address[6] = "00001";

const byte TX_address[6] = "00001";
const byte RX_address[6] = "00001";
char text[4];
byte red,green,blue;
byte effect,remote_data=0,k=0,t=0;
unsigned int count=0,sync_count=sync_count_offset+2;

struct message                  
{
    
    byte header;
    byte effect;
    byte red,green,blue;
    byte id;
    byte chk_sum;

}; 
message paket,data_recive;




void load_value();
void strip_change_type(Adafruit_NeoPixel *,neoPixelType );
void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  delay_ms(100);
  strip.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
  //strip.clear(); // Set all pixel colors to 'off'
  //strip.setBrightness(255);
  
  
  pinMode(ac_pulse, INPUT);
  digitalWrite(ac_pulse, HIGH);
  Serial.begin(9600 , SERIAL_8N1 );
  printf_begin();
  pinMode(led, OUTPUT);
  pinMode(PIN_PC0, INPUT);
  pinMode(PIN_PC1, INPUT);
  pinMode(PIN_PC2, INPUT);
  pinMode(PIN_PC3, INPUT);
  pinMode(PIN_PC7, INPUT);
  digitalWrite(PIN_PC0, HIGH);
  digitalWrite(PIN_PC1, HIGH);
  digitalWrite(PIN_PC2, HIGH);
  digitalWrite(PIN_PC3, HIGH);
  digitalWrite(PIN_PC7, HIGH);
  radio.begin();
  radio.setDataRate(RF24_1MBPS);
  radio.setChannel(29);
  radio.openWritingPipe(TX_address);
  radio.openReadingPipe(0, RX_address);
  radio.setPALevel(RF24_PA_HIGH,1);
  radio.startListening();
  strip.clear();
  strip.show();
  load_value();
  
  
  Serial.print("slave v1\r\n");
  
  //delay_ms(2000);
  digitalWrite(led, HIGH);
  delay_ms(100);
  digitalWrite(led, LOW);
  radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"
  attachInterrupt(2,getrf, FALLING );
  pinMode(PIN_PB2, INPUT);
  digitalWrite(PIN_PB2, HIGH);
  paket.header=sync_header;
  paket.id=0;
  strip.clear();
  strip.setPixelColor(0,strip.Color(255,0,0));
  strip.setPixelColor(1,strip.Color(0,255,0));
  strip.setPixelColor(2,strip.Color(0,0,255));
  for(int i=0;i<16;i++)
  {
    strip.show();
    digitalWrite(led, HIGH);
    delay(50);
    digitalWrite(led, LOW);
    delay(50);
  }
  strip.clear();
  strip.show();
}


void loop() {
    bool tx,fail,rx;
    int j,i,r,g,b;
    
    
    switch(effect)
    {
      case 1:
       
        
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    if(j%3==0)
                    {
                      //Serial.print("1\r\n");
                      color_strip(&strip,strip.Color(0,0,255));//blue
                    } 
                    delay_ms(100);
                    
                    
            }
            digitalWrite(led, HIGH); 
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("2\r\n");
                      color_strip(&strip,strip.Color(0,255,0));//red
                    } 
                    delay_ms(100);
                    
            }  
            digitalWrite(led, LOW);  
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("3\r\n");
                      color_strip(&strip,strip.Color(255,0,0));//green
                    }
                    delay_ms(100);
                    
            }
            digitalWrite(led, HIGH);
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("4\r\n");
                      color_strip(&strip,strip.Color(255,0,255));//
                    }
                    delay_ms(100);
                    
            }
            digitalWrite(led, LOW);
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("5\r\n");
                      color_strip(&strip,strip.Color(127,255,20));
                    } 
                    delay_ms(100);
                    
            }
            digitalWrite(led, HIGH);
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("6\r\n");
                      color_strip(&strip,strip.Color(0,255,255));
                    } 
                    delay_ms(100);
                    
            }
            digitalWrite(led, LOW);
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("7\r\n");
                      color_strip(&strip,strip.Color(220,255,0));
                    }
                    //set_send_rgb(255,128,0); 
                    delay_ms(100);
                    
            }
            digitalWrite(led, HIGH);
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("8\r\n");
                      color_strip(&strip,strip.Color(0,255,128));
                    }
                    delay_ms(100);
                    
            }
            digitalWrite(led, LOW); 
            clear_sync();
            for(j=0;(j<delay_offset*2 && key_recive==FALSE);j++)
            {
                    
                    if(j%3==0)
                    {
                      //Serial.print("9\r\n");
                      color_strip(&strip,strip.Color(255,255,255));
                    }  
                    delay_ms(100);
                    
            }
            
            digitalWrite(led, HIGH);
            
            //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }  
      break;
      case 2:
        while(key_recive==FALSE)
        {
          wait_sync();
         
          for(j=0;(j<256 && key_recive==FALSE);j=j+5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(j,255,0));
                          }
                          delay_ms(10);
                  }
  
          }
          digitalWrite(led, HIGH);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500); 
          for(j=255;(j>=0 && key_recive==FALSE);j=j-5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(255,j,0));
                          }
                          //set_send_rgb(j,green,blue);
                          delay_ms(10);
                  }
  
          } 
          digitalWrite(led, LOW);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500);
          for(j=0;(j<256 && key_recive==FALSE);j=j+5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(255,0,j));
                          }
                          delay_ms(10);
                  }
  
          }
          digitalWrite(led, HIGH);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500);
          for(j=255;(j>=0 && key_recive==FALSE);j=j-5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(j,0,255));
                          }
                          delay_ms(10);
                  }
  
          }
          digitalWrite(led, LOW);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500);
          for(j=0;(j<256 && key_recive==FALSE);j=j+5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(0,j,255));
                          }
                          delay_ms(10);
                  }
  
          }
          digitalWrite(led, HIGH);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500);  
          for(j=0;(j<256 && key_recive==FALSE);j=j+5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(j,255,255));
                          }
                          delay_ms(10);
                  }
  
          }
          digitalWrite(led, LOW);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
          //delay_ms(500); 
          clear_sync();
          for(j=255;(j>=0 && key_recive==FALSE);j=j-5)
          {
                  for(i=0;(i<delay_offset && key_recive==FALSE);i++) 
                  {
                          if(i%4==0)
                          {
                            color_strip(&strip,strip.Color(j,255,j));
                          }
                          delay_ms(10);
                  }
  
          } 
          
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 3:
        while(key_recive==FALSE)
        {
            iran_flag_effect(&strip,normal);
            digitalWrite(led, HIGH);
            repate_sync();
            delay_ms(20);
            digitalWrite(led, LOW);
            repate_sync();
            delay_ms(20);
          
        }
      break;
      case 4:
      
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_fade(&strip,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              //clear_sync();
              delay_ms(20);
             
            }
            clear_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_fade(&strip,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              //clear_sync();
              delay_ms(20);
             
            }
            
            //delay(1);
          
        }  
      
      break;
      case 5:
      
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_open(&strip,30,300,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            clear_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_open(&strip,30,300,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            //delay(1);
          
        }  
      
      break;
      case 6:
      
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<4 && key_recive==FALSE;j++)
            {
              iran_flag_pixelbar(&strip,65,500,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            clear_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_pixelbar(&strip,65,500,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            //delay(1);
          
        }  
      
      break;
      case 7:
      
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<6 && key_recive==FALSE;j++)
            {
              iran_flag_pixelbar_revers(&strip,65,500,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            clear_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_pixelbar_revers(&strip,65,500,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            //delay(1);
          
        }  
      
      break;
      case 8:
      
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<10 && key_recive==FALSE;j++)
            {
              iran_flag_rainbar_revers(&strip,50,700,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            clear_sync();
            for(j=0;j<2 && key_recive==FALSE;j++)
            {
              iran_flag_rainbar_revers(&strip,50,700,normal);
              digitalWrite(led, HIGH);
              delay_ms(20);
              digitalWrite(led, LOW);
              delay_ms(20);
              
            }
            //delay(1);
          
        }  
      
      break;
      case 9:
        while(key_recive==FALSE)
        {
            wait_sync();
            for(j=0;j<4 && key_recive==FALSE;j++)
            {
              iran_flag_fade(&strip,normal);
              
            }
            digitalWrite(led, HIGH);
            for(j=0;j<6 && key_recive==FALSE;j++)
            {
              iran_flag_open(&strip,30,180,normal);
              
            }
            digitalWrite(led, LOW);
            for(j=0;j<4 && key_recive==FALSE;j++)
            {
              iran_flag_rainbar_revers(&strip,50,700,normal);
              
            }
            clear_sync();
            digitalWrite(led, HIGH);
            for(j=0;j<3 && key_recive==FALSE;j++)
            {
              iran_flag_effect(&strip,normal);
              wait(700);
            }
            
            //delay(1);
        }
        
      break;
      case 10:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(255,0,0,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, HIGH);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(0,255,0,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, LOW);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(0,0,255,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, HIGH);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(255,0,255,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, LOW);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(255,255,0,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, HIGH);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(0,255,255,strip.numPixels()/5,12,50);
          }
          digitalWrite(led, LOW);
          for(j=0;(j<5 && key_recive==FALSE);j++)
          {
            CylonBounce(255,255,255,strip.numPixels()/5,12,50);
          }
          clear_sync();
          strip.clear();
          strip.show();
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      
      case 11:
        while(key_recive==FALSE)
        {
          wait_sync();
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            FadeInOut(255,0,0);
          }
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            FadeInOut(0,255,0);
          }
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            FadeInOut(0,0,255);
          }
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            FadeInOut(255,255,0);
          }
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            FadeInOut(0,255,255);
          }
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            FadeInOut(255,0,255);
          }
          clear_sync();
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            FadeInOut(255,255,255);
          }
          
          //delay(1);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 12:
        while(key_recive==FALSE)
        {
          wait_sync();
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            RunningLights(255,0,0,60); 
          } 
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            RunningLights(0,255,0,60);
          }
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            RunningLights(0,0,255,60);
          }
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            RunningLights(0,255,255,60);
          }
          digitalWrite(led, HIGH);
          if(key_recive==FALSE)
          {
            RunningLights(255,255,0,60);
          }
          clear_sync();
          digitalWrite(led, LOW);
          if(key_recive==FALSE)
          {
            RunningLights(255,255,255,60);
          }
          
          //delay(1);
        }
      break;
      case 13:
          while(key_recive==FALSE)
          {
            wait_sync();
            digitalWrite(led, LOW);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(255,0,0),40);
            }
            digitalWrite(led, HIGH);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(0,255,0),40);
            }
            digitalWrite(led, LOW);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(0,0,255),40);
            }
            digitalWrite(led, HIGH);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(255,255,0),40);
            }
            digitalWrite(led, LOW);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(255,0,255),40);
            }
            digitalWrite(led, HIGH);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(0,255,255),40);
            }
            digitalWrite(led, LOW);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(100,200,0),40);
            }
            digitalWrite(led, HIGH);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(255,255,255),40);
            }
            clear_sync();
            digitalWrite(led, LOW);
            if(key_recive==FALSE)
            {
              colorWipe(strip.Color(0,0,0),40);
            }
            
            //delay(1);
          }
      break;
      case 128:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;(j<23 && key_recive==FALSE);j++)
          {
            CylonBounce(red,green,blue,strip.numPixels()/5,15,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
            //delay_ms(20);
          }
          clear_sync();
          for(j=0;(j<2 && key_recive==FALSE);j++)
          {
            CylonBounce(red,green,blue,strip.numPixels()/5,15,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
            //delay_ms(20);
          }
          
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 129:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;(j<18 && key_recive==FALSE);j++)
          {
            RunningLights(red,green,blue,60);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          clear_sync();
          for(j=0;(j<2 && key_recive==FALSE);j++)
          {
            RunningLights(red,green,blue,60);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 130:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;(j<13 && key_recive==FALSE);j++)
          {
            FadeInOut(red,green,blue);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
            
          }
          clear_sync();
          for(j=0;(j<2 && key_recive==FALSE);j++)
          {
            FadeInOut(red,green,blue);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
            
          }
          //delay(10);
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 131:
        while(key_recive==FALSE)
        {
            setAll(red,green,blue);
            digitalWrite(led, HIGH);
            repate_sync();
            delay_ms(20);
            digitalWrite(led, LOW);
            repate_sync();
            delay_ms(20);
            
        }
      break;
      case 132:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;(j<16 && key_recive==FALSE);j++)
          {
            rain(red,green,blue,strip.numPixels()/3,4,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          clear_sync();
          for(j=0;(j<2 && key_recive==FALSE);j++)
          {
            rain(red,green,blue,strip.numPixels()/3,4,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      case 133:
        while(key_recive==FALSE)
        {
          wait_sync();
          for(j=0;j<13 && key_recive==FALSE;j++)
          {
            rain_revers(red,green,blue,strip.numPixels()/3,4,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          clear_sync();
          for(j=0;j<2 && key_recive==FALSE;j++)
          {
            rain_revers(red,green,blue,strip.numPixels()/3,4,50);
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
          }
          //while(digitalRead(ac_pulse)==1 && key_recive==FALSE);
        }
      break;
      default:
        while(key_recive==FALSE)
        {
          for(j=0;(j<15 && key_recive==FALSE);j++)
          {
            color_strip(&strip,strip.Color(0,0,0));
            digitalWrite(led, HIGH);
            delay_ms(20);
            digitalWrite(led, LOW);
            delay_ms(20);
            repate_sync();
          }
        }
      break;
      
    }
    if(key_recive==TRUE)
    {
            radio.maskIRQ(1, 1, 1); // args = "data_sent", "data_fail", "data_ready"
            key_recive=FALSE;
            sync_recive=TRUE;
            sync_count=0;
            effect=data_recive.effect;
            red=data_recive.red;
            green=data_recive.green;
            blue=data_recive.blue;
            radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"
            EEPROM.update(effect_add,effect);
            EEPROM.update(effect_add+1,~effect);
            EEPROM.update(red_add,red);
            EEPROM.update(green_add,green);
            EEPROM.update(blue_add,blue);
            digitalWrite(led, LOW);
            
    }

    delay(5); // Pause before next pass through loop
    

}


void load_value()
{
  byte type=0,tmp1,tmp2;
  strip.updateLength(NUMPIXELS);
  if(digitalRead(PIN_PC0)==1)
  {
    type=type+1; 
  }
  if(digitalRead(PIN_PC1)==1)
  {
    type=type+2; 
  }
  if(digitalRead(PIN_PC2)==1)
  {
    type=type+4; 
  }
  if(digitalRead(PIN_PC3)==1)
  {
    type=type+8;
  }
  strip_change_type(&strip,type); 
  
  tmp1=EEPROM.read(effect_add);
  tmp2=EEPROM.read(effect_add+1); 
  if(tmp1=~tmp2)
  {
      effect=tmp1;
  }
  else
  {
      effect=200;
      Serial.print("effect reset\r\n");
  }
  red=EEPROM.read(red_add);
  green=EEPROM.read(green_add);
  blue=EEPROM.read(blue_add); 
  //effect=2;
  printf("\n\r red=%i green=%i blue=%i effect=%i \n\r",red,green,blue,effect); 
  
  
}

void strip_change_type(Adafruit_NeoPixel *pixels,neoPixelType strip_type)
{
  neoPixelType strip_speed;
  if(strip_type & 0x08==0x08)
  {
    strip_speed=NEO_KHZ400;
    Serial.print("khz400 \r\n");
  }
  else
  {
    strip_speed=NEO_KHZ800;
    Serial.print("khz800 \r\n");
  }
  strip_type=strip_type & 0x07;
  Serial.print("type="+(String)strip_type+"\r\n");
  switch (strip_type)
  {
     case 0:
      pixels->updateType(NEO_RGB + strip_speed);        
     break;
     case 1:
      pixels->updateType(NEO_RBG + strip_speed);
     break;
     case 2:
      pixels->updateType(NEO_GRB + strip_speed);
     break;
     case 3:
      pixels->updateType(NEO_GBR + strip_speed);
     break;
     case 4:
      pixels->updateType(NEO_BRG + strip_speed);
     break;
     case 5:
      pixels->updateType(NEO_BGR + strip_speed);
     break;
     default:
      pixels->updateType(NEO_GRB + strip_speed);
     break;
     
  }   
}

void send_paket(message d,byte num)
{
  byte i,sum=0,j;
  byte *p;
  radio.stopListening();
  p=&d.header;
  for(i=0;i<message_size;i++)
  {
    sum=sum+*(p+i);
    //p++;      
  }
  d.chk_sum=sum;
  printf("\n\r s heade=%i effect=%i red=%i green=%i blue=%i id=%i\n\r",d.header,d.effect,d.red,d.green,d.blue,d.id);
  delayMicroseconds(100);
  for(j=0;j<num;j++)
  {
    radio.write(&d,sizeof(d));
    delayMicroseconds(1850);
  }
  radio.startListening();
  delayMicroseconds(50);
}
byte cal_checksum(message d)
{
  byte i,sum=0;
  byte *p;
  p=&d.header;
  for(i=0;i<message_size;i++)
  {
    sum=sum+*(p+i);
    //p++;      
  }
  return sum; 
}
void getrf()
{
    bool tx,fail,rx;
    radio.whatHappened(tx,fail,rx);
    //Serial.print("int 2\r\n");
    if ( rx )
    {
      if (radio.available()) {

          radio.read(&data_recive, sizeof(data_recive));
          if(cal_checksum(data_recive)==data_recive.chk_sum)
          {
              printf("\n\r R heade=%i effect=%i red=%i green=%i blue=%i id=%i",data_recive.header,data_recive.effect,data_recive.red,data_recive.green,data_recive.blue,data_recive.id);  
              //delayMicroseconds(1200);
              if(data_recive.header==sync_header && data_recive.id!=sync_id )
              {
                sync_id=data_recive.id;
                if(data_recive.effect!=effect)
                {
                  
                    key_recive=TRUE;
                    //printf("\n\r 1");
                   
                }
                else if(effect>=128 && (red!=data_recive.red || green!=data_recive.green || blue!=data_recive.blue))
                {
                  
                    key_recive=TRUE;
                    //printf("\n\r 2");
                     
                }
                else
                {
                  
                    sync_recive=TRUE;
                    //printf("\n\r 3");
                     
                }
                  
                //Serial.print("TRUE\r\n");
              }
          }
//          else
//          {
//              Serial.print("chk err\r\n");
//          }
        }
      //Serial.print("recive 2\r\n");  
    }
    
  
}
void wait_sync()
{
  byte EXIT=FALSE;
  unsigned int us_count=0,ms_count=0,wait_send_sync_count;
  Serial.print("wait_sync \r\n");
  digitalWrite(led, HIGH);
  wait_send_sync_count=(wait_send_sync_time+(send_paket_count*2)+14)*2;
  //printf("\n\r wait_sync ws=%i\n\r",wait_send_sync_count);
  while(EXIT==FALSE)
  {
      if(sync_recive==TRUE)
      {
          //printf("\n\r us=%i\n\r",us_count);
          radio.maskIRQ(1, 1, 1); // args = "data_sent", "data_fail", "data_ready"
           send_paket(data_recive,send_paket_count);
           
//           sync_id++;
//           if(red!=data_recive.red || green!=data_recive.green || blue!=data_recive.blue)
//           {
//            
//           }
           red=data_recive.red;
           green=data_recive.green;
           blue=data_recive.blue;
           radio.flush_rx();
           sync_recive=FALSE;
           radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"
           sync_count=0;
           EXIT=TRUE;  
      }
      if(key_recive==TRUE)
      {
        EXIT=TRUE;
      }
      
      
      delayMicroseconds(500);
      us_count++;
      if(us_count==wait_send_sync_count)
      {
        if(sync_count<sync_count_offset)
        {
          sync_count++; 
          delayMicroseconds(sync_count*1000);
          EXIT=TRUE;
        }
      }
      if(us_count%200==0)
      {
        strip.show(); 
        ms_count++;
        if(ms_count>15)
        {
          Serial.print("wait_sync \r\n");  
          ms_count=0;
        }
      }
  }
  digitalWrite(led, LOW);
}
void repate_sync()
{
    if(sync_recive==TRUE)
    {
        radio.maskIRQ(1, 1, 1); // args = "data_sent", "data_fail", "data_ready"
         send_paket(data_recive,send_paket_count);
         
         //sync_id++;
         red=data_recive.red;
         green=data_recive.green;
         blue=data_recive.blue;
         radio.flush_rx();
         sync_recive=FALSE;
         radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready"
          
    }
      
}
void clear_sync()
{
  radio.maskIRQ(1, 1, 1); // args = "data_sent", "data_fail", "data_ready" 
  sync_recive=FALSE;
  radio.flush_rx();
  radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready" 
}
void clear_buffer()
{
  radio.maskIRQ(1, 1, 1); // args = "data_sent", "data_fail", "data_ready" 
  //sync_recive=FALSE;
  radio.flush_rx();
  radio.maskIRQ(1, 1, 0); // args = "data_sent", "data_fail", "data_ready" 
}
