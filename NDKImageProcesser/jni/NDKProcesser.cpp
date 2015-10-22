/*
 * NDKProcesser.cpp
 *
 *  Created on: 2015年10月21日
 *      Author: Cocoonshu@Plf.MediaCenter.Gallery
 */

#include "NDKProcesser.h"
#include "Log.h"
#include <time.h>

namespace Cocoonshu {

NDKProcesser::NDKProcesser() {
	// Initialize members
}

NDKProcesser::~NDKProcesser() {
	// release members
}

void NDKProcesser::grayImage(const AndroidBitmapInfo* pInfo, const void* pPixels) {
    if (pInfo == 0x00 || pPixels == 0x00) {
    	return;
    }
    uint32_t startTime = clock();
    Log_i("[NDKProcesser][grayImage] Start graying bitmap");

    if (pInfo->format == ANDROID_BITMAP_FORMAT_RGBA_8888) {
    	Log_i("[NDKProcesser][grayImage] Bitmap format = RGBA_8888");

    	uint32_t  widthSize  = pInfo->width;
    	uint32_t  heightSize = pInfo->height;
    	uint32_t  strideSize = pInfo->stride;
    	uint32_t* pPixelPtr  = (uint32_t*)pPixels;
    	Log_i("[NDKProcesser][grayImage] Bitmap size = (%d, %d), stride = %d", widthSize, heightSize, strideSize);

    	for (uint32_t height = 0; height < heightSize; height++) {
    		for (uint32_t width = 0; width < widthSize; width++) {
    			uint8_t  alpha = ((*pPixelPtr) & 0xFF000000) >> 24;
    			uint8_t  red   = ((*pPixelPtr) & 0x00FF0000) >> 16;
    			uint8_t  green = ((*pPixelPtr) & 0x0000FF00) >> 8;
    			uint8_t  blue  = ((*pPixelPtr) & 0x000000FF) >> 0;
    			uint8_t  gray  = RGB2GRAY(red, green, blue);
    			*pPixelPtr = MIX2RGBA8888(gray, gray, gray, alpha);
    			pPixelPtr++;
    		}
    	}
    } else if (pInfo->format == ANDROID_BITMAP_FORMAT_RGB_565) {
    	Log_i("[NDKProcesser][grayImage] Bitmap format = RGB_565");

    	uint32_t  widthSize  = pInfo->width;
    	uint32_t  heightSize = pInfo->height;
    	uint32_t  strideSize = pInfo->stride;
    	uint16_t* pPixelPtr  = (uint16_t*)pPixels;
    	Log_i("[NDKProcesser][grayImage] Bitmap size = (%d, %d), stride = %d", widthSize, heightSize, strideSize);

    	for (uint32_t height = 0; height < heightSize; height++) {
    		for (uint32_t width = 0; width < widthSize; width++) {
    			uint8_t  red   = ((*pPixelPtr) & 0xF800) >> 11;
    			uint8_t  green = ((*pPixelPtr) & 0x07E0) >> 5;
    			uint8_t  blue  = ((*pPixelPtr) & 0x001F) >> 0;
    			uint8_t  gray  = RGB2GRAY(red, green, blue);
    			*pPixelPtr = MIX2RGB565(gray, gray, gray);
    			pPixelPtr++;
    		}
    	}
    } else if (pInfo->format == ANDROID_BITMAP_FORMAT_RGBA_4444) {
    	Log_i("[NDKProcesser][grayImage] Bitmap format = RGBA_4444");

    	uint32_t  widthSize  = pInfo->width;
    	uint32_t  heightSize = pInfo->height;
    	uint32_t  strideSize = pInfo->stride;
    	uint16_t* pPixelPtr  = (uint16_t*)pPixels;
    	Log_i("[NDKProcesser][grayImage] Bitmap size = (%d, %d), stride = %d", widthSize, heightSize, strideSize);

    	for (uint32_t height = 0; height < heightSize; height++) {
    		for (uint32_t width = 0; width < widthSize; width++) {
    			uint8_t  alpha = ((*pPixelPtr) & 0xF000) >> 12;
    			uint8_t  red   = ((*pPixelPtr) & 0x0F00) >> 8;
    			uint8_t  green = ((*pPixelPtr) & 0x00F0) >> 4;
    			uint8_t  blue  = ((*pPixelPtr) & 0x000F) >> 0;
    			uint8_t  gray  = RGB2GRAY(red, green, blue);
    			*pPixelPtr = MIX2RGBA4444(gray, gray, gray, alpha);
    			pPixelPtr++;
    		}
    	}
    }

    uint32_t endTime = clock();
    Log_i("[NDKProcesser][grayImage] Finish graying bitmap, duration %ldms",
    		                         ((endTime - startTime) / 1000L));
}

} /* namespace Cocoonshu */
