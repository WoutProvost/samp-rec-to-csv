#include "CsvFile.h"
#include <sstream>
#include <iomanip>
#include <limits>

using std::stringstream;
using std::stoi;
using std::stof;
using std::setprecision;
using std::numeric_limits;

CsvFile::CsvFile(const string &name) :
	// Call base class method
	File::File(name, false) {
}

vector<string> CsvFile::readLine() {
	string line;
	string field;
	vector<string> fields;

	// Get a single non-comment line
	getline(input, line);
	if (line[0] == '#') {
		getline(input, line);
	}

	// Split it into fields
	stringstream stream(line);
	while (getline(stream, field, ',')) {
		fields.push_back(field);
	}

	return fields;
}

void CsvFile::loadData(vector<DataBlock*> &data) {
	vector<string> fields = readLine();
	if (fields.size() >= 2 && fields.size() <= 3) {
		bool corrupt = false;

		// Read header
		HeaderDataBlock *header = new HeaderDataBlock();
		header->version = stoi(fields[0]);
		header->type = stoi(fields[1]);
		switch (header->type) {
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
				if (fields.size() != 2) {
					corrupt = true;
				}
				break;
			}
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
				if (fields.size() != 3) {
					corrupt = true;
				} else {
					header->hydra = stoi(fields[2]);
				}
				break;
			}
		}
		data.emplace_back(header);
		if (corrupt) {
			delete header;
			data.clear();
		}

		// Read data
		while (input.peek() != EOF && !corrupt) {
			fields = readLine();
			switch (header->type) {
				case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
					// Check amount of fields
					if (fields.size() != 30) {
						corrupt = true;
						for (auto block : data) {
							delete block;
						}
						data.clear();
						break;
					}

					OnFootDataBlock *onFoot = new OnFootDataBlock();
					onFoot->time = stoi(fields[0]);
					onFoot->leftRight = stoi(fields[1]);
					onFoot->upDown = stoi(fields[2]);
					onFoot->keys = stoi(fields[3]);
					onFoot->position[0] = stof(fields[4]);
					onFoot->position[1] = stof(fields[5]);
					onFoot->position[2] = stof(fields[6]);
					onFoot->rotation[0] = stof(fields[7]);
					onFoot->rotation[1] = stof(fields[8]);
					onFoot->rotation[2] = stof(fields[9]);
					onFoot->rotation[3] = stof(fields[10]);
					onFoot->health = stoi(fields[11]);
					onFoot->armour = stoi(fields[12]);
					onFoot->weaponIdYesNoBack.weaponId = stoi(fields[13]);
					onFoot->weaponIdYesNoBack.yesNoBack = stoi(fields[14]);
					onFoot->specialAction = stoi(fields[15]);
					onFoot->velocity[0] = stof(fields[16]);
					onFoot->velocity[1] = stof(fields[17]);
					onFoot->velocity[2] = stof(fields[18]);
					onFoot->surfing[0] = stof(fields[19]);
					onFoot->surfing[1] = stof(fields[20]);
					onFoot->surfing[2] = stof(fields[21]);
					onFoot->surfingId = stoi(fields[22]);
					onFoot->animationId = stoi(fields[23]);
					onFoot->animationFlags.animationDelta = stoi(fields[24]);
					onFoot->animationFlags.animationLoop = stoi(fields[25]);
					onFoot->animationFlags.animationLockX = stoi(fields[26]);
					onFoot->animationFlags.animationLockY = stoi(fields[27]);
					onFoot->animationFlags.animationFreeze = stoi(fields[28]);
					onFoot->animationFlags.animationTime = stoi(fields[29]);
					data.emplace_back(onFoot);
					break;
				}
				case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
					// Check amount of fields
					if ((header->hydra && fields.size() != 25) || (!header->hydra && fields.size() != 24)) {
						corrupt = true;
						for (auto block : data) {
							delete block;
						}
						data.clear();
						break;
					}

					VehicleDataBlock *vehicle = new VehicleDataBlock();
					vehicle->time = stoi(fields[0]);
					vehicle->vehicleId = stoi(fields[1]);
					vehicle->leftRight = stoi(fields[2]);
					vehicle->upDown = stoi(fields[3]);
					vehicle->keys = stoi(fields[4]);
					vehicle->rotation[0] = stof(fields[5]);
					vehicle->rotation[1] = stof(fields[6]);
					vehicle->rotation[2] = stof(fields[7]);
					vehicle->rotation[3] = stof(fields[8]);
					vehicle->position[0] = stof(fields[9]);
					vehicle->position[1] = stof(fields[10]);
					vehicle->position[2] = stof(fields[11]);
					vehicle->velocity[0] = stof(fields[12]);
					vehicle->velocity[1] = stof(fields[13]);
					vehicle->velocity[2] = stof(fields[14]);
					vehicle->vehicleHealth = stof(fields[15]);
					vehicle->health = stoi(fields[16]);
					vehicle->armour = stoi(fields[17]);
					vehicle->weaponIdYesNoBack.weaponId = stoi(fields[18]);
					vehicle->weaponIdYesNoBack.yesNoBack = stoi(fields[19]);
					vehicle->sirenState = stoi(fields[20]);
					vehicle->gearState = stoi(fields[21]);
					vehicle->trailerId = stoi(fields[22]);
					if (header->hydra) {
						vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[0] = stoi(fields[23]);
						vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[1] = stoi(fields[24]);
					} else {
						vehicle->hydraThrustAngleTrainSpeed.trainSpeed = stof(fields[23]);
					}
					data.emplace_back(vehicle);
					break;
				}
			}
		}
	}
}

