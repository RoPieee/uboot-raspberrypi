/* DO NOT EDIT! */
/* This file is originally from the Yocto layer: https://github.com/mendersoftware/meta-mender/blob/master/meta-mender-core/recipes-bsp/u-boot/u-boot-mender-common.inc */

#ifndef HEADER_CONFIG_MENDER_DEFINES_H
#define HEADER_CONFIG_MENDER_DEFINES_H

/* Shell variables */
#define MENDER_BOOT_PART_NUMBER 1 
#define MENDER_ROOTFS_PART_A_NUMBER 2
#define MENDER_ROOTFS_PART_B_NUMBER 3
#define MENDER_UBOOT_STORAGE_INTERFACE "mmc"
#define MENDER_UBOOT_STORAGE_DEVICE 0

/* BB variables. */
#define MENDER_STORAGE_DEVICE_BASE "/dev/mmcblk0p"
#define MENDER_UBOOT_ENV_STORAGE_DEVICE_OFFSET_1 0x4000
#define MENDER_UBOOT_ENV_STORAGE_DEVICE_OFFSET_2 0x8000
#define MENDER_ROOTFS_PART_A_NAME "${MENDER_ROOTFS_PART_A_NAME}"
#define MENDER_ROOTFS_PART_B_NAME "${MENDER_ROOTFS_PART_B_NAME}"

/* For sanity checks. */
#define MENDER_BOOTENV_SIZE 0x4000

#define MENDER_BOOT_KERNEL_TYPE "bootz"
#define MENDER_KERNEL_NAME "kernel7.img"
#define MENDER_DTB_NAME "$MENDER_DTB_NAME"
#define MENDER_UBOOT_PRE_SETUP_COMMANDS "$MENDER_UBOOT_PRE_SETUP_COMMANDS"
#define MENDER_UBOOT_POST_SETUP_COMMANDS "$MENDER_UBOOT_POST_SETUP_COMMANDS"

#endif
