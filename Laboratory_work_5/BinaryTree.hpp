#pragma once

#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_

#include <memory>
#include <functional>
#include <iostream>

//Построить дерево двоичного поиска, вывести на экран(одним из 3 способов), сделать 3 полных обхода,указав об вывести их на экран.
//Правая прошивка, вывести на экран
//Выполнить удаление из деерва(прошитого) выполнить дерево на экран
//
//Последнее задание по методичке

template<class DataType>
class BinaryTree {
public:
	
	class Vertex;

private:

	std::shared_ptr<Vertex> root_;
	mutable std::function<void(const Vertex&)> process_vertex_;

public:

	class Vertex final {
	public:

		Vertex()noexcept(true):
			data_{},
			left_{ nullptr },
			right_{ nullptr }
		{};

		Vertex(const DataType& data)noexcept(true) :
			data_{ data },
			left_{ nullptr },
			right_{ nullptr }
		{};

		Vertex(DataType&& data)noexcept(true) :
			data_{ data },
			left_{ nullptr },
			right_{ nullptr }{};

		DataType data_;
		std::shared_ptr<Vertex> left_;
		std::shared_ptr<Vertex> right_;

	};

	BinaryTree(const std::initializer_list<DataType>& list)noexcept(true):
		root_{ std::make_shared<Vertex>(*list.begin()) },
		process_vertex_{ [](const Vertex& vertex)->void{} } {
		
		auto list_it = list.begin();
		++list_it;

		for (; list_it != list.end(); ++list_it)
			Add(*list_it);

	}

	explicit BinaryTree(const DataType& data)noexcept(true) :
		root_{ std::make_shared<Vertex>(data) },
		process_vertex_{ [](const Vertex& vertex)->void {} } {
	
	}

	explicit BinaryTree()noexcept(true):
		root_{ nullptr },
		process_vertex_{ [](const Vertex& vertex)->void {} }{}


	inline void SetProcessVertexFunc(const std::function<void(const Vertex&)> func)const noexcept(true) { 
	
		process_vertex_ = func;
	
	};
	
	
	void TraversePreorder()noexcept(true);
	void TraverseInorder() noexcept(true);
	void TraversePostorder()noexcept(true);
	void TraversePreorder(const Vertex& vertex)noexcept(true);
	void TraverseInorder(const Vertex& vertex) noexcept(true);
	void TraversePostorder(const Vertex& vertex)noexcept(true);

	void Add(Vertex& vertex, const DataType& data)noexcept(true);

	void Add(const DataType& data)noexcept(true);


	struct node_print_state_t {
		struct node_print_state_t* child_state;
		int printing_last_child;
	};

	struct node_print_state_t* _root_state = NULL;

	void print_subtree(const std::shared_ptr<Vertex>& node) {

		node_print_state_t* parent_state;
		if (_root_state != NULL) {
			printf(" ");
			node_print_state_t* s = _root_state;
			while (s->child_state != NULL) {
				printf(s->printing_last_child ? "  " : "| ");
				s = s->child_state;
			}
			parent_state = s;
			printf(parent_state->printing_last_child ? "L" : "+");
		}
		else {
			parent_state = NULL;
		}
		printf(">%i\n", node->data_);

		if ((node->left_ != NULL) || (node->right_!= NULL)) { // åñëè åñòü äåòè
			struct node_print_state_t s;
			if (parent_state != NULL) {
				parent_state->child_state = &s;
			}
			else {
				_root_state = &s;
			}
			s.child_state = NULL;

			// ïå÷àòàåì äåòåé
			if (node->right_ != NULL) {
				s.printing_last_child = (node->left_ == NULL);
				print_subtree(node->right_);
			}
			if (node->left_ != NULL) {
				s.printing_last_child = 1;
				print_subtree(node->left_);
			}

			if (parent_state != NULL) {
				parent_state->child_state = NULL;
			}
			else {
				_root_state = NULL;
			}
		}
	}

	void print_tree() {

		if (root_ != nullptr) {
			print_subtree(root_);
		}

	}

};

template<class DataType>
void BinaryTree<DataType>::TraverseInorder() noexcept(true){
	
	std::cout << root_->data_;
	if (root_->left_ != nullptr) TraverseInorder(*root_->left_);
	else
		std::cout << "0";

	process_vertex_(*root_);

	if (root_->right_ != nullptr) TraverseInorder(*root_->right_);
	else
		std::cout << "0";

	std::cout << root_->data_ ;
}

template<class DataType>
void BinaryTree<DataType>::TraverseInorder(const Vertex& vertex) noexcept(true) {
	
	std::cout << vertex.data_ ;
	if (vertex.left_ != nullptr) TraverseInorder(*(vertex.left_));
	else
		std::cout << "0";

	process_vertex_(vertex);

	if (vertex.right_ != nullptr) TraverseInorder(*(vertex.right_));
	else
		std::cout << "0";

	std::cout << vertex.data_;


}



template<class DataType>
void BinaryTree<DataType>::TraversePostorder() noexcept(true){

	std::cout << root_->data_ ;

	if (root_->left_ != nullptr) TraversePostorder(*root_->left_);
	else
		std::cout << "0";

	std::cout << root_->data_ ;

	if (root_->right_ != nullptr) TraversePostorder(*root_->right_);
	else
		std::cout << "0";

	process_vertex_(*root_);

}

template<class DataType>
void BinaryTree<DataType>::TraversePostorder(const Vertex& vertex) noexcept(true) {

	std::cout << vertex.data_ ;
	
	if (vertex.left_ != nullptr) TraversePostorder(*(vertex.left_));
		else 
			std::cout << "0";

	std::cout << vertex.data_ ;

	if (vertex.right_ != nullptr) TraversePostorder(*(vertex.right_));
	else
		std::cout << "0";

	process_vertex_(vertex);

}

template<class DataType>
void BinaryTree<DataType>::TraversePreorder(const Vertex& vertex) noexcept(true){

	process_vertex_(vertex);

	if (vertex.left_ != nullptr) TraversePreorder(*(vertex.left_));
	else 
		std::cout << "0";
	
	std::cout << vertex.data_;

	if (vertex.right_ != nullptr)TraversePreorder(*(vertex.right_));
	else 
		std::cout << "0";

	std::cout << vertex.data_;

}

template<class DataType>
void BinaryTree<DataType>::TraversePreorder() noexcept(true) {

	process_vertex_(*root_);
	if (root_->left_ != nullptr) 
		TraversePreorder(*root_->left_);
	
	std::cout << root_->data_;

	if (root_->right_ != nullptr) 
		TraversePreorder(*root_->right_);

	std::cout << root_->data_ ;

}

template<class DataType>
void BinaryTree<DataType>::Add(Vertex& vertex, const DataType& data) noexcept(true){

	if (data < vertex.data_) {

		if (vertex.left_ != nullptr) {

			Add(*vertex.left_, data);

		} else {

			vertex.left_.reset(new Vertex{ data });

		}

	} else {

		if (vertex.right_ != nullptr) {

			Add(*vertex.right_, data);

		} else {

			vertex.right_.reset(new Vertex{ data });

		}

	}

}

template<class DataType>
inline void BinaryTree<DataType>::Add(const DataType& data) noexcept(true){
	
	if (root_ == nullptr)
		root_ = std::make_shared<Vertex>(data);
	else
		Add(*root_, data);

}

#endif //_BINARYTREE_HPP_