#ifndef ADVANCED_PROGRAMMING_MATRIX_H
#define ADVANCED_PROGRAMMING_MATRIX_H
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class SparseMatrix
{
public:
    SparseMatrix() : SparseMatrix(std::vector<double>(), std::vector<int>(), std::vector<int>())
    {
    }
    SparseMatrix(const std::vector<double>& values, const std::vector<int>& column_data,
                 const std::vector<int>& row_data) : values(values), column_data(column_data), row_data(row_data),
                                                     colnum(deduce_colnum(column_data))
    {
        if (!is_valid(values, column_data)) throw std::invalid_argument("Invalid matrix values");
    }
    virtual ~SparseMatrix() = default;

    /* We override the operator virtually in the base class
     * so all we are left with is to implement get_element
     */
    virtual double& operator()(const int i, const int j)
    {
        try
        {
            double& res = get_element(i, j);
            return res;
        } catch (std::exception& e)
        {
            std::cerr << "Matrix element does not exist" << std::endl;
            throw;
        }

    }
    virtual std::vector<double> operator*(const std::vector<double>& x) final;

    static SparseMatrix* COOtoCSR(const SparseMatrix& coo);
    static SparseMatrix* CSRtoCOO(const SparseMatrix& csr);

    static bool is_valid(const std::vector<double>& values, const std::vector<int>& column_data)
    {
        return values.size() == column_data.size();
    }

    virtual int get_colnum() const final
    {
        return colnum;
    }
    virtual int get_rownum() const final
    {
        return rownum;
    }
    virtual int get_nonzerosnum() const final
    {
        return static_cast<int>(values.size());
    }

    virtual void print() const final;

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
    int colnum;
    int rownum{};

    virtual int deduce_rownum(const std::vector<int>& row_data) const = 0;
    virtual double& get_element(int i, int j) = 0;

    /* Since the column information in both formats is the same
     * we can implement this function in the base class
     */
    static int deduce_colnum(const std::vector<int>& column_data)
    {
        if (column_data.empty()) return 0;
        return *std::max_element(column_data.begin(), column_data.end()) + 1;
    }

private:

};

class SparseMatrixCOO final : public SparseMatrix
{
public:
    SparseMatrixCOO()
    {
        row_data = std::vector<int>();
        rownum = deduce_rownum(row_data);
    }

    SparseMatrixCOO(const std::vector<double>& values, const std::vector<int>& column_data,
                    const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        if (!is_valid(values, column_data, row_data)) throw std::invalid_argument("Invalid matrix values");
        rownum = deduce_rownum(row_data);
    }

    static bool is_valid(const std::vector<double>& values, const std::vector<int>& column_data, const std::vector<int>& row_data)
    {
        return SparseMatrix::is_valid(values, column_data) && values.size() == row_data.size() && !duplicates_exist(column_data, row_data);
    }

protected:
    int deduce_rownum(const std::vector<int>& row_data) const override
    {
        if (row_data.empty()) return 0;
        return *std::max_element(row_data.begin(), row_data.end()) + 1;
    }

    double& get_element(int i, int j) override;

private:
    static bool duplicates_exist(const std::vector<int>& column_data, const std::vector<int>& row_data)
    {
        const int size = static_cast<int>(column_data.size());
        bool duplicates_exist = false;
        for (int k = 0; k < size - 1 && !duplicates_exist; k++)
        {
            const auto r = row_data.at(k);
            const auto c = column_data.at(k);
            for (int i = k+1; i < size; i++)
            {
                if (row_data.at(i) == r && column_data.at(i) == c)
                {
                    duplicates_exist = true;
                    break;
                }
            }
        }
        return duplicates_exist;
    }
};

class SparseMatrixCSR final : public SparseMatrix
{
public:
    SparseMatrixCSR(const std::vector<double>& values, const std::vector<int>& column_data,
                    const std::vector<int>& row_data) : SparseMatrix(values, column_data, row_data)
    {
        if (!is_valid(values, column_data, row_data)) throw std::invalid_argument("Invalid matrix values");
        rownum = deduce_rownum(row_data);
    }

    static bool is_valid(const std::vector<double>& values, const std::vector<int>& column_data, const std::vector<int>& row_data)
    {
        const bool starts_with_zero = row_data.at(0) == 0;
        const bool is_sorted = std::is_sorted(row_data.begin(), row_data.end());
        bool rows_overflow = false;
        for (int i = 1; i < static_cast<int>(row_data.size()); i++)
        {
            if (row_data.at(i) - row_data.at(i-1) > deduce_colnum(column_data))
            {
                rows_overflow = true;
                break;
            }
        }
        const bool sums_to_numvals = row_data.at(row_data.size() - 1) == values.size();
        return SparseMatrix::is_valid(values, column_data) && starts_with_zero && is_sorted && !rows_overflow && sums_to_numvals;
    }

protected:
    int deduce_rownum(const std::vector<int>& row_data) const override
    {
        if (row_data.empty()) return 0;
        return static_cast<int>(row_data.size() - 1);
    }

    double& get_element(int i, int j) override;

private:
};

#endif //ADVANCED_PROGRAMMING_MATRIX_H
