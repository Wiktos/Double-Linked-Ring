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


    Ring<Key, Info>& operator=(const Ring<Key, Info>& rhs);

    bool is_empty() const noexcept { return length == 0; }
    std::size_t size() const noexcept { return length; }

    void push(const Key& key, const Info& info);

    void clear() noexcept;
};

#include "ring.tpp"
