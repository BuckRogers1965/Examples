/* Functions for drawing lines, boxes and ellipse.
 * Lines & box revised from kuk's - http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1200398529/16#16
 * ellipse revised from   // from MauJaber / John Kennedy
 * ex.  PlotEllipse(40,20,40,10);
 */


void initProgressBar() {
  clearPixels();
  drawRect(BAR_X,BAR_Y,BAR_W,BAR_H); //(x,y,w,h) Start at x,y of width w and height h
}


void setProgressBar(int value) {
  for (int i=0;i<abs(value);i++){ 
    if (value >1) drawVerticalLine(BAR_X+(BAR_W/2)+i,BAR_Y,BAR_H); // bars to right
             else drawVerticalLine(BAR_X+(BAR_W/2)-i,BAR_Y,BAR_H); // bars to left
  }
}


void clearPixels() {
  for (int x=0;x<83;x++) {  // SB 84?
    for(int y=0;y<47;y++) { // SB 48?
      pixels[x][y] = 0;
    }
  }
}


// Enable (d=1) or disable (d=0) a specific pixel
// x: 0 to 84, y: 0 to 48
void setPixel(int x, int y, int d) {
  if (x > 84 || y > 48) return; 
  // The LCD has 6 rows, with 8 pixels per  row.
  // 'y_mod' is the row that the pixel is in.
  // 'y_pix' is the pixel in that row we want to enable/disable
  int y_mod = (int)(y >> 3);	// >>3 divides by 8
  int y_pix = (y-(y_mod << 3));// <<3 multiplies by 8
  int val = 1 << y_pix;

  /// We have to keep track of which pixels are on/off in order to
  // write the correct character out to the LCD.
  if (d) pixels[x][y_mod] |= val; 
  else pixels[x][y_mod] &= ~val;

  // Write the updated pixel out to the LCD
  lcd.LCD_3310_set_XY(x,y_mod);
  lcd.LCD_3310_write_byte(pixels[x][y_mod],DEC);
}


// Draw a rectangle of width w and height h from x,y Use clearPixels() first
void drawRect(int x, int y, int w, int h){
  drawHorizontalLineXY(x,x+w,y);
  drawHorizontalLineXY(x,x+w,y+h);
  drawVerticalLineXY(y,y+h,x);
  drawVerticalLineXY(y,y+h,x+w);
}


// Draw a horizontal line between x1 and x2 at row y
void drawHorizontalLineXY(int x1, int x2, int y){
  for (int i=x1;i<=x2;i++) {
    setPixel(i,y,1);
  }
}


// Draw a vertical line of height h from x,y  TODO CAN ELIMINATE THIS _ CALL WITH Y+H
void drawVerticalLine(int x, int y, int h){
  drawVerticalLineXY(y,y+h,x);
}


// Draw a vertical line from y1 to y2 on column x
void drawVerticalLineXY(int y1, int y2, int x){
  for (int i=y1;i<=y2;i++) {
    setPixel(x,i,1);
  }
}


void PlotEllipse(long CX, long  CY, long XRadius,long YRadius) {
  // from MauJaber / John Kennedy
  // C-X/Y are center point of ellipse, X/YRadius are horizontal and vertical Radius
  // portted the algorithm found at http://homepage.smc.edu/kennedy_john/belipse.pdf

  long X, Y;
  long XChange, YChange;
  long EllipseError;
  long TwoASquare,TwoBSquare;
  long StoppingX, StoppingY;
  TwoASquare = 2*XRadius*XRadius;
  TwoBSquare = 2*YRadius*YRadius;
  X = XRadius;
  Y = 0;
  XChange = YRadius*YRadius*(1-2*XRadius);
  YChange = XRadius*XRadius;
  EllipseError = 0;
  StoppingX = TwoBSquare*XRadius;
  StoppingY = 0;

  while ( StoppingX >=StoppingY ){ //first set of points,y'>-1
    DispEllipse(CX,CY,X,Y);
    Y++;
    StoppingY=StoppingY+ TwoASquare;
    EllipseError = EllipseError+ YChange;
    YChange=YChange+TwoASquare;
    if ((2*EllipseError + XChange) > 0 ) {
      X--;
      StoppingX=StoppingX- TwoBSquare;
      EllipseError=EllipseError+ XChange;
      XChange=XChange+TwoBSquare;
    }
  }
  //{ first point set is done; start the 2nd set of points }

  Y = YRadius;
  X = 0;
  YChange = XRadius*XRadius*(1-2*YRadius);
  XChange = YRadius*YRadius;
  EllipseError = 0;
  StoppingY = TwoASquare*YRadius;
  StoppingX = 0;
  while ( StoppingY >=StoppingX ){ //{2nd set of points, y'< -1}
    DispEllipse(CX,CY,X,Y);
    X++;
    StoppingX=StoppingX + TwoBSquare;
    EllipseError=EllipseError+ XChange;
    XChange=XChange+TwoBSquare;
    if ((2*EllipseError + YChange) > 0 ) {
      Y--;
      StoppingY=StoppingY- TwoASquare;
      EllipseError=EllipseError+ YChange;
      YChange=YChange+TwoASquare;
    }
  }
}


void DispEllipse(long CX,long  CY,long X,long Y){
  setPixel(CX+X,CY+Y,1);          //{point in quadrant 1}
  setPixel(CX-X,CY+Y,1);          //{point in quadrant 2}
  setPixel(CX-X,CY-Y,1);          //{point in quadrant 3}
  setPixel(CX+X,CY-Y,1);          //{point in quadrant 4}
}

void DiagLine(int x1,int y1,int x2,int y2){ // NEEDS WORK!
  // Basic line draw - start point x1/y1, end point x2/y2 
  // DiagLine(42,45,80,10);  // example call
  for (int i= x1; i<x2;i++){  // loop on x first (assumes Cx < x)
    for (int j= y2; i<y1;j++){  // then y (assumes y < Cy)
      setPixel(i,j,1);
    }
  }
}



