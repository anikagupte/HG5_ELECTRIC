#region VEXcode Generated Robot Configuration
from vex import *
import urandom

# Brain should be defined by default
brain=Brain()

# Robot configuration code
left_motor = Motor(Ports.PORT11, GearSetting.RATIO_18_1, False)
right_motor = Motor(Ports.PORT12, GearSetting.RATIO_18_1, True)
intake_motor = Motor(Ports.PORT3, GearSetting.RATIO_18_1, False)
conveyor_motor = Motor(Ports.PORT1, GearSetting.RATIO_18_1, False)


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
#   Project: VEXcode Project
#   Author: HG5_ELECTR!C
#   Created: 14/10/2025
#   Description: VEXcode V5 Python Project
#
# ------------------------------------------

# Library imports
from vex import *

"""
This script is for the VEX robotics game "Push Back"
and includes the code for both the autonomous section
of the game, as well as the code for the controller.
"""
controller = Controller()

def setup():
# pre-autonomous setup
controller = Controller()
intake_motor.set_stopping(HOLD)
conveyor_motor.set_stopping(HOLD)
intake_motor.set_velocity(60, PERCENT)
conveyor_motor.set_velocity(30, PERCENT)


def controller_mode():
# controller buttons

while True:
left_motor.set_velocity(controller.axis3.position(), PERCENT)
right_motor.set_velocity(controller.axis2.position(), PERCENT)
left_motor.spin(FORWARD)
right_motor.spin(FORWARD)
wait(5, MSEC)

# move forward
if controller.buttonL1.pressing():
intake_motor.spin(FORWARD)
# move backwards
elif controller.buttonL2.pressing():
intake_motor.spin(REVERSE)
# stop moving
else:
intake_motor.stop()

# move conveyor belt up (pick up or placement into high tube)
if controller.buttonR1.pressing():
conveyor_motor.spin(FORWARD)
# place ball into lower tube
elif controller.buttonR2.pressing():
conveyor_motor.spin(REVERSE)
else:
# stop conveyor belt
intake_motor.stop()

wait(5, MSEC)


def autonomous_mode():
# autonomous section - picks up a ball and places in high tube

def pick_up():
conveyor_motor.spin_for(FORWARD, 90, DEGREES)
intake_motor.spin_for(FORWARD, 90, DEGREES)

def release_low():
intake_motor.spin_for(REVERSE, 90, DEGREES)

def release_high():
conveyor_motor.spin_for(FORWARD, 90, DEGREES)

while True:
if controller.buttonA():
controller_mode()


setup()
controller_mode()
