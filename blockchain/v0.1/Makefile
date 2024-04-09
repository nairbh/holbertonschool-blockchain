CC := gcc
CFLAGS := -Wall -Wextra -Werror -pedantic

PROVIDED := provided/_blockchain_print.c provided/_blockchain_destroy.c
LIBS := -I. -L../../crypto -lhblk_crypto -lllist -lssl -lcrypto -pthread

blockchain_create-test: blockchain_create.c test/blockchain_create-main.c $(PROVIDED)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

block_create-test: block_create.c blockchain_create.c test/block_create-main.c $(PROVIDED)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

block_destroy-test: block_destroy.c block_create.c blockchain_create.c test/block_destroy-main.c $(PROVIDED)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

blockchain_destroy-test: blockchain_destroy.c block_destroy.c block_create.c blockchain_create.c test/blockchain_destroy-main.c $(PROVIDED)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

block_hash-test: block_hash.c blockchain_destroy.c block_destroy.c block_create.c blockchain_create.c test/block_hash-main.c
	$(PROVIDED)$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(LIB)

re: fclean all

.PHONY: all clean fclean re
