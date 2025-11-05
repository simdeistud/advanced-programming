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

    SparseMatrix(const std::vector<double>& values, const std::vector<int>& column_data,
                 const std::vector<int>& row_data) : values(values), column_data(column_data), row_data(row_data),
                                                     colnum(deduce_colnum(column_data))
    {
    }

    virtual ~SparseMatrix() = default;

    /* We override the operator virtually in the base class
     * so all we are left with is to implement get_element
     */
    virtual double& operator()(const int i, const int j)
    {
        return get_element(i, j);
    }

    virtual std::vector<double> operator*(const std::vector<double>& x) final
    {
        std::vector<double> y;
        for (int r = 0; r < rownum; r++)
        {
            std::vector<double> row;
            for (int c = 0; c < colnum; c++)
            {
                try
                {
                    row.push_back(get_element(r, c));
                }
                catch (std::exception e)
                {
                    row.push_back(0);
                }
            }
            double sum = 0;
            for (int k = 0; k < x.size(); k++)
            {
                sum += x[k] * row[k];
            }
            y.push_back(sum);
        }
        return y;
    }

    virtual std::size_t get_colnum() const final
    {
        return colnum;
    }

    virtual std::size_t get_rownum() const final
    {
        return rownum;
    }

    virtual std::size_t get_nonzerosenum() const final
    {
        return values.size();
    }

    virtual void print() const final
    {
        ...
    }

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
    virtual double& get_element(int i, int j) = 0;

private:
    std::size_t deduce_colnum(const std::vector<int>& column_data) const
    {
        return *std::max_element(column_data.begin(), column_data.end()) + 1;
    }
};

class SparseMatrixCOO final : public SparseMatrix
{
public:
    SparseMatrixCOO(const std::vector<double>& values, const std::vector<int>& column_data,
                    const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        rownum = deduce_rownum(column_data);
    }

protected:
    std::size_t deduce_rownum(const std::vector<int>& row_data) const override
    {
        return *std::max_element(row_data.begin(), row_data.end()) + 1;
    }

    double& get_element(const int i, const int j) override
    {
        for (int c = 0; c < values.size(); c++)
        {
            if (row_data[c] == i && column_data[c] == j)
            {
                return values[c];
            }
        }
        std::cerr << "Matrix element does not exist" << std::endl;
        throw;
    }

private:
};

class SparseMatrixCSR final : public SparseMatrix
{
public:
    SparseMatrixCSR(const std::vector<double>& values, const std::vector<int>& column_data,
                    const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        rownum = deduce_rownum(column_data);
    }

protected:
    std::size_t deduce_rownum(const std::vector<int>& row_data) const override
    {
        return row_data.size() - 1;
    }

    double& get_element(const int i, const int j) override
    {
        for (int c = row_data[i]; c < row_data[i + 1]; c++)
        {
            if (column_data[c] == j)
            {
                return values[c];
            }
        }
        std::cerr << "Matrix element does not exist" << std::endl;
        throw;
    }

private:
};

#endif //ADVANCED_PROGRAMMING_MATRIX_H
