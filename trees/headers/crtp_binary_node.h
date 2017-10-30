#ifndef CRTP_BINARY_NODE_H
#define CRTP_BINARY_NODE_H
#include "binary_node.h"

namespace trees{
	template<typename T>
	struct crtp_binary_node : binary_node<T, crtp_binary_node>{
		crtp_binary_node()
			: binary_node() {
		}
		explicit crtp_binary_node(T&& key) 
			: binary_node(std::forward<T>(key)) {
		}
		virtual ~crtp_binary_node() = default;

		//there can't be two same nodes in a binary tree
		crtp_binary_node(const crtp_binary_node& other) = delete;
		crtp_binary_node& operator=(const crtp_binary_node&) = delete;

		crtp_binary_node(crtp_binary_node&& other)
			:binary_node(std::move(other)){
		}
		crtp_binary_node&& operator=(crtp_binary_node&& other){
			if (this != &other)
				binary_node::operator =(std::move(other));
			
			return std::move(*this);
		}
	};
}

#endif