#pragma once

#include <algorithm>
#include <cstring>

namespace Rendering
{
    template<typename T, int channels>
    class PixelMap
    {
    public:
        explicit PixelMap() = default;
        explicit PixelMap(int x, int y);
        explicit PixelMap(int x, int y, const T* source);
        ~PixelMap();

        explicit PixelMap(const PixelMap&);
        PixelMap& operator=(const PixelMap&);
        
        T GetPixel(int x, int y, int channel = 0);
        void SetPixel(int x, int y, T value, int channel = 0);
        void Fill(T value);

        T* GetArray() { return array; }

    private:
        int xSize;
        int ySize;
        T* array;

        int IndexOf(int x, int y, int channel);
        int GetModulo(int value, int modulo);
    };

    template<typename T, int channels>
    PixelMap<T, channels>::PixelMap(int x, int y)
    {
        xSize = x;
        ySize = y;

        array = new T[x * y * channels];
    }

    template<typename T, int channels>
    PixelMap<T, channels>::PixelMap(int x, int y, const T* source) : PixelMap(x, y)
    {
        memcpy(array, source, x * y * channels * sizeof(T));
    }

    template<typename T, int channels>
    T PixelMap<T, channels>::GetPixel(int x, int y, int channel)
    {
        return array[IndexOf(x, y, channel)];
    }

    template<typename T, int channels>
    void PixelMap<T, channels>::SetPixel(int x, int y, T value, int channel)
    {
        array[IndexOf(x, y, channel)] = value;
    }

    template<typename T, int channels>
    void PixelMap<T, channels>::Fill(T value)
    {
        std::fill(array, array + xSize * ySize * channels, value);
    }

    template<typename T, int channels>
    int PixelMap<T, channels>::GetModulo(int value, int modulo)
    {
        return ((value % modulo) + modulo) % modulo;
    }

    template<typename T, int channels>
    int PixelMap<T, channels>::IndexOf(int x, int y, int channel)
    {
        return (GetModulo(x, xSize) + GetModulo(y, ySize) * xSize) * channels + channel;
    }

    template<typename T, int channels>
    PixelMap<T, channels>::PixelMap(const PixelMap& other)
    {
        xSize = other.xSize;
        ySize = other.ySize;

        array = new T[xSize * ySize * channels];
        memcpy(array, other.array, xSize * ySize * channels * sizeof(T));
    }

    template<typename T, int channels>
    PixelMap<T, channels>& PixelMap<T, channels>::operator=(const PixelMap& other)
    {
        xSize = other.xSize;
        ySize = other.ySize;

        array = new T[xSize * ySize * channels];
        memcpy(array, other.array, xSize * ySize * channels * sizeof(T));

        return *this;
    }

    template<typename T, int channels>
    PixelMap<T, channels>::~PixelMap()
    {
        delete[] array;
    }
}