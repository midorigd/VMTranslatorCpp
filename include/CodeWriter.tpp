template <typename T>
void CodeWriter::commandA(const T& label) {
    writeCommand("@" + processToString(label));
}

template <typename T>
void CodeWriter::constToData(const T& constant) {
    commandA(constant);
    commandC("D", "A");
}

template <typename T>
void CodeWriter::ptrToData(const T& pointer) {
    commandA(pointer);
    memToData();
}

template <typename T>
void CodeWriter::dataToPtr(const T& pointer) {
    commandA(pointer);
    dataToMem();
}

template <typename T>
void CodeWriter::savePointer(const T& pointer) {
    ptrToData(pointer);
    pushD();
}

template <typename T, typename U>
void CodeWriter::copyPointer(const T& src, const U& dest) {
    ptrToData(src);
    dataToPtr(dest);
}

template <typename T>
void CodeWriter::restorePointer(const T& pointer, const int offset) {
    if (processToString(pointer) != RET_ADDR) {
        ptrToData(END_FRAME);
    }

    commandA(offset);
    commandC("A", "D-A");
    memToData();
    dataToPtr(pointer);
}
