#include "Pipes.h"

SliceMesh Pipes::GenerateSliceMesh()
{
    SliceMesh res;

    static const size_t segments = 16;

    res.positions.resize(segments * 2);
    res.normals.resize(segments * 2);
    res.indices.resize(segments * 6);
    for (size_t i = 0; i < segments; i++)
    {
        float ng = (PI * 2.f) / float(segments) * float(i);
        float cs = cosf(ng);
        float sn = sinf(ng);
        res.positions[i + 0] = { cs, sn, 0.f };
        res.positions[i + 1] = { cs, sn, 1.f };

        res.normals[i + 0] = { cs, sn, 0.f };
        res.normals[i + 1] = { cs, sn, 0.f };

        auto& ind = res.indices;
        ind[i * 6 + 0] = static_cast<uint16_t>(i + 0);
        ind[i * 6 + 1] = static_cast<uint16_t>(i + 1);
        ind[i * 6 + 2] = static_cast<uint16_t>(i + 2);

        ind[i * 6 + 3] = static_cast<uint16_t>(i + 1);
        ind[i * 6 + 4] = static_cast<uint16_t>(i + 2);
        ind[i * 6 + 5] = static_cast<uint16_t>(i + 3);
    }

    return res;
}