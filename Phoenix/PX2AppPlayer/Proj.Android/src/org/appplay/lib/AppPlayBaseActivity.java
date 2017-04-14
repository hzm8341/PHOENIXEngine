package org.appplay.lib;

import java.io.File;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.List;
import java.util.Set;

import android.R.string;
import android.provider.Settings;

import org.appplay.ap.R;
import org.appplay.bluetooth.BluetoothSPP;
import org.appplay.bluetooth.BluetoothState;
import org.appplay.platformsdk.PlatformSDKNatives;
import org.appplay.platformsdk.PlatformSDK;
import org.appplay.platformsdk.PlatformSDKCreater;
import org.appplay.voice.VoiceSDK;
import org.appplay.voice.VoiceSDKCreater;

import com.baidu.tts.client.SpeechSynthesizer;

import android.app.Activity;
import android.app.ActivityManager;
import android.app.AlertDialog;
import android.app.Dialog;
import android.app.ActivityManager.RunningAppProcessInfo;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ActivityInfo;
import android.content.pm.ApplicationInfo;
import android.content.pm.ConfigurationInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.telephony.TelephonyManager;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.FrameLayout;
import android.widget.Toast;

public class AppPlayBaseActivity extends Activity {
	// Activtiy
	public static AppPlayBaseActivity sTheActivity;

	// AppPlay LibSO
	public static String sLibSO_Filename = "";
	public static String sLibSO_Dir = "";
	private static String sLibSO_Name = "AppPlay";

	// Vsersion
	public static String sVersion_Dir = "";
	public static String sVersion_Filename = "";
	public static String sVersion_Filename_Temp = "";

	// Siews
	public AppPlayUpdateLayout mUpdateView = null;
	public AppPlayGLView TheGLView = null;

	private static String msPackageName; // use static to support export
	private boolean mIsAppForeground = true;

	// Bluetooth
	BluetoothSPP mBt = null;
	private BluetoothAdapter mBtAdapter = null;
	ArrayList<String> mPairedDeviceStrs = new ArrayList<String>();
	ArrayList<String> mScanedDeviceStrs = new ArrayList<String>();
    
	// View
	private static FrameLayout sFrame = null;
	private AppPlayWebViewNatives mWebViewNatives = null;

