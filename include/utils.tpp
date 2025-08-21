template <typename T>
string processToString(const T& data) {
    if constexpr (is_same_v<T, string>) {
        return data;
    } else if constexpr (is_array_v<T> && is_same_v<typename remove_extent<T>::type, char>) {
        return string(data);
    } else if constexpr (is_same_v<T, int>) {
        return to_string(data);
    } else if constexpr (is_same_v<T, SEGMENT>) {
        return +data;
    } else {
        cerr << "Cannot convert type " << typeid(T).name() << " to string\n";
        exit(5);
    }
}
