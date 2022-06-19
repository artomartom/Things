
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <assert.h>

using std::cout;
using std::max;
using std::string;
using std::string_view;
using std::vector;
using T = int;
using ColIt = std::vector<std::vector<T>>::iterator;
using RowIt = std::vector<T>::iterator;
using Vec = std::vector<T>;
using Mat = std::vector<Vec>;

#define COUT_WIDTH 4
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &vec)
{
    for (auto &each : vec)
    {
        os << std::setw(COUT_WIDTH) << each << std::setw(COUT_WIDTH);
    }
    return os << '\n';
}
RowIt Up(ColIt &col, RowIt &row)
{
    auto index{row - (*col).begin()};
    --col;
    RowIt newRow{(*col).begin()};
    std::advance(newRow, index);
    return newRow;
};
Mat LCS(string_view left, string_view right)
{
    if (left.length() == 0 || right.length() == 0)
        return {};
    Mat mat(
        right.length() + 1,    // add 1 col for "" cast
        Vec(left.length() + 1, // add 1 row for "" cast
            '\0'));

    for (size_t col{1}; // skip "" cast col
         col != right.size() + 1;
         ++col)
    {
        char m{right[col - 1]};

        for (size_t row{1}; // skip "" cast row
             row != left.size() + 1;
             ++row)
        {
            char n{left[row - 1]};
            if (n == m)
            {
                mat[col][row] = 1 + mat[col - 1][row - 1];
            }
            else
            {
                mat[col][row] = std::max(mat[col - 1][row], mat[col][row - 1]);
            }
        };
    };
    return mat;
};

int main(int argv, char *args[])
{
    if (!(argv >= 3))
    {
        return -1;
        cout << "lol";
    };

    const string_view left{args[1]};  // n
    const string_view right{args[2]}; // m

    string common{""};
    cout << "'" << left << "', '" << right << "'\n";

    auto mat{LCS(left, right)};
    for (auto &vec : mat)
        cout << vec;

    auto LSC{mat.back().back()};
    cout << "LSC: " << LSC << '\n';

    // ulong to int conv
    auto col{mat.size() - 1};
    auto row{mat.back().size() - 1};
    string str(LSC, ' ');
    auto i{LSC - 1};

    //      string leftDiff(left.length()-LSC, ' ');
    //      auto leftI{leftDiff.length() - 1};

    while (row > 0)
    {
        if (mat[col][row] != mat[col][row - 1])
        {
            while (mat[col][row] == mat[col - 1][row])
            {
                --col;
                cout << right[col - 1];
            }
            str[i] = left[row - 1];
            --i;
        }
        --row;
    };

    //    cout << str;
    // cout << "common " << common.c_str();
};