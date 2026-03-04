#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


#include <float.h>
#include <math.h>
#include <stdio.h>

char *dtoa(double dd, int mode, int ndigits, int *decpt, int *sign, char **rve);
/* 
    * mode - indicates the way the string is generated
    * ndigits - 
    * decpt - if d is +-Infinity or NaN, *decpt is set to 9999, otherwise it is set to decimal point position
    * sign - read sign of dd
    * rve - if not NULL, points to the end of return value
*/

void test_dtoa_positive_number(void){
    int decpt;
    int sign;
    char *rve;
    double val = 123.45;

    char *result = dtoa(val, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT_EQUAL(decpt, 3);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_negative_number(void){
    int decpt;
    int sign;
    char *rve;
    double val = -123.45;

    char *result = dtoa(val, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 1);
    CU_ASSERT_EQUAL(decpt, 3);
    CU_ASSERT(strlen(result) > 0);
    CU_ASSERT_STRING_EQUAL(result, "12345");
}

void test_dtoa_zero(void){
    int decpt;
    int sign;
    char *rve;
    double val = 0.0;

    char *result = dtoa(val, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT_EQUAL(decpt, 1);
    CU_ASSERT(strlen(result) > 0);
    CU_ASSERT_STRING_EQUAL(result, "0");
}

void test_dtoa_large_positive_number(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(DBL_MAX, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_small_positive_number(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(DBL_MIN, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_nan(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(NAN, 0, 0, &decpt, &sign, &rve);
    
    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(decpt, 9999);
    CU_ASSERT(strlen(result) > 0);
    CU_ASSERT_STRING_EQUAL(result, "NaN");
}

void test_dtoa_positive_inf(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(INFINITY, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT_EQUAL(decpt, 9999);
    CU_ASSERT(strlen(result) > 0);
    CU_ASSERT_STRING_EQUAL(result, "Infinity");
}

void test_dtoa_negative_inf(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(-INFINITY, 0, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 1);
    CU_ASSERT_EQUAL(decpt, 9999);
    CU_ASSERT(strlen(result) > 0);
    CU_ASSERT_STRING_EQUAL(result, "Infinity");
}

void test_dtoa_very_big_positive_number(void){
    int decpt;
    int sign;
    char *rve;
    double val = DBL_MAX*0.9999;

    char *result = dtoa(val, 2, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT(decpt != 9999);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_very_small_positive_number(void){
    int decpt;
    int sign;
    char *rve;
    double val = DBL_MIN*0.9999;

    char *result = dtoa(val, 2, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 0);
    CU_ASSERT(decpt != 9999);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_very_small_negative_number(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(-DBL_MAX*0.9999, 2, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 1);
    CU_ASSERT(decpt != 9999);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_very_big_negative_number(void){
    int decpt;
    int sign;
    char *rve;

    char *result = dtoa(-DBL_MIN*0.9999, 2, 0, &decpt, &sign, &rve);

    CU_ASSERT_PTR_NOT_NULL(result);
    CU_ASSERT_EQUAL(sign, 1);
    CU_ASSERT(decpt != 9999);
    CU_ASSERT(strlen(result) > 0);
}

void test_dtoa_numbers_close_to_1(void){
    int decpt;
    int sign;
    char *rve;
    double vals[] = {0.9999999999999999999999999999999999999999999999, 
                     1.0000000000000000000000000000000000000000000002,
                     0.9999999999999999999999999999999999999999999995,
                     1.0000000000000000000000000000000000000000000004};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 2, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, 0);
        CU_ASSERT_EQUAL(decpt, 1);
        CU_ASSERT(strlen(result) > 0);
        CU_ASSERT_STRING_EQUAL(result, "1");
    }
}

void test_dtoa_numbers_close_to_negative_1(void){
    int decpt;
    int sign;
    char *rve;
    double vals[] = {-0.9999999999999999999999999999999999999999999999, 
                     -1.0000000000000000000000000000000000000000000002,
                     -0.9999999999999999999999999999999999999999999995,
                     -1.0000000000000000000000000000000000000000000004};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 2, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, 1);
        CU_ASSERT_EQUAL(decpt, 1);
        CU_ASSERT(strlen(result) > 0);
        CU_ASSERT_STRING_EQUAL(result, "1");
    }
}

void test_dtoa_positive_halfway_complex(void) {
    int decpt;
    int sign;
    char *rve;
    double vals[] = {0.9999999999999999999999999999999999999999999995, 
                     1.0000000000000000000000000000000000000000000005,
                     99999999999999999999999999.999999999999999999995,
                     10000000000000000000000000000000.000000000000004};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 2, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, 0);
        CU_ASSERT(decpt != 9999);
        CU_ASSERT(strlen(result) > 0);
    }
}

void test_dtoa_negative_halfway_complex(void) {
    int decpt;
    int sign;
    char *rve;
    double vals[] = {-0.9999999999999999999999999999999999999999999995, 
                     -1.0000000000000000000000000000000000000000000005,
                     -99999999999999999999999999.999999999999999999995,
                     -10000000000000000000000000000000.000000000000004};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 2, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, 1);
        CU_ASSERT(decpt != 9999);
        CU_ASSERT(strlen(result) > 0);
    }
}

void test_dtoa_precision_and_mode_3(void){
    int decpt;
    int sign;
    char *rve;
    double vals[] = {148632148632147862114141.99999999999999999999995, 
                     -148632148632147862114141.99999999999999999999995,
                     3.1415926535897932384626433832795028841971693993,
                     -3.1415926535897932384626433832795028841971693993};

    int signs[] = {0,1,0,1};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 3, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, signs[i]);
        CU_ASSERT(decpt != 9999);
        CU_ASSERT(strlen(result) > 0);
    }
}

void test_dtoa_precision_and_mode_4(void){
    int decpt;
    int sign;
    char *rve;
    double vals[] = {148632148632147862114141.99999999999999999999995, 
                     -148632148632147862114141.99999999999999999999995,
                     3.1415926535897932384626433832795028841971693993,
                     -3.1415926535897932384626433832795028841971693993};

    int signs[] = {0,1,0,1};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 4, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, signs[i]);
        CU_ASSERT(decpt != 9999);
        CU_ASSERT(strlen(result) > 0);
    }
}

