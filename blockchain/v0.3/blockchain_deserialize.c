#include "blockchain.h"

/**
 * deserialize_blocks - deserializes all blocks in the file
 * @fd: fd to save datas
 * @size: number of blocks in the file
 * @endian: endian switch
 * Return: pointer to list of blocks or NULL
 */
llist_t *deserialize_blocks(int fd, uint32_t size, uint8_t endian)
{
	block_t *block;
	llist_t *list = llist_create(MT_SUPPORT_TRUE);
	uint32_t i = 0;

	if (!list)
		return (NULL);
	for (i = 0; i < size; i++)
	{
		block = calloc(1, sizeof(*block));
		if (!block)
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
		if (read(fd, &(block->info), sizeof(block->info)) != sizeof(block->info))
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
		CHECK_ENDIAN(block->info.index);
		CHECK_ENDIAN(block->info.difficulty);
		CHECK_ENDIAN(block->info.timestamp);
		CHECK_ENDIAN(block->info.nonce);
		if (read(fd, &(block->data.len), 4) != 4)
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
		CHECK_ENDIAN(block->data.len);
		if (read(fd, block->data.buffer, block->data.len) != block->data.len)
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
		if (read(fd, block->hash, SHA256_DIGEST_LENGTH) !=
			SHA256_DIGEST_LENGTH)
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
		if (llist_add_node(list, block, ADD_NODE_REAR))
			return ((free(block), llist_destroy(list, 1, NULL)), NULL);
	}
	return (list);
}


/**
 * blockchain_deserialize - deserializes a Blockchain from a file
 * @path: path to path to a file to load the Blockchain from
 * Return: a pointer to the deserialized Blockchain upon success,
 *         or NULL upon failure
 */
blockchain_t *blockchain_deserialize(char const *path)
{
	int fd;
	blockchain_t *chain = NULL;
	uint8_t endian;
	char buf[4096] = {0};
	uint32_t size;
	char *hblk_magic = "\x48\x42\x4c\x4b";
	char *hblk_version = "\x30\x2E\x31";

	if (!path)
		return (NULL);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if ((size_t)read(fd, buf, strlen(hblk_magic)) != strlen(hblk_magic) ||
		strcmp(buf, hblk_magic))
		return ((free(chain), close(fd)), NULL);
	buf[strlen(hblk_version)] = 0;
	if ((size_t)read(fd, buf, strlen(hblk_version)) != strlen(hblk_version) ||
		strcmp(buf, hblk_version))
		return ((free(chain), close(fd)), NULL);
	chain = calloc(1, sizeof(*chain));
	if (!chain)
		return ((free(chain), close(fd)), NULL);
	if (read(fd, &endian, 1) != 1)
		return ((free(chain), close(fd)), NULL);
	endian = endian != _get_endianness();
	if (read(fd, &size, 4) != 4)
		return ((free(chain), close(fd)), NULL);
	CHECK_ENDIAN(size);
	chain->chain = deserialize_blocks(fd, size, endian);
	if (!chain)
		return ((free(chain), close(fd)), NULL);
	return (close(fd), chain);
}
