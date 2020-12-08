#pragma once
#ifndef _LINKEDBINARYTREE_HPP_
#define _LINKEDBINARYTREE_HPP_

#include "BinaryTree.hpp"

template<class DataType>
class LinkedBinaryTree final {
public:

	class Vertex;

private:

	Vertex* root_;
	mutable std::function<void(const Vertex&)> process_vertex_;
	Vertex* find_vertex_ = nullptr;
	Vertex* parent_ = nullptr;
	DataType delete_data_;
	Vertex* del_vertex_;

public:

	class Vertex final {
	public:

		Vertex()noexcept(true) :
			data_{},
			left_child_{ nullptr },
			right_child_{ nullptr },
			linked_{ false }
		{};

		Vertex(const DataType& data)noexcept(true) :
			data_{ data },
			left_child_{ nullptr },
			right_child_{ nullptr },
			linked_{ false }
		{};

		Vertex(DataType&& data)noexcept(true) :
			data_{ data },
			left_child_{ nullptr },
			right_child_{ nullptr },
			linked_{ false }{}

		bool hasRightChild()const noexcept(true) {

			return this->right_child_ != nullptr && !this->linked_;

		}

		bool hasLeftChild()const noexcept(true) {

			return this->left_child_ != nullptr;

		}

		bool hasTwoChilds()const noexcept(true) {

			return hasLeftChild() && hasRightChild();

		}

		bool hasOneChild()const noexcept(true) {

			return (!hasLeftChild() && hasRightChild()) || (hasLeftChild() && !hasRightChild());

		}

		bool hasChilds()const noexcept(true) {

			return hasLeftChild() || hasRightChild();

		}

		DataType data_;

		bool linked_;
		Vertex* left_child_;
		Vertex* right_child_;
		

	};

	explicit LinkedBinaryTree(const std::initializer_list<DataType>& list)noexcept(true) :
		root_{ new Vertex{*list.begin() } },
		process_vertex_{ [](const Vertex& vertex)->void {} } {

		auto list_it = list.begin();
		++list_it;

		for (; list_it != list.end(); ++list_it)
			Add(*list_it);

	}

	explicit LinkedBinaryTree(const DataType& data)noexcept(true) :
		root_{ new Vertex{ data } },
		process_vertex_{ [](const Vertex& vertex)->void {} } { }


	explicit LinkedBinaryTree()noexcept(true) :
		root_{ nullptr },
		process_vertex_{ [](const Vertex& vertex)->void {} }{}

	void Add(const DataType& data)noexcept(true) {

		if (root_ == nullptr)
			root_ = new Vertex{ data };
		else
			Add(*root_, data);

	}

	template<class DataType>
	void Add(Vertex& vertex, const DataType& data) noexcept(true) {

		if (data < vertex.data_) {

			if (vertex.left_child_ != nullptr) {

				Add(*vertex.left_child_, data);

			}
			else {

				Vertex* new_vertex = new Vertex{ data };
				new_vertex->right_child_ = &vertex;
				new_vertex->linked_ = true;
				vertex.left_child_ = new_vertex;

			}

		}
		else {

			if (vertex.right_child_ != nullptr && !vertex.linked_) {

				Add(*vertex.right_child_, data);

			}
			else {

				Vertex* new_vertex = new Vertex{ data };
				new_vertex->right_child_ = vertex.right_child_;
				new_vertex->linked_ = true;
				vertex.right_child_ = new_vertex;
				vertex.linked_ = false;

			}

		}

	}

	struct node_print_state_t {

		node_print_state_t* child_state;
		int printing_last_child;

	};

	node_print_state_t* _root_state = NULL;

