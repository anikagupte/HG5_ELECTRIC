/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Project:      VEX Competition Code                                      */
/*    Author:       HG5_ELECTR!C                                              */
/*    Created:      02/12/2025                                                */
/*    Configuration: Right                                                    */
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
drivetrain Drivetrain = drivetrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, mm, 1);

motor conveyor_motor_a = motor(PORT5, ratio18_1, false);
motor conveyor_motor_b = motor(PORT6, ratio18_1, false);
motor_group conveyor   = motor_group(conveyor_motor_a, conveyor_motor_b);

controller Controller = controller(primary);

// Competition instance
competition Competition;

/*---------------------------------------------------------------------------*/
/*                            Pre-Autonomous                                 */
/*---------------------------------------------------------------------------*/
void pre_autonomous() {
    Brain.Screen.clearScreen();
    Brain.Screen.print("Waiting for autonomous to begin...");
    wait(1, seconds);
}

/*---------------------------------------------------------------------------*/
/*                              Autonomous                                   */
/*---------------------------------------------------------------------------*/
void autonomous() {
    Brain.Screen.clearScreen();
    Brain.Screen.print("Autonomous code running...");

    // Auton code - start facing right wall
    Drivetrain.driveFor(reverse, 125, mm);
    Drivetrain.turnFor(right, 80, degrees);
    Drivetrain.driveFor(reverse, 690, mm);

    conveyor.setVelocity(100, percent);
    conveyor.spinFor(reverse, 1250, degrees);   // load 3

    Drivetrain.turnFor(right, 45, degrees);
    Drivetrain.driveFor(reverse, 110, mm);
    Drivetrain.turnFor(right, 10, degrees);

    conveyor.spinFor(forward, 3240, degrees);   // score 3 balls
}

/*---------------------------------------------------------------------------*/
/*                             User Control                                  */
/*---------------------------------------------------------------------------*/
void user_control() {
    Brain.Screen.clearScreen();

    while (true) {
        // Tank drive - Axis3 = left stick vertical, Axis2 = right stick vertical
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

        wait(20, msec);
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

    // Register competition callbacks
    Competition.autonomous(autonomous);
    Competition.drivercontrol(user_control);

    // Run pre-autonomous
    pre_autonomous();

    // Idle loop — competition switch drives autonomous/user_control callbacks
    while (true) {
        wait(100, msec);
    }

    return 0;
}
