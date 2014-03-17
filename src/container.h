#ifndef BINARY_MAPPING_SRC_CONTAINER_H_
#define BINARY_MAPPING_SRC_CONTAINER_H_

#include <cstddef>
#include <cstdint>
#include <stdexcept>

#include "detail/io/buffer.h"
#include "endianess/undefined.h"

#include "type/custom_serializable.h"

#include "iterator.h"

namespace BinaryMapping {

template <typename Type>
class Container {
	public:
		typedef std::size_t size_type;

		typedef typename Type::template type<
			dtl::Buffer::memory_type
		> element_type;

		typedef typename Type::template type<
			const dtl::Buffer::memory_type
		> const_element_type;

		typedef Iterator<
			dtl::Buffer::iterator_type<element_type::size>,
			element_type
		> iterator_type;

		typedef Iterator<
			dtl::Buffer::const_iterator_type<element_type::size>,
			const_element_type
		> const_iterator_type;

		explicit Container(size_type size):
			buffer_(size * element_type::size),
			count_(buffer_.size<element_type::size>()) { }

		template <size_type Size>
		explicit Container(ByteField<Size>* field):
			buffer_(field->bytes.data(), field->bytes.size()),
			count_(buffer_.size<element_type::size>()) { }

		Container(dtl::Buffer::pointer ptr, dtl::Buffer::size_type size):
			buffer_(ptr, size),
			count_(buffer_.size<element_type::size>()) { }

		inline size_type size() const {
			return this->count_;
		}

		inline const_element_type operator[](size_type index) const {
			return const_element_type(
				this->buffer_[element_type::size * index]
			);
		}

		inline const_element_type at(size_type index) const {
			return const_element_type(
				this->buffer_.template at<element_type::size>(index)
			);
		}

		inline const_element_type front() const {
			return const_element_type(this->buffer_.front());
		}

		inline const_element_type back() const {
			return const_element_type(
				this->buffer_.template at<element_type::size>(
					this->count_ - 1
				)
			);
		}

		inline const_iterator_type begin() const {
			return const_iterator_type(
				this->buffer_.template begin<element_type::size>()
			);
		}

		inline const_iterator_type end() const {
			return const_iterator_type(
				this->buffer_.template end<element_type::size>()
			);
		}

		inline std::pair<
			const dtl::Buffer::pointer,
			const dtl::Buffer::size_type
		> data() const {
			return std::make_pair(
				this->buffer_.front(),
				this->buffer_.size()
			);
		}

		inline element_type operator[](size_type index) {
			return element_type(
				this->buffer_[element_type::size * index]
			);
		}

		inline element_type at(size_type index) {
			return element_type(
				this->buffer_.template at<element_type::size>(index)
			);
		}

		inline element_type front() {
			return element_type(this->buffer_.front());
		}

		inline element_type back() {
			return element_type(
				this->buffer_.template at<element_type::size>(
					this->count_ - 1
				)
			);
		}

		inline iterator_type begin() {
			return iterator_type(
				this->buffer_.template begin<element_type::size>()
			);
		}

		inline iterator_type end() {
			return iterator_type(
				this->buffer_.template end<element_type::size>()
			);
		}

		inline std::pair<
			dtl::Buffer::pointer,
			const dtl::Buffer::size_type
		> data() {
			return std::make_pair(
				this->buffer_.front(),
				this->buffer_.size()
			);
		}

	private:
		dtl::Buffer buffer_;
		const size_type count_;

};

}

#endif  // BINARY_MAPPING_SRC_CONTAINER_H_
