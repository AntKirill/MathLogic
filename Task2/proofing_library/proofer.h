#ifndef PROOFER_H
#define PROOFER_H

#include "string_handler"
#include "iostream"
#include <memory>
#include "node.h"

/*
 * Takes line of correct to that line proofment and generating proofment for A->B, where A is assumption and B is taken line.
 */
class proofer : private string_handler {
	using node_ptr = shared_ptr<node>;

public:

	void generate(node_ptr &root)
}

#endif