template <typename T>
T Parser::arg1() const {
    if constexpr (std::is_same_v<T, OP>) {
        return opLookup.at(current[0]);
    } else if constexpr (std::is_same_v<T, SEGMENT>) {
        return segmentLookup.at(current[1]);
    } else {
        return current[1];
    }
}
