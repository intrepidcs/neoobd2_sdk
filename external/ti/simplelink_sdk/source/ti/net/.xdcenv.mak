#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = /vagrant/Q4_04/sdk_root/kernel/tirtos/packages
override XDCROOT = /opt/ti/xdctools_3_50_04_43_core
override XDCBUILDCFG = /vagrant/Q4_04/sdk_root/source/ti/net/ns.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = TIPOSIX_REPO="/vagrant/Q4_04/sdk_root/source" ti.targets.arm.elf.M4="/opt/ti/ccs-latest/ccsv7/tools/compiler/ti-cgt-arm_16.9.6.LTS" gnu.targets.arm.M4="/opt/ti/ccs-latest/ccsv7/tools/compiler/gcc-arm-none-eabi-6-2017-q1-update" iar.targets.arm.M4="/opt/iar/arm/latest"
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = /vagrant/Q4_04/sdk_root/kernel/tirtos/packages;/opt/ti/xdctools_3_50_04_43_core/packages;../..
HOSTOS = Linux
endif
