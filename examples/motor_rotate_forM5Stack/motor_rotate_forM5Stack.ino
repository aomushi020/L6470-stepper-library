#include <M5Stack.h>
#include <L6470.h>

L6470 stepper = L6470(2);

void setup() {
  // put your setup code here, to run once:
//  Serial.begin(9600);
  stepper.begin();
  stepper.setMaxSpeed(0x0050);
  stepper.setHoldVoltage(0x20);
  stepper.setRunVoltage(0x40);
  stepper.setAccelVoltage(0x40);
  stepper.setDecelVoltage(0x40);
  stepper.setSteps(0x00);

  stepper.run(1,0x004000);
  delay(10000);
  stepper.softStop();
  delay(1000);

  stepper.run(0,0x004000);
  delay(4000);
  stepper.softStop();
  delay(5000);

  stepper.run(0,0x010000);
  delay(1000);
  stepper.hardStop();
  delay(5000);

  stepper.goHome();
  delay(8000);
}

void loop() {
  // put your main code here, to run repeatedly:
}