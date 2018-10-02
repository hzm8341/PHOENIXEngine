package org.appplay.voice;

import org.appplay.lib.AppPlayMetaData;

import android.app.Activity;
import android.util.Log;

public class VoiceSDKCreater
{
	public static String sSDK_NAME_UNKNOWN = "unknown";
	public static String sSDK_NAME_BAIDU = "baidu";
	public static String sSDK_NAME_KEDA = "keda";
	
	public static String sSDK_CurrentName = "";
	
	public static VoiceSDK Create (Activity activity)
	{	
		sSDK_CurrentName = AppPlayMetaData.sVOICESDKName;
		
		return _Create(activity, sSDK_CurrentName);
	}
	
	private static VoiceSDK _Create (Activity activity, String source)
	{	
		if (sSDK_NAME_BAIDU.equals(source)) 
		{
			return new VoiceSDKBaiDu(activity);
		}
		else if (sSDK_NAME_KEDA.equals(source)) 
		{
			return null;
		}
		else 
		{
			return null;
		}
	}
}
