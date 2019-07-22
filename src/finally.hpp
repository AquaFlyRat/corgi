#pragma once

/* A simple Scope Guard implementation.
 *
 * Example usage:
 *
 *   int *ptr = new int[10];
 *   FINALLY( delete[] ptr; )
 *   // More potentially throwing code here.
 *
 * When FINALLY is reached, it doesn't execute the enclosed code immediately.
 * Instead, the code is executed when control leaves current scope, whether it's caused by an exception or not.
 * In the example above, `ptr` will be deleted no matter what.
 *
 * There are rare cases where a scope guard doesn't work. If you terminate your program (or leave current scope)
 * in a way that doesn't call destructors of local variables, a scope guard won't trigger.
 *
 * In addition to FINALLY, there is also FINALLY_ON_THROW, which is only triggered when you leave current scope
 * due to an exception.
 */

#include <exception>
#include <utility>

namespace Macro
{
    template <typename T> class FinallyObject
    {
        T func;

      public:
        FinallyObject(T &&func) : func(std::move(func)) {}
        FinallyObject(const FinallyObject &) = delete;
        FinallyObject &operator=(const FinallyObject &) = delete;
        ~FinallyObject()
        {
            func();
        }
    };
}

#define FINALLY_impl_cat(a, b) FINALLY_impl_cat_(a, b)
#define FINALLY_impl_cat_(a, b) a##b

#define FINALLY(...) ::Macro::FinallyObject FINALLY_impl_cat(_finally_object_,__LINE__) ([&]{ __VA_ARGS__ });
#define FINALLY_ON_THROW(...) FINALLY( if (::std::uncaught_exceptions()) { __VA_ARGS__ } )
