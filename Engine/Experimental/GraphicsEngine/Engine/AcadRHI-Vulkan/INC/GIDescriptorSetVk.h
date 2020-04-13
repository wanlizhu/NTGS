#pragma once

#include "GIDeviceObjectVk.h"

namespace AutoCAD::Graphics::Engine
{
    class GIDescriptorSetLayoutVk;
    class GIDescriptorPoolVk;
    class GIResourceVk;
    class GICommandBufferVk;

    class GIDescriptorSetVk : public GIDeviceObjectVk
    {
        DECL_DEVICE_OBJECT(GIDescriptorSetVk)
    public:
        static SharedPtr<GIDescriptorSetVk> Create(
            SharedPtr<GIDescriptorPoolVk> pool,
            SharedPtr<GIDescriptorSetLayoutVk> setLayout,
            SharedPtr<GIDescriptorSetVk> parent
        );

        virtual ~GIDescriptorSetVk();
        virtual bool IsValid() const override final;
        virtual void SetDebugName(const char* name) const override final;
        virtual void SetDebugTag(const DebugTag& tag) const override final;

        operator const VkDescriptorSet& () const;
        bool IsPushDescriptorSet() const;
        SharedPtr<GIDescriptorSetLayoutVk> GetDescriptorSetLayout() const;
        
        void BindResource(const char* name, WeakPtr<GIResourceVk> resource, SharedPtr<GICommandBufferVk> cmdbuf = nullptr);
        void BindResourceArray(const char* name, const std::vector<WeakPtr<GIResourceVk>>& resourceArray, SharedPtr<GICommandBufferVk> cmdbuf = nullptr);
        void Update(SharedPtr<GICommandBufferVk> cmdbuf = nullptr);

    private:
        GIDescriptorSetVk(SharedPtr<GIDeviceVk> device);

    private:
        VkDescriptorSet mDescriptorSetHandle = VK_NULL_HANDLE; // Must be NULL for push-descriptor-set
        SharedPtr<GIDescriptorSetLayoutVk> mDescriptorSetLayout;
        WeakPtr<GIDescriptorPoolVk> mDescriptorPool;
        
        std::unordered_map<std::string, WeakPtr<GIResourceVk>> mBoundResources;
        std::unordered_map<std::string, std::vector<WeakPtr<GIResourceVk>>> mBoundResourceArrays;
        std::vector<VkWriteDescriptorSet> mPendingUpdates;
    };
}