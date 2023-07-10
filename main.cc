#include "shashtable.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <stdio.h>

using namespace std::chrono;

int distance0(std::string path, int capacity) {
    Dist0HashTable hashtable = Dist0HashTable(capacity);
    std::ifstream infile("data/" + path);
    std::ofstream outfile("data/dist0_" + path);

    std::string line;
    int fsize = 0;

    std::vector<std::string> sentences;
    while (std::getline(infile, line)) {
        if (hashtable.insert(&line[0]) == 0) outfile << line << std::endl;
        fsize += 1;
    }

    return fsize;
}

void distance1(std::string path) {
    Dist1HashTable hashtable = Dist1HashTable();
    std::ifstream infile("data/dist0_" + path);
    std::ofstream outfile("data/dist1_" + path);

    std::string line;
    std::vector<std::string> sentences;
    while (std::getline(infile, line)) {
        if (hashtable.insert(line) == 0) outfile << line << std::endl;
    }
}

int main() {
    std::vector<std::string> data_paths = {"tiny.txt", "small.txt", "100.txt", "1K.txt",
                                           "10K.txt",  "100K.txt"};

    // distance 0
    for (int i = 0; i < data_paths.size(); i++) {
        auto start = high_resolution_clock::now();
        distance0(data_paths[i], 2e+9);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << data_paths[i] << ": " << duration.count() << std::endl;
    }

    // distance 1
    for (int i = 0; i < data_paths.size(); i++) {
        auto start = high_resolution_clock::now();
        distance1(data_paths[i]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << data_paths[i] << ": " << duration.count() << std::endl;
    }

    return 0;
}
