#include "../include/Matrix.h"

bool SparseMatrix::is_valid(const std::vector<double>& values,
                         const std::vector<int>& column_data,
                         const int colnum)
{
    /* Since COO and CSR share the same format for the values
     * and the column data, in a first approximation we can
     * already check for some validity by making sure that
     * there is exactly one column for each value and the given
     * number of total columns is coherent with the column data
     */
    const bool is_empty = values.empty();
    const bool columns_empty = column_data.empty() || colnum == 0;
    const bool exist_neg_columns = deduce_mincolumn(column_data) <= 0 || colnum <= 0;
    const bool columns_in_bounds = deduce_maxcolumn(column_data) <= colnum;
    const bool sizes_match = values.size() == column_data.size();
    return !is_empty && !columns_empty && !exist_neg_columns && columns_in_bounds && sizes_match;
}

std::vector<double> SparseMatrix::operator*(const std::vector<double>& x)
{
    // We cannot make this operator static
    if (static_cast<int>(x.size()) != get_colnum()) throw std::invalid_argument("Size of x does not match matrix's dimensions");

    std::vector<double> y;
    for (int r = 0; r < get_rownum(); r++)
    {
        std::vector<double> row;
        for (int c = 0; c < get_colnum(); c++)
        {
            try
            {
                row.push_back(read_element(r, c));
            }
            catch (std::exception& e)
            {
                row.push_back(0);
            }
        }
        double sum = 0;
        for (int k = 0; k < get_colnum(); k++)
        {
            sum += x[k] * row[k];
        }
        y.push_back(sum);
    }
    return y;
}

SparseMatrix* SparseMatrix::COOtoCSR(const SparseMatrix& coo)
{
    /* Since the COO matrix might not be formatted in a convenient
     * way (i.e. with everything ordered by row), for each row index
     * we keep track of the indexes if the elements in values and column_data
     * that belong to that row, and then we add them in order to the new vectors
     */
    auto csr_values = std::vector<double>();
    auto csr_column_data = std::vector<int>();
    auto csr_row_data = std::vector<int>();
    csr_row_data.push_back(0);
    for (int r = 0, acc = 0; r < coo.get_rownum(); r++)
    {
        auto indexes = std::vector<int>();
        for (int k = 0; k < coo.get_nonzerosnum(); k++)
        {
            if (coo.row_data[k] == r)
            {
                acc++;
                indexes.push_back(k);
            }
        }
        for (const auto i : indexes)
        {
            csr_values.push_back(coo.values[i]);
            csr_column_data.push_back(coo.column_data[i]);
        }
        csr_row_data.push_back(acc);
    }
    return new SparseMatrixCSR(csr_values, csr_column_data, csr_row_data, coo.get_colnum(), coo.get_rownum());
}

SparseMatrix* SparseMatrix::CSRtoCOO(const SparseMatrix& csr)
{
    auto row_data = std::vector<int>();
    for (int r = 0; r < static_cast<int>(csr.row_data.size() - 1); r++)
    {
        for (int i = 0; i < csr.row_data[r + 1] - csr.row_data[r]; i++)
        {
            row_data.push_back(r);
        }
    }
    return new SparseMatrixCOO(csr.values, csr.column_data, row_data, csr.get_colnum(), csr.get_rownum());
}

void SparseMatrix::print() const
{
    std::cout << "Values:       [";
    for (const auto value : values)
    {
        std::cout << value << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "Column data:  [";
    for (const auto i : column_data)
    {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "Row data:     [";
    for (const auto i : row_data)
    {
        std::cout << i << " ";
    }
    std::cout << "]" << std::endl;
}

bool SparseMatrixCOO::is_valid(const std::vector<double>& values,
                               const std::vector<int>& column_data,
                               const std::vector<int>& row_data,
                               const int colnum, const int rownum)
{
    const bool rows_empty = row_data.empty() || rownum == 0;
    const bool rows_valid = deduce_maxrow(row_data) <= rownum && values.size() == row_data.size();
    const bool exist_neg_rows = deduce_minrow(row_data) <= 0 || rownum <= 0;
    const bool rows_in_bounds = deduce_maxrow(row_data) <= rownum;
    const bool sizes_match = values.size() == row_data.size();
    return SparseMatrix::is_valid(values, column_data, colnum) && !rows_empty && rows_valid  && !exist_neg_rows && rows_in_bounds && sizes_match && !duplicates_exist(column_data, row_data);
}

bool SparseMatrixCOO::duplicates_exist(const std::vector<int>& column_data,
                                       const std::vector<int>& row_data)
{
    const int size = static_cast<int>(column_data.size());
    bool duplicates_exist = false;
    for (int k = 0; k < size - 1 && !duplicates_exist; k++)
    {
        const auto r = row_data.at(k);
        const auto c = column_data.at(k);
        for (int i = k + 1; i < size; i++)
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

double& SparseMatrixCOO::get_element(const int i, const int j)
{
    if (i < 0 || j < 0 || i >= get_rownum() || j >= get_colnum()) throw std::invalid_argument("Index out of bounds");
    for (int c = 0; c < static_cast<int>(values.size()); c++)
    {
        if (row_data[c] == i && column_data[c] == j)
        {
            return values[c];
        }
    }
    throw std::invalid_argument("Access to unallocated data");
}

double SparseMatrixCOO::read_element(const int i, const int j) const
{
    if (i < 0 || j < 0 || i >= get_rownum() || j >= get_colnum()) throw std::invalid_argument("Index out of bounds");
    for (int c = 0; c < static_cast<int>(values.size()); c++)
    {
        if (row_data[c] == i && column_data[c] == j)
        {
            return values[c];
        }
    }
    return 0.0;
}

bool SparseMatrixCSR::is_valid(const std::vector<double>& values,
                               const std::vector<int>& column_data,
                               const std::vector<int>& row_data,
                               const int colnum, const int rownum)
{
    const bool rows_empty = row_data.empty() || rownum == 0;
    const bool rows_in_bounds = deduce_maxrow(row_data) <= rownum;
    const bool starts_with_zero = row_data.at(0) == 0;
    const bool is_sorted = std::is_sorted(row_data.begin(), row_data.end());
    bool rows_overflow = false;
    for (int i = 1; i < static_cast<int>(row_data.size()); i++)
    {
        if (row_data.at(i) - row_data.at(i - 1) > deduce_maxcolumn(column_data))
        {
            rows_overflow = true;
            break;
        }
    }
    const bool accumulates_to_numvals = row_data.at(row_data.size() - 1) == static_cast<int>(values.size());
    return SparseMatrix::is_valid(values, column_data, colnum) && !rows_empty && rows_in_bounds && starts_with_zero && is_sorted && !rows_overflow && accumulates_to_numvals;
}

double& SparseMatrixCSR::get_element(const int i, const int j)
{
    if (i < 0 || j < 0 || i >= get_rownum() || j >= get_colnum()) throw std::invalid_argument("Index out of bounds");
    for (int c = row_data[i]; c < row_data[i + 1]; c++)
    {
        if (column_data[c] == j)
        {
            return values[c];
        }
    }
    throw std::invalid_argument("Access to unallocated data");
}

double SparseMatrixCSR::read_element(const int i, const int j) const
{
    if (i < 0 || j < 0 || i >= get_rownum() || j >= get_colnum()) throw std::invalid_argument("Index out of bounds");
    for (int c = row_data[i]; c < row_data[i + 1]; c++)
    {
        if (column_data[c] == j)
        {
            return values[c];
        }
    }
    return 0.0;
}
