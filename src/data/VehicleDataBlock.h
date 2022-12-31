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
		uint8_t weaponId = 0; // Only 6 trailing bits used
		uint8_t yesNo = 0; // Only 2 trailing bits used, which are the 2 leading bits from weaponId
		bool sirenState = false; // Full 8 bits wide (0 = siren off, 1 = siren on)
		bool gearState = false; // Full 8 bits wide (0 = gear down, 1 = gear up)
		uint16_t trailerId = 0;
		union {
			uint16_t hydraReactorAngle[2] = {0, 0}; // 0 to 5000
			float trainSpeed; // -1.0 to 1.0
		};

};

#endif