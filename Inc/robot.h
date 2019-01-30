#ifndef ROBOT_H
#define ROBOT_H

#include <stdbool.h>
#include <math.h>
#include <stdint.h>

#include "messages.h"

enum VMA {
	HLB = 0,
    HLF,
    HRB,
    HRF,
    VB,
    VF,
    VL,
    VR
};

#define DEV_AMOUNT 7

enum DEV {
    AGAR = 0,
    GRAB,
    GRAB_ROTATION,
    TILT,
    LIGHT,
    DEV1,
	DEV2
};

#define LOGDEV_AMOUNT 1

enum LOGDEV {
	ACOUSTIC = 0
};

enum I2C {
	I2C_SENSORS = 0,
	I2C_PC
};

struct Robot
{
	// Current camera ID (controls multiplexor)
	uint8_t cameraNum;

	// Individual characteristics, controls and current state of each VMA
	struct robot_thrusters {
		// current controls (data ready to fetch)
		uint8_t address;
		uint8_t settings;
		int8_t desiredSpeed;
		// current state (fresh data)
		uint16_t current;
		uint8_t errors;
		int8_t realSpeed;
		int8_t speedError;
		// characteristics (this parameters affects only sending data, they are not meant to be sent or received)
		float kForward;	// this constants will be multiplied with desiredSpeed
		float kBackward;
		bool inverse; // inverts thruster
	} thrusters[THRUSTERS_NUMBER];

	struct f_Sensors {
		float roll;
		float pitch;
		float yaw;
		float rollSpeed;
		float pitchSpeed;
		float yawSpeed;
		float accelX;
		float accelY;
		float accelZ;
		float magX;
		float magY;
		float magZ;
		float quatA;
		float quatB;
		float quatC;
		float quatD;
		bool resetIMU;
		float pressure;
		float in_pressure;
		float leak;
	} f_sensors;

	// TODO send all data in float, why the fuck u need that?
	struct i_Sensors {
		int16_t roll;
		int16_t pitch;
		int16_t yaw;
		int16_t rollSpeed;
		int16_t pitchSpeed;
		int16_t yawSpeed;
		int16_t accelX;
		int16_t accelY;
		int16_t accelZ;
		int16_t magX;
		int16_t magY;
		int16_t magZ;
		int16_t quatA;
		int16_t quatB;
		int16_t quatC;
		int16_t quatD;
		bool resetIMU;
		uint16_t pressure;
		uint16_t in_pressure;
		uint16_t leak;
	} i_sensors;

	// TODO you don't need that
	struct robotWifi {
		uint8_t type;
		uint8_t tickrate;
		uint8_t voltage;
		float x;
		float y;
	} wifi;

	struct robotPC {
		uint8_t reset;
		uint8_t errors;
	} pc;

	struct i_JoystickRobotSpeed {
		int16_t march;
		int16_t lag;
		int16_t depth;
		int16_t roll;
		int16_t pitch;
		int16_t yaw;
	} i_joySpeed;

	// TODO same way as sensors
	struct f_JoystickRobotSpeed {
		float march;
		float lag;
		float depth;
		float roll;
		float pitch;
		float yaw;
	} f_joySpeed;

	struct i_PositionRobotMovement {
		int16_t march;
		int16_t lag;
		int16_t depth;
		int16_t roll;
		int16_t pitch;
		int16_t yaw;
	} i_posMov;

	// TODO same way as sensors
	struct f_PositionRobotMovement {
		float march;
		float lag;
		float depth;
		float roll;
		float pitch;
		float yaw;
	} f_posMov;

	struct RobotDev {
		uint8_t address;
		uint8_t settings;
		int8_t force;
		uint16_t current;
		uint8_t errors;
	} device[DEV_AMOUNT];

	struct RobotLogDev {
		uint8_t state;
		uint8_t control;
		uint8_t errors;
	} logdevice[LOGDEV_AMOUNT];

	// TODO u need something like structure in structure for that (settings will be inside)
	struct RobotStabilizationConstants {
		bool enable;
		// Before P
		uint8_t cameras;
		float iJoySpeed;
		float pSpeedDyn;
		float pErrGain;
		// Feedback
		float pSpeedFback;
		// PID
		float pid_pGain;
		float pid_iGain;
		float pid_iMax;
		float pid_iMin;
	} depthStabCons, rollStabCons, pitchStabCons, yawStabCons;

	struct RobotStabilizationState {
		float posError;
		float speedError;
		float dynSummator;
		float pidValue;
		float posErrorAmp;

		float joy_iValue;
		float joy_iLastTick;
	} depthStabSt, rollStabSt, pitchStabSt, yawStabSt;

};

#endif
