# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_script_asm.sh                                 :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/04/10 22:48:52 by skpn              #+#    #+#              #
#    Updated: 2020/04/21 19:16:49 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

usage_msg="sh script_asm binary_name [options] path/to/file[s].s\n"
usage_msg+="options:\n"
usage_msg+="\t-show_err: show diff and exit script on error\n"
usage_msg+="\t-show_out: show what the exec prints to stdout\n"

output_dir=/tmp
parent_dir=$HOME/corewar
if [ ! -d $parent_dir ]; then
	echo "Parent folder not found, please check line 19"
	exit
fi
ref_dir_cor=$parent_dir/cwr_checker/champ/cor_files
exec_dir=$parent_dir/cwr_asm
exec=$exec_dir/asm
ref_exec=$parent_dir/cwr_resources/asm

args=("$@")
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

if [ "$#" -lt 2 ]; then
	echo -e $usage_msg
	exit 1
fi

make -C $exec_dir &> $output_dir/check_make

if grep -q -e "Error" -e "error" $output_dir/check_make; then
	cat $output_dir/check_make
	exit
else
	rm -rf $output_dir/check_make
fi


######## PARSE ARGS #########

idx=0

while [ $idx -lt "$#" ]
do
##
	arg=${args[$idx]}
##
	if [ $arg == "-show_err" ]; then
		show_err=1
		echo show err: $show_err
##
	elif [ $arg == "-show_out" ]; then
		show_out=1
##
	elif [ ! -f $arg ]; then
		echo "File '"$arg"'" not found
		exit 1
##
	elif [ ${arg: -2} != ".s" ]; then
		echo bad file extension: $arg
##
	elif [ ${#arg} -lt 3 ]; then
		echo file name too short: $(arg $s_file)
##
	else
		s_files_array+=($arg)
##
	fi
##
	idx=$(($idx + 1))
##
done


######## LAUNCH CHECKS #########

rm -f $output_dir/failed_tests > /dev/null

current_check=0
max_check=${#s_files_array[@]}
if [ $max_check -lt 1 ]; then
	echo no valid test files
	exit
fi
score=0
echo "failed tests:" > $output_dir/failed_tests
failed_nb=0

while [ $current_check -lt $max_check ]
do
	s_file=${s_files_array[$current_check]}
	current_check=$(($current_check + 1))

## GET NAMES
	shortname=$(basename $s_file)
	shortname=${shortname%.*}
	cor_file="$shortname.cor"
	echo -ne "\n[$current_check / $max_check]: $shortname - "

## GET FOLDERS
	ref_dir_s=${s_file%/*}
	check_dir=$output_dir/$shortname
	mkdir -p $check_dir
	rm -rf $check_dir/* &> /dev/null

## GET COR FILES
	$exec $s_file &> $check_dir/test_exec
	if grep -q -e "SEGV" -e "leak" $check_dir/test_exec; then
		cat $output_dir/test_exec
		exit
	fi
	mv $ref_dir_s/$cor_file $check_dir/test_cor
	$ref_exec $s_file &> $check_dir/ref_exec
	mv $ref_dir_s/$cor_file $check_dir/ref_cor

## GET HEXDUMPS
	hexdump $check_dir/test_cor > $check_dir/test_hex
	hexdump $check_dir/ref_cor > $check_dir/ref_hex

## CHECK RESULTS
	diff $check_dir/test_hex $check_dir/ref_hex > $check_dir/diff
	if [ -s $check_dir/diff ]; then
		echo -e $RED"ERROR"$NC
		echo " - " $s_file >> $output_dir/failed_tests
		failed_nb=$(($failed_nb + 1))
		if [ ! -z $show_err ]; then
			vim -O $check_dir/test_hex $check_dir/ref_hex $check_dir/diff
			exit
		fi
	else
		echo -e $GREEN"OK"$NC
		score=$(($score + 1))
	fi
	if [ ! -z $show_out ]; then
		cat $check_dir/test_exec
	fi
	echo -e "\n"
##
done

echo final score: [ $score / $max_check ]
if [ $failed_nb -gt 0 ]; then
	echo -ne $failed_nb " "
	cat $output_dir/failed_tests
fi
