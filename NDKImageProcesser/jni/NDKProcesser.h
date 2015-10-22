/*
 * NDKProcesser.h
 *
 *  Created on: 2015年10月21日
 *      Author: Cocoonshu@Plf.MediaCenter.Gallery
 */

#ifndef NDKPROCESSER_H_
#define NDKPROCESSER_H_
#include <android/bitmap.h>

namespace Cocoonshu {

#define RGB2GRAY(red, green, blue)            ((77 * red + 150 * green + 29 * blue + 128) >> 8);
#define MIX2RGBA8888(red, green, blue, alpha) (((alpha << 24) & 0xFF000000) \
		                                     | ((red   << 16) & 0x00FF0000) \
		                                     | ((green << 8 ) & 0x0000FF00) \
		                                     | ((blue  << 0 ) & 0x000000FF));
#define MIX2RGBA4444(red, green, blue, alpha) (((alpha << 12) & 0x0000F000) \
											 | ((red   << 8 ) & 0x00000F00) \
											 | ((green << 4 ) & 0x000000F0) \
											 | ((blue  << 0 ) & 0x0000000F));
#define MIX2RGB565(red, green, blue)          (((red   << 11) & 0x0000F800) \
											 | ((green << 5 ) & 0x000007E0) \
											 | ((blue  << 0 ) & 0x0000001F));

class NDKProcesser {
public:
	NDKProcesser();
	virtual ~NDKProcesser();

	void grayImage(const AndroidBitmapInfo* pInfo, const void* pPixels);
};

} /* namespace Cocoonshu */

#endif /* NDKPROCESSER_H_ */
