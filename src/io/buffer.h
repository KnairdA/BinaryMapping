#ifndef BINARY_MAPPING_SRC_IO_BUFFER_H_
#define BINARY_MAPPING_SRC_IO_BUFFER_H_

namespace BinaryMapping {

class Buffer {
	public:
		Buffer(uint8_t* d, size_t s):
			data(d),
			size(s),
			owner_(true) { }

		Buffer(const Buffer& source):
			data(source.data),
			size(source.size),
			owner_(false) { }

		~Buffer() {
			if ( this->owner_ ) {
				std::free(this->data);
			}
		}

		uint8_t* data;
		const size_t size;

	private:
		const bool owner_;
};

}

#endif  // BINARY_MAPPING_SRC_IO_BUFFER_H_
