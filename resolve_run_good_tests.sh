#!/bin/sh

for good in typecheck-book-tests/good*.bminor
do
    echo "---------------"
    echo $good
    if ./bminor -resolve $good
    then
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done

