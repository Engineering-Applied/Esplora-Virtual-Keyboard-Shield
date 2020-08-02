/*Keyboard Emulator
 * By: Joshua Harrell
 * University of North Florida
 * Created and calibrated v1.0 9/4/19
 * Revised for Nano board and recalibration v1.1 9/28/19
 */
 // #include <Adafruit_Thermal.h>       
//  #include <Adafruit_GFX.h>           
//  #include <Adafruit_SPITFT.h>        
//  #include <Adafruit_SPITFT_Macros.h> 
//  #include <gfxfont.h>                 
  #include <Adafruit_FT6206.h>       // TouchScreen Library
//  #include <Adafruit_ILI9341.h>     // Hardware-specific library
//  #include <Adafruit_ImageReader.h>

/*Here are the pins used for Mouse Functions*/
/*const int LEFT_BUTTON = 4;
const int MIDDLE_BUTTON = 3;
const int RIGHT_BUTTON = 2;
const int X_AXIS = 1;
const int Y_AXIS = 0;
const int SENS = 5;
const int SENS_LED = 9; */

/*Here are the pins for the LCD functions */
//  const int CARD_SELECT = 8;
//  const int DATA_COMMAND = 0;               
//  const int LCD_SELECT = 7;
    const int Screen_Switch = 7;       // Sets Screen Switching control to pin 7

/*Here are the Virtual Mouse/Keyboard Libraries */
//  #include <Mouse.h>
  #include <Keyboard.h>                     
  
/*Here we are instantiating the ImageReader and TFT */
//  Adafruit_ILI9341 tft = Adafruit_ILI9341(LCD_SELECT, DATA_COMMAND);    // creates LCD object
//  Adafruit_ImageReader sd;
//  Adafruit_Image img;
  Adafruit_FT6206 touch = Adafruit_FT6206();        // creates touchscreen object
//  uint32_t width = 320, height = 240;
boolean alternate = 0;

void setup() {
//  Mouse.begin();
  Keyboard.begin();
  Serial.begin(9600);
//  tft.begin();
  touch.begin(40);  // begins and sets touchscreen sensitivity to 40 (0-255)
//  pinMode(SENS_LED, OUTPUT);  
//  pinMode(CARD_SELECT, OUTPUT);
//  pinMode(DATA_COMMAND, OUTPUT); 
//  pinMode(LCD_SELECT, OUTPUT);
    pinMode(Screen_Switch, OUTPUT);
//  ImageReturnCode stat;    

/*Serial Monitor SD card checker */
/*  Serial.print(F("Initializing SD card..."));
  if(!SD.begin(CARD_SELECT)) {
    Serial.println(F("failed!"));
    for(;;); // Loop here forever
  }
  Serial.println(F("OK!")); */
  
/*  tft.fillScreen(ILI9341_BLUE); // starts with a blue screen to verify working
  tft.setRotation(1);           // sets correct picture orientation
  stat = sd.drawBMP("/keyboard.bmp", tft, 0, 0);
  stat = sd.bmpDimensions("/keyboard.bmp", &width, &height);
  stat = sd.loadBMP("/keyboard.bmp", img);
  tft.setCursor(10, 6);        // Exact position for Keyboard typing line
  tft.setTextSize(2);          // Sets good size for text on line
  tft.setTextColor(ILI9341_BLACK);  // sets text color to black
  tft.println("Type in your input here"); 
 */ 
}

