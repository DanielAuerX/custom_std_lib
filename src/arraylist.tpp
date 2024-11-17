namespace clib
{

    template <typename T>
    ArrayList<T>::ArrayList(size_t size)
    {
        length = 0;
        capacity = size;
        std::cout << "instantiating new ArrayList" << std::endl;
        std::cout << "current capacity: " << capacity << ", total size in bytes: " << capacity * sizeof(T) << std::endl;
        array = new T[size];
    }

    template <typename T>
    ArrayList<T>::~ArrayList()
    {
        delete[] array;
    }

    template <typename T>
    void ArrayList<T>::push_back(const T &value)
    {
        if (length >= capacity)
        {
            std::cout << "length=" << length << ", capacity=" << capacity << ": not enough space... resizing..." << std::endl;
            resize();
        }
        array[length] = value;
        length++;
    }

    template <typename T>
    void ArrayList<T>::pop_back()
    {
        if (length == 0)
        {
            std::cout << "length=" << length << " : nothing to remove" << std::endl;
            return;
        }
        length--;
        // enough to reduce length because memory section stays allocated and next push_back call will override
        // maybe call desctructor if clean up is needed
        std::cout << "'deleted' last element. new length: " << length << std::endl;
    }

    template <typename T>
    T &ArrayList<T>::operator[](size_t index) const
    {
        if (index >= length)
        { // size_t (therefore index) cannot be negative
            std::cerr << "index " << index << " is out of bounds" << std::endl;
            throw std::out_of_range("index out of bounds");
        }

        return array[index];
    }

    template <typename T>
    size_t ArrayList<T>::size() const
    {
        return length;
    }

    template <typename T>
    void ArrayList<T>::resize()
    {
        capacity = capacity * 2;
        T *resizedArray = new T[capacity];
        for (size_t i = 0; i < length; i++)
        {
            resizedArray[i] = array[i];
        }
        delete[] array; // releases the entire block of memory allocated for the array (calls destructor if applicable)
        array = resizedArray;
        std::cout << "resized: new capacity: " << capacity
                  << ", total size in bytes: " << capacity * sizeof(T) << std::endl;
    }

    template <typename T>
    void ArrayList<T>::merge(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize)
    {
        size_t i = 0, j = 0, k = 0;
        while (i < leftSize && j < rightSize)
        {
            // i < j == aufsteigend ; i > j == absteigend
            if (left[i] < right[j])
            {
                inputArray[k] = left[i];
                i++;
            }
            else
            {
                inputArray[k] = right[j];
                j++;
            }
            k++;
        }
        while (i < leftSize)
        {
            inputArray[k] = left[i];
            i++;
            k++;
        }
        while (j < rightSize)
        {
            inputArray[k] = right[j];
            j++;
            k++;
        }
    }

    template <typename T>
    void ArrayList<T>::merge_sort(T inputArray[], size_t inputLength)
    {
        if (inputLength < 2)
        { // base case
            return;
        }

        // devide
        size_t midIndex = inputLength / 2;
        T *leftHalf = new T[midIndex];
        T *rightHalf = new T[inputLength - midIndex];

        for (size_t i = 0; i < midIndex; i++)
        {
            leftHalf[i] = inputArray[i];
        }
        for (size_t i = midIndex; i < inputLength; i++)
        {
            rightHalf[i - midIndex] = inputArray[i];
        }

        merge_sort(leftHalf, midIndex);
        merge_sort(rightHalf, inputLength - midIndex);

        merge(inputArray, leftHalf, midIndex, rightHalf, inputLength - midIndex);

        delete[] leftHalf;
        delete[] rightHalf;
    }

    template <typename T>
    void ArrayList<T>::sort(){
        // TODO: enum: bubble vs merge
        merge_sort(array, length);
    }

}