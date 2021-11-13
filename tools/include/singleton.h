#pragma once
#include <mutex>
#include <memory>

namespace BirdChirp::Tools {
template<typename T>
struct singleton {
  using type = T;
  using type_ptr = std::shared_ptr<T>;

  singleton(const singleton &) = delete;
  void operator=(const singleton &) = delete;

  static type_ptr GetInstance() {
	static type_ptr instance;
	if (!instance) {

	  std::unique_lock<std::mutex> lock;
	  if (instance) {
		return instance;
	  }

	  instance = std::make_shared<T>();
	}
	return instance;
  }
 private:
  singleton() = default;
};
} // namespace BirdChirp::Tools
