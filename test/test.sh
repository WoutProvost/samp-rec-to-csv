#!/bin/bash

# Declare variables
ANSI_RESET=\\e[0m
ANSI_RED=\\e[31m
ANSI_GREEN=\\e[32m
DIR_EXAMPLE=../examples
DIR_REC2CSV=../test/rec2csv-tests
DIR_CSV2REC=../test/csv2rec-tests

# Subroutines
function error() {
	echo -e "$ANSI_RED"FAIL:"$ANSI_RESET" $1.
}
function cleanup {
	rm -rf $DIR_REC2CSV $DIR_CSV2REC
	exit 0
}

# Go to directory of script
cd $(dirname "${BASH_SOURCE[0]}")

# Go to build directory
cd ../build

# Convert example .rec files to .csv and back to .rec
./rec2csv $DIR_EXAMPLE/* $DIR_REC2CSV >> /dev/null
./csv2rec $DIR_REC2CSV/* $DIR_CSV2REC >> /dev/null

# Count if input and both output folders contain same amount of files
count_example=$(ls $DIR_EXAMPLE | wc -l)
if [ $count_example -ne $(ls $DIR_REC2CSV | wc -l) ] || [ $count_example -ne $(ls $DIR_CSV2REC | wc -l) ]; then
	error "Unequal amount of files"
	cleanup
fi

# Check if conversion round trip worked without any differences
success=0
for f in $DIR_EXAMPLE/*; do
	f2=$DIR_CSV2REC/$(basename $f)
	if ! [ -z "$(diff $f $f2)" ]; then
		error "Files $f and $f2 are not equal"
	else
		echo -e "$ANSI_GREEN"SUCCESS:"$ANSI_RESET" Files $f and $f2 are equal.
		((success++))
	fi
done

# Print summary
echo -n "==> "
if [ $success -eq $count_example ]; then
	echo -e "$ANSI_GREEN"SUCCESS:"$ANSI_RESET" Succesfully converted $success/$count_example files.
else
	error "Failed to successfully convert $((count_example-success))/$count_example files"
fi

# Remove temporary directories
cleanup