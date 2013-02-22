/* Includes for menu processing.
 * Revised from - www.nuelectronics.com/download/projects/nokia_3310_lcd_180110.zip
 * Do not Auto Format
 */ 

//keypad debounce parameter
#define DEBOUNCE_MAX   15
#define DEBOUNCE_ON    10
#define DEBOUNCE_OFF   3 
#define NUM_KEYS       5
#define NUM_MENU_ITEM  6               // max is 6
// menu starting points
#define MENU_X	   4                   // 0-83
#define MENU_Y	   0                   // 0-5


// Joystick key numbers - set up for the way my switch is wired
#define UP_KEY     0                    // analogRead = 0
#define CENTER_KEY 1                    // analogRead = 888
///#define LEFT_KEY   2                    // analogRead = 918
#define DOWN_KEY   2                    // 2analogRead = 943
#define RIGHT_KEY  3                    // 3analogRead = 979

                                        // no key - analogRead = 1023
                                        
// Max adc value for each key. Key is ID's if the analog read is LESS than these 
// when a key is pressed - set noise & margin = 30 (0.15V@5V)
//int  adc_key_val[5] ={                  // analogRead for key must be < value
  //50, 200, 375, 550, 800 };
int  adc_key_val[4] ={                  // analogRead for key must be < value
  50, 900, 950, 990 };                  // removed
byte button_count[NUM_KEYS];            // debounce counters
byte button_status[NUM_KEYS];           // button status - pressed/released
byte button_flag[NUM_KEYS];             // button on flags for user program 
char current_menu_item;

// menu definition
char menu_items[NUM_MENU_ITEM][14]={
  "COMPASS      ",
  "PERFORMANCE  ",
  "ACCELEROMETER",
  "ROLL & PITCH ",
  "DEBUG DISPLAY",
  "CALIBRATE    "
};

// For LCD Drawing lines and boxes
int pixels[85][6] = {{0}};
// menu starting points
#define BAR_X	   0                    // X position of upper left of bar (0-83)
#define BAR_Y	   25                   // Y position of upper left of bar (0-48)
#define BAR_W	   83                   // Width of bar (0-83)
#define BAR_H	   10                   // Hieght of bar (0-48)
