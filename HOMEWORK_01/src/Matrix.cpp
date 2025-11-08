#include "../include/Matrix.h"

std::vector<double> SparseMatrix::operator*(const std::vector<double>& x)
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
            catch (std::exception& e)
            {
                row.push_back(0);
            }
        }
        double sum = 0;
        for (int k = 0; k < static_cast<int>(x.size()); k++)
        {
            sum += x[k] * row[k];
        }
        y.push_back(sum);
    }
    return y;
}

SparseMatrix* SparseMatrix::COOtoCSR(const SparseMatrix& coo)
{
    auto row_data = std::vector<int>();
    row_data.push_back(0);
    for (int r = 0, acc = 0; r < coo.rownum; r++)
    {
        for (int k = 0; k < coo.get_nonzerosnum(); k++)
        {
           if (coo.row_data[k] == r)
           {
               acc++;
           }
        }
        row_data.push_back(acc);
    }
    return new SparseMatrixCSR(coo.values, coo.column_data, row_data);
}
SparseMatrix* SparseMatrix::CSRtoCOO(const SparseMatrix& csr)
{
    auto row_data = std::vector<int>();
    for (int r = 0; r < static_cast<int>(csr.row_data.size() - 1); r++)
    {
        for (int i = 0; i < csr.row_data[r+1] - csr.row_data[r]; i++)
        {
            row_data.push_back(r);
        }
    }
    return new SparseMatrixCOO(csr.values, csr.column_data, row_data);
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

double& SparseMatrixCOO::get_element(const int i, const int j)
{
    for (int c = 0; c < static_cast<int>(values.size()); c++)
    {
        if (row_data[c] == i && column_data[c] == j)
        {
            return values[c];
        }
    }
    throw std::exception();
}

double& SparseMatrixCSR::get_element(const int i, const int j)
{
    for (int c = row_data[i]; c < row_data[i + 1]; c++)
    {
        if (column_data[c] == j)
        {
            return values[c];
        }
    }
    throw std::exception();
}


