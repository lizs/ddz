#include "ddz.h"
#include <algorithm>
#include <sstream>

namespace DDZ
{
	std::vector<short> Util::clone_cards_mask()
	{
		return std::vector<short>(CardsMask);
	}

	short Util::get_value(short card)
	{
		return card & Mask::Value;
	}

	short Util::get_color(short card)
	{
		return card & Mask::Color;
	}

	std::wstring Util::get_description(short card)
	{
		auto color = get_color(card);
		auto value = get_value(card);

		std::wstringstream description;
		switch (color)
		{
		case Color::Square:
			description << L"♦";
			break;
		case Color::Plum:
			description << L"♣";
			break;
		case Color::RedHeart:
			description << L"♥";
			break;
		case Color::BlackHeart:
			description << L"♠";
			break;
		case Color::Queen:
		case Color::King:
			description << L"";
			break;

		default:
			description << L"×";
			break;
		}

		if(value < 11)
		{
			description << value;
		}
		else
		{
			switch (value)
			{
			case 11:
				description << L"J";
				break;

			case 12:
				description << L"Q";
				break;

			case 13:
				description << L"K";
				break;

			case 14:
				description << L"A";
				break;

			case 15:
				description << L"2";
				break;

			case 16:
				description << L"Queen";
				break;

			case 17:
				description << L"King";
				break;
			}
		}

		return std::move(description.str());
	}

	std::wstring Util::get_description(const std::vector<short> & cards)
	{
		std::wstringstream ss;
		for(auto card : cards)
		{
			ss << get_description(card);
			ss << "\t";
		}

		return ss.str();
	}

	void Util::shuffle_cards(std::vector<short>& cards)
	{
		std::random_shuffle(cards.begin(), cards.end());
	}

	void Util::sort_cards(std::vector<short>& cards, bool l2h)
	{
		if (cards.size() == 1)
			return;

		std::sort(cards.begin(), cards.end(), [=](short a, short b)
		          {
			          return l2h ? get_value(a) < get_value(b) : get_value(a) > get_value(b);
		          });
	}

	bool Util::contains(const std::vector<short>& cards, short card)
	{
		return std::find(cards.begin(), cards.end(), card) != cards.end();
	}

	bool Util::contains(const std::vector<short>& cards, const std::vector<short>& subcards)
	{
		return std::all_of(subcards.begin(), subcards.end(), [&cards](short card)
		                   {
			                   return contains(cards, card);
		                   });
	}

	bool Util::is_double(const std::vector<short>& cards)
	{
		if (!verify(cards, 0, 2)) return false;
		return cards.size() == 2 && is_same(cards);
	}

	bool Util::is_triple(const std::vector<short>& cards)
	{
		if (!verify(cards, 0, 3)) return false;
		return cards.size() == 3 && is_same(cards);
	}
	
	bool Util::is_triple_plus_single(const std::vector<short>& cards)
	{
		return cards.size() == 4 && is_triple_chain_plus_single(cards);
	}

	bool Util::is_triple_plus_double(const std::vector<short>& cards)
	{
		return cards.size() == 5 && is_triple_chain_plus_double(cards);
	}

	bool Util::is_single_chain(const std::vector<short>& cards)
	{
		auto cnt = cards.size();
		if (cnt < 5 || cnt > 12)
			return false;

		return is_sequence(cards);
	}

	bool Util::is_double_chain(const std::vector<short>& cards)
	{
		auto cnt = cards.size();
		if (cnt % 2 != 0 || cnt < 5)
			return false;

		return is_sequence(cards, 2);
	}

	bool Util::is_triple_chain(const std::vector<short>& cards)
	{
		auto cnt = cards.size();
		if (cnt % 3 != 0 || cnt < 5)
			return false;

		return is_sequence(cards, 3);
	}

	bool Util::is_triple_chain_plus_single(const std::vector<short>& cards)
	{
		// N*3 + N = 4*N   N∈[1, 5]
		auto cnt = cards.size();
		if (cnt % 4 != 0 || cnt < 4 || cnt > 20)
			return false;

		// 存在三连即可
		auto n = cnt / 4;
		for (auto i = 0; i < n; ++i)
		{
			if (is_sequence(cards, i, n * 3, 3))
				return true;
		}

		return false;
	}

