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
		uint8_t weaponId = 0; // Only 6 trailing bits used
		uint8_t yesNo = 0; // Only 2 trailing bits used, which are the 2 leading bits from weaponId
		uint8_t specialAction = 0;
		float velocity[3] = {0.0, 0.0, 0.0};
		float surfing[3] = {0.0, 0.0, 0.0};
		uint16_t surfingVehicleId = 0;
		uint16_t animationId = 0;
		float animationDelta = 0.0; // Only 8 trailing bits used
		bool animationLoop = false; // Only 1 trailing bit used (0 = play animation once, 1 = loop animation)
		bool animationLock[2] = {false, false}; // Only 1 trailing bit used (0 = return to old coordinate on animation end, 1 = don't return to old coordinate on animation end)
		bool animationFreeze = false; // Only 1 trailing bit used (0 = freeze on animation end, 1 = don't freeze on animation end)
		uint8_t animationTime = 0; // Only 4 trailing bits used

};

#endif