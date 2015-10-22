#include <jni.h>
#include <android/bitmap.h>
#include "NDKProcesser.h"
#include "com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser.h"

/*
 * Class:     com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser
 * Method:    long createNativeProcesser(void)
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser_createNativeProcesser
  (JNIEnv *env, jobject caller)
{
	Cocoonshu::NDKProcesser* pProcesser = new Cocoonshu::NDKProcesser();
	return (jlong)pProcesser;
}

/*
 * Class:     com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser
 * Method:    void releaseNativeProcesser(long)
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser_releaseNativeProcesser
  (JNIEnv *env, jobject caller, jlong pointer)
{
	Cocoonshu::NDKProcesser* pProcesser = (Cocoonshu::NDKProcesser*)pointer;
	if (pProcesser != 0x00) {
		delete pProcesser;
		pProcesser = 0x00;
	}
}

/*
 * Class:     com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser
 * Method:    java.lang.String getVersion(void)
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser_getVersion
  (JNIEnv *env, jobject caller)
{
	jstring version = env->NewStringUTF("NDKProcesser v1.0");
	return version;
}

/*
 * Class:     com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser
 * Method:    android.graphics.Bitmap grayBitmap(long, android.graphics.Bitmap);
 * Signature: (JLandroid/graphics/Bitmap;)Landroid/graphics/Bitmap;
 */
JNIEXPORT jobject JNICALL Java_com_cocoonshu_example_ndkimageprocesser_nativelayer_NDKProcesser_grayBitmap
  (JNIEnv *env, jobject caller, jlong pointer, jobject javaBitmap)
{
	Cocoonshu::NDKProcesser* pProcesser = (Cocoonshu::NDKProcesser*)pointer;
	if (pProcesser != 0x00) {

		// 获取Bitmap的格式信息
		AndroidBitmapInfo* pBitmapInfo = new AndroidBitmapInfo();
		int result = AndroidBitmap_getInfo(env, javaBitmap, pBitmapInfo);
		switch (result) {
		case ANDROID_BITMAP_RESULT_BAD_PARAMETER:
			delete pBitmapInfo;
			pBitmapInfo = 0x00;
			env->ThrowNew(env->FindClass("java/lang/Exception"), "Bad parameter");
			return 0x00;

		case ANDROID_BITMAP_RESULT_JNI_EXCEPTION:
			delete pBitmapInfo;
			pBitmapInfo = 0x00;
			env->ThrowNew(env->FindClass("java/lang/Exception"), "Jni exception");
			return 0x00;

		case ANDROID_BITMAP_RESULT_ALLOCATION_FAILED:
			delete pBitmapInfo;
			pBitmapInfo = 0x00;
			env->ThrowNew(env->FindClass("java/lang/Exception"), "Allocation failed");
			return 0x00;
		}

		// 获取Bitmap的像素内容
		void* pPixels = 0x00;
		result = AndroidBitmap_lockPixels(env, javaBitmap, &pPixels);
		pProcesser->grayImage(pBitmapInfo, pPixels);
		AndroidBitmap_unlockPixels(env, javaBitmap);

		// 垃圾回收
		pPixels = 0x00;
		delete pBitmapInfo;
		pBitmapInfo = 0x00;
	}
	return javaBitmap;
}
