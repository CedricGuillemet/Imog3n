#pragma once
#include <vector>
#include "MathTypes.h"

struct ColorRGBA8
{
    uint8_t r,g,b,a;
    Vec4 ToVec4() const
    {
        return {static_cast<float>(r), static_cast<float>(g), static_cast<float>(b), static_cast<float>(a)};
    }
    void FromVec4(const Vec4& v)
    {
        r = static_cast<uint8_t>(v.x);
        g = static_cast<uint8_t>(v.y);
        b = static_cast<uint8_t>(v.z);
        a = static_cast<uint8_t>(v.w);
    }
};

struct GradientEntry
{
    ColorRGBA8 value;
    float key; // 0-1
};

std::vector<ColorRGBA8> Build(const std::vector<GradientEntry>& arr, size_t size)
{
    std::vector<ColorRGBA8> res;

    if (arr.empty())
    {
        res.resize(size, { 0, 0, 0, 0 });
        return res;
    }

    if (arr.size() == 1)
    {
        res.resize(size, arr[0].value);
        return res;
    }
    res.resize(size);

    size_t index = 0;
    for (size_t i = 0; i < arr.size() - 1; i++)
    {
        auto& arr0 = arr[i];
        auto& arr1 = arr[i + 1];

        size_t start = static_cast<size_t>(arr0.key * float(size));
        size_t end = static_cast<size_t>(arr1.key * float(size));
        for (; index < start; index++)
        {
            res[index] = arr0.value;
        }
        for (; index < end; index++)
        {
            auto v0 = arr0.value.ToVec4();
            auto v1 = arr1.value.ToVec4();
            v0.sRGBToLinear();
            v1.sRGBToLinear();
            float t = float(index - start) / float(end - start);
            auto v = Lerp(v0, v1, t);
            v.LinearTosRGB();

            res[index].FromVec4(v);
        }
    }
    for (; index < size; index++)
    {
        res[index] = arr.back().value;
    }
    return res;
}
