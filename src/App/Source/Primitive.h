#pragma once
#include "MathTypes.h"

#include <vector>

namespace Imog3n {

	struct PrimType
	{
		enum Enum
		{
			Box,
			Sphere,
			Cylinder,
			Cone,
			Torus,
			Prism,
			Pyramid,
			Spline,

			Count
		};
	};

	struct UnionType
	{
		enum Enum
		{
			Add,
			Sub,

			Count
		};
	};

	struct Prim
	{

		Mat4x4 mMatrix{ Identity };
		float mBlendFactor{};

		PrimType::Enum mType{ PrimType::Sphere };
		UnionType::Enum mUnion{ UnionType::Add };


		BoundingBox ComputeBoundingBox() const
		{
			return BoundingBox({ -1.f }, { 1.f });
		}
	};

	class PrimBatch
	{
	public:
		PrimBatch()
		{
		}

		BoundingBox ComputeBoundingBox() const
		{
			BoundingBox boundingBox({ FLT_MAX }, { -FLT_MAX });
			for (const auto& prim : mPrims)
			{
				boundingBox.Insert(prim.ComputeBoundingBox());
			}
			boundingBox.MakeCubic();
			boundingBox.Expand(0.01f);
			return boundingBox;
		}

		const std::vector<Prim>& GetPrims() const { return mPrims; }
	private:

		std::vector<Prim> mPrims{
			{}
		};
	};

} // namespace