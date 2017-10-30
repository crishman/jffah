#ifndef SRTP_AVL_NODE_H
#define SRTP_AVL_NODE_H
#include "binary_node.h"

namespace trees {
	template<typename T>
	struct crtp_avl_node : binary_node<T, crtp_avl_node> {
		enum class balance : int {
			BALANCE = 1,//height in left and right subtrees differ by not more than 1
			IDEAL_BALANCE = 0,//number of nodes in left and right subtrees differ by not more than 1
			DISBALANCE = -1,//substree is dibalanced
		};

		crtp_avl_node()
			: binary_node()
			, count_(0)
			, bal_(balance::IDEAL_BALANCE)
		{}
		explicit crtp_avl_node(T&& key, int count = 1, balance bal = balance::IDEAL_BALANCE)
			: binary_node(std::forward<T>(key))
			, count_(std::move(count))
			, bal_(std::move(bal))
		{}
		virtual ~crtp_avl_node() = default;

		//there can't be two same nodes in a binary tree
		crtp_avl_node(const crtp_avl_node& other) = delete;
		crtp_avl_node& operator=(const crtp_avl_node&) = delete;

		crtp_avl_node(crtp_avl_node&& other)
			: binary_node(std::move(other))
			, count_(std::move(other.coumt_))
			, bal_(std::move(other.bal_)) {
		}
		crtp_avl_node&& operator=(crtp_avl_node&& other) {
			if (this != &other) {
				binary_node::operator =(std::move(other));
				count_ = 0;
				bal_ = balance::IDEAL_BALANCE;
				std::swap(count_, other.count_);
				std::swap(bal_, other.bal_);
			}

			return std::move(*this);
		}

		//count of key in tree with this key value
		int count_;
		//balance of subtree with root in this node
		balance bal_;
	};
}

#endif