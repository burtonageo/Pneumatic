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

#include "pneu/core/ResourceLoader.hpp"

#include <fstream>
#include <iostream>
#include <string>

using namespace std;
using namespace pneu::core;

auto
pneu::core::ResourceLoader::loadTextFile(const std::string& path) -> pneu::core::FuncResult<std::string>
{
  string file_contents;
  ifstream file_stream(path, ios::in);
  if (file_stream.is_open()) {
    string line = "";
    while (getline(file_stream, line)) {
        file_contents += "\n" + line;
    }
    file_stream.close();
  } else {
    return FuncResult<std::string>::error(string("Could note open file: ") + path);
  }

  return FuncResult<std::string>::ok(file_contents);
}