	public static FrameLayout GetFrameLayout() {
		return AppPlayBaseActivity.sFrame;
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		Log.d("appplay.ap", "AppPlayBaseActivity::onCreate");

		sTheActivity = this;

		super.onCreate(savedInstanceState);

		// Package
		String packageName = getApplication().getPackageName();
		PackageManager packMgr = getApplication().getPackageManager();
		ApplicationInfo info = null;
		try {
			info = packMgr
					.getApplicationInfo(packageName, MODE_WORLD_WRITEABLE);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
		}

		String dataDir = info.dataDir;

		sLibSO_Dir = dataDir;
		sLibSO_Filename = dataDir + "/lib" + sLibSO_Name + ".so";

		sVersion_Dir = dataDir;
		sVersion_Filename = info.dataDir + "/version.xml";
		sVersion_Filename_Temp = info.dataDir + "/version_Temp.xml";

		// Initlize
		Log.d("appplay.ap", "begin - AppPlayActivity::onCreate");

		AppPlayMetaData.Initlize(getApplicationContext());

		if (AppPlayMetaData.sIsBluetoothable) {
			mBt = new BluetoothSPP(this);

			if (!mBt.IsBluetoothAvailable()) {
				Toast.makeText(getApplicationContext(),
						"Bluetooth is not available", Toast.LENGTH_SHORT)
						.show();

				// finish();
			}

			mBt.SetBluetoothConnectionListener(new BluetoothSPP.BluetoothConnectionListener() {
				public void onDeviceConnected(String name, String address) {
					Toast.makeText(getApplicationContext(),
							"Connected to " + name, Toast.LENGTH_SHORT).show();

					AppPlayNatives.nativeBluetoothOnConnected();
				}

				public void onDeviceDisconnected() {
					Toast.makeText(getApplicationContext(), "Connection lost",
							Toast.LENGTH_SHORT).show();

					AppPlayNatives.nativeBluetoothOnDisConnected();
				}

				public void onDeviceConnectionFailed() {
					Log.i("Check", "Unable to connect");

					AppPlayNatives.nativeBluetoothOnConnectFailed();
				}
			});

			mBt.SetAutoConnectionListener(new BluetoothSPP.AutoConnectionListener() {
				public void onNewConnection(String name, String address) {
					Log.i("Check", "New Connection - " + name + " - " + address);
				}

				public void onAutoConnectionStarted() {
					Log.i("Check", "Auto menu_connection started");
				}
			});

			mBtAdapter = BluetoothAdapter.getDefaultAdapter();
			_BtGetPairedDevices();

			IntentFilter filter = new IntentFilter(BluetoothDevice.ACTION_FOUND);
			this.registerReceiver(mReceiver, filter);
			filter = new IntentFilter(
					BluetoothAdapter.ACTION_DISCOVERY_FINISHED);
			this.registerReceiver(mReceiver, filter);
		}

		// voice
		if (AppPlayMetaData.sIsVoiceable)
			VoiceSDK.sTheVoiceSDK = VoiceSDKCreater.Create(this);

		// frame
		ViewGroup.LayoutParams framelayout_params = 
				new FrameLayout.LayoutParams(FrameLayout.LayoutParams.MATCH_PARENT,
						FrameLayout.LayoutParams.MATCH_PARENT);

		FrameLayout framelayout = new FrameLayout(
				AppPlayBaseActivity.sTheActivity);		
		framelayout.setLayoutParams(framelayout_params);
		
		sFrame = framelayout;
		setContentView(sFrame);

		if (AppPlayMetaData.sIsNettable)
			PlatformSDK.sThePlatformSDK = PlatformSDKCreater.Create(this);
		else
			Show_GLView();

		Log.d("appplay.ap", "end - AppPlayActivity::onCreate");
		
		if (null == savedInstanceState)
		{
			mWebViewNatives = new AppPlayWebViewNatives(sFrame);	
		}
		else
		{
			 mWebViewNatives = new AppPlayWebViewNatives(sFrame);             
			 String[] strs = savedInstanceState.getStringArray("WEBVIEW");             
			 mWebViewNatives.setAllWebviews(strs);
			 
			 savedInstanceState.clear();
		}
	}
	
	@Override
	protected void onSaveInstanceState(Bundle outState) {
		
		Log.d("appplay.ap", "begin - AppPlayActivity::onSaveInstanceState");
		
		if (null != mWebViewNatives)
			outState.putStringArray("WEBVIEW", mWebViewNatives.getAllWebviews());
		
		super.onSaveInstanceState(outState);
		
		Log.d("appplay.ap", "end - AppPlayActivity::onSaveInstanceState");
	}

	private void _SetDeviceID() {
		// Device IDs
		TelephonyManager telephonyManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
		String deviceIDStr = telephonyManager.getDeviceId();
		String subScriberIDStr = telephonyManager.getSubscriberId();

		String serialnumStr = null;
		try {
			Class<?> c = Class.forName("android.os.SystemProperties");
			Method get = c.getMethod("get", String.class, String.class);
			serialnumStr = (String) (get.invoke(c, "ro.serialno", "unknown"));
		} catch (Exception ignored) {
		}
		String serialnumStr2 = null;
		try {
			Class myclass = Class.forName("android.os.SystemProperties");
			Method[] methods = myclass.getMethods();
			Object[] params = new Object[] { new String("ro.serialno"),
					new String("Unknown") };
			serialnumStr2 = (String) (methods[2].invoke(myclass, params));
		} catch (Exception ignored) {
		}

		String androidIDStr = Settings.Secure.getString(getContentResolver(),
				Settings.Secure.ANDROID_ID);

		String myDeviceIDStr = deviceIDStr + serialnumStr;

		Log.d("appplay.ap", "begin - AppPlayNatives.nativeSetDeviceIDStr");
		AppPlayNatives.nativeSetDeviceIDStr(myDeviceIDStr);
		Log.d("appplay.ap", "end - AppPlayNatives.nativeSetDeviceIDStr");
	}

	@Override
	public void onStart() {
		Log.d("appplay.lib", "AppPlayBaseActivity::onStart");
		
		super.onStart();

		if (AppPlayMetaData.sIsBluetoothable) {
			if (!mBt.IsBluetoothEnabled()) {
				Intent intent = new Intent(
						BluetoothAdapter.ACTION_REQUEST_ENABLE);
				startActivityForResult(intent, BluetoothState.REQUEST_ENABLE_BT);
			} else {
				if (!mBt.IsServiceAvailable()) {
					mBt.SetupService();
					mBt.StartService(BluetoothState.IS_DEVICE_SELF);
				}
			}
		}		
	}

