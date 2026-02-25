// Configure pneumatics
digital_out descorer = digital_out(Brain.ThreeWirePort.A);
digital_out match_loader = digital_out(Brain.ThreeWirePort.B);

// Moving the descorer
if (Controller1.ButtonL2.pressing()) {
    // Descorer up
    descorer.set(true);
}
else if (Controller1.ButtonL1.pressing()) {
    // Descorer down
    descorer.set(false);
}

// Moving the loader
if (Controller1.ButtonDown.pressing()) {
    // Loader down
    match_loader.set(true);
}
else if (Controller1.ButtonUp.pressing()) {
    // Loader up
    match_loader.set(false);
}
