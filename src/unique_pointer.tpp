#include "../include/unique_pointer.hpp"
#include "../include/logging.hpp"

namespace clib
{

    template <typename T>
    UniquePtr<T>::UniquePtr(T *aPointer) : mPointer(aPointer)
    {
        mLogger.log(LogLevel::INFO, "constructed UniquePtr");
    }

    template <typename T>
    UniquePtr<T>::~UniquePtr()
    {
        mLogger.log(LogLevel::INFO, "deleting UniquePtr");
        delete mPointer;
    }

    template <typename T>
    T *UniquePtr<T>::get() const
    {
        return mPointer;
    }

    template <typename T>
    T &UniquePtr<T>::operator*() const
    {
        return *mPointer;
    }

    template <typename T>
    T *UniquePtr<T>::operator->() const
    {
        return mPointer;
    }

    template <typename T>
    T *UniquePtr<T>::release()
    {
        T *temp = mPointer;
        mPointer = nullptr;
        return temp;
    }

    template <typename T>
    void UniquePtr<T>::reset(T *aPointer)
    {
        delete mPointer;
        mPointer = aPointer;
    }

    template <typename T>
    UniquePtr<T>::UniquePtr(UniquePtr &&other) noexcept : mPointer(other.mPointer)
    {
        other.mPointer = nullptr;
    }

    template <typename T>
    UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr &&other) noexcept
    {
        if (this != &other)
        {
            delete mPointer;
            mPointer = other.mPointer;
            other.mPointer = nullptr;
        }
        return *this;
    }

}