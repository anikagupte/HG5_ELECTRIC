// ------------------------------------------
//
// Project: VEX Controller Code
// Configuration: Controller
//
// ------------------------------------------

#include "vex.h"

using namespace vex;

// Brain should be defined by default
brain Brain;

// Robot configuration code
motor left_motor = motor(PORT11, ratio36_1, false);
motor right_motor = motor(PORT12, ratio36_1, true);
motor conveyor_motor = motor(PORT3, ratio36_1, false);
motor intake_motor = motor(PORT1, ratio36_1, true);

// Controller instance
controller Controller1 = controller(primary);

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

// User control function
void user_control(void) {
    Brain.Screen.clearScreen();
    
    while (true) {
        // Tank drive control - left side
        left_motor.setVelocity(Controller1.Axis3.position(), percent);
        left_motor.spin(reverse);
        
        // Tank drive control - right side
        right_motor.setVelocity(Controller1.Axis2.position(), percent);
        right_motor.spin(reverse);
        
        wait(5, msec);
        
        // Move conveyor belt up (pick up or place ball into high tube)
        conveyor_motor.setVelocity(100, percent);
        
        if (Controller1.ButtonR1.pressing()) {
            conveyor_motor.spin(forward);
        }
        // Place ball into lower tube
        else if (Controller1.ButtonR2.pressing()) {
            conveyor_motor.spin(reverse);
        }
        else {
            // Stop conveyor belt
            conveyor_motor.stop();
        }
        
        wait(20, msec);
    }
}

// Main function
int main() {
    // Wait for sensor initialization
    wait(30, msec);
    
    // Initialize random seed
    initializeRandomSeed();
    
    // Add a small delay
    wait(200, msec);
    
    // Clear the console
    printf("\033[2J");
    
    // Run user control
    user_control();
    
    // Prevent main from exiting
    while (true) {
        wait(100, msec);
    }
}
