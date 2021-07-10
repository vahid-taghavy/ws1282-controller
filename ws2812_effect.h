
// Which pin on the Arduino is connected to the NeoPixels?
// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel strip(50, PIN, NEO_GRB + NEO_KHZ800);
volatile byte key_recive=FALSE,sync_recive=FALSE,sync_id=0;
//#define NUM_LEDS  NUMPIXELS
void showStrip() {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.show();
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   FastLED.show();
 #endif
}

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H
   // NeoPixel
   strip.setPixelColor(Pixel, strip.Color(red, green, blue));
 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}

void wait(int delay_time)
{
    int i;
    for(i=0;i<delay_time && key_recive==FALSE;i++)
    {
      if(i%50==0)
      {
        showStrip();  
      }
      delay(1);
    }
}

//void setAll(Adafruit_NeoPixel *pixels,byte red, byte green, byte blue) {
//  for(int i = 0; i < pixels->numPixels(); i++ ) {
//    pixels->setPixelColor(i,pixels->Color(red, green, blue));
//  }
//  pixels->show();
//}
void setAll(byte red, byte green, byte blue) {
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i = 0; i < NUM_LEDS; i++ ) {
    setPixel(i, red, green, blue);
  }
  showStrip();
}

void color_strip(Adafruit_NeoPixel *pixels,uint32_t color)
{
  int i;
  for(i=0;i<pixels->numPixels();i++)
  {
    pixels->setPixelColor(i,color);  
  }
  pixels->show();
}
void color_strip_range(Adafruit_NeoPixel *pixels,uint32_t color,uint16_t s,uint16_t e)
{
  int i;
  
  for(i=s;i<=e && i<pixels->numPixels();i++)
  {
    pixels->setPixelColor(i,color);    
  }
  pixels->show();
}
void iran_flag_effect(Adafruit_NeoPixel *pixels,byte mode)
{
  int s,a,b;
  a=pixels->numPixels()/3; 
  b=pixels->numPixels()%3;
  s=(2*a)+b;
  if(mode==normal)
  {
    color_strip_range(pixels,pixels->Color(255,0,0),0,a-1);
    color_strip_range(pixels,pixels->Color(255,255,255),a,s-1);
    color_strip_range(pixels,pixels->Color(0,255,0),s,pixels->numPixels());   
  }
  else
  {
    color_strip_range(pixels,pixels->Color(0,255,0),0,a-1);
    color_strip_range(pixels,pixels->Color(255,255,255),a,s-1);
    color_strip_range(pixels,pixels->Color(255,0,0),s,pixels->numPixels());
    
  }
  pixels->show();
}

void iran_flag_fade(Adafruit_NeoPixel *pixels,byte mode)
{
  int s,a,c;
  //float r, g, b;
  a=pixels->numPixels()/3; 
  c=pixels->numPixels()%3;
  s=(2*a)+c;  
  pixels->clear();
  if(mode==normal)
  {
     
    for(int k = 0; k < 256 && key_recive==FALSE; k=k+4) {
    
      color_strip_range(pixels,pixels->Color(k,0,0),0,a-1);
      color_strip_range(pixels,pixels->Color(k,k,k),a,s-1);
      color_strip_range(pixels,pixels->Color(0,k,0),s,pixels->numPixels()); 
      showStrip();
      delay(5);
    }
    wait(400);
//    for(int k = 0; k < 400 && key_recive==FALSE; k=k+1)
//    {
//      delay(1); 
//      if(k%50==0)
//      {
//        showStrip(); 
//      }
//    } 
    for(int k = 255; k >= 0 && key_recive==FALSE; k=k-4) {

      color_strip_range(pixels,pixels->Color(k,0,0),0,a-1);
      color_strip_range(pixels,pixels->Color(k,k,k),a,s-1);
      color_strip_range(pixels,pixels->Color(0,k,0),s,pixels->numPixels()); 
      showStrip();
      delay(5);
    }
    pixels->clear();
    showStrip();
  }
  else
  {
    for(int k = 0; k < 256 && key_recive==FALSE; k=k+4) {
      
      color_strip_range(pixels,pixels->Color(0,k,0),0,a-1);
      color_strip_range(pixels,pixels->Color(k,k,k),a,s-1);
      color_strip_range(pixels,pixels->Color(k,0,0),s,pixels->numPixels());
      showStrip();
      delay(5);
    }
//    for(int k = 0; k < 400 && key_recive==FALSE; k=k+1)
//    {
//      delay(1); 
//      if(k%50==0)
//      {
//        showStrip(); 
//      }
//    } 
    wait(400);
    for(int k = 255; k >= 0 && key_recive==FALSE; k=k-4) {

      color_strip_range(pixels,pixels->Color(0,k,0),0,a-1);
      color_strip_range(pixels,pixels->Color(k,k,k),a,s-1);
      color_strip_range(pixels,pixels->Color(k,0,0),s,pixels->numPixels());
      showStrip();
      delay(5);
    } 
    pixels->clear();
    showStrip();
  }
}


