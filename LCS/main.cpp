
#include <iostream>
#include <vector>
#include <iomanip>

using std::cout;
using std::max;
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

int main(int argv, char *args[])
{
    if (!(argv >= 3))
    {
        return -1;
        cout << "lol";
    };

    const string_view left{args[1]};  // n
    const string_view right{args[2]}; // m
    vector<vector<int>> mat(
        right.length() + 1,            // add 1 col for "" cast
        vector<int>(left.length() + 1, // add 1 row for "" cast
                    '\0'));

    for (size_t col{1}; // skip "" cast col
         col != right.size() + 1;
         ++col)
    {
        char m{right[col-1]};

        for (size_t row{1}; // skip "" cast row
             row != left.size() + 1;
             ++row)
        {
            char n{left[row-1]};
            if (n == m)
            {
                cout << '[' << n << m << ']'<<'\n';
                mat[col][row] = 1 + std::max(mat[col - 1][row], mat[col][row - 1]);
            };
        };
    };
    for (auto &vec : mat)
        cout << vec;
    //   cout << left << ' ' << right;
};