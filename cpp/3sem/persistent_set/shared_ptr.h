#ifndef __SHARED_PTR_
#define __SHARED_PTR_
#include <algorithm>

template <typename T>
class my_shared_ptr {
	T *data;
	size_t *ref_counter;

public:
	my_shared_ptr(T *new_data = nullptr) : data(new_data), ref_counter(nullptr) {
		if (data) {
			try {
				ref_counter = new size_t(1);
			} catch(...) {
				delete data;
				throw;
			}
		}
	}

	my_shared_ptr(const my_shared_ptr &other) noexcept : data(other.data), ref_counter(other.ref_counter) {
		if (ref_counter)
			++(*other.ref_counter);
	}
	my_shared_ptr(my_shared_ptr &&other) noexcept : data(other.data), ref_counter(other.ref_counter) {
		other.data = nullptr;
		other.ref_counter = nullptr;
	}

	~my_shared_ptr() {
		if (ref_counter) {
			(*ref_counter) -= 1;
			if (*ref_counter == 0) {
				delete data;
				delete ref_counter;
			}
		}
	}

	my_shared_ptr& operator=(const my_shared_ptr &rhs) noexcept {
		my_shared_ptr tmp(rhs);
		swap(*this, tmp);
		return *this;
	}
	my_shared_ptr& operator=(my_shared_ptr &&rhs) noexcept {
		swap(*this, rhs);
		return *this;
	}

	T* get() const noexcept { return data; }

	operator bool() const noexcept {
		return data != nullptr;
	}

	template<class TT>
		friend void swap(my_shared_ptr<TT> &lhs, my_shared_ptr<TT> &rhs) noexcept;
};

template<class T>
void swap(my_shared_ptr<T> &lhs, my_shared_ptr<T> &rhs) noexcept {
	std::swap(lhs.ref_counter, rhs.ref_counter);
	std::swap(lhs.data, rhs.data);
}

#endif // __SHARED_PTR_