void iran_flag_open(Adafruit_NeoPixel *pixels,int SpeedDelay,int stopDelay,byte mode)
{
  int center,i,p_f,p_b;
  int s,a,b;
  a=pixels->numPixels()/3; 
  s=(2*a)+pixels->numPixels()%3;
  center=pixels->numPixels()/2; 
  b=pixels->numPixels()%2;
  pixels->clear();
  if(b!=0)
  {
    pixels->setPixelColor(center, pixels->Color(255,255,255));
    showStrip();
    delay(SpeedDelay); 
  }
  for(i=0;i<center && key_recive==FALSE;i++)
  {
    p_f=center+i+b;
    p_b=center-i-1;
    if(p_f>s-1)
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_f, pixels->Color(0,255,0)); 
      }
      else
      {
        pixels->setPixelColor(p_f, pixels->Color(255,0,0));   
      }
    }
    else
    {
      pixels->setPixelColor(p_f, pixels->Color(255,255,255)); 
    }
    if(p_b<a)
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_b, pixels->Color(255,0,0)); 
      }
      else
      {
        pixels->setPixelColor(p_f, pixels->Color(0,255,0)); 
      }
    }
    else
    {
      pixels->setPixelColor(p_b, pixels->Color(255,255,255));  
    }
    showStrip();
    delay(SpeedDelay);
     
  }
//  for(i=0;i<stopDelay/5 && key_recive==FALSE;i++)
//  {
//    delay(5);
//    if(i%10==0)
//    {
//        showStrip(); 
//    }
//  }
  wait(stopDelay);
  for(i=center-1;i>=0 && key_recive==FALSE;i--)
  {
    pixels->setPixelColor(center+i+b, pixels->Color(0,0,0));
    pixels->setPixelColor(center-i-1, pixels->Color(0,0,0)); 
    showStrip();
    delay(SpeedDelay);
  }
  if(b!=0)
  {
    pixels->setPixelColor(center, pixels->Color(0,0,0));
    showStrip();
    delay(SpeedDelay); 
  }  

}
void iran_flag_pixelbar(Adafruit_NeoPixel *pixels,int SpeedDelay,int stopDelay,byte mode)
{
  int i,p_r,p_g,p_w;
  int s,a,b;
  a=pixels->numPixels()/3; 
  b=pixels->numPixels()%3;
  s=(2*a)+b; 
  pixels->clear(); 
  p_r=0;
  p_w=a;
  p_g=s;
  for(i=0;i<(a+b) && key_recive==FALSE;i++)
  {
    if(p_r<a)
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_r, pixels->Color(255,0,0));
        
      }
      else
      {
        pixels->setPixelColor(p_r, pixels->Color(0,255,0));   
      }
      p_r++;
    }
    if(p_w<s)
    {
      pixels->setPixelColor(p_w, pixels->Color(255,255,255));
      p_w++;
    }
    if(p_g<pixels->numPixels())
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_g, pixels->Color(0,255,0));
        
      }
      else
      {
        pixels->setPixelColor(p_g, pixels->Color(255,0,0));   
      }
      p_g++;  
    }
    showStrip();
    wait(SpeedDelay);
  }
