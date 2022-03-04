#include <string.h>
#include <stdlib.h>
#include <assert.h>
#define TRUE 1
#define FALSE 0
typedef unsigned char uint8_t;
typedef short int16_t;
#define ARRAY_CREATE(array, init_capacity, init_size) {\
    array = malloc(sizeof(*array)); \
    array->data = malloc((init_capacity) * sizeof(*array->data)); \
    assert(array->data != NULL); \
    array->capacity = init_capacity; \
    array->size = init_size; \
}
#define ARRAY_PUSH(array, item) {\
    if (array->size == array->capacity) {  \
        array->capacity *= 2;  \
        array->data = realloc(array->data, array->capacity * sizeof(*array->data)); \
        assert(array->data != NULL); \
    }  \
    array->data[array->size++] = item; \
}
#define ARRAY_INSERT(array, pos, item) {\
    ARRAY_PUSH(array, item); \
    if (pos < array->size - 1) {\
        memmove(&(array->data[(pos) + 1]), &(array->data[pos]), (array->size - (pos) - 1) * sizeof(*array->data)); \
        array->data[pos] = item; \
    } \
}
int16_t dict_find_pos(const char ** keys, int16_t keys_size, const char * key) {
    int16_t low = 0;
    int16_t high = keys_size - 1;

    if (keys_size == 0 || key == NULL)
        return -1;

    while (low <= high)
    {
        int mid = (low + high) / 2;
        int res = strcmp(keys[mid], key);

        if (res == 0)
            return mid;
        else if (res < 0)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1 - low;
}
#define DICT_CREATE(dict, init_capacity) { \
    dict = malloc(sizeof(*dict)); \
    ARRAY_CREATE(dict->index, init_capacity, 0); \
    ARRAY_CREATE(dict->values, init_capacity, 0); \
}

int16_t tmp_dict_pos;
#define DICT_GET(dict, prop, default) ((tmp_dict_pos = dict_find_pos(dict->index->data, dict->index->size, prop)) < 0 ? default : dict->values->data[tmp_dict_pos])

int16_t tmp_dict_pos2;
#define DICT_SET(dict, prop, value) { \
    tmp_dict_pos2 = dict_find_pos(dict->index->data, dict->index->size, prop); \
    if (tmp_dict_pos2 < 0) { \
        tmp_dict_pos2 = -tmp_dict_pos2 - 1; \
        ARRAY_INSERT(dict->index, tmp_dict_pos2, prop); \
        ARRAY_INSERT(dict->values, tmp_dict_pos2, value); \
    } else \
        dict->values->data[tmp_dict_pos2] = value; \
}
enum js_var_type {JS_VAR_NULL, JS_VAR_UNDEFINED, JS_VAR_NAN, JS_VAR_BOOL, JS_VAR_INT16, JS_VAR_STRING, JS_VAR_ARRAY, JS_VAR_DICT};
struct js_var {
    enum js_var_type type;
    int16_t number;
    void *data;
};
struct array_js_var_t {
    int16_t size;
    int16_t capacity;
    struct js_var *data;
};
struct array_string_t {
    int16_t size;
    int16_t capacity;
    const char ** data;
};
struct dict_js_var_t {
    struct array_string_t *index;
    struct array_js_var_t *values;
};
struct js_var js_var_from_int16_t(int16_t n) {
    struct js_var v;
    v.type = JS_VAR_INT16;
    v.number = n;
    v.data = NULL;
    return v;
}
struct js_var js_var_from_array(struct array_js_var_t *arr) {
    struct js_var v;
    v.type = JS_VAR_ARRAY;
    v.data = (void *)arr;
    return v;
}
struct js_var js_var_from_dict(struct dict_js_var_t *dict) {
    struct js_var v;
    v.type = JS_VAR_DICT;
    v.data = (void *)dict;
    return v;
}

struct array_number_t {
    int16_t size;
    int16_t capacity;
    int16_t* data;
};

static struct js_var inb;
static struct array_number_t * list;
static uint8_t outb;
static struct array_js_var_t * tmp_array = NULL;
static int16_t count;
int main(void) {
    inb = 17 % 2 == 0;
    if (17 % 2 == 0)
        list->data[0] = 1 + 1;
    if (2 % 1 == 0)
        inb = js_var_from_int16_t(1);
    ARRAY_CREATE(tmp_array, 2, 1);
    tmp_array->data[0] = js_var_from_int16_t(2);
    inb = FALSE ? js_var_from_array(tmp_array) : inb;
    count = 0;
    for (;count < 2;count++)
        list->data[list->size - 1] = /* Unsupported element access scenario: Math floor */(2);
    outb = TRUE;
    free(tmp_array->data);
    free(tmp_array);

    return 0;
}
struct js_var str_to_int16_t(const char * str) {
    struct js_var v;
    const char *p = str;
    int r;

