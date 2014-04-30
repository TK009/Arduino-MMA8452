#ifndef MMA8452_H_
#define MMA8452_H_

#include <Arduino.h>
#include <Wire.h>

#include "MMA8452Reg.h"
#include "SoftwareSerial.h"

// I2C address set in hardware (tied high or low)
#define SA0 0
#if SA0
#define MMA8452_ADDRESS 0x1D
#else
#define MMA8452_ADDRESS 0x1C
#endif

typedef enum {
	MMA_RANGE_2G = 0,
	MMA_RANGE_4G,
	MMA_RANGE_8G
} mma8452_range_t;

class MMA8452
{

	public:
		bool init();
		void setRange(mma8452_range_t range);
		void getRawData(uint16_t *x, uint16_t *y, uint16_t *z);
		void getAcceleration(float *x, float *y, float *z);

		SoftwareSerial *debug;

	private:
		mma8452_range_t range;

		void setActive(bool standby);
		byte read(byte reg);
		void readMultiple(byte reg, byte *buffer, uint8_t numBytes);
		void write(byte reg, byte value);

		float convertGCounts(uint16_t data);
};

#endif // MMA8452_H_