//  for(i=0;i<stopDelay/5 && key_recive==FALSE;i++)
//  {
//    delay(5);
//    if(i%10==0)
//    {
//        showStrip(); 
//    }
//  }
  wait(SpeedDelay);
}
void iran_flag_pixelbar_revers(Adafruit_NeoPixel *pixels,int SpeedDelay,int stopDelay,byte mode)
{
  int i,p_r,p_g,p_w;
  int s,a,b;
  a=pixels->numPixels()/3; 
  b=pixels->numPixels()%3;
  s=(2*a)+b; 
  pixels->clear(); 
  p_r=a-1;
  p_w=s-1;
  p_g=pixels->numPixels()-1;
  for(i=0;i<(a+b) && key_recive==FALSE;i++)
  {
    if(p_r>=0)
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_r, pixels->Color(255,0,0));
        
      }
      else
      {
        pixels->setPixelColor(p_r, pixels->Color(0,255,0));   
      }
      p_r--;
    }
    if(p_w>=a)
    {
      pixels->setPixelColor(p_w, pixels->Color(255,255,255));
      p_w--;
    }
    if(p_g>=s)
    {
      if(mode==normal)
      {
        pixels->setPixelColor(p_g, pixels->Color(0,255,0));
        
      }
      else
      {
        pixels->setPixelColor(p_g, pixels->Color(255,0,0));   
      }
      p_g--;  
    }
    showStrip();
    wait(SpeedDelay);
  }
//  for(i=0;i<stopDelay/5 && key_recive==FALSE;i++)
//  {
//    delay(5);
//    if(i%10==0)
//    {
//        showStrip(); 
//    }
//  }
  wait(SpeedDelay);    
}
void iran_flag_rainbar_revers(Adafruit_NeoPixel *pixels,int SpeedDelay,int stopDelay,byte mode)
{
  int i,j,r_start,r_end,w_start,w_end,g_start,g_end,r_p,g_p,w_p;
  int s,a,b;
  byte background_p=20;
  a=pixels->numPixels()/3; 
  b=pixels->numPixels()%3;
  s=(2*a)+b; 
  //pixels->clear(); 
  r_start=a-1;
  w_start=s-1;
  g_start=pixels->numPixels()-1;
  r_end=0;
  w_end=a;
  g_end=s;
  if(mode==normal)
  {
    color_strip_range(pixels,pixels->Color(background_p,0,0),0,a-1);
    color_strip_range(pixels,pixels->Color(background_p,background_p,background_p),a,s-1);
    color_strip_range(pixels,pixels->Color(0,background_p,0),s,pixels->numPixels());
    pixels->setPixelColor(r_start,pixels->Color(255,0,0));
    pixels->setPixelColor(g_start,pixels->Color(0,255,0)); 
  }
  else
  {
    color_strip_range(pixels,pixels->Color(background_p,0,0),0,a-1);
    color_strip_range(pixels,pixels->Color(background_p,background_p,background_p),a,s-1);
    color_strip_range(pixels,pixels->Color(0,background_p,0),s,pixels->numPixels());
    pixels->setPixelColor(r_start,pixels->Color(0,255,0));
    pixels->setPixelColor(g_start,pixels->Color(255,0,0)); 
  }
  pixels->setPixelColor(w_start,pixels->Color(255,255,255));
  for(i=0;i<=b;i++)
  {
    pixels->setPixelColor(w_start-i,pixels->Color(255,255,255)); 
  }
  w_start=w_start-b;
  
  
  showStrip();
  wait(SpeedDelay);
  for(i=(a-1);i>0 && key_recive==FALSE;i--)
  {
    //Serial.print("for1= "+(String)i+"\r\n");
    for(j=1;j<=i && key_recive==FALSE;j++)
    {
      //Serial.print("for2= "+(String)j+"\r\n");
      r_p=r_start-j;
      w_p=w_start-j;
      g_p=g_start-j;
      if(r_p>=r_end)
      {  
        if(mode==normal)
        { 
          pixels->setPixelColor(r_p,pixels->Color(255,0,0));  
          if(r_p+1!=r_start)
          {
            pixels->setPixelColor(r_p+1,pixels->Color(background_p,0,0));
          }
        }
        
      }
      if(w_p>=w_end)
      {  
        
        pixels->setPixelColor(w_p,pixels->Color(255,255,255));  
        
        if(w_p+1!=w_start)
        {
          pixels->setPixelColor(w_p+1,pixels->Color(background_p,background_p,background_p));
        }
      }
      if(g_p>=g_end)
      {  
        if(mode==normal)
        { 
          pixels->setPixelColor(g_p,pixels->Color(0,255,0));
          if(g_p+1!=g_start)
          {
            pixels->setPixelColor(g_p+1,pixels->Color(0,background_p,0));
          }  
        }
        
      }
      
      showStrip();
      wait(SpeedDelay);
    }
    r_end++;
    w_end++;
    g_end++;
    
  }
  wait(SpeedDelay);

}


