#include <Keyboard.h>
#define CLK 2
#define DT 3
#define SW 4

int mode = 1;
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir = "";
unsigned long lastButtonPress = 0;

word keyup = KEY_UP_ARROW;
word keydown = KEY_DOWN_ARROW;

word winkey = KEY_LEFT_GUI;
word ctrl = KEY_LEFT_CTRL;

void setup() {
  // put your setup code here, to run once:
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);

  Keyboard.begin();

  Serial.begin(9600);

  lastStateCLK = digitalRead(CLK);
}
void ModeChecker() {
  if (mode == 1) {
    keyup = KEY_UP_ARROW;
    keydown = KEY_DOWN_ARROW;
  } else if (mode == 2) {
    keyup = KEY_RIGHT_ARROW;
    keydown = KEY_LEFT_ARROW;
  } else if (mode = 3) {
    keyup = KEY_RIGHT_ARROW;
    keydown = KEY_LEFT_ARROW;
  }
}
void loop() {
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != lastStateCLK && currentStateCLK == 1 && mode == 3) {
    if (digitalRead(DT) != currentStateCLK) {
      counter ++;
      currentDir = "CW";
      Keyboard.press(winkey);
      delay(31);
      Keyboard.press(ctrl);
      delay(31);
      Keyboard.press(keyup);
      delay(31);
      Keyboard.release(winkey);
      delay(31);
      Keyboard.release(ctrl);
      delay(31);
      Keyboard.release(keyup);
      delay(31);
    } else {
      counter --  ;
      currentDir = "CCW";
      Keyboard.press(winkey);
      delay(31);
      Keyboard.press(ctrl);
      delay(31);
      Keyboard.press(keydown);
      delay(31);
      Keyboard.release(winkey);
      delay(31);
      Keyboard.release(ctrl);
      delay(31);
      Keyboard.release(keydown);
      delay(31);
    }
    Serial.print("Direction = ");
    Serial.println(currentDir);
    Serial.print("     Counter = ");
    Serial.println(counter);
  }
  else if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {
    if (digitalRead(DT) != currentStateCLK) {
      counter ++;
      currentDir = "CW";
      Keyboard.press(keyup);
      delay(31);
      Keyboard.release(keyup);
    } else {
      counter --  ;
      currentDir = "CCW";
      Keyboard.press(keydown);
      delay(31);
      Keyboard.release(keydown);
    }
    Serial.print("Direction = ");
    Serial.println(currentDir);
    Serial.print("     Counter = ");
    Serial.println(counter);
  }

  //Remember Last CLK state
  lastStateCLK = currentStateCLK;

  //Read the button state
  int btnState = digitalRead(SW);

  //If btn is LOW, its pressed
  if (btnState == LOW) {
    if (millis() - lastButtonPress > 50) {
      Serial.println("Button Pressed!");
      mode = 1;
      ModeChecker();
      if (millis() - lastButtonPress < 250) {
        Serial.println("Double Press");
        mode = 2;
        ModeChecker();
        
      } else if(millis() - lastButtonPress < 1000) {
          Serial.println("Long Press");
          mode = 3;
          ModeChecker();
        }
        Serial.println(millis() - lastButtonPress);
    }

    //Remember last button press event
    lastButtonPress = millis();

  }
  delay(1);
}
