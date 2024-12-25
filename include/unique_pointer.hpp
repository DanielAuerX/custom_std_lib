#pragma once
#include <utility>

namespace clib
{

    template <typename T>
    class UniquePtr
    {
    private:
        T *mPointer;
        clib::Log &mLogger = Log::get_instance();

    public:
        // cannot be used for implicit conversions
        explicit UniquePtr(T *aPointer = nullptr);

        ~UniquePtr();

        //&& rvalue reference
        // noexcept: does not throw exception
        UniquePtr(UniquePtr &&other) noexcept;
        UniquePtr &operator=(UniquePtr &&other) noexcept;

        // ensures unique ownership
        UniquePtr(const UniquePtr &) = delete;
        UniquePtr &operator=(const UniquePtr &) = delete;

        T *get() const;

        // accesses object
        T &operator*() const;

        // access  members of the object
        T *operator->() const;

        // convert back to raw pointer ("release" ownership)
        T *release();

        // set held pointer to new one or to null pointer
        void reset(T *aPointer = nullptr);
    };

} // namespace ende

#include "../src/unique_pointer.tpp"