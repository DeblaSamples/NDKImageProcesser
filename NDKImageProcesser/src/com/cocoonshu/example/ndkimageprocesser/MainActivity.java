
package com.cocoonshu.example.ndkimageprocesser;

import com.cocoonshu.example.ndkimageprocesser.data.DataManager;
import com.cocoonshu.example.ndkimageprocesser.data.NDKGrayLoader;
import com.cocoonshu.example.ndkimageprocesser.data.PictureLoader;
import com.cocoonshu.example.ndkimageprocesser.data.TaskManager;
import com.cocoonshu.example.ndkimageprocesser.nativelayer.NDKProcesser;

import android.net.Uri;
import android.os.Bundle;
import android.widget.ImageView;
import android.app.Activity;
import android.content.Intent;
import android.graphics.Bitmap;

public class MainActivity extends Activity {

    private ImageView mImgPreviewImage     = null;
    private ImageView mImgAfterEffectImage = null;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        setupViews();
        setupListeners();
        initializeFromIntent();
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        DataManager.getInstance().destory();
    }

    private void setupViews() {
        mImgPreviewImage     = (ImageView) findViewById(R.id.ImageViewPreview);
        mImgAfterEffectImage = (ImageView) findViewById(R.id.ImageViewAfterEffect);
    }

    private void setupListeners() {
        // TODO Auto-generated method stub
    }

    private void initializeFromIntent() {
        Intent intent = getIntent();
        String action = intent.getAction();

        if (Intent.ACTION_EDIT.equals(action)) {
            Uri userPhoto = intent.getData();
            PictureLoader loader = new PictureLoader(getApplicationContext(), userPhoto) {
                
                @Override
                protected void onTaskFinished(Object result) {
                    super.onTaskFinished(result);
                    mImgPreviewImage.setImageBitmap((Bitmap)result);
                    DataManager.getInstance().setOrignalBitmap((Bitmap)result);
                    
                    startGrayTask();
                }

            };
            loader.needCallbackInMainThread(true);
            TaskManager.getInstance().sumbitTask(loader);
        }
    }
    
    private void startGrayTask() {
        NDKGrayLoader loader = new NDKGrayLoader(DataManager.getInstance().getOrignalBitmap()) {
            
            @Override
            protected void onTaskFinished(Object result) {
                super.onTaskFinished(result);
                mImgAfterEffectImage.setImageBitmap((Bitmap)result);
            }
            
        };
        loader.needCallbackInMainThread(true);
        TaskManager.getInstance().sumbitTask(loader);
    }
}