	void print_subtree(const Vertex* node) {

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

		if (node->linked_) {

			if(node->right_child_ != nullptr)
				printf(">%i(%i)\n", node->data_, node->right_child_->data_);
			else
				printf(">%i(%i)\n", node->data_, 0);

		}
		else
			printf(">%i\n", node->data_);

		if ((node->left_child_ != NULL) || (node->right_child_ != NULL && !node->linked_)) { // åñëè åñòü äåòè
			struct node_print_state_t s;
			if (parent_state != NULL) {
				parent_state->child_state = &s;
			}
			else {
				_root_state = &s;
			}
			s.child_state = NULL;

			

			// ïå÷àòàåì äåòåé
			if (node->right_child_ != NULL && !node->linked_) {
				s.printing_last_child = (node->left_child_ == NULL);
				print_subtree(node->right_child_);
			}

			if (node->left_child_ != NULL) {
				s.printing_last_child = 1;
				print_subtree(node->left_child_);
			}


			//// ïå÷àòàåì äåòåé
			//if (node->left_child_ != NULL) {
			//	s.printing_last_child = (node->right_child_ == NULL);
			//	print_subtree(node->left_child_);
			//}

			//if (node->right_child_ != NULL && !node->linked_) {
			//	s.printing_last_child = 1;
			//	print_subtree(node->right_child_);
			//}


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

	void Find(Vertex& vertex, Vertex& previous) noexcept(true) {


		if (vertex.left_child_ != nullptr ) Find(*(vertex.left_child_), vertex);
		
		if (vertex.data_ == delete_data_) {

			find_vertex_ = &vertex ;
			parent_  = &previous;

		}

		if (vertex.right_child_!= nullptr && !vertex.linked_) Find(*(vertex.right_child_), vertex);

	}

	struct VertexInfo{

		Vertex* vertex;
		Vertex* previous;

	};

	VertexInfo Max(Vertex* vertex, Vertex* previous)noexcept(true) {

		if (vertex->right_child_ == nullptr || vertex->linked_)
			return VertexInfo{ vertex , previous };
		else
			return Min(vertex->right_child_, vertex);

	}

	VertexInfo Min(Vertex* vertex, Vertex* previous)noexcept(true) {

		if (vertex->left_child_ == nullptr)
			return VertexInfo{ vertex , previous };
		else 
			return Min(vertex->left_child_, vertex);

	}

	void Delete(const DataType& data)noexcept(true) {

		//Данные элемента, который нужно удалить
		delete_data_ = data;
		Vertex null_vertex{};
		Find(*root_, null_vertex);

		//После выполнения функции Find
		//в parent_ хранится укзаатель на родителя удаляемого элемента
		//в find_element_ хранится указатель на удаляемый элемент

		if (!find_vertex_->hasChilds()) {

			if (parent_->right_child_ == find_vertex_) {

				Vertex* delete_vertex = find_vertex_;
				parent_->right_child_ = delete_vertex->right_child_;
				parent_->linked_ = delete_vertex->linked_;
				delete delete_vertex;

			} else {
				
				delete parent_->left_child_;
				parent_->left_child_ = nullptr;

			}

		} else 
		if(find_vertex_->hasOneChild()){
			
			if (find_vertex_->hasRightChild()){

				if (parent_->right_child_ == find_vertex_) {

					Vertex* delete_vertex = find_vertex_;
					parent_->right_child_ = find_vertex_->right_child_;
					delete delete_vertex;

				} else {

					Vertex* delete_vertex = find_vertex_;
					parent_->left_child_ = find_vertex_->right_child_;
					delete delete_vertex;

				}

			} else {
				
				if (parent_->right_child_ == find_vertex_) {
						
					Vertex* delete_vertex = find_vertex_;

					VertexInfo max_vertex = Max(delete_vertex->left_child_, delete_vertex);
					if (max_vertex.vertex->linked_) {

						max_vertex.vertex->right_child_ = delete_vertex->right_child_;

					}

					parent_->right_child_ = delete_vertex->left_child_;
					delete delete_vertex;

				} else {

					Vertex* delete_vertex = find_vertex_;
						
					VertexInfo max_vertex = Max(delete_vertex->left_child_, delete_vertex);
					if (max_vertex.vertex->linked_) {

						max_vertex.vertex->right_child_ = delete_vertex->right_child_;

					}

					parent_->left_child_ = delete_vertex->left_child_;
					delete delete_vertex;

				}

			}

		} else
		if (find_vertex_->hasTwoChilds()) {

			Vertex* delete_vertex = find_vertex_;
			VertexInfo min_vertex = Min(delete_vertex->right_child_, delete_vertex);

			if (min_vertex.previous->left_child_ == min_vertex.vertex)
				min_vertex.previous->left_child_ = nullptr;
			else
				min_vertex.previous->right_child_ = nullptr;

			delete_vertex->data_ = min_vertex.vertex->data_;

			if (min_vertex.previous == delete_vertex) {

				delete_vertex->right_child_ = min_vertex.vertex->right_child_;
				delete_vertex->linked_ = min_vertex.vertex->linked_;

			}

			delete min_vertex.vertex;
					
		}

	}

};





#endif //_LINKEDBINARYTREE_HPP_