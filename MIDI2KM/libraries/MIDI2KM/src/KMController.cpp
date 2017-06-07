#include "MIDI2KM.h"

#define bitSet64(value, bit) ((value) |= (1ULL << (bit)))
#define bitClear64(value, bit) ((value) &= ~(1ULL << (bit)))


PROGMEM static const u8 MIDI2KM_REPORT_DESCRIPTOR[] = {
	0x05, 0x01,							// Usage Page (Generic Desktop)
	0x09, 0x05,							// Usage (Gamepad)
	0xA1, 0x01,							// Collection (Application)

	0x05, 0x09,							//   Usage Page (Button)
	0x19, 0x3A,							//   Usage Minimum (58)
	0x29, 0x3F,							//   Usage Maximum (63)
	0x15, 0x00,							//   Logical Minimum (0)
	0x25, 0x01,							//   Logical Maximum (1)
	0x75, 0x01,							//   Report Size (1)
	0x95, 0x06,							//   Report Count (6)
	0x81, 0x02,							//   Input (Data, Variable, Absolute)

	0x75, 0x01,							//   Report Size (1)
	0x95, 0x02,							//   Report Count (2)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0x05, 0x09,							//   Usage Page (Button)
	0x19, 0x01,							//   Usage Minimum (1)
	0x29, 0x07,							//   Usage Maximum (7)
	0x15, 0x00,							//   Logical Minimum (0)
	0x25, 0x01,							//   Logical Maximum (1)
	0x75, 0x01,							//   Report Size (1)
	0x95, 0x07,							//   Report Count (7)
	0x81, 0x02,							//   Input (Data, Variable, Absolute)

	0x75, 0x01,							//   Report Size (1)
	0x95, 0x01,							//   Report Count (1)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0x05, 0x09,							//   Usage Page (Button)
	0x19, 0x08,							//   Usage Minimum (8)
	0x29, 0x0E,							//   Usage Maximum (14)
	0x15, 0x00,							//   Logical Minimum (0)
	0x25, 0x01,							//   Logical Maximum (1)
	0x75, 0x01,							//   Report Size (1)
	0x95, 0x07,							//   Report Count (7)
	0x81, 0x02,							//   Input (Data, Variable, Absolute)

	0x75, 0x01,							//   Report Size (1)
	0x95, 0x01,							//   Report Count (1)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0x05, 0x09,							//   Usage Page (Button)
	0x19, 0x0F,							//   Usage Minimum (15)
	0x29, 0x15,							//   Usage Maximum (21)
	0x15, 0x00,							//   Logical Minimum (0)
	0x25, 0x01,							//   Logical Maximum (1)
	0x75, 0x01,							//   Report Size (1)
	0x95, 0x07,							//   Report Count (7)
	0x81, 0x02,							//   Input (Data, Variable, Absolute)

	0x75, 0x01,							//   Report Size (1)
	0x95, 0x01,							//   Report Count (1)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0x05, 0x09,							//   Usage Page (Button)
	0x19, 0x16,							//   Usage Minimum (22)
	0x29, 0x1C,							//   Usage Maximum (28)
	0x15, 0x00,							//   Logical Minimum (0)
	0x25, 0x01,							//   Logical Maximum (1)
	0x75, 0x01,							//   Report Size (1)
	0x95, 0x07,							//   Report Count (7)
	0x81, 0x02,							//   Input (Data, Variable, Absolute)

	0x75, 0x01,							//   Report Size (1)
	0x95, 0x01,							//   Report Count (1)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0x05, 0x01,							//   Usage Page (Generic Desktop)
	0x09, 0x01,							//   Usage (Pointer)
	0xA1, 0x00,							//   Collection (Physical)

	0x09, 0x30,							//     Usage (X)
	0x09, 0x31,							//     Usage (Y)
	0x15, 0xFF,							//     Logical Minimum (-1)
	0x25, 0x01,							//     Logical Maximum (1)
	0x75, 0x02,							//     Report Size (2)
	0x95, 0x02,							//     Report Count (2)
	0x81, 0x02,							//     Input (Data, Variable, Absolute)

	0x75, 0x01,							//     Report Size (1)
	0x95, 0x04,							//     Report Count (4)
	0x81, 0x01,							//     Input (Constant, Array, Absolute)

	0xC0,								//   End Collection

	0x75, 0x08,							//   Report Size (8)
	0x95, 0x02,							//   Report Count (2)
	0x81, 0x01,							//   Input (Constant, Array, Absolute)

	0xC0								// End Collection
};

static const uint8_t BUTTONS[] = {
	0x16, 0x1E
};

static const uint8_t KEYS[] = {
	0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
	0x10, 0x11, 0x12, 0x13, 0x14, 0x15,
	0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D,
	0x20, 0x21, 0x22, 0x23, 0x24
};

static const uint8_t WHEELS[] = {
	0x25, 0x26
};

MIDI2KM_ MIDI2KM;


MIDI2KM_::MIDI2KM_() {
	static HIDSubDescriptor node(MIDI2KM_REPORT_DESCRIPTOR, sizeof(MIDI2KM_REPORT_DESCRIPTOR));
	HID().AppendDescriptor(&node);
}

void MIDI2KM_::setButtonState(uint8_t button, uint8_t state) {
	switch(state) {
		case BUTTON_UP:
			bitClear64(this->report, BUTTONS[button]);
			break;
		case BUTTON_DOWN:
			bitSet64(this->report, BUTTONS[button]);
			break;
	}
}

void MIDI2KM_::setKeyState(uint8_t key, uint8_t state) {
	switch(state) {
		case KEY_UP:
			bitClear64(this->report, KEYS[key]);
			break;
		case KEY_DOWN:
			bitSet64(this->report, KEYS[key]);
			break;
	}
}

void MIDI2KM_::setWheelState(uint8_t state) {
	bitClear64(this->report, WHEELS[0]);
	bitClear64(this->report, WHEELS[1]);

	if(state != WHEEL_MIDDLE) {
		bitSet64(this->report, WHEELS[state - 1]);
	}
}

void MIDI2KM_::sendStates() {
	USB_Send(1 | TRANSFER_RELEASE, &this->report, sizeof(this->report));
}
