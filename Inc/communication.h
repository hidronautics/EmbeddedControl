#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "robot.h"

#define UART_NUMBER 4

enum {
	SHORE_UART = 0,
	THRUSTERS_UART,
	DEVICES_UART,
	IMU_UART
};

enum {
	DEV_I2C = 0,
	PC_I2C
};

enum ImuErrcodes {
    IMU_FIND_ERROR=1,
    IMU_BAD_CHECKSUM_ERROR
};

enum BTErrCodes {
    BT_ERROR_RECEIVED_NOTHING=1,
    BT_ERROR_RECEIVED_LESS
};

enum uartTxRxType {
	TXRX_IT = 0,
	TXRX_DMA
};

// Structure for each UART bus
struct uartBus_s {
	// Data storage
	uint8_t* rxBuffer;				// Buffer for received messages
	uint8_t* txBuffer;				// Buffer for messages to be transmitted
	// State of the bus
	bool packageReceived; 			// Is new package received in this moment
	bool packageTransmitted;		// Is new package transmitted in this moment (true if transmitted but not received)
	uint16_t successRxCounter;		// Successfully received packages counter (checksum is correct + timeout not reached)
	uint32_t brokenRxCounter;		// Broken received packages counter (incorrect checksum)
	uint32_t outdatedRxCounter;		// Outdated received packages counter (timeout reached)
	TickType_t timeoutCounter;		// Timeout counter for receive and transmit
	// Bus configuration
	uint8_t brokenRxTolerance;		// How many broken packages will be received until special event
	uint32_t timeoutRxTolerance;	// How many milliseconds to wait new package and not cast special event
	uint8_t rxLength;				// Length of the next received message
	uint8_t txLength;				// Length of the next message to be transmitted
	uint32_t receiveTimeout;		// How many milliseconds to wait until timeout
	uint32_t transmitTimeout;		// How many milliseconds to wait until timeout
	UART_HandleTypeDef *huart;		// Link to huart structure
	uint8_t txrxType;				// How to send and receive messages (use DMA or regular interruptions)
};

extern struct uartBus_s uartBus[UART_NUMBER];

extern bool uartPackageReceived[UART_NUMBER];
extern uint16_t counterRx; // TODO structure for every communication protocol which includes all these things
extern uint32_t brokenRxCounter;
extern uint32_t outdatedRxCounter;
extern uint32_t successRxCounter;
extern uint8_t brokenRxTolerance;

// Initialization of user variables
void variableInit(void);
void uartBusesInit(void);

// Custom UART DMA receive/transmit functions
bool receivePackage(struct uartBus_s *bus, bool isrMode);
bool transmitPackage(struct uartBus_s *bus, bool isrMode);
bool transmitAndReceive(struct uartBus_s *bus, bool isrMode);
void receiveI2cPackageDMA (uint8_t I2C, uint16_t addr, uint8_t *buf, uint8_t length);
void transmitI2cPackageDMA(uint8_t I2C, uint16_t addr, uint8_t *buf, uint8_t length);

void DevicesRequestUpdate(struct Robot *robot, uint8_t *buf, uint8_t device);
void DevicesResponseUpdate(struct Robot *robot, uint8_t *buf, uint8_t device);

void ThrustersRequestUpdate(struct Robot *robot, uint8_t *buf, uint8_t thruster);
void ThrustersResponseUpdate(struct Robot *robot, uint8_t *buf, uint8_t thruster);

void ShoreReceive();
void ShoreRequest(struct Robot *robot, uint8_t *requestBuf);
void ShoreConfigRequest(struct Robot *robot, uint8_t *requestBuf);
void ShoreResponse(struct Robot *robot, uint8_t *responseBuf);

void ImuReceive(struct Robot *robot, uint8_t *IMUReceiveBuf, uint8_t *ErrCode);

void SensorsResponseUpdate(struct Robot *robot, uint8_t *buf, uint8_t Sensor_id);

#endif
