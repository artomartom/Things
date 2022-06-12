
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using std::cout;
using std::max;
using std::string;
using std::string_view;
using std::vector;

#define COUT_WIDTH 4

template <typename T>
std::ostream &operator<<(std::ostream &os, const vector<T> &vec)
{
    for (auto &each : vec)
    {
        os << std::setw(COUT_WIDTH) << each << std::setw(COUT_WIDTH);
    }
    return os << '\n';
}

vector<vector<int>> LCS(string_view left, string_view right)
{
    if (left.length() == 0 || right.length() == 0)
        return {};
    vector<vector<int>> mat(
        right.length() + 1,            // add 1 col for "" cast
        vector<int>(left.length() + 1, // add 1 row for "" cast
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
    cout << "LSC: " << mat.back().back() << '\n';

    auto begin{mat.back().rbegin()};
    auto end{mat.back().rend()};
    auto target{*end};

    for (; begin != end ;++begin)
    {
        //if (*begin == target)
           // break;
           //cout<<' ' <<*begin;
    };

    // cout << "common " << common.c_str();
};