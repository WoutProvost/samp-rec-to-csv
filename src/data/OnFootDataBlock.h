#ifndef ON_FOOT_DATA_BLOCK_H
#define ON_FOOT_DATA_BLOCK_H

#include "DataBlock.h"

class OnFootDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t time = 0;
		int16_t leftRight = 0;
		int16_t upDown = 0;
		uint16_t keys = 0;
		float position[3] = {0.0, 0.0, 0.0};
		float angle[4] = {0.0, 0.0, 0.0, 0.0};
		uint8_t health = 0;
		uint8_t armour = 0;
		uint8_t weaponId = 0;
		uint8_t specialAction = 0;
		float velocity[3] = {0.0, 0.0, 0.0};
		float surfing[3] = {0.0, 0.0, 0.0};
		uint16_t surfingVehicleId = 0;
		uint16_t animationId = 0;
		float animationDelta = 0.0;
		bool animationLoop = false;
		bool animationLock[2] = {false, false};
		bool animationFreeze = false;
		uint8_t animationTime = 0;

};

#endif