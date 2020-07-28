#!/bin/bash

ANDROID_PATH=$ANDROID_BUILD_TOP

cp init.mt6735.rc $ANDROID_PATH/device/mediatek/mt6735/init.mt6735.rc
cp device2.mk $ANDROID_PATH/device/mediatek/mt6735/device.mk
cp satfi.te $ANDROID_PATH/system/sepolicy/satfi.te
cp pppd.te $ANDROID_PATH/system/sepolicy/pppd.te
cp file_contexts $ANDROID_PATH/system/sepolicy/file_contexts
cp device.mk $ANDROID_PATH/device/lentek/len6737t_66_sh_n/device.mk
cp ProjectConfig.mk $ANDROID_PATH/device/lentek/len6737t_66_sh_n/ProjectConfig.mk
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
cp AudioSystem.java $ANDROID_PATH/frameworks/base/media/java/android/media/AudioSystem.java
cp pseudo_mnl.c $ANDROID_PATH/vendor/mediatek/proprietary/hardware/connectivity/gps/mtk_mnld/mnl/src/pseudo_mnl.c

cp kd_sensorlist.c $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/imgsensor/src/mt6735/kd_sensorlist.c
cp len6737t_66_sh_n_defconfig $ANDROID_PATH/kernel-3.18/arch/arm64/configs/len6737t_66_sh_n_defconfig
cp n_gsm.c $ANDROID_PATH/kernel-3.18/drivers/tty/n_gsm.c

cp mt_auxadc.c $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/auxadc/mt_auxadc.c
cp dm9051.c $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/dm9051/dm9051.c
cp spi.c $ANDROID_PATH/kernel-3.18/drivers/spi/mediatek/mt6735/spi.c

cp custom_MemoryDevice.h $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/len6737t_66_sh_n/inc/custom_MemoryDevice.h
cp MemoryDeviceList_MT6737T.xls $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/preloader/tools/emigen/MT6735/MemoryDeviceList_MT6737T.xls

cp AndroidManifest.xml $ANDROID_PATH/packages/apps/Settings/AndroidManifest.xml
cp BootFinishBroadcastReceiver.java $ANDROID_PATH/packages/apps/Settings/src/com/mediatek/settings/BootFinishBroadcastReceiver.java

mkdir -p $ANDROID_PATH/packages/apps/Settings/src/com/mediatek/sim
cp IMEIUtils.java $ANDROID_PATH/packages/apps/Settings/src/com/mediatek/sim/IMEIUtils.java

cp codegen.dws $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/lk/target/len6737t_66_sh_n/dct/dct/codegen.dws

