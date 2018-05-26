#include "matrix.h"

#include <cassert>

using namespace std;

ColVector :: ColVector(size_t row, const double *value) :
    BaseMatrix(row, value), row_(row)
{

}

ColVector :: ColVector(size_t n, double k) :
    BaseMatrix(n), row_(n)
{
    double *ptr = begin();
    for (size_t i = 0; i < n; i ++)
        *ptr++ = k;
}

const RowVector ColVector :: Transposition() const{
    return RowVector(row_, cbegin());
}

const bool ColVector :: operator == (const ColVector &cvec) const{
    return row_ == cvec.row_ && BaseMatrix :: operator == (cvec);
}

const bool ColVector :: operator != (const ColVector &cvec) const{
    return row_ != cvec.row_ || BaseMatrix :: operator != (cvec);
}

ColVector & ColVector :: operator += (const ColVector &cvec){
    assert(row_ == cvec.row_);
    BaseMatrix :: operator += (cvec);
    return *this;
}

ColVector & ColVector :: operator -= (const ColVector &cvec){
    assert(row_ == cvec.row_);
    BaseMatrix :: operator -= (cvec);
    return *this;
}

ColVector & ColVector :: operator *= (double k){
    BaseMatrix :: operator *= (k);
    return *this;
}

ColVector & ColVector :: operator /= (double k){
    BaseMatrix :: operator /= (k);
    return *this;
}

const ColVector operator + (const ColVector &cvec){
    return cvec;
}

const ColVector operator - (const ColVector &cvec){
    ColVector ans = cvec;
    ans *= -1;
    return ans;
}

const ColVector operator + (const ColVector &a, const ColVector &b){
    ColVector ans = a;
    ans += b;
    return ans;
}

const ColVector operator - (const ColVector &a, const ColVector &b){
    ColVector ans = a;
    ans -= b;
    return ans;
}

const ColVector operator * (const ColVector &cvec, double k){
    ColVector ans = cvec;
    ans *= k;
    return ans;
}

const ColVector operator * (double k, const ColVector &cvec){
    ColVector ans = cvec;
    ans *= k;
    return ans;
}

const ColVector operator / (const ColVector &cvec, double k){
    ColVector ans = cvec;
    ans /= k;
    return ans;
}

istream & operator >> (istream &is, ColVector &cvec){
    is >> (BaseMatrix &) cvec;
    return is;
}

std :: ostream & operator << (ostream &os, const ColVector &cvec){
    os << "row = " << cvec.row_ << endl;
    for (size_t i = 0; i < cvec.row_; i ++)
        os << cvec[i] << endl;
    return os;
}
