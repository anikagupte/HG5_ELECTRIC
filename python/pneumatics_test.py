# configure pneumatics
loader = DigitalOut(brain.three_wire_port.a)
descorer = DigitalOut(brain.three_wire_port.b)

# set cylinders to down
digital_out_a.set(False)
digital_out_b.set(False)

if controller.buttonL1.pressing():
    # cylinder up for loader
    digital_out_a.set(True)
elif controller.buttonL2.pressing():
    # cylinder down for loader
    digital_out_a.set(False)

if controller.buttonUp.pressing():
    # cylinder up for descorer
    digital_out_b.set(True)
elif controller.buttonDown.pressing():
    # cylinder down for descorer
    digital_out_b.set(False)
