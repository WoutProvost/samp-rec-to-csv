#ifndef ON_FOOT_DATA_BLOCK_H
#define ON_FOOT_DATA_BLOCK_H

#include "DataBlock.h"

class OnFootDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t time;
		int16_t leftRight;
		int16_t upDown;
		uint16_t keys;
		float position[3];
		float angle[4];
		uint8_t health;
		uint8_t armour;
		struct {
			uint8_t weaponId : 6;
			uint8_t yesNo : 2;
		} weaponIdYesNo;
		uint8_t specialAction;
		float velocity[3];
		float surfing[3];
		uint16_t surfingVehicleId;
		uint16_t animationId;
		float animationDelta; // Only 8 trailing bits used
		bool animationLoop; // Only 1 trailing bit used (0 = play animation once, 1 = loop animation)
		bool animationLock[2]; // Only 1 trailing bit used (0 = return to old coordinate on animation end, 1 = don't return to old coordinate on animation end)
		bool animationFreeze; // Only 1 trailing bit used (0 = freeze on animation end, 1 = don't freeze on animation end)
		uint8_t animationTime; // Only 4 trailing bits used

};

#endif