#pragma once

#include "Easing.h"
#include "Geometry.h"

struct Keyframe {
    Transform start;
    Transform end;
    EasingFunction easing;

    Keyframe() : start(), end(), easing(Easing::Linear) {}

    Keyframe(Transform start, Transform end, EasingFunction easing)
        : start(start), end(end), easing(easing) {}
};

struct FrameState {
    Keyframe keyframe;
    float duration;
    float elapsed;

    FrameState(Keyframe keyframe, float duration, float elapsed)
        : keyframe(keyframe), duration(duration), elapsed(elapsed) {}

    void update(float delta) {
        elapsed += delta;
    }

    bool isComplete() { return elapsed >= duration; }

    Transform getTransform() {
        Transform transform;
        float alpha = elapsed / duration;

        transform.position.x =
            keyframe.easing(keyframe.start.position.x, keyframe.end.position.x, alpha);
        transform.position.y =
            keyframe.easing(keyframe.start.position.y, keyframe.end.position.y, alpha);

        transform.scale.x = keyframe.easing(keyframe.start.scale.x, keyframe.end.scale.x, alpha);
        transform.scale.y = keyframe.easing(keyframe.start.scale.y, keyframe.end.scale.y, alpha);

        transform.rotation = keyframe.easing(keyframe.start.rotation, keyframe.end.rotation, alpha);

        return transform;
    }
};

class Animation {
    std::vector<FrameState> frames;
    unsigned index = 0;

  public:
    Animation() : index(0) {}

    Animation(std::vector<FrameState> frames) : frames(frames) {}

    void update(float delta) {
        auto& frame = frames[index];
        frame.update(delta);

        if (frame.isComplete()) {
            index = (index + 1) % frames.size();
            frame.elapsed = 0.0f;
        }
    }

    void add(Keyframe keyframe, float duration) {
        frames.push_back(FrameState(keyframe, duration, 0.0f));
    }

    Transform get() { return frames[index].getTransform(); }
};

class AnimationBuilder {
    std::vector<FrameState> frames;
    Keyframe keyframe = Keyframe();

  public:
    AnimationBuilder() {}

    AnimationBuilder(float x, float y) {
        keyframe.start.position.x = x;
        keyframe.start.position.y = y;
        keyframe.end.position.x = x;
        keyframe.end.position.y = y;
        this->add(0.0f);
    }

    AnimationBuilder(Transform start) {
        keyframe.start = start;
        keyframe.end = start;
        this->add(0.0f);
    }

    void moveTo(float x, float y) {
        auto last = frames.back();
        keyframe.start.position = last.keyframe.end.position;
        keyframe.end.position.x = x;
        keyframe.end.position.y = y;
    }

    void scaleTo(float x, float y) {
        auto last = frames.back();
        keyframe.start.scale = last.keyframe.end.scale;
        keyframe.end.scale.x = x;
        keyframe.end.scale.y = y;
    }

    void rotateTo(float angle) {
        auto last = frames.back();
        keyframe.start.rotation = last.keyframe.end.rotation;
        keyframe.end.rotation = angle;
    }

    void moveBy(float x, float y) {
        auto last = frames.back();
        keyframe.start.position = last.keyframe.end.position;
        keyframe.end.position.x = last.keyframe.end.position.x + x;
        keyframe.end.position.y = last.keyframe.end.position.y + y;
    }

    void scaleBy(float x, float y) {
        auto last = frames.back();
        keyframe.start.scale = last.keyframe.end.scale;
        keyframe.end.scale.x = last.keyframe.end.scale.x + x;
        keyframe.end.scale.y = last.keyframe.end.scale.y + y;
    }

    void rotateBy(float angle) {
        auto last = frames.back();
        keyframe.start.rotation = last.keyframe.end.rotation;
        keyframe.end.rotation = last.keyframe.end.rotation + angle;
    }

    void add(float duration) {
        frames.push_back(FrameState(keyframe, duration, 0.0f));
        keyframe = Keyframe();
    }

    Animation build() { return Animation(frames); }
};
