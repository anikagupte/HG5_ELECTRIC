/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Project:      Controller Code                                           */
/*    Author:       HG5_ELECTR!C                                              */
/*    Description:  VEXcode V5 C++ Test Code                                  */
/*                                                                            */
/*    This is the test code for our robot - it is used solely during          */
/*    training and does not include a competition instance.                   */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

/*---------------------------------------------------------------------------*/
/*                          Robot Configuration                              */
/*---------------------------------------------------------------------------*/

brain Brain;

motor left_motor_a  = motor(PORT1, ratio36_1, false);
motor left_motor_b  = motor(PORT3, ratio36_1, false);
motor right_motor_a = motor(PORT2, ratio36_1, true);
motor right_motor_b = motor(PORT4, ratio36_1, true);

motor_group left_drive_smart  = motor_group(left_motor_a, left_motor_b);
motor_group right_drive_smart = motor_group(right_motor_a, right_motor_b);

// Drivetrain: wheel circumference=319.19mm, track=295mm, wheelbase=40mm
smartdrive Drivetrain = smartdrive(left_drive_smart, right_drive_smart, PORT20, 319.19, 295, 40, mm, 1);

motor conveyor_motor_a = motor(PORT5, ratio18_1, false);
motor conveyor_motor_b = motor(PORT6, ratio18_1, false);
motor_group conveyor   = motor_group(conveyor_motor_a, conveyor_motor_b);

// Descorer on 3-wire port A, match loader on 3-wire port B
digital_out descorer     = digital_out(Brain.ThreeWirePort.A);
digital_out match_loader = digital_out(Brain.ThreeWirePort.B);

controller Controller = controller(primary);

/*---------------------------------------------------------------------------*/
/*                             User Control                                  */
/*                                                                           */
/*    Defines controller buttons and begins project code.                    */
/*---------------------------------------------------------------------------*/
void user_control() {
    Brain.Screen.clearScreen();

    Drivetrain.setDriveVelocity(100, percent);

    while (true) {
        // Tank drive - Axis3 = left stick vertical, Axis2 = right stick vertical
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
            conveyor.spin(forward);          // pick up / place into high tube
        } else if (Controller.ButtonR2.pressing()) {
            conveyor.spin(reverse);          // place into lower tube
        } else {
            conveyor.stop();
        }

        wait(20, msec);

        // Descorer control
        if (Controller.ButtonL2.pressing()) {
            descorer.set(true);   // close
        } else if (Controller.ButtonL1.pressing()) {
            descorer.set(false);  // open
        }

        // Match loader control
        if (Controller.ButtonDown.pressing()) {
            match_loader.set(true);   // open
        } else if (Controller.ButtonUp.pressing()) {
            match_loader.set(false);  // close
        }
    }
}

/*---------------------------------------------------------------------------*/
/*                                  Main                                     */
/*---------------------------------------------------------------------------*/
int main() {
    // Initialize random seed
    srand((int)(Brain.Battery.voltage(voltageUnits::mV)
              + Brain.Battery.current(currentUnits::amp) * 100
              + Brain.Timer.systemHighResolution()));

    wait(200, msec);
    Brain.Screen.clearScreen();

    // Run driver control directly (no competition instance — training only)
    user_control();

    return 0;
}

// may need to swap smartdrive for drivetrain (lack of inertial sensor) with this code:
// drivetrain drivetrain = drivetrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, mm, 1);
