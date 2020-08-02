/*Keyboard Emulator
 * By: Joshua Harrell
 * University of North Florida
 * Created and calibrated 9/4/19
 */
//  #include <Adafruit_Thermal.h> 
  #include <SPI.h>
  #include <SD.h>      
  #include <Adafruit_GFX.h>           
  #include <Adafruit_SPITFT.h>        
  #include <Adafruit_SPITFT_Macros.h> 
  #include <gfxfont.h>                 
//  #include <Adafruit_FT6206.h>       // TouchScreen Library
  #include <Adafruit_ILI9341.h>     // Hardware-specific library
  #include <Adafruit_ImageReader.h>

/*Here are the pins used for Mouse Functions*/
/*const int LEFT_BUTTON = 4;
const int MIDDLE_BUTTON = 3;
const int RIGHT_BUTTON = 2;
const int X_AXIS = 1;
const int Y_AXIS = 0;
const int SENS = 5;
const int SENS_LED = 9; */

/*Here are the pins for the LCD functions */
  const int CARD_SELECT = 5;    // Nano Digital 5
  const int DATA_COMMAND = 4;   // Nano Digital 4            
  const int LCD_SELECT = 3;     // Nano Digital 3
  const int Screen_Switch = 2;  // Nano Digital 2

/*Here are the Virtual Mouse/Keyboard Libraries */
//  #include <Mouse.h>
//  #include <Keyboard.h>                     
  
/*Here we are instantiating the ImageReader and TFT */
  Adafruit_ILI9341 tft = Adafruit_ILI9341(LCD_SELECT, DATA_COMMAND);    // creates LCD object
  Adafruit_ImageReader sd;
  Adafruit_Image img;
  ImageReturnCode stat;
//  Adafruit_FT6206 touch = Adafruit_FT6206();        // creates touchscreen object
  uint32_t width = 320, height = 240;
  volatile boolean change = 0;
  volatile boolean SET = 0;

void setup() {
//  Mouse.begin();
//  Keyboard.begin(); 
  Serial.begin(9600);
  tft.begin();
//  touch.begin(40);  // begins and sets touchscreen sensitivity to 40 (0-255)
//  pinMode(SENS_LED, OUTPUT);  
  pinMode(CARD_SELECT, OUTPUT);
  pinMode(DATA_COMMAND, OUTPUT); 
  pinMode(LCD_SELECT, OUTPUT);
  pinMode(Screen_Switch, INPUT_PULLUP);   

/*Serial Monitor SD card checker */
  Serial.print(F("Initializing SD card..."));
  if(!SD.begin(CARD_SELECT)) {
    Serial.println(F("failed!"));
    for(;;); // Loop here forever
  }
  Serial.println(F("OK!"));
  
  tft.fillScreen(ILI9341_BLUE); // starts with a blue screen to verify working
  tft.setRotation(1);           // sets correct picture orientation
  stat = sd.drawBMP("/keyboard.bmp", tft, 0, 0);
  //stat = sd.bmpDimensions("/keyboard.bmp", &width, &height);
  //stat = sd.loadBMP("/keyboard.bmp", img);
  tft.setCursor(10, 6);        // Exact position for Keyboard typing line
  tft.setTextSize(2);          // Sets good size for text on line
  tft.setTextColor(ILI9341_BLACK);  // sets text color to black
  tft.println("Type in your input here"); 
  
}

