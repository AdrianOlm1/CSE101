#include <fstream>
#include <iostream>

#include "BigInteger.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
        return EXIT_FAILURE;
    }

    ifstream in(argv[1]);
    ofstream out(argv[2]);
    if (!in) {
        cerr << "Error: Unable to open file " << argv[1] << " for reading" << endl;
        return EXIT_FAILURE;
    }

    string sA, sB;
    in >> sA >> sB;

    BigInteger A(sA);
    BigInteger B(sB);
    BigInteger two("2");
    BigInteger three("3");
    BigInteger nine("9");
    BigInteger sixteen("16");

    out << A << endl << endl;
    out << B << endl << endl;
    out << A + B << endl << endl;
    out << A - B << endl << endl;
    out << A - A << endl << endl;
    out << (three * A) - (two * B) << endl << endl;
    out << A * B << endl << endl;
    out << A * A << endl << endl;
    out << B * B << endl << endl;
    out << (nine * (A * A * A * A)) + (sixteen * (B * B * B * B * B)) << endl << endl;

    in.close();
    out.close();
    return 0;
}