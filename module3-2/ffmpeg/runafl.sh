#!/bin/bash

AFL_I_DONT_CARE_ABOUT_MISSING_CRASHES=1 AFL_SKIP_CPUFREQ=1 afl-fuzz -i corpus -o output -n ./ffmpeg -i sig.wav -f null new.wav
