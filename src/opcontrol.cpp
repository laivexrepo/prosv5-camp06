#include "main.h"
#include "portdef.h"

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::Motor left_mtr(LEFT_WHEELS_PORT);
	pros::Motor right_mtr(RIGHT_WHEELS_PORT, true);	// reverse motor

	pros::ADIEncoder encoder (QUAD1_PORT_TOP, QUAD1_PORT_BOTTOM, true);
  pros::ADIDigitalIn bumper (BUMPER_PORT);

	while (true) {
		left_mtr.move(master.get_analog(ANALOG_LEFT_Y));
		right_mtr.move(master.get_analog(ANALOG_RIGHT_Y));

		std::cout << "Encoder value: " << encoder.get_value() << "\n";

		std::cout << "Bumper Switch State: " << bumper.get_value() << "\n";

		pros::delay(20);
	}
}
