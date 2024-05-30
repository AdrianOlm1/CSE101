#include "BigInteger.h"
#include "List.h"

#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

const ListElement BASE  = 1000000000;
const int         POWER = 9;

void delZero( List* L) {
    L->moveFront();
    while (L->length() > 0 && !L->peekNext()) {
        L->eraseAfter();
    }
}

List tempMult(long s, List *b, int* ctr) {
    List L;
    long carry = 0;
    long temp = 0;
    for (b->moveBack(); b->position() > 0; b->movePrev()) {
        temp = (b->peekPrev() * s) + carry;
        carry = temp / BASE;
        temp %= BASE;
        L.insertAfter(temp);
    }
    if (carry > 0) {
        L.insertAfter(carry);
    }
    L.moveBack();
    for (int i = 0; i < *ctr; i++) {
        L.insertAfter(0);
    }
    return L;
}

BigInteger::BigInteger() {
    signum = 0;
    digits = List();
}

BigInteger::BigInteger(long x) {
    if (x == 0) {
        signum = 0;
        digits.insertAfter(0);
        return;
    }
    if (x < 0) {
        signum = -1;
        x = -x;
    } else {
        signum = 1;
    }
    while (x > 0) {
        digits.insertBefore(x % BASE);
        x /= BASE;
    }
}

BigInteger::BigInteger(std::string s) {
    if (!s.length()) {
        throw std::invalid_argument("BigInteger: Constructor: empty string");
    }
    int offset = 0;
    if ((s[0] == '+') | (s[0] == '-')) {
        signum = 1;
        if (s[0] == '-') {
            signum = -1;
        }
        offset = 1;
        s = s.substr(offset, s.length() - 1);
    } else {
        signum = 1;
    }
    for (long unsigned int i = 0; i < s.length();) {
        if (!std::isdigit(s[i])) {
            throw std::invalid_argument("BigInt Constructor is non-numeric");
        }
        i = i + 1;
    }
    std::string num = "";
    List L;
    size_t max = 0;
    size_t curr_digits = s.length();
    while (max < s.length() / POWER) {
        num = s.substr(curr_digits - POWER, POWER);
        digits.insertAfter(std::stol(num, nullptr, 10));
        curr_digits = curr_digits - POWER;
        max++;
    }
    if (curr_digits > 0) {
        num = s.substr(0, curr_digits);
        digits.insertAfter(std::stol(num, nullptr, 10));
    }

    delZero(&digits);
}

BigInteger::BigInteger(const BigInteger& N) {
    this->signum = N.signum;
    this->digits = N.digits;
}

int BigInteger::sign() const{
    return this->signum;
}

int BigInteger::compare(const BigInteger& N) const {
    if (signum > N.signum) {
        return 1;
    }
    else if (signum < N.signum) {
        return -1;
    }
    else if (signum == 0 && N.signum == 0) {
        return 0;
    }
    const List& A = digits;
    const List& B = N.digits;
    int length = A.length();
    if (length != B.length()) {
        return (length > B.length()) ? signum : -N.signum;
    }
    List A_copy = A;
    List B_copy = B;
    A_copy.moveFront();
    B_copy.moveFront();
    for (int i = 0; i < length; ++i) {
        if (A_copy.peekNext() > B_copy.peekNext()) {
            return signum;
        }
        else if (A_copy.peekNext() < B_copy.peekNext()) {
            return -N.signum;
        }
        A_copy.moveNext();
        B_copy.moveNext();
    }
    return 0;
}

void BigInteger::makeZero() {
    digits.clear();
    signum = 0;
}

void BigInteger::negate() {
    signum *= -1;
}

BigInteger BigInteger::add(const BigInteger& N) const {
    BigInteger X = *this;
    BigInteger Y = N;
    BigInteger Z;

    if (X.sign() > 0 && Y.sign() < 0) {
        Y.negate();
        return X.sub(Y);
    } else if (X.sign() < 0 && Y.sign() > 0) {
        X.negate();
        return Y.sub(X);
    } else if (X.sign() < 0 && Y.sign() < 0) {
        X.negate();
        Y.negate();
        Z = X.add(Y);
        Z.negate();
        return Z;
    }
    if (X > Y) {
        return Y.add(X);
    }
    List x = X.digits;
    List y = Y.digits;
    List z = Z.digits;
    long carry = 0;
    long temp = 0;
    x.moveBack();
    y.moveBack();
    while (x.position() > 0 && y.position() > 0) {
        temp = carry + x.peekPrev() + y.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        z.insertAfter(temp);
        x.movePrev();
        y.movePrev();
    }

    while (y.position() > 0) {
        temp = carry + y.peekPrev();
        carry = temp / BASE;
        temp %= BASE;
        z.insertAfter(temp);
        y.movePrev();
    }
    if (carry > 0) {
        z.insertAfter(carry);
    }

    Z.signum = 1;
    Z.digits = z;
    return Z;
}

