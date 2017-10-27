#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <memory>
#include <functional>
#include "binary_node.h"

namespace trees{
	template <typename T, template<class> class N = Node>
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
			binary_tree temp(other);
			std::swap(head_, temp.head_);
			return *this;
		}

		//move constructor
		binary_tree(binary_tree&& other) :head_(std::move(other.head_)) {}
		binary_tree&& operator=(binary_tree&& other) {
			binary_tree temp(std::move(other));
			std::swap(head_, temp.head_);
			return std::move(*this);
		}

	protected:
		node_ptr make_copy(const node_ptr copy_head, node_ptr node_def_val = nullptr){
			node_ptr head = node_def_val;
			if (copy_head != node_def_val){
				head = std::make_shared<node_t>(std::forward<T>(*(copy_head->key_)));
				head->left_ = make_copy(copy_head->left_);
				head->right_ = make_copy(copy_head->right_);
			}

			return head;
		}

		//tree traversal
		using order_pred = std::function<void(node_ptr)>;
		virtual void preorder(node_ptr t, order_pred& P){
			if (t != nullptr){
				P(t);
				preorder(t->left_, P);
				preorder(t->right_, P);
			}
		}

		virtual void inorder(node_ptr t, order_pred& P){
			if (t != nullptr){				
				inorder(t->left_, P);
				P(t);
				inorder(t->right_, P);
			}
		}

		virtual void postorder(node_ptr t, order_pred& P){
			if (t != nullptr){
				postorder(t->left_, P);
				postorder(t->right_, P);
				P(t);
			}
		}

	protected:
		node_ptr head_;
	};
}

#endif