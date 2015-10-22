package com.cocoonshu.example.ndkimageprocesser.data;

import java.lang.ref.WeakReference;

import android.graphics.Bitmap;

import com.cocoonshu.example.ndkimageprocesser.data.TaskManager.Loader;
import com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser;


public class NDKGrayLoader extends Loader {

    private WeakReference<Bitmap> mRefBitmap = null;
    
    public NDKGrayLoader(Bitmap bitmap) {
        mRefBitmap = new WeakReference<Bitmap>(bitmap);
    }
    
    @Override
    protected Object doInBackground() {
        Bitmap orignalBitmap = mRefBitmap.get();
        if (orignalBitmap == null) {
            return null;
        }
        
        NDKProcesser processer   = new NDKProcesser();
        Bitmap       afterEffect = DataManager.getInstance().getAffectEffctBitmap();
        if (afterEffect == null) {
            afterEffect = orignalBitmap.copy(orignalBitmap.getConfig(), true);
        }
        processer.gray(afterEffect);
        DataManager.getInstance().setAffectEffctBitmap(afterEffect);
        
        return afterEffect;
    }

    @Override
    protected void onTaskFinished(Object result) {
        if (mRefBitmap != null) {
            mRefBitmap.clear();
            mRefBitmap = null;
        }
    }
    
}
