#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <jansson.h>
#include <string.h>
#include <stdio.h>

void test_json_loads_with_unicode_valide(void) {

    const char* valid_input[] = {
        "\"Hello, World!\"",
        "\"Привет, мир!\"", 
        "\"你好，世界\"",
        "\"😘💜🧡\"",
        NULL 
    };

   
    for (int i = 0; valid_input[i] != NULL; i++) {
        json_error_t error;
        json_t *result = json_loads(valid_input[i], 0, &error);
        
        CU_ASSERT_PTR_NOT_NULL_FATAL(result);
        CU_ASSERT(json_is_string(result));
        
        const char *str = json_string_value(result);
        CU_ASSERT_PTR_NOT_NULL(str);
        CU_ASSERT(strlen(str) > 0);
        
        json_decref(result);
    }

}

void test_json_loads_with_unicode_invalide(void) {
    const char* invalid_input[] = {
        "\"\x80\"",
        "\"\xC0\x80\"",
        "\"\xE0\x80\x80\"",
        "\"\xED\xA0\x80\"",
        "\"\xF4\x90\x80\x80\"",
        NULL
    };

    for (int i = 0; invalid_input[i] != NULL; i++) {
        json_error_t error;
        json_t *result = json_loads(invalid_input[i], 0, &error);
        
        
        CU_ASSERT_PTR_NULL(result);
        CU_ASSERT(error.line > 0);
        CU_ASSERT(error.text[0] != '\0');
    }
}

// ===== TEST 2: JSON serializer + UTF enkoder =====
void test_json_dumps_with_unicode(void) {
    // Testira kako json_dumps koristi utf8_encode
    
    const char *test_strings[] = {
        "Hello, World!",
        "Привет, мир!",
        "你好，世界",
        "\"😘💜🧡\"",
        "Mešano: Hello, Привет, 你好, 💜",
        NULL
    };
    
    for (int i = 0; test_strings[i] != NULL; i++) {
        json_t *str = json_string(test_strings[i]);
        CU_ASSERT_PTR_NOT_NULL_FATAL(str);

        char *dump = json_dumps(str, JSON_ENCODE_ANY);
        CU_ASSERT_PTR_NOT_NULL_FATAL(dump);
        
  
        json_error_t error;
        json_t *str2 = json_loads(dump, 0, &error);
        CU_ASSERT_PTR_NOT_NULL_FATAL(str2);
        
        // Proveri da li je isti
        CU_ASSERT_STRING_EQUAL(json_string_value(str2), test_strings[i]);
        
        free(dump);
        json_decref(str);
        json_decref(str2);
        
        printf("Roundtrip test %d: %s\n", i, test_strings[i]);
    }
}

void test_json_object_with_unicode_keys(void) {
    
    json_t *obj = json_object();
    CU_ASSERT_PTR_NOT_NULL_FATAL(obj);
    
    struct {
        const char *key;
        const char *value;
    } test_data[] = {
        {"ascii", "value1"},
        {"ћирилица", "value2"},
        {"汉字", "value3"},
        {"😀", "value4"},
        {NULL, NULL}
    };
    

    for (int i = 0; test_data[i].key != NULL; i++) {
        int ret = json_object_set_new(obj, test_data[i].key, 
                                      json_string(test_data[i].value));
        CU_ASSERT_EQUAL(ret, 0);
    }

    for (int i = 0; test_data[i].key != NULL; i++) {
        json_t *val = json_object_get(obj, test_data[i].key);
        CU_ASSERT_PTR_NOT_NULL_FATAL(val);
        CU_ASSERT_STRING_EQUAL(json_string_value(val), test_data[i].value);
    }

    char *dump = json_dumps(obj, JSON_ENCODE_ANY);
    CU_ASSERT_PTR_NOT_NULL_FATAL(dump);
    
    json_error_t error;
    json_t *obj2 = json_loads(dump, 0, &error);
    CU_ASSERT_PTR_NOT_NULL_FATAL(obj2);

    for (int i = 0; test_data[i].key != NULL; i++) {
        json_t *val = json_object_get(obj2, test_data[i].key);
        CU_ASSERT_PTR_NOT_NULL_FATAL(val);
        CU_ASSERT_STRING_EQUAL(json_string_value(val), test_data[i].value);
    }
    
    free(dump);
    json_decref(obj);
    json_decref(obj2);
    
    printf("Object with Unicode keys: PASS\n");
}


