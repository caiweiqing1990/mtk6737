#!/bin/bash

ANDROID_PATH=/home/book/work/XY3701_N0

cp init.mt6735.rc $ANDROID_PATH/device/mediatek/mt6735/init.mt6735.rc
cp device2.mk $ANDROID_PATH/device/mediatek/mt6735/device.mk
cp satfi.te $ANDROID_PATH/system/sepolicy/satfi.te
cp pppd.te $ANDROID_PATH/system/sepolicy/pppd.te
cp device.mk $ANDROID_PATH/device/lentek/len6737t_66_sh_n/device.mk
cp satbusy.wav $ANDROID_PATH/device/lentek/len6737t_66_sh_n/satbusy.wav
cp busy.wav $ANDROID_PATH/device/lentek/len6737t_66_sh_n/busy.wav
cp dudu.wav $ANDROID_PATH/device/lentek/len6737t_66_sh_n/dudu.wav
cp bohao.wav $ANDROID_PATH/device/lentek/len6737t_66_sh_n/bohao.wav
cp disconnect-chat $ANDROID_PATH/device/lentek/len6737t_66_sh_n/disconnect-chat
cp sat-chat $ANDROID_PATH/device/lentek/len6737t_66_sh_n/sat-chat
cp sat-dailer $ANDROID_PATH/device/lentek/len6737t_66_sh_n/sat-dailer
cp busybox $ANDROID_PATH/device/lentek/len6737t_66_sh_n/busybox
cp libTTUpdate.so $ANDROID_PATH/device/lentek/len6737t_66_sh_n/libTTUpdate.so
cp ipconfig.txt $ANDROID_PATH/device/lentek/len6737t_66_sh_n/ipconfig.txt
cp EthernetConfigStore.java $ANDROID_PATH/frameworks/opt/net/ethernet/java/com/android/server/ethernet/EthernetConfigStore.java

cp AndroidManifest.xml $ANDROID_PATH/packages/apps/Settings/AndroidManifest.xml
cp BootFinishBroadcastReceiver.java $ANDROID_PATH/packages/apps/Settings/src/com/mediatek/settings/BootFinishBroadcastReceiver.java
cp IMEIUtils.java $ANDROID_PATH/packages/apps/Settings/src/com/mediatek/sim/IMEIUtils.java
