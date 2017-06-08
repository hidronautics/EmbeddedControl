#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdint.h>
#include <stdbool.h>

#include "robot.h"
#include "messages.h"

extern struct Robot Q100;

extern bool shore_RX_enable;
extern bool shore_TX_enable;
extern bool VMA_RX_enable;
extern bool VMA_TX_enable;
extern bool DEV_RX_enable;
extern bool DEV_TX_enable;

extern bool VMA_RX_enable;
extern bool VMA_TX_enable;
extern bool DEV_RX_enable;
extern bool DEV_TX_enable;

extern uint8_t shorePackageError;

extern uint8_t ShoreRequestBuf[SHORE_REQUEST_LENGTH];
extern uint8_t ShoreRequestConfigBuf[REQUEST_CONFIG_LENGTH];
extern uint8_t ShoreResponseBuf[SHORE_RESPONSE_LENGTH];

extern uint8_t IMUReceiveBuf[IMU_RECEIVE_PACKET_SIZE*5*4];

extern uint8_t BTReceiveBuf[BT_SIZE];
extern uint8_t BTCalls;

extern uint8_t VMARequestBuf[VMA_DEV_REQUEST_LENGTH];
extern uint8_t VMAResponseBuf[VMA_DEV_RESPONSE_LENGTH];

extern uint8_t DevRequestBuf[VMA_DEV_REQUEST_LENGTH];
extern uint8_t DevResponseBuf[VMA_DEV_RESPONSE_LENGTH];

#endif
