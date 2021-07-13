#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <cmath>
#include <iomanip>
#include <cstdint>
#include "sha.h"

using namespace std;
/*Program hashes a given string with SHA-256*/ 
/* *
 * Sources: 
 * https://qvault.io/cryptography/how-sha-2-works-step-by-step-sha-256/
 * http://www.mathcs.emory.edu/~cheung/Courses/255/Syllabus/1-C-intro/bit-array.html
 * https://stackoverflow.com/questions/2525310/how-to-define-and-work-with-an-array-of-bits-in-c
 * https://www.geeksforgeeks.org/rotate-bits-of-an-integer/
 * */

ShaHash::ShaHash(string initHash) {
	this->myHash(initHash);
}

ShaHash::~ShaHash() {

}

string ShaHash::getHash() {
	return this->hashedString;
}

void ShaHash::setHash(string myString) {
	this->myHash(myString);
}

/*Converts a given string to binary using a bitset*/
string ShaHash::convertToBinary(string str) {
	//You can't parse by whitespace, else that'd change the hash, so just read each char in the str
	string wordBin = "";
	for(int i=0; i<(int)str.size(); ++i) {
		//Take that word and convert it into binary (<8> is size)
		bitset<8> bits (str[i]);
		string bin = bits.to_string<char, string::traits_type, string::allocator_type>();
		wordBin += bin;
	}
	return wordBin;
}

/*Converts a given integer to binary*/
string ShaHash::convertToBinary(int n) {
	//From https://stackoverflow.com/questions/22746429/c-decimal-to-binary-converting
	string r;
    while(n!=0) {r=(n%2==0 ?"0":"1")+r; n/=2;}
    return r;
}

//Modified code from Emory
void ShaHash::setBit(uint32_t* A, int i, int pos) {
	unsigned int flag = 1; // flag = 0000.....00001

	flag = flag << pos; // flag = 0000...010...000   (shifted k positions)
	A[i] = A[i] | flag;

	return;
}

//Code from Emory
void ShaHash::testBit(int* A, int i, int pos)
{
	unsigned int flag = 1;  // flag = 0000.....00001

	flag = flag << pos;     // flag = 0000...010...000   (shifted k positions)

	if ( A[i] & flag )  {
		cout << "1 ";
	}     // Test the bit at the k-th position in A[i]
		// k-th bit is 1
	else {
		cout << "0 ";
	}
		// k-th bit is 0   
}

/*Following two functions I understand in theory but still would like more practice in.*/

int ShaHash::leftRotate(uint32_t n, unsigned int d) {
	return (n << d) | (n >> (32 - d));
}

int ShaHash::rightRotate(uint32_t n, unsigned int d) {
	return (n >> d) | (n << (32 - d));
}

/*Hashes a string into its SHA-256 equivalent. Uses a mix of strings and bits, 
  not exactly efficient but more of a learning process*/
