#!/bin/sh

for good in printer-book-tests/good*.bminor
do
    echo $good
    ./bminor -print $good &> tmp1.bminor
    ./bminor -print tmp1.bminor &> tmp2.bminor
    res=$(diff tmp1.bminor tmp2.bminor)
    if [ ! $res ]
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done

for good in printer-tests/good*.bminor
do
    echo $good
    ./bminor -print $good &> tmp1.bminor
    ./bminor -print tmp1.bminor &> tmp2.bminor
    res=$(diff tmp1.bminor tmp2.bminor)
    if [ ! $res ]
    then 
        echo "Good"
    else
        echo "Wrong"
        exit 1
    fi
done

rm tmp1.bminor tmp2.bminor
