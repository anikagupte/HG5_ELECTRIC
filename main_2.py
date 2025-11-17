#region VEXcode Generated Robot Configuration
from vex import *
import urandom

# Brain should be defined by default
brain=Brain()

# Robot configuration code
left_motor = Motor(Ports.PORT11, GearSetting.RATIO_36_1, False)
right_motor = Motor(Ports.PORT12, GearSetting.RATIO_36_1, True)
conveyor_motor = Motor(Ports.PORT3, GearSetting.RATIO_36_1, False)
intake_motor = Motor(Ports.PORT1, GearSetting.RATIO_36_1, True)


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
# 	Project:      VEXcode Project
#	Author:       VEX
#	Created:
#	Description:  VEXcode V5 Python Project
# 
# ------------------------------------------

# Library imports
from vex import *

# Begin project code
"""
def pre_autonomous():
    # actions to do when the program starts
    brain.screen.clear_screen()
    brain.screen.print("pre auton code")
    wait(1, SECONDS)

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("autonomous code")
    # place automonous code here
"""
def user_control():
    brain.screen.clear_screen()
    controller = Controller()
    
    # place driver control in this while loop
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
            conveyor_motor.stop()
        wait(20, MSEC)
        

# create competition instance
user_control()
