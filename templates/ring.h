#pragma once
#include <stdexcept>
#include <iostream>

template <typename Key, typename Info>
class Ring
{
    struct Node;

    Node *any;
    std::size_t length;

    template <typename K, typename I>
    friend std::ostream& operator<<(std::ostream& os, const Ring<K, I>& seq);

public:
    class RingInvalidArgument;
    class iterator;
    typedef const iterator const_iterator;

    Ring() noexcept : any(nullptr), length(0)
    {}
    Ring(const Ring<Key, Info>& source) : any(nullptr), length(0) {
        *this = source;
    }
    Ring(Ring<Key, Info>&& source) noexcept : any(std::move(source.any)), length(std::move(source.length)) {
       source.any = nullptr;
       source.length = 0;
    }


    Ring<Key, Info>& operator=(const Ring<Key, Info>& rhs);
    Ring<Key, Info>& operator=(Ring<Key, Info>&& rhs) noexcept;

    bool is_empty() const noexcept { return length == 0; }
    std::size_t size() const noexcept { return length; }

    void push(const Key& key, const Info& info);

    void clear() noexcept;

    ~Ring() noexcept{
        clear();
    }
};

#include "ring.tpp"
