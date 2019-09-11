#pragma once

#include "IResource.h"

namespace ZHU
{
	enum class EAccessFlags
	{
		None,
		Read,
		Write,
		ReadWrite,
	};

	enum class EMapType
	{
		Read,
		Write,
		WriteDiscard,
	};

	class IBuffer : public IResource
	{
	public:
		virtual ~IBuffer() = 0;
		virtual void UpdateData(size_t offset, size_t size, const void* data) = 0;
		virtual size_t GetSize() const = 0;

		virtual void* Map(EMapType type) = 0;
		virtual void UnMap() = 0;
	};
}