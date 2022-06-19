#include <iostream>
#include <algorithm>
#include <vector>

using T = int;
using ColIt = std::vector<std::vector<T>>::iterator;
using RowIt = std::vector<T>::iterator;
using Vec = std::vector<T>;
using Mat = std::vector<Vec>;

void Up(ColIt &col, RowIt &row)
{
    auto index{row - (*col).begin()};
    --col;
    RowIt newRow{(*col).begin()};
    std::advance(newRow, index);
    row = newRow;
};
int main()
{
    Mat mat{5, Vec(5, 0)};
    mat[0] = {{12, 33467, 5, 3466, 3468}};
    mat[1] = {{12, 1243, 5, 6135, 8}};
    mat[2] = {{1782, 37, 5124, 6, 8}};
    mat[3] = {{14562, 3, 465, 776, 8}};
    mat[4] = {{12, 3456, 5, 6, 8}};
    ColIt Col{mat.end() - 1};
    RowIt Row{mat.back().end() - 1};
    Row--;
    Row--;
    Row--;
    Row--;
    Up(Col, Row);
    std::cout << *Row;
    return 0;
}
