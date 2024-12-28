#include <bits/stdc++.h>
#include "../include/vector.h"

Vector::Vector(double x, double y, double z){
    components[0] = x;
    components[1] = y;
    components[2] = z;
}

Vector::Vector(){
    components[0] = 0;
    components[1] = 0;
    components[2] = 0;
}

size_t Vector::dimension() const {
    return 3;
}

double Vector::getComponent(size_t index) const {
    if (index >= components.size()) {
        throw std::out_of_range("Index out of range");
    }
    return components[index];
}

void Vector::setComponent(size_t index, double value) {
    if (index >= components.size()) {
        throw std::out_of_range("Index out of range");
    }
    components[index] = value;
}

double Vector::magnitude() const {
    double sum = 0.0;
    for (double c : components) {
        sum += c * c;
    }
    return std::sqrt(sum);
}

Vector Vector::normalize() const {
    double mag = magnitude();
    if (mag == 0.0) return Vector();
    return Vector(components[0] / mag, components[1] / mag, components[2] / mag);
}

Vector Vector::operator+(const Vector& other) const {
    return Vector(
        components[0] + other.components[0],
        components[1] + other.components[1],
        components[2] + other.components[2]
    );
}

Vector Vector::operator-(const Vector& other) const {
    return Vector(
        components[0] - other.components[0],
        components[1] - other.components[1],
        components[2] - other.components[2]
    );
}

Vector Vector::operator*(double scalar) const {
    return Vector(
        components[0] * scalar,
        components[1] * scalar,
        components[2] * scalar
    );
}

Vector Vector::operator+=(const Vector& other) {
    components[0] += other.components[0];
    components[1] += other.components[1];
    components[2] += other.components[2];
    return *this;
}