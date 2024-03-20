#include "Robot.h"

void Robot::TeleopInit() {
    m_Shooter.init();
    //m_AmpDump.Init();
}

void Robot::TeleopPeriodic() {

    std::shared_ptr<nt::NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    targetOffsetH = table->GetNumber("tx", 0.0);

    // AIM AT TARGET
    if (driver.GetAButton() == true) {
        m_Drivetrain.Drive(
            -units::meters_per_second_t{deadband(driver.GetLeftY())},
            -units::meters_per_second_t{deadband(driver.GetLeftX())},
            units::radians_per_second_t{0.5 * targetOffsetH / 27},
            false, true);
    } 

    // DRIVE FIELD-ORIENTED
    else if (driver.GetLeftBumper()) {
        m_Drivetrain.Drive(
            -units::meters_per_second_t{deadband(driver.GetLeftY())},
            -units::meters_per_second_t{deadband(driver.GetLeftX())},
            -units::radians_per_second_t{deadband(driver.GetRightX())},
            true, true);
    }
    
    // DRIVE NORMALLY
    else {
        m_Drivetrain.Drive(
            -units::meters_per_second_t{deadband(driver.GetLeftY())},
            -units::meters_per_second_t{deadband(driver.GetLeftX())},
            -units::radians_per_second_t{deadband(driver.GetRightX())},
            false, true);
    }

    // RESET NAV-X GYRO
    if (driver.GetYButtonPressed()) {
        m_Drivetrain.ZeroHeading();
    }

    // INTAKE CONTROLS
    if (copilot.GetAButton()) {
        m_Intake.Set(1);
    }

    // SHOOTER CONTROLS
    if (copilot.GetBButtonPressed()) {
        m_Shooter.TimerStart();
    }

    if (copilot.GetBButton()) {
        m_Shooter.load();
        m_Intake.Set(1);
    } else if (copilot.GetYButton()) {
        m_Shooter.shoot();
        m_Intake.Set(1);
    } else if (copilot.GetStartButton()) {
        m_Shooter.Set(0.1);
    } else if (copilot.GetXButton()) {
        m_Shooter.Set(-0.222);
    } else {
        m_Shooter.zero();
    }

    if (!copilot.GetAButton() && !copilot.GetBButton() && !copilot.GetYButton()) {
        m_Intake.Set(0);
    }

    // CLIMBER CONTROLS
    m_Climber.setClimber(
        deadband(
            copilot.GetRightTriggerAxis()
             - copilot.GetLeftTriggerAxis()
        )
    ); 

}