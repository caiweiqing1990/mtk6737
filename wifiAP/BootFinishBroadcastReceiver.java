package com.mediatek.settings;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.provider.Settings;
import android.util.Log;

public class BootFinishBroadcastReceiver extends BroadcastReceiver {
	private WifiManager mWifiManager;
	private WifiConfiguration mWifiConfig;

	@Override
	public void onReceive(Context context, Intent intent) {
		String action = intent.getAction();
		if("android.intent.action.BOOT_COMPLETED".equals(action)){
			System.out.println("系统启动完成 BOOT_COMPLETED");//系统启动完成
			Log.d("Anand","系统启动完成 BOOT_COMPLETED");

			mWifiManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
			mWifiConfig = mWifiManager.getWifiApConfiguration();

			mWifiConfig.SSID = "SatFi-MTK6737";
			mWifiConfig.preSharedKey ="12345678";
			mWifiConfig.apBand = 0;
			mWifiConfig.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.WPA2_PSK);
			mWifiConfig.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.OPEN);

			mWifiManager.setWifiApConfiguration(mWifiConfig);

			//始终开启AP
			int value = Settings.System.getInt(context.getContentResolver(), Settings.System.WIFI_HOTSPOT_AUTO_DISABLE,
			Settings.System.WIFI_HOTSPOT_AUTO_DISABLE_FOR_FIVE_MINS);
			if(value != Settings.System.WIFI_HOTSPOT_AUTO_DISABLE_OFF){

				Settings.System.putInt(context.getContentResolver(), Settings.System.WIFI_HOTSPOT_AUTO_DISABLE,
				Settings.System.WIFI_HOTSPOT_AUTO_DISABLE_OFF);
			}

			//AP开启
			mWifiManager.setWifiApEnabled(mWifiConfig, true);

		}
	}
}