#ifndef BINARY_NODE_H
#define BINARY_NODE_H
#include <memory>

namespace trees{
	template<typename T>
	struct Node{
		Node() :left_(nullptr), right_(nullptr) {}
		explicit Node(T&& key) :left_(nullptr), right_(nullptr) {
			key_ = std::make_shared<T>(std::forward<T>(key));
		}
		virtual ~Node() = default;

		//there can't be two same nodes in a binary tree
		Node(const Node& other) = delete;
		Node& operator=(const Node&) = delete;

		Node(Node&& other) :key_(nullptr), left_(std::move(left_)), right_(std::move(right_)){
			std::swap(key_, other.key_);
		}
		Node&& operator=(Node&& other){
			std::swap(key_, other.key_);
			std::swap(left_, other.left_);
			std::swap(right_, other.right_);

			return std::move(*this);
		}

		std::shared_ptr<T> key_;
		std::shared_ptr<Node<T>> left_;
		std::shared_ptr<Node<T>> right_;
	};
}

#endif