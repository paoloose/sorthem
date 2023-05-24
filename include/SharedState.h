#pragma once
#include <string>
#include <mutex>
#include <thread>
#include <iostream>

// Transformation from a linear input to a cubic speed
#define LINEAR_SPEED_TO_REAL_SPEED(x) ((((x) * (x) * (x)) / 5.f) + ((x) / 2.f))

class SharedState {
    mutable std::mutex m_mutex;

    /* Application flags */

    // Whether the program is paused (starts paused)
    bool m_paused = true;

    // Whether the program has finished the sorting
    bool m_finished = false;

    // Speed of the sorting animation. It changes linearly with user input
    float m_user_speed = 1.f;

    // Real speed applied to the sorting animation (from 0 to inf)
    float m_real_speed = LINEAR_SPEED_TO_REAL_SPEED(m_user_speed);

    std::size_t m_operation_index = 0;

public:
    SharedState() = default;
    ~SharedState() = default;

    bool isPaused() const;
    void setIsPaused(bool paused);

    bool isFinished() const;
    void setIsFinished(bool finished);

    float getUserSpeed() const;
    void setUserSpeed(float speed);

    // Real speed is just a transformation of the user speed
    // and it's not meant to be changed directly (use setUserSpeed() instead)
    float getRealSpeed() const;

    std::size_t getOperationIndex() const;
    void setOperationIndex(std::size_t index);
};
