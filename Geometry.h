#pragma once

#include <cmath>

struct Vector2 {
    float x, y;

    Vector2() : x(0), y(0) {}

    Vector2(float x, float y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }

    Vector2 operator*(const float& other) const {
        return Vector2(x * other, y * other);
    }

    Vector2 operator/(const float& other) const {
        return Vector2(x / other, y / other);
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator*=(const Vector2& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }

    Vector2& operator/=(const Vector2& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }

    Vector2& operator*=(const float& other) {
        x *= other;
        y *= other;
        return *this;
    }

    Vector2& operator/=(const float& other) {
        x /= other;
        y /= other;
        return *this;
    }

    bool operator==(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2& other) const {
        return !(*this == other);
    }

    float magnitude() const {
        return sqrt(x * x + y * y);
    }

    Vector2 normalized() const {
        auto mag = magnitude();
        return Vector2(x / mag, y / mag);
    }

    float dot(const Vector2& other) const {
        return x * other.x + y * other.y;
    }

    float cross(const Vector2& other) const {
        return x * other.y - y * other.x;
    }

    float angle(const Vector2& other) const {
        return acos(dot(other) / (magnitude() * other.magnitude()));
    }

    Vector2 rotate(float angle) const {
        return Vector2(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
    }
};

struct Transform {
    Vector2 position;
    Vector2 scale;
    float rotation;

    Transform() : position(Vector2()), scale(Vector2(1, 1)), rotation(0) {}

    Transform(Vector2 position, Vector2 scale, float rotation)
        : position(position), scale(scale), rotation(rotation) {}

    Vector2 apply(const Vector2& point) const {
        return (point - position) * scale;
    }
    
    Vector2 unapply(const Vector2& point) const {
        return point / scale + position;
    }

    Transform combine(const Transform& other) const {
        return Transform {
            position + other.position,
            scale * other.scale,
            rotation + other.rotation
        };
    }
};