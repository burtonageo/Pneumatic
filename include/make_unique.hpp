#pragma once

#ifndef PNEUMATIC_MAKEUNIQUE_HPP
#define PNEUMATIC_MAKEUNIQUE_HPP

#include <memory>
#include <utility>

template <typename T, typename... Args>
auto make_unique(Args&&... args) -> std::unique_ptr<T>
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

#endif // PNEUMATIC_MAKEUNIQUE_HPP
