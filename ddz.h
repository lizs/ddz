#pragma once
#include <vector>

namespace DDZ
{
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
	// |----|----|----|----|
	// 保留(4bits)+花色(4bits)+值(8bits)
	enum Mask
	{
		// 高4位表征花色
		Color = 0x0F00,
		// 低4位表征数字
		Value = 0x00FF,
	};

	enum Color
	{
		// 方片
		Square = 0x0100,
		// 梅花
		Plum = 0x0200,
		// 红桃
		RedHeart = 0x0300,
		// 黑桃
		BlackHeart = 0x0400,
		// 小王
		Queen = 0x0500,
		// 大王
		King = 0x0600,
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

	const std::vector<short> CardsMask =
	{
		0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x010E, 0x010F, //方块 3 -> 10 -> K -> A -> 2
		0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 0x020A, 0x020B, 0x020C, 0x020D, 0x020E, 0x020F, //梅花 3 -> 10 -> K -> A -> 2
		0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E, 0x030F, //红桃 3 -> 10 -> K -> A -> 2
		0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, //黑桃 3 -> 10 -> K -> A -> 2
		0x0510,	// 小毛
		0x0611,	// 大毛
	};

#pragma region 方法

	class Util
	{
	public:
		// 拷贝原始牌码
		static std::vector<short> clone_cards_mask();

		// 获取数字
		static short get_value(short card);

		// 获取花色
		static short get_color(short card);

		// 获取名字
		static std::wstring get_description(short card);

		// 获取描述
		static std::wstring get_description(const std::vector<short> & cards);

		// 洗牌
		static void shuffle_cards(std::vector<short> & cards);

		// 排序
		// 默认从大到小排序
		static void sort_cards(std::vector<short> & cards, bool orderFromSmallToLarge = false);

		// 判断是否存在指定牌
		static bool contains(const std::vector<short> & cards, short card);
		static bool contains(const std::vector<short> & cards, const std::vector<short> & subcards);

#pragma region 判断牌型

		static bool is_double(const std::vector<short> & cards);
		static bool is_triple(const std::vector<short> & cards);

		static bool is_triple_plus_single(const std::vector<short> & cards);
		static bool is_triple_plus_double(const std::vector<short> & cards);
		static bool is_single_chain(const std::vector<short> & cards);
		static bool is_double_chain(const std::vector<short> & cards);
		static bool is_triple_chain(const std::vector<short> & cards);
		static bool is_triple_chain_plus_single(const std::vector<short> & cards);
		static bool is_triple_chain_plus_double(const std::vector<short> & cards);
		static bool is_quadruple_plus_single(const std::vector<short> & cards);
		static bool is_quadruple_plus_double(const std::vector<short> & cards);
		static bool is_bomb(const std::vector<short> & cards);
		static bool is_missile(const std::vector<short> & cards);

#pragma endregion 

#pragma region 提取牌型
		
#pragma endregion 

	private:
		// 判断指定索引区间的牌是否大小一致
		static bool is_same(const std::vector<short> & cards);
		static bool is_same(const std::vector<short> & cards, int from, int cnt);

		// 参数校验
		static bool verify(const std::vector<short> & cards, int from, int cnt);

		// 判断牌是否为序列
		static bool is_sequence(const std::vector<short> & cards);
		static bool is_sequence(const std::vector<short> & cards, int step);
		static bool is_sequence(const std::vector<short>& cards, int from, int step);
		static bool is_sequence(const std::vector<short>& cards, int from, int to, int step);
	};
}
