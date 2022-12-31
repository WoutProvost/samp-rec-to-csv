#ifndef VEHICLE_DATA_BLOCK_H
#define VEHICLE_DATA_BLOCK_H

#include "DataBlock.h"

class VehicleDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t time = 0;
		uint16_t vehicleId = 0;
		int16_t leftRight = 0;
		int16_t upDown = 0;
		uint16_t keys = 0;
		float angle[4] = {0.0, 0.0, 0.0, 0.0};
		float position[3] = {0.0, 0.0, 0.0};
		float velocity[3] = {0.0, 0.0, 0.0};
		float vehicleHealth = 0.0;
		uint8_t health = 0;
		uint8_t armour = 0;
		uint8_t weaponId = 0;
		uint8_t weaponUnknown = 0;
		uint16_t trailerId = 0;
		union {
			uint16_t hydraReactorAngle[2] = {0, 0};
			float trainSpeed;
		};

};

#endif