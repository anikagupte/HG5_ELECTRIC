// ------------------------------------------
//
// Project: VEX Controller Code
// Configuration: Controller
//
// ------------------------------------------

#include "vex.h"

using namespace vex;

// Brain
brain Brain;

// Motors
motor left_motor_a  = motor(PORT1, ratio36_1, false);
motor left_motor_b  = motor(PORT3, ratio36_1, false);
motor right_motor_a = motor(PORT2, ratio36_1, true);
motor right_motor_b = motor(PORT4, ratio36_1, true);

motor_group left_drive_smart  = motor_group(left_motor_a, left_motor_b);
motor_group right_drive_smart = motor_group(right_motor_a, right_motor_b);

// Drivetrain: wheel circumference=319.19mm, track width=295mm, wheel base=40mm
smartdrive drivetrain = smartdrive(left_drive_smart, right_drive_smart, PORT19, 319.19, 295, 40, mm, 1);
// Note: If you don't have an inertial sensor, replace PORT19 with your actual inertial sensor port,
// or use a drivetrain without one (see comment below).

// Conveyor
motor conveyor_motor_a = motor(PORT5, ratio18_1, false);
motor conveyor_motor_b = motor(PORT6, ratio18_1, false);
motor_group conveyor   = motor_group(conveyor_motor_a, conveyor_motor_b);

// Descorer (pneumatic / digital out on 3-wire port A)
digital_out descorer = digital_out(Brain.ThreeWirePort.A);

// Controller
controller Controller = controller(primary);

/*---------------------------------------------------------------------------*/
/*                              User Control Task                            */
/*---------------------------------------------------------------------------*/
void user_control() {
    Brain.Screen.clearScreen();

    while (true) {
        // Tank drive: axis3 = left stick vertical, axis2 = right stick vertical
        // Spinning REVERSE to match original Python logic
        int leftSpeed  = Controller.Axis3.position();
        int rightSpeed = Controller.Axis2.position();

        left_motor_a.setVelocity(leftSpeed, percent);
        left_motor_a.spin(reverse);
        left_motor_b.setVelocity(leftSpeed, percent);
        left_motor_b.spin(reverse);

        right_motor_a.setVelocity(rightSpeed, percent);
        right_motor_a.spin(reverse);
        right_motor_b.setVelocity(rightSpeed, percent);
        right_motor_b.spin(reverse);

        wait(5, msec);

        // Conveyor belt control
        conveyor.setVelocity(100, percent);
        if (Controller.ButtonR1.pressing()) {
            conveyor.spin(forward);
        } else if (Controller.ButtonR2.pressing()) {
            conveyor.spin(reverse);
        } else {
            conveyor.stop();
        }

        wait(20, msec);

        // Descorer control
        if (Controller.ButtonL1.pressing()) {
            descorer.set(true);   // open
        } else if (Controller.ButtonL2.pressing()) {
            descorer.set(false);  // close
        }
    }
}

/*---------------------------------------------------------------------------*/
/*                                 Main                                      */
/*---------------------------------------------------------------------------*/
int main() {
    // Initialize random seed (equivalent to initializeRandomSeed in Python)
    srand((int)(Brain.Battery.voltage(voltageUnits::mV)
              + Brain.Battery.current(currentUnits::amp) * 100
              + Brain.Timer.systemHighResolution()));

    wait(200, msec);
    Brain.Screen.clearScreen();

    // Run driver control directly (no competition switch — mirrors Python's user_control() call)
    user_control();

    return 0;
}

// may need to swap smartdrive for drivetrain (lack of inertial sensor) with this code:
// drivetrain drivetrain = drivetrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, mm, 1);
