# Arduino Pill Dispenser

Automated pill dispender using Arduino, on 2 levels using only one stepper for rotation. Handles morning and evening medication schedules, displays time, and alerts the user with LED and buzzer.
This is especially for elders, since taking medication can be a complex task for them

## Overview

This project is a practical embedded system that:

- Dispenses pills automatically at scheduled times.
- Shows time and reminders on a 7-segment display.
- Uses a servo motor to release pills and a stepper motor to rotate compartments.
- Alerts the user with a buzzer and LED.
- Resets daily for continuous, automated operation.

## Key Features

- **Time Display:** Real-time display via 7-segment module.
- **Automated Dispensing:** Stepper rotates compartment; servo releases pill.
- **Morning & Evening Scheduling:** Configurable times in code.
- **Alerts:** LED and buzzer notify the user; button stops the alert.
- **Daily Reset:** Flags reset at midnight for next-day dispensing.

## Hardware Components

- Arduino (any compatible board)  
- DS3231 RTC module  
- Servo motor  
- Stepper motor  
- Adafruit PCF8574 I/O Expander  
- 7-segment display  
- Buzzer, LED, push button  

## Software / Libraries

- Arduino IDE  
- `Wire.h` / `SoftwareWire.h` for I2C  
- `Adafruit_PCF8574` for I/O expansion  
- `RtcDS3231` for real-time clock  
- `Servo.h` for servo control  

## Usage

1. Connect hardware according to pin definitions in the code.  
2. Install required libraries.  
3. Upload the sketch to Arduino.  
4. The system automatically displays time and handles pill dispensing at set hours.  
5. Press the button to acknowledge and stop alerts.  

## How It Works

1. RTC tracks current time.  
2. 7-segment display shows time and reminders.  
3. At scheduled times:  
   - Stepper rotates compartment (that is both levels are rotated)
   - Servo releases pill (this happens only for the evening, since in the morning pill are released automatically though the whole. The servo manipulates a trapp that hold the evning pill until the right time arrives).  
   - Buzzer and LED alert user.  
4. Pressing the button stops alert.  
5. System resets flags at midnight for next-day operation.
   
## Demo video
https://youtu.be/yCr5uvRQxGc
