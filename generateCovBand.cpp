﻿

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

void generateCovBand(int windowSize, std::string corrMatrix, std::string output);
//int argc, char *argv[]
int main(int argc, char*argv[])
{
	if (argc == 4) {
		generateCovBand(atoi(argv[1]), argv[2], argv[3]);
	}
	else {
		std::cout << "Usage: generateCovBand [window_size] [inputPath] [outputPath]" << std::endl;
	}
	return 0;
}

void generateCovBand(int windowSize, std::string corrMatrix, std::string output) {
	std::ifstream in(corrMatrix.c_str()); //input matrix file
	std::ofstream out(output); //output path
	std::string read_buffer; //corrMatrix read buffer
	std::getline(in, read_buffer); //read first line(perhaps.. preprocessing)
	int snpCnt = 0; //snip count??
	std::string token;
	std::stringstream stream;

	while (in.peek() != EOF){
		++snpCnt;
		std::getline(in, read_buffer);
		stream.str(read_buffer);

		for (int i = 0; i < windowSize - snpCnt; i++) {
			out << "0\t";
		}

		for (int i = 0; i < snpCnt - windowSize; i++) {
			stream >> token;
		}
		
		if (snpCnt <= windowSize) {
			for (int i = 0; i < snpCnt; i++) {
				stream >> token;
				out << token << "\t";
			}
		} 
		else {
			for (int i = 0; i < windowSize; i++) {
				stream >> token;
				out << token << "\t";
			}
		}
		out << "\n";
	} //end while
	std::cout << snpCnt << " number of lines read" << std::endl;
	in.close();
	out.close();

}
