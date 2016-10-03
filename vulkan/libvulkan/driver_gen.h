/*
 * Copyright 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// WARNING: This file is generated. See ../README.md for instructions.

#ifndef LIBVULKAN_DRIVER_GEN_H
#define LIBVULKAN_DRIVER_GEN_H

#include <bitset>
#include <vulkan/vulkan.h>
#include <vulkan/vk_android_native_buffer.h>

namespace vulkan {
namespace driver {

struct ProcHook {
    enum Type {
        GLOBAL,
        INSTANCE,
        DEVICE,
    };
    enum Extension {
        ANDROID_native_buffer,
        EXT_debug_report,
        KHR_android_surface,
        KHR_surface,
        KHR_swapchain,

        EXTENSION_CORE,  // valid bit
        EXTENSION_COUNT,
        EXTENSION_UNKNOWN,
    };

    const char* name;
    Type type;
    Extension extension;

    PFN_vkVoidFunction proc;
    PFN_vkVoidFunction checked_proc;  // always nullptr for non-device hooks
};

struct InstanceDriverTable {
    // clang-format off
    PFN_vkDestroyInstance DestroyInstance;
    PFN_vkEnumeratePhysicalDevices EnumeratePhysicalDevices;
    PFN_vkGetInstanceProcAddr GetInstanceProcAddr;
    PFN_vkCreateDevice CreateDevice;
    PFN_vkEnumerateDeviceExtensionProperties EnumerateDeviceExtensionProperties;
    PFN_vkCreateDebugReportCallbackEXT CreateDebugReportCallbackEXT;
    PFN_vkDestroyDebugReportCallbackEXT DestroyDebugReportCallbackEXT;
    PFN_vkDebugReportMessageEXT DebugReportMessageEXT;
    // clang-format on
};

struct DeviceDriverTable {
    // clang-format off
    PFN_vkGetDeviceProcAddr GetDeviceProcAddr;
    PFN_vkDestroyDevice DestroyDevice;
    PFN_vkGetDeviceQueue GetDeviceQueue;
    PFN_vkCreateImage CreateImage;
    PFN_vkDestroyImage DestroyImage;
    PFN_vkAllocateCommandBuffers AllocateCommandBuffers;
    PFN_vkGetSwapchainGrallocUsageANDROID GetSwapchainGrallocUsageANDROID;
    PFN_vkAcquireImageANDROID AcquireImageANDROID;
    PFN_vkQueueSignalReleaseImageANDROID QueueSignalReleaseImageANDROID;
    PFN_vkGetSwapchainGrallocUsage2ANDROID GetSwapchainGrallocUsage2ANDROID;
    // clang-format on
};

const ProcHook* GetProcHook(const char* name);
ProcHook::Extension GetProcHookExtension(const char* name);

bool InitDriverTable(VkInstance instance,
                     PFN_vkGetInstanceProcAddr get_proc,
                     const std::bitset<ProcHook::EXTENSION_COUNT>& extensions);
bool InitDriverTable(VkDevice dev,
                     PFN_vkGetDeviceProcAddr get_proc,
                     const std::bitset<ProcHook::EXTENSION_COUNT>& extensions);

}  // namespace driver
}  // namespace vulkan

#endif  // LIBVULKAN_DRIVER_TABLE_H
