/**
 * This file is part of the Pneumatic game engine
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

#ifndef PNEUMATIC_OPRESULT_HPP
#define PNEUMATIC_OPRESULT_HPP

#include <string>

namespace Pneumatic {

namespace Core {

class MethodResult final {
public:
  static auto ok(void) -> MethodResult
  {
    return MethodResult(true, "");
  }

  static auto error(const std::string& desc) -> MethodResult
  {
    return MethodResult(false, desc);
  }

  MethodResult(const MethodResult&) = default;
  ~MethodResult(void)               = default;

  inline auto isOk(void) const -> bool
  {
    return fOk;
  }

  inline auto getError(void) const -> std::string
  {
    return fDescription;
  }

private:
  MethodResult(bool ok, const std::string& desc)
    :
    fOk(ok),
    fDescription(desc) { }

  const bool fOk;
  const std::string fDescription;
};

} // namespace Core

} // namespace Pneumatic

#define PNEU_EXCEPT_TO_METHODRES(func) \
  do { \
    try { \
      func; \
    } catch(const std::exception& e) { \
      return Pneumatic::Graphics::MethodResult::error(e.what()); \
    } \
  }

#define PNEU_TRY_METHOD(func) \
  do { \
    auto err = func; \
    if (!err.isOk()) { \
      return err; \
    } \
  } while(0)

#endif // PNEUMATIC_OPRESULT_HPP
