#include "gtest/gtest.h"

#include <cstdint>

#include "container.h"
#include "type/tuple.h"

#include "helper/base_pointer.h"
#include "helper/relative_pointer.h"

class SpecialUseCaseTest : public ::testing::Test { };

TEST_F(SpecialUseCaseTest, ContainerNesting) {
	BinaryMapping::Container<
		BinaryMapping::PlainTuple<
			std::uint32_t,
			BinaryMapping::ByteField<16>
		>
	> container(10);

	for ( auto level1(container.begin());
	      level1 != container.end();
	      ++level1 ) {
		(*level1).set<0>(level1 - container.begin());

		BinaryMapping::Container<
			BinaryMapping::PlainTuple<
				std::uint16_t,
				std::int16_t
			>
		> nestedContainer((*level1).ptr<1>());

		for ( auto level2(nestedContainer.begin());
		      level2 != nestedContainer.end();
		      ++level2 ) {
			(*level2).set<0>(level2 - nestedContainer.begin());
			(*level2).set<1>(level2 - nestedContainer.begin());
		}
	}

	for ( auto level1(container.begin());
	      level1 != container.end();
	      ++level1 ) {
		EXPECT_EQ((*level1).get<0>(), level1 - container.begin());

		BinaryMapping::Container<
			BinaryMapping::PlainTuple<
				std::uint16_t,
				std::int16_t
			>
		> nestedContainer((*level1).ptr<1>());

		for ( auto level2(nestedContainer.begin());
		      level2 != nestedContainer.end();
		      ++level2 ) {
			EXPECT_EQ((*level2).get<0>(), level2 - nestedContainer.begin());
			EXPECT_EQ((*level2).get<1>(), level2 - nestedContainer.begin());
		}
	}
}

template <
	typename Base,
	typename Type1,
	typename Type2
>
class PairImpl {
	public:
		typedef std::pair<
			typename std::remove_const<Type1>::type,
			typename std::remove_const<Type2>::type
		> value_type;

		static const size_t size = sizeof(Type1) + sizeof(Type2);

		template <typename BaseType>
		PairImpl(BaseType data):
			base_ptr_(data),
			first_(base_ptr_.get(), 0),
			second_(base_ptr_.get(), sizeof(Type1)) { }

		operator value_type() const {
			return std::make_pair(
				*this->first_.get(),
				*this->second_.get()
			);
		}

		Type1 first() const {
			return *this->first_.get();
		}

		Type2 second() const {
			return *this->second_.get();
		}

		void operator=(const value_type& values) {
			*this->first_.get()  = values.first;
			*this->second_.get() = values.second;
		}

	private:
		const BinaryMapping::BasePointer<Base> base_ptr_;

		BinaryMapping::RelativePointer<Base, Type1> first_;
		BinaryMapping::RelativePointer<Base, Type2> second_;

};

template <
	typename Type1,
	typename Type2
>
struct Pair {
	template <typename Base>
	using type = typename std::conditional<
		std::is_const<Base>::value,
		PairImpl<
			Base,
			typename std::add_const<Type1>::type,
			typename std::add_const<Type2>::type
		>,
		PairImpl<Base, Type1, Type2>
	>::type;
};

TEST_F(SpecialUseCaseTest, CustomType) {
	BinaryMapping::Container<
		Pair<std::uint32_t, std::uint8_t>
	> container(10);

	for ( auto iter = container.begin();
	      iter     != container.end();
	      ++iter ) {
		(*iter) = std::pair<std::uint32_t, std::uint8_t>(
			iter - container.begin() + 2,
			iter - container.begin()
		);
	}

	for ( auto iter = container.begin();
	      iter     != container.end();
	      ++iter ) {
		EXPECT_EQ((*iter).first(),  iter - container.begin() + 2);
		EXPECT_EQ((*iter).second(), iter - container.begin());
	}
}
