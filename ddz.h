#pragma once
#include <functional>

namespace DDZ
{
	typedef unsigned char byte;

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
	enum Mask
	{
		// ��ʼ��
		Zero = 0x00,
		// ��4λ������ɫ
		Color = 0xF0,
		// ��4λ��������
		Number = 0x0F,
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

	// �Ʊ���
	const byte CardsMask[TotalCardsCount] =
	{
		0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, //���� A - K (14,15,3,4,5,...13)
		0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, //÷�� A - K (14,15,3,4,5,...13)
		0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, //���� A - K (14,15,3,4,5,...13)
		0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, //���� A - K (14,15,3,4,5,...13)
		0x4E, 0x4F, //��С��
	};

#pragma region ����

	class Util
	{
		// ������
		//typedef byte(*indexer)(byte);
		typedef std::function<byte(byte)> indexer;

	public:
		// ����ԭʼ����
		// output �����С����ΪTotalCardsCount bytes
		static void clone_cards_mask(byte* output, byte len = TotalCardsCount);

		// ��ȡ����
		static byte get_value(byte card);

		// ��ȡ��ɫ
		static byte get_color(byte card);

		// ��ȡ����
		static std::wstring get_description(byte card);

		// ��ȡ����
		static std::wstring get_description(byte* cards, byte cnt);

		// ��ȡ�߼�ֵ
		static byte get_logical_value(byte card);

		// ��ȡ�߼�ֵ
		static void get_logical_values(byte* inputCards, byte inputLen, byte** outputCards, byte outputLen);

		// ϴ��
		static void shuffle_cards(byte* cards, byte cnt);

		// ����
		// Ĭ�ϴӴ�С����
		static void sort_cards(byte* cards, byte cnt, bool orderFromSmallToLarge = false);

#pragma region �ж�����

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

#pragma region ��ȡ����

		static bool trait_double(byte* cards, byte cnt, byte** output, byte outputCnt);

#pragma endregion 

	private:
		// �ж�ָ�������������Ƿ��Сһ��
		static bool is_equal(byte* cards, byte cnt, byte indexesCount, ...);
		// �ж�ָ��������������Ƿ��Сһ��
		static bool is_equal(byte* cards, byte cnt, byte begin, byte end, indexer indexer);
		// �ж����Ƿ�Ϊ����
		static bool is_sequence(byte* cards, byte cnt);
		// �ж�ָ��������������Ƿ�Ϊ����
		static bool is_sequence(byte* cards, byte cnt, byte begin, byte end, indexer indexer);
		// �ж�ָ�������������ֵ�Ƿ�Ϊexpected
		static bool equal_to(byte* cards, byte cnt, byte expected, byte begin, byte end, indexer indexer);

		// У�����
		static bool verify_arguments(byte* cards, byte cnt);
		static bool verify_arguments(byte* cards, byte cnt, byte begin, byte end);

	};
}
