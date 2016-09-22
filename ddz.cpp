#include "ddz.h"
#include <algorithm>
#include <cstdarg>
#include <sstream>

namespace DDZ
{
	byte Util::get_value(byte mask)
	{
		return mask & Number;
	}

	byte Util::get_color(byte mask)
	{
		return (mask & Color) >> 4;
	}

	std::wstring Util::get_description(byte card)
	{
		auto color = get_color(card);
		auto value = get_logical_value(card);

		std::wstringstream description;
		switch (color)
		{
		case 0:
			description << L"♦";
			break;
		case 1:
			description << L"♣";
			break;
		case 2:
			description << L"♥";
			break;
		case 3:
			description << L"♠";
			break;
		case 4:
			description << L"";	// 毛
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
				description << (color == 4 ? L"King" : L"A");
				break;

			case 15:
				description << (color == 4 ? L"God" : L"2");
				break;
			}
		}

		return std::move(description.str());
	}

	std::wstring Util::get_description(byte* cards, byte cnt)
	{
		std::wstringstream ss;
		for(auto i = 0; i < cnt; ++i)
		{
			ss << get_description(cards[i]);
			ss << "\t";
		}

		return ss.str();
	}

	byte Util::get_logical_value(byte card)
	{
		auto color = get_color(card);
		auto number = get_value(card);

		// 大小王
		if (color == 0x40)
		{
			number += 15;
		}
		// A/2
		else if (number <= 2 && number > 0)
		{
			number += 13;
		}

		return number;
	}

	void Util::get_logical_values(byte* inputCards, byte inputLen, byte** outputCards, byte outputLen)
	{
		if (outputLen < inputLen)
			throw std::exception("get_logical_values failed, output buffer not enough!");

		memset(*outputCards, 0, outputLen);
		for (auto i = 0; i < inputLen; ++i)
		{
			(*outputCards)[i] = get_logical_value(inputCards[i]);
		}
	}

	void Util::clone_cards_mask(byte* output, byte bufSize)
	{
		memset(output, 0, bufSize);
		auto error = memcpy_s(output, bufSize, CardsMask, TotalCardsCount);
		if (error != 0)
			throw std::exception("clone_cards_mask failed! error = " + error);
	}

	void Util::shuffle_cards(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return;

		std::random_shuffle(cards, cards + cnt);
	}

	bool Util::verify_arguments(byte* cards, byte cnt)
	{
		if (cards == nullptr || cnt == 0)
		{
#ifdef _DEBUG
			throw std::exception("Invalid arguments");
#else
			return false;
#endif
		}

		return true;
	}

	bool Util::verify_arguments(byte* cards, byte cnt, byte begin, byte end)
	{
		auto ret = verify_arguments(cards, cnt);
		if (!ret)
			return false;

		if (begin > end || end > cnt)
		{
#ifdef _DEBUG
			throw std::exception("Invalid arguments");
#else
			return false;
#endif
		}

		return true;
	}

	void Util::sort_cards(byte* cards, byte cnt, bool orderFromSmallToLarge)
	{
		if (!verify_arguments(cards, cnt))
			return;

		if (cnt == 1)
			return;

		std::sort(cards, cards + cnt, [=](byte a, byte b)
		          {
			          return orderFromSmallToLarge ? get_logical_value(a) < get_logical_value(b) : get_logical_value(a) > get_logical_value(b);
		          });
	}

	bool Util::is_single(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		return cnt == 1;
	}

	bool Util::is_double(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		return cnt == 2 && is_equal(cards, cnt, 2, 0, 1);
	}

	bool Util::is_triple(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		return cnt == 3 && is_equal(cards, cnt, 3, 0, 1, 2);
	}

	bool Util::is_triple_plus_single(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		return cnt == 4 && (is_equal(cards, cnt, 3, 0, 1, 2) || is_equal(cards, cnt, 3, 1, 2, 3));
	}

	bool Util::is_triple_plus_double(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		return cnt == 5 && ((is_equal(cards, cnt, 3, 0, 1, 2) && is_equal(cards, cnt, 2, 3, 4)) || (is_equal(cards, cnt, 3, 2, 3, 4) && is_equal(cards, cnt, 2, 0, 1)));
	}

	bool Util::is_single_chain(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt < 5 || cnt > 12)
			return false;

		return is_sequence(cards, cnt);
	}

	bool Util::is_double_chain(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt % 2 != 0 || cnt < 5)
			return false;

		return is_double(cards, 2)
			&& is_sequence(cards, cnt, 0, cnt, [](auto idx)
			               {
				               return idx + 2;
			               })
			&& is_sequence(cards, cnt, 1, cnt, [](auto idx)
			               {
				               return idx + 2;
			               });
	}

	bool Util::is_triple_chain(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt % 3 != 0 || cnt < 5)
			return false;

		return is_triple(cards, cnt)
			&& is_sequence(cards, cnt, 0, cnt, [](auto idx)
			               {
				               return idx + 3;
			               })
			&& is_sequence(cards, cnt, 1, cnt, [](auto idx)
			               {
				               return idx + 3;
			               })
			&& is_sequence(cards, cnt, 2, cnt, [](auto idx)
			               {
				               return idx + 3;
			               });
	}

	bool Util::is_quadruple_plus_single(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt != 6)
			return false;

		return is_bomb(cards, 4)		// 炸弹在左侧
			|| is_bomb(cards + 1, 4)	// 炸弹在中间
			|| is_bomb(cards + 2, 4);	// 炸弹在右侧
	}

	bool Util::is_quadruple_plus_double(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt != 8)
			return false;

		return (is_bomb(cards, 4) && is_double(cards + 4, 2) && is_double(cards + 6, 2) && !is_bomb(cards + 4, 4))// 炸+对+对
			|| is_bomb(cards + 2, 4) && is_double(cards, 2) && is_double(cards + 6, 2) // 对+炸+对
			|| is_double(cards, 2) && is_double(cards + 2, 2) && !is_bomb(cards, 4) && is_bomb(cards + 4, 4); // 对+对+炸
	}

	bool Util::is_bomb(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt != 4)
			return false;

		return is_equal(cards, cnt, 4, 0, 1, 2, 3);
	}

	bool Util::is_missile(byte* cards, byte cnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		if (cnt != 2)
			return false;

		return is_equal(cards, cnt, 2, 0, 1, 2, 3);
	}

	bool Util::trait_double(byte* cards, byte cnt, byte** output, byte outputCnt)
	{
		if (!verify_arguments(cards, cnt))
			return false;


	}

	bool Util::is_equal(byte* cards, byte cnt, byte indexesCount, ...)
	{
		if (cnt < indexesCount)
#ifdef _DEBUG
			throw std::exception("invlid arguments");
#else
			return false;
#endif

		auto ret = true;

		va_list vl;
		va_start(vl, indexesCount);

		auto logic_num = 0;
		for (auto i = 0; i < indexesCount; ++i)
		{
			auto idx = va_arg(vl, byte);
			if (logic_num == 0)
				logic_num = get_logical_value(cards[idx]);
			else
			{
				if (logic_num != get_logical_value(cards[idx]))
				{
					ret = false;
					break;
				}
			}
		}

		va_end(vl);

		return ret;
	}

	bool Util::is_sequence(byte* cards, byte cnt)
	{
		return is_sequence(cards, cnt, 0, cnt, [](byte idx)
		                   {
			                   return idx + 1;
		                   });
	}

	bool Util::is_sequence(byte* cards, byte cnt, byte begin, byte end, indexer indexer)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		auto logic_num = 0;
		for (auto i = begin; i < end; i = indexer(i))
		{
			if (logic_num == 0)
				logic_num = get_logical_value(cards[i]);
			else
			{
				if (++logic_num != get_logical_value(cards[i]))
				{
					return false;
				}
			}
		}

		return true;
	}

	bool Util::equal_to(byte* cards, byte cnt, byte expected, byte begin, byte end, indexer indexer)
	{
		if (!verify_arguments(cards, cnt))
			return false;

		for (auto i = begin; i < end; i = indexer(i))
		{
			if (get_logical_value(cards[i]) != expected)
				return false;
		}

		return true;
	}

	bool Util::is_equal(byte* cards, byte cnt, byte begin, byte end, indexer indexer)
	{
		if (!verify_arguments(cards, cnt, begin, end))
			return false;

		auto expected = get_logical_value(cards[begin]);
		return equal_to(cards, cnt, expected, begin, end, indexer);
	}
}
