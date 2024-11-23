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
    void ArrayList<T>::mergeAsc(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize)
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
    void ArrayList<T>::mergeDesc(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize)
    {
        size_t i = 0, j = 0, k = 0;
        while (i < leftSize && j < rightSize)
        {
            // i < j == aufsteigend ; i > j == absteigend
            if (left[i] > right[j])
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
    void ArrayList<T>::merge_sort(T inputArray[], size_t inputLength, const Order &order)
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

        merge_sort(leftHalf, midIndex, order);
        merge_sort(rightHalf, inputLength - midIndex, order);

        if (order == ASC)
        {
            mergeAsc(inputArray, leftHalf, midIndex, rightHalf, inputLength - midIndex);
        }
        else
        {
            mergeDesc(inputArray, leftHalf, midIndex, rightHalf, inputLength - midIndex);
        }

        delete[] leftHalf;
        delete[] rightHalf;
    }

    template <typename T>
    void ArrayList<T>::bubble_sort(T inputArray[], const size_t &inputLength, const Order &order)
    {
        for (size_t i = 0; i < inputLength - 1; i++)
        {
            for (size_t j = 0; j < inputLength - 1 - i; j++)
            {
                if (isBigger(inputArray[j], inputArray[j + 1], order))
                {
                    T temp = inputArray[j];
                    inputArray[j] = inputArray[j + 1];
                    inputArray[j + 1] = temp;
                }
            }
        }
    }

    template <typename T>
    bool ArrayList<T>::isBigger(const T x, const T y, const Order &order)
    {
        if (order == ASC)
        {
            return x > y;
        }
        else
        {
            return x < y;
        }
    }

    template <typename T>
    int ArrayList<T>::binary_search(const T sortedInputArray[], const size_t &inputLength, const T &target)
    {
        // TODO: dont use copy of sortedInputArray?
        // add to header
        size_t low = 0;
        size_t high = inputLength - 1;
        size_t mid;
        while (low <= high)
        {
            mid = low + (high - low) / 2;
            if (sortedInputArray[mid] == target)
            {
                return mid;
            }
            else if (sortedInputArray[mid] < target)
            {
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }
        return -1;
    }

    template <typename T>
    bool ArrayList<T>::contains(const T &value)
    {
        // TODO: better algorithms for contains?
        T *tempArray = new T[length];
        for (size_t i = 0; i < length; ++i)
        {
            tempArray[i] = array[i];
        }

        // TODO: sort once outside this function for repeated use.
        merge_sort(tempArray, length, Order::ASC);

        if (binary_search(tempArray, length, value) < 0)
        {
            delete[] tempArray;
            return false;
        }
        delete[] tempArray;
        return true;
    }

    template <typename T>
    void ArrayList<T>::sort()
    {
        // TODO use isBigger in merge sort
        merge_sort(array, length, Order::ASC);
    }

    template <typename T>
    void ArrayList<T>::sort(const Order &order, const SortType &sortType)
    {
        if (sortType == MERGE_SORT)
        {
            merge_sort(array, length, order);
        }
        else
        {
            bubble_sort(array, length, order);
        }
    }

}