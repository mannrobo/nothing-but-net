/**
 * tbh.c - A implementation of the Take Back Half algorithm
 * Copyright (c) Brendan McGuire 2016. All Rights Reserved.
 * This code has been created for Vex 3796B "Some Assembly Required"
 * @TODO: Compile on an actual Windows Machine
 * @TODO: Implement a point system to allow mulitple TBH controlled systems
 */


/** Flywheel Control **/

typedef struct {
  // number of ticks in a revolution (for Vex 393 Turbo Motors)
  float ticksPerRev = 261.333;

  // current values (raw: ticks, current: RPM)
  int currentRaw;
  int current;

  // Target, the target RPM
  int target;

  // Error, the difference between our current value and out target value
  int error;

  // Gain, equivalent to Kp in PID (je pense)
  int gain = 0.00025;

  // The last time we did a motor check (should always be 20, since we don't have super heavy calculations)
  long lastTime = nSysTime;
  // The last IME count
  int lastCount = 0;
} TakeBackHalf

// Make it global to make my life easier (and because pointers are hard :/)
static TakeBackHalf flywheel;
// The actual value to write to the Motors
int drive;
int getMotorEncoderValue() {
  return nMotorEncoder[FlywheelLeft];
}
void updateCurrentRPM() {
  /** Calculate current RPM **/

  int deltaTime;
  int deltaCount;

  // Calculate deltaTime
  deltaTime = nSysTime - lastTime;
  flywheel.lastTime = nSysTime;

  // calculate raw encoder value
  flywheel.currentRaw = getMotorEncoderValue();

  // calculate deltaCount
  flywheel.deltaCount = flywheel.currentRaw - flywheel.lastCount

  // Calulate our current value, in RPM (before gearbox)
  flywheel.current = (1000 / deltaTime) * deltaCount * (60 * flywheel.ticksPerRev)

}
task FlywheelControl() {
  while(true) {

    // Exactly how it looks (see function above)
    updateCurrentRPM();

    // Calculate error
    flywheel.error = flywheel.target - flywheel.current;

    // Calculate final drive
    flywheel.drive+= flywheel.gain * flywheel.error

    // Run at 50Hz clock
    wait1Msec(20);
  }
}

task main() {
  startTask(FlywheelControl);
  while (true) {

    motor[FlywheelLeft] = flywheel.drive;
    motor[FlywheelRight] = flywheel.drive;
  }
}
