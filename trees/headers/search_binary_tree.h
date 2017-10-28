#ifndef SEARCH_BINARY_TREE_H
#define SEARCH_BINARY_TREE_H
#include "ideal_balance_tree.h"
#include "crtp_search_binary_node.h"
#include <memory>
#include <istream>

namespace trees{
	template <typename T, template<class> class N = crtp_search_binary_node>
	class search_binary_tree : public binary_tree<T, N>{
	public:
		//default constructor
		search_binary_tree() :binary_tree() {
			//create search barrier node
			end_ = std::make_shared<node_t>();
			end_->key_ = std::make_shared<T>();
			//root in empty tree points to the barrier 
			head_ = end_;
		}
		//open from sequence from stream
		search_binary_tree(std::istream* in) {			
			//create search barrier node
			end_ = std::make_shared<node_t>();
			end_->key_ = std::make_shared<T>();
			//root in empty tree points to the barrier 
			head_ = end_;
			//build a search binary tree with nodes	
			while (!in->eof()) {
				T x;
				(*in) >> x;
				*(end_->key_) = x;
				search_and_input(std::move(x), head_);
			}
		}
		virtual ~search_binary_tree() = default;

		//copy construct
		search_binary_tree(const search_binary_tree& other){
			head_ = make_copy(other.head_, end_);
		}
		search_binary_tree& operator=(const search_binary_tree& other) {
			if (this != &other){
				search_binary_tree temp(other);
				std::swap(head_, temp.head_);
				std::swap(end_, temp.end_);
			}
			return *this;
		}
		
		//move constructor
		search_binary_tree(search_binary_tree&& other) :binary_tree(std::move(other)), end_(nullptr) {
			std::swap(end_, other.end_);
		}
		search_binary_tree&& operator=(search_binary_tree&& other) {
			if (this != &other){
				binary_tree::operator=(std::move(other));
				end_ = nullptr;
				std::swap(end_, other.end_);
			}
			return std::move(*this);
		}

		void search_and_input(T&& x, node_ptr& p) {
			if (x < *(p->key_))
				search_and_input(std::forward<T>(x), p->left_);
			else if (x > *(p->key_))
				search_and_input(std::forward<T>(x), p->right_);
			else if (p != end_)
				++p->count_;
			else {//вставить
				p = std::make_shared<node_t>(std::forward<T>(x));
				p->left_ = end_;
				p->right_ = end_;
			}
		}

		//output key values starting from the head_
		virtual void print_tree(const int& h, std::ostream* out) const override{
			PrintTree(head_, h, out, end_);
		}

		void delete_by_key(T&& x) {
			delete_by_key(std::forward<T>(x), head_);
		}

	protected:
		void delete_by_key(T&& x, node_ptr& p) {
			if (p == end_);
			else if (x < *(p->key_))
				delete_by_key(std::forward<T>(x), p->left_);
			else if (x > *(p->key_))
				delete_by_key(std::forward<T>(x), p->right_);
			else {//удалить *p
				if (p->right_ == end_)
					p = p->left_;
				else if (p->left_ == end_)
					p = p->right_;
				else
					delete_node(p->left_, p);
			}
		}

		//p - pointer to delete node
		//r - at first call of method it's pointer to r.left_
		virtual void delete_node(node_ptr& r, node_ptr p) override {
			if (r->right_ != end_)
				delete_node(r->right_, p);
			else {
				p->key_ = r->key_;
				p->count_ = r->count_;
				r = r->left_;
			}
		}

	protected:
		//search_barier
		node_ptr end_;
	};
}

#endif