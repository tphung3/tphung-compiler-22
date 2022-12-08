#!/bin/sh
declare -a arr=("good1 good2 good3 good4 good5 good6 good7 good8 good9 good10 good11 good12 good13 good14 good15 good16 good17 good18 good19 good20")
for good in codegen-book-tests/good*.bminor
do
    echo "---------------"
    echo $good
    if ./bminor -codegen $good "$good".s
    then
        echo "Good"; rm "$good".s
    else
        echo "Wrong"; rm "$good".s
        exit 1
    fi
done

for good in codegen-tests/good*.bminor
do
    echo "---------------"
    echo $good
    if ./bminor -codegen $good "$good".s
    then
        echo "Good"; rm "$good".s
    else
        echo "Wrong"; rm "$good".s
        exit 1
    fi
done

