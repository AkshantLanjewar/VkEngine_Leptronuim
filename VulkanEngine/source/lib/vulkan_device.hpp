#pragma once
#include <exception>
#include <assert.h>
#include <algorithm>

#include <vulkan/vulkan.h>
#include "vulkan_tools.h"
#include "vulkan_buffer.hpp"

namespace vk_engine
{
	struct VulkanDevice
	{
		VkPhysicalDevice physicalDevice;
		//logical device (applications view of the device)
		VkDevice logicalDevice;
		//properties of the physcial device including limits
		VkPhysicalDeviceProperties properties;
		//features of the physical device that an application use
		VkPhysicalDeviceFeatures features;
		//features that have been enabled
		VkPhysicalDeviceFeatures enabledFeatures;
		//memory types and heaps of the physical device
		VkPhysicalDeviceMemoryProperties memoryProperties;
		//queue family properties of the physical device
		std::vector<VkQueueFamilyProperties> queueFamilyProperties;
		//list of extensions supported by the device
		std::vector<std::string> supportedExtensions;

		//default command pool for the graphics queue family index
		VkCommandPool commandPool = VK_NULL_HANDLE;

		//set to true when debug marker is enabled
		bool enableDebugMarker = false;

		//contains queue family indicies
		struct
		{
			uint32_t graphics;
			uint32_t compute;
			uint32_t transfer;
		}queueFamilyIndicies;

		//typecast to vk device
		operator VkDevice() { return logicalDevice; };

		//default constructor
		VulkanDevice(VkPhysicalDevice physicalDevice)
		{
			assert(physicalDevice);
			this->physicalDevice = physicalDevice;

			// Store Properties features, limits and properties of the physical device for later use
			// Device properties also contain limits and sparse properties
			vkGetPhysicalDeviceProperties(physicalDevice, &properties);
			//features should be checked by the program
			vkGetPhysicalDeviceFeatures(physicalDevice, &features);
			//memory properties are used for creating all kinds of buffers
			vkGetPhysicalDeviceMemoryProperties(physicalDevice, &memoryProperties);
			//Queue family properties used for setting up requested queues on device creation
			uint32_t queueFamilyCount;
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);
			queueFamilyProperties.resize(queueFamilyCount);
			vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilyProperties.data());

			//get list of supported extensions

		}
	};
}