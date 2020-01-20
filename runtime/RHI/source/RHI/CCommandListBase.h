#pragma once

#include "RHI/ICommandList.h"
#include "CDeviceObjectBase.h"

namespace Wanlix
{
    class CCommandListBase : public CDeviceObjectBase<ICommandList>
    {
    public:

    protected:
        CCommandListBase(IDevice* device, const String& name)
            : CDeviceObjectBase<ICommandList>(device, CommandListDesc(), name)
        {}
    };
}