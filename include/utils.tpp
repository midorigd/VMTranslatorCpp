template <typename T>
std::string processToString(const T& data) {
    if constexpr (std::is_same_v<T, std::string>) {
        return data;
    } else if constexpr (std::is_array_v<T> && std::is_same_v<typename std::remove_extent<T>::type, char>) {
        return std::string(data);
    } else if constexpr (std::is_same_v<T, int>) {
        return std::to_string(data);
    } else if constexpr (std::is_same_v<T, SEGMENT>) {
        return +data;
    } else {
        std::cerr << "Cannot convert type " << typeid(T).name() << " to string\n";
        exit(5);
    }
}
