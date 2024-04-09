#include "transaction.h"

/**
 * transaction_destroy - Write a function that deallocates
 *                       a transaction structure
 * @transaction: pointer to the transaction to delete
 */
void transaction_destroy(transaction_t *transaction)
{
	if (!transaction)
		return;
	if (llist_destroy(transaction->inputs, 1, free) ||
	    llist_destroy(transaction->outputs, 1, free))
		return;
	free(transaction);
}
