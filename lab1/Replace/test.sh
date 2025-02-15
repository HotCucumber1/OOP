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

"$PROGRAM" data/fox.txt output/fox.txt bird cat
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertFilesEqual output/fox.txt data/right_output/fox-out
fi

"$PROGRAM" data/fox-replace-dog-with-cat.txt output/fox-replace-dog-with-cat.txt dog cat
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertFilesEqual output/fox-replace-dog-with-cat.txt data/right_output/fox-replace-dog-with-cat-out
fi

"$PROGRAM" data/test-more-than-one-string.txt output/test-more-than-one-string.txt ma mama
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertFilesEqual output/test-more-than-one-string.txt data/right_output/more-than-one-string-out
fi

"$PROGRAM" -h > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid help flag"
fi

"$PROGRAM" data/not-existed-file output/output1.txt ma mama > /dev/null
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid file"
fi

"$PROGRAM" data/test-more-than-one-string.txt output/output1.txt ma > /dev/null
if [ $? -eq 0 ]
then
    print_error "Program testing failed: Program failed with invalid arguments"
fi

"$PROGRAM" < data/test-valid-args.txt > output/valid-args
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid arguments"
else
    assertFilesEqual output/valid-args data/right_output/valid-args-out
fi

"$PROGRAM" < data/test-empty-search.txt > output/test-empty-search
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with empty search"
else
    assertFilesEqual output/test-empty-search data/right_output/empty-search-out
fi

"$PROGRAM" < data/test-empty-replace.txt > output/test-empty-replace
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with empty replace"
else
    assertFilesEqual output/test-empty-replace data/right_output/empty-replace-out
fi

"$PROGRAM" < data/test-empty-subject > output/test-empty-subject
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with empty subject"
else
    assertFilesEqual output/test-empty-subject data/right_output/error-out
fi

"$PROGRAM" < data/test-empty-input > output/test-empty-input
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with empty input"
else
    assertFilesEqual output/test-empty-input data/right_output/error-out
fi

echo "OK"
exit 0
