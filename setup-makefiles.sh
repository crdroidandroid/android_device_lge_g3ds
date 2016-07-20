#!/bin/bash

set -e

export VENDOR=lge
export DEVICE=d857
./../../$VENDOR/g3-common/setup-makefiles.sh $@
