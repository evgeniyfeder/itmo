#ifndef __PERS_SET_H_
#define __PERS_SET_H_
#include <vector>
#include "shared_ptr.h"
#include "linked_ptr.h"

template <typename T, template <typename> class U = my_linked_ptr>
class persistent_set
{
public:
	class iterator;
private:
	struct base_node;
	using ptr_type = U<base_node>;

	/* Fake node type */
	struct base_node {
		base_node(const base_node &other) noexcept : left(other.left) {}
		base_node(base_node &&other) noexcept : left(std::move(other.left)) {}
		base_node(const ptr_type &left = ptr_type()) noexcept : left(left) {}

		base_node& operator=(const base_node &other) noexcept {
			left = other.left;
			return *this;
		}

		virtual ~base_node() {}

		ptr_type left;
	};

	/* All nodes type */
	struct node : base_node {
		node() = delete;
		node(const node &other) noexcept : base_node(other.left),
			right(other.right),
			data(other.data) {
			
		}

		node& operator=(const node &other) noexcept {
			left = other.left;
			right = other.right;
			data = other.data;
			return *this;
		}
		node(T data, const ptr_type &left = nullptr, const ptr_type &right = nullptr) noexcept(noexcept(T(std::move(data)))) : 
			base_node(left),
			right(right),
			data(data) {}
		ptr_type right;
		T data;
	};

	static ptr_type& right(const base_node *n) {
		return const_cast<node *>(static_cast<const node*>(n))->right;
	}

	static const T& data(const base_node *n) {
		return static_cast<const node*>(n)->data;
	}

	static ptr_type& left(const base_node *n) {
		return const_cast<base_node *>(n)->left;
	}

	base_node end_elem; /* Tree root */
	
	

	iterator find(const base_node *cur_node, const T &elem) const noexcept {
		if (cur_node == nullptr)
			return end();
		if (elem == data(cur_node))
			return iterator(cur_node, &end_elem);
		if (elem < data(cur_node))
			return find(left(cur_node).get(), elem);
		else
			return find(right(cur_node).get(), elem);
	}

	struct insert_res {
		bool existed;
		ptr_type inserted;
		ptr_type son;

		insert_res(const ptr_type &son, const ptr_type &inserted, bool existed)
			: existed(existed), inserted(inserted), son(son)
		{}
	};

	insert_res insert(ptr_type cur_node, const T &elem) {
		if (!cur_node) {
			auto new_node_ptr = ptr_type(new node(elem));
			return insert_res(new_node_ptr, new_node_ptr, false);
		}

		ptr_type new_node;
		if (data(cur_node.get()) == elem)
			return insert_res(cur_node, cur_node, true);
		if (elem < data(cur_node.get())) {
			insert_res res = insert(left(cur_node.get()), elem);
			if (res.existed) {
				res.son = cur_node;
				return res;
			}

			new_node = ptr_type(new node(data(cur_node.get())));
			right(new_node.get()) = right(cur_node.get());
			left(new_node.get()) = res.son;

			res.son = new_node;
			return res;
		}
		else {
			insert_res res = insert(right(cur_node.get()), elem);
			if (res.existed) {
				res.son = cur_node;
				return res;
			}

			new_node = ptr_type(new node(data(cur_node.get())));
			right(new_node.get()) = res.son;
			left(new_node.get()) = left(cur_node.get());

			res.son = new_node;
			return res;
		}
	}

	ptr_type erase(const base_node *cur_node, const T &elem) {
		if (elem < data(cur_node))
			return ptr_type(new node(data(cur_node), erase(left(cur_node).get(), elem), right(cur_node)));
		if (data(cur_node) < elem)
			return ptr_type(new node(data(cur_node), left(cur_node), erase(right(cur_node).get(), elem)));
		if (left(cur_node) && right(cur_node)) {
			base_node *min_right = right(cur_node).get();

			while (left(min_right)) {
				min_right = left(min_right).get();
			}
			T copy = data(min_right);
			return ptr_type(new node(data(min_right), left(cur_node), erase(right(cur_node).get(), copy)));
		}
		if (left(cur_node)) {
			return left(cur_node);
		}
		if (right(cur_node)) {
			return right(cur_node);
		}
		return ptr_type(nullptr);
	}

public:
	class iterator
	{
	public:
		friend class persistent_set<T, U>;
	private:
		/* Get next pointer */
		std::pair<bool, base_node *> get_next(base_node *cur_node, const T &elem) {
			if (elem < data(cur_node)) {
				auto res = get_next(left(cur_node).get(), elem);
				if (res.first)
					return std::make_pair(false, cur_node);
				return res;
			}
			if (data(cur_node) < elem)
				return get_next(right(cur_node).get(), elem);

			if (!right(cur_node))
				return std::make_pair(true, cur_node);

			base_node *min_right = right(cur_node).get();

			while (left(min_right)) {
				min_right = left(min_right).get();
			}
			return std::make_pair(false, min_right);
		}

