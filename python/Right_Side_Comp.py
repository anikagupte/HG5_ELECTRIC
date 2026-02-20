#region VEXcode Generated Robot Configuration
from vex import *
import urandom
import math

# Brain should be defined by default
brain=Brain()

# Robot configuration code
left_motor_a = Motor(Ports.PORT1, GearSetting.RATIO_36_1, False)
left_motor_b = Motor(Ports.PORT3, GearSetting.RATIO_36_1, False)
left_drive_smart = MotorGroup(left_motor_a, left_motor_b)
right_motor_a = Motor(Ports.PORT2, GearSetting.RATIO_36_1, True)
right_motor_b = Motor(Ports.PORT4, GearSetting.RATIO_36_1, True)
right_drive_smart = MotorGroup(right_motor_a, right_motor_b)
drivetrain = DriveTrain(left_drive_smart, right_drive_smart, 319.19, 295, 40, MM, 1)
conveyor_motor_a = Motor(Ports.PORT5, GearSetting.RATIO_18_1, False)
conveyor_motor_b = Motor(Ports.PORT6, GearSetting.RATIO_18_1, False)
conveyor = MotorGroup(conveyor_motor_a, conveyor_motor_b)


# wait for rotation sensor to fully initialize
wait(30, MSEC)


# Make random actually random
def initializeRandomSeed():
    wait(100, MSEC)
    random = brain.battery.voltage(MV) + brain.battery.current(CurrentUnits.AMP) * 100 + brain.timer.system_high_res()
    urandom.seed(int(random))
     
# Set random seed
initializeRandomSeed()


def play_vexcode_sound(sound_name):
    # Helper to make playing sounds from the V5 in VEXcode easier and
    # keeps the code cleaner by making it clear what is happening.
    print("VEXPlaySound:" + sound_name)
    wait(5, MSEC)

# add a small delay to make sure we don't print in the middle of the REPL header
wait(200, MSEC)
# clear the console to make sure we don't have the REPL in the console
print("\033[2J")

#endregion VEXcode Generated Robot Configuration

# ------------------------------------------
#
# Project: VEX Competition Code
# Author: HG5_ELECTR!C
# Created: 02/12/2025
# Configuration: Right
#
# ------------------------------------------

# Library imports
from vex import *

# Begin project code

def pre_autonomous():
    # actions to do when the program starts
    brain.screen.clear_screen()
    brain.screen.print("Waiting for autonomous to begin...")
    wait(1, SECONDS)

# Begin project code
def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("Autonomous code running...")
    # auton code - start facing right wall
    drivetrain.drive_for(REVERSE, 125, MM)
    drivetrain.turn_for(RIGHT, 80, DEGREES)
    drivetrain.drive_for(REVERSE, 690, MM)
    conveyor.set_velocity(100,PERCENT)
    conveyor.spin_for(REVERSE, 1250, DEGREES) # load 3
    drivetrain.turn_for(RIGHT, 45, DEGREES)
    drivetrain.drive_for(REVERSE, 110, MM)
    drivetrain.turn_for(RIGHT, 10, DEGREES)
    conveyor.spin_for(FORWARD, 3240, DEGREES) # score 3 balls

def user_control():
    brain.screen.clear_screen()
    controller=Controller()
    while True:
        left_motor_a.set_velocity(controller.axis3.position(), PERCENT)
        left_motor_a.spin(REVERSE)
        left_motor_b.set_velocity(controller.axis3.position(), PERCENT)
        left_motor_b.spin(REVERSE)

        right_motor_a.set_velocity(controller.axis2.position(), PERCENT)
        right_motor_a.spin(REVERSE)
        right_motor_b.set_velocity(controller.axis2.position(), PERCENT)
        right_motor_b.spin(REVERSE)
       
        wait(5, MSEC)

        # move conveyor belt up (pick up or place ball into high tube)
        conveyor.set_velocity(100, PERCENT)
        if controller.buttonR1.pressing():
            conveyor.spin(FORWARD)
        # place ball into lower tube
        elif controller.buttonR2.pressing():
            conveyor.spin(REVERSE)
        else:
            # stop conveyor belt
            conveyor.stop()
        wait(20, MSEC)

# create competition instance
comp = Competition(user_control, autonomous)
pre_autonomous()
