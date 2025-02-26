#!/bin/bash

PROGRAM="${1//\"}"

print_error() {
    echo "$1"
    exit 1
}

assertFilesEqual() {
    if ! cmp -s "$1" "$2"
    then
        print_error "Program testing failed: <$1> and <$2> are not equal"
    fi
}

if [ -z "$PROGRAM" ]
then
    print_error "You need to specify program"
fi