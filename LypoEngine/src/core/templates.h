//
// Created by GuillaumeIsCoding on 7/26/2024.
//
#pragma once

#include <memory>

namespace core
{
    template<typename T>
    using LypoUniquePtr = std::unique_ptr<T>;

    template<typename T, typename ... Args>
    constexpr LypoUniquePtr<T> CreateLypoUniquePtr(Args& ... args)
    {
        return std::make_unique<T>(std::forward<Args>(args) ...);
    }
}
