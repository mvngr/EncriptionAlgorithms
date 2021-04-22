#ifndef COMMONALGHORITHMS_H
#define COMMONALGHORITHMS_H

#include <utility>
#include <memory>

#include "CiphersLibrary_global.h"

namespace MyAlgo
{

template<template<class ...> class Container1, template<class ...> class Container2, typename Type>
std::shared_ptr<std::pair<int, int>> CIPHERSLIBRARY_EXPORT findPosition(const Container1<Container2<Type>> &data, const Type value)
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

template<template<class ...> class Container1, typename Type>
std::shared_ptr<int> CIPHERSLIBRARY_EXPORT findPosition(const Container1<Type> &data, const Type value)
{
    for(std::size_t i = 0; i < data.size(); i++)
    {
            if(data.at(i) == value)
            {
                return std::make_shared<int>(i);
            }
    }
    return nullptr;
}

}

#endif // COMMONALGHORITHMS_H
