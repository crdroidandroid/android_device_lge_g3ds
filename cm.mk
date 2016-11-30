$(call inherit-product, device/lge/g3ds/full_g3ds.mk)

# Inherit some common CM stuff.
$(call inherit-product, vendor/cm/config/common_full_phone.mk)

PRODUCT_NAME := cm_g3ds

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_DEVICE="g3"
