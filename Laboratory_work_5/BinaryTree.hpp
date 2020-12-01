#pragma once

#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_

#include <memory>
#include <functional>

//��������� ������ ��������� ������, ������� �� �����(����� �� 3 ��������), ������� 3 ������ ������,������ �� ������� �� �� �����.
//������ ��������, ������� �� �����
//��������� �������� �� ������(���������) ��������� ������ �� �����
//
//��������� ������� �� ���������

template<class DataType>
class BinaryTree final{
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

	void SetProcessVertexFunc(const std::function<void(const Vertex&)> func)const noexcept(true) { 
	
		process_vertex_ = func;
	
	};
	
	
	void TraversePreorder()noexcept(true) {

		process_vertex_(*root_);
		if (root_->left_ != nullptr) TraversePreorder(*root_->left_);
		if (root_->right_ != nullptr) TraversePreorder(*root_->right_);
		
	}
	
	void TraversePreorder(const Vertex& vertex)noexcept(true) {

		process_vertex_(vertex);
		if (vertex.left_ != nullptr) TraversePreorder(*(vertex.left_));
		if (vertex.right_ != nullptr) TraversePreorder(*(vertex.right_));

	}

	
	void TraverseInorder() noexcept(true) {

		if (root_->left_ != nullptr) TraverseInorder(*root_->left_);
		process_vertex_(*root_);
		if (root_->right_ != nullptr) TraverseInorder(*root_->right_);

	}

	void TraverseInorder(const Vertex& vertex) noexcept(true) {

		if (vertex.left_ != nullptr) TraverseInorder(*vertex.left_);
		process_vertex_(vertex);
		if (vertex.right_ != nullptr) TraverseInorder(*vertex.right_);

	}

	void TraversePostorder()noexcept(true) {

		if (root_->left_ != nullptr) TraverseInorder(*root_->left_);
		if (root_->right_ != nullptr) TraverseInorder(*root_->right_);
		process_vertex_(*root_);

	}

	void TraversePostorder(const Vertex* vertex)noexcept(true) {

		if (vertex.left_ != nullptr) TraverseInorder(*vertex.left_);
		if (vertex.right_ != nullptr) TraverseInorder(*vertex.right_);
		process_vertex_(vertex);

	}

	void Add(Vertex& vertex, const DataType& data)noexcept(true) {

		if (data < vertex.data_) {

			if (vertex.left_ != nullptr) {

				Add(*vertex.left_, data);

			} else {

				vertex.left_.reset(new Vertex{ data });

			}

		} else {

			if (vertex.right_ != nullptr) {

				Add(*vertex.right_, data);

			}
			else {

				vertex.right_.reset(new Vertex{ data });

			}

		}

	}

	void Add(const DataType& data)noexcept(true) {
		
		Add(*root_, data);
	
	};

	/*void Delete(const DataType& data)noexcept(true);
	size_t Size()const noexcept(true);*/

};
#endif //_BINARYTREE_HPP_

