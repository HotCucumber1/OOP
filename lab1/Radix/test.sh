#!/bin/bash

PROGRAM="${1//\"}"

BIN_RADIX=2
DEC_RADIX=10
HEX_RADIX=16
INVALID_MAX_RADIX=37
INVALID_MIN_RADIX=1

VALID_POS_NUMBER=42
VALID_NEG_NUMBER=-42
VALID_HEX_NUMBER=F4
ZERO=0

INVALID_LETTER_DIGIT=3a
INVALID_HEX_DIGIT=G

VALID_POS_DEC_TO_HEC=2A
VALID_NEG_DEC_TO_HEC=-2A

VALID_POS_DEC_TO_BIN=101010
VALID_POS_HEX_TO_DEC=244

MAX_INT=2147483647
MIN_INT=-2147483647

POS_HEX_MAX_INT=7FFFFFFF
NEG_HEX_MAX_INT=-7FFFFFFF


print_error() {
    echo "$1"
    exit 1
}

assertEquals() {
  if [ $1 != $2 ]
  then
     print_error "Wrong answer: $1 <> $2"
  fi
}

if [ -z "$PROGRAM" ]
then
    print_error "You need to specify program"
fi

answer=$("$PROGRAM" $HEX_RADIX)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with wrong argument number"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with wrong argument number"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $VALID_HEX_NUMBER)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with wrong radix"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX $VALID_HEX_NUMBER)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertEquals "$answer" "$VALID_POS_HEX_TO_DEC"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $VALID_POS_NUMBER)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertEquals "$answer" "$VALID_POS_DEC_TO_HEC"
fi

answer=$("$PROGRAM" $DEC_RADIX $BIN_RADIX $VALID_POS_NUMBER)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertEquals "$answer" "$VALID_POS_DEC_TO_BIN"
fi

answer=$("$PROGRAM" $DEC_RADIX $INVALID_MAX_RADIX $VALID_POS_NUMBER)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid radix"
fi

answer=$("$PROGRAM" $INVALID_MIN_RADIX $INVALID_MAX_RADIX $VALID_POS_NUMBER)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid radix"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $VALID_NEG_NUMBER)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with negative number"
else
    assertEquals "$answer" "$VALID_NEG_DEC_TO_HEC"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX $VALID_NEG_DEC_TO_HEC)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with negative number"
else
    assertEquals "$answer" "$VALID_NEG_NUMBER"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $ZERO)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with zero number"
else
    assertEquals "$answer" "$ZERO"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX $INVALID_HEX_DIGIT)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with zero number"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX $INVALID_HEX_DIGIT)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid hex"
fi

answer=$("$PROGRAM" $HEX_RADIX $DEC_RADIX $INVALID_LETTER_DIGIT)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid digit"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $MAX_INT)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with overflow"
else
    assertEquals "$answer" "$POS_HEX_MAX_INT"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $MAX_INT)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with overflow"
else
    assertEquals "$answer" "$POS_HEX_MAX_INT"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $MIN_INT)
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with overflow"
else
    assertEquals "$answer" "$NEG_HEX_MAX_INT"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $MAX_INT+1)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with overflow"
fi

answer=$("$PROGRAM" $DEC_RADIX $HEX_RADIX $MIN_INT-1)
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with overflow"
fi

echo "OK"
echo""
exit 0
