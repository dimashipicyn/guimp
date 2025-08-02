#pragma once

#include <forward_list>
#include <functional>

namespace guimp
{
template<class... Args>
class Signal
{
    using Callback = std::function<void(Args...)>;
public:
    void operator+=(Callback callback)
    {
        m_subscribers.push_front(std::move(callback));
    }

    void Emit(Args&&... args)
    {
        for (Callback& c : m_subscribers)
            c(std::forward<Args>(args)...);
    }

private:
    std::forward_list<Callback> m_subscribers{};
};
} // namespace guimp