#pragma once

template<typename T>
class Node final {
public:
    Node() noexcept;
    ~Node() noexcept;

    int32_t getIndex() const noexcept;
private:

    int32_t id;

    static int32_t minAvailableId;

};