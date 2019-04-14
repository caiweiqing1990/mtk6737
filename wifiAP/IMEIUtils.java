package com.mediatek.sim;

import android.content.Context;
import android.telephony.PhoneStateListener;
import android.telephony.TelephonyManager;

import java.lang.reflect.Method;

public class IMEIUtils {

	private static final String TAG = IMEIUtils.class.getSimpleName();

	private IMEIUtils() {
	};

	private static class IMEIInstance {
		private static IMEIUtils utils = new IMEIUtils();
	}

	private TelephonyManager mTelephony;

	private Context mContext;

	public void Init(Context cxt) {
		if (null == mTelephony) {
			mContext = cxt;
			// mMyPhoneStateListener = new MyPhoneStateListener();
			mTelephony = (TelephonyManager) cxt.getSystemService(Context.TELEPHONY_SERVICE);
			// mTelephony.listen(mMyPhoneStateListener,PhoneStateListener.LISTEN_SIGNAL_STRENGTHS);
		}
	}

	public static IMEIUtils getInstance() {
		return IMEIInstance.utils;
	}
	
	public TelephonyManager getServer(){
		return mTelephony;
	}

	public String getIMEI() {
		return getImeiMethod();// mTelephony.getDeviceId();"861648032528007";//
	}

	private String getImeiMethod() {
		Class<TelephonyManager> telephonyManagerClass = TelephonyManager.class;
		try {
			Method method = telephonyManagerClass.getMethod("getImei");
			Object object = method.invoke(mTelephony);
			String mImei = (String) object;
			return mImei;
		} catch (NoSuchMethodException e) {
			e.printStackTrace();
		} catch (Exception e) {
			e.getMessage();
		}
		return "";

	}
	
}
