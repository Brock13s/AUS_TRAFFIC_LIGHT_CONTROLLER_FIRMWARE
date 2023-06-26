#include <IRremote.h>

#define red_light 3
#define amber_light 4
#define green_light 5
#define ir_pin 2

#define IR_OFF_BTN 4244827904
#define IR_ON_BTN 4228116224
#define IR_FLASH_BTN 4094422784
#define IR_STROBE_BTN 4027576064
#define IR_RED_BTN 4211404544
#define IR_GREEN_BTN 4194692864
#define IR_YELLOW_BTN 3944017664

#define ENABLE true
#define DISABLE false

uint32_t command1 = 0;
bool RelayInvert = DISABLE; // When I get my trigger low relays I need to set this to ENABLE to invert the HIGH and LOW SIGNAL, if using leds connected to ground do not invert the signal by setting to DISABLE
bool lightState = true;
bool flag1 = true;
bool colorbuttonstates[3] = {true, true, true};

unsigned long previousTime = 0;
const unsigned long redDuration = 10000;
const unsigned long greenDuration = 10000;
const unsigned long amberDuration = 5000;

enum TrafficState {
  RED,
  GREEN,
  AMBER
};

TrafficState currentState;

enum Modes {
  TL_ANIMATION,
  TL_TOGGLE
};

Modes currentMode;



void setup() {
  Serial.begin(9600);
  IrReceiver.begin(ir_pin, ENABLE_LED_FEEDBACK);
  pinMode(red_light, OUTPUT);
  pinMode(amber_light, OUTPUT);
  pinMode(green_light, OUTPUT);
  currentState = RED; // Initialize the current state to RED
  currentMode = TL_ANIMATION;
  digitalWrite(red_light, RelayInvert ? !HIGH : HIGH); // Turn on the red LED
}

void turnoff(){
      digitalWrite(red_light, RelayInvert ? !LOW : LOW);
    digitalWrite(amber_light, RelayInvert ? !LOW : LOW);
    digitalWrite(green_light, RelayInvert ? !LOW : LOW);
}

void loop() {
  if (IrReceiver.decode()) {
    command1 = IrReceiver.decodedIRData.decodedRawData;
    switch (command1) {
      case IR_ON_BTN:
        lightState = true;
        break;
      case IR_OFF_BTN:
        lightState = false;
        break;
      case IR_FLASH_BTN:
        currentMode = TL_ANIMATION;
        break;
      case IR_STROBE_BTN:
        currentMode = TL_TOGGLE;
        break;
      case IR_RED_BTN:
        colorbuttonstates[0] ^= true;
        break;
      case IR_GREEN_BTN:
        colorbuttonstates[1] ^= true;
        break;
      case IR_YELLOW_BTN:
        colorbuttonstates[2] ^= true;
        break;
    }
    IrReceiver.resume();

  }
  if (lightState) {
    if (currentMode == TL_ANIMATION) {
      if (flag1) {
        flag1 = false;
        switch (currentState) {
          case RED:
            digitalWrite(red_light, RelayInvert ? !HIGH : HIGH);
            digitalWrite(green_light, RelayInvert ? !LOW : LOW);
            digitalWrite(amber_light, RelayInvert ? !LOW : LOW);
            break;
          case GREEN:
            digitalWrite(red_light, RelayInvert ? !LOW : LOW);
            digitalWrite(green_light, RelayInvert ? !HIGH : HIGH);
            digitalWrite(amber_light, RelayInvert ? !LOW : LOW);
            break;
          case AMBER:
            digitalWrite(red_light, RelayInvert ? !LOW : LOW);
            digitalWrite(green_light, RelayInvert ? !LOW : LOW);
            digitalWrite(amber_light, RelayInvert ? !HIGH : HIGH);
            break;
        }
      }

      switch (currentState) {
        case RED:
          if (millis() - previousTime >= redDuration) {
            currentState = GREEN;
            previousTime = millis();
            digitalWrite(red_light, RelayInvert ? !LOW : LOW);
            digitalWrite(green_light, RelayInvert ? !HIGH : HIGH);
          }
          break;

        case GREEN:
          if (millis() - previousTime >= greenDuration) {
            currentState = AMBER;
            previousTime = millis();
            digitalWrite(green_light, RelayInvert ? !LOW : LOW);
            digitalWrite(amber_light, RelayInvert ? !HIGH : HIGH);
          }
          break;

        case AMBER:
          if (millis() - previousTime >= amberDuration) {
            currentState = RED;
            previousTime = millis();
            digitalWrite(amber_light, RelayInvert ? !LOW : LOW);
            digitalWrite(red_light, RelayInvert ? !HIGH : HIGH);
          }
          break;
      }
      if(command1 == IR_STROBE_BTN){
        turnoff();
      }
    }

    else if(currentMode == TL_TOGGLE){
            if(command1 == IR_FLASH_BTN){
        Serial.println("DEBUG");
        turnoff();
        
      }
       
      digitalWrite(amber_light, RelayInvert ^ colorbuttonstates[2]);
      digitalWrite(green_light, RelayInvert ^ colorbuttonstates[1]);
      digitalWrite(red_light, RelayInvert ^ colorbuttonstates[0]);

    }


  } else {
    turnoff();
    flag1 = true;
  }


}