void test_dtoa_precision_and_mode_5(void){
    int decpt;
    int sign;
    char *rve;
    double vals[] = {148632148632147862114141.99999999999999999999995, 
                     -148632148632147862114141.99999999999999999999995,
                     3.1415926535897932384626433832795028841971693993,
                     -3.1415926535897932384626433832795028841971693993};

    int signs[] = {0,1,0,1};

    for(int i = 0; i < 4; i++){
        char *result = dtoa(vals[i], 5, 47, &decpt, &sign, &rve);

        CU_ASSERT_PTR_NOT_NULL(result);
        CU_ASSERT_EQUAL(sign, signs[i]);
        CU_ASSERT(decpt != 9999);
        CU_ASSERT(strlen(result) > 0);
    }
}

int main(){
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("dtoa_test_suite", 0, 0);

    CU_add_test(suite, "test_dtoa_positive_number", test_dtoa_positive_number);
    CU_add_test(suite, "test_dtoa_negative_number", test_dtoa_negative_number);
    CU_add_test(suite, "test_dtoa_zero", test_dtoa_zero);
    CU_add_test(suite, "test_dtoa_large_positive_number", test_dtoa_large_positive_number);
    CU_add_test(suite, "test_dtoa_small_positive_number", test_dtoa_small_positive_number);
    CU_add_test(suite, "test_dtoa_nan", test_dtoa_nan);
    CU_add_test(suite, "test_dtoa_positive_inf", test_dtoa_positive_inf);
    CU_add_test(suite, "test_dtoa_negative_inf", test_dtoa_negative_inf);
    CU_add_test(suite, "test_dtao_very_big_positive_number", test_dtoa_very_big_positive_number);
    CU_add_test(suite, "test_dtoa_very_small_positive_number", test_dtoa_very_small_positive_number);
    CU_add_test(suite, "test_dtoa_very_big_negative_number", test_dtoa_very_big_negative_number);
    CU_add_test(suite, "test_dtoa_very_small_positive_number", test_dtoa_very_small_positive_number);
    CU_add_test(suite, "test_dtoa_numbers_close_to_1", test_dtoa_numbers_close_to_1);
    CU_add_test(suite, "test_dtoa_numbers_close_to_negative_1", test_dtoa_numbers_close_to_negative_1);
    CU_add_test(suite, "test_dtoa_positive_halfway_complex", test_dtoa_positive_halfway_complex);
    CU_add_test(suite, "test_dtoa_negative_halfway_complex", test_dtoa_negative_halfway_complex);
    CU_add_test(suite, "test_dtoa_precision_and_mode_3", test_dtoa_precision_and_mode_3);
    CU_add_test(suite, "test_dtoa_precision_and_mode_4", test_dtoa_precision_and_mode_4);
    CU_add_test(suite, "test_dtoa_precision_and_mode_5", test_dtoa_precision_and_mode_5);

    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}