FOLDERS = array_search hashtable_search bf_search

build clean:
	@for folder in $(FOLDERS) ; do \
		make -C ./$$folder/ -s $@;\
	done

run:
	@for folder in $(FOLDERS) ; do \
		echo $$folder && make -C ./$$folder/ -s run && tail -n 1 ./$$folder/result.txt && echo '';\
	done