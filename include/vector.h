#ifndef VECTOR_H
#define VECTOR_H

#include <bits/stdc++.h>

class Vector {
private:
    std::array<double, 3> components;

public:
    Vector(double x, double y, double z);
    Vector();

    size_t dimension() const;
    
    double getComponent(size_t index) const;

    void setComponent(size_t index, double value);

    double magnitude() const ;

    Vector normalize() const ;

    double getAngleXY() const;

    Vector operator+(const Vector& other) const;

    Vector operator-(const Vector& other) const;

    Vector operator*(double scalar) const;

    double operator*(const Vector& other) const;

    Vector operator+=(const Vector& other);
};


#endif//VECTOR_H