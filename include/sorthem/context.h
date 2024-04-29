#pragma once

#include <vector>

// INCLUSIVE pair of vector bounds
typedef std::pair<size_t, size_t> context_t;

namespace sorthem {

template <typename T>
class ContextVector {
  private:
    std::vector<T> m_data;
    context_t m_context;

  public:
    ContextVector() : m_context(0, 0) { }
    ContextVector(std::vector<T> data) : m_data(data) { }

    void set_context(context_t context) { m_context = context; }
    void clear_context() { m_context = {0, m_data.size() - 1}; }
    void fit_context() { clear_context(); }
    std::vector<T>& underlying() { return m_data; }
    const std::vector<T>& underlying() const { return m_data; }

    void push_back(T value) { m_data.push_back(value); }
    void resize(size_t size) { m_data.resize(size); fit_context(); }
    template<typename... Args>
    void emplace_back(Args&&... args) { m_data.emplace_back(args...); }
    T& operator[](size_t index) { return m_data[m_context.first + index]; }
    size_t size() const { return m_context.second - m_context.first + 1; }
    T& last() { return m_data[m_context.second]; }
};

}
