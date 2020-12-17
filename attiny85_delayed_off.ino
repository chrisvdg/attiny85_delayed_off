#include <avr/sleep.h>
#include <avr/wdt.h>

const int INPUTPIN = A1;
const int LED =  0;


int inputVal = 0;
unsigned long MillisFull = 60000; // for 1 minute since powerloss full on
unsigned long MillisDim = 300000; // for 5 minutes since powerloss go into higher dim mode
unsigned long MillisOff = 600000; // after 10 mins since powerloss turn light off, before this in low dim mode
unsigned long lastMillis = 0;

void setup() {
  // initialize the LED pin as an output:
  pinMode(LED, OUTPUT);
  wdt_disable();
}

void loop() {
  inputVal = analogRead(INPUTPIN);

  if (inputVal >= 100) {
    digitalWrite(LED, HIGH);
    lastMillis = millis();
  } else {
    unsigned long millisDiff = 0;
    if (lastMillis == 0) {
      millisDiff = MillisOff;
    }
    else {
      millisDiff = millis() - lastMillis;
    }
    
    if (millisDiff < MillisFull){
      // switching from digital high or 255 causes the LED to turn off for a brief moment
      // This will cause the blackout to happen when the power is lost and not when going into the first dimmed state
      analogWrite(LED, 254);
    }
    else if (millisDiff < MillisDim){
      analogWrite(LED, 200);
    }
    else if (millisDiff < MillisOff) {
      analogWrite(LED, 100);
    }
    else{
      digitalWrite(LED, LOW);
      deep_sleep();
    }
  }
}

void deep_sleep(){
  // Disable the ADC
  static byte prevADCSRA = ADCSRA;
  ADCSRA = 0;

  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  sleep_bod_disable();
  noInterrupts();

  // clear various "reset" flags
  MCUSR = 0;  // allow changes, disable reset
  WDTCR = bit (WDCE) | bit(WDE); // set interrupt mode and an interval
  WDTCR = bit (WDIE) | bit(WDP2) | bit(WDP0);
  wdt_reset();

  interrupts();

  sleep_cpu();
  sleep_disable();

  // Re-enable ADC if it was previously running
  ADCSRA = prevADCSRA;
}

// When WatchDog timer causes µC to wake it comes here
ISR (WDT_vect) {
  wdt_disable();

}
