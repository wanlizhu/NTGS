#pragma once

#include "Common.h"

namespace Wanlix
{
    struct ShaderVariableDesc
    {
        Uint shaderStages = ShaderStages::Unknown;
        String name;
        ShaderVariableType type = ShaderVariableType::Static;
    };

    class IShaderVariable : public inherit_shared_from_this<Object, IShaderVariable>
    {
    public:
        virtual ~IShaderVariable() = default;

        virtual void Set(IDeviceObject* object) = 0;
        virtual void SetArray(IDeviceObject** objects, Uint firstElement, Uint elements) = 0;
        virtual ShaderVariableType GetType() const = 0;
        virtual ShaderResourceDesc GetResourceDesc() const = 0;
        virtual Uint GetIndex() const = 0;
        virtual Bool IsBound(Uint arrayIndex) const = 0;
    };
}