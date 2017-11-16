//
// Created by john on 11/16/17.
//

#ifndef ALGS4_UTILS_HPP
#define ALGS4_UTILS_HPP

#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace sort {
    pair<string, int> ParseCommandLine(int argc, const char **argv) {
        if (argc < 3) {
            cerr << "Usage: executor [test_file_path] [top_number]" << endl;
            exit(0);
        }

        string testFile = argv[1];
        int source = strtoul(argv[2], nullptr, 0);

        return {testFile, source};
    };

    class Transaction {
    private:
        string name;
        string date;
        double volume;

    public:
        Transaction() {
            name = "";
            date = "";
            volume = 0.0;
        };

        explicit Transaction(istringstream pLine) {
            pLine >> name >> date >> volume;
        }

        string ToString() {
            ostringstream lOss;
            lOss << name << " " << date << " " << volume;
            return lOss.str();
        }

        bool operator==(const Transaction &rhs) {
            return (*this).volume == rhs.volume;
        }

        bool operator!=(const Transaction &rhs) {
            return !(*this == rhs);
        }

        bool operator>(const Transaction &rhs) {
            return (*this).volume > rhs.volume;
        }

        bool operator<(const Transaction &rhs) {
            return (*this).volume < rhs.volume;
        }

        bool operator<=(const Transaction &rhs) {
            return *this < rhs or *this == rhs;
        }

        bool operator>=(const Transaction &rhs) {
            return *this > rhs or *this == rhs;
        }
    };
}

#endif //ALGS4_UTILS_HPP
