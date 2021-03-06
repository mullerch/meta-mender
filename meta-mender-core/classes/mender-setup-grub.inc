EXTRA_IMAGEDEPENDS_append_mender-grub = " grub-efi"

# If we are using efi-secure-boot from the meta-secure-core layer, then it
# handles adding these files.
IMAGE_BOOT_FILES_append = '${@bb.utils.contains("DISTRO_FEATURES", "efi-secure-boot", "", " ${_MENDER_EFI_BOOT_FILE}", d)}'

_MENDER_EFI_BOOT_FILE = ""
_MENDER_EFI_BOOT_FILE_mender-grub_arm = "grub-efi-bootarm.efi;EFI/BOOT/bootarm.efi"
_MENDER_EFI_BOOT_FILE_mender-grub_x86 = "grub-efi-bootia32.efi;EFI/BOOT/bootia32.efi"
_MENDER_EFI_BOOT_FILE_mender-grub_x86-64 = "grub-efi-bootx64.efi;EFI/BOOT/bootx64.efi"
_MENDER_EFI_BOOT_FILE_mender-grub_aarch64 = "grub-efi-bootaa64.efi;EFI/BOOT/bootaa64.efi"
_MENDER_EFI_BOOT_FILE_mender-grub_mender-bios = ""

# We want to use upstream grub variants if possible. However, we have recipes
# that will be enabled in some configurations where COMPATIBLE_HOSTS doesn't
# match for the upstream recipe. See the recipes-bsp/grub folder.
PREFERRED_PROVIDER_grub-efi ?= "grub-efi"
PREFERRED_RPROVIDER_grub-efi ?= "grub-efi"
PREFERRED_PROVIDER_grub-editenv ?= "grub"
PREFERRED_RPROVIDER_grub-editenv ?= "grub"

PREFERRED_PROVIDER_virtual/grub-bootconf ?= "grub-mender-grubenv"
PREFERRED_RPROVIDER_virtual/grub-bootconf ?= "grub-mender-grubenv"

# Set EFI_PROVIDER.  Not all MACHINE configs use it but notably
# intel-corei7-64 does and without this we use the default of systemd-boot.
EFI_PROVIDER_mender-grub="grub-efi"

python() {
    if d.getVar('MENDER_GRUB_STORAGE_DEVICE'):
        bb.fatal("MENDER_GRUB_STORAGE_DEVICE is deprecated. This is now dynamically determined at runtime.")
}