void CsvFile::saveData(const vector<DataBlock*> &data) {
	// Set floating point precision
	output << setprecision(numeric_limits<float>::max_digits10);

	// Write header
	HeaderDataBlock *header = (HeaderDataBlock*)data[0];
	output << "#"
		<< "version,"
		<< "type"
	;
	if (header->type == PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER) {
		output << ","
			<< "hydra"
			<< "\n"
		;
	} else {
		output
			<< "\n"
		;
	}
	output
		<< header->version << ","
		<< header->type
	;
	if (header->type == PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER) {
		output << ","
			<< header->hydra
			<< "\n"
		;
	} else {
		output
			<< "\n"
		;
	}

	// Write data
	switch (header->type) {
		case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
			output << "#"
				<< "time,"
				<< "leftRight,"
				<< "upDown,"
				<< "keys,"
				<< "positionX,"
				<< "positionY,"
				<< "positionZ,"
				<< "rotationW,"
				<< "rotationX,"
				<< "rotationY,"
				<< "rotationZ,"
				<< "health,"
				<< "armour,"
				<< "weaponId,"
				<< "yesNoBack,"
				<< "specialAction,"
				<< "velocityX,"
				<< "velocityY,"
				<< "velocityZ,"
				<< "surfingX,"
				<< "surfingY,"
				<< "surfingZ,"
				<< "surfingId,"
				<< "animationId,"
				<< "animationDelta,"
				<< "animationLoop,"
				<< "animationLockX,"
				<< "animationLockY,"
				<< "animationFreeze,"
				<< "animationTime"
				<< "\n"
			;
			break;
		}
		case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
			output << "#"
				<< "time,"
				<< "vehicleId,"
				<< "leftRight,"
				<< "upDown,"
				<< "keys,"
				<< "rotationW,"
				<< "rotationX,"
				<< "rotationY,"
				<< "rotationZ,"
				<< "positionX,"
				<< "positionY,"
				<< "positionZ,"
				<< "velocityX,"
				<< "velocityY,"
				<< "velocityZ,"
				<< "vehicleHealth,"
				<< "health,"
				<< "armour,"
				<< "weaponId,"
				<< "yesNoBack,"
				<< "sirenState,"
				<< "gearState,"
				<< "trailerId,"
			;
			if (header->hydra) {
				output
					<< "hydraThrustAngle0,"
					<< "hydraThrustAngle1"
					<< "\n"
				;
			} else {
				output
					<< "trainSpeed"
					<< "\n"
				;
			}
			break;
		}
	}
	for (int i = 1, n = data.size(); i < n; i++) {
		switch (header->type) {
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
				OnFootDataBlock *onFoot = (OnFootDataBlock*)data[i];
				output
					<< onFoot->time << ","
					<< onFoot->leftRight << ","
					<< onFoot->upDown << ","
					<< onFoot->keys << ","
					<< onFoot->position[0] << ","
					<< onFoot->position[1] << ","
					<< onFoot->position[2] << ","
					<< onFoot->rotation[0] << ","
					<< onFoot->rotation[1] << ","
					<< onFoot->rotation[2] << ","
					<< onFoot->rotation[3] << ","
					<< +onFoot->health << ","
					<< +onFoot->armour << ","
					<< +onFoot->weaponIdYesNoBack.weaponId << ","
					<< +onFoot->weaponIdYesNoBack.yesNoBack << ","
					<< +onFoot->specialAction << ","
					<< onFoot->velocity[0] << ','
					<< onFoot->velocity[1] << ','
					<< onFoot->velocity[2] << ','
					<< onFoot->surfing[0] << ','
					<< onFoot->surfing[1] << ','
					<< onFoot->surfing[2] << ','
					<< onFoot->surfingId << ","
					<< onFoot->animationId << ","
					<< +onFoot->animationFlags.animationDelta << ","
					<< onFoot->animationFlags.animationLoop << ","
					<< onFoot->animationFlags.animationLockX << ","
					<< onFoot->animationFlags.animationLockY << ","
					<< onFoot->animationFlags.animationFreeze << ","
					<< +onFoot->animationFlags.animationTime
					<< "\n"
				;
				break;
			}
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
				VehicleDataBlock *vehicle = (VehicleDataBlock*)data[i];
				output
					<< vehicle->time << ","
					<< vehicle->vehicleId << ","
					<< vehicle->leftRight << ","
					<< vehicle->upDown << ","
					<< vehicle->keys << ","
					<< vehicle->rotation[0] << ","
					<< vehicle->rotation[1] << ","
					<< vehicle->rotation[2] << ","
					<< vehicle->rotation[3] << ","
					<< vehicle->position[0] << ","
					<< vehicle->position[1] << ","
					<< vehicle->position[2] << ","
					<< vehicle->velocity[0] << ','
					<< vehicle->velocity[1] << ','
					<< vehicle->velocity[2] << ','
					<< vehicle->vehicleHealth << ","
					<< +vehicle->health << ","
					<< +vehicle->armour << ","
					<< +vehicle->weaponIdYesNoBack.weaponId << ","
					<< +vehicle->weaponIdYesNoBack.yesNoBack << ","
					<< +vehicle->sirenState << ","
					<< +vehicle->gearState << ","
					<< vehicle->trailerId << ","
				;
				if (header->hydra) {
					output
						<< vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[0] << ","
						<< vehicle->hydraThrustAngleTrainSpeed.hydraThrustAngle[1]
						<< "\n"
					;
				} else {
					output
						<< vehicle->hydraThrustAngleTrainSpeed.trainSpeed
						<< "\n"
					;
				}
				break;
			}
		}
	}
}