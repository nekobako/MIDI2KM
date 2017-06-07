#include <MIDI2KM.h>

void setup() {
}

void loop() {
/*
  MIDI2KM.setButtonState(0, BUTTON_DOWN);
  MIDI2KM.sendStates();
  delay(200);
  MIDI2KM.setButtonState(0, BUTTON_UP);
  MIDI2KM.sendStates();
  delay(5000);

  MIDI2KM.setButtonState(1, BUTTON_DOWN);
  MIDI2KM.sendStates();
  delay(200);
  MIDI2KM.setButtonState(1, BUTTON_UP);
  MIDI2KM.sendStates();
  delay(5000);
*/

  MIDI2KM.setWheelState(WHEEL_BACK);
  MIDI2KM.sendStates();
  delay(200);
  MIDI2KM.setWheelState(WHEEL_MIDDLE);
  MIDI2KM.sendStates();

  MIDI2KM.setWheelState(WHEEL_FRONT);
  MIDI2KM.sendStates();
  delay(200);
  MIDI2KM.setWheelState(WHEEL_MIDDLE);
  MIDI2KM.sendStates();

  for(int i = 0; i < 24; i++) {
    MIDI2KM.setKeyState(i, KEY_DOWN);
    MIDI2KM.sendStates();
    delay(200);
    MIDI2KM.setKeyState(i, KEY_UP);
    MIDI2KM.sendStates();
  }
}

