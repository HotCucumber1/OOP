#!/bin/bash

source ../../base-test.sh

MAX_VALID_KEY=255
MIN_VALID_KEY=0
VALID_KEY=42
INVALID_HEX_KEY=4A
TOO_LARGE_KEY=256
TOO_SMALL_KEY=-1

"$PROGRAM" crypt tests/non-exist output/tests/closed $MAX_VALID_KEY >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with non-existed file"
fi

"$PROGRAM" crypt tests/non-exist output/tests/closed >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong arguments number"
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $INVALID_HEX_KEY >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with invalid hex key"
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $TOO_LARGE_KEY >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with too large key"
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $TOO_SMALL_KEY >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with too small key"
fi

"$PROGRAM" ivalid-action tests/one-line output/one-line-cripted $VALID_KEY >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with invalid action"
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $VALID_KEY >> /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid key"
else
    "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $VALID_KEY >> /dev/null
    assertFilesEqual tests/one-line output/one-line-decripted
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $MAX_VALID_KEY >> /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with max valid key"
else
    "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $MAX_VALID_KEY >> /dev/null
    assertFilesEqual tests/one-line output/one-line-decripted
fi

"$PROGRAM" crypt tests/one-line output/one-line-cripted $MIN_VALID_KEY >> /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with min valid key"
else
    "$PROGRAM" decrypt output/one-line-cripted output/one-line-decripted $MIN_VALID_KEY >> /dev/null
    assertFilesEqual tests/one-line output/one-line-decripted
fi

"$PROGRAM" crypt tests/empty-file output/empty-file-cripted $VALID_KEY >> /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with empty file"
else
    "$PROGRAM" decrypt output/empty-file-cripted output/empty-file-decripted $MIN_VALID_KEY >> /dev/null
    assertFilesEqual tests/empty-file output/empty-file-decripted
fi

"$PROGRAM" crypt tests/lots-of-lines output/lots-of-lines-cripted $VALID_KEY >> /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with file with more than 1 strings"
else
    "$PROGRAM" decrypt output/lots-of-lines-cripted output/lots-of-lines-decripted $VALID_KEY >> /dev/null
    assertFilesEqual tests/lots-of-lines output/lots-of-lines-decripted
fi

echo "Test: OK"
exit 0