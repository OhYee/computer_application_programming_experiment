FOLDERS = hash_search tree pattern_match


test: build
	-@make -C ./utils/ -s $@

build:
	@for folder in $(FOLDERS) ; do \
		make -C ./$$folder/ -s $@;\
	done\

clean:
	-@for folder in $(FOLDERS) ; do \
		make -C ./$$folder/ -s $@;\
	done
	-@make -C ./utils/ -s $@