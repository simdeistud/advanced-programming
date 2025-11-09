#include "../include/SparseMatrix.h"
using namespace std;

bool can_get_colnum()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);

    return coo.get_colnum() == 4 && csr.get_colnum() == 4;
}

bool can_get_rownum()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);

    return coo.get_rownum() == 4 && csr.get_rownum() == 4;
}

bool can_get_nonzerosnum()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);

    return coo.get_nonzerosnum() == 4 && csr.get_nonzerosnum() == 4;
}

bool can_read_entry()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);

    return coo(3, 1) == 6 && csr(3, 1) == 6;
}

bool can_write_entry()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);
    coo(3, 1) = 999;

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);
    csr(3, 1) = 999;

    return coo(3, 1) == 999 && csr(3, 1) == 999;
}

bool can_compute_Mx()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);

    auto I = std::vector{1.0, 1.0, 1.0, 1.0};
    auto e3 = std::vector{0.0, 0.0, 1.0, 0.0};

    return coo * I == std::vector{5.0, 8.0, 3.0, 6.0} && coo * e3 == std::vector{0.0, 0.0, 3.0, 0.0} &&
        csr * I == std::vector{5.0, 8.0, 3.0, 6.0} && csr * e3 == std::vector{0.0, 0.0, 3.0, 0.0};
}

void can_print()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);
    coo.print();
    cout << endl;
    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);
    csr.print();
}

void can_convert_CSR()
{
    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);
    cout << "Original CSR: " << endl;
    csr.print();

    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);
    cout << "COO to CSR: " << endl;
    SparseMatrix::COOtoCSR(coo)->print();

}

void can_convert_COO()
{
    const auto coo_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo_col_data = std::vector{0, 1, 2, 1};
    const auto coo_row_data = std::vector{0, 1, 2, 3};
    auto coo = SparseMatrixCOO(coo_values, coo_col_data, coo_row_data, 4, 4);
    cout << "Original COO: " << endl;
    coo.print();

    const auto csr_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr_col_data = std::vector{0, 1, 2, 1};
    const auto csr_row_data = std::vector{0, 1, 2, 3, 4};
    auto csr = SparseMatrixCSR(csr_values, csr_col_data, csr_row_data, 4, 4);
    cout << "CSR to COO: " << endl;
    SparseMatrix::CSRtoCOO(csr)->print();
}

bool COO_equality_works()
{
    const auto coo1_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto coo1_col_data = std::vector{0, 1, 2, 1};
    const auto coo1_row_data = std::vector{0, 1, 2, 3};
    const auto coo1 = SparseMatrixCOO(coo1_values, coo1_col_data, coo1_row_data, 4, 4);

    const auto coo2_values = std::vector{3.0, 6.0, 5.0, 8.0};
    const auto coo2_col_data = std::vector{2, 1, 0, 1};
    const auto coo2_row_data = std::vector{2, 3, 0, 1};
    const auto coo2 = SparseMatrixCOO(coo2_values, coo2_col_data, coo2_row_data, 4, 4);

    return coo1 == coo1 && coo2 == coo2 && coo1 == coo2;
}

bool CSR_equality_works()
{
    const auto csr1_values = std::vector{8.0, 5.0, 6.0, 3.0};
    const auto csr1_col_data = std::vector{1, 0, 3, 2};
    const auto csr1_row_data = std::vector{0, 2, 2, 4, 4};
    const auto csr1 = SparseMatrixCSR(csr1_values, csr1_col_data, csr1_row_data, 4, 4);

    const auto csr2_values = std::vector{5.0, 8.0, 3.0, 6.0};
    const auto csr2_col_data = std::vector{0, 1, 2, 3};
    const auto csr2_row_data = std::vector{0, 2, 2, 4, 4};
    const auto csr2 = SparseMatrixCSR(csr2_values, csr2_col_data, csr2_row_data, 4, 4);

    return csr1 == csr1 && csr2 == csr2 && csr1 == csr2;
}

int main()
{
    /*
     * | 5 0 0 0 |
     * | 0 8 0 0 |
     * | 0 0 3 0 |
     * | 0 6 0 0 |
     */

    cout << "Can get number of columns: " << can_get_colnum() << endl;
    cout << "Can get number of rows: " << can_get_rownum() << endl;
    cout << "Can get number of nonzeros: " << can_get_nonzerosnum() << endl;
    cout << "Can read entry: " << can_read_entry() << endl;
    cout << "Can write entry: " << can_write_entry() << endl;
    cout << "Can perform product: " << can_compute_Mx() << endl;
    cout << "Can print: " << endl;
    can_print();
    cout << endl;
    cout << "Can convert to CSR: " << endl;
    can_convert_CSR();
    cout << "Can convert to COO: " << endl;
    can_convert_COO();
    cout << "COO equality works: " << COO_equality_works() << endl;
    cout << "CSR equality works: " << CSR_equality_works() << endl;

    return 0;
}
