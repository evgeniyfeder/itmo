#ifndef __CALL_ONCE_FUNCTION
#define __CALL_ONCE_FUNCTION
#include <type_traits>
#include <cassert>
#include <functional>

template <typename T>
class call_once_function;

template <typename Res, typename ...Args>
class call_once_function<Res(Args...)> {
private:
	static const int SIZE = 16;
	static const int ALLIGN = 8;
	using storage_type = typename std::aligned_storage<SIZE, ALLIGN>::type;

	
	storage_type global_storage;
private:
	template <typename T>
	static constexpr bool is_small_type() {
		return (sizeof(T) <= SIZE && alignof(T) <= ALLIGN && std::is_nothrow_move_constructible<T>());
	}

	template <typename T>
	static void destroy_small_object(storage_type &storage) {
		reinterpret_cast<T&>(storage).T::~T();
	}

	template <typename T>
	static void destroy_big_object(storage_type &storage) {
		delete reinterpret_cast<T*&>(storage);
	}

	static void destroy_empty_object(storage_type &storage) noexcept {}

	template <typename T>
	static Res call_small_object(storage_type &storage, Args&& ...args) {
		return std::move(reinterpret_cast<T&>(storage))(std::forward<Args>(args)...);
	}

	template <typename T>
	static Res call_big_object(storage_type &storage, Args&& ...args) {
		return std::move(*reinterpret_cast<T*&>(storage))(std::forward<Args>(args)...);
	}

	static Res call_empty_object(storage_type &storage, Args&& ...) { throw std::bad_function_call(); }

	template <typename T>
	static void move_small_object(storage_type &a, storage_type &b) noexcept {
		new(&b) T(std::move(reinterpret_cast<T&>(a)));
		destroy_small_object<T>(a);
	}

	template <typename T>
	static void move_big_object(storage_type &a, storage_type &b) {
		new(&b) T*(std::move(reinterpret_cast<T*&>(a)));
		reinterpret_cast<T*&>(a) = nullptr;
	}

	static void move_empty_object(storage_type &a, storage_type &b) noexcept {
	}

	struct func_ops {
		using destroy_type = void(*)(storage_type &);
		destroy_type destroy;

		using call_type = Res(*)(storage_type &, Args&& ...);
		call_type call;

		using mover_type = void(*)(storage_type &, storage_type &);
		mover_type move;

		constexpr func_ops() : destroy(destroy_empty_object), call(call_empty_object), move(move_empty_object) {}
		constexpr func_ops(destroy_type destroy, call_type call, mover_type move) : destroy(destroy), call(call), move(move) {}
	} const* ops;


	template <typename T>
	static constexpr func_ops const* get_func_ops() noexcept {
		static constexpr func_ops instance = is_small_type<T>() ?
			func_ops(destroy_small_object<T>, call_small_object<T>, move_small_object<T>) :
			func_ops(destroy_big_object<T>, call_big_object<T>, move_big_object<T>);
		return &instance;
	}

	static constexpr func_ops const* get_func_ops_empty() noexcept {
		static constexpr func_ops instance = func_ops();
		return &instance;
	}
public:

	call_once_function() noexcept : ops(get_func_ops_empty()) {}
	~call_once_function() {
		ops->destroy(global_storage);
	}
	
	call_once_function(const call_once_function &) = delete;
	call_once_function& operator=(const call_once_function&) = delete;
	
	call_once_function(call_once_function &&other) noexcept: 
		ops(other.ops) { 
		ops->move(other.global_storage, global_storage);
		other.ops = get_func_ops_empty();
	}

	call_once_function& operator=(call_once_function && other) noexcept {
		swap(other);
		return *this;
	}

	template <typename T>
	call_once_function(T func) noexcept(is_small_type<T>()) : ops(get_func_ops<T>()) {
		if (is_small_type<T>()) {
			new(&global_storage) T(std::move(func));
		}
		else {
			new(&global_storage) T*(new T(std::move(func)));
		}
	}

	explicit operator bool() const noexcept {
		return is_valid();
	}

	bool is_valid() const noexcept {
		return ops != get_func_ops_empty();
	}

	Res operator()(Args ...args) && {
		call_once_function tmp(std::move(*this));
		return tmp.ops->call(tmp.global_storage,
			std::forward<Args>(args)...);
	}

	void swap(call_once_function &rhs) noexcept {
		storage_type a, b;

		ops->move(global_storage, a);
		rhs.ops->move(rhs.global_storage, b);
		ops->move(a, rhs.global_storage);
		rhs.ops->move(b, global_storage);

		std::swap(ops, rhs.ops);
	}
};
	
#endif