//void test_color(Adafruit_NeoPixel *pixels)
//{
//  int s,a,b;
//  a=pixels->numPixels()/3; 
//  b=pixels->numPixels()%3;
//  s=(2*a)+b;
//  
//  color_strip_range(pixels,pixels->Color(255,0,0),0,a-1);
//  color_strip_range(pixels,pixels->Color(0,255,0),a,s-1);
//  color_strip_range(pixels,pixels->Color(0,0,255),s,pixels->numPixels());  
//   
//}

// Rainbow cycle along whole strip. Pass delay time (in ms) between frames.
void rainbow(int wait) {
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show(); // Update strip with new contents
    delay(wait);  // Pause for a moment
  }
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int stopDelay) {
  for(int i=0; i<strip.numPixels() && key_recive==FALSE; i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    wait(stopDelay);                           //  Pause for a moment
  }
}

// Theater-marquee-style chasing lights. Pass in a color (32-bit value,
// a la strip.Color(r,g,b) as mentioned above), and a delay time (in ms)
// between frames.
void theaterChase(uint32_t color, int wait) {
  for(int a=0; a<10; a++) {  // Repeat 10 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents
      delay(wait);  // Pause for a moment
    }
  }
}
// Rainbow-enhanced theater marquee. Pass delay time (in ms) between frames.
void theaterChaseRainbow(int wait) {
  int firstPixelHue = 0;     // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) {  // Repeat 30 times...
    for(int b=0; b<3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<strip.numPixels(); c += 3) {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / strip.numPixels();
        uint32_t color = strip.gamma32(strip.ColorHSV(hue)); // hue -> RGB
        strip.setPixelColor(c, color); // Set pixel 'c' to value 'color'
      }
      strip.show();                // Update strip with new contents
      delay(wait);                 // Pause for a moment
      firstPixelHue += 65536 / 90; // One cycle of color wheel over 90 frames
    }
  }
}


//The Cylon() function takes 6 parameters, where the first 3 are you preferred color (a Cylon has a red “eye”, but you can pick whatever you like with the Color Picker)
//The 4th parameter (EyeSize) determines how many LEDs run around, or: the width of the “eye” (outer 2, faded, LEDs not counted).
//The 5th parameter (SpeedDelay) influences how fast the eye moves, higher values means slow movement.
//The last parameter (ReturnDelay) sets how much time it should wait to bounce back
void CylonBounce(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i = 0; i < NUM_LEDS-EyeSize-2 && key_recive==FALSE; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }

  delay(ReturnDelay);

  for(int i = NUM_LEDS-EyeSize-2; i > 0 && key_recive==FALSE; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
 
  delay(ReturnDelay);
}

