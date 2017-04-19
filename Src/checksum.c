#include "checksum.h"



/* CRC16-CCITT algorithm */
bool isChecksumm16bCorrect(uint8_t *msg, uint16_t length)
{
  int i;
	uint16_t crc = 0, crc_got = (uint16_t)((msg[length - 2] << 8) + msg[length - 1]);
	
		for(i = 0; i < length - 2; ++i){
			crc = (uint8_t)(crc >> 8) | (crc << 8);
			crc ^= msg[i];
			crc ^= (uint8_t)(crc & 0xff) >> 4;
			crc ^= (crc << 8) << 4;
			crc ^= ((crc & 0xff) << 4) << 1;
		}
	
	if(crc == crc_got ){
    return 1;
  }
	else{
    return 0;
  }
}



/* CRC16-CCITT algorithm */
void addChecksumm16b(uint8_t *msg, uint16_t length)
{
	uint16_t crc = 0;
	int i = 0;
	
	for(i = 0; i < length - 2; ++i){
			crc = (uint8_t)(crc >> 8) | (crc << 8);
			crc ^= msg[i];
			crc ^= (uint8_t)(crc & 0xff) >> 4;
			crc ^= (crc << 8) << 4;
			crc ^= ((crc & 0xff) << 4) << 1;
		}
	
	msg[length - 2] = (uint8_t) (crc >> 8);
	msg[length - 1] = (uint8_t) crc;
}



bool isChecksumm8bCorrect(uint8_t *msg, uint16_t length)
{
	uint8_t crcGot, crc = 0;
	int i;
	
	crcGot = msg[length-1] ;
	
		for(i=0; i < length - 1; i++){
			crc ^= msg[i];
		}
	
	if(crc == crcGot )
		return 1;
	else return 0;
}



void addCheckSumm8b(uint8_t *msg, uint16_t length)
{
	uint8_t crc = 0;
	int i = 0;
	
	for(i=0; i < length - 1; i++){
			crc ^= msg[i];
		}
	
	msg[length-1] = crc;
}



uint16_t IMUchecksum(uint8_t *buf, uint16_t length)
{
  uint16_t checksum = 0;
  for(uint8_t i = 0; i < length; ++i){
    checksum += buf[i];
  }
  return checksum;
}
