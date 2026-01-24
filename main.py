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

# Begin project code

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
        conveyor_2.set_velocity(100, PERCENT)
        if controller.buttonR1.pressing():
            conveyor.spin(FORWARD)
            conveyor_2.spin(FORWARD)
        # place ball into lower tube
        elif controller.buttonR2.pressing():
            conveyor.spin(REVERSE)
            conveyor_2.spin(REVERSE)
        else:
            # stop conveyor belt
            conveyor.stop()
            conveyor_2.stop()
        wait(20, MSEC)

user_control()
