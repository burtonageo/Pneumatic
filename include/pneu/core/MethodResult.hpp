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

#ifndef PNEUMATIC_METHODRESULT_HPP
#define PNEUMATIC_METHODRESULT_HPP

#include <exception>
#include <functional>
#include <string>

namespace pneu {

namespace core {

class MethodResult final {
public:
  static inline auto ok()
    -> MethodResult
  {
    return {true, ""};
  }

  static inline auto error(const std::string& desc)
    -> MethodResult
  {
    return {false, desc};
  }

  inline auto isOk() const
    -> bool
  {
    return fOk;
  }

  inline auto getError() const
    -> std::string
  {
    return fDescription;
  }

  inline auto onError(const std::function<void (const std::string&)>& f)
    -> void
  {
    if (!isOk()) {
      f(getError());
    }
  }

  inline auto throwOnError(const std::exception& e)
    -> void
  {
    if (!isOk()) {
      throw e;
    }
  }

private:
  MethodResult(bool ok, const std::string& desc)
    :
    fOk(ok),
    fDescription(desc) { }

  const bool fOk;
  const std::string fDescription;
};

} // namespace core

} // namespace pneu

#define PNEU_EXCEPT_TO_METHODRES(func) \
  do { \
    try { \
      func; \
    } catch(const std::exception& e) { \
      return pneu::Graphics::MethodResult::error(e.what()); \
    } \
  }

#define PNEU_TRY_METHOD(func) \
  do { \
    pneu::core::MethodResult result = func; \
    if (!result.isOk()) { \
      return result; \
    } \
  } while(0)

#define PNEU_TRY_METHOD_ASYNC(func) \
  do { \
    auto future = std::async(std::launch::async, func); \
    future.wait(); \
    pneu::core::MethodResult result = future.get(); \
    if (!result.isOk()) { \
      return result; \
    } \
  } while(0)

#endif // PNEUMATIC_METHODRESULT_HPP
