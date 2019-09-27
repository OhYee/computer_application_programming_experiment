FOLDERS = array_search hashtable_search bf_search

build clean:
	@for folder in $(FOLDERS) ; do \
		make -C ./src/$$folder/ -s $@;\
	done