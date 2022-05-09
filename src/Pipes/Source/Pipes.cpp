#include "Pipes.h"

Pipe::Pipe()
{
}

bool Pipe::Build(PipeConstraint& constraints)
{
    mControlPoints.reserve(constraints.controlPoints.size() + 2);
    mControlPoints.push_back(constraints.start.Translation());
    for (auto& cp : constraints.controlPoints)
    {
        mControlPoints.push_back(cp);
    }
    mControlPoints.push_back(constraints.end.Translation());

    return true;
}

float Pipe::GetLength(uint16_t precision, std::vector<float>& steps) const
{
    Vec3 p = mControlPoints[0];
    float length = 0.f;
    for (uint16_t i = 0; i < precision; i++)
    {
        float t = float(i + 1) / float(precision);

        Vec3 np = QuadradicBezier(mControlPoints[0], mControlPoints[1], mControlPoints[2], t);
        length += (np - p).Length();
        p = np;
        steps.push_back(length);
    }
    return length;
}


Pipes::Pipes()
{
    mPipes.reserve(1024);
}

Pipe* Pipes::NewPipe()
{
    mPipes.push_back({});
    return &mPipes.back();
}

SliceMesh Pipes::GenerateSliceMesh()
{
    SliceMesh res;

    static const size_t segments = 32;
    const size_t vtsCount = segments * 2;

    res.vertices.resize(segments * 2);
    res.indices.resize(segments * 6);
    
    for (size_t i = 0; i < segments; i++)
    {
        float ng = (PI * 2.f) / float(segments) * float(i);
        float cs = cosf(ng);
        float sn = sinf(ng);
        res.vertices[i * 2 + 0].position = { cs, sn, 0.f };
        res.vertices[i * 2 + 1].position = { cs, sn, 1.f };

        res.vertices[i * 2 + 0].normal = { cs, sn, 0.f };
        res.vertices[i * 2 + 1].normal = { cs, sn, 0.f };

        auto& ind = res.indices;
        ind[i * 6 + 0] = static_cast<uint16_t>(i * 2 + 2) % vtsCount;
        ind[i * 6 + 1] = static_cast<uint16_t>(i * 2 + 1) % vtsCount;
        ind[i * 6 + 2] = static_cast<uint16_t>(i * 2 + 0) % vtsCount;

        ind[i * 6 + 3] = static_cast<uint16_t>(i * 2 + 1) % vtsCount;
        ind[i * 6 + 4] = static_cast<uint16_t>(i * 2 + 2) % vtsCount;
        ind[i * 6 + 5] = static_cast<uint16_t>(i * 2 + 3) % vtsCount;
    }

    return res;
}

float GetInterpolatedT(const std::vector<float>& steps, float desiredLength)
{
    const float stepT = 1.f / float(steps.size());
    float prevStep = 0.f;
    for(size_t i = 0; i < steps.size(); i++)
    {
        if (steps[i] > desiredLength)
        {
            float localT = (desiredLength - prevStep) / (steps[i] - prevStep);
            return (float(i) + localT ) * stepT;
        }
        prevStep = steps[i];
    }
    return 1.f;
}

std::vector<float> Pipes::GetTexture(size_t width) const
{
    std::vector<float> res;
    res.resize(width * width * 4);

    std::vector<float> steps;
    auto& pipe = mPipes[0];
    float length = pipe.GetLength(100, steps);
    Vec3 up{ 0.f, 1.f, 0.f };

    for (size_t i = 0; i < width; i++)
    {
        float desiredLength = float(i) / float(width) * length;
        float t = GetInterpolatedT(steps, desiredLength);

        Vec3 pos = QuadradicBezier(pipe.mControlPoints[0], pipe.mControlPoints[1], pipe.mControlPoints[2], t);
        Vec3 dir = QuadradicBezierDfDt(pipe.mControlPoints[0], pipe.mControlPoints[1], pipe.mControlPoints[2], t);
        dir.Normalize();

        
        
        res[i * 4 + 0] = pos.x;
        res[i * 4 + 1] = pos.y;
        res[i * 4 + 2] = pos.z;
        res[i * 4 + 3] = 0.f;

        res[(i + width) * 4 + 0] = up.x;
        res[(i + width) * 4 + 1] = up.y;
        res[(i + width) * 4 + 2] = up.z;
        res[(i + width) * 4 + 3] = 0.f;

        res[(i + width * 2) * 4 + 0] = dir.x;
        res[(i + width * 2) * 4 + 1] = dir.y;
        res[(i + width * 2) * 4 + 2] = dir.z;
        res[(i + width * 2) * 4 + 3] = 0.f;

        Vec3 right;
        right.Cross(dir, up);
        right.Normalize();
        up.Cross(right, dir);
        up.Normalize();
    }

    return res;
}