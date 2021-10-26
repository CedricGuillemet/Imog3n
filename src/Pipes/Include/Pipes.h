#pragma once
#include <stdint.h>
#include <vector>
#include "MathTypes.h"


struct PipeConstraint
{
    Mat4x4 start;
    Mat4x4 end;
    float radius;
    uint16_t controlPointCount;
};

class Pipe
{
public:
    // return true if able to build pipe with constraints
    bool Build(PipeConstraint& constraints);

    /*
    control points -> length discretization
    */
    /*
    want : 
    - autocurve from A to B
    - control pt tweaking(gizmo)
    - segment length tweak
    - noise position
    - realtime
    */

    /*
    matrix start/end
    autocurve (max angular
    controlPt count
    segment length
    verlet iteration count
    */
    const std::vector<Vec3>& GetControlPoints() const { return mControlPoints; }
private:
    Pipe();
    friend class Pipes;
    std::vector<Vec3> mControlPoints;
};

struct SliceMesh
{
    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    std::vector<uint16_t> indices;
};

class Pipes
{
public:
    Pipes();

    Pipe* NewPipe();
    std::vector<float> GetTexture(size_t width) const;
    SliceMesh GenerateSliceMesh();
private:

    std::vector<Pipe> mPipes;
};