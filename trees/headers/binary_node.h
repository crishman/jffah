#ifndef BINARY_NODE_H
#define BINARY_NODE_H
#include <memory>

namespace trees{
	template<typename T, template <class> class U>
	struct binary_node{
		//default constructor
		binary_node() 
			: key_(nullptr)
			, left_(nullptr)
			, right_(nullptr) {
		}
		//construct with key parameter
		explicit binary_node(T&& key)
			: left_(nullptr)
			, right_(nullptr) {
			key_ = std::make_shared<T>(std::forward<T>(key));
		}
		virtual ~binary_node() = default;

		//there can't be two same nodes in a binary tree
		binary_node(const binary_node& other) = delete;
		binary_node& operator=(const binary_node&) = delete;

		binary_node(binary_node&& other)
			: key_(nullptr)
			, left_(std::move(left_))
			, right_(std::move(right_)){
			std::swap(key_, other.key_);
		}
		binary_node&& operator=(binary_node&& other){
			if (this != &other){
				std::swap(key_, other.key_);
				std::swap(left_, other.left_);
				std::swap(right_, other.right_);
			}

			return std::move(*this);
		}

		//key of node
		std::shared_ptr<T> key_;
		//left child node
		std::shared_ptr<U<T>> left_;
		//right child node
		std::shared_ptr<U<T>> right_;
	};
}

#endif