void ShaHash::myHash(string myString) {
// 	/*Initalize 8 hashed values that are unsigned bits*/

	//cout << "Starting hash of '" << myString << "'" << endl;

	string hash = "";

	string strBin = convertToBinary(myString);	

	//cout << "String in binary: " << strBin << endl;

	int size = strBin.size();
	//string strSize(1,size);

	/*Pre-processing*/
	//cout << "Starting preprocessing" << endl;
	//cout << "----------------" << endl;

	//Append a single 1
	strBin += "1";

	//cout << "String w/ appended 1: " << strBin << endl;
	//Pad with 0s until it is a multiple of 512
	while(strBin.size()%512 != 0)  {
		strBin += '0';
	}
	
	//Take away 64 bits
	for(int i=0; i<64; ++i) {
		strBin.pop_back();
	}

	//Add the original size in binary to the end
	string sizeBin = convertToBinary(size);
	for(int i=0; i<(int)(64-sizeBin.size()); ++i) {
		strBin += '0';
	}
	strBin += sizeBin;

	//cout << "After preprocessing: ";
	// for(int i=0; i<(int)strBin.size(); ++i) {
	// 	if(i%8 == 0 && i != 0) cout << " ";
	// 	if(i%64 == 0 && i != 0) cout << endl;
	// 	cout << strBin[i];
	// }
	// cout << endl << endl;

	// cout << "Starting chunk loop" << endl;
	// cout << "----------------" << endl;

	/*Chunk loop*/
	//Happens for each 512 chunk of data

	int bitIndex = 0;
	uint64_t intLimit = pow(2,32);
	//Note: strBin.size() is always a multiple of 512

	//cout << "Binary string size:" << strBin.size() << endl;
	while(bitIndex < (int)strBin.size()) {
		//cout << "Starting new chunk loop" << endl;
		//Create the 16 index chunk (32 bits per index, so 1 int per index)
		//Maybe this has to be dynamically allocated instead?
		//vector<int> bitChunk(16,0);

		//int* A = new int[32];

		uint32_t* A = new uint32_t[64];
		std::fill(A, A + 64, 0);
		
		//Note: We use 32 since an int is 32-bits large

		//e.x. bitChunk[0] is one int, representing the first 32 bits of strBin.
		for(int j = 0; j<512; ++j) {
			int i = bitIndex/32; // index for array
			int pos = abs((32*(i+1))-bitIndex)%32; // index for ind. bit
			if(strBin[bitIndex] == '1') {

				setBit(A, i, pos-1);
				//cout << "Setting A[" << i << "] to " << A[i] << endl;
				//testBit(A, i, pos);
			}
			bitIndex++;
			//cout << "Bit index: " << bitIndex << endl;
		}
		//Once the bit chunk is set, insert the chunk into the larger array

		//bitChunks.push_back(A);
		//cout << endl;

		//At this point, check to make sure the bits are properly inputted
		// cout << "Checking current message schedule: " << endl;
		// cout << "----------------" << endl;
		
		// for(int i=0; i<64; ++i) {
		// 	if(i%8 == 0 && i != 0) cout << endl;
		// 	cout << A[i] << " ";
		// }
		// cout << endl << endl;
		// cout << "Current bitIndex: " << bitIndex << endl;
		// cout << "Current strBin size: " << strBin.size() << endl;

		/*Modifying all the 0 indexed items (which will always be 16 <= i <= 63)*/
		for(int i=16; i<64; ++i) {
			//Why are we choosing these values and not others?
			uint32_t s0 = rightRotate(A[i-15], 7) ^ rightRotate(A[i-15], 18) ^ (A[i-15] >> 3);
			uint32_t s1 = rightRotate(A[i-2], 17) ^ rightRotate(A[i-2], 19) ^ (A[i-2] >> 10);
			A[i] = (A[i-16] + s0 + A[i-7] + s1)%intLimit;
		}

		//Note: Haven't checked above for loop for accuracy yet. I assume it should be working
		//lol i should have tested it
		// cout << "Checking final message schedule: " << endl;
		// cout << "----------------" << endl;
		
		// for(int i=0; i<64; ++i) {
		// 	if(i%8 == 0 && i != 0) cout << endl;
		// 	cout << A[i] << " ";
		// }
		// cout << endl << endl;

		// cout << "Starting compression" << endl;
		// cout << "----------------" << endl;
		uint32_t a = hashValues[0];
		uint32_t b = hashValues[1];
		uint32_t c = hashValues[2];
		uint32_t d = hashValues[3];
		uint32_t e = hashValues[4];
		uint32_t f = hashValues[5];
		uint32_t g = hashValues[6];
		uint32_t h = hashValues[7];

		//Compression loop
		for(int i=0; i<64; ++i) {
			//Note: There are some weird variable names here. I think they
			//correspond with official names and guidelines given by the NIST.
			uint32_t S1 = rightRotate(e,6) ^ rightRotate(e,11) ^ rightRotate(e,25);
			uint32_t ch = (e & f) ^ ((~e) & g);
			uint32_t temp1 = (h + S1 + ch + roundConstants[i] + A[i]) % intLimit;

			uint32_t S0 = rightRotate(a,2) ^ rightRotate(a,13) ^ rightRotate(a,22);
			uint32_t maj = (a & b) ^ (a & c) ^ (b & c);
			uint32_t temp2 = (S0 + maj) % intLimit;

			// cout << "Iteration #" << i+1 << endl << endl;
			// cout << "S1: " << S1 << endl;
			// cout << "ch: " << ch << endl;
			// cout << "temp1: " << temp1 << endl;
			// cout << "----------------" << endl;
			// cout << "S0: " << S0 << endl;
			// cout << "maj: " << maj << endl;
			// cout << "temp2: " << temp2 << endl;

			h = g;
			g = f;
			f = e;
			e = (d + temp1)% intLimit;
			d = c;
			c = b;
			b = a;
			a = (temp1 + temp2) % intLimit;
		}

		// //Checking compression loop results
		// cout << "Checking compression loop results" << endl;
		// cout << "----------------" << endl;
		// for(int i=0; i<8; ++i) {
		// 	cout << "h" << i << ": " << std::hex << hashValues[i] << " => ";
		// 	cout << std::setfill('0') << std::setw(8) << hashValues[i] << endl;
		// }
		// cout << endl;

		hashValues[0] = (hashValues[0] + a) % intLimit;
		hashValues[1] = (hashValues[1] + b) % intLimit;
		hashValues[2] = (hashValues[2] + c) % intLimit;
		hashValues[3] = (hashValues[3] + d) % intLimit;
		hashValues[4] = (hashValues[4] + e) % intLimit;
		hashValues[5] = (hashValues[5] + f) % intLimit;
		hashValues[6] = (hashValues[6] + g) % intLimit;
		hashValues[7] = (hashValues[7] + h) % intLimit;
	}

	// cout << "Checking addition results" << endl;
	// cout << "----------------" << endl;
	for(int i=0; i<8; ++i) {
		stringstream ss;

		// cout << "h" << i << ": " << std::hex << hashValues[i] << " => ";
		// cout << std::setfill('0') << std::setw(8) << hashValues[i] << endl;

		ss << std::hex << hashValues[i];

		hash += ss.str();
	}

	this->hashedString = hash;
	return;
}

