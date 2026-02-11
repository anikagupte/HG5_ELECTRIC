# configure pneumatics
pneumatics = DigitalOut(brain.three_wire_port.a)

# set cylinder to down
digital_out_a.set(False)

if controller.buttonL1.pressing():
    # cylinder up
    digital_out_a.set(True)
elif controller.buttonL2.pressing():
    # cylinder down
    digital_out_a.set(False)
