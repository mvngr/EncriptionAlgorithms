#ifndef COMMONALGHORITHMS_H
#define COMMONALGHORITHMS_H

#include <utility>
#include <memory>

namespace MyAlgo
{

template<template<class ...> class Container1, template<class ...> class Container2, typename Type>
std::shared_ptr<std::pair<int, int>> findPosition(const Container1<Container2<Type>> &data, const Type value)
{
    for(std::size_t i = 0; i < data.size(); i++)
    {
        for(std::size_t j = 0; j < data.size(); j++)
            if(data.at(i).at(j) == value)
            {
                return std::make_shared<std::pair<int, int>>(std::make_pair(i, j));
            }
    }
    return nullptr;
}

}

#endif // COMMONALGHORITHMS_H
