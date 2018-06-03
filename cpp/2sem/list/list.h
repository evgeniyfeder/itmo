#pragma once
#include <type_traits>
#include <iterator>

template <typename T>
class list {
private:
	struct node_base {
		node_base *left, *right;

		node_base(node_base *left = nullptr, node_base *right = nullptr) : left(left), right(right) {}
		virtual ~node_base() {
		}

		void free_node(const node_base &fake_node) {
			node_base *next = right->right, *cur = right;
			while (cur != &fake_node) {
				delete cur;
				cur = next;
				next = next->right;
			}
		}

		void set_empty(const list &list) {
			left = list.fake_node;
			right = list.fake_node;
		}
	};
	struct node : node_base {
		T data;
		node(const T &data, node_base *left = nullptr, node_base *right = nullptr) : node_base(left, right), data(data) {};
	};

	node_base fake;
	node_base *fake_node = &fake;

public:
	template <typename U>
	struct my_iterator {
		node_base *cur;
		my_iterator(node_base *cur) : cur(cur) {};

		template <typename C>
		my_iterator(const my_iterator<C> &data,
			typename std::enable_if<std::is_same<U, const C>::value>::type * = nullptr)
			: cur(data.cur) {
		}

		my_iterator & operator++() {
			cur = cur->right;
			return *this;
		}

		my_iterator & operator--() {
			cur = cur->left;
			return *this;
		}

		my_iterator operator++(int) {
			iterator was(cur);
			++(*this);
			return was;
		}

		my_iterator operator--(int) {
			iterator was(cur);
			--(*this);
			return was;
		}

		U & operator*() const {
			return static_cast<node *>(cur)->data;
		}

		friend bool operator==(my_iterator a, my_iterator b) {
			return a.cur == b.cur;
		}

		friend bool operator!=(my_iterator a, my_iterator b) {
			return a.cur != b.cur;
		}

		typedef std::ptrdiff_t difference_type;
		typedef U value_type;
		typedef U* pointer;
		typedef U& reference;
		typedef std::bidirectional_iterator_tag iterator_category;
	};

	typedef my_iterator<T> iterator;
	typedef my_iterator<const T> const_iterator;
	typedef std::reverse_iterator<iterator> reverse_iterator;
	typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
public:

	/***** Helpful functions ******/
	list() {
		fake.left = fake_node;
		fake.right = fake_node;
	};

	list(const list &other) : list() {
		node_base *other_node = other.fake_node->right;
		while (other_node != other.fake_node) {
			push_back(static_cast<node *>(other_node)->data);
			other_node = other_node->right;
		}
	}

	list &operator=(const list &other) {
		list tmp(other);
		swap(*this, tmp);
		return *this;
	}
	~list() { clear(); }
	bool empty() const {
		return fake_node->left == fake_node;
	}

	void clear() {
		fake_node->free_node(fake);
	}

	/* Working with list module */
	void push_back(T const &elem) {
		node *new_node = new node(elem, fake_node->left, fake_node);
		fake_node->left->right = new_node;
		fake_node->left = new_node;
	}

	void pop_back() {
		node_base *to_delete = fake_node->left;
		fake_node->left->left->right = fake_node;
		fake_node->left = fake_node->left->left;
		to_delete->set_empty(*this);
		delete to_delete;
	}

	void push_front(T const &elem) {
		node_base *new_node = new node(elem, fake_node, fake_node->right);
		fake_node->right->left = new_node;
		fake_node->right = new_node;
	}

	void pop_front() {
		node_base *to_delete = fake_node->right;
		fake_node->right->right->left = fake_node;
		fake_node->right = fake_node->right->right;
		to_delete->set_empty(*this);
		delete to_delete;
	}

	T &get_data(node_base *cur) const {
		return static_cast<node *>(cur)->data;
	}
	T &back() { return get_data(fake_node->left); }
	const T &back() const { return get_data(fake_node->left); }

	T &front() { return get_data(fake_node->right); }
	const T &front() const { return get_data(fake_node->right); }

	/* Work with iterator module */
	iterator begin() { return iterator(fake_node->right); }
	const_iterator begin() const { return const_iterator(fake_node->right); }

	iterator end() { return iterator(fake_node); }
	const_iterator end() const { return const_iterator(fake_node); }

	reverse_iterator rbegin() { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }

	reverse_iterator rend() { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

	/* Work in random access module */
	iterator insert(const_iterator it, const T &data) {
		node *new_node = new node(data, it.cur->left, it.cur);
		it.cur->left->right = new_node;
		it.cur->left = new_node;
		return iterator(new_node);
	}

	iterator erase(const_iterator it) {
		iterator res = iterator(it.cur->right);

		it.cur->left->right = it.cur->right;
		it.cur->right->left = it.cur->left;

		it.cur->set_empty(*this);

		delete it.cur;
		return res;
	}

	iterator erase(const_iterator begin, const_iterator end) {
		node_base new_base;
		new_base.right = begin.cur;
		new_base.left = end.cur->left;

		begin.cur->left->right = end.cur;
		end.cur->left->right = &new_base;

		end.cur->left = begin.cur->left;
		begin.cur->left = &new_base;

		new_base.free_node(new_base);
		return iterator(end.cur);
	}

	iterator splice(const_iterator pos, list &other, const_iterator first, const_iterator last) {
		node_base *tmp = last.cur->left->right;
		last.cur->left->right = pos.cur->left->right;
		pos.cur->left->right = first.cur->left->right;
		first.cur->left->right = tmp;

		tmp = pos.cur->left;
		pos.cur->left = last.cur->left;
		last.cur->left = first.cur->left;
		first.cur->left = tmp;
		return iterator(pos.cur);
		/*pos.cur->left->right = first.cur;
		pos.cur->left = last.cur->left;

		node_base *pre_last = last.cur->left;

		first.cur->left->right = last.cur;

		first.cur->left = pos.cur->left;
		pre_last->right = pos.cur;

		last.cur->left = first.cur->left;
		return iterator(pos.cur);*/
	}

	template <typename TT>
	friend void swap(list<TT> &a, list<TT> &b);
};

template <typename T>
void swap(list<T> &a, list<T> &b) {
	std::swap(a.fake, b.fake);

	if (a.fake_node->left == b.fake_node) {
		a.fake_node->left = &a.fake;
		a.fake_node->right = &a.fake;
	}
	if (b.fake_node->left == a.fake_node) {
		b.fake_node->left = &b.fake;
		b.fake_node->right = &b.fake;
	}

	a.fake_node->left->right = &a.fake;
	a.fake_node->right->left = &a.fake;
	b.fake_node->left->right = &b.fake;
	b.fake_node->right->left = &b.fake;
}
