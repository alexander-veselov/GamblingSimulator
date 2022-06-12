#include "gtest/gtest.h"

#include "../Core/Slot.h"

// Board:
// K O O
// Q Q W
// W A A
// Win : 32

TEST(TestSlot, Lines1)
{
	Lines lines;
	Symbols symbols;

	Symbol O = Symbol(0, "O", { 1 });
	Symbol J = Symbol(1, "J", { 2 });
	Symbol Q = Symbol(2, "Q", { 4 });
	Symbol K = Symbol(3, "K", { 8 });
	Symbol A = Symbol(4, "A", { 16 });
	Symbol W = Symbol(5, "W", { 32 });

	symbols.AddSymbol(0.30, O);
	symbols.AddSymbol(0.25, J);
	symbols.AddSymbol(0.17, Q);
	symbols.AddSymbol(0.13, K);
	symbols.AddSymbol(0.10, A);
	symbols.AddSymbol(0.05, W);

	Slot slot(3, 3, symbols, lines);

	Board board{
		{K, O, O},
		{Q, Q, W},
		{W, A, A},
	};
	slot.SetBoard(board);

	EXPECT_EQ(slot.MakeSpin(), 0);
}

TEST(TestActions, AssertTrue)
{
	ASSERT_TRUE(false);
}