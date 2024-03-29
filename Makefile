.PHONY: all build rebuild check test memtest_general clean coverage_tests_general test_imperative coverage_tests_imperative memtest_imperative test_multi coverage_tests_multi memtest_multi

all: clean check build generate test_general coverage_tests_general memtest_general test_imperative coverage_tests_imperative memtest_imperative test_multi coverage_tests_multi memtest_multi

NUMBER_OF_RECORDS  = 1000
GENERATOR = ./build/generator_data/generator
SETS_FOR_GEN = generator_data/sets/female_name.txt generator_data/sets/male_name.txt generator_data/sets/surname.txt generator_data/sets/female_surname.txt generator_data/sets/male_surname.txt generator_data/sets/position.txt

NEW_DATABASE = generated_database.txt
SORTED_DATABASE = sorted_database.txt
REPORT = report.txt

TARGET_TEST_GENERAL = ./build/gtest/gtest_general
TARGET_TEST_IMPERATIVE = ./build/gtest/gtest_imperative
TARGET_TEST_MULTI = ./build/gtest/gtest_multi


TARGET_COVERAGE = [6789]
GTEST_GENERAL_COVERAGE = build/project/CMakeFiles/GENERAL.dir/general/src
GTEST_IMPERATIVE_COVERAGE = build/project/CMakeFiles/IMPERATIVE_MODEL.dir/pattern/imperative_model/src
GTEST_MULTI_COVERAGE = build/project/CMakeFiles/MULTI_THREADED_MODEL.dir/pattern/multi_threaded_model/src

#1 - imperative mod
#2 - multi_threaded mod

clean:
	rm -rf build coverage-report valgrind.log test.log coverage.info generated_database.txt report.txt sorted_database.txt report_imp report_multi

check:
	./run_linters.sh

build:
	./run_build.sh

rebuild: clean build

generate:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}



test_general:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_GENERAL}

coverage_tests_general:
	./run_build.sh
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_GENERAL}
	./run_coverage.sh ${GTEST_GENERAL_COVERAGE} ${TARGET_COVERAGE}

memtest_general:
	./run_build.sh
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	./run_memtest.sh ${TARGET_TEST_GENERAL}



test_imperative:
	./run_build.sh
	mkdir -p report_imp
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_IMPERATIVE}

coverage_tests_imperative:
	./run_build.sh
	./run_build.sh
	mkdir -p report_imp
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_IMPERATIVE}
	./run_coverage.sh ${GTEST_IMPERATIVE_COVERAGE} ${TARGET_COVERAGE}

memtest_imperative:
	./run_build.sh
	mkdir -p report_imp
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	./run_memtest.sh ${TARGET_TEST_IMPERATIVE}



test_multi:
	./run_build.sh
	mkdir -p report_multi
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_MULTI}

coverage_tests_multi:
	./run_build.sh
	./run_build.sh
	mkdir -p report_multi
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	${TARGET_TEST_MULTI}
	./run_coverage.sh ${GTEST_MULTI_COVERAGE} ${TARGET_COVERAGE}

memtest_multi:
	./run_build.sh
	mkdir -p report_multi
	${GENERATOR} ${NUMBER_OF_RECORDS} ${NEW_DATABASE} ${SETS_FOR_GEN}
	./run_memtest.sh ${TARGET_TEST_MULTI}



launch_imp:
	./run_build.sh
	mkdir -p report_imp
	./build/HW-2 1 ${NEW_DATABASE} ${SORTED_DATABASE} 1

launch_multi:
	./run_build.sh
	mkdir -p report_multi
	./build/HW-2 1 ${NEW_DATABASE} ${SORTED_DATABASE} 2

get_time_imperative:
	time (./build/HW-2 0 ${SORTED_DATABASE} ${SORTED_DATABASE} 1)

get_time_multi:
	time (./build/HW-2 0 ${SORTED_DATABASE} ${SORTED_DATABASE} 2)