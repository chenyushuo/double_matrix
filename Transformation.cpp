#include "matrix.h"

#include <cassert>

using namespace std;

void Matrix :: RowTransformationMulti(size_t r1, double k){
    assert(k == k); //if k == nan
    double *ptr = begin() + r1 * col_; //pointer of r1
    for (size_t i = 0; i < col_; i ++)
        *ptr++ *= k;
}

void Matrix :: RowTransformationAdd(size_t r1, size_t r2, double k){
    assert(k == k); //if k == nan
    assert(r1 != r2); //if r1 == r2
    double *p1 = begin() + r1 * col_; //pointer of r1
    double *p2 = begin() + r2 * col_; //pointer of r2
    for (size_t i = 0; i < col_; i ++)
        *p1++ += k * (*p2++);
}

void Matrix :: RowTransformationSwap(size_t r1, size_t r2){
    if (r1 == r2)
        return;
    swap_times_ ++;
    double *p1 = begin() + r1 * col_; //pointer of r1
    double *p2 = begin() + r2 * col_; //pointer of r2
    for (size_t i = 0; i < col_; i ++)
        swap(*p1++, *p2++);
}

void Matrix :: RowTransformation(){
    swap_times_ = 0;
    for (size_t i = 0, j = 0; i < col_; i ++){
        size_t r;
        double *ptr = begin() + j * col_ + i;
        for (r = j; r < row_; r ++){
            if (*ptr != double(0))
                break;
            ptr += col_;
        }
        if (r == row_)
            continue;
        RowTransformationMulti(r, double(1) / (*ptr));
        RowTransformationSwap(j, r);
        ptr = begin() + i;
        for (r = 0; r < row_; r ++){
            if (r != j && *ptr != double(0))
                RowTransformationAdd(r, j, -(*ptr));
            ptr += col_;
        }
        j ++;
    }
}

void Matrix :: ColTransformationMulti(size_t l1, double k){
    assert(k == k); //if k == nan
    double *ptr = begin() + l1;
    for (size_t i = 0; i < row_; i ++){
        *ptr *= k;
        ptr += col_;
    }
}

void Matrix :: ColTransformationAdd(size_t l1, size_t l2, double k){
    assert(k == k); //if k == nan
    assert(l1 != l2); //if l1 == l2
    double *p1 = begin() + l1;
    double *p2 = begin() + l2;
    for (size_t i = 0; i < row_; i ++){
        *p1 += k * (*p2);
        p1 += col_, p2 += col_;
    }
}

void Matrix :: ColTransformationSwap(size_t l1, size_t l2){
    if (l1 == l2)
        return;
    swap_times_ ++;
    double *p1 = begin() + l1;
    double *p2 = begin() + l2;
    for (size_t i = 0; i < row_; i ++){
        swap(*p1, *p2);
        p1 += col_, p2 += col_;
    }
}

void Matrix :: ColTransformation(){
    swap_times_ = 0;
    for (size_t i = 0, j = 0; i < row_; i ++){
        size_t l;
        double *ptr = begin() + i * col_ + j;
        for (l = j; l < col_; l ++){
            if (*ptr != double(0))
                break;
            ptr ++;
        }
        if (l == col_)
            continue;
        ColTransformationMulti(l, double(1) / (*ptr));
        ColTransformationSwap(l, j);
        ptr = begin() + i * col_;
        for (l = 0; l < col_; l ++){
            if (l != j && *ptr != double(0))
                ColTransformationAdd(l, j, -(*ptr));
            ptr ++;
        }
        j ++;
    }
}

const double Det(const Matrix &mtr){
    assert(mtr.row_ == mtr.col_); //if row != col
    Matrix temp = mtr;
    temp.RowTransformation();
    double result = (temp.swap_times_ & 1) ? -1 : 1;
    for (size_t i = 0; i < temp.row_; i ++)
        result *= temp[i][i];
    return result;
}

const Matrix Inverse(const Matrix &mtr){
    assert(mtr.row_ == mtr.col_); //if row != col
    double *value = new double [2 * mtr.row_ * mtr.col_];
    size_t idx = 0;
    for (size_t i = 0; i < mtr.row_; i ++){
        for (size_t j = 0; j < mtr.col_; j ++)
            value[idx ++] = mtr[i][j];
        for (size_t j = 0; j < mtr.col_; j ++)
            value[idx ++] = (i == j);
    }
    Matrix temp(mtr.row_, mtr.col_ * 2, value);
    temp.RowTransformation();
    bool can_inverse = true;
    idx = 0;
    for (size_t i = 0; i < mtr.row_; i ++){
        if (temp[i][i] != double(1)){
            can_inverse = false;
            break;
        }
        for (size_t j = 0; j < mtr.col_; j ++)
            value[idx ++] = temp[i][mtr.col_ + j];
    }
    assert(can_inverse);
    Matrix ans(mtr.row_, mtr.col_, value);
    delete [] value;
    return ans;
}