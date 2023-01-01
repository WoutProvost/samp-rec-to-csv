#ifndef VEHICLE_DATA_BLOCK_H
#define VEHICLE_DATA_BLOCK_H

#include "DataBlock.h"

class VehicleDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t time;
		uint16_t vehicleId;
		int16_t leftRight;
		int16_t upDown;
		uint16_t keys;
		float angle[4];
		float position[3];
		float velocity[3];
		float vehicleHealth;
		uint8_t health;
		uint8_t armour;
		uint8_t weaponId; // Only 6 trailing bits used
		uint8_t yesNo; // Only 2 trailing bits used, which are the 2 leading bits from weaponId
		bool sirenState; // Full 8 bits wide (0 = siren off, 1 = siren on)
		bool gearState; // Full 8 bits wide (0 = gear down, 1 = gear up)
		uint16_t trailerId;
		union {
			uint16_t hydraReactorAngle[2]; // 0 to 5000
			float trainSpeed; // -1.0 to 1.0
		};

};

#endif