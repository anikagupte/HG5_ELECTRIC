// ------------------------------------------
//
// Project: VEX Competition Code
// Author: HG5_ELECTR!C
// Created: 12/02/2025
// Configuration: Right
//
// ------------------------------------------

#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;

// Robot configuration code
motor left_motor_a = motor(PORT1, ratio36_1, false);
motor left_motor_b = motor(PORT3, ratio36_1, false);
motor_group left_drive_smart = motor_group(left_motor_a, left_motor_b);

motor right_motor_a = motor(PORT2, ratio36_1, true);
motor right_motor_b = motor(PORT4, ratio36_1, true);
motor_group right_drive_smart = motor_group(right_motor_a, right_motor_b);

drivetrain Drivetrain = drivetrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, mm, 1);

motor conveyor_motor_a = motor(PORT5, ratio18_1, false);
motor conveyor_motor_b = motor(PORT6, ratio18_1, false);
motor_group conveyor = motor_group(conveyor_motor_a, conveyor_motor_b);

// Controller instance
controller Controller1 = controller(primary);

// Competition instance
competition Competition;

// Function to initialize random seed
void initializeRandomSeed() {
    wait(100, msec);
    int random = Brain.Battery.voltage(voltageUnits::mV) + 
                 Brain.Battery.current(currentUnits::amp) * 100 + 
                 Brain.Timer.systemHighResolution();
    srand(random);
}

// Helper function to play VEXcode sounds
void play_vexcode_sound(const char* sound_name) {
    printf("VEXPlaySound:%s\n", sound_name);
    wait(5, msec);
}

// Pre-autonomous function
void pre_auton(void) {
    // Actions to do when the program starts
    Brain.Screen.clearScreen();
    Brain.Screen.print("Waiting for autonomous to begin...");
    wait(1, seconds);
    
    // Initialize random seed
    initializeRandomSeed();
}

// Autonomous function
void autonomous(void) {
    Brain.Screen.clearScreen();
    Brain.Screen.print("Autonomous code running...");
    
    // Auton code - start facing right wall
    Drivetrain.driveFor(reverse, 125, mm);
    Drivetrain.turnFor(right, 80, degrees);
    Drivetrain.driveFor(reverse, 690, mm);
    
    conveyor.setVelocity(100, percent);
    conveyor.spinFor(reverse, 1250, degrees); // load 3
    
    Drivetrain.turnFor(right, 45, degrees);
    Drivetrain.driveFor(reverse, 100, mm);
    Drivetrain.turnFor(right, 12, degrees);
    
    conveyor.spinFor(forward, 3240, degrees); // score 3 balls
}

// User control function
void usercontrol(void) {
    Brain.Screen.clearScreen();
    
    while (true) {
        Drivetrain.setDriveVelocity(100, percent);
        
        // Tank drive control
        left_motor_a.setVelocity(Controller1.Axis3.position(), percent);
        left_motor_a.spin(reverse);
        left_motor_b.setVelocity(Controller1.Axis3.position(), percent);
        left_motor_b.spin(reverse);
        
        right_motor_a.setVelocity(Controller1.Axis2.position(), percent);
        right_motor_a.spin(reverse);
        right_motor_b.setVelocity(Controller1.Axis2.position(), percent);
        right_motor_b.spin(reverse);
        
        wait(5, msec);
        
        // Move conveyor belt up (pick up or place ball into high tube)
        conveyor.setVelocity(100, percent);
        
        if (Controller1.ButtonR1.pressing()) {
            conveyor.spin(forward);
        }
        // Place ball into lower tube
        else if (Controller1.ButtonR2.pressing()) {
            conveyor.spin(reverse);
        }
        else {
            // Stop conveyor belt
            conveyor.stop();
        }
        
        wait(20, msec);
    }
}

// Main function
int main() {
    // Set up callbacks for autonomous and driver control periods
    Competition.autonomous(autonomous);
    Competition.drivercontrol(usercontrol);
    
    // Run the pre-autonomous function
    pre_auton();
    
    // Prevent main from exiting with an infinite loop
    while (true) {
        wait(100, msec);
    }
}
