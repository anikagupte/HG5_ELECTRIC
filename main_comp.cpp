// ------------------------------------------
2//
3// Project: VEX Competition Code
4// Author: HG5_ELECTR!C
5// Created: 12/02/2025
6// Configuration: Right
7//
8// ------------------------------------------
9
10#include "vex.h"
11
12using namespace vex;
13
14// Brain should be defined by default
15brain Brain;
16
17// Robot configuration code
18motor left_motor_a = motor(PORT1, ratio36_1, false);
19motor left_motor_b = motor(PORT3, ratio36_1, false);
20motor_group left_drive_smart = motor_group(left_motor_a, left_motor_b);
21
22motor right_motor_a = motor(PORT2, ratio36_1, true);
23motor right_motor_b = motor(PORT4, ratio36_1, true);
24motor_group right_drive_smart = motor_group(right_motor_a, right_motor_b);
25
26drivetrain Drivetrain = drivetrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, mm, 1);
27
28motor conveyor_motor_a = motor(PORT5, ratio18_1, false);
29motor conveyor_motor_b = motor(PORT6, ratio18_1, false);
30motor_group conveyor = motor_group(conveyor_motor_a, conveyor_motor_b);
31
32// Controller instance
33controller Controller1 = controller(primary);
34
35// Competition instance
36competition Competition;
37
38// Function to initialize random seed
39void initializeRandomSeed() {
40    wait(100, msec);
41    int random = Brain.Battery.voltage(voltageUnits::mV) + 
42                 Brain.Battery.current(currentUnits::amp) * 100 + 
43                 Brain.Timer.systemHighResolution();
44    srand(random);
45}
46
47// Helper function to play VEXcode sounds
48void play_vexcode_sound(const char* sound_name) {
49    printf("VEXPlaySound:%s\n", sound_name);
50    wait(5, msec);
51}
52
53// Pre-autonomous function
54void pre_auton(void) {
55    // Actions to do when the program starts
56    Brain.Screen.clearScreen();
57    Brain.Screen.print("Waiting for autonomous to begin...");
58    wait(1, seconds);
59    
60    // Initialize random seed
61    initializeRandomSeed();
62}
63
64// Autonomous function
65void autonomous(void) {
66    Brain.Screen.clearScreen();
67    Brain.Screen.print("Autonomous code running...");
68    
69    // Auton code - start facing right wall
70    Drivetrain.driveFor(reverse, 125, mm);
71    Drivetrain.turnFor(right, 80, degrees);
72    Drivetrain.driveFor(reverse, 690, mm);
73    
74    conveyor.setVelocity(100, percent);
75    conveyor.spinFor(reverse, 1250, degrees); // load 3
76    
77    Drivetrain.turnFor(right, 45, degrees);
78    Drivetrain.driveFor(reverse, 100, mm);
79    Drivetrain.turnFor(right, 12, degrees);
80    
81    conveyor.spinFor(forward, 3240, degrees); // score 3 balls
82}
83
84// User control function
85void usercontrol(void) {
86    Brain.Screen.clearScreen();
87    
88    while (true) {
89        Drivetrain.setDriveVelocity(100, percent);
90        
91        // Tank drive control
92        left_motor_a.setVelocity(Controller1.Axis3.position(), percent);
93        left_motor_a.spin(reverse);
94        left_motor_b.setVelocity(Controller1.Axis3.position(), percent);
95        left_motor_b.spin(reverse);
96        
97        right_motor_a.setVelocity(Controller1.Axis2.position(), percent);
98        right_motor_a.spin(reverse);
99        right_motor_b.setVelocity(Controller1.Axis2.position(), percent);
100        right_motor_b.spin(reverse);
101        
102        wait(5, msec);
103        
104        // Move conveyor belt up (pick up or place ball into high tube)
105        conveyor.setVelocity(100, percent);
106        
107        if (Controller1.ButtonR1.pressing()) {
108            conveyor.spin(forward);
109        }
110        // Place ball into lower tube
111        else if (Controller1.ButtonR2.pressing()) {
112            conveyor.spin(reverse);
113        }
114        else {
115            // Stop conveyor belt
116            conveyor.stop();
117        }
118        
119        wait(20, msec);
120    }
121}
122
123// Main function
124int main() {
125    // Set up callbacks for autonomous and driver control periods
126    Competition.autonomous(autonomous);
127    Competition.drivercontrol(usercontrol);
128    
129    // Run the pre-autonomous function
130    pre_auton();
131    
132    // Prevent main from exiting with an infinite loop
133    while (true) {
134        wait(100, msec);
135    }
136}
