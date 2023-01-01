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
		uint16_t surfingId;
		uint16_t animationId;
		struct {
			uint8_t animationDelta;
			bool animationLoop : 1; // 0 = play animation once, 1 = loop animation
			bool animationLockX : 1; // 0 = return to old coordinate on animation end, 1 = don't return to old coordinate on animation end
			bool animationLockY : 1; // 0 = return to old coordinate on animation end, 1 = don't return to old coordinate on animation end
			bool animationFreeze : 1; // 0 = freeze on animation end, 1 = don't freeze on animation end
			uint8_t animationTime : 4;
		} animationFlags;

};

#endif