//void CylonBounce(Adafruit_NeoPixel *pixels,byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay){
//
//  for(int i = 0; i < pixels->numPixels()-EyeSize-2; i++) {
//    setAll(pixels,0,0,0);
//    pixels->setPixelColor(i,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      pixels->setPixelColor(i+j,pixels->Color(green,red,blue));
//      //setPixel(i+j, red, green, blue);
//    }
//    pixels->setPixelColor(i+EyeSize+1,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    pixels->show();
//    delay(SpeedDelay);
//  }
//
//  delay(ReturnDelay);
//
//  for(int i = pixels->numPixels()-EyeSize-2; i > 0; i--) {
//    setAll(pixels,0,0,0);
//    pixels->setPixelColor(i,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      pixels->setPixelColor(i+j,pixels->Color(green,red,blue));
//      //setPixel(i+j, red, green, blue);
//    }
//    pixels->setPixelColor(i+EyeSize+1,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    //showStrip();
//    pixels->show();
//    delay(SpeedDelay);
//  }
// 
//  delay(ReturnDelay);
//}
void CenterToOutside(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i =((NUM_LEDS-EyeSize)/2); i>=0 && key_recive==FALSE; i--) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize && key_recive==FALSE; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void OutsideToCenter(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i = 0; i<=((NUM_LEDS-EyeSize)/2) && key_recive==FALSE ; i++) {
    setAll(0,0,0);
   
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
   
    setPixel(NUM_LEDS-i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize && key_recive==FALSE; j++) {
      setPixel(NUM_LEDS-i-j, red, green, blue);
    }
    setPixel(NUM_LEDS-i-EyeSize-1, red/10, green/10, blue/10);
   
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void LeftToRight(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i = 0; i < NUM_LEDS-EyeSize-2 && key_recive==FALSE; i++) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

void RightToLeft(byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int i = NUM_LEDS-EyeSize-2; i > 0 && key_recive==FALSE; i--) {
    setAll(0,0,0);
    setPixel(i, red/10, green/10, blue/10);
    for(int j = 1; j <= EyeSize; j++) {
      setPixel(i+j, red, green, blue);
    }
    setPixel(i+EyeSize+1, red/10, green/10, blue/10);
    showStrip();
    delay(SpeedDelay);
  }
  delay(ReturnDelay);
}

//void LeftToRight(Adafruit_NeoPixel *pixels,byte red, byte green, byte blue, int EyeSize, int SpeedDelay, int ReturnDelay) {
//  for(int i = 0; i < pixels->numPixels()-EyeSize-2; i++) {
//    setAll(pixels,0,0,0);
//    pixels->setPixelColor(i,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i, red/10, green/10, blue/10);
//    for(int j = 1; j <= EyeSize; j++) {
//      pixels->setPixelColor(i+j,pixels->Color(green,red,blue));
//      //setPixel(i+j, red, green, blue);
//    }
//    pixels->setPixelColor(i+EyeSize+1,pixels->Color(green/10, red/10, blue/10));
//    //setPixel(i+EyeSize+1, red/10, green/10, blue/10);
//    //showStrip();
//    pixels->show();
//    delay(SpeedDelay);
//  }
//  delay(ReturnDelay);
//}

void FadeInOut(byte red, byte green, byte blue){
  float r, g, b;
     
  for(int k = 0; k < 256 && key_recive==FALSE; k=k+1) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(4);
  }
  wait(200);
  for(int k = 255; k >= 0 && key_recive==FALSE; k=k-2) {
    r = (k/256.0)*red;
    g = (k/256.0)*green;
    b = (k/256.0)*blue;
    setAll(r,g,b);
    showStrip();
    delay(4);
  }
}

//It takes 4 parameters, of which the first 3 define the color (roughly).
//The last parameter indicates how much delay is put in the loop, the higher the number, the slower it will go.

void RunningLights(byte red, byte green, byte blue, int WaveDelay) {
  int Position=0;
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for(int j=0; j<NUM_LEDS*2 && key_recive==FALSE; j++)
  {
      Position++; // = 0; //Position + Rate;
      for(int i=0; i<NUM_LEDS; i++) {
        // sine wave, 3 offset waves make a rainbow!
        //float level = sin(i+Position) * 127 + 128;
        //setPixel(i,level,0,0);
        //float level = sin(i+Position) * 127 + 128;
        setPixel(i,((sin(i+Position) * 127 + 128)/255)*red,
                   ((sin(i+Position) * 127 + 128)/255)*green,
                   ((sin(i+Position) * 127 + 128)/255)*blue);
      }
     
      showStrip();
      wait(WaveDelay);
  }
}

