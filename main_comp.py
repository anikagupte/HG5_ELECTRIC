def pre_autonomous():
    # actions to do when the program starts
    brain.screen.clear_screen()
    brain.screen.print("Waiting for autonomous...")
    wait(1, SECONDS)

def autonomous():
    brain.screen.clear_screen()
    brain.screen.print("Autonomous code running...")
    # auton code - start on right facing right wall of field
    drivetrain.drive_for(FORWARD, 500, MM) # drive towards right wall
    drivetrain.turn_for(RIGHT, 90, DEGREES) # turn towards right loader
    drivetrain.drive_for(FORWARD, 300, MM) # drive to loader
    conveyor.spin_for(FORWARD, 1080, DEGREES) # load 3
    conveyor_2.spin_for(FORWARD, 1080, DEGREES)
    drivetrain.turn_for(LEFT, 180, DEGREES) # turn towards right goal
    drivetrain.drive_for(FORWARD, 1000, MM) # drive towards right goal
    conveyor.spin_for(FORWARD, 3240, DEGREES) # score 4 balls
    conveyor_2.spin_for(FORWARD, 3240, DEGREES) # score 4 balls
    # create new program for left side

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

# create competition instance
comp = Competition(user_control, autonomous)
pre_autonomous()
