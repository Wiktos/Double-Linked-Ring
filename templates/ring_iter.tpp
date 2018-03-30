template <typename Key, typename Info>
class Ring<Key, Info>::iterator
{
    mutable Node *it;

public:
    iterator(Node *node) noexcept : it(node)
    {}

    iterator& operator=(const iterator& rhs) noexcept{
        it = rhs.it;
        return *this;
    }

    Node operator*() noexcept{
        return *it;
    }
    const Node operator*() const noexcept{
        return *it;
    }

    Node* operator->() noexcept{
        return it;
    }

    const Node* operator->() const noexcept{
        return it;
    }

    bool operator==(iterator rhs) const noexcept{
        return it == rhs.it;
    }
    bool operator!=(iterator rhs) const noexcept{
        return it != rhs.it;
    }

    iterator operator++(int) const noexcept{
        iterator curr(it);
        it = it->next;
        return curr;
    }

    iterator operator++() const noexcept{
        it = it->next;
        return *this;
    }

    iterator operator+(int rhs) const noexcept{
        for(int i = 0; i < rhs; i++)
            it = it->next;

        return *this;
    }

    iterator operator--(int) const noexcept{
        iterator curr(it);
        it = it->prev;
        return curr;
    }

    iterator operator--() const noexcept{
        it = it->prev;
        return *this;
    }

    iterator operator-(int rhs) const noexcept{
        for(int i = 0; i < rhs; i++)
            it = it->prev;

        return *this;
    }
};
