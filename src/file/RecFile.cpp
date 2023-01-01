#include "RecFile.h"
#include <filesystem>

namespace fs = std::filesystem;

RecFile::RecFile(const string &name) :
	// Call base class method
	File::File(name, true) {
}

void RecFile::loadData(vector<DataBlock*> &data) {
	// Read header
	HeaderDataBlock *header = new HeaderDataBlock();
	input.read((char*)&header->version, sizeof(header->version));
	input.read((char*)&header->type, sizeof(header->type));
	data.emplace_back(header);

	// Check file size
	bool corrupt = false;
	uintmax_t size = fs::file_size(name);
	switch (header->type) {
		case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
			if ((size-8) % 72 != 0) {
				corrupt = true;
				delete header;
				data.clear();
			}
			break;
		}
		case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
			if ((size-8) % 67 != 0) {
				corrupt = true;
				delete header;
				data.clear();
			}
			break;
		}
	}

	// Read data
	if (!corrupt) {
		bool hydra = true;
		while (input.peek() != EOF) {
			switch (header->type) {
				case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
					OnFootDataBlock *onFoot = new OnFootDataBlock();
					input.read((char*)&onFoot->time, sizeof(onFoot->time));
					input.read((char*)&onFoot->leftRight, sizeof(onFoot->leftRight));
					input.read((char*)&onFoot->upDown, sizeof(onFoot->upDown));
					input.read((char*)&onFoot->keys, sizeof(onFoot->keys));
					input.read((char*)&onFoot->position, sizeof(onFoot->position));
					input.read((char*)&onFoot->rotation, sizeof(onFoot->rotation));
					input.read((char*)&onFoot->health, sizeof(onFoot->health));
					input.read((char*)&onFoot->armour, sizeof(onFoot->armour));
					input.read((char*)&onFoot->weaponIdYesNoBack, sizeof(onFoot->weaponIdYesNoBack));
					input.read((char*)&onFoot->specialAction, sizeof(onFoot->specialAction));
					input.read((char*)&onFoot->velocity, sizeof(onFoot->velocity));
					input.read((char*)&onFoot->surfing, sizeof(onFoot->surfing));
					input.read((char*)&onFoot->surfingId, sizeof(onFoot->surfingId));
					input.read((char*)&onFoot->animationId, sizeof(onFoot->animationId));
					input.read((char*)&onFoot->animationFlags, sizeof(onFoot->animationFlags));
					data.emplace_back(onFoot);
					break;
				}
				case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
					VehicleDataBlock *vehicle = new VehicleDataBlock();
					input.read((char*)&vehicle->time, sizeof(vehicle->time));
					input.read((char*)&vehicle->vehicleId, sizeof(vehicle->vehicleId));
					input.read((char*)&vehicle->leftRight, sizeof(vehicle->leftRight));
					input.read((char*)&vehicle->upDown, sizeof(vehicle->upDown));
					input.read((char*)&vehicle->keys, sizeof(vehicle->keys));
					input.read((char*)&vehicle->rotation, sizeof(vehicle->rotation));
					input.read((char*)&vehicle->position, sizeof(vehicle->position));
					input.read((char*)&vehicle->velocity, sizeof(vehicle->velocity));
					input.read((char*)&vehicle->vehicleHealth, sizeof(vehicle->vehicleHealth));
					input.read((char*)&vehicle->health, sizeof(vehicle->health));
					input.read((char*)&vehicle->armour, sizeof(vehicle->armour));
					input.read((char*)&vehicle->weaponIdYesNoBack, sizeof(vehicle->weaponIdYesNoBack));
					input.read((char*)&vehicle->sirenState, sizeof(vehicle->sirenState));
					input.read((char*)&vehicle->gearState, sizeof(vehicle->gearState));
					input.read((char*)&vehicle->trailerId, sizeof(vehicle->trailerId));
					input.read((char*)&vehicle->hydraThrustAngleTrainSpeed, sizeof(vehicle->hydraThrustAngleTrainSpeed));
					if (vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[0] > 5000 || vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[1] > 5000) {
						hydra = false;
					}
					data.emplace_back(vehicle);
					break;
				}
			}
		}
		if (header->type == PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER) {
			header->hydra = hydra;
		}
	}
}

void RecFile::saveData(const vector<DataBlock*> &data) {
	// Write header
	HeaderDataBlock *header = (HeaderDataBlock*)data[0];
	output.write((char*)&header->version, sizeof(header->version));
	output.write((char*)&header->type, sizeof(header->type));

	// Write data
	for (int i = 1, n = data.size(); i < n; i++) {
		switch (header->type) {
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
				OnFootDataBlock *onFoot = (OnFootDataBlock*)data[i];
				output.write((char*)&onFoot->time, sizeof(onFoot->time));
				output.write((char*)&onFoot->leftRight, sizeof(onFoot->leftRight));
				output.write((char*)&onFoot->upDown, sizeof(onFoot->upDown));
				output.write((char*)&onFoot->keys, sizeof(onFoot->keys));
				output.write((char*)&onFoot->position, sizeof(onFoot->position));
				output.write((char*)&onFoot->rotation, sizeof(onFoot->rotation));
				output.write((char*)&onFoot->health, sizeof(onFoot->health));
				output.write((char*)&onFoot->armour, sizeof(onFoot->armour));
				output.write((char*)&onFoot->weaponIdYesNoBack, sizeof(onFoot->weaponIdYesNoBack));
				output.write((char*)&onFoot->specialAction, sizeof(onFoot->specialAction));
				output.write((char*)&onFoot->velocity, sizeof(onFoot->velocity));
				output.write((char*)&onFoot->surfing, sizeof(onFoot->surfing));
				output.write((char*)&onFoot->surfingId, sizeof(onFoot->surfingId));
				output.write((char*)&onFoot->animationId, sizeof(onFoot->animationId));
				output.write((char*)&onFoot->animationFlags, sizeof(onFoot->animationFlags));
				break;
			}
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
				VehicleDataBlock *vehicle = (VehicleDataBlock*)data[i];
				output.write((char*)&vehicle->time, sizeof(vehicle->time));
				output.write((char*)&vehicle->vehicleId, sizeof(vehicle->vehicleId));
				output.write((char*)&vehicle->leftRight, sizeof(vehicle->leftRight));
				output.write((char*)&vehicle->upDown, sizeof(vehicle->upDown));
				output.write((char*)&vehicle->keys, sizeof(vehicle->keys));
				output.write((char*)&vehicle->rotation, sizeof(vehicle->rotation));
				output.write((char*)&vehicle->position, sizeof(vehicle->position));
				output.write((char*)&vehicle->velocity, sizeof(vehicle->velocity));
				output.write((char*)&vehicle->vehicleHealth, sizeof(vehicle->vehicleHealth));
				output.write((char*)&vehicle->health, sizeof(vehicle->health));
				output.write((char*)&vehicle->armour, sizeof(vehicle->armour));
				output.write((char*)&vehicle->weaponIdYesNoBack, sizeof(vehicle->weaponIdYesNoBack));
				output.write((char*)&vehicle->sirenState, sizeof(vehicle->sirenState));
				output.write((char*)&vehicle->gearState, sizeof(vehicle->gearState));
				output.write((char*)&vehicle->trailerId, sizeof(vehicle->trailerId));
				output.write((char*)&vehicle->hydraThrustAngleTrainSpeed, sizeof(vehicle->hydraThrustAngleTrainSpeed));
				break;
			}
		}
	}
}