void loop() {
  if (touch.touched()) {
    delay(50);                //added delay for verifying human touch
    if (touch.touched()) {
    TS_Point p = touch.getPoint();                          
   /* Serial.println("You have been touched!");
    Serial.print("The X coordinate is \t"), Serial.println(p.x);     //Used for calibration
    Serial.print("The Y coordinate is \t"), Serial.println(p.y); */
   if (!alternate) {
    if ((p.x > 40) && (p.x < 67)) {        // Calibration v1.1
      sendTopChar(p.y, 0) ;
    }
    if ((p.x > 95) && (p.x < 125)) {       // Calibration v1.1
      sendMidChar(p.y, 0) ;
    }
    if ((p.x > 144) && (p.x < 190)) {      // Calibration v1.1
      sendBotChar(p.y, 0) ;
    } 
    if ((p.x > 195) && (p.x < 240)) {      // Calibration v1.1
      sendSpaceChar(p.y, 0) ;
    } 
   }
   if (alternate) {
    if ((p.x > 60) && (p.x < 90)) {        // Calibration v1.2   10/4/19
      sendTopChar(p.y, 1) ;
    }
    if ((p.x > 100) && (p.x < 148)) {       // Calibration v1.2  10/4/19
      sendMidChar(p.y, 1) ;
    }
    if ((p.x > 144) && (p.x < 190)) {      // Calibration v1.2   10/4/19
      sendBotChar(p.y, 1) ;
    } 
    if ((p.x > 196) && (p.x < 232)) {      // Calibration v1.2   10/4/19
      sendSpaceChar(p.y, 1) ;
    } 
   }
  }
  
/*  int xVal = readJoystick(X_AXIS);
  int yVal = readJoystick(Y_AXIS);
  int sensitivity = analogRead(SENS);                    // reads pot for input sensitivity
  int LED = map(sensitivity, 1023, 0, 0, 255);               // whenever max sensitvity, the LED gets brighter 
  sensitivity = map(sensitivity, 0, 1023, 0, 25);      // increased value causes slower mouse feedback
  analogWrite(SENS_LED, LED);

  Mouse.move(xVal, yVal, 0);

  readButton(LEFT_BUTTON, MOUSE_LEFT);
  readButton(MIDDLE_BUTTON, MOUSE_MIDDLE);
  readButton(RIGHT_BUTTON, MOUSE_RIGHT);
  delay(sensitivity);
*/
 }
 digitalWrite(Screen_Switch, HIGH);
}

/*
  Verified by Keyboard Calibration v1.1
*/
void sendTopChar(int y, boolean type)
{
 if (!type){ 
  if ((y > 305) && (y < 322))
    Keyboard.write('q'); 
  if ((y > 248) && (y < 281))
    Keyboard.write('w'); 
  if ((y > 228) && (y < 248))
    Keyboard.write('e'); 
  if ((y > 198) && (y < 220))
    Keyboard.write('r'); 
  if ((y > 168) && (y < 186))
    Keyboard.write('t'); 
  if ((y > 140) && (y < 155))
    Keyboard.write('y'); 
  if ((y > 100) && (y < 121))
    Keyboard.write('u'); 
  if ((y > 74) && (y < 93))
    Keyboard.write('i'); 
  if ((y > 52) && (y < 68))
    Keyboard.write('o');
  if ((y > 0) && (y < 20))
    Keyboard.write('p');
 }
 if (type) {                  // MS Paint Calibration v1.2
  if ((y > 292) && (y < 322))
    Keyboard.write('1');
  if ((y > 256) && (y < 290))
    Keyboard.write('2');
  if ((y > 225) && (y < 255))
    Keyboard.write('3');
  if ((y > 192) && (y < 224))
    Keyboard.write('4');
  if ((y > 162) && (y < 191))
    Keyboard.write('5');
  if ((y > 129) && (y < 161))
    Keyboard.write('6');
  if ((y > 98) && (y < 128))
    Keyboard.write('7');
  if ((y > 66) && (y < 97))
    Keyboard.write('8');
  if ((y > 35) && (y < 65))
    Keyboard.write('9');
  if ((y > 6) && (y < 33))
    Keyboard.write('0');
 }
}

