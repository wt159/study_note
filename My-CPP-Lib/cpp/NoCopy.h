#pragma once

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

}