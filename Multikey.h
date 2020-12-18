#ifndef MULTIKEY_H
#define MULTIKEY_H
#include <array>

/* Tp - type of element, 
 * Nm - number of elements, 
 * 
 * template for a Multikey class inspired by 
 * https://cnx.org/contents/bAqxAubo@2/C-STL-map-with-multiple-keys
 */
template <class Tp, size_t Nm>
class Multikey
{
    public:
        Multikey(){};
        Multikey(std::array<Tp,Nm> _keys, size_t __sort_by) 
        : keys{_keys}, _sort_by{0} 
        {
            sort_by(__sort_by);
        };

        std::array<Tp,Nm> keys{};

        Tp at(size_t i)
        {
            return keys.at(i);
        }

        /* Sets the key that will be used for comparison to the i'th key */
        void sort_by(size_t i)
        {
            if ( i < keys.size() )
                _sort_by=i;
        };

        /* Returns which key currently being used for comparison */
        size_t sorts_by()
        {
            return _sort_by;
        };

        bool operator<(const Multikey<Tp, Nm> &right) const
        {
            if ( !( keys.empty() ) && !( right.keys.empty() ) )
            {
                return keys.at(_sort_by) < right.keys.at(right._sort_by);
            }
            else
            {
                return !( right.keys.empty() );
            }
        };

        bool operator==(const Multikey<Tp, Nm> &right)
        {
            return !(*this < right) && !(right < *this);
        }

    protected:
        size_t _sort_by{0};
};

template <class Tp>
class Dualkey : public Multikey<Tp,2>
{
    Dualkey(Tp _first, Tp _second) 
        : Multikey<Tp,2>(std::array<Tp,2>{_first, _second},0), 
        first{Multikey<Tp, 2>::keys[0]}, second{Multikey<Tp, 2>::keys[1]} {};
    Tp &first;
    Tp &second;
};

template <size_t Nm>
class Multikeyf : public Multikey<float, Nm>
{
    Multikeyf(std::array<float, Nm> _keys, size_t _sort_by)
        : Multikey<float,Nm>(_keys, _sort_by) {};
};

#endif