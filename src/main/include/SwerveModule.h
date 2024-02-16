#pragma once

#include <frc/kinematics/SwerveDriveKinematics.h>

#include "ctre/Phoenix.h"
#include "rev/CANSparkMax.h"

class SwerveModule {
    public:
        SwerveModule(int driveMotorId, int turnMotorId, int turnEncoderId);

        double getAngle();
        void setState(frc::SwerveModuleState desiredState);
    
    private:
        int driveMotorId;
        int turnMotorId;
        int turnEncoderId;

        WPI_TalonFX driveMotor{driveMotorId};
        rev::CANSparkMax turnMotor{turnMotorId, rev::CANSparkMax::MotorType::kBrushless};
        WPI_CANCoder turnEncoder{turnEncoderId};
};