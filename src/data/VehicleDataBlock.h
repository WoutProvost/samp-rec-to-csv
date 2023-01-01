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
		struct {
			uint8_t weaponId : 6;
			uint8_t yesNo : 2;
		} weaponIdYesNo;
		bool sirenState; // 0 = siren off, 1 = siren on
		bool gearState; // 0 = gear down, 1 = gear up
		uint16_t trailerId;
		union {
			uint16_t hydraReactorAngle[2]; // 0 to 5000
			float trainSpeed; // -1.0 to 1.0
		};

};

#endif