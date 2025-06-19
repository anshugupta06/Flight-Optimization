#include "cleaning.h" // Include the header you created
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>

using namespace std;

string trim(const string &str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == string::npos) ? "" : str.substr(first, (last - first + 1));
}

std::string cleanAirportData(const string &originalFile) {
    const string tempFile = "temp_cleaned.csv";
    const string missingValuePlaceholder = "NA";

    ifstream infile(originalFile);
    ofstream outfile(tempFile);

    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Failed to open input or output file." << endl;
        return ""; // Indicate failure
    }

    string line;
    while (getline(infile, line)) {
        stringstream ss(line);
        string cell;
        vector<string> fields;

        while (getline(ss, cell, ',')) {
            string cleaned = trim(cell);
            if (cleaned.empty()) {
                cleaned = missingValuePlaceholder;
            }
            fields.push_back(cleaned);
        }

        for (size_t i = 0; i < fields.size(); ++i) {
            outfile << fields[i];
            if (i < fields.size() - 1)
                outfile << ",";
        }
        outfile << "\n";
    }

    infile.close();
    outfile.close();
    return tempFile;
}
