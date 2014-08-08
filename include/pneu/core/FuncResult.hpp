/**
 * This file is part of the pneu game engine
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

#ifndef PNEUMATIC_FUNCRESULT_HPP
#define PNEUMATIC_FUNCRESULT_HPP

#include <cassert>
#include <functional>
#include <memory>
#include <string>

namespace pneu {

namespace core {

template<typename T>
class FuncResult final {
public:
  static auto ok(const T& val) -> FuncResult<T>
  {
    return FuncResult(std::make_unique<T>(val), "");
  }

  static auto error(const std::string& desc) -> FuncResult<T>
  {
    return FuncResult(nullptr, desc);
  }

  FuncResult(const FuncResult& other)
    :
    fContents(std::unique_ptr<T>(other.fContents.get())),
    fDescription(other.fDescription) { }

  auto resetOk(const T& val) -> void
  {
    fContents.reset(&val);
  }

  auto resetError(const std::string& description) -> void
  {
    fContents.release();
    fDescription = description;
  }

  auto isOk(void) const -> bool
  {
    return fContents != nullptr;
  }

  auto getError(void) const -> std::string
  {
    return fDescription;
  }

  auto map(const std::function<T (T)>& f) -> FuncResult<T>
  {
    if (!isOk()) {
      return *this;
    }
    return FuncResult(f(*fContents), fDescription);
  }

  template<typename U>
  auto mapOrElse(const std::function<U (T)>& f, const U& val) -> FuncResult<U>
  {
    if (!isOk()) {
      return FuncResult::ok(val);
    }
    return FuncResult(f(*fContents), fDescription);
  }

  auto voidMap(const std::function<void (T)>& f) -> void
  {
    if (isOk()) {
      f(*fContents);
    }
  }

  auto get(void) const -> T
  {
    assert(isOk());
    return *fContents;
  }

  auto getOrElse(const T& val) -> T
  {
    return isOk() ? *fContents : val;
  }

  auto getOrElse(const std::function<T (const std::string&)>& f) -> T
  {
    return isOk() ? *fContents : f(getError());
  }

  auto getOrThrow(const std::exception& e) -> T
  {
    if (!isOk()) {
      throw e;
    }
    return *fContents;
  }

private:
  FuncResult(std::unique_ptr<T> data,
             const std::string& desc)
    :
    fContents(std::move(data)),
    fDescription(desc) { }

  std::unique_ptr<T> fContents;
  const std::string fDescription;
};

} // namespace core

} // namespace pneu

#define PNEU_TRY_FUNC(var, func) \
  auto var = func; \
  do { \
    if (!var_name.isOk()) { \
      return var_name; \
    } \
  } while(0)

#endif // PNEUMATIC_FUNCRESULT_HPP