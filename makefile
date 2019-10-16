

DIRS = src crypto db http nosql

all:
	@for dir in ${DIRS}; do make -C $$dir -j8; echo ; done


clean:
	@for dir in ${DIRS}; do make -C $$dir clean; echo ; done


type_test:
	@echo ${OS_NAME};


