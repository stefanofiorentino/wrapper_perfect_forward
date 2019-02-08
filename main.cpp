#include <iostream>
#include <memory>

template<typename T>
class wrapper
{
    T t;
public:
    explicit wrapper(T const &t) :
            t(t)
    {
        std::puts(__PRETTY_FUNCTION__);
    }

    explicit wrapper(T &&t) :
            t(std::forward<T>(t))
    {
        std::puts(__PRETTY_FUNCTION__);
    }


    wrapper(wrapper<T> const &) = default;
    wrapper<T> &operator=(wrapper<T> const&) = default;

    wrapper(wrapper<T> &&) noexcept = default;
    wrapper<T> &operator=(wrapper<T> &&) noexcept = default;

};

template<typename _Tp, typename... _Args>
inline wrapper<_Tp> make_wrapper(_Args &&... __args)
{
    std::puts(__PRETTY_FUNCTION__);
    typedef typename std::remove_const<_Tp>::type _Tp_nc;
    return wrapper<_Tp_nc>(std::forward<_Args>(__args)...);
}

class wrappee
{
};

int main()
{
    auto w = wrappee{};
    const auto wc = wrappee{};
    const auto &wcr = wrappee{};
    make_wrapper<wrappee>(w);
    make_wrapper<wrappee>(wc);
    make_wrapper<wrappee>(wcr);
    make_wrapper<wrappee>(wrappee());
    make_wrapper<wrappee>(wrappee{});
    return 0;
}