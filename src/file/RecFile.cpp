#include "RecFile.h"

RecFile::RecFile(const string &name) :
	// Call base class method
	File::File(name, true) {
}

vector<DataBlock*> RecFile::load() {
	// Call base class method
	vector<DataBlock*> data = File::load();

	// Read header
	HeaderDataBlock *header = new HeaderDataBlock();
	input.read((char*)&header->version, sizeof(header->version));
	input.read((char*)&header->type, sizeof(header->type));
	data.emplace_back(header);

	// Read data
	while (input.peek() != EOF) {
		switch (header->type) {
			case HeaderType::ONFOOT: {
				OnFootDataBlock *onFoot = new OnFootDataBlock();				
				input.read((char*)&onFoot->time, sizeof(onFoot->time));
				input.read((char*)&onFoot->leftRight, sizeof(onFoot->leftRight));
				input.read((char*)&onFoot->upDown, sizeof(onFoot->upDown));
				input.read((char*)&onFoot->keys, sizeof(onFoot->keys));
				input.read((char*)&onFoot->position, sizeof(onFoot->position));
				input.read((char*)&onFoot->angle, sizeof(onFoot->angle));
				input.read((char*)&onFoot->health, sizeof(onFoot->health));
				input.read((char*)&onFoot->armour, sizeof(onFoot->armour));
				input.read((char*)&onFoot->weaponId, sizeof(onFoot->weaponId));
				input.read((char*)&onFoot->specialAction, sizeof(onFoot->specialAction));
				input.read((char*)&onFoot->velocity, sizeof(onFoot->velocity));
				input.read((char*)&onFoot->surfing, sizeof(onFoot->surfing));
				input.read((char*)&onFoot->surfingVehicleId, sizeof(onFoot->surfingVehicleId));
				input.read((char*)&onFoot->animationId, sizeof(onFoot->animationId));
				uint16_t animationFlags = 0;
				input.read((char*)&animationFlags, sizeof(animationFlags));
				onFoot->animationDelta = (float)(animationFlags & 0xFF);
				onFoot->animationLoop = (animationFlags >> 8 & 0x1) != 0;
				onFoot->animationLock[0] = (animationFlags >> 9 & 0x1) != 0;
				onFoot->animationLock[1] = (animationFlags >> 10 & 0x1) != 0;
				onFoot->animationFreeze = (animationFlags >> 11 & 0x1) != 0;
				onFoot->animationTime = (animationFlags >> 12 & 0xF);
				data.emplace_back(onFoot);
				break;
			}
			case HeaderType::DRIVER: {
				VehicleDataBlock *vehicle = new VehicleDataBlock();
				input.read((char*)&vehicle->time, sizeof(vehicle->time));
				input.read((char*)&vehicle->vehicleId, sizeof(vehicle->vehicleId));
				input.read((char*)&vehicle->leftRight, sizeof(vehicle->leftRight));
				input.read((char*)&vehicle->upDown, sizeof(vehicle->upDown));
				input.read((char*)&vehicle->keys, sizeof(vehicle->keys));
				input.read((char*)&vehicle->angle, sizeof(vehicle->angle));
				input.read((char*)&vehicle->position, sizeof(vehicle->position));
				input.read((char*)&vehicle->velocity, sizeof(vehicle->velocity));
				input.read((char*)&vehicle->vehicleHealth, sizeof(vehicle->vehicleHealth));
				input.read((char*)&vehicle->health, sizeof(vehicle->health));
				input.read((char*)&vehicle->armour, sizeof(vehicle->armour));
				input.read((char*)&vehicle->weaponId, sizeof(vehicle->weaponId));
				input.read((char*)&vehicle->sirenState, sizeof(vehicle->sirenState));
				input.read((char*)&vehicle->gearState, sizeof(vehicle->gearState));
				input.read((char*)&vehicle->trailerId, sizeof(vehicle->trailerId));
				uint32_t hydraReactorAngleAndTrainSpeed = 0;
				input.read((char*)&hydraReactorAngleAndTrainSpeed, sizeof(hydraReactorAngleAndTrainSpeed));
				vehicle->hydraReactorAngle[0] = hydraReactorAngleAndTrainSpeed & 0xFFFF;
				vehicle->hydraReactorAngle[1] = hydraReactorAngleAndTrainSpeed >> 16 & 0xFFFF;
				vehicle->trainSpeed = (float)hydraReactorAngleAndTrainSpeed;
				data.emplace_back(vehicle);
				break;
			}
		}
	}

	input.close();
	return data;
}

