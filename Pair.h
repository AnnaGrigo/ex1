
#ifndef RATUV1_PAIR_H
#define RATUV1_PAIR_H

template <class Key, class Value>
class Pair
{
    Key key;
    Value value;

public:
    Pair() = default;
    Pair(Key new_key,Value new_value)
            : key(new_key)
            , value(new_value)
    {
    }
    Pair(const Pair<Key, Value> &other)
    {
        this->key = other.key;
        this->data = other.data;
    }


    friend bool operator<(Pair<Key, Value> pair1, Pair<Key, Value> pair2)
    {
        return pair1.key < pair2.key;
    }
};
#endif //RATUV1_PAIR_H
