/*
 * Copyright 2015 The Android Open Source Project
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

#ifndef __VK_ANDROID_NATIVE_BUFFER_H__
#define __VK_ANDROID_NATIVE_BUFFER_H__

#include <system/window.h>
#include <vulkan/vulkan.h>

#ifdef __cplusplus
extern "C" {
#endif

#define VK_ANDROID_native_buffer 1

#define VK_ANDROID_NATIVE_BUFFER_EXTENSION_NUMBER 11
#define VK_ANDROID_NATIVE_BUFFER_SPEC_VERSION     6
#define VK_ANDROID_NATIVE_BUFFER_EXTENSION_NAME   "VK_ANDROID_native_buffer"

#define VK_ANDROID_NATIVE_BUFFER_ENUM(type,id)    ((type)(1000000000 + (1000 * (VK_ANDROID_NATIVE_BUFFER_EXTENSION_NUMBER - 1)) + (id)))
#define VK_STRUCTURE_TYPE_NATIVE_BUFFER_ANDROID   VK_ANDROID_NATIVE_BUFFER_ENUM(VkStructureType, 0)

/* NOTE ON VK_ANDROID_NATIVE_BUFFER_SPEC_VERSION 6
 *
 * This version of the extension transitions from gralloc0 to gralloc1 usage
 * flags (int -> 2x uint64_t). The WSI implementation will temporarily continue
 * to fill out deprecated fields in VkNativeBufferANDROID, and will call the
 * deprecated vkGetSwapchainGrallocUsageANDROID if the new
 * vkGetSwapchainGrallocUsage2ANDROID is not supported. This transitionary
 * backwards-compatibility support is temporary, and will likely be removed in
 * (along with all gralloc0 support) in a future release.
 */

typedef struct {
    VkStructureType             sType; // must be VK_STRUCTURE_TYPE_NATIVE_BUFFER_ANDROID
    const void*                 pNext;

    // Buffer handle and stride returned from gralloc alloc()
    buffer_handle_t             handle;
    int                         stride;

    // Gralloc format and usage requested when the buffer was allocated.
    int                         format;
    int                         usage;  // DEPRECATED in SPEC_VERSION 6
    // -- Added in SPEC_VERSION 6 --
    struct {
        uint64_t                consumer;
        uint64_t                producer;
    } usage2;
} VkNativeBufferANDROID;


// -- DEPRECATED in SPEC_VERSION 6 --
typedef VkResult (VKAPI_PTR *PFN_vkGetSwapchainGrallocUsageANDROID)(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, int* grallocUsage);

typedef VkResult (VKAPI_PTR *PFN_vkAcquireImageANDROID)(VkDevice device, VkImage image, int nativeFenceFd, VkSemaphore semaphore, VkFence fence);
typedef VkResult (VKAPI_PTR *PFN_vkQueueSignalReleaseImageANDROID)(VkQueue queue, uint32_t waitSemaphoreCount, const VkSemaphore* pWaitSemaphores, VkImage image, int* pNativeFenceFd);

// -- ADDED in SPEC_VERSION 6 --
typedef VkResult (VKAPI_PTR *PFN_vkGetSwapchainGrallocUsage2ANDROID)(VkDevice device, VkFormat format, VkImageUsageFlags imageUsage, uint64_t* grallocConsumerUsage, uint64_t* grallocProducerUsage);

#ifndef VK_NO_PROTOTYPES

// -- DEPRECATED in SPEC_VERSION 6 --
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainGrallocUsageANDROID(
    VkDevice            device,
    VkFormat            format,
    VkImageUsageFlags   imageUsage,
    int*                grallocUsage
);
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireImageANDROID(
    VkDevice            device,
    VkImage             image,
    int                 nativeFenceFd,
    VkSemaphore         semaphore,
    VkFence             fence
);
VKAPI_ATTR VkResult VKAPI_CALL vkQueueSignalReleaseImageANDROID(
    VkQueue             queue,
    uint32_t            waitSemaphoreCount,
    const VkSemaphore*  pWaitSemaphores,
    VkImage             image,
    int*                pNativeFenceFd
);
// -- ADDED in SPEC_VERSION 6 --
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainGrallocUsage2ANDROID(
    VkDevice            device,
    VkFormat            format,
    VkImageUsageFlags   imageUsage,
    uint64_t*           grallocConsumerUsage,
    uint64_t*           grallocProducerUsage
);
#endif

#ifdef __cplusplus
}
#endif

#endif // __VK_ANDROID_NATIVE_BUFFER_H__
