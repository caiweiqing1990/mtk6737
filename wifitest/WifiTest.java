import android.util.Slog;
import android.os.ServiceManager;
import android.os.IBinder;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.net.wifi.IWifiManager;
import android.net.StaticIpConfiguration;
import android.net.LinkAddress;
import android.net.IEthernetManager;
import android.net.IpConfiguration;
import android.net.IpConfiguration.IpAssignment;
import android.net.IpConfiguration.ProxySettings;
import android.net.NetworkUtils;

public class WifiTest {
    private static final String TAG = "WifiTest";
	
    public static void main(String args[]) throws Exception
    {
        if (args.length == 1 && args[0].equals("wifiapstop"))
        {
            /* 1. getService */
            IBinder binder = ServiceManager.getService("wifi");
            if (binder == null)
            {
                System.out.println("can not get wifi service");
                //Slog.i(TAG, "can not get wifi service");
                return;
            }
			
			System.out.println("get wifi service ok");
			//Slog.i(TAG, "get wifi service ok");
				
            IWifiManager mWifiManager = IWifiManager.Stub.asInterface(binder);
			System.out.println("getWifiApEnabledState="+(mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED));//public static final int WIFI_AP_STATE_ENABLED = 13;
			System.out.println("getWifiEnabledState="+(mWifiManager.getWifiEnabledState() == WifiManager.WIFI_STATE_ENABLED));//public static final int WIFI_STATE_ENABLED = 3;

			while(mWifiManager.getWifiEnabledState() == WifiManager.WIFI_STATE_ENABLED)
			{
				System.out.println("setWifiEnabled");
				mWifiManager.setWifiEnabled(false);		
				Thread.sleep(2000);
			}
			
			//mWifiManager.setWifiApConfiguration(mWifiConfig);
			while(mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED)
			{
				System.out.println("setWifiApEnabled");
				WifiConfiguration mWifiConfig = mWifiManager.getWifiApConfiguration();
				mWifiManager.setWifiApEnabled(mWifiConfig, false);
				Thread.sleep(2000);
			}
		}
        else if (args.length == 3 && args[0].equals("wifiapstart"))
        {
            /* 1. getService */
            IBinder binder = ServiceManager.getService("wifi");
            if (binder == null)
            {
                System.out.println("can not get wifi service");
                //Slog.i(TAG, "can not get wifi service");
                return;
            }
			
			System.out.println("get wifi service ok");
			//Slog.i(TAG, "get wifi service ok");
			
            IWifiManager mWifiManager = IWifiManager.Stub.asInterface(binder);
			System.out.println("getWifiApEnabledState="+(mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED));//public static final int WIFI_AP_STATE_ENABLED = 13;
			System.out.println("getWifiEnabledState="+(mWifiManager.getWifiEnabledState() == WifiManager.WIFI_STATE_ENABLED));//public static final int WIFI_STATE_ENABLED = 3;
			
			while(mWifiManager.getWifiEnabledState() == WifiManager.WIFI_STATE_ENABLED)
			{
				System.out.println("setWifiEnabled1");
				mWifiManager.setWifiEnabled(false);		
				Thread.sleep(2000);
			}
			
			WifiConfiguration mWifiConfig = mWifiManager.getWifiApConfiguration();
			
			//mWifiManager.setWifiApConfiguration(mWifiConfig);
			while(mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED)
			{
				System.out.println("setWifiApEnabled2");
				mWifiManager.setWifiApEnabled(mWifiConfig, false);
				Thread.sleep(2000);
			}
						
			if((mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED) == false)
			{
				System.out.println("setWifiApEnabled3");
				mWifiConfig.SSID = args[1];
				mWifiConfig.preSharedKey = args[2];
				//mWifiConfig.apBand = 0;
				//mWifiConfig.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.WPA2_PSK);
				//mWifiConfig.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.OPEN);
				mWifiManager.setWifiApConfiguration(mWifiConfig);
				mWifiManager.setWifiApEnabled(mWifiConfig, true);				
			}
		}
		else
		{
			System.out.println("Usage: need parameter: wifiapstop");
			System.out.println("Usage: need parameter: wifiapstart ssid passwd");
            return;			
		}

/*		
		IBinder binder = ServiceManager.getService("ethernet");
		if (binder == null)
		{
			System.out.println("can not get ethernet service");
			//Slog.i(TAG, "can not get wifi service");
			return;
		}
		
		System.out.println("get ethernet service ok");
		
		StaticIpConfiguration staticIpConfiguration = new StaticIpConfiguration();
		LinkAddress linkAddr = new LinkAddress(NetworkUtils.numericToInetAddress("192.168.5.1"),24);
		staticIpConfiguration.ipAddress= linkAddr;
		
		IpConfiguration config = new IpConfiguration(IpAssignment.STATIC, ProxySettings.NONE, staticIpConfiguration, null);
		IEthernetManager mEthernet = IEthernetManager.Stub.asInterface(binder);
		mEthernet.setConfiguration(config);
		
		System.out.println("mEthernet.setConfiguration" + mEthernet.isAvailable());
*/
	}
}