void RecFile::save(const vector<DataBlock*> &data) {
	// Call base class method
	File::save(data);

	// Write header
	HeaderDataBlock *header = (HeaderDataBlock*)data[0];
	output.write((char*)&header->version, sizeof(header->version));
	output.write((char*)&header->type, sizeof(header->type));

	// Write data
	for (int i = 1, n = data.size(); i < n; i++) {
		switch (header->type) {
			case HeaderType::ONFOOT: {
				OnFootDataBlock *onFoot = (OnFootDataBlock*)data[i];
				output.write((char*)&onFoot->time, sizeof(onFoot->time));
				output.write((char*)&onFoot->leftRight, sizeof(onFoot->leftRight));
				output.write((char*)&onFoot->upDown, sizeof(onFoot->upDown));
				output.write((char*)&onFoot->keys, sizeof(onFoot->keys));
				output.write((char*)&onFoot->position, sizeof(onFoot->position));
				output.write((char*)&onFoot->angle, sizeof(onFoot->angle));
				output.write((char*)&onFoot->health, sizeof(onFoot->health));
				output.write((char*)&onFoot->armour, sizeof(onFoot->armour));
				output.write((char*)&onFoot->weaponId, sizeof(onFoot->weaponId));
				output.write((char*)&onFoot->specialAction, sizeof(onFoot->specialAction));
				output.write((char*)&onFoot->velocity, sizeof(onFoot->velocity));
				output.write((char*)&onFoot->surfing, sizeof(onFoot->surfing));
				output.write((char*)&onFoot->surfingVehicleId, sizeof(onFoot->surfingVehicleId));
				output.write((char*)&onFoot->animationId, sizeof(onFoot->animationId));
				uint16_t animationFlags = ((uint8_t)onFoot->animationDelta & 0xFF)
										| (onFoot->animationLoop << 8)
										| (onFoot->animationLock[0] << 9)
										| (onFoot->animationLock[1] << 10)
										| (onFoot->animationFreeze << 11)
										| (onFoot->animationTime << 12);
				output.write((char*)&animationFlags, sizeof(animationFlags));
				break;
			}
			case HeaderType::DRIVER: {
				VehicleDataBlock *vehicle = (VehicleDataBlock*)data[i];
				output.write((char*)&vehicle->time, sizeof(vehicle->time));
				output.write((char*)&vehicle->vehicleId, sizeof(vehicle->vehicleId));
				output.write((char*)&vehicle->leftRight, sizeof(vehicle->leftRight));
				output.write((char*)&vehicle->upDown, sizeof(vehicle->upDown));
				output.write((char*)&vehicle->keys, sizeof(vehicle->keys));
				output.write((char*)&vehicle->angle, sizeof(vehicle->angle));
				output.write((char*)&vehicle->position, sizeof(vehicle->position));
				output.write((char*)&vehicle->velocity, sizeof(vehicle->velocity));
				output.write((char*)&vehicle->vehicleHealth, sizeof(vehicle->vehicleHealth));
				output.write((char*)&vehicle->health, sizeof(vehicle->health));
				output.write((char*)&vehicle->armour, sizeof(vehicle->armour));
				output.write((char*)&vehicle->weaponId, sizeof(vehicle->weaponId));
				output.write((char*)&vehicle->sirenState, sizeof(vehicle->sirenState));
				output.write((char*)&vehicle->gearState, sizeof(vehicle->gearState));
				output.write((char*)&vehicle->trailerId, sizeof(vehicle->trailerId));
				uint32_t hydraReactorAngleAndTrainSpeed = vehicle->hydraReactorAngle[0]
														| (vehicle->hydraReactorAngle[1] << 16)
														| (uint32_t)vehicle->trainSpeed;
				output.write((char*)&hydraReactorAngleAndTrainSpeed, sizeof(hydraReactorAngleAndTrainSpeed));
				break;
			}
		}
	}

	output.close();
}