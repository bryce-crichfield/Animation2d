#pragma once

#include <cmath>
#include <functional>

using EasingFunction = std::function<float(float, float, float)>;

namespace Easing {
float Linear(float start, float end, float delta) { return start + delta * (end - start); }
} // namespace Easing

namespace Easing::Sine {
float In(float start, float end, float delta) {
    end -= start;
    return -end * cos(delta * (M_PI / 2)) + end + start;
}

float Out(float start, float end, float delta) {
    end -= start;
    return end * sin(delta * (M_PI / 2)) + start;
}

float InOut(float start, float end, float delta) {
    end -= start;
    return -end / 2 * (cos(M_PI * delta) - 1) + start;
}
} // namespace Easing::Sine

namespace Easing::Quadratic {
float In(float start, float end, float delta) {
    end -= start;
    return end * delta * delta + start;
}

float Out(float start, float end, float delta) {
    end -= start;
    return -end * delta * (delta - 2) + start;
}

float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return end / 2 * delta * delta + start;
    delta--;
    return -end / 2 * (delta * (delta - 2) - 1) + start;
}
} // namespace Easing::Quadratic

namespace Easing::Cubic {
float In(float start, float end, float delta) {
    end -= start;
    return end * delta * delta * delta + start;
}
float Out(float start, float end, float delta) {
    delta--;
    end -= start;
    return end * (delta * delta * delta + 1) + start;
}
float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return end / 2 * delta * delta * delta + start;
    delta -= 2;
    return end / 2 * (delta * delta * delta + 2) + start;
}
} // namespace Easing::Cubic

namespace Easing::Quartic {
float In(float start, float end, float delta) {
    end -= start;
    return end * delta * delta * delta * delta + start;
}

float Out(float start, float end, float delta) {
    delta--;
    end -= start;
    return -end * (delta * delta * delta * delta - 1) + start;
}

float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return end / 2 * delta * delta * delta * delta + start;
    delta -= 2;
    return -end / 2 * (delta * delta * delta * delta - 2) + start;
}
} // namespace Easing::Quartic

namespace Easing::Quintic {
float In(float start, float end, float delta) {
    end -= start;
    return end * delta * delta * delta * delta * delta + start;
}

float Out(float start, float end, float delta) {
    delta--;
    end -= start;
    return end * (delta * delta * delta * delta * delta + 1) + start;
}

float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return end / 2 * delta * delta * delta * delta * delta + start;
    delta -= 2;
    return end / 2 * (delta * delta * delta * delta * delta + 2) + start;
}
} // namespace Easing::Quintic

namespace Easing::Exponential {
float In(float start, float end, float delta) {
    end -= start;
    return end * pow(2, 10 * (delta - 1)) + start;
}

float Out(float start, float end, float delta) {
    end -= start;
    return end * (-pow(2, -10 * delta) + 1) + start;
}

float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return end / 2 * pow(2, 10 * (delta - 1)) + start;
    delta--;
    return end / 2 * (-pow(2, -10 * delta) + 2) + start;
}
} // namespace Easing::Exponential

namespace Easing::Circular {
float In(float start, float end, float delta) {
    end -= start;
    return -end * (sqrt(1 - delta * delta) - 1) + start;
}

float Out(float start, float end, float delta) {
    delta--;
    end -= start;
    return end * sqrt(1 - delta * delta) + start;
}

float InOut(float start, float end, float delta) {
    delta *= 2;
    end -= start;
    if (delta < 1) return -end / 2 * (sqrt(1 - delta * delta) - 1) + start;
    delta -= 2;
    return end / 2 * (sqrt(1 - delta * delta) + 1) + start;
}
} // namespace Easing::Circular

namespace Easing::Back {
float In(float start, float end, float delta) {
    end -= start;
    float s = 1.70158f;
    return end * delta * delta * ((s + 1) * delta - s) + start;
}

float Out(float start, float end, float delta) {
    float s = 1.70158f;
    end -= start;
    delta--;
    return end * (delta * delta * ((s + 1) * delta + s) + 1) + start;
}

float InOut(float start, float end, float delta) {
    float s = 1.70158f * 1.525f;
    end -= start;
    delta *= 2;
    if (delta < 1) return end / 2 * (delta * delta * ((s + 1) * delta - s)) + start;
    delta -= 2;
    return end / 2 * (delta * delta * ((s + 1) * delta + s) + 2) + start;
}
} // namespace Easing::Back