BigInteger BigInteger::sub(const BigInteger& N) const {
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;
    List a = A.digits;
    List b = B.digits;
    List c = C.digits;

    if (A == B) {
        return C; 
    }
    if (A.sign() && !B.sign()) {
        A.negate();
        return A;
    }
    if (!A.sign() && B.sign()) {
        return B;
    }
    if (A.sign() < 0 && B.sign() > 0) {
        B.negate();
        C = A.add(B);
        C.negate();
        return C;
    }
    if (A.sign() > 0 && B.sign() < 0) {
        A.negate();
        C = A.add(B);
        return C;
    }
    if (A.sign() < 0 && B.sign() < 0) {
        A.negate();
        B.negate();
        C = B.sub(A);
        C.negate();
        return C;
    }
    if (A < B) {
        C = A.sub(B);
        C.negate();
        return C;
    }
    a.moveBack();
    b.moveBack();
    long dist = 0;
    long temp = 0;
    int i = b.position();
    while (!(i <= 0)) {
        if (a.peekPrev() - dist < b.peekPrev()) {
            temp = a.peekPrev() + BASE - b.peekPrev() - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - dist - b.peekPrev();
            if (!(a.peekPrev() <= 0)) {
                dist = 0;
            }
        }
        c.insertAfter(temp);
        a.movePrev();
        b.movePrev();
        i--;
    }
    while (a.position() > 0) {
        if (a.peekPrev() - dist < 0) {
            temp = a.peekPrev() + BASE - 0 - dist;
            dist = 1;
        } else {
            temp = a.peekPrev() - dist - 0;
            if (!(a.peekPrev() <= 0)) {
                dist = 0;
            }
        }
        c.insertAfter(temp);
        a.movePrev();
    }
    C.digits = c;
    delZero(&(C.digits));
    C.signum = -1;
    return C;
}

BigInteger BigInteger::mult(const BigInteger& N) const {
    BigInteger B = *this;
    BigInteger A = N;
    BigInteger C;
    List a = A.digits;
    List b = B.digits;
    int ctr = 0;
    a.moveBack();
    b.moveBack();
    int p = a.position();
    for (int i = p; i > 0; i--) {
        List temp = tempMult(a.peekPrev(), &b, &ctr);
        BigInteger T;
        T.signum = 1;
        T.digits = temp;
        C = C.add(T);
        a.movePrev();
        ctr++;
    }
    C.signum = A.signum * B.signum;
    return C;
}

std::string BigInteger::to_string() {
    std::string out = "";
    if (this->signum == 0) {
        return "0";
    } else if (signum == -1) {
        out += "-";
    }
    digits.moveFront();
    while (digits.front() == 0 && digits.length() > 1) {
        digits.eraseAfter();
    }
    for (digits.moveFront(); digits.position() < digits.length(); digits.moveNext()) {
        std::string A = std::to_string(digits.peekNext());
        std::string B = "";
        while ((int)(B.length() + A.length()) < POWER && digits.position() != 0) {
            B += '0';
        }
        out += (B + A);
    }
    return out;
}

std::ostream& operator<<( std::ostream& stream, BigInteger N ) {
    return stream<<N.BigInteger::to_string();
}


bool operator==( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 0) ? true : false;
}

bool operator<( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == -1) ? true : false;
}

bool operator<=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == -1)) ? true : false;
}

bool operator>( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return (i == 1) ? true : false;
}

bool operator>=( const BigInteger& A, const BigInteger& B ) {
    int i = A.compare(B);
    return ((i == 0) || (i == 1)) ? true : false;
}

BigInteger operator+( const BigInteger& A, const BigInteger& B ) {
    return A.add(B);
}

BigInteger operator+=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.add(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator-( const BigInteger& A, const BigInteger& B ) {
    return A.sub(B);
}

BigInteger operator-=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.sub(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}

BigInteger operator*( const BigInteger& A, const BigInteger& B ) {
    return A.mult(B);
}

BigInteger operator*=( BigInteger& A, const BigInteger& B ) {
    BigInteger I = A.mult(B);
    A.digits = I.digits;
    A.signum = I.signum;
    return A; 
}