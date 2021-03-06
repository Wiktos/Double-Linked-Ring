template <typename Key, typename Info>
std::ostream& operator<<(std::ostream& os, const Ring<Key, Info>& ring){
    typename Ring<Key, Info>::Node *curr = ring.any;
    if(!curr)
        return os;

    do{
        os << curr->key << ' ' << curr->info << '\n';
        curr = curr->next;
    }
    while(curr != ring.any);

    return os;
}

template <typename Key, typename Info>
struct Ring<Key, Info>::Node
{
    Key key;
    Info info;
    Node *prev;
    Node *next;
};

template <typename Key, typename Info>
class Ring<Key, Info>::RingInvalidArgument final : public std::invalid_argument
{
public:
    using std::invalid_argument::invalid_argument;
};

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(const Ring<Key, Info>& rhs){
    if(this == &rhs)
        return *this;

    clear();
    Node *curr = rhs.any;
    if(!curr)
        return *this;

    do{
        this->push(curr->key, curr->info);
        curr = curr->next;
    }
    while(curr != rhs.any);

    return *this;
}

template <typename Key, typename Info>
Ring<Key, Info>& Ring<Key, Info>::operator=(Ring<Key, Info>&& rhs) noexcept{
    if(this == &rhs)
        return *this;

    clear();
    any = std::move(rhs.any);
    length = std::move(rhs.length);
    rhs.any = nullptr;
    rhs.length = 0;

    return *this;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::operator==(const Ring<Key, Info>& rhs) const noexcept{
    if(size() != rhs.size())
        return false;

    if(is_empty())
        return true;

    Node *left = any;
    Node *right = rhs.any;

    do{
        if(left->key != right->key || left->info != right->info)
            return false;
        left = left->next;
        right = right->next;
    }
    while(left != any);

    return true;
}

template <typename Key, typename Info>
void Ring<Key, Info>::push(const Key& key, const Info& info){
    if(is_empty()){
        any = new Node{key, info};
        any->next = any;
        any->prev = any;
        length++;
        return;
    }

    Node *new_elem = new Node{key, info, any->prev, any};
    any->prev->next = new_elem;
    any->prev = new_elem;
    length++;
}

template <typename Key, typename Info>
void Ring<Key, Info>::remove(const Key& key){
    if(is_empty())
        throw RingInvalidArgument("Ring::remove exception");

    if(size() == 1 && any->key == key){
        delete any;
        any = nullptr;
        length--;
        return;
    }

    Node *curr = any;
    do{
        if(curr->key == key){
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
            any = curr->next;
            delete curr;
            length--;
            return;
        }
        curr = curr->next;
    }
    while(curr != any);

    throw RingInvalidArgument("Ring::remove exception");
}

template <typename Key, typename Info>
void Ring<Key, Info>::clear() noexcept{
    if(!any)
        return;

    Node *curr = any->next;
    while(curr != any){
        Node *curr_del = curr;
        curr = curr->next;
        delete curr_del;
    }
    delete any;

    length = 0;
    any = nullptr;
}

template <typename Key, typename Info>
void Ring<Key, Info>::swap(Ring<Key, Info>& ring){
    Ring<Key, Info> tmp(*this);
    *this = ring;
    ring = tmp;
}

template <typename Key, typename Info>
void Ring<Key, Info>::reverse() noexcept{
    if(is_empty())
        return;

    Node *curr = any;
    Node *next = any->next;
    do{
        //switch pointers
        Node *prev = curr->prev;
        curr->prev = curr->next;
        curr->next = prev;

        curr = next;
        next = curr->next;
    }
    while(curr != any);
}

template <typename Key, typename Info>
Ring<Key, Info> Ring<Key, Info>::merge(const Ring<Key, Info>& ring) const {
    Ring<Key, Info> ret_ring(*this);

    Node *curr = ring.any;
    do{
        ret_ring.push(curr->key, curr->info);
        curr = curr->next;
    }
    while(curr != ring.any);

    return ret_ring;
}

template <typename Key, typename Info>
bool Ring<Key, Info>::contain(const Key& loc) const {
    Node *curr = any;

    do{
        if(curr->key == loc)
            return true;
        curr = curr->next;
    }
    while(curr != any);

    return false;
}
