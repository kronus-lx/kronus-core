#pragma once

#if __cplusplus < 202002L && (!_MSVC_LANG || _MSVC_LANG < 202002L)
    #error "Compiler does not support C++20 or newer"
#endif

#include <concepts>
#include <string>
#include <vector>
#include <array>
#include <tuple>
#include <map>

namespace types {

    template<typename T>
    struct is_tuple : std::false_type {};
    template<typename... Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

    template<typename T>
    concept PermittedContainerType =
        std::is_same_v<T, std::vector<typename T::value_type, typename T::allocator_type>> ||
        is_tuple<T>::value ||
        std::is_same_v<T, std::map<typename T::key_type, typename T::mapped_type, typename T::key_compare, typename T::allocator_type>> ||
        std::is_same_v<T, std::array<typename T::value_type, T::size()>>;

    template<typename F, typename C>
    concept Callable = requires(F f, C c) {
        { f(c) } -> std::same_as<typename C::value_type>; // Example return type constraint
    };

    template<typename ContainerType, typename CallableType>
        requires PermittedContainerType<ContainerType>&& Callable<CallableType, ContainerType>
    struct Object {
        using Container = ContainerType;
        using Functor = CallableType;

        std::string name;
        Container data;
        Functor operation;

        Object(const std::string& name, ContainerType container, CallableType func)
            : name(name), data(std::move(container)), operation(std::move(func)) {
        }

        auto run() const { return operation(data); }
    };

} // namespace types