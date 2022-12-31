#ifndef HEADER_DATA_BLOCK_H
#define HEADER_DATA_BLOCK_H

#include "DataBlock.h"

class HeaderDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t version = 0;
		uint32_t type = 0;
		bool hydra = false; // Custom field not present in .rec file

};

#endif