void BouncingBalls(byte red, byte green, byte blue, int BallCount) {
  float Gravity = -9.81;
  int StartHeight = 1;
 
  float Height[BallCount];
  float ImpactVelocityStart = sqrt( -2 * Gravity * StartHeight );
  float ImpactVelocity[BallCount];
  float TimeSinceLastBounce[BallCount];
  int   Position[BallCount];
  long  ClockTimeSinceLastBounce[BallCount];
  float Dampening[BallCount];
  int NUM_LEDS;
  NUM_LEDS=strip.numPixels();
  for (int i = 0 ; i < BallCount ; i++) {  
    ClockTimeSinceLastBounce[i] = millis();
    Height[i] = StartHeight;
    Position[i] = 0;
    ImpactVelocity[i] = ImpactVelocityStart;
    TimeSinceLastBounce[i] = 0;
    Dampening[i] = 0.90 - float(i)/pow(BallCount,2);
  }

  while (true) {
    for (int i = 0 ; i < BallCount ; i++) {
      TimeSinceLastBounce[i] =  millis() - ClockTimeSinceLastBounce[i];
      Height[i] = 0.5 * Gravity * pow( TimeSinceLastBounce[i]/1000 , 2.0 ) + ImpactVelocity[i] * TimeSinceLastBounce[i]/1000;
 
      if ( Height[i] < 0 ) {                      
        Height[i] = 0;
        ImpactVelocity[i] = Dampening[i] * ImpactVelocity[i];
        ClockTimeSinceLastBounce[i] = millis();
 
        if ( ImpactVelocity[i] < 0.01 ) {
          ImpactVelocity[i] = ImpactVelocityStart;
        }
      }
      Position[i] = round( Height[i] * (NUM_LEDS - 1) / StartHeight);
    }
 
    for (int i = 0 ; i < BallCount ; i++) {
      setPixel(Position[i],red,green,blue);
    }
   
    showStrip();
    setAll(0,0,0);
  }
}

void rain(byte red, byte green, byte blue,int DropSize,int speace_num, int SpeedDelay)
{
 int x,j,i;
 uint32_t color;
 float r, g, b;
 int NUM_LEDS;
 NUM_LEDS=strip.numPixels();
 x=255/DropSize;
 for(i = 255; i>0 && key_recive==FALSE; i=i-x) 
 {
    for(j=NUM_LEDS-1;j>0 && key_recive==FALSE;j--)
    {
      strip.setPixelColor(j, strip.getPixelColor(j-1)); 
    }
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    setPixel(0, r, g, b);
    showStrip();
    wait(SpeedDelay);
 }
 for(i=0;i<speace_num && key_recive==FALSE;i++)
 {
   for(j=NUM_LEDS-1;j>0 && key_recive==FALSE;j--)
      {
        strip.setPixelColor(j, strip.getPixelColor(j-1)); 
      }
   setPixel(0, 0, 0, 0);
   showStrip();
   wait(SpeedDelay);
 }
 
 
}
void rain_revers(byte red, byte green, byte blue,int DropSize,int speace_num, int SpeedDelay)
{
 int x,j,i;
 uint32_t color;
 float r, g, b;
 int NUM_LEDS;
 NUM_LEDS=strip.numPixels();
 x=255/DropSize;
 for(i = 255; i>0 && key_recive==FALSE; i=i-x) 
 {
    for(j=1;j<NUM_LEDS && key_recive==FALSE;j++)
    {
      strip.setPixelColor(j-1, strip.getPixelColor(j)); 
    }
    r = (i/256.0)*red;
    g = (i/256.0)*green;
    b = (i/256.0)*blue;
    setPixel(NUM_LEDS-1, r, g, b);
    showStrip();
    wait(SpeedDelay);
 }
 for(i=0;i<speace_num && key_recive==FALSE;i++)
 {
   for(j=1;j<NUM_LEDS && key_recive==FALSE;j++)
      {
        strip.setPixelColor(j-1, strip.getPixelColor(j)); 
      }
   setPixel(NUM_LEDS-1, 0, 0, 0);
   showStrip();
   wait(SpeedDelay);
   
 }
 
}
