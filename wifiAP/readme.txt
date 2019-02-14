开机将wifi配置为AP热点模式

增加注册广播BOOT_COMPLETED
packages/apps/Settings/AndroidManifest.xml

<!-- M: for RECEIVE_BOOT_COMPLETED @{ -->
<receiver android:name="com.mediatek.settings.BootFinishBroadcastReceiver" >
	<intent-filter android:priority="1000" >
		<action android:name="android.intent.action.BOOT_COMPLETED" />
		<action android:name="android.media.AUDIO_BECOMING_NOISY" />
	</intent-filter>
</receiver>

增加文件

packages/apps/Settings/src/com/mediatek/settings/BootFinishBroadcastReceiver.java
