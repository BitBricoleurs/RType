
#pragma once

#include <functional>

struct KeyMapping {
    int key;
    std::function<bool(int)> checkFunction;
    const char* eventName;
};
