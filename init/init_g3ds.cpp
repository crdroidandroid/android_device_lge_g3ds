/*
   Copyright (C) 2016, The CyanogenMod Project
   Copyright (C) 2017-2020, The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include <vector>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

#include <android-base/properties.h>
#include <android-base/logging.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using android::init::property_set;

std::vector<std::string> ro_product_props_default_source_order = {
    ".",
    "product.",
    "product_services.",
    "odm.",
    "vendor.",
    "system.",
};

void property_override(char const prop[], char const value[], bool add = true)
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else if (add)
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void cdma_properties()
{
    property_set("ro.telephony.default_cdma_sub", "0");
    property_set("ro.telephony.default_network", "10,1");
    property_set("ro.telephony.get_imsi_from_sim", "true");
    property_set("telephony.lteOnCdmaDevice", "1");
}

void gsm_properties(char const default_network[])
{
    property_set("ro.telephony.default_network", default_network);
    property_set("telephony.lteOnGsmDevice", "1");
}

void vendor_load_properties()
{

    std::string serialno;
    std::string device;

    const auto set_ro_build_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro." + source + "build." + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    const auto set_ro_product_prop = [](const std::string &source,
            const std::string &prop, const std::string &value) {
        auto prop_name = "ro.product." + source + prop;
        property_override(prop_name.c_str(), value.c_str(), false);
    };

    serialno = GetProperty("ro.boot.serialno", "");

    if (serialno == "D856") {
        /* CIS */
        gsm_properties("9,1");
        property_override("ro.build.description", "g3_open_cis-user 6.0 MRA58K 16228163339a2 release-keys");
        for (const auto &source : ro_product_props_default_source_order ) {
            set_ro_build_prop(source, "fingerprint", "lge/g3_open_cis/g3:6.0/MRA58K/16228163339a2:user/release-keys");
            set_ro_product_prop(source, "device", "lg_d856");
            set_ro_product_prop(source, "model", "LG-D856");
        }
    } else if (serialno == "D857") {
        /* CHINA_OPEN_LTE */
        gsm_properties("20,1");
        property_override("ro.build.description", "g3_open_cn-user 5.0.1 LRX22G 152311653f5c9 release-keys");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "lge/g3_open_cn/g3:5.0.1/LRX22G/152311653f5c9:user/release-keys");
            set_ro_product_prop(source, "device", "lg_d857");
            set_ro_product_prop(source, "model", "LG-D857");
        }
    } else if (serialno == "D858HK") {
        /* HONGKONG */
        gsm_properties("20,1");
        property_override("ro.build.description", "g3_open_hk-user 6.0 MRA58K 160331641f312 release-keys");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "lge/g3_open_hk/g3:6.0/MRA58K/160331641f312:user/release-keys");
            set_ro_product_prop(source, "device", "lg_d858hk");
            set_ro_product_prop(source, "model", "LG-D858HK");
        }
    } else if (serialno == "D858") {
        /* CHINA_MOBILE_LTE */
        gsm_properties("20,1");
        property_override("ro.build.description", "g3_cmcc_cn-user 5.0.1 LRX22G 1523117098b82 release-keys");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "lge/g3_cmcc_cn/g3:5.0.1/LRX22G/1523117098b82:user/release-keys");
            set_ro_product_prop(source, "device", "lg_d858");
            set_ro_product_prop(source, "model", "LG-D858");
        }
    } else if (serialno == "D859") {
        /* CHINA_TELECOM_LTE */
        cdma_properties();
        property_override("ro.build.description", "g3_ctc_cn-user 5.0.1 LRX22G 152311713704b release-keys");
        for (const auto &source : ro_product_props_default_source_order) {
            set_ro_build_prop(source, "fingerprint", "lge/g3_ctc_cn/g3:5.0.1/LRX22G/152311713704b:user/release-keys");
            set_ro_product_prop(source, "device", "lg_d859");
            set_ro_product_prop(source, "model", "LG-D859");
        }
    }

    device = GetProperty("ro.product.device", "");
    LOG(INFO) << "Found serialno id '" << serialno.c_str() << "'. Setting build properties for '" << device.c_str() << "'.\n";
}
