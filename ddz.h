#pragma once
#include <functional>

namespace DDZ
{
	typedef unsigned char byte;

	// 类型
	enum Category
	{
		Invalid,

		//	单
		Single,
		// 对
		Double,
		// 三
		Triple,

		// 单连
		SingleChain,
		// 对连
		DoubleChain,
		// 三连
		TripleChain,

		// 三带单
		TriplePlusSingle,
		// 三带对
		TriplePlusDouble,

		// 四带单
		QuadruplePlusSingle,
		// 四带对
		QuadruplePlusDouble,

		// 炸弹
		Bomb,
		// 火箭
		Missile,
	};

	// 掩码
	enum Mask
	{
		// 初始码
		Zero = 0x00,
		// 高4位表征花色
		Color = 0xF0,
		// 低4位表征数字
		Number = 0x0F,
	};

	enum Constants
	{
		// 底牌张数
		HandCardsCount = 3,
		// 农民初始牌张数
		FarmerInitCardsCount = 17,
		// 地主初始牌张数
		LandlordInitCardsCount = 20,
		// 总牌张数
		TotalCardsCount = 54,
	};

	// 牌编码
	const byte CardsMask[TotalCardsCount] =
	{
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, //方块 A - K (14,15,3,4,5,...13)
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, //梅花 A - K (14,15,3,4,5,...13)
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, //红桃 A - K (14,15,3,4,5,...13)
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, //黑桃 A - K (14,15,3,4,5,...13)
		0x4E, 0x4F, //大小王
	};

#pragma region 方法

	class Util
	{
		// 迭代器
		//typedef byte(*indexer)(byte);
		typedef std::function<byte(byte)> indexer;

	public:
		// 拷贝原始牌码
		// output 数组大小至少为TotalCardsCount bytes
		static void clone_cards_mask(byte* output, byte len = TotalCardsCount);

		// 获取数字
		static byte get_value(byte card);

		// 获取花色
		static byte get_color(byte card);

		// 获取名字
		static std::wstring get_description(byte card);

		// 获取描述
		static std::wstring get_description(byte* cards, byte cnt);

		// 获取逻辑值
		static byte get_logical_value(byte card);

		// 获取逻辑值
		static void get_logical_values(byte* inputCards, byte inputLen, byte** outputCards, byte outputLen);

		// 洗牌
		static void shuffle_cards(byte* cards, byte cnt);

		// 排序
		// 默认从大到小排序
		static void sort_cards(byte* cards, byte cnt, bool orderFromSmallToLarge = false);

#pragma region 判断牌型

		static bool is_single(byte* cards, byte cnt);
		static bool is_double(byte* cards, byte cnt);
		static bool is_triple(byte* cards, byte cnt);
		static bool is_triple_plus_single(byte* cards, byte cnt);
		static bool is_triple_plus_double(byte* cards, byte cnt);
		static bool is_single_chain(byte* cards, byte cnt);
		static bool is_double_chain(byte* cards, byte cnt);
		static bool is_triple_chain(byte* cards, byte cnt);
		static bool is_quadruple_plus_single(byte* cards, byte cnt);
		static bool is_quadruple_plus_double(byte* cards, byte cnt);
		static bool is_bomb(byte* cards, byte cnt);
		static bool is_missile(byte* cards, byte cnt);

#pragma endregion 

#pragma region 提取牌型

		static bool trait_double(byte* cards, byte cnt, byte** output, byte outputCnt);

#pragma endregion 

	private:
		// 判断指定索引处的牌是否大小一致
		static bool is_equal(byte* cards, byte cnt, byte indexesCount, ...);
		// 判断指定索引区间的牌是否大小一致
		static bool is_equal(byte* cards, byte cnt, byte begin, byte end, indexer indexer);
		// 判断牌是否为序列
		static bool is_sequence(byte* cards, byte cnt);
		// 判断指定索引区间的牌是否为序列
		static bool is_sequence(byte* cards, byte cnt, byte begin, byte end, indexer indexer);
		// 判断指定索引区间的牌值是否为expected
		static bool equal_to(byte* cards, byte cnt, byte expected, byte begin, byte end, indexer indexer);

		// 校验参数
		static bool verify_arguments(byte* cards, byte cnt);
		static bool verify_arguments(byte* cards, byte cnt, byte begin, byte end);

	};
}
