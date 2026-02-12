// ------------------------------------------
2//
3// Project: VEX Controller Code
4// Configuration: Controller
5//
6// ------------------------------------------
7
8#include "vex.h"
9
10using namespace vex;
11
12// Brain should be defined by default
13brain Brain;
14
15// Robot configuration code
16motor left_motor = motor(PORT11, ratio36_1, false);
17motor right_motor = motor(PORT12, ratio36_1, true);
18motor conveyor_motor = motor(PORT3, ratio36_1, false);
19motor intake_motor = motor(PORT1, ratio36_1, true);
20
21// Controller instance
22controller Controller1 = controller(primary);
23
24// Function to initialize random seed
25void initializeRandomSeed() {
26    wait(100, msec);
27    int random = Brain.Battery.voltage(voltageUnits::mV) + 
28                 Brain.Battery.current(currentUnits::amp) * 100 + 
29                 Brain.Timer.systemHighResolution();
30    srand(random);
31}
32
33// Helper function to play VEXcode sounds
34void play_vexcode_sound(const char* sound_name) {
35    printf("VEXPlaySound:%s\n", sound_name);
36    wait(5, msec);
37}
38
39// User control function
40void user_control(void) {
41    Brain.Screen.clearScreen();
42    
43    while (true) {
44        // Tank drive control - left side
45        left_motor.setVelocity(Controller1.Axis3.position(), percent);
46        left_motor.spin(reverse);
47        
48        // Tank drive control - right side
49        right_motor.setVelocity(Controller1.Axis2.position(), percent);
50        right_motor.spin(reverse);
51        
52        wait(5, msec);
53        
54        // Move conveyor belt up (pick up or place ball into high tube)
55        conveyor_motor.setVelocity(100, percent);
56        
57        if (Controller1.ButtonR1.pressing()) {
58            conveyor_motor.spin(forward);
59        }
60        // Place ball into lower tube
61        else if (Controller1.ButtonR2.pressing()) {
62            conveyor_motor.spin(reverse);
63        }
64        else {
65            // Stop conveyor belt
66            conveyor_motor.stop();
67        }
68        
69        wait(20, msec);
70    }
71}
72
73// Main function
74int main() {
75    // Wait for sensor initialization
76    wait(30, msec);
77    
78    // Initialize random seed
79    initializeRandomSeed();
80    
81    // Add a small delay
82    wait(200, msec);
83    
84    // Clear the console
85    printf("\033[2J");
86    
87    // Run user control
88    user_control();
89    
90    // Prevent main from exiting
91    while (true) {
92        wait(100, msec);
93    }
94}