void test_json_array_with_unicode_strings(void) {

    
    json_t *arr = json_array();
    CU_ASSERT_PTR_NOT_NULL_FATAL(arr);
    
    const char *strings[] = {
        "ascii",
        "ћирилица",
        "汉字",
        "😀",
        NULL
    };
    

    for (int i = 0; strings[i] != NULL; i++) {
        int ret = json_array_append_new(arr, json_string(strings[i]));
        CU_ASSERT_EQUAL(ret, 0);
    }
    

    for (int i = 0; strings[i] != NULL; i++) {
        json_t *val = json_array_get(arr, i);
        CU_ASSERT_PTR_NOT_NULL_FATAL(val);
        CU_ASSERT_STRING_EQUAL(json_string_value(val), strings[i]);
    }
    

    char *dump = json_dumps(arr, JSON_ENCODE_ANY);
    CU_ASSERT_PTR_NOT_NULL_FATAL(dump);
    
    json_error_t error;
    json_t *arr2 = json_loads(dump, 0, &error);
    CU_ASSERT_PTR_NOT_NULL_FATAL(arr2);
    

    CU_ASSERT_EQUAL(json_array_size(arr2), 4);
    for (int i = 0; i < 4; i++) {
        json_t *val = json_array_get(arr2, i);
        CU_ASSERT_PTR_NOT_NULL_FATAL(val);
        CU_ASSERT_STRING_EQUAL(json_string_value(val), strings[i]);
    }
    
    free(dump);
    json_decref(arr);
    json_decref(arr2);
    
    printf("Array with Unicode strings: PASS\n");
}


void test_nested_unicode_structures(void) {

    
    json_t *root = json_object();
    CU_ASSERT_PTR_NOT_NULL_FATAL(root);

    json_t *arr = json_array();
    json_array_append_new(arr, json_string("први"));
    json_array_append_new(arr, json_string("第二"));
    json_array_append_new(arr, json_string("🚀"));
    
    json_object_set_new(root, "мешани_низ", arr);
    json_object_set_new(root, "ascii_key", json_string("obična vrednost"));
    json_object_set_new(root, "😀", json_string("emoji vrednost"));
    

    json_t *inner = json_object();
    json_object_set_new(inner, "унутрашњи", json_string("vrednost"));
    json_object_set_new(inner, "inner_ascii", json_string("value"));
    json_object_set_new(root, "objekat", inner);
    

    char *dump = json_dumps(root, JSON_ENCODE_ANY);
    CU_ASSERT_PTR_NOT_NULL_FATAL(dump);
    

    json_error_t error;
    json_t *root2 = json_loads(dump, 0, &error);
    CU_ASSERT_PTR_NOT_NULL_FATAL(root2);

    json_t *arr2 = json_object_get(root2, "мешани_низ");
    CU_ASSERT_PTR_NOT_NULL(arr2);
    CU_ASSERT_EQUAL(json_array_size(arr2), 3);
    
    CU_ASSERT_STRING_EQUAL(json_string_value(json_array_get(arr2, 0)), "први");
    CU_ASSERT_STRING_EQUAL(json_string_value(json_array_get(arr2, 1)), "第二");
    CU_ASSERT_STRING_EQUAL(json_string_value(json_array_get(arr2, 2)), "🚀");
    
    json_t *inner2 = json_object_get(root2, "objekat");
    CU_ASSERT_PTR_NOT_NULL(inner2);
    CU_ASSERT_STRING_EQUAL(json_string_value(json_object_get(inner2, "унутрашњи")), "vrednost");
    
    free(dump);
    json_decref(root);
    json_decref(root2);
    
    printf("Nested Unicode structures: PASS\n");
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("utf_integration_suite", 0, 0);
    
    CU_add_test(suite, "test_json_loads_with_unicode_valide", test_json_loads_with_unicode_valide);
    CU_add_test(suite, "test_json_loads_with_unicode_invalide", test_json_loads_with_unicode_invalide);
    CU_add_test(suite, "test_json_dumps_with_unicode", test_json_dumps_with_unicode);
    CU_add_test(suite, "test_json_object_with_unicode_keys", test_json_object_with_unicode_keys);
    CU_add_test(suite, "test_json_array_with_unicode_strings", test_json_array_with_unicode_strings);
    CU_add_test(suite, "test_nested_unicode_structures", test_nested_unicode_structures);
    
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}