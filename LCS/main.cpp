
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

#define COUT_WIDTH 6
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

    const string_view oldVersion{args[1]}; // n , row
    const string_view newVersion{args[2]}; // m , col

    cout << "'" << oldVersion << "', '" << newVersion << "'\n";

    auto mat{LCS(oldVersion, newVersion)};
    auto LSC{mat.back().back()};

#define DEBUG_INFO
#ifdef DEBUG_INFO

    cout
        << std::setw(COUT_WIDTH )
        << ' '
        << std::setw(COUT_WIDTH)
        << ' ' << std::setw(COUT_WIDTH);
    for (auto &each : oldVersion)
        cout << std::setw(COUT_WIDTH) << each << std::setw(COUT_WIDTH);
    cout << '\n';

    {

        int i{0};
        auto begin{mat.begin() + 1};
        auto end{mat.end()};

        cout << std::setw(COUT_WIDTH) << ' ' << std::setw(COUT_WIDTH) << *mat.begin();

        for (; begin != end; ++begin)
        {
            cout << std::setw(COUT_WIDTH) << newVersion[i++] << std::setw(COUT_WIDTH) << *begin;
        };
    }

    cout << "LSC: " << LSC << '\n';
#endif

    auto col{mat.size() - 1};
    auto row{mat.back().size() - 1};
    string common(LSC, '\0');
    string removed(oldVersion.length() - LSC, '\0');
    string added(newVersion.length() - LSC, '\0');

    while (col != 0 || row != 0)
    {

        if (row > 0 && (mat[col][row] == mat[col][row - 1]))
        {
            removed += oldVersion[row - 1];
            --row;
        }
        else if (mat[col][row] == mat[col - 1][row])
        {
            added += newVersion[col - 1];
            --col;
        }
        else
        {
            common += oldVersion[row - 1];
            --row;
            --col;
        }
    }
    std::reverse(common.begin(), common.end());
    std::reverse(removed.begin(), removed.end());
    std::reverse(added.begin(), added.end());
    cout << "==: " << common << '\n';
    cout << "--: " << removed << '\n';
    cout << "++: " << added << '\n';
    // cout << "common " << common.c_str();
};