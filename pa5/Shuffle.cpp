#include <stdexcept>
#include <iomanip>

#include "List.h"

using namespace std;

void shuffle(List& D) {
    List A, B;
    int x, y;
    int n = D.length();
    D.moveFront();
    while (D.position() < n / 2) {
        x = D.moveNext();
        A.insertBefore(x);
    }   
    while (D.position() < n) {
        y = D.moveNext();
        B.insertBefore(y);
    }
    D.clear();
    A.moveFront();
    B.moveFront();
    while (A.position() < A.length() && B.position() < B.length()) {
        x = B.moveNext();
        D.insertBefore(x);

        y = A.moveNext();
        D.insertBefore(y);
    }
    while (A.position() < A.length()) {
        y = A.moveNext();
        D.insertBefore(y);
    }
    while (B.position() < B.length()) {
        x = B.moveNext();
        D.insertBefore(x);
    }
}

int main(int argc, char* argv[]) {
    int n, count, num;
    List Deck, Temp;
    if (argc != 2) {
        throw invalid_argument("Incorrect number of arguments. Usage: Shuffle <int>");
    }
    num = stoi(argv[1]);
    if (num <= 0) {
        throw invalid_argument("Argument must be a positive integer.");
    }
    cout << "deck size\tshuffle count" << endl;
    string div(30, '-');
    cout << div << endl;    
    for (n = 1; n <= num; n++) {
        count = 0;
        Deck.moveBack();
        Deck.insertBefore(n - 1);    
        Temp = Deck;
        shuffle(Deck);
        count++;
        while (!(Temp == Deck)) {
            shuffle(Deck);
            count++;
        }
        cout << " " << left << setw(16) << n << count << endl;
    }    
}
