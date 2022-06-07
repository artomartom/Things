#pragma once
#include "../Hello/Hello.hpp"
#include "vec.hpp"
#include <DirectXMath.h>
using namespace DirectX;

struct Vec
{
  Vec(float x, float y, float z, float w) : d{x, y, z, w} {};
  Vec(_In_reads_(4) const float *pArray) noexcept;
  float d[4]{};
  float operator[](UINT index) const { return d[index]; };
};

float operator*(const Vec &left, const Vec &right)
{
  return {left[0] * right[0] + left[1] * right[1] + left[2] * right[2] + left[3] * right[3]};
};

Vec mul(Vec vec, Vec mat[4])
{
  return {vec * mat[0],
          vec * mat[1],
          vec * mat[2],
          vec * mat[3]};
};

int main()
{
  //::Log<Console>::Write("hello");
  Vec vec{1.04f, .03325f, .654f, .235f};

  Vec mat[4]{
      {.84f, .2f, .714f, .643f},
      {.25f, .35f, .74f, .241f},
      {.42f, .2f, .42f, .2f},
      {.12f, .54f, .53f, .42f}};
  auto res{mul(vec, mat)};

  ::Log<Console>::Write(res[0], res[1], res[2], res[3]);

  XMVECTOR XMvec{XMLoadFloat4((XMFLOAT4 *)&vec)};
  XMMATRIX XMmat{(float *)mat};
  auto XMres{XMVector4Transform(XMvec, XMmat)};
  ::Log<Console>::Write(XMres.m128_f32[0], XMres.m128_f32[1], XMres.m128_f32[2], XMres.m128_f32[3]);

  auto XMresT{XMVector4Transform(XMvec, XMMatrixTranspose(XMmat))};
  ::Log<Console>::Write(XMresT.m128_f32[0], XMresT.m128_f32[1], XMresT.m128_f32[2], XMresT.m128_f32[3]);

  return 0;
};
