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


		BoundingBox ComputeWorldBoundingBox() const
		{
			BoundingBox res{ { FLT_MAX, FLT_MAX, FLT_MAX }, { -FLT_MAX, -FLT_MAX, -FLT_MAX } };

			for (int i = 0;i<8;i++)
			{
				Vec3 p{i&1?-1.f:1.f, i&2?-1.f:1.f, i&4?-1.f:1.f};
				p.TransformPoint(mMatrix);
				res.Insert(p);
			}
			return res;
		}
	};

	class PrimBatch
	{
	public:
		PrimBatch()
		{
			mPrims.push_back({ Mat4x4::TranslationMatrix({0.f,1.f,0.f}), 0.1f });
			mPrims.push_back({ Mat4x4::ScaleMatrix({0.5f,1.5f,0.5f}).Translate({5.f,2.f,0.f}), 0.5f });
			mPrims.push_back({ Mat4x4::TranslationMatrix({10.f,0.f,0.f}), 1.f });
			
		}

		BoundingBox ComputeWorldBoundingBox() const
		{
			BoundingBox boundingBox({ FLT_MAX }, { -FLT_MAX });
			for (const auto& prim : mPrims)
			{
				boundingBox.Insert(prim.ComputeWorldBoundingBox());
			}
			boundingBox.MakeCubic();
			boundingBox.Expand(0.1f);
			return boundingBox;
		}

		void AddPrimitive(const Vec3& position)
		{
			mPrims.push_back({ Mat4x4::TranslationMatrix(position), 0.f });
		}

		const std::vector<Prim>& GetPrims() const { return mPrims; }
	private:

		std::vector<Prim> mPrims{};
	};

} // namespace