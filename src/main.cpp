// Mohawk College - COMP-10184
//
// Digital Input/Output Lab - Test Program
//
#include <Arduino.h>

/*
 * I, Justin Borzi, 000798465 certify that this material is my original
 * work. No other person's work has been used without due
 * acknowledgement. (Replace with your own name and student number)
 */

// Track the state of the button and light 
byte lastButtonState = HIGH;
byte ledState = HIGH;

// Track the brightness state of the light
unsigned long lastBrightness = 0;

// Setup the debounce timings and time since it was last clicked.
unsigned long debounceDuration = 50; // millis
unsigned long lastTimeButtonStateChanged = 0;

void setup()
{
  // configure the USB serial monitor
  Serial.begin(115200);

  // configure pin D5 as digital input - this is the pushbutton
  pinMode(D5, INPUT_PULLUP);

  // configure pin D4 as a digital output - this is the LED
  pinMode(D4, OUTPUT);

  // set default PWM range
  analogWriteRange(1023);
}

void loop()
{
  // Check the time between button presses is atleast ~50ms for a debounce.
  if (millis() - lastTimeButtonStateChanged > debounceDuration)
  {

    // Set the default of the light state to off.
    analogWrite(D4, 1023);

    // Read the current state
    byte buttonState = digitalRead(D5);

    // Determine if the button press doesnt equal the last. if it doesnt then its a new button press...
    if (buttonState != lastButtonState)
    {

      // Save the new button state as the last state.
      lastButtonState = buttonState;

      if (buttonState == LOW)
      {
        // Swap the LED state to on or off depending on previous state.
        ledState = (ledState == HIGH) ? LOW : HIGH;

        // Write the new state to the light.
        digitalWrite(D4, ledState);
      }
    }
  }

  // Determine if the LED state is on, if so turn the light on with the current or last brightness observed.
  if (ledState == LOW)
  {
    // read the brightness and set it to a global variable.
    lastBrightness = analogRead(A0);

    // set the PWM pulse width with the new brightness.
    analogWrite(D4, lastBrightness);
  }
}