void loop() {
/*
 * The Serial Monitor polls the Esplora for a "1" or "0" to turn on the "change screen" if statment
 * Created 10/3/19
 */
/*if (Serial.available() > 0) {
  Serial.println("Gotcha");
  uint8_t received = Serial.read();
  if (received == '1') {    // Sent a 1
    SET = !SET;
    change = 1;             // Go to alternate keyboard screen
  }
  if (received == '0') {    // Sent a 0
    SET = !SET;
    change = 0;             // Go to main keyboard screen
  }
}*/

/*
 * The Digital 2 pin of Nano checks output of Digital 7 of Esplora to see if the screen needs to be switched
 * Created 12/20/19  
 */
if (!digitalRead(Screen_Switch)) {  //Poll for start sequence 
  delay(10); 
  if (digitalRead(Screen_Switch)) {    // Sent a HIGH
      SET = !SET;
      change = 0;             // Go to main keyboard screen
  }
  if (!digitalRead(Screen_Switch)) {     // Sent a LOW
      SET = !SET;
      change = 1;             // Go to alternate keyboard screen
  }
}
/*
 * When the serial receives a desired character, the if statement runs
 * Verified correct transitions with State Graph created 10/3/19
 */
if (SET){
 if (change) {
  tft.fillScreen(ILI9341_GREEN); // starts with a blue screen to verify working
  tft.setRotation(1);           // sets correct picture orientation
    sd.drawBMP("/altkey.bmp", tft, 0, 0);
  //stat = sd.bmpDimensions("/altkey.bmp", &width, &height);
 // stat = sd.loadBMP("/altkey.bmp", img);
  SET = 0;
 }
 if (!change){
  tft.fillScreen(ILI9341_BLUE); // starts with a blue screen to verify working
  tft.setRotation(1);           // sets correct picture orientation
  sd.drawBMP("/keyboard.bmp", tft, 0, 0);
  //stat = sd.bmpDimensions("/keyboard.bmp", &width, &height);
  //stat =  sd.loadBMP("/keyboard.bmp", img);
  tft.setCursor(10, 6);        // Exact position for Keyboard typing line
  tft.setTextSize(2);          // Sets good size for text on line
  tft.setTextColor(ILI9341_BLACK);  // sets text color to black
  tft.println("Type in your input here");
  SET = 0;
 }
}
 /* if (touch.touched()) {
    delay(50);                //added delay for verifying human touch
    if (touch.touched()) {
    TS_Point p = touch.getPoint();                          
    Serial.println("You have been touched!");
    Serial.print("The X coordinate is \t"), Serial.println(p.x);
    Serial.print("The Y coordinate is \t"), Serial.println(p.y);
    if ((p.x > 40) && (p.x < 67)) {
      sendTopChar(p.y) ;
    }
    if ((p.x > 102) && (p.x < 125)) {
      sendMidChar(p.y) ;
    }
    if ((p.x > 155) && (p.x < 190)) {
      sendBotChar(p.y) ;
    } 
    if ((p.x > 220) && (p.x < 240)) {
      sendSpaceChar(p.y) ;
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

/*
  Verified by Keyboard Calibration v1.0

void sendTopChar(int y){
  if ((y > 305) && (y < 322))
    Keyboard.write('q'); 
  if ((y > 248) && (y < 266))
    Keyboard.write('w'); 
  if ((y > 228) && (y < 242))
    Keyboard.write('e'); 
  if ((y > 198) && (y < 215))
    Keyboard.write('r'); 
  if ((y > 168) && (y < 180))
    Keyboard.write('t'); 
  if ((y > 140) && (y < 155))
    Keyboard.write('y'); 
  if ((y > 100) && (y < 115))
    Keyboard.write('u'); 
  if ((y > 74) && (y < 92))
    Keyboard.write('i'); 
  if ((y > 55) && (y < 65))
    Keyboard.write('o');
  if ((y > 0) && (y < 15))
    Keyboard.write('p');
} */

/*
  Verified by Keyboard Calibration v1.0

void sendMidChar(int y){
  if ((y > 288) && (y < 300))
    Keyboard.write('a'); 
  if ((y > 248) && (y < 260))
    Keyboard.write('s'); 
  if ((y > 220) && (y < 230))
    Keyboard.write('d'); 
  if ((y > 188) && (y < 202))
    Keyboard.write('f'); 
  if ((y > 155) && (y < 168))
    Keyboard.write('g'); 
  if ((y > 125) && (y < 138))
    Keyboard.write('h'); 
  if ((y > 95) && (y < 105))
    Keyboard.write('j'); 
  if ((y > 58) && (y < 68))
    Keyboard.write('k'); 
  if ((y > 24) && (y < 36))
    Keyboard.write('l');
}
 */
/*
  Verified by Keyboard Calibration v1.0

void sendBotChar(int y){
  if ((y > 300) && (y < 312))
    Keyboard.write(193);      //keyboard Caps-Lock defined by Arduino special characters
  if ((y > 250) && (y < 262))
    Keyboard.write('z'); 
  if ((y > 217) && (y < 227))
    Keyboard.write('x'); 
  if ((y > 180) && (y < 193))
    Keyboard.write('c'); 
  if ((y > 150) && (y < 165))
    Keyboard.write('v'); 
  if ((y > 125) && (y < 135))
    Keyboard.write('b'); 
  if ((y > 90) && (y < 105))
    Keyboard.write('n'); 
  if ((y > 58) && (y < 70))
    Keyboard.write('m'); 
  if ((y > 0) && (y < 20))
    Keyboard.write(178);    //keyboard Backspace defined by Arduino special characters
} */
/*
void sendSpaceChar(int y){
  if ((y > 70) && (y < 240))
    Keyboard.write(32);       //keyboard SPACE     defined by Ascii characters 
  if ((y > 5) && (y < 35))
    Keyboard.write(176);       //keyboard RETURN    defined by Arduino special characters https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
} */
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
