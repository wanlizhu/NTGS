#pragma once

#include "RHI/IBuffer.h"
#include "RHI/CDeviceObjectBase.h"

namespace Wanlix
{
    class CBufferBase : public CDeviceObjectBase<IBuffer>
    {
    public:
        virtual SharedPtr<IBufferView> CreateView(const BufferViewDesc& desc) override;
        virtual SharedPtr<IBufferView> GetDefaultView(EBufferViewType type) override;
        virtual void SetState(EResourceState state) override final { mResourceState = state; }
        virtual EResourceState GetState() const override final { return mResourceState; }
        
        inline Bool IsInKnownState() const { return mResourceState != EResourceState::Unknown; }
        inline Bool CheckState(EResourceState state) const;

    protected:
        CBufferBase(IDevice* device,
                    const BufferDesc& desc,
                    const String& name)
            : CDeviceObjectBase<IBuffer>(device, desc, name)
        {}

        virtual SharedPtr<IBufferView> CreateViewInternal(const BufferViewDesc& viewDesc, Bool isDefault) = 0;
        void AdjustBufferViewDesc(BufferViewDesc& desc) const;

    protected:
        EResourceState mResourceState = EResourceState::Unknown;
        SharedPtr<IBufferView> mDefaultUAV;
        SharedPtr<IBufferView> mDefaultSRV;
    };
}