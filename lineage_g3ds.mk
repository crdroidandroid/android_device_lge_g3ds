$(call inherit-product, device/lge/g3ds/full_g3ds.mk)

# Inherit some common Lineage stuff.
$(call inherit-product, vendor/lineage/config/common_full_phone.mk)

PRODUCT_NAME := lineage_g3ds

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRODUCT_DEVICE="g3"
