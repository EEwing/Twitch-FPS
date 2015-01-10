#include "Vector.h"
#include <stdio.h>
#include <cmath>

Vector::Vector()
{
   x = y = z = 0.0;
}
Vector::Vector(double x, double y, double z)
{
   this->x = x;
   this->y = y;
   this->z = z;
}
Vector::Vector(const Vector &v)
{
   x = v.x;
   y = v.y;
   z = v.z;
}
// MUST be at LEAST 3 deep
Vector::Vector(double *in) {
   x = in[0];
   y = in[1];
   z = in[2];
}
double Vector::GetMagnitude() const
{
   return sqrt(Vector::dot(*this, *this));
}
Vector Vector::normalize() const
{
   return *this/GetMagnitude();
}
double Vector::dot(Vector v1, Vector v2)
{
   return ((v1.x*v2.x) + (v1.y*v2.y) + (v1.z*v2.z));
}
Vector Vector::cross(Vector v) const
{
   Vector newV(( y * v.z) - ( z * v.y),
               ( z * v.x) - ( x * v.z),
               ( x * v.y) - ( y * v.x));
   return newV;
}

char * Vector::toString() const
{
   char * msg = new char[1024];
   sprintf(msg, "Vector Components: (%f, %f, %f)", x, y, z);
   return msg;
}

Vector Vector::operator+(const Vector& v)  const
{
   return Vector(this->x+v.x, this->y+v.y, this->z+v.z);
}
Vector Vector::operator-(const Vector& v) const
{
   return Vector(this->x-v.x, this->y-v.y, this->z-v.z);
}
Vector Vector::operator*(const double& coeff) const
{
   return Vector(this->x*coeff, this->y*coeff, this->z*coeff);
}
Vector Vector::operator/(const Vector& v) const
{
   return Vector(this->x/v.x, this->y/v.y, this->z/v.z);
}
Vector Vector::operator/(const double& coeff) const
{
   return Vector(this->x/coeff, this->y/coeff, this->z/coeff);
}
bool   operator==(const Vector& first, const Vector &other) {
    return (first.x == other.x &&
            first.y == other.y &&
            first.z == other.z);
}
bool   operator!=(const Vector& first, const Vector &second) {
    return !(first==second);
}
