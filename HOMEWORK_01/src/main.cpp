#include "../include/Matrix.h"
using namespace std;
int main()
{
    /*
     * | 5 0 0 0 |
     * | 0 8 0 0 |
     * | 0 0 3 0 |
     * | 0 6 0 0 |
     */

    // COO Example
    const auto coo_values = std::vector<double>{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data);
    cout << "Nonzeros = " << coo.get_nonzerosnum() << endl;
    cout << "Columns = " << coo.get_colnum() << endl;
    cout << "Rows = " << coo.get_rownum() << endl;
    coo.print();
    cout << "Change value to 999:" << endl;
    coo(2, 2) = 999;
    coo.print();
    cout << endl;

    // CSR Example
    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data);
    cout << "Nonzeros = " << csr.get_nonzerosnum() << endl;
    cout << "Columns = " << csr.get_colnum() << endl;
    cout << "Rows = " << csr.get_rownum() << endl;
    csr.print();
    cout << endl;
    cout << "Change value to 999:" << endl;
    csr(2, 2) = 999;
    csr.print();
    cout << endl;

    cout << "COO to CSR:" << endl;
    auto* csr_from_coo = dynamic_cast<SparseMatrixCSR*>(SparseMatrix::COOtoCSR(coo));
    csr_from_coo->print();
    cout << "Change value to 333:" << endl;
    (*csr_from_coo)(3, 1) = 333;
    csr_from_coo->print();
    cout << endl;

    cout << "CSR to COO:" << endl;
    auto* coo_from_csr = dynamic_cast<SparseMatrixCOO*>(SparseMatrix::CSRtoCOO(csr));
    coo_from_csr->print();
    cout << "Change value to 333:" << endl;
    (*coo_from_csr)(3, 1) = 333;
    coo_from_csr->print();
    cout << endl;

    // x example
    const auto x = std::vector{1.0, 2.0, 3.0, 4.0};
    const auto y1 = coo * x;
    const auto y2 = csr * x;
    std::cout << "y1 = coo*x:   [";
    for (const auto d : y1)
    {
        cout << d << " ";
    }
    std::cout << "]" << std::endl;
    std::cout << "y2 = coo*x:   [";
    for (const auto d : y2)
    {
        cout << d << " ";
    }
    std::cout << "]" << std::endl;
    //cout << "coo * x = " << y1 << endl;
    //cout << "csr * x = " << y2 << endl;
    //cout << "" << << endl;

    return 0;
}