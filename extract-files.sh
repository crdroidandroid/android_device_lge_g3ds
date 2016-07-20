#!/bin/sh

set -e

export VENDOR=lge
export DEVICE=d857
./../../$VENDOR/g3-common/extract-files.sh $@
