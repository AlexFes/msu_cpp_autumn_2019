#pragma once
#include <iostream>

enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
public:
    explicit Serializer(std::stringstream& out)
        : out_(out) {
    }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }

    template <class T>
    void process(T&& value) {
        out_ << Separator << value;
    }

    template <class T, class... Args>
    void process(T&& value, Args&&... args) {
        process(std::forward<Args>(args)...);
    }

    std::stringstream get_result() {
        return out_;
    }

private:
    // process использует variadic templates
    std::stringstream out_;
    static constexpr char Separator = ' ';
};
