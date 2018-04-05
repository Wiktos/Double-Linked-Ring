#pragma once

#include "ring.h"

template <typename Key, typename Info>
Ring<Key, Info> produce(const Ring<Key, Info>& r1, int start1, int step1 , bool dir1,
                        const Ring<Key, Info>& r2, int start2, int step2 , bool dir2,
                        int num, bool dir)
{
    Ring<Key, Info> retv;
    if(num < 0)
        return retv;

    typename Ring<Key, Info>::iterator iter1 = r1.iter();
    typename Ring<Key, Info>::iterator iter2 = r2.iter();

    //offset
    iter1 = iter1 + start1;
    iter2 = iter2 + start2;

    auto receive_values = [&retv](typename Ring<Key, Info>::const_iterator& iter, int start, int step , bool dir)->void{
           for(int j = 0; j < step; j++){
                std::pair<Key, Info> curr_val = *iter;
                retv.push(curr_val.first, curr_val.second);
                if(dir)
                    iter++;
                else
                    iter--;
            }
        };

    for(int i = 0; i < num; i++){
        receive_values(iter1, start1, step1, dir1);
        receive_values(iter2, start2, step2, dir2);
    }

    if(!dir)
        retv.reverse();

    return retv;
}
