#ifndef AVL_TREE_H
#define AVL_TREE_H
#include "search_binary_tree.h"
#include "crtp_avl_node.h"
#include <memory>
#include <istream>
#include <functional>

namespace trees {
	template <typename T, template<class> class N = crtp_avl_node>
	class avl_tree : public search_binary_tree<T, N> {
	protected:
		using node_bal = typename N<T>::balance;
	public:
		//default constructor
		avl_tree()
			:search_binary_tree() {
		}
		//open from sequence from stream
		avl_tree(std::istream* in) {
			//create search barrier node
			end_ = std::make_shared<node_t>();
			end_->key_ = std::make_shared<T>();
			//root in empty tree points to the barrier 
			head_ = end_;
			//build a search binary tree with nodes	
			while (!in->eof()) {
				T x;
				if ((*in) >> x) {
					*(end_->key_) = x;
					search_and_input(std::move(x), head_);
				}
			}
		}
		virtual ~avl_tree() = default;

		//copy construct
		avl_tree(const avl_tree& other)
			:search_binary_tree(other) {
		}
		avl_tree& operator=(const avl_tree& other) {
			if (this != &other)
				search_binary_tree::operator=(other);
			return *this;
		}

		//move constructor
		avl_tree(avl_tree&& other)
			:search_binary_tree(std::move(other)) {
		}
		avl_tree&& operator=(avl_tree&& other) {
			if (this != &other) 
				search_binary_tree::operator=(std::move(other));
			return std::move(*this);
		}

protected:
		//method search_and_input with balance recovery 
		virtual void search_and_input(T&& x, node_ptr& p) override{			
			//!h
			if (p == end_) {//input
				p = std::make_shared<node_t>(std::forward<T>(x));
				p->left_ = end_;
				p->right_ = end_;
				h_ = true;
			}
			else if (*(p->key_) > x) {
				search_and_input(std::forward<T>(x), p->left_);
				if (h_) {//left side has grown
					if (p->bal_ == node_bal::BALANCE) {
						p->bal_ = node_bal::IDEAL_BALANCE;
						h_ = false;
					}
					else if (p->bal_ == node_bal::IDEAL_BALANCE)
						p->bal_ = node_bal::DISBALANCE;
					else {//case when p->bal == DISBALANCE, need to restore balance(..to the Force)
						node_ptr p1 = p->left_;
						if (p1->bal_ == node_bal::DISBALANCE) {//single LL rotation
							p->left_ = p1->right_;
							p1->right_ = p;
							p->bal_ = node_bal::IDEAL_BALANCE;
							p = p1;
						}
						else {//double LR rotation
							node_ptr p2 = p1->right_;
							p1->right_ = p2->left_;
							p2->left_ = p1;
							p->left_ = p2->right_;
							p2->right_ = p;
							if (p2->bal_ == node_bal::DISBALANCE)
								p->bal_ = node_bal::BALANCE;
							else
								p->bal_ = node_bal::IDEAL_BALANCE;
							if (p2->bal_ == node_bal::BALANCE)
								p1->bal_ = node_bal::DISBALANCE;
							else
								p1->bal_ = node_bal::IDEAL_BALANCE;
							p = p2;
						}
						p->bal_ = node_bal::IDEAL_BALANCE;
						h_ = false;
					}
				}
			}
			else if (*(p->key_) < x) {
				search_and_input(std::forward<T>(x), p->right_);
				if (h_) {//right side has grown
					if (p->bal_ == node_bal::DISBALANCE) {
						p->bal_ = node_bal::IDEAL_BALANCE;
						h_ = false;
					}
					else if (p->bal_ == node_bal::IDEAL_BALANCE)
						p->bal_ = node_bal::BALANCE;
					else {//case when p->bal == BALANCE, need to restore balance(..to the Force..again)
						node_ptr p1 = p->right_;
						if (p1->bal_ == node_bal::BALANCE) {//single RR rotation
							p->right_ = p1->left_;
							p1->left_ = p;
							p->bal_ = node_bal::IDEAL_BALANCE;
							p = p1;
						}
						else {// double RL rotation
							node_ptr p2 = p1->left_;
							p1->left_ = p2->right_;
							p2->right_ = p1;
							p->right_ = p2->left_;
							p2->left_ = p;
							if (p2->bal_ == node_bal::BALANCE)
								p->bal_ = node_bal::DISBALANCE;
							else
								p->bal_ = node_bal::IDEAL_BALANCE;
							if (p2->bal_ == node_bal::DISBALANCE)
								p1->bal_ = node_bal::BALANCE;
							else
								p1->bal_ = node_bal::IDEAL_BALANCE;
							p = p2;
						}
						p->bal_ = node_bal::IDEAL_BALANCE;
						h_ = false;
					}
				}
			} else
				++p->count_;
		}