	bool Util::is_triple_chain_plus_double(const std::vector<short>& cards)
	{
		// N*3 + N*2 = 5*N   N∈[1, 4]
		auto cnt = cards.size();
		if (cnt % 5 != 0 || cnt < 10 || cnt > 20)
			return false;

		// 存在三连，且其余皆为对子
		auto n = cnt / 5;
		for (auto i = 0; i < n; ++i)
		{
			auto match = true;

			// 三连之前的对子
			for (auto j = 0; j < i; ++j)
			{
				if (!is_same(cards, 2 * j, 2))
				{
					match = false;
					break;
				}
			}

			// 三连
			if(match)
			{
				if (!is_sequence(cards, i, n * 3, 3))
				{
					match = false;
				}
			}

			// 三连之后的对子
			if(match)
			{
				auto head = 2 * (i - 1) + n * 3;
				for (auto j =0; j < n - i; ++j)
				{
					if (!is_same(cards, head + 2 * j, 2))
					{
						match = false;
						break;
					}
				}
			}

			if (match)
				return true;
		}

		return false;
	}

	bool Util::is_quadruple_plus_single(const std::vector<short>& cards)
	{
		if (cards.size() != 6)
			return false;

		// 左中右
		return is_same(cards, 0, 4)
			|| is_same(cards, 1, 4)
			|| is_same(cards, 2, 4);
	}

	bool Util::is_quadruple_plus_double(const std::vector<short>& cards)
	{
		if (cards.size() != 8)
			return false;

		// 左中右
		return (is_same(cards, 0, 4) && is_same(cards, 4, 2) && is_same(cards, 6, 2) && !is_same(cards, 4, 4))
			|| (is_same(cards, 0, 2) && is_same(cards, 2, 4) && is_same(cards, 6, 2)
			|| (is_same(cards, 0, 2) && is_same(cards, 2, 2) && is_same(cards, 4, 4) && !is_same(cards, 0, 4)));
	}

	bool Util::is_bomb(const std::vector<short>& cards)
	{
		auto cnt = cards.size();

		if (cnt != 4)
			return false;

		return is_same(cards);
	}

	bool Util::is_missile(const std::vector<short>& cards)
	{
		auto cnt = cards.size();
		if (cnt != 2)
			return false;

		return get_color(cards[0]) == Color::Queen && get_color(cards[1]) == Color::King;
	}

	bool Util::is_same(const std::vector<short>& cards)
	{
		return is_same(cards, 0, cards.size());
	}

	bool Util::is_same(const std::vector<short>& cards, int begin, int cnt)
	{
		if (!verify(cards, begin, cnt)) return false;
		if (cnt < 2) return true;

		auto expected = get_value(cards[begin]);
		return std::all_of(cards.begin() + 1, cards.end(), [=](auto card)
		{
			return get_value(card) == expected;
		});
	}

	bool Util::verify(const std::vector<short>& cards, int begin, int cnt)
	{
		return !(begin < 0 || cnt < 0 || cnt < 0 || cards.size() < begin + cnt);
	}

	bool Util::is_sequence(const std::vector<short>& cards)
	{
		return is_sequence(cards, 1);
	}

	bool Util::is_sequence(const std::vector<short>& cards, int step)
	{
		return is_sequence(cards, 0, step);
	}

	bool Util::is_sequence(const std::vector<short>& cards, int from, int step)
	{
		return is_sequence(cards, from, cards.size() - from, step);
	}

	bool Util::is_sequence(const std::vector<short>& cards, int from, int cnt, int step)
	{
		if (!verify(cards, from, cnt))
			return false;

		if (step < 1 || cnt % step != 0)
			return false;

		auto expected = 0;
		for (auto i = from; i < cnt; i += step)
		{
			if (!is_same(cards, i, step))
				return false;

			if (expected == 0)
				expected = get_value(cards[i]);
			else
			{
				if (expected != get_value(cards[i]))
					return false;

				++expected;
			}
		}

		return true;
	}
}
