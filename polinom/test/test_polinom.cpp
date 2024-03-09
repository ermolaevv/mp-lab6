#include <gtest.h>
#include "Polinom.h"
using namespace std;

TEST(TPolinom, test1)
{
	TPolinom P, Q, res;
	
	int deg1[] = { 5, 2, 5 };
	int deg2[] = { 4, 3, 3 };
	int deg3[] = { 3, 5, 1 };
	int deg4[] = { 3, 2, 6 };
	int deg5[] = { 2, 1, 8 };

	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
	P.AddMonom(TMonom(7, 3, deg3));
	
	Q.AddMonom(TMonom(4, 3, deg4));
	Q.AddMonom(TMonom(-6, 3, deg5));
	
	res.AddMonom(TMonom(3, 3, deg1));
	res.AddMonom(TMonom(-5, 3, deg2));
	res.AddMonom(TMonom(7, 3, deg3));
	res.AddMonom(TMonom(4, 3, deg4));
	res.AddMonom(TMonom(-6, 3, deg5));

	ASSERT_EQ(res, P + Q);
}

TEST(TPolinom, test2)
{
	TPolinom P, Q, res;
	
	int deg1[] = {5, 2, 5};
	int deg2[] = {4, 3, 3};
	int deg3[] = {3, 5, 1};
	int deg4[] = {7, 2, 6};
	int deg5[] = {6, 1, 8};

	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
	P.AddMonom(TMonom(7, 3, deg3));
	
	Q.AddMonom(TMonom(4, 3, deg4));
	Q.AddMonom(TMonom(-6, 3, deg5));
	
	res.AddMonom(TMonom(3, 3, deg1));
	res.AddMonom(TMonom(-5, 3, deg2));
	res.AddMonom(TMonom(7, 3, deg3));
	res.AddMonom(TMonom(4, 3, deg4));
	res.AddMonom(TMonom(-6, 3, deg5));

	ASSERT_EQ(res, P + Q);
}

TEST(TPolinom, test3)
{
	TPolinom P, Q, res;
	
	int deg1[] = {5, 2, 5};
	int deg2[] = {4, 3, 3};
	int deg3[] = {3, 5, 1};

	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
	P.AddMonom(TMonom(7, 3, deg3));
	
	Q.AddMonom(TMonom(4, 3, deg1));
	Q.AddMonom(TMonom(-6, 3, deg2));
	
	res.AddMonom(TMonom(3, 3, deg1));
	res.AddMonom(TMonom(-5, 3, deg2));
	res.AddMonom(TMonom(7, 3, deg3));
	res.AddMonom(TMonom(4, 3, deg1));
	res.AddMonom(TMonom(-6, 3, deg2));

	ASSERT_EQ(res, P + Q);
}

TEST(TPolinom, test4)
{
	TPolinom P, Q, res;
	
	int deg1[] = {5, 2, 5};
	int deg2[] = {4, 3, 3};
	int deg3[] = {3, 5, 1};
	int deg4[] = {6, 2, 6};

	int deg5[] = {2, 1, 8};
	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
	P.AddMonom(TMonom(7, 3, deg3));
	
	Q.AddMonom(TMonom(4, 3, deg1));
	Q.AddMonom(TMonom(-6, 3, deg2));
	
	res.AddMonom(TMonom(3, 3, deg1));
	res.AddMonom(TMonom(-5, 3, deg2));
	res.AddMonom(TMonom(7, 3, deg3));
	res.AddMonom(TMonom(4, 3, deg1));
	res.AddMonom(TMonom(-6, 3, deg2));

	ASSERT_EQ(res, P + Q);
}

TEST(TPolinom, test5)
{
	TPolinom P, Q, res;
	
	int deg1[] = {5, 2, 5};
	int deg2[] = {4, 3, 3};
	int deg3[] = {7, 5, 1};

	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
    P.AddMonom(TMonom(7, 3, deg3));

    Q = P * -1.0;

	ASSERT_EQ(res, P + Q);
}
