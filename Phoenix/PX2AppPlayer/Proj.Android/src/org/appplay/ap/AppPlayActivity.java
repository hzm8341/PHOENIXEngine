package org.appplay.ap;

import java.util.List;

import org.appplay.lib.AppPlayBaseActivity;
import org.appplay.lib.AppPlayMetaData;
import org.appplay.platformsdk.PlatformSDK;
import org.appplay.platformsdk.PlatformSDKCreater;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.ActivityManager;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.content.Context;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;

public class AppPlayActivity extends AppPlayBaseActivity
{	
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
		// super create     	
        super.onCreate(savedInstanceState);
    }
    
    @Override
	protected void onPause() 
    {  
    	Log.d("appplay.ap", "AppPlayActivity::onPause");
		 
	    super.onPause();
    }

	 @Override
	 protected void onResume() 
	 {	 
		 super.onResume();
	 }
	 
    static {
    	String TAG = "appplay.ap";
    	/*
    	
    	Log.d("appplay.ap", "build.version.sdk:"+Build.VERSION.SDK_INT);
    	
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.GINGERBREAD_MR1) 
        {
            try {
                if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.HONEYCOMB_MR1)
                {
                    System.loadLibrary("anw.10");	
                    Log.d("appplay.ap", "vlc load anw.10");
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.HONEYCOMB_MR2)
                {
                    System.loadLibrary("anw.13");	
                    Log.d("appplay.ap", "vlc load anw.13");
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.JELLY_BEAN_MR1)
                {
                    System.loadLibrary("anw.14");
                    Log.d("appplay.ap", "vlc load anw.14");
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.KITKAT_WATCH)
                {
                    System.loadLibrary("anw.18");
                    Log.d("appplay.ap", "vlc load anw.18");
                }
                else
                {
                    System.loadLibrary("anw.21");	
                    Log.d("appplay.ap", "vlc load anw.21");
                }
            } catch (Throwable t)
            {
                Log.d("appplay.ap", "Unable to load the anw library: " + t);
            }

            try 
            {
                if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.GINGERBREAD_MR1)
                {
                    Log.d("appplay.ap", "vlc load iomx.10");
                    System.loadLibrary("iomx.10");	
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.HONEYCOMB_MR2)
                {
                    Log.d("appplay.ap", "vlc load iomx.13");
                    System.loadLibrary("iomx.13");	
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.JELLY_BEAN_MR1)
                {
                    Log.d("appplay.ap", "vlc load iomx.14");
                    System.loadLibrary("iomx.14");	
                }
                else if (Build.VERSION.SDK_INT <= Build.VERSION_CODES.JELLY_BEAN_MR2)
                {
                    Log.d("appplay.ap", "vlc load iomx.14");
                    System.loadLibrary("iomx.14");	
                }
                else
                {
                    Log.d("appplay.ap", "vlc load iomx.14");
                    System.loadLibrary("iomx.14");	
                }
            } 
            catch (Throwable t)
            {
            	Log.d("appplay.ap",  "Unable to load the iomx");   
            }
        }
        else
        {
        	Log.d("appplay.ap", "build.version.sdk small");
        }

        try 
        {
            System.loadLibrary("vlcjni");
        }
        catch (UnsatisfiedLinkError ule) 
        {
            Log.e(TAG, "Can't load vlcjni library: " + ule);
            /// FIXME Alert user
            //System.exit(1);
        } 
        catch (SecurityException se) 
        {
            Log.e(TAG, "Encountered a security issue when loading vlcjni library: " + se);
            /// FIXME Alert user
            //System.exit(1);
        }
        */
    }
}
