#
# System properties for g3ds
#

# Radio
PRODUCT_PROPERTY_OVERRIDES += \
    rild.libpath=/vendor/lib/libril-qc-qmi-1.so \
    ro.telephony.call_ring.multiple=0 \
    ro.multisim.set_audio_params=true \
    persist.radio.multisim.config=dsda \
