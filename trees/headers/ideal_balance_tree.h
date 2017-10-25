#ifndef IDEAL_BALANCE_TREE_H
#define IDEAL_BALANCE_TREE_H
#include "binary_tree.h"
#include <functional>
#include <memory>
#include <iostream>

namespace trees{

	template <typename T>
	class ideal_balance_tree : public binary_tree<T>{
	public:
		ideal_balance_tree() :binary_tree() {}
		//open from sequence from stream
		ideal_balance_tree(const int& n, std::istream* in) :binary_tree() {
			//build a ideal balanced tree with nodes		
			std::function<std::unique_ptr<Node<T>>(const int&, std::istream*)> make_by_input = [&make_by_input](const int& n, std::istream* in){
				std::unique_ptr<Node<T>> temp = nullptr;
				if (n > 0) {
					auto nl = n / 2;
					auto nr = n - nl - 1;					
					T ch;
					(*in) >> ch;
					temp = std::make_unique<Node<T>>(std::move(ch));
					//temp->key_(ch);
					temp->left_ = make_by_input(nl, in);
					temp->right_ = make_by_input(nr, in);
				}

				return temp;
			};

			head_ = make_by_input(n, in);
		}
		virtual ~ideal_balance_tree() = default;

		ideal_balance_tree(const ideal_balance_tree& other) :binary_tree(other) {}
		ideal_balance_tree& operator=(const ideal_balance_tree&) = delete;

		ideal_balance_tree(ideal_balance_tree&& other) :binary_tree(std::move(other)) {}
		ideal_balance_tree&& operator=(ideal_balance_tree&&) = delete;
	};
}

#endif