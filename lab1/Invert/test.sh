#!/bin/bash

PROGRAM="${1//\"}"

print_error() {
    echo "$1"
    exit 1
}

if [ -z "$PROGRAM" ]
then
    print_error "You need to specify program"
fi

"$PROGRAM" -h > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
fi

"$PROGRAM" < input/valid > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
fi

"$PROGRAM" input/valid > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
fi

"$PROGRAM" input/file-not-exist > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with non-existed file"
fi

"$PROGRAM" input/letter > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with invalid letter"
fi

"$PROGRAM" input/non-invertable > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with non-invertable matrix"
fi

"$PROGRAM" input/real-number > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with real-number matrix"
fi

"$PROGRAM" input/less-column > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong column matrix"
fi

"$PROGRAM" input/less-row > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong row matrix"
fi

"$PROGRAM" input/more-row > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong row matrix"
fi

"$PROGRAM" input/more-column > /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong column matrix"
fi

echo "OK"
exit 0