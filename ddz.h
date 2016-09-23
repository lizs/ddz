#pragma once
#include <vector>

namespace DDZ
{
	// ����
	enum Category
	{
		Invalid,

		//	��
		Single,
		// ��
		Double,
		// ��
		Triple,

		// ����
		SingleChain,
		// ����
		DoubleChain,
		// ����
		TripleChain,

		// ������
		TriplePlusSingle,
		// ������
		TriplePlusDouble,

		// �Ĵ���
		QuadruplePlusSingle,
		// �Ĵ���
		QuadruplePlusDouble,

		// ը��
		Bomb,
		// ���
		Missile,
	};

	// ����
	// |----|----|----|----|
	// ����(4bits)+��ɫ(4bits)+ֵ(8bits)
	enum Mask
	{
		// ��4λ������ɫ
		Color = 0x0F00,
		// ��4λ��������
		Value = 0x00FF,
	};

	enum Color
	{
		// ��Ƭ
		Square = 0x0100,
		// ÷��
		Plum = 0x0200,
		// ����
		RedHeart = 0x0300,
		// ����
		BlackHeart = 0x0400,
		// С��
		Queen = 0x0500,
		// ����
		King = 0x0600,
	};

	enum Constants
	{
		// ��������
		HandCardsCount = 3,
		// ũ���ʼ������
		FarmerInitCardsCount = 17,
		// ������ʼ������
		LandlordInitCardsCount = 20,
		// ��������
		TotalCardsCount = 54,
	};

	const std::vector<short> CardsMask =
	{
		0x0103, 0x0104, 0x0105, 0x0106, 0x0107, 0x0108, 0x0109, 0x010A, 0x010B, 0x010C, 0x010D, 0x010E, 0x010F, //���� 3 -> 10 -> K -> A -> 2
		0x0203, 0x0204, 0x0205, 0x0206, 0x0207, 0x0208, 0x0209, 0x020A, 0x020B, 0x020C, 0x020D, 0x020E, 0x020F, //÷�� 3 -> 10 -> K -> A -> 2
		0x0303, 0x0304, 0x0305, 0x0306, 0x0307, 0x0308, 0x0309, 0x030A, 0x030B, 0x030C, 0x030D, 0x030E, 0x030F, //���� 3 -> 10 -> K -> A -> 2
		0x0403, 0x0404, 0x0405, 0x0406, 0x0407, 0x0408, 0x0409, 0x040A, 0x040B, 0x040C, 0x040D, 0x040E, 0x040F, //���� 3 -> 10 -> K -> A -> 2
		0x0510,	// Сë
		0x0611,	// ��ë
	};

#pragma region ����

	class Util
	{
	public:
		// ����ԭʼ����
		static std::vector<short> clone_cards_mask();

		// ��ȡ����
		static short get_value(short card);

		// ��ȡ��ɫ
		static short get_color(short card);

		// ��ȡ����
		static std::wstring get_description(short card);

		// ��ȡ����
		static std::wstring get_description(const std::vector<short> & cards);

		// ϴ��
		static void shuffle_cards(std::vector<short> & cards);

		// ����
		// Ĭ�ϴӴ�С����
		static void sort_cards(std::vector<short> & cards, bool orderFromSmallToLarge = false);

		// �ж��Ƿ����ָ����
		static bool contains(const std::vector<short> & cards, short card);
		static bool contains(const std::vector<short> & cards, const std::vector<short> & subcards);

#pragma region �ж�����

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

#pragma region ��ȡ����
		
#pragma endregion 

	private:
		// �ж�ָ��������������Ƿ��Сһ��
		static bool is_same(const std::vector<short> & cards);
		static bool is_same(const std::vector<short> & cards, int from, int cnt);

		// ����У��
		static bool verify(const std::vector<short> & cards, int from, int cnt);

		// �ж����Ƿ�Ϊ����
		static bool is_sequence(const std::vector<short> & cards);
		static bool is_sequence(const std::vector<short> & cards, int step);
		static bool is_sequence(const std::vector<short>& cards, int from, int step);
		static bool is_sequence(const std::vector<short>& cards, int from, int to, int step);
	};
}
