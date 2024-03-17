#include <gtest/gtest.h>
#include "Polinom.h"
using namespace std;

const double EPSILON = 1e-6;

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

TEST(TPolinom, Calculate_test)
{
	TPolinom P;
	
	int deg1[] = {2, 1, 1};
	int deg2[] = {1, 1, 2};
	int deg3[] = {1, 2, 1};

	P.AddMonom(TMonom(3, 3, deg1));
	P.AddMonom(TMonom(-5, 3, deg2));
    P.AddMonom(TMonom(7, 3, deg3));

    double values[] = { 2, 3, 4 };
    ASSERT_EQ(168, round(P.Calculate(3, values) * 100) / 100);
}


TEST(TPolinom, IntegrateTest) {
    int deg[] = { 2, 1, 3 }; 
    TMonom monom(5.0, 3, deg);

    TMonom integrated_monom = monom.Integrate_Monom(1);

    double expected_coeff = 5.0 / 2; 
    int expected_deg[] = { 2, 2, 3 }; 
    TMonom expected_monom(expected_coeff, 3, expected_deg);

    ASSERT_EQ(integrated_monom, expected_monom);
}


TEST(TPolinomTest, DifferentiationTest) {
    int deg[] = { 2, 1, 3 }; 
    TMonom monom(5.0, 3, deg);

    TMonom diff_monom = monom.Differentiation_Monom(1);

    double expected_coeff = 5.0 * 1; 
    int expected_deg[] = { 2, 0, 3 }; 
    TMonom expected_monom(expected_coeff, 3, expected_deg);

    ASSERT_EQ(diff_monom, expected_monom);
}

