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
    TPolinom P;
    int deg1[] = { 3, 1, 0 };
    int deg2[] = { 1, 2, 2 };
    P.AddMonom(TMonom(4, 3, deg1)); // 4*x0^3*x1
    P.AddMonom(TMonom(-3, 3, deg2)); // -3*x0*x1^2*x2^2
    TPolinom integrated_P = P.Integrate(1); 
    EXPECT_EQ("2*x0^3*x1^2 - 1*x0*x1^3*x2^2", integrated_P.ToString());
}


TEST(TPolinom, DifferentiationTest) {
    TPolinom P;
    int deg1[] = { 3, 1, 0 };
    int deg2[] = { 1, 2, 2 };
    P.AddMonom(TMonom(4, 3, deg1)); // 4*x0^3*x1
    P.AddMonom(TMonom(-3, 3, deg2)); // -3*x0*x1^2*x2^2
    TPolinom diff_P = P.Differentiation(1); 
    EXPECT_EQ("4*x0^3 - 6*x0*x1*x2^2", diff_P.ToString());
}



TEST(TPolinom, CalculateDefiniteIntegralTest) {
    TPolinom P(3); 
    int deg[] = { 2, 0, 0 };
    P.AddMonom(TMonom(3, 3, deg)); 
    double start[] = { 0, 0, 0 }; 
    double end[] = { 1, 0, 0 }; 
    double integral = P.CalculateDefiniteIntegral(0, start, end); 
    EXPECT_DOUBLE_EQ(1.0, integral); 
}
