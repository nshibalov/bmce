#ifndef BMCE_CORE_EVENT_H
#define BMCE_CORE_EVENT_H


#include <functional>
#include <vector>


namespace bmce
{
namespace detail
{


template <class C, typename R, typename ...ARGS>
std::function<R(ARGS...)> make_func(C* c, R (C::*m)(ARGS...))
{
    return [=](ARGS&&... args)
    {
        return (c->*m)(std::forward<ARGS>(args)...);
    };
}


template <class C, typename R, typename ...ARGS>
std::function<R(ARGS...)> make_func(
    const C* c, R (C::*m)(ARGS...) const)
{
    return [=](ARGS&&... args)
    {
        return (c->*m)(std::forward<ARGS>(args)...);
    };
}


} // namespace detail
} // namespace bmce


namespace bmce
{


template<typename ...ARGS>
class Event
{
public:
    using Func = std::function<void(ARGS...)>;
    using NoArgFunc = std::function<void()>;

private:
    std::vector<Func> funcs_;
    std::vector<NoArgFunc> na_funcs_;

public:
    void add_listener(const Func& func)
    {
        funcs_.push_back(func);
    }

    void add_listener(const NoArgFunc& func)
    {
        na_funcs_.push_back(func);
    }

    template<typename T>
    void add_listener(void(T::*func_ptr)(ARGS...), T* obj)
    {
        funcs_.push_back(detail::make_func(obj, func_ptr));
    }

    template<typename T>
    void add_listener(void(T::*func_ptr)(), T* obj)
    {
        na_funcs_.push_back(detail::make_func(obj, func_ptr));
    }

    void trigger(ARGS&&... args)
    {
        for (const auto& func : funcs_)
        {
            func(std::forward<ARGS>(args)...);
        }

        for (const auto& func : na_funcs_)
        {
            func();
        }
    }

};


template<>
class Event<>
{
public:
    using Func = std::function<void()>;

private:
    std::vector<Func> funcs_;

public:
    void add_listener(const Func& func)
    {
        funcs_.push_back(func);
    }

    template<typename T>
    void add_listener(void(T::*func_ptr)(), T* obj)
    {
        funcs_.push_back(detail::make_func(obj, func_ptr));
    }

    void trigger()
    {
        for (const auto& func : funcs_) { func(); }
    }

};


} // namespace bmce


#endif
