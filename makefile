FOLDERS = hash_search

build clean:
	@for folder in $(FOLDERS) ; do \
		make -C ./$$folder/ -s $@;\
	done

test: build