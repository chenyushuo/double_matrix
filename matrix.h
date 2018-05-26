#ifndef MATRIX_H
#define MATRIX_H

#include <cstddef>

#include <iostream>
#include <string>

class BaseMatrix{
private:
    size_t size_;
    double *value_;

public:
    BaseMatrix(size_t size, const double *value = nullptr);
    BaseMatrix(const BaseMatrix &bmtr);

    BaseMatrix & operator = (const BaseMatrix &bmtr);

    virtual std :: string Type() const = 0;

    const size_t Size() const{return size_;}

    double * const begin(){return value_;}
    const double * const cbegin() const{return value_;}
    double * const end(){return value_ + size_;}
    const double * const cend() const{return value_ + size_;}

    double & operator [] (size_t idx){return *(value_ + idx);}
    const double & operator [] (size_t idx) const{return *(value_ + idx);}

    const bool operator == (const BaseMatrix &bmtr) const;
    const bool operator != (const BaseMatrix &bmtr) const;

    BaseMatrix & operator += (const BaseMatrix &bmtr);
    BaseMatrix & operator -= (const BaseMatrix &bmtr);
    BaseMatrix & operator *= (double k);
    BaseMatrix & operator /= (double k);

    friend std :: istream & operator >> (std :: istream &is, BaseMatrix &bmtr);

    virtual ~BaseMatrix();
};

class Matrix;
class ColVector;
class RowVector;

class Matrix : public BaseMatrix{
private:
    size_t row_, col_;
    size_t swap_times_;

public:
    Matrix(size_t row, size_t col, const double *value = nullptr);
    explicit Matrix(size_t n, double k);
    explicit Matrix(const ColVector &cvec);
    explicit Matrix(const RowVector &rvec);

    const size_t Row() const{return row_;}
    const size_t Col() const{return col_;}

    virtual std :: string Type() const{return "Matrix";}

    double * operator [] (size_t idx){return & BaseMatrix :: operator[](idx * col_);}
    const double * const operator [] (size_t idx) const {
        return & BaseMatrix :: operator[](idx * col_);
    }

    const Matrix Transposition() const;

    const bool operator == (const Matrix &mtr) const;
    const bool operator != (const Matrix &mtr) const;

    Matrix & operator += (const Matrix &mtr);
    Matrix & operator -= (const Matrix &mtr);
    Matrix & operator *= (double k);
    Matrix & operator /= (double k);

    void RowTransformationMulti(size_t r1, double k);
    void RowTransformationAdd(size_t r1, size_t r2, double k);
    void RowTransformationSwap(size_t r1, size_t r2);
    void RowTransformation();

    void ColTransformationMulti(size_t l1, double k);
    void ColTransformationAdd(size_t l1, size_t l2, double k);
    void ColTransformationSwap(size_t r1, size_t r2);
    void ColTransformation();

    friend const double Det(const Matrix &mtr);
    friend const Matrix Inverse(const Matrix &mtr);

    friend const Matrix operator + (const Matrix &mtr);
    friend const Matrix operator - (const Matrix &mtr);

    friend const Matrix operator + (const Matrix &a, const Matrix &b);
    friend const Matrix operator - (const Matrix &a, const Matrix &b);

    friend const Matrix operator * (const Matrix &mtr, double k);
    friend const Matrix operator * (double k, const Matrix &mtr);

    friend const Matrix operator / (const Matrix &mtr, double k);

    friend const Matrix operator * (const Matrix &a, const Matrix &b);
    friend const ColVector operator * (const Matrix &mtr, const ColVector &cvec);
    friend const RowVector operator * (const RowVector &rvec, const Matrix &mtr);
    friend const Matrix operator * (const ColVector &cvec, const RowVector &rvec);

    friend std :: istream & operator >> (std :: istream &is, Matrix &mtr);
    friend std :: ostream & operator << (std :: ostream &os, const Matrix &mtr);

    virtual ~Matrix(){}
};

class ColVector : public BaseMatrix{
private:
    size_t row_;

public:
    ColVector(size_t row, const double *value = nullptr);
    explicit ColVector(size_t n, double k);

    const size_t Row() const{return row_;}

    virtual std :: string Type() const{return "ColVector";}

    double & operator [] (size_t idx){return BaseMatrix :: operator[](idx);}
    const double & operator [] (size_t idx) const{
        return BaseMatrix :: operator[](idx);
    }

    const RowVector Transposition() const;

    const bool operator == (const ColVector &cvec) const;
    const bool operator != (const ColVector &cvec) const;

    ColVector & operator += (const ColVector &cvec);
    ColVector & operator -= (const ColVector &cvec);
    ColVector & operator *= (double k);
    ColVector & operator /= (double k);

    friend Matrix :: Matrix(const ColVector &cvec);

    friend const ColVector operator + (const ColVector &cvec);
    friend const ColVector operator - (const ColVector &cvec);

    friend const ColVector operator + (const ColVector &a, const ColVector &b);
    friend const ColVector operator - (const ColVector &a, const ColVector &b);

    friend const ColVector operator * (const ColVector &cvec, double k);
    friend const ColVector operator * (double k, const ColVector &cvec);

    friend const ColVector operator / (const ColVector &cvec, double k);

    friend const ColVector operator * (const Matrix &mtr, const ColVector &cvec);
    friend const Matrix operator * (const ColVector &cvec, const RowVector &rvec);
    friend const double operator * (const RowVector &rvec, const ColVector &cvec);

    friend std :: istream & operator >> (std :: istream &is, ColVector &cvec);
    friend std :: ostream & operator << (std :: ostream &os, const ColVector &cvec);

    virtual ~ColVector(){}
};

class RowVector : public BaseMatrix{
private:
    size_t col_;

public:
    RowVector(size_t col, const double *value = nullptr);
    explicit RowVector(size_t n, double k);

    const size_t Col() const{return col_;}

    virtual std :: string Type() const{return "RowVector";}

    double & operator [] (size_t idx){return BaseMatrix :: operator[](idx);}
    const double & operator [] (size_t idx) const{
        return BaseMatrix :: operator[](idx);
    }

    const ColVector Transposition() const;

    const bool operator == (const RowVector &rvec) const;
    const bool operator != (const RowVector &rvec) const;

    RowVector & operator += (const RowVector &rvec);
    RowVector & operator -= (const RowVector &rvec);
    RowVector & operator *= (double k);
    RowVector & operator /= (double k);

    friend Matrix :: Matrix(const RowVector &rvec);

    friend const RowVector operator + (const RowVector &rvec);
    friend const RowVector operator - (const RowVector &rvec);

    friend const RowVector operator + (const RowVector &a, const RowVector &b);
    friend const RowVector operator - (const RowVector &a, const RowVector &b);

    friend const RowVector operator * (const RowVector &rvec, double k);
    friend const RowVector operator * (double k, const RowVector &rvec);

    friend const RowVector operator / (const RowVector &rvec, double k);

    friend const RowVector operator * (const RowVector &rvec, const Matrix &mtr);
    friend const Matrix operator * (const ColVector &cvec, const RowVector &rvec);
    friend const double operator * (const RowVector &rvec, const ColVector &cvec);

    friend std :: istream & operator >> (std :: istream &is, RowVector &rvec);
    friend std :: ostream & operator << (std :: ostream &os, const RowVector &rvec);

    virtual ~RowVector(){}
};

#endif