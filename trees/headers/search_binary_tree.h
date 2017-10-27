#ifndef SEARCH_BINARY_TREE_H
#define SEARCH_BINARY_TREE_H
#include "ideal_balance_tree.h"
#include "crtp_search_binary_node.h"
#include <memory>

namespace trees{
	template <typename T, template<class> class N = crtp_search_binary_node>
	class search_binary_tree : public ideal_balance_tree<T, N>{
	public:
		//default constructor
		search_binary_tree() :ideal_balance_tree() {
			//create search barrier node
			end_ = std::make_shared<node_t>();
			head_ = end_;
		}
		//open from sequence from stream
		search_binary_tree(const int& n, std::istream* in) {			
			//create search barrier node
			end_ = std::make_shared<node_t>();
			//build a search binary tree with nodes	
			head_ = make_by_input(n, in, end_);
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
		search_binary_tree(search_binary_tree&& other) :ideal_balance_tree(std::move(other)), end_(nullptr) {
			std::swap(end_, other.end_);
		}
		search_binary_tree&& operator=(search_binary_tree&& other) {
			if (this != &other){
				ideal_balance_tree::operator=(std::move(other));
				end_ = nullptr;
				std::swap(end_, other.end_);
			}
			return std::move(*this);
		}
	protected:
		//search_barier
		node_ptr end_;
	};
}

#endif