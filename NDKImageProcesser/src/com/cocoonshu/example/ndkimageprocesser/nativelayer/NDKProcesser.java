package com.cocoonshu.example.ndkimageprocesser.nativelayer;

import android.graphics.Bitmap;

/**
 * 用于管理JNI模块的Java类
 * @author Cocoonshu
 * @date   2015-10-20 13:35:25
 */
public class NDKProcesser {
    
    private static final long NullPointer    = 0x0000;
    private              long mNativePointer = NullPointer;

    static {
        // 用于加载位于libs目录中的libNKDProcesser.so动态库
        // so文件是linux中的动态加载库文件，由C/C++编译而成
        //
        // 如果so文件的命名遵循libXXXXXX.so，则可以使用
        //          System.loadLibrary("XXXXXX");
        // 来加载此库文件；
        // 否则，可以直接使用
        //          System.load("path/libXXXXXX.so");
        // 来加载指定的库文件
        
        System.loadLibrary("NDKProcesser");
    }
    
    public NDKProcesser() {
        // 创建一个Native层的NDKProcesser对象，与此Java对象绑定
        mNativePointer = createNativeProcesser();
    }
    
    /**
     * 销毁NDKProcesser
     * 调用此方法，则代表这个NDKProcesser对象不再会被使用，
     * 因为方法调用了Native层NDKProcesser对象的析构函数，
     * 从内存上释放了这个对象，因此这个对象不再能够被使用
     */
    public void release() {
        if (mNativePointer != NullPointer) {
            // 释放掉Native层的NDKProcesser对象后，Java对象上绑定的
            // Native对象指针也需要赋为空
            releaseNativeProcesser(mNativePointer);
            mNativePointer = NullPointer;
        }
    }
    
    /**
     * 对Bitmap作灰度处理，使之变成黑白的图片
     * 
     * 这里是对native方法的一个封装，因为native方法grayBitmap需要传入nativePointer，
     * 而nativePointer不方便开放给外界，因此我们需要一个封装函数来自己传入敏感参数
     * nativePointer
     * @param bitmap
     * @return
     */
    public final Bitmap gray(Bitmap bitmap) {
        return grayBitmap(mNativePointer, bitmap);
    }
    
    /**
     * 创建一个Native层的Processer对象，并返回其对象的指针
     * 销毁Native层的Processer对象时，请调用releaseNativeProcesser
     * 否则会造成内存泄露
     * 
     * 如果Native层需要使用C++去创建类的对象，并希望Java层NDKProcesser对象能
     * 一直复用它，那么可以做此设计。此时，调用Native层的Processer对象的每一个
     * 函数时，都需要把mNativePointer传入JNI，这样才能在Native上利用这个对象
     * 指针去操作对应的Native层对象
     * 
     * @see #releaseNativeProcesser(long)
     * @return
     */
    private native long createNativeProcesser();
    
    /**
     * 销毁Native层的Processer对象
     * @param nativePointer
     */
    private native void releaseNativeProcesser(long nativePointer);
    
    /**
     * 返回JNI模块中的Version信息
     * 
     * 如果只是Native层返回一些静态信息，而并非Native层中某个对象
     * 特有的信息，则可不必传入mNativePointer去调用对应的Native层
     * 对象
     * 
     * @return 版本字符串
     */
    public native String getVersion();
    
    /**
     * 对Bitmap作灰度处理，使之变成黑白的图片
     * @param bitmap 需要要处理的Bitmap
     * @return 处理后的灰度Bitmap
     */
    private native Bitmap grayBitmap(long nativePointer, Bitmap bitmap);
}
