#include <functional>
#include <SFML/Graphics.hpp>

struct VectorXZ
{
	int x, z;
};

inline bool operator==(const VectorXZ& left, const VectorXZ& right)
{
	return  (left.x == right.x) &&
		(left.z == right.z);
}


namespace std
{
	template<>
	struct hash<VectorXZ>
	{
		size_t operator()(const VectorXZ& vect) const
		{
			std::hash<decltype(vect.x)> hasher;

			auto hash1 = hasher(vect.x);
			auto hash2 = hasher(vect.z);

			return std::hash<decltype(vect.x)>{}((hash1 ^ hash2) >> 2);
		}
	};
}

namespace std
{
	template<>
	struct hash<sf::Vector3i>
	{
		size_t operator()(const sf::Vector3i& vect) const
		{
			std::hash<decltype(vect.x)> hasher;

			auto hash1 = hasher(vect.x);
			auto hash2 = hasher(vect.y);
			auto hash3 = hasher(vect.z);

			return std::hash<decltype(vect.x)>{}((hash1 ^ (hash2 << hash3) ^ hash3));
		}
	};
}