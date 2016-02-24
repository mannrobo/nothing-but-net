/**
 * pid.h - Implementation of Proportional Integral Derivative in ROBOTC
 * Copyright (c) 2016 Brendan McGuire. All rights reserved.
 * The code has been created for VEX 3796B "Some Assembly Required"
 * ALGORITHM:
 *  The pid algorithm is calculated as follows:
 *    u(t) = (Kp * error) + (Ki * accumulate) + (Kd * (error - last_error))
 *    where:
 *      - Kp, Ki, and Kd are tuning variables
 *      - error is the target - current:
 *        -- target is the wanted value (RPM in this implementation)
 *        -- current is the current value (RPM in this implementation)
 *      - accumulate is the all the error that has been recorded
 *      - last_error is the error on last calculation
 */

/** Define Motor Gearings **/
#define VEX_393_Standard    627.2
#define VEX_393_HighSpeed   392.0
#define VEX_393_Turbo       261.333

typedef struct {
  /** Constants **/
  float Kp = 5;
  float Ki = 3;
  float Kd = 0;


  // number of ticks in a revolution (for Vex 393 Turbo Motors)
  float ticksPerRev = VEX_393_Turbo;

  // current values (raw: ticks, current: RPM)
  int currentCountRaw;
  float currentVelocity;

  // Target, the target RPM
  int target;

  // Error, the difference between our current value and out target value
  int error;

  // Integral, the accumulate of all error
  int integral;
  // Derivative, the current error minus the last error
  int derivative

  // Last error, used for calculating derivative
  int lastError = 0;
  // The last time we did a motor check (should always be 20, since we don't have super heavy calculations)
  long lastTime = nSysTime;

  // The last IME count
  int lastCount = 0;

  // Total time (in ms) since last recalculating the velocity
  int deltaTime;
  // Total change in ticks since last reclaculation
  int deltaCount;

  // The motor that the IME is installed on
  tMotor IMEMotor;

  // Actual output to set your motors to
  int drive;
} PIDControlled



void PIDUpdateVelocity(PIDControlled *system) {
  // Get the current tick count from the motor encoder
  system->currentRaw = nMotorEncoder[flywheel->IMEMotor];

  // Recalculate the deltaTime
  system->deltaTime = nSysTime - system->lastTime;
  system->lastTime = nSysTime;

  // Calculate change in ticks
  system->deltaCount = system->currentCountRaw - system->lastCount;
  system->lastCount = system->currentCountRaw;

  // Update actual velocity
  system->currentVelocity = (1000.0 / deltaTime) * deltaCount * (60 / system->ticksPerRev)
}

void PIDUpdate(PIDControlled *system) {
  // Update velocity
  PIDUpdateVelocity(&system);
  // Calculate error, for Proportional
  system->error = system->target - system->currentVelocity;

  // Calculate error accumulate, for Integral (and account for deltaTime)
  system->integral += system->error * system->deltaTime;

  // Calculate derivative, the previous error minus the current error (divided by deltaTime)
  system->derivative = (system->error - system->lastError) / system.deltaTime;


  // Calculate final drive, the value to be sent to the motors
  system->drive =
    /** Proportional **/
    (system->Kp * system->error) +
    (system->Ki * system->integral) +
    (system->Kd * system->derivative);

  // Clamp drive to motor values
  if (system->drive > 127) {
    system->drive = 127;
  } else if (system->drive < -127) {
    system->drive = -127;
  }
  // Update last error
  system->lastError = system.error
}
