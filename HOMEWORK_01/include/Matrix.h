#ifndef ADVANCED_PROGRAMMING_MATRIX_H
#define ADVANCED_PROGRAMMING_MATRIX_H
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

class SparseMatrix
{
public:
    // An empty sparse matrix does not make sense, so we don't implement any default constructor

    SparseMatrix(const std::vector<double>& values,
                 const std::vector<int>& column_data,
                 const std::vector<int>& row_data,
                 const int colnum, const int rownum) : values(values),
                                                       column_data(column_data), row_data(row_data),
                                                       colnum(colnum), rownum(rownum)
    {
        if (!is_valid(values, column_data, colnum)) throw std::invalid_argument("Invalid matrix values");
    }

    virtual ~SparseMatrix() = default;

    SparseMatrix& operator=(const SparseMatrix&) = delete;


    // Tries to access element (i, j) of the matrix. If outside of bounds or non-existent, throws.
    virtual double& operator()(const int i, const int j) final
    {
        /* To avoid having to override the () operator for every subclass,
         * we override it once in the base class and force every subclass to
         * implement their own get_element method. We also make it final to
         * force this exact logic.
         */
        try
        {
            auto& res = get_element(i, j);
            return res;
        }
        catch (std::exception& e)
        {
            /* The exercise leaves open the possibility of allocating
             * a new element when A(i, j) = x is performed with an in-bounds
             * pair of coordinates if an element is not present. This cannot
             * be done by simply overriding the () operator, since it
             * doesn't know if it's being called for a simple read or for
             * a write operation. This would mean that the user could
             * repeatedly call A(i, j) and allocate zero values across
             * the sparse matrix, with no way to automatically prune unused
             * allocations, which is incompatible with the matrix format's purpose.
             */
            std::cerr << "Matrix element does not exist" << std::endl;
            throw;
        }
    }

    // Tries to perform the product y = Mx. Throws if dimensional errors are found.
    virtual std::vector<double> operator*(const std::vector<double>& x) final;

    /*
     * Since the format conversion has to use directly the internal vectors of the matrix,
     * they are declared in the base class as static utilities in order to access everything
     * they need.
     */

    // Returns a CSR-formatted matrix from a COO one
    static SparseMatrix* COOtoCSR(const SparseMatrix& coo);
    // Returns a COO-formatted matrix from a CSR one
    static SparseMatrix* CSRtoCOO(const SparseMatrix& csr);

    // Checks initial validity of the SparseMatrix
    static bool is_valid(const std::vector<double>& values,
                         const std::vector<int>& column_data,
                         const int colnum);

    // Returns the number of columns of the matrix
    virtual int get_colnum() const final
    {
        return colnum;
    }

    // Returns the number of rows of the matrix
    virtual int get_rownum() const final
    {
        return rownum;
    }

    // Returns the number of nonzero elements of the matrix
    virtual int get_nonzerosnum() const final
    {
        return static_cast<int>(values.size());
    }

    // Prints the three vectors defining the matrix one below the other
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

    // Tries to retrieve element (i, j) of the matrix. If outside of bounds or non-existent, throws.
    virtual double& get_element(int i, int j) = 0;

    // Tries to retrieve a copy of element (i, j) of the matrix. If outside of bounds or non-existent, throws.
    virtual double read_element(int i, int j) const = 0;

    // Returns the 1-indexed highest column found in the provided data
    static int deduce_maxcolumn(const std::vector<int>& column_data)
    {
        /* Since the column information in both formats is the same
         * we can implement this function in the base class
         */
        if (column_data.empty()) return 0;
        return *std::max_element(column_data.begin(), column_data.end()) + 1;
    }

    // Returns the 1-indexed lowest column found in the provided data
    static int deduce_mincolumn(const std::vector<int>& column_data)
    {
        /* Since the column information in both formats is the same
         * we can implement this function in the base class
         */
        if (column_data.empty()) return 0;
        return *std::min_element(column_data.begin(), column_data.end()) + 1;
    }

private:
    const int colnum;
    const int rownum;
};

class SparseMatrixCOO final : public SparseMatrix
{
public:
    // Creates a sparse matrix in the COO format.
    SparseMatrixCOO(const std::vector<double>& values,
                    const std::vector<int>& column_data,
                    const std::vector<int>& row_data,
                    const int colnum, const int rownum): SparseMatrix(values, column_data, row_data, colnum, rownum)
    {
        if (!is_valid(values, column_data, row_data, colnum, rownum)) throw std::invalid_argument("Invalid matrix values");
    }

    /* A COO matrix is valid iff the following conditions are met:
     * There are no duplicates;
     * All the vectors have the same size;
     * Dimensions are coherent with provided data;
     */
    static bool is_valid(const std::vector<double>& values,
                         const std::vector<int>& column_data,
                         const std::vector<int>& row_data,
                         const int colnum, const int rownum);

protected:
    // Returns the 1-indexed highest row found in the provided data
    static int deduce_maxrow(const std::vector<int>& row_data)
    {
        if (row_data.empty()) return 0;
        return *std::max_element(row_data.begin(), row_data.end()) + 1;
    }

    // Returns the 1-indexed lowest row found in the provided data
    static int deduce_minrow(const std::vector<int>& row_data)
    {
        if (row_data.empty()) return 0;
        return *std::min_element(row_data.begin(), row_data.end()) + 1;
    }

    double& get_element(int i, int j) override;

    double read_element(int i, int j) const override;

private:
    static bool duplicates_exist(const std::vector<int>& column_data,
                                 const std::vector<int>& row_data);
};

class SparseMatrixCSR final : public SparseMatrix
{
public:
    // Creates a sparse matrix in the CSR format.
    SparseMatrixCSR(const std::vector<double>& values,
                    const std::vector<int>& column_data,
                    const std::vector<int>& row_data,
                    const int colnum, const int rownum): SparseMatrix(values, column_data, row_data, colnum, rownum)
    {
        if (!is_valid(values, column_data, row_data, colnum, rownum)) throw std::invalid_argument("Invalid matrix values");
    }

    /* A CSR matrix is valid iff the following conditions are met:
     * Dimensions are coherent with provided data;
     * There are no duplicates (Already guaranteed by CSR format);
     * The values and the column vectors must have the same size;
     * The row indexes must start with 0;
     * The row indexes must be non-decreasing;
     * The last element of the row indexes must be equal to the numer of nonzero values in the matrix;
     * The difference between contiguous row indexes must be less than the number of column in the matrix;
     */
    static bool is_valid(const std::vector<double>& values,
                         const std::vector<int>& column_data,
                         const std::vector<int>& row_data,
                         const int colnum, const int rownum);

protected:
    // Returns the 1-indexed highest row found in the provided data
    static int deduce_maxrow(const std::vector<int>& row_data)
    {
        if (row_data.empty()) return 0;
        return static_cast<int>(row_data.size() - 1);
    }

    double& get_element(int i, int j) override;

    double read_element(int i, int j) const override;

private:
};

#endif //ADVANCED_PROGRAMMING_MATRIX_H
