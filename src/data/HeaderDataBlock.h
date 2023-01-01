#ifndef HEADER_DATA_BLOCK_H
#define HEADER_DATA_BLOCK_H

#include "DataBlock.h"

class HeaderDataBlock : public DataBlock {

	public:
		// Fields
		uint32_t version;
		uint32_t type;
		bool hydra; // Custom field not present in .rec file

};

#endif