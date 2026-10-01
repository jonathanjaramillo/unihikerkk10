# k10-gamecontroller

Arduino/PlatformIO driver for the I2C game controller (analog joystick plus
buttons A, B, C, D and OK) used with the UNIHIKER K10.

- I2C address `0x5A` by default.
- Uses a bus the application has already initialized, so it shares the K10's I2C
  bus (SDA GPIO47, SCL GPIO48) with the onboard peripherals.
- No pins or build flags are required; pass the bus and address to `begin()`.

## Use

This library lives in the `unihikerk10` umbrella repo under `libs/`. From a
project folder that sits at the umbrella root:

```ini
; platformio.ini
lib_extra_dirs = ../libs
```

```cpp
#include <GameController.h>

GameController controller;

void setup() {
  Wire.begin(47, 48);
  controller.begin(Wire);            // or begin(Wire, 0x5A)
}

void loop() {
  uint8_t x, y, event;
  controller.readAxes(x, y);                                       // 0-255 raw
  controller.readButtonEvent(GameController::BUTTON_A, event);     // see ButtonEvent
}
```

Both read functions return `false` if the controller doesn't answer (for example
when unplugged), which is how callers can detect hot-plug. See
`examples/basic/main.cpp` for a complete sketch.

## API

| | |
|---|---|
| `begin(TwoWire&, uint8_t address = 0x5A)` | attach to an initialized bus |
| `readAxes(uint8_t& x, uint8_t& y)` | joystick position, registers `0x10`/`0x11` |
| `readButtonEvent(Button, uint8_t& event)` | latest event for one button |

Buttons: `BUTTON_A`, `BUTTON_B`, `BUTTON_C`, `BUTTON_D`, `BUTTON_OK`.
Events: `PRESS_DOWN`, `PRESS_UP`, `PRESS_REPEAT`, `SINGLE_CLICK`, `DOUBLE_CLICK`,
`LONG_PRESS_START`, `LONG_PRESS_HOLD`, `NONE_PRESS`.

Button registers: A `0x22`, B `0x23`, C `0x21`, D `0x24`, OK `0x20`.

## Note

`esp-doom` (`lib/GameController`) and `esp32-SfM` (`firmware/game_controller`)
still carry their own copies of this driver; new projects should use this one.
