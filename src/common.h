#ifndef _COMMON_H_
#define _COMMON_H_

#include <memory>
#include <string>
#include <unordered_map>

#include "Animation.hpp"

using animationMap_t = std::unordered_map<std::string, std::unique_ptr<Animation>>;

#endif//_COMMON_H_
