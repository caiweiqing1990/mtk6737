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
import java.net.InetAddress;
import com.android.internal.telephony.ITelephony;
import android.telephony.SubscriptionManager;
import android.telephony.SignalStrength;
import android.telephony.TelephonyManager;
import com.android.internal.telephony.TelephonyProperties;
import com.android.internal.telephony.IPhoneSubInfo;
import android.telephony.PhoneStateListener;

//adb push Z:\out\target\product\len6737t_66_sh_n\system\framework\WifiTest.jar /system/framework
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest wifiapstop
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest wifiapstart weiqing 12345678
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest setDataEnabled
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest setDataDisabled
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest getnetworktype
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest getimei
//CLASSPATH=/system/framework/WifiTest.jar app_process / WifiTest getimsi

//wifi Telephony Ethernet control
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
        else if (args.length >= 1 && args[0].equals("wifiapstart"))
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

			while(mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED)
			{
				System.out.println("setWifiApEnabled2");
				mWifiManager.setWifiApEnabled(mWifiConfig, false);
				Thread.sleep(2000);
			}
			
			if((mWifiManager.getWifiApEnabledState() == WifiManager.WIFI_AP_STATE_ENABLED) == false)
			{
				System.out.println("setWifiApEnabled3");
				if(args.length == 3)
				{
					System.out.println("SSID="+args[1]+",PASSWD="+args[2]);
					mWifiConfig.SSID = args[1];
					mWifiConfig.preSharedKey = args[2];
				}
				//mWifiConfig.apBand = 0;
				//mWifiConfig.allowedKeyManagement.set(WifiConfiguration.KeyMgmt.WPA2_PSK);
				//mWifiConfig.allowedAuthAlgorithms.set(WifiConfiguration.AuthAlgorithm.OPEN);
				mWifiManager.setWifiApConfiguration(mWifiConfig);
				mWifiManager.setWifiApEnabled(mWifiConfig, true);	
			}
		}
		else if (args.length == 1 && args[0].equals("setDataEnabled"))
		{
			//System.out.println("get phone service ok");
			ITelephony telephony = ITelephony.Stub.asInterface(ServiceManager.getService("phone"));
			int subId = SubscriptionManager.getDefaultDataSubscriptionId();

			if(telephony.getDataEnabled(subId) == false)
			{
				telephony.setDataEnabled(subId, true);
				System.out.println("setDataEnabled");
			}

			//int phoneId = SubscriptionManager.getPhoneId(subId);
			//System.out.println("getSimOperatorName="+TelephonyManager.getTelephonyProperty(phoneId,TelephonyProperties.PROPERTY_ICC_OPERATOR_ALPHA, ""));

			/*
			public static final int SIGNAL_STRENGTH_NONE_OR_UNKNOWN = 0;
			public static final int SIGNAL_STRENGTH_POOR = 1;
			public static final int SIGNAL_STRENGTH_MODERATE = 2;
			public static final int SIGNAL_STRENGTH_GOOD = 3;
			public static final int SIGNAL_STRENGTH_GREAT = 4;
			*/
			//SignalStrength mSignalStrength = new SignalStrength();
			//System.out.println("mSignalStrength.getLevel=" + mSignalStrength.getLevel());//获取信号格数
			/*
			System.out.println("mSignalStrength.getTdScdmaLevel=" + mSignalStrength.getTdScdmaLevel());//获取信号格数
			System.out.println("mSignalStrength.getGsmLevel=" + mSignalStrength.getGsmLevel());//获取信号格数
			System.out.println("mSignalStrength.getCdmaLevel=" + mSignalStrength.getCdmaLevel());//获取信号格数
			System.out.println("mSignalStrength.getEvdoLevel=" + mSignalStrength.getEvdoLevel());//获取信号格数

			System.out.println("mSignalStrength.getEvdoDbm=" + mSignalStrength.getEvdoDbm());//获取信号格数
			System.out.println("mSignalStrength.getLteDbm=" + mSignalStrength.getLteDbm());//获取信号格数
			System.out.println("mSignalStrength.getTdScdmaLevel=" + mSignalStrength.getTdScdmaLevel());//获取信号格数
			System.out.println("mSignalStrength.getGsmDbm=" + mSignalStrength.getGsmDbm());//获取信号格数
			System.out.println("mSignalStrength.getTdScdmaDbm=" + mSignalStrength.getTdScdmaDbm());//获取信号格数
			System.out.println("mSignalStrength.getCdmaDbm=" + mSignalStrength.getCdmaDbm());//获取信号格数
			System.out.println("mSignalStrength.getEvdoDbm=" + mSignalStrength.getEvdoDbm());//获取信号格数
			*/
		}
		else if (args.length == 1 && args[0].equals("setDataDisabled"))
		{
			IBinder binder = ServiceManager.getService("phone");
			if (binder == null)
			{
				System.out.println("can not get phone service");
				//Slog.i(TAG, "can not get wifi service");
				return;
			}

			System.out.println("get phone service ok");
			ITelephony telephony = ITelephony.Stub.asInterface(binder);
			int subId = SubscriptionManager.getDefaultDataSubscriptionId();

			if(telephony.getDataEnabled(subId) == true)
			{
				telephony.setDataEnabled(subId, false);
				System.out.println("setDataDisabled");
			}
		}
		else if (args.length == 1 && args[0].equals("getimei"))
		{
			ITelephony telephony = ITelephony.Stub.asInterface(ServiceManager.getService("phone"));
			String imeiUtils = telephony.getDeviceId(null);
			System.out.println(imeiUtils);
		}
		else if (args.length == 1 && args[0].equals("getimsi"))
		{
			IPhoneSubInfo info = IPhoneSubInfo.Stub.asInterface(ServiceManager.getService("iphonesubinfo"));
			int subId = SubscriptionManager.getDefaultDataSubscriptionId();
			String imsiUtils = info.getSubscriberIdForSubscriber(subId, null);
			System.out.println(imsiUtils);	
		}
		else if (args.length == 1 && args[0].equals("getnetworktype"))
		{
			/*
			public static final int NETWORK_CLASS_UNKNOWN = 0;
			public static final int NETWORK_CLASS_2_G = 1;
			public static final int NETWORK_CLASS_3_G = 2;
			public static final int NETWORK_CLASS_4_G = 3;
			*/
			ITelephony telephony = ITelephony.Stub.asInterface(ServiceManager.getService("phone"));
			int networkType = telephony.getNetworkType();
			System.out.println(TelephonyManager.getNetworkClass(networkType));//获取网络类型 2G 3G 4G
		}
		else
		{
			System.out.println("Usage: need parameter: getnetworktype");
			System.out.println("Usage: need parameter: getimei");
			System.out.println("Usage: need parameter: getimsi");
			System.out.println("Usage: need parameter: wifiapstop");
			System.out.println("Usage: need parameter: wifiapstart");
			System.out.println("Usage: need parameter: wifiapstart ssid passwd");
 			System.out.println("Usage: need parameter: setDataEnabled");
			System.out.println("Usage: need parameter: setDataDisabled");
		}


		//IBinder binder = ServiceManager.getService("ethernet");//获取ethernet服务
		//if (binder == null)
		//{
		//	System.out.println("can not get ethernet service");
			//Slog.i(TAG, "can not get wifi service");
		//	return;
		//}

		//System.out.println("get ethernet service ok");
		//StaticIpConfiguration staticIpConfiguration = new StaticIpConfiguration();
		//LinkAddress linkAddr = new LinkAddress(NetworkUtils.numericToInetAddress("192.168.1.1"),24);//ip
		//staticIpConfiguration.ipAddress= linkAddr;
		
		//InetAddress gateway = NetworkUtils.numericToInetAddress("192.168.1.1");//gateway
		//staticIpConfiguration.gateway = gateway;
		
		//staticIpConfiguration.dnsServers.add(NetworkUtils.numericToInetAddress("192.168.1.1"));//dns
		
		//IpConfiguration config = new IpConfiguration(IpAssignment.STATIC, ProxySettings.NONE, staticIpConfiguration, null);
		//IEthernetManager mEthernet = IEthernetManager.Stub.asInterface(binder);
		//mEthernet.setConfiguration(config);
		
		//System.out.println("mEthernet.setConfiguration" + mEthernet.isAvailable());

	}
}
