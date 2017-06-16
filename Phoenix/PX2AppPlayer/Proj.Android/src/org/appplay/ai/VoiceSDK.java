package org.appplay.ai;

import org.appplay.lib.AppPlayNatives;
import org.appplay.platformsdk.PlatformSDK;
import android.app.Activity;
import android.os.Bundle;

abstract public class VoiceSDK {

	public static Activity sTheActivtiy = null;
	public static VoiceSDK sTheVoiceSDK = null;
	public static String sPlatformStr = "empty";
	
	public VoiceSDK(Activity act)
	{
		sTheActivtiy = act;
		TheType = Type.T_NONE;
	}

	public enum Type
	{
		T_NONE,
		T_BAIDU,
		T_TULING,
		T_MAX_TYPE
	}
	
	public Type TheType;
	
	public void OnSpeechStart()
	{
		AppPlayNatives.nativeOnSpeechStart();		
	}
	
	public void OnSpeechPause()
	{
		AppPlayNatives.nativeOnSpeechPause();
	}
	
	public void OnSpeechFinish()
	{
		AppPlayNatives.nativeOnSpeechFinish();
	}
	
	public void OnSpeechCancel()
	{
		AppPlayNatives.nativeOnSpeechCancel();
	}
	
	public abstract void StartVoiceListening();
	public abstract void EndVoiceListening();
	
	public void OnVoiceRecordStart()
	{
		AppPlayNatives.nativeOnVoiceRecordStart();		
	}
	
	public void OnVoiceRecordEnd()
	{
		AppPlayNatives.nativeOnVoiceRecordEnd();		
	}
	
	public void OnVoiceRecognizeResults(String strRet, String strJSON)
	{
		AppPlayNatives.nativeOnVoiceRecognizeResults(strRet, strJSON);
	}

	public abstract void speak(String text);
	public abstract void speakPause();
	public abstract void speakResume();
	public abstract void speakStop();
	public abstract void destory();
	
}
