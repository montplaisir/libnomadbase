#!/bin/bash

# Argument 1: bin directory where the unit tests are compiled.
if [ "$1" == "" ]
then
    echo Usage: $0 \<BIN_TEST_DIR\>
    echo Example: $0 \$BUILD_DIR/test/bin
    exit
fi

BIN_TEST_DIR=$1

tput setaf 3; echo; echo "Running libnomadbase Unit tests"
for test in `ls $BIN_TEST_DIR | grep _unittest`
do
    tput setaf 2; test_failed=`$BIN_TEST_DIR/$test | grep FAILED`
    if [ "$test_failed" != "" ]
    then
        # Failure in red
        tput setaf 1; echo "$test failure"
    else
        # Success in green
        tput setaf 2; echo "$test success"
    fi
done

#reset color.
tput sgr0
