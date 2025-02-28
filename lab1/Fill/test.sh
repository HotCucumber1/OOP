#!/bin/bash

source ../../base-test.sh

"$PROGRAM" tests/non-exist output/tests/closed >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with non-existed file"
fi

"$PROGRAM" < tests/closed > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with CLI input"
fi

"$PROGRAM" -h > /dev/null
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with help calling"
fi

"$PROGRAM" tests/non-exist >> /dev/null
if [ $? -ne 1 ]
then
    print_error "Program testing failed: Program failed with wrong arguments number"
fi

"$PROGRAM" tests/closed output/tests/closed
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with valid files"
else
    assertFilesEqual output/correct/closed output/tests/closed
fi

"$PROGRAM" tests/full output/tests/full
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with full-free field"
else
    assertFilesEqual output/correct/full output/tests/full
fi

"$PROGRAM" tests/islands output/tests/islands
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with more than one islands"
else
    assertFilesEqual output/correct/islands output/tests/islands
fi

"$PROGRAM" tests/lots-of-start-points output/tests/lots-of-start-points
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with lots-of-start-points"
else
    assertFilesEqual output/correct/lots-of-start-points output/tests/lots-of-start-points
fi

"$PROGRAM" tests/no-start-points output/tests/no-start-points
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with no-start-points"
else
    assertFilesEqual output/correct/no-start-points output/tests/no-start-points
fi

"$PROGRAM" tests/unclosed output/tests/unclosed
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with unclosed island"
else
    assertFilesEqual output/correct/unclosed output/tests/unclosed
fi

"$PROGRAM" tests/unlimit-and-outside output/tests/unlimit-and-outside
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with unlimit and outside area"
else
    assertFilesEqual output/correct/unlimit-and-outside output/tests/unlimit-and-outside
fi

"$PROGRAM" tests/near-start-points output/tests/near-start-points
if [ $? -ne 0 ]
then
    print_error "Program testing failed: Program failed with near start points"
else
    assertFilesEqual output/correct/near-start-points output/tests/near-start-points
fi

echo "Test: OK"
exit 0