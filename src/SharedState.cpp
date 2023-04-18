#include "SharedState.h"

bool SharedState::isPaused() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_paused;
}

void SharedState::setIsPaused(bool paused) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_paused = paused;
}

bool SharedState::isFinished() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_finished;
}

void SharedState::setIsFinished(bool finished) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_finished = finished;
}

float SharedState::getUserSpeed() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_user_speed;
}

float SharedState::getRealSpeed() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_real_speed;
}

void SharedState::setUserSpeed(float speed) {
    m_user_speed = speed;
    m_real_speed = LINEAR_SPEED_TO_REAL_SPEED(m_user_speed);
    std::cout << "m_real_speed: " << m_real_speed << std::endl;
}

std::size_t SharedState::getOperationIndex() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    return m_operation_index;
}

void SharedState::setOperationIndex(std::size_t index) {
    std::lock_guard<std::mutex> lock(m_mutex);
    m_operation_index = index;
}
