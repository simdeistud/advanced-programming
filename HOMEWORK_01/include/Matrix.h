#ifndef ADVANCED_PROGRAMMING_MATRIX_H
#define ADVANCED_PROGRAMMING_MATRIX_H
#include <algorithm>
#include <iostream>
#include <vector>

class SparseMatrix
{
public:
    SparseMatrix() : colnum(0), rownum(0)
    {
    }

    SparseMatrix(const std::vector<double>& values, const std::vector<int>& column_data, const std::vector<int>& row_data) : values(values), column_data(column_data), row_data(row_data), colnum(deduce_colnum(column_data))
    {
    }

    virtual ~SparseMatrix() = default;

protected:
    /* Since we only implement the COO and CSR formats, both of them deal
     * with rows and columns, thus we can put those vectors inside the base
     * class, even though they might mean different things in the two
     * implementations.
     */
    std::vector<double> values;
    std::vector<int> column_data;
    std::vector<int> row_data;
    /* Even though the dimensions of the matrix can be inferred at construction
     * time from the provided vectors, since their update only happens in very
     * specific conditions, it is useful to have them as accessible fields for
     * frequent usage. Since the point is to represent big sparse matrices, we
     * use size_t.
     */
    std::size_t colnum;
    std::size_t rownum;

    virtual std::size_t deduce_rownum(const std::vector<int>& row_data) const = 0;

private:
    std::size_t deduce_colnum(const std::vector<int>& column_data) const
    {
        return *std::max_element(column_data.begin(), column_data.end()) + 1;
    }
};

class SparseMatrixCOO final : public SparseMatrix
{
public:
    SparseMatrixCOO(const std::vector<double>& values, const std::vector<int>& column_data, const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        rownum = deduce_rownum(column_data);
    }

protected:
    std::size_t deduce_rownum(const std::vector<int>& row_data) const override
    {
        return *std::max_element(row_data.begin(), row_data.end()) + 1;
    }

private:
};

class SparseMatrixCSR final : public SparseMatrix
{
public:
    SparseMatrixCSR(const std::vector<double>& values, const std::vector<int>& column_data, const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        rownum = deduce_rownum(column_data);
    }

protected:
    std::size_t deduce_rownum(const std::vector<int>& row_data) const override
    {
        return row_data.size();
    }

private:
};

#endif //ADVANCED_PROGRAMMING_MATRIX_H
