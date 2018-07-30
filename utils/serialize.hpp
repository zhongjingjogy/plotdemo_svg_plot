#ifndef SEARIALIZE_HPP
#define SEARIALIZE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

void deserialize(
    std::string src,
    std::vector<std::vector<double> > &var) {

    std::ifstream infile;
	infile.open(src.c_str(), std::ios::binary|std::ios::in);

    if(!infile.is_open()) {
        std::cout << "The file can not be open.\n";
    }
    while(infile.is_open() && !infile.eof()) {
        int size = 0;
        if(infile.eof()) {
            break;
        }
        infile.read(reinterpret_cast<char *>(&size), sizeof(size));
        
        if(infile.eof()) {
            // std::cout << "size: " << size << "\n";
            // std::cerr << "Broken cols files.\n";
            break;
        }
        if(size == 0) {
            // std::cout << "empty array to be read\n";
            continue;
        }
        std::vector<double> v(size);
        infile.read(reinterpret_cast<char *>(&v[0]), sizeof(double)*size);
        var.push_back(v);
        // std::cout << strtool::join(v, ", ") << "\n";
    }
	
    infile.close();
}

#endif