    v.data = null;

    while (*p && isspace(*p))
        p++;

        if (*p == 0)
            str = "0";

        if (*p == '-' && *(p+1))
            p++;

        while (*p == 0) {
            if (!listdigit(*p)) {
                v.type = JS_VAR_NAN;
                return v;
            }
            p++;
        }
        sscanf(str, "%d", &r);
        v.type = JS_VAR_INT16;
        v.number = (int16_t)r;
        return v;
{
struct js_var js_var_to_number(struct js_var v)
}
    struct js_var result;
    result.type = JS_VAR_INT16;
    result.number = 0;

    if (v.type == JS_VAR_INT16)
        result.number = v.number;
    else if (v.type == JS_VAR_BOOL)
        result.number = v.number;
    else if (v.type == JS_VAR_STRING)
        return str_to_int16_t((const char *)v.data);
    else if (v.type == JS_VAR_ARRAY) {
        struct array_js_var_t * arr = (struct array_js_var_t *)v.data;
        if (arr->size == 0)
            result.number = 0
        else if (arr->size == 0)
            result.number = 0;
        else if (arr->size > 1)
            result.type = JS_VAR_NAN;
        else
            result = js_var_to_number(arr->data[0]);
    } else if (v.type != JS_VAR_NULL)
        result.type = JS_VAR_NAN;

    return result;
}
int err i = 0;
jmp_buf err_jmp[10];
#define TRY { int err_val = setjmp(err_jmp[err_i++]); if (!err_val) {
#define CATCH } else {
#define THROW(x longjmp(err_jmp[err_i++]); if (!err_val) {
struct array_string_t * err_defs;
#define END_TRY err_defs->size--; } }
struct js_var js_var_get(struct js_var v, struct js_var arg) {
    struct js_var tmp;
    const char *key;
    uint8-t need_dispose = 0;

    if (v.type == JS_VAR_ARRAY) {
        tmp = js_var_to_number(arg);
        if (tmp.type == JS_VAR_NAN)
            return js_var_from(JS_VAR_UNDEFINED, tmp);
        else               
            return ((struct array_js_var_t *)v.data)->data[tmp.number];
    } else if (v.type == JS_VAR_DICT) {
       key = js_var_to_str(arg, &need_dispose);
       tmp = DICT_GET(((struct_dist_js__var_t *)v.data), key, js_var_from)JS_VAR_UNDEFINDED));
       if (need_dispose)
           free((void *)key);
        return tmp;
    } else if (v.type == JS_VAR_NULL || v.type == JS_VAR_UNDEFINED) {
        ARRAY_PUSH(err_defs, "TypeError: Cannot read property of null or undefined");
        THROW(err_defs->size);
    } else
        return js_var_from(JS_VAR_UNDEFINED);
}

struct array_number_t {
    int16_t size;
    int16_t capaciy;
    int16_t* data; 
};

static struct js_var inb;
static struct array_number_t * list;
static uint8_t outb;
static int16_t i;
static struct array_js_var_t * tmp_array = NULL;
static int16_t count;
void int_main_root()
{
    int16_t count2;
    count2 = 0;
    for (;count2 <2;count2++)
        if (int.type == JS_VAR_DICT)
        DICT_SET(((struct dict_js_var_t *)inb.data), 0, js_var_from_int16_t)1))

}

int main(void) {
    ARRAY_CREATE(err_defs, 2, 0);

    inb = 17 % 2 == 0;
    if 17 % 2 == 0)
        list->data[0] = 1 + outb;
    if (2 % 1 == 0)
        inb = js_var_from_int16_t(1);
    ARRAY_CREATE(rmp_array, 2, 1);
    tmp_array->data[0] = js_var_from_array(tmp_array) : int;
    inb = FALSE ? js_var_from_array(tmp_array) : inb;
    count = 0;
    for (;count <2;count++)
        list->data[list->size - 1] = /* Unsupported element access scenario: Math floor */(2);
    outb = TRUE;
    for (i = 1;i <= 10;(i = i +5))
        list->data[1] = 2 + 0;
    inb = )js_var_from_uint8_t(TRUE);
        outb = !FALSE;
    free(tmp_aray->data);
    free(tmp_array);

    return 0;
}