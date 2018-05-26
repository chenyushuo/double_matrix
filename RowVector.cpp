#include "matrix.h"

#include <cassert>

using namespace std;

RowVector :: RowVector(size_t col, const double *value) :
    BaseMatrix(col, value), col_(col)
{

}

RowVector :: RowVector(size_t n, double k) :
    BaseMatrix(n), col_(n)
{
    double *ptr = begin();
    for (size_t i = 0; i < n; i ++)
        *ptr++ = k;
}

const ColVector RowVector :: Transposition() const{
    return ColVector(col_, cbegin());
}

const bool RowVector :: operator == (const RowVector &rvec) const{
    return col_ == rvec.col_ && BaseMatrix :: operator == (rvec);
}

const bool RowVector :: operator != (const RowVector &rvec) const{
    return col_ != rvec.col_ || BaseMatrix :: operator != (rvec);
}

RowVector & RowVector :: operator += (const RowVector &rvec){
    assert(col_ == rvec.col_);
    BaseMatrix :: operator += (rvec);
    return *this;
}

RowVector & RowVector :: operator -= (const RowVector &rvec){
    assert(col_ == rvec.col_);
    BaseMatrix :: operator -= (rvec);
    return *this;
}

RowVector & RowVector :: operator *= (double k){
    BaseMatrix :: operator *= (k);
    return *this;
}

RowVector & RowVector :: operator /= (double k){
    BaseMatrix :: operator /= (k);
    return *this;
}

const RowVector operator + (const RowVector &rvec){
    return rvec;
}

const RowVector operator - (const RowVector &rvec){
    RowVector ans = rvec;
    ans *= -1;
    return ans;
}

const RowVector operator + (const RowVector &a, const RowVector &b){
    RowVector ans = a;
    ans += b;
    return ans;
}

const RowVector operator - (const RowVector &a, const RowVector &b){
    RowVector ans = a;
    ans -= b;
    return ans;
}

const RowVector operator * (const RowVector &rvec, double k){
    RowVector ans = rvec;
    ans *= k;
    return ans;
}

const RowVector operator * (double k, const RowVector &rvec){
    RowVector ans = rvec;
    ans *= k;
    return ans;
}

const RowVector operator / (const RowVector &rvec, double k){
    RowVector ans = rvec;
    ans /= k;
    return ans;
}

istream & operator >> (istream &is, RowVector &rvec){
    is >> (BaseMatrix &) rvec;
    return is;
}

std :: ostream & operator << (ostream &os, const RowVector &rvec){
    os << "col = " << rvec.col_ << endl;
    for (size_t i = 0; i < rvec.col_; i ++)
        os << rvec[i] << ' ';
    os << endl;
    return os;
}
