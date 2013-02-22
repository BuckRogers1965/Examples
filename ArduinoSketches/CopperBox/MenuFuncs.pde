/* Menu functions for menu processing.
 * Revised from - www.nuelectronics.com/download/projects/nokia_3310_lcd_180110.zip
 * lcd related routines . . .
 *  LCD_3310_init() - to init display
 *  LCD_3310_write_byte(dat,dat_type) - dat_type ?
 *  LCD_3310_draw_bmp_pixel(X,Y,bmp name,#Pix_x,#Pix_y)
 *  LCD_3310_write_string(X,Y,stringname,normal(0)/highlight(1)) 6x14 char
 *  LCD_3310_write_string_big (X,Y,stringname,normal(0)/highlight(1))
 *  LCD_3310_write_char_big (X,Y,unsigned char name,normal(0)/highlight(1)) - 1 ASCII Char
 *  LCD_3310_write_char(unsigned char name,normal(0)/highlight(1)) - 1 ASCII Char
 *  LCD_3310_set_XY(X,Y);
 *  LCD_3310_clear(void);
 */

void init_MENU(){
  byte i;
  lcd.LCD_3310_clear();
  lcd.LCD_3310_write_string(MENU_X, MENU_Y, menu_items[0], MENU_HIGHLIGHT );
  for (i=1; i<NUM_MENU_ITEM; i++){
    lcd.LCD_3310_write_string(MENU_X, MENU_Y+i, menu_items[i], MENU_NORMAL);
  }
}


void waitfor_OK(){  // waiting for center key press
  byte i;
  byte key = 0xFF;

  while (key!= CENTER_KEY){
    for(i=0; i<NUM_KEYS; i++){
      if(button_flag[i] !=0){
        button_flag[i]=0;  // reset button flag
        if(i== CENTER_KEY) key=CENTER_KEY;
      }
    }
  }
}


byte OK_Pressed(){  // test if OK was pressed while in menu function
  byte i;
  byte key = 0xFF;
    for(i=0; i<NUM_KEYS; i++){
      if(button_flag[i] !=0){
        button_flag[i]=0;  // reset button flag
        if(i== CENTER_KEY) return true;
      }
    }
return false;
}


 void reset_buttons(){
  for(byte i=0; i<NUM_KEYS; i++){
    button_count[i]=0;
    button_status[i]=0;
    button_flag[i]=0;
  }
}

// The following are interrupt-driven keypad reading functions
//  which includes DEBOUNCE ON/OFF mechanism, and continuous pressing detection
void update_adc_key(){  // called by ISR - setup by TIMER2_OVF_vect
  int adc_key_in;
  char key_in;
  byte i;

  adc_key_in = analogRead(JOYSTICK_PIN);
//Serial.println (adc_key_in);
//delay(1000);
  key_in = get_key(adc_key_in);         // ID key based on it's analog value
  for(i=0; i<NUM_KEYS; i++) {           // loop through keytypes
    if(key_in==i) {                     //one key is pressed 
      if(button_count[i]<DEBOUNCE_MAX) {
        button_count[i]++;
        if(button_count[i]>DEBOUNCE_ON) {
          if(button_status[i] == 0) {
            button_flag[i] = 1;
            button_status[i] = 1;       //button debounced to 'pressed' status
          }
        }
      }
    }
    else {   // no button pressed
      if (button_count[i] >0) {  
        button_flag[i] = 0;	
        button_count[i]--;
        if(button_count[i]<DEBOUNCE_OFF){
          button_status[i]=0;           //button debounced to 'released' status
        }
      }
    }
  }
}


char get_key(unsigned int input){ // Convert ADC value to key number
  char k;
  for (k = 0; k < NUM_KEYS; k++) {
    if (input < adc_key_val[k])  {
      return k;
    }
  }
  if (k >= NUM_KEYS) k = -1;            // No valid key pressed
  return k;
}


void SetupInterrupt(){   //setup Timer2 interrupt routine
  // Setup timer2 -- Prescaler/256
  TCCR2A &= ~((1<<WGM21) | (1<<WGM20));
  TCCR2B &= ~(1<<WGM22);
  TCCR2B = (1<<CS22)|(1<<CS21);      
  ASSR |=(0<<AS2);
  TCCR2A =0;                            // Use normal mode  
  TIMSK2 |= (0<<OCIE2A);               //Timer2 Overflow Interrupt Enable  
  TCNT2=0x6;                            // counting starts from 6;  
  TIMSK2 = (1<<TOIE2);    
  SREG|=1<<SREG_I;
}


// Timer2 interrupt routine -
// 1/(160000000/256/(256-6)) = 4ms interval  NOTE: ADJ IF RUNNING AT 8MHz
ISR(TIMER2_OVF_vect) {  
  TCNT2  = 6;
  update_adc_key();
}

void toString (int bValue, char *pString){ // converts a byte to the string passed
// TEST USING AN INT HERE
// If needed, make another func that appends a byte to the passed string
  memset(pString,'\0',sizeof(pString));
  itoa(bValue,pString,10);
}
