#pragma once

#include <chrono>

namespace WTP
{

    class NoCopy
    {
    public:
        NoCopy() = default;
        NoCopy(NoCopy &&) = delete;
        NoCopy(const NoCopy &) = delete;
        NoCopy &operator=(NoCopy &&) = delete;
        NoCopy &operator=(const NoCopy &) = delete;
        ~NoCopy() = default;
    };

    using Ss = std::chrono::seconds;
    using Ms = std::chrono::milliseconds;
    using Us = std::chrono::microseconds;

}