#!/bin/bash
set -ex

TESTS=./testsuite
BIN=./test_portable_binary_archive_symmetry

for file in $(ls $TESTS); do $BIN $TESTS/$file; done

set +ex
