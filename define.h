#define TRUE	1
#define FALSE	0

#define normal  1
#define revese  100
#define   effect_add   10
#define red_add   14
#define green_add 18
#define blue_add  22
#define message_size  6
#define set_effect_header   '$'
#define set_effect      's'

#define sync_header   '@'
#define wait_send_sync_time 85 //ms
#define send_paket_count  7
#define sync_count_offset   10
#define delay_ms(x)	delay(x)

#define PIN        PIN_PD4 // On Trinket or Gemma, suggest changing this to 1
#define D0         PIN_PA0
#define D1         PIN_PA1
#define D2         PIN_PA2
#define D3         PIN_PA3
#define ac_pulse   PIN_PD2
#define led        PIN_PA4


// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 40 // Popular NeoPixel ring size

//#define DELAYVAL 100// Time (in milliseconds) to pause between pixels

#define delay_offset	10
