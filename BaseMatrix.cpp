#include "matrix.h"

#include <cstring>
#include <cassert>

#include <iostream>

using namespace std;

BaseMatrix :: BaseMatrix(size_t size, const double *value) :
    size_(size), value_(new double [size_]())
{
    if (value != nullptr)
        memcpy(value_, value, sizeof(double) * size_);
}

BaseMatrix :: BaseMatrix(const BaseMatrix &bmtr) :
    size_(bmtr.size_), value_(new double [size_])
{
    memcpy(value_, bmtr.value_, sizeof(double) * size_);
}

BaseMatrix & BaseMatrix :: operator = (const BaseMatrix &bmtr){
    if (this == &bmtr)
        return *this;
    assert(size_ == bmtr.size_);
    delete [] value_;
    value_ = new double [size_];
    memcpy(value_, bmtr.value_, sizeof(double) * size_);
    return *this;
}

const bool BaseMatrix :: operator == (const BaseMatrix &bmtr) const{
    const double *p1 = value_;
    const double *p2 = bmtr.value_;
    for (size_t i = 0; i < size_; i ++)
        if (*p1++ != *p2++)
            return false;
    return true;
}

const bool BaseMatrix :: operator != (const BaseMatrix &bmtr) const{
    const double *p1 = value_;
    const double *p2 = bmtr.value_;
    for (size_t i = 0; i < size_; i ++)
        if (*p1++ != *p2++)
            return true;
    return false;
}

BaseMatrix & BaseMatrix :: operator += (const BaseMatrix &bmtr){
    assert(size_ == bmtr.size_);
    double *p1 = value_;
    const double *p2 = bmtr.value_;
    for (size_t i = 0; i < size_; i ++)
        *p1++ += *p2++;
    return *this;
}

BaseMatrix & BaseMatrix :: operator -= (const BaseMatrix &bmtr){
    assert(size_ == bmtr.size_);
    double *p1 = value_;
    const double *p2 = bmtr.value_;
    for (size_t i = 0; i < size_; i ++)
        *p1++ -= *p2++;
    return *this;
}

BaseMatrix & BaseMatrix :: operator *= (double k){
    assert(k == k); //k == nan?
    double *p1 = value_;
    for (size_t i = 0; i < size_; i ++)
        *p1++ *= k;
    return *this;
}

BaseMatrix & BaseMatrix :: operator /= (double k){
    assert(k != 0); //k == 0
    double *p1 = value_;
    for (size_t i = 0; i < size_; i ++)
        *p1++ *= k;
    return *this;
}

istream & operator >> (istream &is, BaseMatrix &bmtr){
    for (size_t i = 0; i < bmtr.size_; i ++)
        is >> bmtr[i];
    return is;
}

BaseMatrix :: ~BaseMatrix(){
    delete [] value_;
}