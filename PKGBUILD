# U-Boot: Raspberry Pi
# Maintainer: Kevin Mihelich <kevin@archlinuxarm.org>

buildarch=12

pkgname=uboot-ropieee-pi3
pkgver=2018.07
pkgrel=10
pkgdesc="U-Boot for Raspberry Pi"
arch=('armv7h')
url='http://www.denx.de/wiki/U-Boot/WebHome'
license=('GPL')
backup=('boot/boot.txt' 'boot/boot.scr' 'boot/config.txt')
makedepends=('bc' 'dtc' 'git')
#conflicts_armv7h=('linux-raspberrypi')
source=("ftp://ftp.denx.de/pub/u-boot/u-boot-${pkgver/rc/-rc}.tar.bz2"
        '0001-arch-linux-arm-modifications.patch'
	'https://github.com/mendersoftware/meta-mender/raw/master/meta-mender-core/recipes-bsp/u-boot/patches/0001-Add-missing-header-which-fails-on-recent-GCC.patch'
	'https://github.com/mendersoftware/meta-mender/raw/master/meta-mender-core/recipes-bsp/u-boot/patches/0002-Generic-boot-code-for-Mender.patch'
	'https://github.com/mendersoftware/meta-mender/raw/master/meta-mender-core/recipes-bsp/u-boot/patches/0003-Integration-of-Mender-boot-code-into-U-Boot.patch'
	'https://github.com/mendersoftware/meta-mender/raw/master/meta-mender-core/recipes-bsp/u-boot/patches/0004-Disable-CONFIG_BOOTCOMMAND-and-enable-CONFIG_MENDER_.patch'
	'https://github.com/mendersoftware/meta-mender/raw/master/meta-mender-core/recipes-bsp/u-boot/patches/0006-env-Kconfig-Add-descriptions-so-environment-options-.patch'
        'boot.txt.v2'
        'boot.txt.v3'
	'fw_env.config'
        'mkscr')
md5sums=('2b8eaa30dd118b29889669070da22bb0'
         'f8ae1ac4c0bd70712a7cb36967ad35fb'
         '2f1a49f212b51e7937cda2ab67d503d9'
         'b8d86a3064db6433ee32a302e913b272'
         '9ec5ce95d5ec5631f026cd14e1ac964b'
         'f6904bf5cced09ad846ea3d2cffc8158'
         '1d33d038111fe551a9dc5f9a8e25affd'
         '315c82ddf099db367c8c510acfff51e4'
         'be8abe44b86d63428d7ac3acc64ee3bf'
         '065b382b171f9ceea93cc7a902a41aa9'
         '021623a04afd29ac3f368977140cfbfd')

prepare() {
  cd u-boot-${pkgver/rc/-rc}
 
  echo "pwd: $( pwd )"
  msg2 'Applying patches...'

# seems not necessary with 2018.07
#   patch -p1 < ../0001-arch-linux-arm-modifications.patch

   patch -p1 < ../0001-Add-missing-header-which-fails-on-recent-GCC.patch
   patch -p1 < ../0002-Generic-boot-code-for-Mender.patch
   patch -p1 < ../0003-Integration-of-Mender-boot-code-into-U-Boot.patch

# we don't want that for now, because with this patch we can't ue the boot.scr file anymore
#   patch -p1 < ../0004-Disable-CONFIG_BOOTCOMMAND-and-enable-CONFIG_MENDER_.patch

   patch -p1 < ../0006-env-Kconfig-Add-descriptions-so-environment-options-.patch

  cp ../../mender-patches/config_mender_defines.h include
  cp ../../mender-patches/mender_Kconfig_fragment . 

#  cp ../../common.h include/
}

build() {
  cd u-boot-${pkgver/rc/-rc}

  unset CFLAGS
  unset CXXFLAGS
  unset CPPFLAGS

  make distclean
  [[ $CARCH == "armv7h" ]] && make rpi_3_32b_config
  [[ $CARCH == "aarch64" ]] && make rpi_3_config
  echo 'CONFIG_IDENT_STRING=" RoPieee"'        >> .config
  echo 'CONFIG_BOOTCOUNT_LIMIT=y'              >> .config
  echo 'CONFIG_BOOTCOUNT_ENV=y'                >> .config
  echo '# CONFIG_BOOTCOUNT_GENERIC is not set' >> .config
  echo '# CONFIG_BOOTCOUNT_EXT is not set'     >> .config
  echo '# CONFIG_BOOTCOUNT_RAM is not set'     >> .config
  echo '# CONFIG_BOOTCOUNT_I2C is not set'     >> .config
  echo '# CONFIG_CMD_BOOTCOUNT is not set'     >> .config
  echo 'CONFIG_ENV_SIZE=0x4000'                >> .config

  # 20180802: experimental, let's see if we can make it work without the env file
  echo 'CONFIG_ENV_IS_IN_MMC=y'                >> .config
  echo '# CONFIG_ENV_IS_IN_FAT is not set'     >> .config

  make EXTRAVERSION=-${pkgrel}
  make envtools EXTRAVERSION=-${pkgrel}
}

package() {
  cd u-boot-${pkgver/rc/-rc}

  #mkdir -p "${pkgdir}"/boot
  mkdir -p "${pkgdir}"/uboot

  if [[ $CARCH == "armv7h" ]]; then
    cp u-boot.bin ${pkgdir}/uboot/kernel7.img
    cp ../boot.txt.v2 ../boot.txt
    echo "enable_uart=1" > ${pkgdir}/uboot/config.txt
  elif [[ $CARCH == "aarch64" ]]; then
    cp u-boot.bin ${pkgdir}/uboot/kernel8.img
    cp ../boot.txt.v3 ../boot.txt
  fi

  tools/mkimage -A arm -O linux -T script -C none -n "U-Boot boot script" -d ../boot.txt "${pkgdir}"/uboot/boot.scr
  cp ../{boot.txt,mkscr} "${pkgdir}"/uboot

  # and the tools
  install -dm755 ${pkgdir}/{usr/{bin,share/man/man1},etc}
  install -m755 {tools/dumpimage,tools/mkimage,tools/mkenvimage,tools/netconsole,tools/proftool,tools/env/fw_printenv} ${pkgdir}/usr/bin
  ln -s /usr/bin/fw_printenv ${pkgdir}/usr/bin/fw_setenv
  install -m644 ../fw_env.config ${pkgdir}/etc
  install -m644 doc/{mkimage,kwboot}.1 ${pkgdir}/usr/share/man/man1

  # finally create the env file
  dd if=/dev/zero of=${pkgdir}/uboot/uboot.env bs=18384 count=1
}
