/**
 * This file is part of the pneumatic game engine
 *
 * Copyright (c) 2014 George Burton
 *
 * THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED
 * WARRANTY. IN NO EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES
 * ARISING FROM THE USE OF THIS SOFTWARE.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 *    1. The origin of this software must not be misrepresented; you must not
 *       claim that you wrote the original software. If you use this software
 *       in a product, an acknowledgment in the product documentation would be
 *       appreciated but is not required.
 *
 *    2. Altered source versions must be plainly marked as such, and must not be
 *       misrepresented as being the original software.
 *
 *    3. This notice may not be removed or altered from any source
 *       distribution.
 *
 **/

#pragma once

#ifndef PNEUMATIC_CORE_FUNCRESULT_HPP
#define PNEUMATIC_CORE_FUNCRESULT_HPP

#include <cassert>
#include <exception>
#include <functional>
#include <memory>
#include <string>

#include "pneu/core/Forward.hpp"

namespace pneu {

namespace core {

#ifdef __EXCEPTIONS

class FuncResultException : std::exception {
public:
    FuncResultException(const char* const desc): fDescription(desc) { }

    FuncResultException(const std::string& desc): fDescription(desc.c_str()) { }

    inline virtual auto what() const noexcept -> const char*
    {
        return fDescription;
    }

private:
    const char* const fDescription;
};

#endif // __EXCEPTIONS

template<typename T>
class FuncResult final {
public:
    static inline auto ok(const T& val) -> FuncResult<T>
    {
        return {std::make_unique<T>(val), ""};
    }

    static inline auto error(const std::string& desc) -> FuncResult<T>
    {
        return {nullptr, desc};
    }

    FuncResult(const FuncResult& other) :
        fContents(std::unique_ptr<T>(other.fContents.get())),
        fDescription(other.fDescription) { }

    inline auto resetOk(const T& val) -> void
    {
        fContents.reset(&val);
    }

    inline auto resetError(const std::string& description) -> void
    {
        fContents.release();
        fDescription = description;
    }

    inline auto isOk() const -> bool
    {
        return fContents != nullptr;
    }

    inline auto getError() const -> std::string
    {
        return fDescription;
    }

    inline auto map(const std::function<T (T)>& f) -> FuncResult<T>
    {
        if (!isOk()) {
            return *this;
        }
    return FuncResult(f(*fContents), fDescription);
    }

    template<typename U>
    inline auto mapOrElse(const std::function<U (T)>& f, const U& val) -> FuncResult<U>
    {
        if (!isOk()) {
            return FuncResult::ok(val);
        }
    return FuncResult(f(*fContents), fDescription);
    }

    inline auto voidMap(const std::function<void (T)>& f) -> void
    {
        if (isOk()) {
            f(*fContents);
        }
    }

    inline auto get() const -> T
    {
        assert(isOk());
        return *fContents;
    }

    inline auto getOrElse(const T& val) -> T
    {
        return isOk() ? *fContents : val;
    }

    inline auto getOrElse(const std::function<T (const std::string&)>& f) -> T
    {
        return isOk() ? *fContents : f(getError());
    }

#ifdef __EXCEPTIONS
    inline auto getOrThrow(const std::exception& e) -> T
    {
        if (!isOk()) {
            throw e;
        }
        return *fContents;
    }

    inline auto getOrThrow() -> T
    {
        if (!isOk()) {
            throw FuncResultException(fDescription);
        }
        return *fContents;
    }
#endif // __EXCEPTIONS

private:
    FuncResult(std::unique_ptr<T> data, const std::string& desc):
        fContents(std::move(data)),
        fDescription(desc) { }

    std::unique_ptr<T> fContents;
    const std::string fDescription;
};

template<>
class FuncResult<void> final {
public:
    static inline auto ok() -> FuncResult<void>
    {
        return {true, ""};
    }

    static inline auto error(const std::string& desc) -> FuncResult<void>
    {
        return {false, desc};
    }

    inline auto isOk() const -> bool
    {
        return fOk;
    }

    inline auto getError() const -> std::string
    {
        return fDescription;
    }

    inline auto onError(const std::function<void (const std::string&)>& f) -> void
    {
        if (!fOk) {
            f(fDescription);
        }
    }

#ifdef __EXCEPTIONS
    inline auto throwOnError(const std::exception& e) -> void
    {
        if (!fOk) {
            throw e;
        }
    }

    inline auto throwOnError() -> void
    {
        if (!fOk) {
            throw FuncResultException(fDescription);
        }
    }
#endif // __EXCEPTIONS

private:
    FuncResult(bool ok, const std::string& description):
        fOk(ok),
        fDescription(description) { }

    bool fOk;
    std::string fDescription;
};

} // namespace core

} // namespace pneu

#define PNEU_TRY_FUNC(var, func) \
    pneu::core::FuncResult var = func; \
    do { \
        if (!var_name.isOk()) { \
            return var_name; \
        } \
    } while(0)

#define PNEU_EXCEPT_TO_METHODRES(func) \
    do { \
        try { \
            func; \
        } catch(const std::exception& e) { \
            return pneu::Graphics::MethodResult::error(e.what()); \
        } \
    }

#define PNEU_TRY_METHOD_ASYNC(func) \
do { \
    auto future = std::async(std::launch::async, func); \
    future.wait(); \
    pneu::core::MethodResult result = future.get(); \
    if (!result.isOk()) { \
        return result; \
    } \
} while(0)

#define PNEU_TRY_METHOD(func) \
    do { \
        pneu::core::MethodResult result = func; \
        if (!result.isOk()) { \
            return result; \
        } \
    } while(0)

#endif // PNEUMATIC_CORE_FUNCRESULT_HPP