/*
  Verified by Keyboard Calibration v1.1
*/
void sendMidChar(int y, boolean type){
 if (!type){
  if ((y > 288) && (y < 308))
    Keyboard.write('a'); 
  if ((y > 248) && (y < 265))
    Keyboard.write('s'); 
  if ((y > 216) && (y < 235))
    Keyboard.write('d'); 
  if ((y > 186) && (y < 205))
    Keyboard.write('f'); 
  if ((y > 155) && (y < 171))
    Keyboard.write('g'); 
  if ((y > 125) && (y < 140))
    Keyboard.write('h'); 
  if ((y > 90) && (y < 107))
    Keyboard.write('j'); 
  if ((y > 58) && (y < 75))
    Keyboard.write('k'); 
  if ((y > 24) && (y < 50))
    Keyboard.write('l');
 }
 if (type) {
  if ((y > 290) && (y < 322))
    Keyboard.write('@');
  if ((y > 256) && (y < 290))
    Keyboard.write('#');
  if ((y > 225) && (y < 255))
    Keyboard.write('$');
  if ((y > 192) && (y < 224))
    Keyboard.write('%');
  if ((y > 162) && (y < 191))
    Keyboard.write('&');
  if ((y > 130) && (y < 161))
    Keyboard.write('-');
  if ((y > 98) && (y < 130))
    Keyboard.write('+');
  if ((y > 66) && (y < 97))
    Keyboard.write('(');
  if ((y > 35) && (y < 65))
    Keyboard.write(')');
  if ((y > 5) && (y < 34))
    Keyboard.write('/');
 }
}
/*
  Verified by Keyboard Calibration v1.1
*/
void sendBotChar(int y, boolean type){
 if (!type){
  if ((y > 290) && (y < 321))
    Keyboard.write(193);      //keyboard Caps-Lock defined by Arduino special characters
  if ((y > 250) && (y < 268))
    Keyboard.write('z'); 
  if ((y > 217) && (y < 232))
    Keyboard.write('x'); 
  if ((y > 180) && (y < 202))
    Keyboard.write('c'); 
  if ((y > 150) && (y < 179))
    Keyboard.write('v'); 
  if ((y > 125) && (y < 140))
    Keyboard.write('b'); 
  if ((y > 90) && (y < 110))
    Keyboard.write('n'); 
  if ((y > 58) && (y < 80))
    Keyboard.write('m'); 
  if ((y > 0) && (y < 50))
    Keyboard.write(178);    //keyboard Backspace defined by Arduino special characters
 }
 if (type) {
  if ((y > 294) && (y < 320))
    Keyboard.write('<');
  if ((y > 269) && (y < 292))
    Keyboard.write('>');
  if ((y > 242) && (y < 268))
    Keyboard.write('*');
  if ((y > 210) && (y < 240))
    Keyboard.write('"');
  if ((y > 178) && (y < 209))
    Keyboard.write(0x27);       //Keyboard " ' "
  if ((y > 145) && (y < 178))
    Keyboard.write(':');
  if ((y > 114) && (y < 144))
    Keyboard.write(';');
  if ((y > 83) && (y < 114))
    Keyboard.write('!');
  if ((y > 51) && (y < 82))
    Keyboard.write('?');
  if ((y > 6) && (y < 48))
    Keyboard.write(178);      // Keyboard Backspace defined by Arduino special character
 }
}

/*
  Verified by Keyboard Calibration v1.1
*/
void sendSpaceChar(int y, boolean type){
 if (!type){
  if ((y > 280) && (y < 321))
    //Serial.write('1'); 
    digitalWrite(Screen_Switch, LOW);
    delay(20);
    alternate = 1;      
  if ((y > 65) && (y < 262))
    Keyboard.write(32);       //keyboard SPACE     defined by Ascii characters 
  if ((y > 5) && (y < 51))
    Keyboard.write(176);       //keyboard RETURN    defined by Arduino special characters https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
 }
 if (type) {
  if ((y > 273) && (y < 317))
    //Serial.write('0');           // Tells Nano to display main keyboard screen
    digitalWrite(Screen_Switch, LOW);
    delay(5);
    alternate = 0;
  if ((y > 245) && (y < 273))
    Keyboard.write(',');
  if ((y > 211) && (y < 244))
    //Serial.write('0');           // Tells Nano to display main keyboard screen
    digitalWrite(Screen_Switch, LOW);
    delay(5);
    alternate = 0;
  if ((y > 121) && (y < 203))
    Keyboard.write(' ');
  if ((y > 79) && (y < 114))
    Keyboard.write('=');
  if ((y > 50) && (y < 78))
    Keyboard.write('.');
  if ((y > 6) && (y < 50))
    Keyboard.write(176);      //keyboard RETURN    defined by Arduino special characters https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
 }
}
/*int readJoystick(int axis) {
  int val = analogRead(axis);
  val = map(val, 0, 1023, -10, 10);           Used for mouse joystick

  if (val <= 2 && val >= -2)
    return 0;    
   else {
    return val;
  }
} */

/*void readButton(int pin, char mouseCommand) {
  if (digitalRead(pin) == HIGH) {
    if (!Mouse.isPressed(mouseCommand)) {      Use for mouse buttons
      Mouse.press(mouseCommand);
    }
  } else {
    if (Mouse.isPressed(mouseCommand)) {
      Mouse.release(mouseCommand);
    }
  }
} */
