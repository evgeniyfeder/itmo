#ifndef __LINKED_PTR_
#define __LINKED_PTR_

template <typename T>
class my_linked_ptr {
private:
	T *data;
	my_linked_ptr *left, *right;

	static void update_pointers(const my_linked_ptr &ptr) noexcept {
		if (ptr.left)
			ptr.left->right = const_cast<my_linked_ptr*>(&ptr);
		if (ptr.right)
			ptr.right->left = const_cast<my_linked_ptr*>(&ptr);
	}
public:
	
	my_linked_ptr(T *new_data = nullptr) noexcept : data(new_data), left(nullptr), right(nullptr) {
	}

	my_linked_ptr(const my_linked_ptr &other) noexcept : data(other.data), left(const_cast<my_linked_ptr*>(&other)), right(const_cast<my_linked_ptr*>(other.right)) {
		update_pointers(*this);
	}

	my_linked_ptr(my_linked_ptr &&other) noexcept : data(other.data), left(other.left), right(other.right) {
		other.data = nullptr;
		other.left = nullptr;
		other.right = nullptr;

		update_pointers(*this);
	}

	~my_linked_ptr() {
		if (left == right)
			delete data;
		else {
			if (left)
				left->right = right;
			if (right)
				right->left = left;
		}
	}

	my_linked_ptr& operator=(const my_linked_ptr &rhs) noexcept {
		my_linked_ptr tmp(rhs);
		swap(*this, tmp);
		return *this;
	}
	my_linked_ptr& operator=(my_linked_ptr &&rhs) noexcept {
		swap(*this, rhs);
		return *this;
	}

	T* get() const noexcept { return data; }

	operator bool() const noexcept {
		return data != nullptr;
	}

	template<class TT>
	friend void swap(my_linked_ptr<TT> &lhs, my_linked_ptr<TT> &rhs) noexcept;
};

template<class T>
void swap(my_linked_ptr<T> &lhs, my_linked_ptr<T> &rhs) noexcept {
	if (lhs.data == rhs.data)
		return;
	std::swap(lhs.data, rhs.data);
	std::swap(lhs.left, rhs.left);
	std::swap(lhs.right, rhs.right);
	my_linked_ptr<T>::update_pointers(lhs);
	my_linked_ptr<T>::update_pointers(rhs);
}
#endif