		//rebalance to left subtree
		void balanceL(node_ptr& p) {
			//h, left side decreased
			if (p->bal_ == node_bal::DISBALANCE)
				p->bal_ = node_bal::IDEAL_BALANCE;
			else if (p->bal_ == node_bal::IDEAL_BALANCE) {
				p->bal_ = node_bal::BALANCE;
				h_ = false;
			} else {//case when p->bal == BALANCE, need to restore balance(..to the Force..again..and again)
				node_ptr p1 = p->right_;
				if (p1->bal_ == node_bal::IDEAL_BALANCE || p1->bal_ == node_bal::BALANCE) {//single RR rotation
					p->right_ = p1->left_;
					p1->left_ = p;
					if (p1->bal_ == node_bal::IDEAL_BALANCE) {
						p->bal_ = node_bal::BALANCE;
						p1->bal_ = node_bal::DISBALANCE;
						h_ = false;
					}
					else {
						p->bal_ = node_bal::IDEAL_BALANCE;
						p1->bal_ = node_bal::IDEAL_BALANCE;
					}
					p = p1;
				}
				else {//double RL rotation
					node_ptr p2 = p1->left_;
					p1->left_ = p2->right_;
					p2->right_ = p1;
					p->right_ = p2->left_;
					p2->left_ = p;
					if (p2->bal_ == node_bal::BALANCE)
						p->bal_ = node_bal::DISBALANCE;
					else
						p->bal_ = node_bal::IDEAL_BALANCE;
					if (p2->bal_ == node_bal::DISBALANCE)
						p1->bal_ = node_bal::BALANCE;
					else
						p1->bal_ = node_bal::IDEAL_BALANCE;
					p = p2;
					p2->bal_ = node_bal::IDEAL_BALANCE;
				}
			}
		}

		//rebalance to right subtree
		void balanceR(node_ptr& p) {
			//h, right side decreased
			if (p->bal_ == node_bal::BALANCE)
				p->bal_ = node_bal::IDEAL_BALANCE;
			else if (p->bal_ == node_bal::IDEAL_BALANCE) {
				p->bal_ = node_bal::DISBALANCE;
				h_ = false;
			}
			else {//case when p->bal = balance::DISBALANCE, so then we need rebalance! 
				node_ptr p1 = p->left_;
				if (p1->bal_ == node_bal::IDEAL_BALANCE || p1->bal_ == node_bal::DISBALANCE) {//single LL rotation
					p->left_ = p1->right_;
					p1->right_ = p;
					if (p1->bal_ == node_bal::IDEAL_BALANCE) {
						p->bal_ = node_bal::DISBALANCE;
						p1->bal_ = node_bal::BALANCE;
						h_ = false;
					}
					else {
						p->bal_ = node_bal::IDEAL_BALANCE;
						p1->bal_ = node_bal::IDEAL_BALANCE;
					}
					p = p1;
				}
				else {//double LR rotation
					node_ptr p2 = p1->right_;
					p1->right_ = p2->left_;
					p2->left_ = p1;
					p->left_ = p2->right_;
					p2->right_ = p;
					if (p2->bal_ == node_bal::DISBALANCE)
						p->bal_ = node_bal::BALANCE;
					else
						p->bal_ = node_bal::IDEAL_BALANCE;
					if (p2->bal_ == node_bal::BALANCE)
						p1->bal_ = node_bal::DISBALANCE;
					else
						p1->bal_ = node_bal::IDEAL_BALANCE;
					p = p2;
					p2->bal_ = node_bal::IDEAL_BALANCE;
				}				
			}
		}

		//method delete node with balance recovery 
		virtual void delete_node(T&& x, node_ptr& p) override {
			std::function<void(node_ptr&, node_ptr)> del = [&del, this](node_ptr& r, node_ptr q) {
				//!h
				if (r->right_ != end_) {
					del(r->right_, q);
					if (h_) balanceR(r);
				}
				else {
					q->key_ = r->key_;
					q->count_ = r->count_;
					q = r;
					r = r->left_;
					h_ = true;
				}
			};

			//!h
			if (p == end_);//node with such key is not in tree
			else if (*(p->key_) > x) {
				delete_node(std::forward<T>(x), p->left_);
				if (h_) balanceL(p);
			} else if (*(p->key_) < x){
				delete_node(std::forward<T>(x), p->right_);
				if (h_) balanceR(p);
			} else {//delete *p
				node_ptr q = p;
				if (q->right_ == end_) {
					p = q->left_;
					h_ = true;
				}
				else if (q->left_ == end_) {
					p = q->right_;
					h_ = true;
				}
				else {
					del(q->left_, q);
					if (h_) balanceL(p);
				}
			}
		}

		//subtree height is increased or is decreased(at search_and_input or at delete_node)
		bool h_;
	};
}

#endif