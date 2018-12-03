/*
Simple utility program to dump relevant information from the replay file,
including header data structure as well as the JSON into a formatted file.
*/

#include <iostream>
#include <fstream>
#include <cstring>

// Define the various datatypes as unsigned of specific bit length.
#define BYTE 	uint8_t
#define SHORT 	uint16_t
#define INT 	uint32_t
#define LONG	uint64_t

// Packing of bytes so we can read it in easily.
#pragma pack(push, r1, 1)
// File header, first 288 bytes.
struct FHeader {
	// ROFL File check.
	BYTE magicBytes[6];
	// Signature
	char signature[256];
	// Other information
	SHORT hLength;
	INT fLength;
	INT metadataOffset;
	INT metadataLength;
	INT dataHeaderOffset;
	INT dataHeaderLength;
	INT dataOffset;
};
#pragma pack(pop, r1)

// Packing bytes together so we can read it easily.
#pragma pack(push, r1, 1)
// Data header, 34 bytes. Encryption key is kept seperate.
struct DHeader {
	LONG gameID;
	INT gameLength; // Milliseconds
	INT keyframeCount;
	INT chunkCount;
	INT chunkID1;
	INT chunkID2;
	INT keyframeInterval; // Milliseconds
	SHORT encryptionKeyLength;
};
#pragma pack(pop, r1)

// Main program.
int main(int argc, char const *argv[]){

	// Create a file header.
	FHeader fh;

	// Create a data header.
	DHeader dh;

	// Create a stream and open in binary mode that was passed in.
	std::fstream replayFile;
	replayFile.open(argv[1], std::fstream::in | std::fstream::binary);
	replayFile.read((char *)&fh, sizeof(FHeader));

	// Valid magic bytes array.
	BYTE validMb[6] = {'R', 'I', 'O', 'T', ' ', ' '};

	// Print out the data and double check it.
	if(std::memcmp(fh.magicBytes, validMb, sizeof(fh.magicBytes))){
		// Print file header information.
		std::cout << "Valid replay file." << std::endl;
		std::cout << "Header length: " << fh.hLength << std::endl;
		std::cout << "File length: " << fh.fLength << std::endl; 
		std::cout << "Metadata offset: " << fh.metadataOffset << std::endl; 
		std::cout << "Metadata length: " << fh.metadataLength << std::endl; 
		std::cout << "Data header offset: " << fh.dataHeaderOffset << std::endl; 
		std::cout << "Data header length: " << fh.dataHeaderLength << std::endl; 
		std::cout << "Data offset: " << fh.dataOffset << std::endl << std::endl;

		// Ignore reading in all the metadata information.
		replayFile.ignore(fh.metadataLength);
		
		// Read in data header information.
		replayFile.read((char *)&dh, sizeof(DHeader));

		// Print data header information.
		std::cout << "Game ID: " << dh.gameID << std::endl;
		std::cout << "Game Length: " << dh.gameLength << " ms" << std::endl;
		std::cout << "Keyframe Count: " << dh.keyframeCount << std::endl;
		std::cout << "Chunk Count: " << dh.chunkCount << std::endl;
		std::cout << "Chunk ID #1: " << dh.chunkID1 << std::endl;
		std::cout << "Chunk ID #2: " << dh.chunkID2 << std::endl;
		std::cout << "Keyframe Interval: " << dh.keyframeInterval << " ms" << std::endl;
		std::cout << "Encryption Key Length: " << dh.encryptionKeyLength << std::endl;
	} else {
		std::cout << "Not a valid replay file." << std::endl;
	}

	// Close the stream once header has been read in.
	replayFile.close(); 

	// End of program.
	return 0;
}