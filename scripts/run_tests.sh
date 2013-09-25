#!/bin/bash

###############################################################################
# Description:
#   This script compiles the test suites using various combinations of
#   compilation parameters:
#     - compiler,
#     - debug settings.
###############################################################################


#halt on all errors
set -e

#maximum number of parallel operations
PARALLEL=4

#combinations of compilation settings
declare -A compiler_exes
compiler_exes=([Clang]="clang++" [GCC]="g++")
declare -A build_types
build_types=([d]="Debug" [rd]="RelWithDebInfo" [r]="Release" [s]="MinSizeRel")


#cleanup build directory
build_dir="$PWD/../build"
if [ -d "$build_dir" ]; then
	rm -rf "${build_dir:-null}"
fi
mkdir "$build_dir"

#run cmake in sub-directory for each combination
echo "= COMPILATIONS ="
for comp in ${!compiler_exes[@]}; do
	lc_comp=`echo $comp | tr '[:upper:]' '[:lower:]'`
	for opt in ${!build_types[@]}; do
		lc_opt=`echo $opt | tr '[:upper:]' '[:lower:]'`
		curcombin="$build_dir/$lc_comp-$lc_opt"
		build_name="Linux-64--$comp-$opt"
		comp_exe=${compiler_exes[$comp]}
		comp_path=`which $comp_exe`
		build_type=${build_types[$opt]}

		mkdir $curcombin
		cd $curcombin
		cmake -DBUILDNAME=$build_name -DCMAKE_CXX_COMPILER=$comp_path -DCMAKE_BUILD_TYPE=$build_type ../..
	done
done

#build each combination and run tests
echo "= COMPILATIONS ="
for comp in ${!compiler_exes[@]}; do
	lc_comp=`echo $comp | tr '[:upper:]' '[:lower:]'`
	for opt in ${!build_types[@]}; do
		lc_opt=`echo $opt | tr '[:upper:]' '[:lower:]'`
		curcombin="$build_dir/$lc_comp-$lc_opt"

		cd $curcombin
		make -j $PARALLEL
	done
done

#run tests for each combination
echo "= TESTS ="
for comp in ${!compiler_exes[@]}; do
	lc_comp=`echo $comp | tr '[:upper:]' '[:lower:]'`
	for opt in ${!build_types[@]}; do
		lc_opt=`echo $opt | tr '[:upper:]' '[:lower:]'`
		curcombin="$build_dir/$lc_comp-$lc_opt"

		cd $curcombin
		make test
	done
done