		const base_node *get_next() {
			if (cur == root)
				return cur;
			auto res = get_next(left(root).get(), data(cur));
			if (res.first)
				return root;
			return res.second;
		}

		/* Get prev pointer */
		std::pair<bool, base_node *> get_prev(base_node *cur_node, const T &elem) {
			if (data(cur_node) > elem)
				return get_prev(left(cur_node).get(), elem);
			if (data(cur_node) < elem) {
				auto res = get_prev(right(cur_node).get(), elem);
				if (res.first)
					return std::make_pair(false, cur_node);
				return res;
			}
			if (!left(cur_node))
				return std::make_pair(true, cur_node);
			base_node *max_left = left(cur_node).get();
			while (right(max_left))
				max_left = right(max_left).get();
			return std::make_pair(false, max_left);
		}

		const base_node *get_prev() {
			if (cur == root) {
				base_node *max_elem = left(cur).get();

				while (right(max_elem))
					max_elem = right(max_elem).get();
				return max_elem;
			}
			auto res = get_prev(left(root).get(), data(cur));
			return res.second;
		}

	public:
		/* Constructor */
		iterator(const base_node *elem, const base_node *fake_elem) : root(fake_elem), cur(elem) {}

		const T& operator*() const {
			return data(cur);
		}

		// Переход к элементу со следующим по величине ключом.
		// Инкремент итератора end() неопределен.
		// Инкремент невалидного итератора неопределен.
		iterator& operator++() {
			return *this = iterator(get_next(), root);
		}
		iterator operator++(int) {
			iterator copy(*this);
			*this = iterator(get_next(), root);
			return copy;
		}

		// Переход к элементу с предыдущим по величине ключом.
		// Декремент итератора begin() неопределен.
		// Декремент невалидного итератора неопределен.
		iterator& operator--() {
			return *this = iterator(get_prev(), root);
		}
		iterator operator--(int) {
			iterator copy(*this);
			*this = iterator(get_prev(), root);
			return copy;
		}

		friend bool operator==(const iterator &a, const iterator &b) {
			return a.cur == b.cur;
		}

		friend bool operator!=(const iterator &a, const iterator &b) {
			return !(a == b);
		}
	private:
		const base_node *root, *cur;
	};
	/* Constructors and operator= */
	persistent_set() noexcept {}
	persistent_set(const persistent_set &other) noexcept : end_elem(other.end_elem) {}
	persistent_set& operator=(const persistent_set &other) noexcept {
		end_elem = other.end_elem;
		return *this;
	}

	/* Destructor */
	~persistent_set() = default;

	/* find element */
	iterator find(const T &elem) const noexcept {
		return find(end_elem.left.get(), elem);
	}

	/* true - new elem
	 * false - existed
	 */
	std::pair<iterator, bool> insert(const T &elem) {
		insert_res res = insert(end_elem.left, elem);
		end_elem.left = res.son;
		return std::make_pair<iterator, bool>(iterator(res.inserted.get(), &end_elem), !res.existed);
	}

	// Удаление элемента.
	// Инвалидирует все итераторы, принадлежащие persistent_set'у this, включая end().
	void erase(const iterator &it) {
		if (it == end())
			return;
		end_elem.left = erase(end_elem.left.get(), *it);
	}

	// Возващает итератор на элемент с минимальный ключом.
	iterator begin() const noexcept {
		base_node *cur = end_elem.left.get();
		if (cur == nullptr)
			return end();
		while (left(cur).get() != nullptr)
			cur = left(cur).get();
		return iterator(cur, &end_elem);
	}
	// Возващает итератор на элемент следующий за элементом с максимальным ключом.
	iterator end() const noexcept {
		return iterator(&end_elem, &end_elem);
	}

	template <typename TT, template <typename> class UU>
	friend void swap(persistent_set<TT, UU> &lhs, persistent_set<TT, UU> &rhs) noexcept;
};

template <typename T, template <typename> class U = my_shared_ptr>
void swap(persistent_set<T, U> &lhs, persistent_set<T, U> &rhs) noexcept {
	std::swap(lhs.end_elem, rhs.end_elem);
}

#endif