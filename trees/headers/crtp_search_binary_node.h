#ifndef CRTP_SEARCH_BINARY_NODE_H
#define CRTP_SEARCH_BINARY_NODE_H
#include "binary_node.h"

namespace trees{
	template<typename T>
	struct crtp_search_binary_node : binary_node<T, crtp_search_binary_node>{
		crtp_search_binary_node()
			: binary_node()
			, count_(0) {
		}
		explicit crtp_search_binary_node(T&& key, int count = 1)
			: binary_node(std::forward<T>(key))
			, count_(std::move(count)) {
		}
		virtual ~crtp_search_binary_node() = default;

		//there can't be two same nodes in a binary tree
		crtp_search_binary_node(const crtp_search_binary_node& other) = delete;
		crtp_search_binary_node& operator=(const crtp_search_binary_node&) = delete;

		crtp_search_binary_node(crtp_search_binary_node&& other)
			: binary_node(std::move(other))
			, count_(std::move(other.coumt_)) {
		}
		crtp_search_binary_node&& operator=(crtp_search_binary_node&& other){
			if (this != &other){
				binary_node::operator =(std::move(other));
				count_ = 0;
				std::swap(count_, other.count_);
			}

			return std::move(*this);
		}

		//count of key in tree with this key value
		int count_;
	};
}

#endif