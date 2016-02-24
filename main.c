#include <pid.c>

/** PID Controllers **/
static PIDControlled flywheel;
flywheel.IMEMotor = LeftFlywheel;

task usercontrol() {
  while (true) {
    PIDUpdate(&flywheel);
    flywheel.target = 200;
    motor[LeftFlywheel] = flywheel.drive;
    motor[RightFlywheel] = flywheel.drive;
    wait1Msec(20);
  }
}
