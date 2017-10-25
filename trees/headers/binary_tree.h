#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include <memory>
#include <functional>

namespace trees{
	template <typename T>
	class binary_tree{
	protected:
		//binary tree node
		template <typename T>
		struct Node{
			Node() :left_(nullptr), right_(nullptr) {}
			explicit Node(T&& key) :left_(nullptr), right_(nullptr) {
				key_ = std::make_shared<T>(std::forward<T>(key));
			}
			~Node() = default;

			//if we copy node, only its contents are copied
			Node(const Node& other) :left_(nullptr), right_(nullptr) {
				key_ = std::make_shared<T>(*(other.key_));
			}
			//binary tree can not have two identical nodes
			Node& operator=(const Node&) = delete;

			Node(Node&& other) :key_(nullptr), left_(std::move(left_)), right_(std::move(right_)){
				std::swap(key_, other.key_);
			}
			Node&& operator=(Node&&) = delete;

			std::shared_ptr<T> key_;
			std::unique_ptr<Node<T>> left_;
			std::unique_ptr<Node<T>> right_;
		};

	public:
		binary_tree() :head_(nullptr) {}
		virtual ~binary_tree() = default;

		binary_tree(const binary_tree& other){
			std::function<void(std::unique_ptr<Node<T>>&, const std::unique_ptr<Node<T>>&)> recursive_create = [&recursive_create](std::unique_ptr<Node<T>>& head, const std::unique_ptr<Node<T>>& other_head){
				if (other_head != nullptr){
					head = std::make_unique<Node<T>>(*other_head);
					if (other_head->left_ != nullptr)
						recursive_create(head->left_, other_head->left_);
					if (other_head->right_ != nullptr)
						recursive_create(head->right_, other_head->right_);
				}
			};

			recursive_create(head_, other.head_);
		}
		binary_tree& operator=(const binary_tree&) = delete;

		binary_tree(binary_tree&& other) :head_(std::move(other.head_)) {}
		binary_tree&& operator=(binary_tree&&) = delete;

	protected:
		//tree traversal
		void preorder(std::unique_ptr<Node<T>>& t, const std::function<void(std::unique_ptr<Node<T>>&)>& P){
			if (t != nullptr){
				P(t);
				preorder(t->left_, P);
				preorder(t->right_, P);
			}
		}

		void inorder(std::unique_ptr<Node<T>>& t, std::function<void(std::unique_ptr<Node<T>>&)>& P){
			if (t != nullptr){
				P(t);
				inorder(t->left_, P);
				inorder(t->right_, P);
			}
		}

		void postorder(std::unique_ptr<Node<T>>& t, std::function<void(std::unique_ptr<Node<T>>&)>& P){
			if (t != nullptr){
				P(t);
				postorder(t->left_, P);
				postorder(t->right_, P);
			}
		}

	protected:
		std::unique_ptr<Node<T>> head_;
	};
}

#endif