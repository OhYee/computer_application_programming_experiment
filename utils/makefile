UTILS_FOLDERS = $(shell ls . -F | grep "\/")

test: run

run:
	@for folder in $(UTILS_FOLDERS) ; do \
		if [ -d ./$$folder/test ]; then \
		echo -e "\n$$folder" && make -C ./$$folder/ -s $@; \
		fi;\
	done

clean build:
	@for folder in $(UTILS_FOLDERS) ; do \
		if [ -d ./$$folder/test ]; then \
			make -C ./$$folder/ -s $@; \
		fi;\
	done