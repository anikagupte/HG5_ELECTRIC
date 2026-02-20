// Configure pneumatics
digital_out pneumatics = digital_out(Brain.ThreeWirePort.A);

// Set cylinder to down
pneumatics.set(false);

if (Controller1.ButtonL1.pressing()) {
    // Cylinder up
    pneumatics.set(true);
}
else if (Controller1.ButtonL2.pressing()) {
    // Cylinder down
    pneumatics.set(false);
}
