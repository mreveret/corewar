# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    test_script_vm.sh                                  :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: skpn <skpn@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/21 11:31:03 by sikpenou          #+#    #+#              #
#    Updated: 2020/04/21 12:26:12 by skpn             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

output_dir=/tmp
parent_dir=$HOME/corewar
exec_dir=$(find $parent_dir -type d -name 'cwr_vm')
ref_dir=$(find $parent_dir -type d -name 'cwr_resources')
exec=$1

usage_msg="sh fight exec [options] path_to_champs/champs\n"
usage_msg="$usage_msg options:\n"
usage_msg="$usage_msg -s		: do not print Aff output\n"
usage_msg="$usage_msg -d N		: dump at cycle N\n"
usage_msg="$usage_msg -v N		: verbose (Zaz-like) level N, default is 31\n"
usage_msg="$usage_msg -time N	: timeout after N seconds, default is 60\n"
usage_msg="$usage_msg -nb N		: number of champs per fight ( >= 1 )\n"
usage_msg="$usage_msg -max N	: max number of fights ( >= 1 )\n"
usage_msg="$usage_msg -rand		: fighters are selected randomly\n"

args=("$@")
dump=-1
verbose=31
aff=1
champs_per_fight=4
max_fight=0
time_limit=60
random=0
GREEN='\033[0;32m'
NC='\033[0m'


######## PRE-CHECK #########

if [ "$#" -lt 2 ]; then
	echo -e $usage_msg
	exit 1
fi

make -C $exec_dir &> $output_dir/check_make

if grep -q -e "Error" -e "error" $output_dir/check_make; then
	cat $output_dir/check_make
	exit
fi

command -v timeout > $output_dir/check_timeout
if [ -s $output_dir/check_timeout ]; then
	time_cmd="timeout"
else
	command -v gtimeout > $output_dir/check_timeout
	if [ -s $output_dir/check_timeout ]; then
		time_cmd="gtimeout"
	else
		echo "missing timeout/gtimeout command"
		echo "for macs  : coreutils package missing, download command: brew install coreutils"
		echo "for linux : I don't know, it should be there... timeout deactivated, some fights can be very long"
		time_limit=""
	fi
fi

rm -rf $output_dir/check_* > /dev/null


######## PARSE ARGS #########

idx=1

while [ $idx -lt "$#" ]
do
##
	arg=${args[$idx]}
##
	if [ $arg == "-v" ]; then
		verbose=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-d" ]; then
		dump=${args[$(($idx+1))]}
		idx=$(($idx+1))
		if [ $dump < 0 ]; then
			echo bad dump option: $dump
			echo -e $usage_msg
			exit
		fi
##
	elif [ $arg == "-nb" ]; then
		champs_per_fight=${args[$(($idx+1))]}
		idx=$(($idx+1))
		if [ $champs_per_fight -lt 1 ]; then
			echo bad nb option: $champs_per_fight
			echo -e $usage_msg
			exit
		fi
##
	elif [ $arg == "-max" ]; then
		max_fight=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-time" ]; then
		time_limit=${args[$(($idx+1))]}
		idx=$(($idx+1))
##
	elif [ $arg == "-s" ]; then
		aff=0
##
	elif [ $arg == "-rand" ]; then
		random=1
##
	elif [ ! -f $arg ]; then
		echo "File '"$arg"'" not found
##
	elif [ ${arg: -2} == ".s" ]; then
		s_champs+=($arg)
##
	elif [ ${arg: -4} == ".cor" ]; then
		cor_champs+=($arg)
##
	else
		echo bad arg: $arg
		echo -e $usage_msg
		exit
##
	fi
##
	idx=$(($idx + 1))
##
done


######## COMPILE S_CHAMPS #########

idx=0

