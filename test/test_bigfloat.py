from unittest import TestCase, main
import sys,os
path = os.path.join(os.path.dirname(__file__), "../")
sys.path.append(path)
import bigfloat

class BigfloatTestCase(TestCase):

    def test_s_to_bf_to_s(self):
        self.assertEqual(bigfloat.Number("0"), bigfloat.Number(" -0"))
        self.assertEqual(bigfloat.Number("0"), bigfloat.Number(" +0"))
        self.assertEqual(bigfloat.Number("0"), bigfloat.Number("0.00000"))
        self.assertEqual(bigfloat.Number("1"), bigfloat.Number("1.00000"))
        self.assertEqual(bigfloat.Number("0").get_sign(), bigfloat.Number("-0").get_sign())

    def test_cmp(self):
        a = bigfloat.Number("0")
        b = bigfloat.Number("-0")
        self.assertTrue(a==b)
        a = bigfloat.Number("0.001")
        b = bigfloat.Number("0")
        self.assertTrue(a>b)
        self.assertTrue(b<a)

    def test_add(self):
        def test_add_helper(ans, a, b):
            u = bigfloat.Number(ans)
            v = bigfloat.Number(a)
            w = bigfloat.Number(b)
            self.assertEqual(u, v+w)
        test_add_helper("3.3", "2.1", "1.2")
        test_add_helper("3.3", "2.1", "1.2")
        test_add_helper("1.0001", "1", "0.0001")
        test_add_helper("1009.91", "999.9", "10.01")
        test_add_helper("-321", "-200.1", "-120.9")
        test_add_helper("-21", "0.1", "-21.1")
        #test_add_helper("1", "1", "0.0000000000000000000000000000000000000000000000000000000000000000001")
        small_num = "0."
        for i in range(bigfloat.NDIGIT):
            small_num += "0"
        small_num += "1"
        test_add_helper("1", "1", small_num)

    def test_sub(self):
        def test_sub_helper(ans, a, b):
            u = bigfloat.Number(ans)
            v = bigfloat.Number(a)
            w = bigfloat.Number(b)
            self.assertEqual(u, v-w)
        test_sub_helper("3.3", "11.2", "7.9")
        test_sub_helper("-3.3", "7.9", "11.2")
        test_sub_helper("-1.0001", "-1", "0.0001")
        test_sub_helper("-1009.91", "-999.9", "10.01")
        test_sub_helper("-200.1", "-321", "-120.9")
        test_sub_helper("21", "-0.1", "-21.1")
        #test_sub_helper("21", "21", "0.0000000000000000000000000000000000000000000000000000000000000000001")
        small_num = "0."
        for i in range(bigfloat.NDIGIT):
            small_num += "0"
        small_num += "1"
        test_sub_helper("21", "21", small_num)

    def test_mul(self):
        def test_mul_helper(ans, a, b):
            u = bigfloat.Number(ans)
            v = bigfloat.Number(a)
            w = bigfloat.Number(b)
            self.assertEqual(u, v*w)
        test_mul_helper("2048", "32", "64")
        test_mul_helper("1 000 000", "0.001", "1 000 000 000")
        test_mul_helper("0.000 001", "1000", "0.000 000 001")
        test_mul_helper("0", "9999", "0")
        test_mul_helper("0", "0", "-0.9999")
        test_mul_helper("21", "-0.1", "-210")
        test_mul_helper("-21", "-210", "0.1")

    def test_div(self):
        def test_div_helper(ans, a, b):
            u = bigfloat.Number(ans)
            v = bigfloat.Number(a)
            w = bigfloat.Number(b)
            self.assertEqual(u, v/w)
        test_div_helper("64", "2048", "32")
        test_div_helper("1 000 000 000", "1 000 000", "0.001")
        test_div_helper("0.000 000 001","0.000 001", "1000")
        test_div_helper("0", "0", "-0.9999")
        test_div_helper("-210", "21", "-0.1")
        test_div_helper("0.1", "-21", "-210")

    def test_float(self):
        self.assertEqual(0.0,               float(bigfloat.Number("")))
        self.assertEqual(-7,                float(bigfloat.Number("-7")))
        self.assertEqual(13423412341234,    float(bigfloat.Number("13423412341234")))
        self.assertEqual(0.0000001431, float(bigfloat.Number("0.0000001431")))

    def test_int(self):
        self.assertEqual(0,              int(bigfloat.Number("")))
        self.assertEqual(-7,             int(bigfloat.Number("-7")))
        self.assertEqual(-7,             int(bigfloat.Number("-7.5")))
        self.assertEqual(13423412341234, int(bigfloat.Number("13423412341234")))
        self.assertEqual(0,              int(bigfloat.Number("0.000000000001431")))

    def test_sqrt(self):
        def test_sqrt_helper(ans, a):
            u = bigfloat.Number(ans)
            v = bigfloat.Number(a)
            self.assertEqual(u, bigfloat.sqrt(v))
        test_sqrt_helper( "32", "1024")
        test_sqrt_helper("1 000 000", "1 000 000 000 000")
        test_sqrt_helper("0.000 001", "0.000 000 000 001")
        test_sqrt_helper("0", "0")
        test_sqrt_helper("1", "1")

    def test_exp(self):
        self.assertEqual(bigfloat.Number("1"), bigfloat.exp(bigfloat.Number("0")))
        self.assertEqual(bigfloat.Number("1")/bigfloat.exp(bigfloat.Number("1")), bigfloat.exp(bigfloat.Number("-1")))
        self.assertEqual(bigfloat.Number("1")/bigfloat.exp(bigfloat.Number("123")), bigfloat.exp(bigfloat.Number("-123")))
        self.assertEqual(bigfloat.Number("1")/bigfloat.exp(bigfloat.Number("0.3")), bigfloat.exp(bigfloat.Number("-0.3")))
        def test_almost_equal(a, b, bound):
            err = a - b
            self.assertGreaterEqual(bigfloat.Number(bound), err)
            self.assertLessEqual(bigfloat.Number("-"+bound), err)
        test_almost_equal(bigfloat.exp(bigfloat.Number("1")), bigfloat.Number("2.71828 18284"), "0.00001")
        def test_exp_helper(a1, a2, a3, b, bound):
            a = bigfloat.exp(bigfloat.Number(a1))*bigfloat.exp(bigfloat.Number(a2))*bigfloat.exp(bigfloat.Number(a3))
            b = bigfloat.exp(bigfloat.Number(b))
            test_almost_equal(a, b, bound)
        test_exp_helper("1", "1", "1", "3",         "0.0000001")
        test_exp_helper("2", "3", "7", "12",        "0.0000001")
        test_exp_helper("0.2", "0.3", "0.9", "1.4", "0.0000001")

    def test_ln(self):
        def test_almost_equal(a, b, bound):
            err = a - b
            self.assertGreaterEqual(bigfloat.Number(bound), err)
            self.assertLessEqual(bigfloat.Number("-"+bound), err)
        test_almost_equal(bigfloat.Number("0"),                                         bigfloat.ln(bigfloat.Number("1")),     "0.00001")
        test_almost_equal(bigfloat.Number("3")*bigfloat.ln(bigfloat.Number("1")),       bigfloat.ln(bigfloat.Number("1")),     "0.00001")
        test_almost_equal(bigfloat.Number("3")*bigfloat.ln(bigfloat.Number("8")),       bigfloat.ln(bigfloat.Number("512")),   "0.00001")
        test_almost_equal(bigfloat.Number("3")*bigfloat.ln(bigfloat.Number("0.3")),     bigfloat.ln(bigfloat.Number("0.027")), "0.00001")
        test_almost_equal(bigfloat.Number("1"),                                 bigfloat.ln(bigfloat.Number("2.71828 18284")), "0.00001")
        def test_ln_helper(a1, a2, a3, b, bound):
            a = bigfloat.ln(bigfloat.Number(a1))+bigfloat.ln(bigfloat.Number(a2))+bigfloat.ln(bigfloat.Number(a3))
            b = bigfloat.ln(bigfloat.Number(b))
            test_almost_equal(a, b, bound)
        test_ln_helper("100", "10", "1", "1000",     "0.00001")
        test_ln_helper("2", "3", "7", "42",          "0.00001")
        test_ln_helper("0.2", "0.3", "0.9", "0.054", "0.00001")

    def test_rand(self):
        bigfloat.rand_seed(123)
        self.assertGreater(  bigfloat.rand(), bigfloat.Number())
        self.assertLess(     bigfloat.rand(), bigfloat.Number("1"))
        self.assertNotEqual( bigfloat.rand(), bigfloat.rand())

"""
    def test_underflow(self):
        a = bigfloat.Number("3")
        b = bigfloat.Number("3")
        c = bigfloat.Number("3")
        a.set_exp(0)
        b.set_exp(0)
        try:
            c = a*b
        except:
            print("qwerqerqw")
        self.assertRaises( Exception, a*b)
        #check documents -> extern "Python": reference
"""
"""
import cProfile
import unittest
import pstats
if __name__ == "__main__":
    #suite = unittest.TestLoader().discover(".")
    suite = unittest.TestLoader().discover("./test")
    def runtests():
        unittest.TextTestRunner().run(suite)
    s = cProfile.run("runtests()",sort="cumtime")
    
"""
if __name__ == "__main__":
    main()
