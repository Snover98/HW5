#!/bin/bash

#	link to Makefile:
makefileurl="https://webcourse.cs.technion.ac.il/236360/Winter2018-2019/hw/WCFiles/Makefile"
#	link to tests:
testsurl="https://webcourse.cs.technion.ac.il/236360/Winter2018-2019/hw/WCFiles/hw5-tests.zip"
#	link to spim:
spimurl="https://webcourse.cs.technion.ac.il/236360/Winter2018-2019/hw/WCFiles/spim.zip"
#	number of tests:
numtests=3

hostname="csl2"
hostname2="csl2b"
tmpdir="selfcheck_tmp"

if [ $( hostname ) != "$hostname" ]
	then
		if [ $( hostname ) != "$hostname2" ]
			then
				echo "This script is only intended to run on "$hostname" or "$hostname2"!"
				exit
		fi
fi

if [ -z "$1" ]
	then
		echo "Usage: ./"$( basename "$0" )" <your submission zip file>"
		exit
fi

if [ ! -f "$1" ]
	then
		echo "Submission zip file not found!"
		exit
fi

rm -rf "$tmpdir" &> /dev/null
if [ -d "$tmpdir" ]
	then
		echo "Cannot clear tmp directory. Please delete '"$tmpdir"' manually and try again"
		exit
fi
mkdir "$tmpdir" &> /dev/null

unzip "$1" -d "$tmpdir" &> /dev/null
if [[ $? != 0 ]] 
	then
		echo "Unable to unzip submission file!"
		exit
fi

cd "$tmpdir"

wget --no-check-certificate "$makefileurl" &> /dev/null
if [ ! -f Makefile ]
	then
		echo "Unable to download Makefile!"
		exit
fi

make &> /dev/null
if [[ $? != 0 ]] 
	then
		echo "Cannot build submission!"
		exit
fi

wget --no-check-certificate "$testsurl" &> /dev/null
if [ ! -f Makefile ]
	then
		echo "Unable to download tests!"
		exit
fi

unzip $( basename "$testsurl" ) &> /dev/null
if [[ $? != 0 ]] 
	then
		echo "Unable to unzip tests!"
		exit
fi

wget --no-check-certificate "$spimurl" &> /dev/null
if [ ! -f Makefile ]
	then
		echo "Unable to download tests!"
		exit
fi

unzip $( basename "$spimurl" ) &> /dev/null
if [[ $? != 0 ]] 
	then
		echo "Unable to unzip spim!"
		exit
fi

i="1"
while [ $i -le $numtests ]
	do
		./hw5 < t$i.in 2>&1 > t$i.il
		./spim -file t$i.il > t$i.res
		diff t$i.res t$i.out &> /dev/null
		if [[ $? != 0 ]] 
			then
				echo "Failed test #"$i"!"
				exit
		fi
		i=$[$i+1]
done

cd - &> /dev/null
rm -rf "$tmpdir"

echo "Ok to submit :)"
exit
