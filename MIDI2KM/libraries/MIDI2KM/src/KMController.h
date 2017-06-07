#ifndef MIDI2KM_H
#define MIDI2KM_H

#include "HID.h"

#define BUTTON_UP		0x00
#define BUTTON_DOWN		0x01
#define KEY_UP			0x00
#define KEY_DOWN		0x01
#define WHEEL_MIDDLE	0x00
#define WHEEL_BACK		0x01
#define WHEEL_FRONT		0x02


class MIDI2KM_ {
public:
	MIDI2KM_();
	void setButtonState(uint8_t button, uint8_t state);
	void setKeyState(uint8_t key, uint8_t state);
	void setWheelState(uint8_t state);
	void sendStates();

private:
	uint64_t report = 0x3f;
};


extern MIDI2KM_ MIDI2KM;


#endif
