FOLDERS = hash_search tree

build clean:
	@for folder in $(FOLDERS) ; do \
		make -C ./$$folder/ -s $@;\
	done

test: build