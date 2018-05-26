#include "matrix.h"

#include <cassert>

#include <numeric>

using namespace std;

Matrix :: Matrix(size_t row, size_t col, const double *value) :
    BaseMatrix(row * col, value), row_(row), col_(col), swap_times_(0)
{

}

Matrix :: Matrix(size_t n, double k) :
    BaseMatrix(n * n), row_(n), col_(n), swap_times_(0)
{
    double *ptr = begin();
    for (size_t i = 0; i < n; i ++){
        *ptr = k;
        ptr += n + 1;
    }
}

Matrix :: Matrix(const ColVector &cvec) :
    BaseMatrix(cvec.row_, cvec.cbegin()), row_(cvec.row_), col_(1), swap_times_(0)
{

}

Matrix :: Matrix(const RowVector &rvec) :
    BaseMatrix(rvec.col_, rvec.cbegin()), row_(1), col_(rvec.col_), swap_times_(0)
{

}

const Matrix Matrix :: Transposition() const{
    Matrix ans = Matrix(col_, row_);
    const double *p1;
    double *p2 = ans.begin();
    for (size_t j = 0; j < col_; j ++){
        p1 = cbegin() + j;
        for (size_t i = 0; i < row_; i ++)
            *p2++ = *p1++;
    }
    return ans;
}

const bool Matrix :: operator == (const Matrix &mtr) const{
    return row_ == mtr.row_ && col_ == mtr.col_ && BaseMatrix :: operator == (mtr);
}

const bool Matrix :: operator != (const Matrix &mtr) const{
    return row_ != mtr.row_ || col_ != mtr.col_ || BaseMatrix :: operator != (mtr);
}

Matrix & Matrix :: operator += (const Matrix &mtr){
    assert(row_ == mtr.row_ && col_ == mtr.col_);
    BaseMatrix :: operator += (mtr);
    return *this;
}

Matrix & Matrix :: operator -= (const Matrix &mtr){
    assert(row_ == mtr.row_ && col_ == mtr.col_);
    BaseMatrix :: operator -= (mtr);
    return *this;
}

Matrix & Matrix :: operator *= (double k){
    BaseMatrix :: operator *= (k);
    return *this;
}

Matrix & Matrix :: operator /= (double k){
    BaseMatrix :: operator /= (k);
    return *this;
}

const Matrix operator + (const Matrix &mtr){
    return mtr;
}

const Matrix operator - (const Matrix &mtr){
    Matrix ans = mtr;
    ans *= -1;
    return ans;
}

const Matrix operator + (const Matrix &a, const Matrix &b){
    Matrix ans = a;
    ans += b;
    return ans;
}

const Matrix operator - (const Matrix &a, const Matrix &b){
    Matrix ans = a;
    ans -= b;
    return ans;
}

const Matrix operator * (const Matrix &mtr, double k){
    Matrix ans = mtr;
    ans *= k;
    return ans;
}

const Matrix operator * (double k, const Matrix &mtr){
    Matrix ans = mtr;
    ans *= k;
    return ans;
}

const Matrix operator / (const Matrix &mtr, double k){
    Matrix ans = mtr;
    ans /= k;
    return ans;
}

const Matrix operator * (const Matrix &a, const Matrix &b){
    assert(a.col_ == b.row_);
    Matrix ans(a.row_, b.col_);
    double *ptr; //pointer of ans
    const double *pa = a.cbegin(); //pointer of a
    const double *pb; //pointer of b
    for (size_t i = 0; i < a.row_; i ++){
        for (size_t k = 0; k < a.col_; k ++){
            double a_i_k = *pa++;
            ptr = ans[i], pb = b[k];
            for (size_t j = 0; j < b.col_; j ++)
                *ptr++ += a_i_k * (*pb++);
        }
    }
    return ans;
}

const ColVector operator * (const Matrix &mtr, const ColVector &cvec){
    assert(mtr.col_ == cvec.row_);
    ColVector ans(mtr.row_);
    double *ptr = ans.begin(); //pointer of ans
    size_t len = cvec.row_;
    const double *pl = cvec.cbegin(), *pr = cvec.cend(); //pointer of cvec
    const double *pm = mtr.cbegin(); //pointer of mtr;
    for (size_t i = 0; i < ans.row_; i ++){
        *ptr++ = inner_product(pl, pr, pm, double(0));
        pm += len;
    }
    return ans;
}

const RowVector operator * (const RowVector &rvec, const Matrix &mtr){
    assert(rvec.col_ == mtr.row_);
    RowVector ans(mtr.col_);
    double *ptr; //pointer of ans
    const double *pr = rvec.cbegin(); //pointer of rvec
    const double *pm = mtr.cbegin(); //pointer of mtr
    for (size_t i = 0; i < mtr.row_; i ++){
        double k = *pr++;
        ptr = ans.begin();
        for (size_t j = 0; j < mtr.col_; j ++)
            *ptr++ += k * (*pm++);
    }
    return ans;
}

const Matrix operator * (const ColVector &cvec, const RowVector &rvec){
    Matrix ans(cvec.row_, rvec.col_);
    double *ptr = ans.begin(); //pointer of ans
    const double *pc = cvec.cbegin(); //pointer of cvec
    const double *pr; //pointer of rvec
    for (size_t i = 0; i < ans.row_; i ++){
        double k = *pc++;
        pr = rvec.cbegin();
        for (size_t j = 0; j < ans.col_; j ++)
            *ptr++ = k * (*pr++);
    }
    return ans;
}

const double operator * (const RowVector &rvec, const ColVector &cvec){
    return inner_product(rvec.cbegin(), rvec.cend(), cvec.cbegin(), 0);
}

istream & operator >> (istream &is, Matrix &mtr){
    is >> (BaseMatrix &) mtr;
    return is;
}

ostream & operator << (ostream &os, const Matrix &mat){
    os << "row = " << mat.row_ << " col = " << mat.col_ << endl;
    for (size_t i = 0; i < mat.row_; i ++){
        for (size_t j = 0; j < mat.col_; j ++)
            os << mat[i][j] << ' ';
        os << endl;
    }
    return os;
}