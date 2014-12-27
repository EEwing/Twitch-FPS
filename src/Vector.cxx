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
double Vector::GetMagnitude()
{
   return sqrt(this->dot(*this));
}
Vector Vector::normalize()
{
   return *this/GetMagnitude();
}
double Vector::dot(Vector v)
{
   return ((x*v.x) + (y*v.y) + (z*v.z));
}
Vector Vector::cross(Vector v)
{
   Vector newV(( y * v.z) - ( z * v.y),
               ( z * v.x) - ( x * v.z),
               ( x * v.y) - ( y * v.x));
   return newV;
}

char * Vector::toString()
{
   char * msg = new char[1024];
   sprintf(msg, "Vector Components: (%f, %f, %f)", x, y, z);
   return msg;
}

Vector Vector::operator+(const Vector& v)
{
   return Vector(this->x+v.x, this->y+v.y, this->z+v.z);
}
Vector Vector::operator-(const Vector& v)
{
   return Vector(this->x-v.x, this->y-v.y, this->z-v.z);
}
Vector Vector::operator*(const Vector& v)
{
   return Vector(this->x*v.x, this->y*v.y, this->z*v.z);
}
Vector Vector::operator*(const double& coeff)
{
   return Vector(this->x*coeff, this->y*coeff, this->z*coeff);
}
Vector Vector::operator/(const Vector& v)
{
   return Vector(this->x/v.x, this->y/v.y, this->z/v.z);
}
Vector Vector::operator/(const double& coeff)
{
   return Vector(this->x/coeff, this->y/coeff, this->z/coeff);
}
Vector Vector::operator%(const double& mod)
{
   double newX = x;
   double newY = y;
   double newZ = z;
   while(newX >= mod) { newX-= mod; };
   while(newY >= mod) { newY-= mod; };
   while(newZ >= mod) { newZ-= mod; };
   return Vector(newX, newY, newZ);
}
