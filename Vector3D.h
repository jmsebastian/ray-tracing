#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <iostream>
using namespace std;

class Vector3D
{
public:
  double x, y, z;

public:
  Vector3D();
  Vector3D(double n);
  Vector3D(const Vector3D &v);
  Vector3D(double v_x, double v_y, double v_z);
  Vector3D &operator=(const Vector3D &v);
  Vector3D operator+(const Vector3D &v) const;
  Vector3D operator-(const Vector3D &v) const;
  Vector3D operator/(double number) const;
  Vector3D operator*(double number) const;
  double operator*(const Vector3D &v) const;
  Vector3D operator^(const Vector3D &v) const;
  void show();
};
#endif