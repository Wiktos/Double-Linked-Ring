#pragma once
#include <stdexcept>
#include <functional>
#include <initializer_list>

template <typename Key, typename Info>
class Ring
{
    //private member type
    std::size_t length;

    //non-member function
    template <typename K, typename I>
    friend std::ostream& operator<<(std::ostream& os, const Ring<K, I>& ring);

protected:
    //protected member types
    struct Node;
    Node *any;

public:
    //public member types
    class RingInvalidArgument;
    class iterator;
    typedef const iterator const_iterator;

    //constructors
    Ring() noexcept : length(0), any(nullptr)
    {}
    Ring(const Ring<Key, Info>& source) : length(0), any(nullptr) {
        *this = source;
    }
    Ring(Ring<Key, Info>&& source) noexcept : length(std::move(source.length)), any(std::move(source.any)) {
       source.any = nullptr;
       source.length = 0;
    }
    Ring(std::initializer_list<std::pair<Key, Info>> ls) noexcept : length(0), any(nullptr){
        for(auto curr_pair : ls)
            push(curr_pair.first, curr_pair.second);
    }

    //operators
    Ring<Key, Info>& operator=(const Ring<Key, Info>& rhs);
    Ring<Key, Info>& operator=(Ring<Key, Info>&& rhs) noexcept;
    Ring<Key, Info> operator+(const Ring<Key, Info>& rhs) const{
        return this->merge(rhs);
    }
    Ring<Key, Info>& operator+=(const Ring<Key, Info>& rhs){
        *this = *this + rhs;
        return *this;
    }
    bool operator==(const Ring<Key, Info>& rhs) const noexcept;
    bool operator!=(const Ring<Key, Info>& rhs) const noexcept {
        return !(*this == rhs);
    }

    //iterator
    iterator iter() noexcept{
        return any ? iterator(any) : iterator(nullptr);
    }
    const_iterator iter() const noexcept{
        return any ? iterator(any) : iterator(nullptr);
    }

    //capacity
    bool is_empty() const noexcept { return length == 0; }
    std::size_t size() const noexcept { return length; }

    //modifiers
    void push(const Key& key, const Info& info);
    void remove(const Key& key);
    void clear() noexcept;
    void swap(Ring<Key, Info>& ring);
    void reverse() noexcept;

    //operations
    Ring<Key, Info> merge(const Ring<Key, Info>& ring) const;
    bool compare(const Ring<Key, Info>& rhs, std::function<bool(const Ring<Key, Info>&, const Ring<Key, Info>&)> comparator) const {
        return comparator(*this, rhs);
    }
    bool contain(const Key& loc) const;

    ~Ring() noexcept {
        clear();
    }
};

#include "ring.tpp"
