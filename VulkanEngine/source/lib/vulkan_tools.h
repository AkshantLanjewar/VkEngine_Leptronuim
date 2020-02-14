#pragma once

#include <vulkan/vulkan.h>
#include "vk_initializers.hpp"

#include <math.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#include <fstream>
#include <assert.h>
#include <stdio.h>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#if defined(_WIN32)
#include <windows.h>
#include <fcntl.h>
#include <io.h>
#include <tchar.h>
#endif

#define VK_FLAGS_NONE 0
#define DEFAULT_FENCE_TIMEOUT 100000000000

#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << vk_engine::tools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}

#define ASSET_PATH "./data/"

namespace vk_engine
{
	namespace tools
	{
		//disables message box on errors
		extern bool errorModeSilent;

		//returns error code as string
		std::string errorString(VkResult errorCode);

		//returns the device type as a string
		std::string physicalDeviceTypeString(VkPhysicalDeviceType type);

		//Selected a suitable supported depth format starting with 32 bit down to 16 bit
		//returns false if none of the depth formats are supported by the list
		VkBool32 getSupportedDepthFormat(VkPhysicalDevice physicalDevice, VkFormat* depthFormat);

		// put an image memory barrier for setting an image layouton the sub resource in the command buffer
		void setImageLayout(
			VkCommandBuffer cmdBuffer,
			VkImage image,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkImageSubresourceRange subresourceRange,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT);

		//uses a fixed sub resource layout with first mip level and layer
		void setImageLayout(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkImageAspectFlags aspectMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,
			VkPipelineStageFlags dstStageMask = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT
		);

		//insert image memory barrier into the command buffer
		void insertImageMemoryBarrier(
			VkCommandBuffer cmdbuffer,
			VkImage image,
			VkAccessFlags srcAccessMask,
			VkAccessFlags dstAccessMask,
			VkImageLayout oldImageLayout,
			VkImageLayout newImageLayout,
			VkPipelineStageFlags srcStageMask,
			VkPipelineStageFlags dstStageMask,
			VkImageSubresourceRange subresourceRange
		);

		//display error message on exit on fatal error
		void exitFatal(std::string message, int32_t exitCode);
		void exitFatal(std::string message, VkResult resultCode);

		//load spir-v shader 
		VkShaderModule loadShader(const char* fileName, VkDevice device);

		//check if file exists
		bool fileExists(const std::string& filename);
	}
}