#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <memory>
#include <functional>
#include "crtp_binary_node.h"

namespace trees{
	template <typename T, template<class> class N = crtp_binary_node>
	class binary_tree{
	protected:
		using node_t = N<T>;
		using node_ptr = std::shared_ptr<node_t>;
	public:
		//default constructor
		binary_tree() :head_(nullptr) {}
		virtual ~binary_tree() = default;

		//copy construct
		binary_tree(const binary_tree& other){
			head_ = make_copy(other.head_);
		}
		binary_tree& operator=(const binary_tree& other){
			if (this != &other){
				binary_tree temp(other);
				std::swap(head_, temp.head_);
			}
			return *this;
		}

		//move constructor
		binary_tree(binary_tree&& other) :head_(std::move(other.head_)) {}
		binary_tree&& operator=(binary_tree&& other) {
			if (this != &other){
				binary_tree temp(std::move(other));
				std::swap(head_, temp.head_);
			}
			return std::move(*this);
		}

	protected:
		//copy tree
		node_ptr make_copy(const node_ptr copy_head, node_ptr node_def_val = nullptr){
			node_ptr head = node_def_val;
			if (copy_head != node_def_val){
				head = std::make_shared<node_t>(std::forward<T>(*(copy_head->key_)));
				head->left_ = make_copy(copy_head->left_, node_def_val);
				head->right_ = make_copy(copy_head->right_, node_def_val);
			}

			return head;
		}

		//tree traversal
		using order_pred = std::function<void(node_ptr)>;
		void preorder(node_ptr t, order_pred& P, node_ptr node_def_val = nullptr){
			if (t != nullptr){
				P(t);
				preorder(t->left_, P, node_def_val);
				preorder(t->right_, P, node_def_val);
			}
		}

		void inorder(node_ptr t, order_pred& P, node_ptr node_def_val = nullptr){
			if (t != nullptr){				
				inorder(t->left_, P, node_def_val);
				P(t);
				inorder(t->right_, P, node_def_val);
			}
		}

		void postorder(node_ptr t, order_pred& P, node_ptr node_def_val = nullptr){
			if (t != nullptr){
				postorder(t->left_, P, node_def_val);
				postorder(t->right_, P, node_def_val);
				P(t);
			}
		}

	protected:
		node_ptr head_;
	};
}

#endif