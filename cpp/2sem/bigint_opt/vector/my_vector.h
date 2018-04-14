#ifndef __MY_VECTOR_
#define __MY_VECTOR_
#include <memory>
#include <cstdint>

class big_integer;
class my_vector {
private:
	typedef std::shared_ptr<uint32_t> sp_type;

	struct big_vector {
		size_t capacity;
		sp_type data;

		void inplace_reserve(int new_capacity);
		void inplace_copy(const big_vector& to_copy);
		big_vector();
        ~big_vector();
		explicit big_vector(size_t size);
	};
	static const uint32_t small_capacity = sizeof(big_vector) / sizeof(uint32_t);

	uint32_t size;
	union {
		big_vector big;
		uint32_t small[small_capacity];
	};
	uint32_t *cur_data;
	bool is_big;
	bool is_small() const;
	void do_unique_copy();
    void push_back_allocate(size_t new_size);
public:
	explicit my_vector(size_t size = 0);
	my_vector(const my_vector &vec);
	~my_vector();
	my_vector &operator=(const my_vector &vec);

	void do_empty();
	void push_back(uint32_t elem);
	void resize(size_t new_size);
	size_t get_capacity() const;
	size_t get_size() const;

	uint32_t operator[](size_t ind) const;
	my_vector &set(size_t ind, uint32_t elem);
	void reverse();
	void normalize();
};
#endif // __MY_VECTOR_H_
