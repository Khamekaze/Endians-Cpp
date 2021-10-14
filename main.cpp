#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <bitset>

using namespace std;

void generateInputFile() {
    ofstream outfile("generated_numbers.txt");
    int min = 1;
    int max = 65535;
    srand(time(NULL));

    for(int i = 0; i < 10; i++) {
        int output = min + (rand() % static_cast<int>(max - min + 1));
        outfile << output << endl;
    }

    outfile.close();
}

template <typename T>
string bin_str8(T n) {
    bitset<8> bs(n);
    return bs.to_string();
}

string bin_str16(unsigned short value) {
    string result = "";
    int count = 0;
    for(int i = 1; i < 32769; i*=2) {
        if((value & i) == i) {
            result = "1" + result;
        }
        else {
            result = "0" + result;
        }
        if(++count % 4 == 0 && count < 16) {
            result = " " + result;
        }
    }
    return result;
}

unsigned short toLittleEndian(unsigned short input) {
    return (input >> 8) | (input << 8);
}

unsigned char middleByte(unsigned short input) {
    unsigned char c = (input >> 4);
    return c;
}

void writeLittleEndian(ofstream& stream, string input) {
    stream << input << endl;
}

void writeMiddleBytes(ofstream& stream, unsigned char c) {
    stream << "Char value: " << (int) c << " | Binary: " << bin_str8(c) << endl;
}

int main() {
    //Generate file with random numbers
    generateInputFile();

    //Read input file and create/open output files
    ifstream inputFile("generated_numbers.txt");
    ofstream littleEndiansFile("little_endians.txt");
    ofstream swappedBytesFile("middle_bytes.txt");

    //Check if inputfile is readable
    if(inputFile.is_open()) {
        string line;
        while(getline(inputFile, line)) {
            //Get the current line we are reading in the input file and convert to unsigned short
            unsigned short currentNum = (unsigned short) strtoul(line.c_str(), NULL, 0);

            //Swap the bytes
            unsigned short swappedBytesShort = toLittleEndian(currentNum);

            //Get the middle byte of the byte-swapped short
            unsigned char middleByteChar = middleByte(swappedBytesShort);

            //Write the byte-swapped number to little endian output file
            writeLittleEndian(littleEndiansFile, bin_str16(swappedBytesShort));
            //Write the extracted middle byte as decimal and binary to
            //middle bytes output file
            writeMiddleBytes(swappedBytesFile, middleByteChar);
        }

        //Close files, zip coffee
        littleEndiansFile.close();
        swappedBytesFile.close();
        inputFile.close();
    }

    /* Testing with known value without writing or reading file
     * Zombie code from testing process, would remove in real case
     *
    //  unsigned short testVal = 12549;
    //  cout << "Original bytes:   " << bin_str16(testVal) << endl;
    //  unsigned short swapVal = toLittleEndian(testVal);
    //  cout << "Swapped bytes:    " << bin_str16(swapVal) << endl;
    //  unsigned char middleByteChar = middleByte(swapVal);
    //  cout << middleByteChar << endl;
    //  cout << "Middle bytes:     " << bin_str16(middleByteChar) << endl;
    //  cout << "Middle bytes val: " << (int) middleByteChar << endl;
     */
    return 0;
}
