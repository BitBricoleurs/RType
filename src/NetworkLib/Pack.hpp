//
// Created by Clément Lagasse on 10/10/2023.
//

#if defined(_MSC_VER)
#define PACK(definition) __pragma(pack(push, 1)) definition __pragma(pack(pop))
#elif defined(__GNUC__) || defined(__clang__)
#define PACK(definition) definition __attribute__((packed))
#else
#error "Unknown compiler, please provide a way to align structures."
#endif

