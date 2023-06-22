#!/bin/sh
set -e
LD_LIBRARY_PATH="`dirname "$0"`" exec ./example1 "$@"