	public void onActivityResult(int requestCode, int resultCode, Intent data) {
		if (requestCode == BluetoothState.REQUEST_ENABLE_BT) {
			if (resultCode == Activity.RESULT_OK) {
				mBt.SetupService();
				mBt.StartService(BluetoothState.IS_DEVICE_SELF);
			} else {
				Toast.makeText(getApplicationContext(),
						"Bluetooth was not enabled.", Toast.LENGTH_SHORT)
						.show();
			}
		}
	}

	@Override
	protected void onStop() {
		Log.d("appplay.lib", "AppPlayBaseActivity::onStop");

		super.onStop();

		if (_IsAppOnForeground()) {
			mIsAppForeground = false;
		}

		if (AppPlayMetaData.sIsBluetoothable) {
			mBt.StopService();
		}	
	}

	@Override
	protected void onPause() {
		Log.d("appplay.lib", "AppPlayBaseActivity::onPause");

		super.onPause();

		if (null != TheGLView)
			TheGLView.onPause();
		
		if (null != mWebViewNatives)
			mWebViewNatives.pauseAll();
	}

	@Override
	protected void onResume() {

		Log.d("appplay.lib", "AppPlayBaseActivity::onResume");

		super.onResume();
		
		if (null != TheGLView)
			TheGLView.onResume();		

		if (!mIsAppForeground) {
			if (null != PlatformSDK.sThePlatformSDK)
				PlatformSDK.sThePlatformSDK.OnResume();

			mIsAppForeground = true;
		}
		
		if (null != mWebViewNatives)
			mWebViewNatives.resumeAll();
	}

	@Override
	public void onDestroy() {
		super.onDestroy();
		
		if (null != VoiceSDK.sTheVoiceSDK)
			VoiceSDK.sTheVoiceSDK.destory();

		if (null != TheGLView)
			TheGLView.Destory();

		if (null != PlatformSDK.sThePlatformSDK)
			PlatformSDK.sThePlatformSDK.Term();

		if (null != mBtAdapter) {
			unregisterReceiver(mReceiver);
			mBtAdapter.cancelDiscovery();
		}
	}

	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		if (keyCode == KeyEvent.KEYCODE_BACK) {
			if (null != PlatformSDK.sThePlatformSDK) {
				PlatformSDK.sThePlatformSDK.OnExist();

				return true;
			}
		}

