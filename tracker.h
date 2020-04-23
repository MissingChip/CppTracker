#pragma once


#ifndef TRACKER_H
#define TRACKER_H

#include <mutex>
#include <vector>

template<class T>
class Tracker
{
    public:
    uint add(T* item);
    void add(T* item, uint id);
    uint add(T& item);
    void add(T& item, uint id);
    T* remove(uint id);
    T* get(uint id);
    T* get_safe(uint id);
    T* operator[](uint id);
    private:
    uint id_a = 0;
    std::mutex mtx;
    std::vector<T*> items;
};

template<class T>
inline uint Tracker<T>::add(T* item){
    mtx.lock();
    items.push_back(item);
    mtx.unlock();
    return id_a++;
}
template<class T>
inline void Tracker<T>::add(T* item, uint id){
    mtx.lock();
    ulong i = items.size();
    if(id >= i){
        items.resize(id+1);
        for(;i<id+1;i++){
            items[i] = nullptr;
        }
    }
    if(items[id]) fprintf(stderr, "Warning: id %d already occupied\n", id_a);
    items[id] = item;
    id_a = id+1;
    mtx.unlock();
}
template<class T>
inline uint Tracker<T>::add(T& item){
    return add(&item);
}
template<class T>
inline void Tracker<T>::add(T& item, uint id){
    add(&item);
}
template<class T>
inline T* Tracker<T>::remove(uint id){
    T* item = items[id];
    items[id] = nullptr;
    return item;
}
template<class T>
inline T* Tracker<T>::get(uint id){
    return items[id];
}
template<class T>
inline T* Tracker<T>::operator[](uint id){
    return items[id];
}
template<class T>
inline T* Tracker<T>::get_safe(uint id){
    if(id>=items.size()) return nullptr;
    return items[id];
}
#endif
