package com.frank.ffmpeg;

import android.util.Log;
import android.widget.Toast;

public class FFmpegCmd {

    public interface OnHandleListener{
        void onBegin();
        void onEnd(int result);
    }

    static{
        System.loadLibrary("media-handle");
    }

    //开子线程调用native方法进行音视频处理
    public static void execute(final String[] commands, final OnHandleListener onHandleListener){
        new Thread(new Runnable() {
            @Override
            public void run() {
                if(onHandleListener != null){
                    onHandleListener.onBegin();
                }
                //调用ffmpeg进行处理
                int result = handle(commands, new OnSubProgressListener() {
                    @Override
                    public void onProgressChange(float progress) {
                        Log.v("FFmpegCmd","progress:"+progress);
                    }

                });
                if(onHandleListener != null){
                    onHandleListener.onEnd(result);
                }
            }
        }).start();
    }
    private native static int handle(String[] commands,OnSubProgressListener listener);

    public interface OnSubProgressListener {
        void onProgressChange(float progress);
    }
}