		return super.onKeyDown(keyCode, event);
	}

	// -- internal functions implemented ourself --

	private boolean _IsOpenGLES20Valied() {
		ActivityManager am = (ActivityManager) getSystemService(Context.ACTIVITY_SERVICE);
		ConfigurationInfo info = am.getDeviceConfigurationInfo();

		return (info.reqGlEsVersion >= 0x20000);
	}

	private void _SetPackageName(String packageName) {
		msPackageName = packageName;
		Log.d("appplay.ap", "PackageName:" + msPackageName);

		String apkFilePath = "";
		ApplicationInfo appInfo = null;
		PackageManager packMgmr = getApplication().getPackageManager();
		try {
			appInfo = packMgmr.getApplicationInfo(packageName, 0);
		} catch (NameNotFoundException e) {
			e.printStackTrace();
			throw new RuntimeException("Unable to locate assets, aborting...");
		}
		apkFilePath = appInfo.sourceDir;
		Log.d("appplay.ap", "ResourcePath:" + apkFilePath);

		// set apkPath
		AppPlayNatives.nativeSetApkDataPath(apkFilePath);

		// set
		if (AppPlayMetaData.sIsNettable && AppPlayMetaData.sIsTest) {
			AppPlayNatives.nativeSetDataUpdateServerType("ResourceServerTest");
		}
	}

	private boolean _IsAppOnForeground() {
		ActivityManager activityManager = (ActivityManager) getApplicationContext()
				.getSystemService(Context.ACTIVITY_SERVICE);
		String packageName = getApplicationContext().getPackageName();
		List<RunningAppProcessInfo> appProcesses = activityManager
				.getRunningAppProcesses();
		if (appProcesses == null)
			return false;
		for (RunningAppProcessInfo appProcess : appProcesses) {
			if (appProcess.processName.equals(packageName)
					&& appProcess.importance == RunningAppProcessInfo.IMPORTANCE_FOREGROUND) {
				return true;
			}
		}
		return false;
	}

	// -- gen functions can be called implemented ourself --

	// show a updateview to load LibSO from server
	public void Show_UpdateView() {
		runOnUiThread(new Runnable() {
			public void run() {
				mUpdateView = new AppPlayUpdateLayout(
						AppPlayBaseActivity.sTheActivity,
						R.layout.appplayupdateview);

				setContentView(mUpdateView);

				mUpdateView.CheckVersion();
			}
		});
	}

	// updated ok, let's show our opengles view
	public void Show_GLView() {
		runOnUiThread(new Runnable() {
			public void run() {

				System.loadLibrary("fmodL");

				File fileLibSO = new File(sLibSO_Filename);
				if (fileLibSO.exists()) {
					// a updated so, load it from a update dir

					Log.d("appplay.lib", "begin - load sLibSO(from dir):"
							+ sLibSO_Filename);

					System.load(sLibSO_Filename);

					Log.d("appplay.lib", "end - load sLibSO(form dir):"
							+ sLibSO_Filename);
				} else { // load so packaged with the first apk

					Log.d("appplay.lib",
							"begin - load sLibSO(form init packaged):"
									+ sLibSO_Name);
					try {
						System.loadLibrary(sLibSO_Name);
					} catch (UnsatisfiedLinkError ulink) {
						ulink.printStackTrace();

						Log.d("appplay.lib",
								"end - load sLibSO(form init packaged Failed):"
										+ sLibSO_Name);
					}

					Log.d("appplay.lib",
							"end - load sLibSO(form init packaged):"
									+ sLibSO_Name);
				}
				Log.d("appplay.lib", "ok - load sLibSO.");

				_SetDeviceID();

				// package name
				String packageName = getApplication().getPackageName();
				_SetPackageName(packageName);

				// set platformsdk
				PlatformSDKNatives
						.SetPlatformSDK(PlatformSDKCreater.sSDK_CurrentName);

				AppPlayNatives.nativeVoiceSetSDK(VoiceSDK.sPlatformStr);

				// -- begin FrameLayout --

				// PX2EditText layout
				ViewGroup.LayoutParams edittext_layout_params = new ViewGroup.LayoutParams(
						ViewGroup.LayoutParams.FILL_PARENT,
						ViewGroup.LayoutParams.WRAP_CONTENT);
				AppPlayEditText edittext = new AppPlayEditText(
						AppPlayBaseActivity.sTheActivity);
				edittext.setLayoutParams(edittext_layout_params);

				// ...add to FrameLayout
				sFrame.addView(edittext);

				// view
				if (_IsOpenGLES20Valied()) {
					TheGLView = new AppPlayGLView(
							AppPlayBaseActivity.sTheActivity);
				} else {
					Log.d("appplay.lib", "info - Don't support gles2.0");
					finish();
				}

				sFrame.addView(TheGLView);

				TheGLView.SetEditText(edittext);

				// -- end FrameLayout --

				// hide soupdateview
				if (null != mUpdateView)
					mUpdateView.setVisibility(View.GONE);
			}
		});
	}

	public void Show_NoNetDlg() {
		Dialog alertDialog = new AlertDialog.Builder(this).setTitle("注意")
				.setMessage("您的网络已经断开，请连接！")
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				}).create();
		alertDialog.show();
	}

	public void Show_NoWifiDialog() {
		Dialog alertDialog = new AlertDialog.Builder(this).setTitle("注意")
				.setMessage("游戏需要更新，您处在非wifi网络环境下，确定进行更新？")
				.setIcon(R.drawable.ic_launcher)
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				})
				.setNegativeButton("取消", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						((AppPlayBaseActivity) sTheActivity).MyExit();
					}
				}).create();
		alertDialog.show();
	}

	public void Show_ConnectResServerFailedDlg() {
		Dialog alertDialog = new AlertDialog.Builder(this).setTitle("注意")
				.setMessage("连接服务器失败！")
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
					}
				}).create();
		alertDialog.show();
	}

	public void Show_HasNewAPKDlg() {
		Dialog alertDialog = new AlertDialog.Builder(this).setTitle("注意")
				.setMessage("安装包已有新版本,请下载安装.")
				.setPositiveButton("确定", new DialogInterface.OnClickListener() {
					public void onClick(DialogInterface dialog, int which) {
						dialog.dismiss();
						((AppPlayBaseActivity) sTheActivity).MyExit();
					}
				}).create();
		alertDialog.show();
	}

	public void MyExit() {
		runOnUiThread(new Runnable() {
			public void run() {
				android.os.Process.killProcess(android.os.Process.myPid());
			}
		});

	}

	public static void SetScreenOrientation(int or) {
		if (0 == or)
			((AppPlayBaseActivity) (sTheActivity))
					.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		else if (1 == or)
			((AppPlayBaseActivity) (sTheActivity))
					.setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE);
	}

	public static String GetPackageName() {
		return msPackageName;
	}

	// platform sdk functions

	public static void PlatformSDKLogin() {
		((AppPlayBaseActivity) (sTheActivity))._ThirdPlatformLogin1();
	}

	public void _ThirdPlatformLogin1() {
		this.runOnUiThread(new Runnable() {
			public void run() {
				if (null != PlatformSDK.sThePlatformSDK)
					PlatformSDK.sThePlatformSDK.Login();
			}
		});
	}

	public static void PlatformSDKLogout() {
		((AppPlayBaseActivity) (sTheActivity))._Show_LogoutExitDlg();
	}

	public void _Show_LogoutExitDlg() {
		this.runOnUiThread(new Runnable() {
			public void run() {
				if (null != PlatformSDK.sThePlatformSDK)
					PlatformSDK.sThePlatformSDK.OnLogoutExist();
			}
		});
	}

	public static void PlatformSDKSynPay(final String productID,
			final String productName, final float productPrice,
			final float productOrginalPrice, final int count,
			final String payDescription) {
		((AppPlayBaseActivity) (sTheActivity))._SynPay(productID, productName,
				productPrice, productOrginalPrice, count, payDescription);
	}

	public void _SynPay(final String productID, final String productName,
			final float productPrice, final float productOrginalPrice,
			final int count, final String payDescription) {
		this.runOnUiThread(new Runnable() {
			public void run() {
				if (null != PlatformSDK.sThePlatformSDK)
					PlatformSDK.sThePlatformSDK.SynPay(productID, productName,
							productPrice, productOrginalPrice, count,
							payDescription);
			}
		});
	}

	public static void PlatformSDKASynPay(final String productID,
			final String productName, final float productPrice,
			final float productOrginalPrice, final int count,
			final String payDescription) {
		((AppPlayBaseActivity) (sTheActivity))._ASynPay(productID, productName,
				productPrice, productOrginalPrice, count, payDescription);
	}

	public void _ASynPay(final String productID, final String productName,
			final float productPrice, final float productOrginalPrice,
			final int count, final String payDescription) {
		this.runOnUiThread(new Runnable() {
			public void run() {
				if (null != PlatformSDK.sThePlatformSDK)
					PlatformSDK.sThePlatformSDK.ASynPay(productID, productName,
							productPrice, productOrginalPrice, count,
							payDescription);
			}
		});
	}

	// bluetooth
	public static boolean BluetoothIsAvailable() {
		if (null != sTheActivity.mBt) {
			return sTheActivity.mBt.IsBluetoothAvailable();
		}

		return false;
	}

	public static boolean BluetoothIsConnected() {
		if (null != sTheActivity.mBt) {
			if (sTheActivity.mBt.IsBluetoothAvailable()) {
				return sTheActivity.mBt.GetServiceState() == BluetoothState.STATE_CONNECTED;
			}
		}

		return false;
	}

	public static void BluetoothDisconnect() {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != sTheActivity.mBt) {
						if (sTheActivity.mBt.IsBluetoothAvailable()) {
							sTheActivity.mBt.Disconnect();
						}
					}				
				}
			});		
		}
	}

	public static void BluetoothConnect(String address) {
		if (null != sTheActivity) {
			sTheActivity._BluetoothConnect(address);
		}
	}
	
	private void _BluetoothConnect(final String address) {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != mBt) {
						if (sTheActivity.mBt.IsBluetoothAvailable()) {
							sTheActivity.mBt.Connect(address);
						}
					}				
				}
			});		
		}
	}	

	public static void BluetoothSend(String str, boolean isAppendCRLF) {
		if (null != sTheActivity) {
				sTheActivity._BluetoothSend(str, isAppendCRLF);
		}
	}
	
	private void _BluetoothSend(final String str, final boolean isAppendCRLF) {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != mBt) {
						if (mBt.IsBluetoothAvailable()) {
							mBt.Send(str, isAppendCRLF);
						}
					}				
				}
			});			
		}
	}

	public static String BluetoothGetPairedDevices() {
		String allStr = new String();

		if (null != sTheActivity.mBt) {
			if (sTheActivity.mBt.IsBluetoothAvailable()) {
				sTheActivity._BtGetPairedDevices();

				for (int i = 0; i < sTheActivity.mPairedDeviceStrs.size(); i++) {
					String str = sTheActivity.mPairedDeviceStrs.get(i);
					allStr += str;
					allStr += ";";
				}
			}
		}

		return allStr;
	}

	public static void BluetoothDoDiscovery() {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != sTheActivity.mBt) {
						if (sTheActivity.mBt.IsBluetoothAvailable()) {
							sTheActivity._BtDoDiscovery();
						}
					}					
				}
			});			
		}
	}

	public static void BluetoothCancelDiscovery() {		
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != sTheActivity.mBt) {
						if (sTheActivity.mBt.IsBluetoothAvailable()) {
							sTheActivity._BtCancelDiscovery();
						}
					}
				}
			});
		}
	}
	
	private void _BtGetPairedDevices() {
		mPairedDeviceStrs.clear();

		if (null == mBtAdapter)
			return;

		Set<BluetoothDevice> devices = mBtAdapter.getBondedDevices();
		for (BluetoothDevice device : devices) {
			mPairedDeviceStrs.add(device.getName() + "_" + device.getAddress());
		}
	}

	private void _BtDoDiscovery() {
		if (null == mBtAdapter)
			return;

		mScanedDeviceStrs.clear();

		if (mBtAdapter.isDiscovering()) {
			mBtAdapter.cancelDiscovery();
		}

		mBtAdapter.startDiscovery();

		Log.d("appplay.ap", "AppPlayBaseActivity::_BtDoDiscovery");
	}

	void _BtOnDiscoveryNewDevice(String strDevice) {
		mScanedDeviceStrs.add(strDevice);
		AppPlayNatives.nativeBluetoothDiscoveryNewDevice(strDevice);
	}

	void _BtOnDiscoveryFinished() {
		AppPlayNatives.nativeBluetoothDiscoveryFinished();
	}

	private void _BtCancelDiscovery() {
		if (null != mBtAdapter)
			mBtAdapter.cancelDiscovery();
	}

	private final BroadcastReceiver mReceiver = new BroadcastReceiver() {
		public void onReceive(Context context, Intent intent) {
			String action = intent.getAction();

			// When discovery finds a device
			if (BluetoothDevice.ACTION_FOUND.equals(action)) {
				// Get the BluetoothDevice object from the Intent
				BluetoothDevice device = intent
						.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);

				String strDevice = device.getName() + "_" + device.getAddress();

				AppPlayBaseActivity.sTheActivity
						._BtOnDiscoveryNewDevice(strDevice);
			} else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED
					.equals(action)) {
				AppPlayBaseActivity.sTheActivity._BtOnDiscoveryFinished();
			}
		}
	};

	// voice recognize

	// Voice
	public static void StartVoiceListening() {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != VoiceSDK.sTheVoiceSDK)
						VoiceSDK.sTheVoiceSDK.StartVoiceListening();
				}
			});
		}
	}

	public static void EndVoiceListening() {
		if (null != sTheActivity) {
			sTheActivity.runOnUiThread(new Runnable() {
				public void run() {
					if (null != VoiceSDK.sTheVoiceSDK)
						VoiceSDK.sTheVoiceSDK.EndVoiceListening();
				}
			});
		}
	}
	
	public static void VoiceSpeak(String text){
		if (null != sTheActivity)
		{
			sTheActivity._VoiceSpeak(text);
		}
	}
	
	private void _VoiceSpeak(final String text)
	{	
		this.runOnUiThread(new Runnable() {
			public void run() {
				if (null != VoiceSDK.sTheVoiceSDK)
					VoiceSDK.sTheVoiceSDK.speak(text);
			}
		});
	}
}