while [ $idx -lt ${#s_champs[@]} ]
do
##
	arg=${s_champs[$idx]}
##
	$ref_dir/asm $arg > $output_dir/check_asm
##
	if ! grep -q "Writing" $output_dir/check_asm; then
		echo "champ "$arg" is invalid"
		cat $output_dir/check_asm
	else
		cor_champs+=(${arg/\.s/\.cor})
	fi
##
	idx=$(($idx + 1))
##
done

if [ ${#cor_champs[@]} -lt 1 ]; then
	echo "no valid champion"
	exit
elif [ ${#cor_champs[@]} -lt $champs_per_fight ]; then
	echo "not enough champs, lower nb option or add champs"
	exit
fi

rm -rf $output_dir/check_*


######## LAUNCH FIGHTS #########

idx=0
current_fight=0
nb_cor_champs=${#cor_champs[@]}
ordered_launch=0


if [ $max_fight -eq 0 ]; then
	max_fight=$(($nb_cor_champs / $champs_per_fight))
fi

rm -f $output_dir/failed > /dev/null

while [ $current_fight -lt $max_fight ]
do
	current_fight=$(($current_fight + 1))
	echo -e "\nfight [$current_fight / $max_fight]"
	fight_dir=$output_dir/fight_$current_fight
	mkdir -p $fight_dir
	rm -rf $fight_dir/*

## GET FIGHTERS
	fighters=()
	current_fighter=0
	while [ $current_fighter -lt $champs_per_fight ]
	do
		if [ $random -eq 0 ]; then
			fighters+=${cor_champs[$idx]}
		else
			fighters+=${cor_champs[$(($RANDOM % $nb_cor_champs))]}
		fi
		fighters+=" "
		idx=$(($idx + 1))
		if [ $idx -eq $nb_cor_champs ]; then
			idx=$((0 + $ordered_launch))
			ordered_launch=$(($ordered_launch + 1))
		fi
		current_fighter=$(($current_fighter + 1))
	done

## GET ARGS
	corewar_args=""
	if [ $aff == 1 ]; then
		corewar_args="${corewar_args}-a "
	fi
	if [ $dump -gt 0 ]; then
		corewar_args="${corewar_args}-d $dump "
	fi
	if [ $verbose -gt 0 ]; then
		corewar_args="${corewar_args}-v $verbose "
	fi
	corewar_args="${corewar_args}${fighters[@]}"

## GET OUTPUT
	timedout=0
	echo line 227: $time_cmd $time_limit $ref_dir/corewar $corewar_args
	$time_cmd $time_limit $ref_dir/corewar $corewar_args > $fight_dir/ref
	if [ -z $time_cmd -a $? == 124 ]; then
		echo "resource_corewar timed out"
		timedout=1
	fi
	$time_cmd $time_limit ./$exec $corewar_args > $fight_dir/exec
	if [ -z $time_cmd -a $? == 124 ]; then
		echo "corewar timed out"
		timedout=1
	fi

## GET DIFF
	lines_ref=$(wc -l < $fight_dir/ref)
	lines_exec=$(wc -l < $fight_dir/exec)
	if [[ $line_ref == 0 ]]; then
		exit
	elif [[ $line_exec == 0 ]]; then
		echo $RED "empty output for exec" $NC
		exit
	fi
	if [ $lines_ref -lt $lines_exec ]; then
		lines_diff=$lines_ref
	else
		lines_diff=$lines_exec
	fi
	echo "output ref: $lines_ref lines \| our output: $lines_exec lines \| lines diff: $lines_diff"
	head -n $lines_diff $fight_dir/exec > $fight_dir/exec
	head -n $lines_diff $fight_dir/ref > $fight_dir/ref
	diff $fight_dir/exec $fight_dir/ref > $fight_dir/diff

## DISPLAY RESULTS
	if [ -s $fight_dir/diff ]; then
		echo -e $RED"ERROR"$NC
		echo " - fight $current_fight: " ${fighters[@]} >> $output_dir/failed
	else
		echo -e $GREEN"OK"$NC
	fi

##
done


######## DISPLAY FAILED TESTS #########

if [ -s $output_dir/failed ]; then
	echo failed:
	cat $fight_dir/failed
fi


######## CLEAN OUTPUT #########

rm -rf $output_dir/fight_* > /dev/null
