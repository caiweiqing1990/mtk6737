#!/bin/bash

ANDROID_PATH=$(pwd)/../../..

FILES_BAK=./files_bak

mkdir -p $FILES_BAK
cp $ANDROID_PATH/device/mediatek/mt6735/init.mt6735.rc $FILES_BAK/
cp $ANDROID_PATH/device/mediatek/mt6735/device.mk $FILES_BAK/device2.mk
cp $ANDROID_PATH/system/sepolicy/file_contexts $FILES_BAK/
cp $ANDROID_PATH/device/lentek/len6737t_66_sh_n/device.mk $FILES_BAK/
cp $ANDROID_PATH/device/lentek/len6737t_66_sh_n/ProjectConfig.mk $FILES_BAK/
cp $ANDROID_PATH/frameworks/opt/net/ethernet/java/com/android/server/ethernet/EthernetConfigStore.java $FILES_BAK/
cp $ANDROID_PATH/frameworks/base/media/java/android/media/AudioSystem.java $FILES_BAK/
cp $ANDROID_PATH/vendor/mediatek/proprietary/hardware/connectivity/gps/mtk_mnld/mnl/src/pseudo_mnl.c $FILES_BAK/

cp $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/imgsensor/src/mt6735/kd_sensorlist.c $FILES_BAK/
cp $ANDROID_PATH/kernel-3.18/arch/arm64/configs/len6737t_66_sh_n_defconfig $FILES_BAK/
cp $ANDROID_PATH/kernel-3.18/drivers/tty/n_gsm.c $FILES_BAK/

cp $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/auxadc/mt_auxadc.c $FILES_BAK/
cp $ANDROID_PATH/kernel-3.18/drivers/misc/mediatek/dm9051/dm9051.c $FILES_BAK/
cp $ANDROID_PATH/kernel-3.18/drivers/spi/mediatek/mt6735/spi.c $FILES_BAK/

cp $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/len6737t_66_sh_n/inc/custom_MemoryDevice.h $FILES_BAK/
cp $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/preloader/tools/emigen/MT6735/MemoryDeviceList_MT6737T.xls $FILES_BAK/

cp $ANDROID_PATH/packages/apps/Settings/AndroidManifest.xml $FILES_BAK/

cp $ANDROID_PATH/vendor/mediatek/proprietary/bootable/bootloader/lk/target/len6737t_66_sh_n/dct/dct/codegen.dws $FILES_BAK/

