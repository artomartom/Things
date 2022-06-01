#pragma once
#include "../Hello/Hello.hpp"
#include <DirectXMath.h>

template <UINT size>
float det(float *matRows[size])
{
  float res{};
  for (int col{}; col < size; col++)
  {
    {
      float prod{1};
      for (int i{}, j{col}; i < size; i++, j++, j %= size)
      {
        float w{matRows[i][j]};
        prod *= w;
        // ::Log<Console>::Write( i, j,' ',w);
        //::Log<Console>::Write(prod);
      }
      //  ::Log<Console>::Write(' ');
      res += prod;
    }
    {
      float prod{1};
      for (int i{size - 1}, j{(col + 1) % size}; i >= 0; i--, j++, j %= size)
      {
        float w{matRows[i][j]};
        prod *= w;
      //  ::Log<Console>::Write(i, j, ' ', w);
      }
      res -= prod;
    }
    //::Log<Console>::Write(' ');
  };

  return res;
};

using namespace DirectX;

int main( )
{
  //::Log<Console>::Write("hello");
  float mat[10][10]{
      {/**/ 4, 1, 1, 1, /**/ 45, 3, 2, 67},
      {/**/ 6, 2, 4, 4, /**/ 45, 3, 2, 67},
      {/**/ 7, 5, 2, 1, /**/ 1, 3, 2, 78},
      {/**/ 1, 2, 1, 1, /**/ 235, 3, 2, 67},
      /////////////////
      {4, 1, 14, 367, 45, 3, 2, 78},
      {4, 34, 14, 367, 45, 538, 2, 67},
      {4, 11, 14, 367, 45, 39, 2, 78},
      {4, 1, 14, 367, 45, 23, 82, 37},
      {4, 1, 14, 367, 4825, 3, 278, 31},
      {4, 1, 14, 367, 45, 3, 2, 67}};

  //(  (16-64) +(4-6)+(56-14)+(6-4));
  float *rows[10]{
      mat[0],
      mat[1],
      mat[2],
      mat[3],
      mat[4],
      mat[5],
      mat[6],
      mat[7],
      mat[8],
      mat[9]};

  ::Log<Console>::Write(det<4>(rows));

   XMMATRIX m{
       XMLoadFloat4((XMFLOAT4*) mat[0]),
       XMLoadFloat4((XMFLOAT4*) mat[1]),
       XMLoadFloat4((XMFLOAT4*) mat[2]),
       XMLoadFloat4((XMFLOAT4*) mat[3]),
   };
    

   XMVECTOR v{XMMatrixDeterminant(XMMatrixTranspose(m))};
  ::Log<Console>::Write(v.m128_f32[0]);

  return 0;
};

 
