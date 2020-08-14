#pragma once

#include <cassert>

#define ASSERT(f) assert(f)

#ifdef _DEBUG
#define VERIFY(f) ASSERT(f)
#else
#define VERIFY(f) ((void)(f))
#endif // !_DEBUG
