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
		using node_ptr = std::unique_ptr<node_t>;
	public:
		//default constructor
		binary_tree() :head_(nullptr) {}
		virtual ~binary_tree() = default;

		//copy construct
		binary_tree(const binary_tree& other){
			std::function<void(node_ptr&, const node_ptr&)> recursive_create = [&recursive_create](node_ptr& head, const node_ptr& other_head){
				if (other_head != nullptr){
					head = std::make_unique<node_t>(std::forward<T>(*(other_head->key_)));
					if (other_head->left_ != nullptr)
						recursive_create(head->left_, other_head->left_);
					if (other_head->right_ != nullptr)
						recursive_create(head->right_, other_head->right_);
				}
			};

			recursive_create(head_, other.head_);
		}
		binary_tree& operator=(const binary_tree&){
			binary_tree temp(other);
			std::swap(head_, temp.head_);
			return this;
		}

		//move constructor
		binary_tree(binary_tree&& other) :head_(std::move(other.head_)) {}
		binary_tree&& operator=(binary_tree&& other) {
			binary_tree temp(std::move(other));
			std::swap(head_, temp.head_);
			return std::move(this);
		}

	protected:
		//tree traversal
		using order_pred = std::function<void(node_ptr&)>;
		void preorder(node_ptr& t, order_pred& P){
			if (t != nullptr){
				P(t);
				preorder(t->left_, P);
				preorder(t->right_, P);
			}
		}

		void inorder(node_ptr& t, order_pred& P){
			if (t != nullptr){				
				inorder(t->left_, P);
				P(t);
				inorder(t->right_, P);
			}
		}

		void postorder(node_ptr& t, order_pred& P){
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