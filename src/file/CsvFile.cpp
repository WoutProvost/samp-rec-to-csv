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

vector<DataBlock*> CsvFile::load() {
	// Call base class method
	vector<DataBlock*> data = File::load();

	// Read header
	vector<string> fields = readLine();
	HeaderDataBlock *header = new HeaderDataBlock();
	header->version = stoi(fields[0]);
	header->type = stoi(fields[1]);
	if (header->type == PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER) {
		header->hydra = stoi(fields[2]);
	}
	data.emplace_back(header);

	// Read data
	while (input.peek() != EOF) {
		fields = readLine();
		switch (header->type) {
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_ONFOOT: {
				OnFootDataBlock *onFoot = new OnFootDataBlock();
				onFoot->time = stoi(fields[0]);
				onFoot->leftRight = stoi(fields[1]);
				onFoot->upDown = stoi(fields[2]);
				onFoot->keys = stoi(fields[3]);
				onFoot->position[0] = stof(fields[4]);
				onFoot->position[1] = stof(fields[5]);
				onFoot->position[2] = stof(fields[6]);
				onFoot->angle[0] = stof(fields[7]);
				onFoot->angle[1] = stof(fields[8]);
				onFoot->angle[2] = stof(fields[9]);
				onFoot->angle[3] = stof(fields[10]);
				onFoot->health = stoi(fields[11]);
				onFoot->armour = stoi(fields[12]);
				onFoot->weaponId = stoi(fields[13]);
				onFoot->specialAction = stoi(fields[14]);
				onFoot->velocity[0] = stof(fields[15]);
				onFoot->velocity[1] = stof(fields[16]);
				onFoot->velocity[2] = stof(fields[17]);
				onFoot->surfing[0] = stof(fields[18]);
				onFoot->surfing[1] = stof(fields[19]);
				onFoot->surfing[2] = stof(fields[20]);
				onFoot->surfingVehicleId = stoi(fields[21]);
				onFoot->animationId = stoi(fields[22]);
				onFoot->animationDelta = stof(fields[23]);
				onFoot->animationLoop = stoi(fields[24]);
				onFoot->animationLock[0] = stoi(fields[25]);
				onFoot->animationLock[1] = stoi(fields[26]);
				onFoot->animationFreeze = stoi(fields[27]);
				onFoot->animationTime = stoi(fields[28]);
				data.emplace_back(onFoot);
				break;
			}
			case PlayerRecordingType::PLAYER_RECORDING_TYPE_DRIVER: {
				VehicleDataBlock *vehicle = new VehicleDataBlock();
				vehicle->time = stoi(fields[0]);
				vehicle->vehicleId = stoi(fields[1]);
				vehicle->leftRight = stoi(fields[2]);
				vehicle->upDown = stoi(fields[3]);
				vehicle->keys = stoi(fields[4]);
				vehicle->angle[0] = stof(fields[5]);
				vehicle->angle[1] = stof(fields[6]);
				vehicle->angle[2] = stof(fields[7]);
				vehicle->angle[3] = stof(fields[8]);
				vehicle->position[0] = stof(fields[9]);
				vehicle->position[1] = stof(fields[10]);
				vehicle->position[2] = stof(fields[11]);
				vehicle->velocity[0] = stof(fields[12]);
				vehicle->velocity[1] = stof(fields[13]);
				vehicle->velocity[2] = stof(fields[14]);
				vehicle->vehicleHealth = stof(fields[15]);
				vehicle->health = stoi(fields[16]);
				vehicle->armour = stoi(fields[17]);
				vehicle->weaponId = stoi(fields[18]);
				vehicle->sirenState = stoi(fields[19]);
				vehicle->gearState = stoi(fields[20]);
				vehicle->trailerId = stoi(fields[21]);
				if (header->hydra) {
					vehicle->hydraReactorAngle[0] = stoi(fields[22]);
					vehicle->hydraReactorAngle[1] = stoi(fields[23]);
				} else {
					vehicle->trainSpeed = stof(fields[22]);
				}
				data.emplace_back(vehicle);
				break;
			}
		}
	}

	input.close();
	return data;
}

void CsvFile::save(const vector<DataBlock*> &data) {
	// Call base class method
	File::save(data);

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
				<< "angleW,"
				<< "angleX,"
				<< "angleY,"
				<< "angleZ,"
				<< "health,"
				<< "armour,"
				<< "weaponId,"
				<< "specialAction,"
				<< "velocityX,"
				<< "velocityY,"
				<< "velocityZ,"
				<< "surfingX,"
				<< "surfingY,"
				<< "surfingZ,"
				<< "surfingVehicleId,"
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
				<< "angleW,"
				<< "angleX,"
				<< "angleY,"
				<< "angleZ,"
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
				<< "sirenState,"
				<< "gearState,"
				<< "trailerId,"
			;
			if (header->hydra) {
				output
					<< "hydraReactorAngle0,"
					<< "hydraReactorAngle1"
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
					<< onFoot->angle[0] << ","
					<< onFoot->angle[1] << ","
					<< onFoot->angle[2] << ","
					<< onFoot->angle[3] << ","
					<< +onFoot->health << ","
					<< +onFoot->armour << ","
					<< +onFoot->weaponId << ","
					<< +onFoot->specialAction << ","
					<< onFoot->velocity[0] << ','
					<< onFoot->velocity[1] << ','
					<< onFoot->velocity[2] << ','
					<< onFoot->surfing[0] << ','
					<< onFoot->surfing[1] << ','
					<< onFoot->surfing[2] << ','
					<< onFoot->surfingVehicleId << ","
					<< onFoot->animationId << ","
					<< onFoot->animationDelta << ","
					<< onFoot->animationLoop << ","
					<< onFoot->animationLock[0] << ","
					<< onFoot->animationLock[1] << ","
					<< onFoot->animationFreeze << ","
					<< +onFoot->animationTime
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
					<< vehicle->angle[0] << ","
					<< vehicle->angle[1] << ","
					<< vehicle->angle[2] << ","
					<< vehicle->angle[3] << ","
					<< vehicle->position[0] << ","
					<< vehicle->position[1] << ","
					<< vehicle->position[2] << ","
					<< vehicle->velocity[0] << ','
					<< vehicle->velocity[1] << ','
					<< vehicle->velocity[2] << ','
					<< vehicle->vehicleHealth << ","
					<< +vehicle->health << ","
					<< +vehicle->armour << ","
					<< +vehicle->weaponId << ","
					<< +vehicle->sirenState << ","
					<< +vehicle->gearState << ","
					<< vehicle->trailerId << ","
				;					
				if (header->hydra) {
					output
						<< vehicle->hydraReactorAngle[0] << ","
						<< vehicle->hydraReactorAngle[1]
						<< "\n"
					;
				} else {
					output
						<< vehicle->trainSpeed
						<< "\n"
					;
				}
				break;
			}
		}
	}

	output.close();
}