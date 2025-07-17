#ifndef __JULIE_H__
#define __JULIE_H__

#define _JULIE_STATUS                                                                                                                           \
    _JULIE_STATUS_X(JULIE_SUCCESS,                             "No error.")                                                                     \
    _JULIE_STATUS_X(JULIE_ERR_UNEXPECTED_EOS,                  "Unexpected end of input.")                                                      \
    _JULIE_STATUS_X(JULIE_ERR_UNEXPECTED_TOK,                  "Unexpected token.")                                                             \
    _JULIE_STATUS_X(JULIE_ERR_EXTRA_RPAREN,                    "Extraneous closing parenthesis.")                                               \
    _JULIE_STATUS_X(JULIE_ERR_MISSING_RPAREN,                  "End of line while parentheses left open.")                                      \
    _JULIE_STATUS_X(JULIE_ERR_LOOKUP,                          "Failed to find symbol.")                                                        \
    _JULIE_STATUS_X(JULIE_ERR_BAD_APPLY,                       "Value is not something that can be applied in this way.")                       \
    _JULIE_STATUS_X(JULIE_ERR_ARITY,                           "Incorrect number of arguments.")                                                \
    _JULIE_STATUS_X(JULIE_ERR_TYPE,                            "Incorrect argument type.")                                                      \
    _JULIE_STATUS_X(JULIE_ERR_NOT_PAIR,                        "List is not a pair.")                                                           \
    _JULIE_STATUS_X(JULIE_ERR_BAD_INDEX,                       "Field or element not found.")                                                   \
    _JULIE_STATUS_X(JULIE_ERR_EVAL_CANCELLED,                  "Evaluation was cancelled.")                                                     \
    _JULIE_STATUS_X(JULIE_ERR_FILE_NOT_FOUND,                  "File not found.")                                                               \
    _JULIE_STATUS_X(JULIE_ERR_FILE_IS_DIR,                     "File is a directory.")                                                          \
    _JULIE_STATUS_X(JULIE_ERR_MMAP_FAILED,                     "mmap() failed.")                                                                \
    _JULIE_STATUS_X(JULIE_ERR_RELEASE_WHILE_BORROWED,          "Value released while a borrowed reference remains outstanding.")                \
    _JULIE_STATUS_X(JULIE_ERR_REF_OF_TRANSIENT,                "References may only be taken to non-transient values.")                         \
    _JULIE_STATUS_X(JULIE_ERR_NOT_LVAL,                        "Result of expression is not assignable.")                                       \
    _JULIE_STATUS_X(JULIE_ERR_NOT_REF,                         "Value is not a reference.")                                                     \
    _JULIE_STATUS_X(JULIE_ERR_MODIFY_WHILE_ITER,               "Value modified while being iterated.")                                          \
    _JULIE_STATUS_X(JULIE_ERR_REF_OF_OBJECT_KEY,               "Taking references to object key values is not allowed.")                        \
    _JULIE_STATUS_X(JULIE_ERR_LOAD_PACKAGE_FAILURE,            "Failed to load package.")                                                       \
    _JULIE_STATUS_X(JULIE_ERR_USE_PACKAGE_FORBIDDEN,           "use-package has been disabled.")                                                \
    _JULIE_STATUS_X(JULIE_ERR_ADD_PACKAGE_DIRECTORY_FORBIDDEN, "add-package-directory has been disabled.")                                      \
    _JULIE_STATUS_X(JULIE_ERR_INFIX,                           "infix function must be the middle expression of three.")                        \
    _JULIE_STATUS_X(JULIE_ERR_MUST_FOLLOW_IF,                  "This special-form function must follow `if` or `elif`.")                        \
    _JULIE_STATUS_X(JULIE_ERR_REST_MUST_BE_LAST,               "'...' may only be specified at the end of a parameter list.")                   \
    _JULIE_STATUS_X(JULIE_ERR_REGEX,                           "Regex error.")                                                                  \
    _JULIE_STATUS_X(JULIE_ERR_NO_EVAL_CALLBACKS,               "Eval callbacks are not enabled. Define JULIE_ENABLE_EVAL_CALLBACKS to enable.")

#define _JULIE_STATUS_X(e, s) e,
typedef enum { _JULIE_STATUS } Julie_Status;
#undef _JULIE_STATUS_X

#define _JULIE_TYPE                                                                    \
    _JULIE_TYPE_X(JULIE_UNKNOWN,           "<unknown type>")                           \
    _JULIE_TYPE_X(JULIE_NIL,               "nil")                                      \
    _JULIE_TYPE_X(JULIE_SINT,              "signed integer")                           \
    _JULIE_TYPE_X(JULIE_UINT,              "unsigned integer")                         \
    _JULIE_TYPE_X(JULIE_FLOAT,             "float")                                    \
    _JULIE_TYPE_X(JULIE_STRING,            "string")                                   \
    _JULIE_TYPE_X(JULIE_SYMBOL,            "symbol")                                   \
    _JULIE_TYPE_X(JULIE_LIST,              "list")                                     \
    _JULIE_TYPE_X(JULIE_OBJECT,            "object")                                   \
    _JULIE_TYPE_X(JULIE_FN,                "function")                                 \
    _JULIE_TYPE_X(JULIE_BUILTIN_FN,        "function")                                 \
    _JULIE_TYPE_X(JULIE_LAMBDA,            "lambda")                                   \
    _JULIE_TYPE_X(_JULIE_INTEGER,          "integer")                                  \
    _JULIE_TYPE_X(_JULIE_NUMBER,           "number")                                   \
    _JULIE_TYPE_X(_JULIE_LIST_OR_OBJECT,   "list or object")                           \
    _JULIE_TYPE_X(_JULIE_KEYLIKE,          "keylike (string, symbol, number, or nil)")

#define _JULIE_TYPE_X(e, s) e,
typedef enum { _JULIE_TYPE } Julie_Type;
#undef _JULIE_TYPE_X

#define JULIE_TYPE_IS_KEYLIKE(_t)    \
    (  (_t) == JULIE_STRING          \
    || (_t) == JULIE_SYMBOL          \
    || (_t) == JULIE_SINT            \
    || (_t) == JULIE_UINT            \
    || (_t) == JULIE_FLOAT           \
    || (_t) == JULIE_NIL)

#define JULIE_TYPE_IS_INTEGER(_t)    \
    (  (_t) == JULIE_SINT            \
    || (_t) == JULIE_UINT)

#define JULIE_TYPE_IS_NUMBER(_t)     \
    (  (_t) == JULIE_SINT            \
    || (_t) == JULIE_UINT            \
    || (_t) == JULIE_FLOAT)

#define JULIE_TYPE_IS_APPLICABLE(_t) \
    (  (_t) == JULIE_FN              \
    || (_t) == JULIE_BUILTIN_FN      \
    || (_t) == JULIE_LAMBDA          \
    || (_t) == JULIE_LIST            \
    || (_t) == JULIE_OBJECT)

enum {
    JULIE_NO_QUOTE  = 1u << 0u,
    JULIE_MULTILINE = 1u << 1u,
};


typedef struct Julie_Interp_Struct        Julie_Interp;
typedef struct Julie_Array_Struct         Julie_Array;
typedef struct Julie_Value_Struct         Julie_Value;
typedef struct Julie_String_Struct        Julie_String;
typedef        Julie_String              *Julie_String_ID;
typedef struct Julie_Closure_Info_Struct  Julie_Closure_Info;

struct Julie_Backtrace_Entry_Struct {
    Julie_Value        *fn;
    Julie_String_ID     file_id;
    unsigned long long  line;
    unsigned long long  col;
};

typedef struct Julie_Source_Value_Info_Struct {
    Julie_String_ID    file_id;
    unsigned long long line;
    unsigned long long col;
    unsigned long long ind;
} Julie_Source_Value_Info;

typedef struct Julie_Backtrace_Entry_Struct Julie_Backtrace_Entry;

struct Julie_Apply_Context_Struct {
    Julie_Array           *args;
    Julie_Backtrace_Entry  bt_entry;
};
typedef struct Julie_Apply_Context_Struct Julie_Apply_Context;

struct Julie_Lookup_Error_Info_Struct {
    char *sym;
};

struct Julie_Release_While_Borrowed_Error_Info_Struct {
    char *sym;
};

struct Julie_Ref_Of_Transient_Error_Info_Struct {
    char *sym;
};

struct Julie_Ref_Of_Object_Key_Error_Info_Struct {
    char *sym;
};

struct Julie_Not_Lval_Error_Info_Struct {
    char *sym;
};

struct Julie_Modify_While_Iter_Error_Info_Struct {
    char *sym;
};

struct Julie_Arity_Error_Info_Struct {
    int                at_least;
    unsigned long long wanted_arity;
    unsigned long long got_arity;
};

struct Julie_Type_Error_Info_Struct {
    Julie_Type wanted_type;
    Julie_Type got_type;
};

struct Julie_Bad_Application_Error_Info_Struct {
    Julie_Type got_type;
};

struct Julie_Bad_Index_Error_Info_Struct {
    Julie_Value *bad_index;
};

struct Julie_File_Error_Info_Struct {
    char *path;
};

struct Julie_Load_Package_Failure_Error_Info_Struct {
    char *path;
    char *package_error_message;
};

struct Julie_Regex_Error_Info_Struct {
    char *regex_error_message;
};

typedef struct Julie_Lookup_Error_Info_Struct Julie_Lookup_Error_Info;
typedef struct Julie_Release_While_Borrowed_Error_Info_Struct Julie_Release_While_Borrowed_Error_Info;
typedef struct Julie_Ref_Of_Transient_Error_Info_Struct Julie_Ref_Of_Transient_Error_Info;
typedef struct Julie_Ref_Of_Object_Key_Error_Info_Struct Julie_Ref_Of_Object_Key_Error_Info;
typedef struct Julie_Not_Lval_Error_Info_Struct Julie_Not_Lval_Error_Info;
typedef struct Julie_Modify_While_Iter_Error_Info_Struct Julie_Modify_While_Iter_Error_Info;
typedef struct Julie_Arity_Error_Info_Struct Julie_Arity_Error_Info;
typedef struct Julie_Type_Error_Info_Struct Julie_Type_Error_Info;
typedef struct Julie_Bad_Application_Error_Info_Struct Julie_Bad_Application_Error_Info;
typedef struct Julie_Bad_Index_Error_Info_Struct Julie_Bad_Index_Error_Info;
typedef struct Julie_File_Error_Info_Struct Julie_File_Error_Info;
typedef struct Julie_Load_Package_Failure_Error_Info_Struct Julie_Load_Package_Failure_Error_Info;
typedef struct Julie_Regex_Error_Info_Struct Julie_Regex_Error_Info;

struct Julie_Error_Info_Struct {
    Julie_Interp       *interp;
    Julie_Status        status;
    Julie_String_ID     file_id;
    unsigned long long  line;
    unsigned long long  col;

    union {
        Julie_Lookup_Error_Info                 lookup;
        Julie_Release_While_Borrowed_Error_Info release_while_borrowed;
        Julie_Ref_Of_Transient_Error_Info       ref_of_transient;
        Julie_Ref_Of_Object_Key_Error_Info      ref_of_object_key;
        Julie_Not_Lval_Error_Info               not_lval;
        Julie_Modify_While_Iter_Error_Info      modify_while_iter;
        Julie_Arity_Error_Info                  arity;
        Julie_Type_Error_Info                   type;
        Julie_Bad_Application_Error_Info        bad_application;
        Julie_Bad_Index_Error_Info              bad_index;
        Julie_File_Error_Info                   file;
        Julie_Load_Package_Failure_Error_Info   load_package_failure;
        Julie_Regex_Error_Info                  regex;
    };
};

typedef struct Julie_Error_Info_Struct Julie_Error_Info;

typedef void (*Julie_Error_Callback)(Julie_Error_Info *info);
typedef void (*Julie_Output_Callback)(const char*, int);
typedef Julie_Status (*Julie_Eval_Callback)(Julie_Value *value);
typedef Julie_Status (*Julie_Post_Eval_Callback)(Julie_Status status, Julie_Value *value, Julie_Value **result);
typedef Julie_Status (*Julie_Fn)(Julie_Interp*, Julie_Value*, unsigned, Julie_Value**, Julie_Value**);

Julie_Interp *julie_init_interp(void);
Julie_Status julie_set_error_callback(Julie_Interp *interp, Julie_Error_Callback cb);
Julie_Status julie_set_output_callback(Julie_Interp *interp, Julie_Output_Callback cb);
Julie_Status julie_set_eval_callback(Julie_Interp *interp, Julie_Eval_Callback cb);
Julie_Status julie_set_post_eval_callback(Julie_Interp *interp, Julie_Post_Eval_Callback cb);
Julie_Status julie_set_argv(Julie_Interp *interp, int argc, char **argv);
Julie_Status julie_set_cur_file(Julie_Interp *interp, Julie_String_ID id);
Julie_Status julie_load_package(Julie_Interp *interp, const char *name, Julie_Value **result);
Julie_Status julie_add_package_directory(Julie_Interp *interp, const char *path);
Julie_Status julie_parse(Julie_Interp *interp, const char *str, int size);
Julie_Status julie_interp(Julie_Interp *interp);
void julie_free(Julie_Interp *interp);



void julie_free_error_info(Julie_Error_Info *info);
void julie_make_parse_error(Julie_Interp *interp, unsigned long long line, unsigned long long col, Julie_Status status);
void julie_make_interp_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status);
void julie_make_bad_apply_error(Julie_Interp *interp, Julie_Value *expr, Julie_Type got);
void julie_make_arity_error(Julie_Interp *interp, Julie_Value *expr, int wanted, int got, int at_least);
void julie_make_type_error(Julie_Interp *interp, Julie_Value *expr, Julie_Type wanted, Julie_Type got);
void julie_make_lookup_error(Julie_Interp *interp, Julie_Value *expr, const Julie_String_ID id);
void julie_make_bind_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, Julie_String_ID id);
void julie_make_bad_index_error(Julie_Interp *interp, Julie_Value *expr, Julie_Value *bad_index);
void julie_make_must_follow_if_error(Julie_Interp *interp, Julie_Value *expr);
void julie_make_file_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, const char *path);
void julie_make_load_package_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, const char *path, const char *message);
void julie_make_regex_error(Julie_Interp *interp, Julie_Value *expr, const char *message);
Julie_Backtrace_Entry *julie_bt_entry(Julie_Interp *interp, unsigned long long depth);
Julie_Source_Value_Info *julie_get_source_value_info(Julie_Value *value);
Julie_Source_Value_Info *julie_get_top_source_value_info(Julie_Interp *interp);

Julie_Value *julie_nil_value(Julie_Interp *interp);
Julie_Value *julie_sint_value(Julie_Interp *interp, long long sint);
Julie_Value *julie_uint_value(Julie_Interp *interp, unsigned long long uint);
Julie_Value *julie_float_value(Julie_Interp *interp, double floating);
Julie_Value *julie_symbol_value(Julie_Interp *interp, const Julie_String_ID id);
Julie_Value *julie_string_value_known_size(Julie_Interp *interp, const char *s, unsigned long long size);
Julie_Value *julie_string_value(Julie_Interp *interp, const char *s);
Julie_Value *julie_string_value_giveaway(Julie_Interp *interp, char *s);
Julie_Value *julie_interned_string_value(Julie_Interp *interp, const Julie_String_ID id);
Julie_Value *julie_list_value(Julie_Interp *interp);
Julie_Value *julie_object_value(Julie_Interp *interp);
Julie_Value *julie_fn_value(Julie_Interp *interp, unsigned long long n_values, Julie_Value **values);
Julie_Value *julie_lambda_value(Julie_Interp *interp, unsigned long long n_values, Julie_Value **values, Julie_Closure_Info *closure);
Julie_Value *julie_builtin_fn_value(Julie_Interp *interp, Julie_Fn fn);
Julie_Status julie_object_insert_field(Julie_Interp *interp, Julie_Value *object, Julie_Value *key, Julie_Value *val, Julie_Value **out_val);
Julie_Value *julie_object_get_field(Julie_Value *object, Julie_Value *key);
Julie_Status julie_object_delete_field(Julie_Interp *interp, Julie_Value *object, Julie_Value *key);

void julie_free_value(Julie_Interp *interp, Julie_Value *value);
void julie_force_free_value(Julie_Interp *interp, Julie_Value *value);
void julie_free_and_reuse_value(Julie_Interp *interp, Julie_Value *value);

Julie_Status julie_bind(Julie_Interp *interp, const Julie_String_ID name, Julie_Value **valuep);
Julie_Status julie_bind_local(Julie_Interp *interp, const Julie_String_ID name, Julie_Value **valuep);
Julie_Status julie_unbind(Julie_Interp *interp, const Julie_String_ID name);
Julie_Status julie_unbind_local(Julie_Interp *interp, const Julie_String_ID name);
Julie_Status julie_bind_fn(Julie_Interp *interp, Julie_String_ID id, Julie_Fn fn);
Julie_Status julie_bind_infix_fn(Julie_Interp *interp, Julie_String_ID id, Julie_Fn fn);
Julie_Value *julie_lookup(Julie_Interp *interp, const Julie_String_ID id);

Julie_String_ID julie_get_string_id(Julie_Interp *interp, const char *s);
const Julie_String *julie_get_string(Julie_Interp *interp, const Julie_String_ID id);
const char *julie_get_cstring(const Julie_String_ID id);
const char *julie_value_cstring(const Julie_Value *value);
Julie_String_ID julie_value_string_id(Julie_Interp *interp, const Julie_Value *value);

char *julie_to_string(Julie_Interp *interp, const Julie_Value *value, int flags);

Julie_Status julie_map_file_into_readonly_memory(const char *path, const char **addr, unsigned long long *size);

const char *julie_error_string(Julie_Status error);
const char *julie_type_string(Julie_Type type);

#ifdef JULIE_IMPL

#include <assert.h>

#ifndef JULIE_ASSERTIONS
#define JULIE_ASSERTIONS (1)
#endif

#if JULIE_ASSERTIONS
#define JULIE_ASSERT(...) assert(__VA_ARGS__)
#else
#define JULIE_ASSERT(...)
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h> /* strlen, memcpy, memset, memcmp */
#include <stdarg.h>
#include <alloca.h>
#include <math.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <regex.h>
#include <time.h>

#define ALIGN_UP(x, align)   ((__typeof(x))((((unsigned long long)(x)) + ((unsigned long long)align)) & ~(((unsigned long long)align) - 1ull)))
#define ALIGN_DOWN(x, align) ((__typeof(x))(((unsigned long long)(x)) & ~(((unsigned long long)align) - 1ull)))
#define IS_ALIGNED(x, align) (!(((unsigned long long)(x)) & (((unsigned long long)align) - 1ull)))
#define IS_POWER_OF_TWO(x)   ((x) != 0 && IS_ALIGNED((x), (x)))
#define NEXT_POT_2(x)        (           (x) | (           (x) >>  1ull))
#define NEXT_POT_4(x)        ( NEXT_POT_2(x) | ( NEXT_POT_2(x) >>  2ull))
#define NEXT_POT_8(x)        ( NEXT_POT_4(x) | ( NEXT_POT_4(x) >>  4ull))
#define NEXT_POT_16(x)       ( NEXT_POT_8(x) | ( NEXT_POT_8(x) >>  8ull))
#define NEXT_POT_32(x)       (NEXT_POT_16(x) | (NEXT_POT_16(x) >> 16ull))
#define NEXT_POT_64(x)       (NEXT_POT_32(x) | (NEXT_POT_32(x) >> 32ull))
#define NEXT_POT(x)          (NEXT_POT_64((x) - 1ull) + 1ull)
#define CLZ(_val)            (__builtin_clzll((_val) | 1ull))
#define BITFIELD_FULL        (0xFFFFFFFFFFFFFFFF)

#define XOR_SWAP_PTR(a, b) do {                                         \
    a = (void*)(((unsigned long long)(a)) ^ ((unsigned long long)(b))); \
    b = (void*)(((unsigned long long)(b)) ^ ((unsigned long long)(a))); \
    a = (void*)(((unsigned long long)(a)) ^ ((unsigned long long)(b))); \
} while (0);

#define likely(x)   (__builtin_expect(!!(x), 1))
#define unlikely(x) (__builtin_expect(!!(x), 0))


/*********************************************************
 *                    Data Structures                    *
 *********************************************************/

#define hash_table_make(K_T, V_T, HASH) (CAT2(hash_table(K_T, V_T), _make)((HASH), NULL))
#define hash_table_make_e(K_T, V_T, HASH, EQU) (CAT2(hash_table(K_T, V_T), _make)((HASH), (EQU)))
#define hash_table_len(t) ((t)->len)
#define hash_table_free(t) ((t)->_free((t)))
#define hash_table_clear(t) ((t)->_clear((t)))
#define hash_table_get_key(t, k) ((t)->_get_key((t), (k)))
#define hash_table_get_val(t, k) ((t)->_get_val((t), (k)))
#define hash_table_get_val_with_hash(t, k, h) ((t)->_get_val_with_hash((t), (k), (h)))
#define hash_table_insert(t, k, v) ((t)->_insert((t), (k), (v)))
#define hash_table_insert_with_hash(t, k, v, h) ((t)->_insert_with_hash((t), (k), (v), (h)))
#define hash_table_delete(t, k) ((t)->_delete((t), (k)))
#define hash_table_delete_with_hash(t, k, h) ((t)->_delete_with_hash((t), (k), (h)))
#define hash_table_traverse(t, key, val_ptr)                         \
    for (/* vars */                                                  \
         uint64_t __i    = 0,                                        \
                  __size = (t)->prime_sizes[(t)->_size_idx];         \
         /* conditions */                                            \
         __i < __size;                                               \
         /* increment */                                             \
         __i += 1)                                                   \
        for (/* vars */                                              \
             __typeof__(*(t)->_data) *__slot_ptr = (t)->_data + __i, \
                                    __slot     = *__slot_ptr;        \
                                                                     \
             /* conditions */                                        \
             __slot != NULL                 &&                       \
             ((key)     = __slot->_key   , 1) &&                     \
             ((val_ptr) = &(__slot->_val), 1);                       \
                                                                     \
             /* increment */                                         \
             __slot_ptr = &(__slot->_next),                          \
             __slot = *__slot_ptr)                                   \
            /* LOOP BODY HERE */                                     \


#define STR(x) _STR(x)
#define _STR(x) #x

#define CAT2(x, y) _CAT2(x, y)
#define _CAT2(x, y) x##y

#define CAT3(x, y, z) _CAT3(x, y, z)
#define _CAT3(x, y, z) x##y##z

#define CAT4(a, b, c, d) _CAT4(a, b, c, d)
#define _CAT4(a, b, c, d) a##b##c##d

#define _hash_table_slot(K_T, V_T) CAT4(_hash_table_slot_, K_T, _, V_T)
#define hash_table_slot(K_T, V_T) CAT4(hash_table_slot_, K_T, _, V_T)
#define _hash_table(K_T, V_T) CAT4(_hash_table_, K_T, _, V_T)
#define hash_table(K_T, V_T) CAT4(hash_table_, K_T, _, V_T)
#define hash_table_pretty_name(K_T, V_T) ("hash_table(" CAT3(K_T, ", ", V_T) ")")

#define _HASH_TABLE_EQU(t_ptr, l, r) \
    ((t_ptr)->_equ ? (t_ptr)->_equ((l), (r)) : (memcmp(&(l), &(r), sizeof((l))) == 0))

#define DEFAULT_START_SIZE_IDX (3)

#define use_hash_table(K_T, V_T)                                                             \
    static uint64_t CAT2(hash_table(K_T, V_T), _prime_sizes)[] = {                           \
        5ULL,        11ULL,        23ULL,        47ULL,        97ULL,                        \
        199ULL,        409ULL,        823ULL,        1741ULL,        3469ULL,                \
        6949ULL,        14033ULL,        28411ULL,        57557ULL,                          \
        116731ULL,        236897ULL,        480881ULL,        976369ULL,                     \
        1982627ULL,        4026031ULL,        8175383ULL,        16601593ULL,                \
        33712729ULL,        68460391ULL,        139022417ULL,                                \
        282312799ULL,        573292817ULL,        1164186217ULL,                             \
        2364114217ULL,        4294967291ULL,        8589934583ULL,                           \
        17179869143ULL,        34359738337ULL,        68719476731ULL,                        \
        137438953447ULL,        274877906899ULL,        549755813881ULL,                     \
        1099511627689ULL,        2199023255531ULL,        4398046511093ULL,                  \
        8796093022151ULL,        17592186044399ULL,        35184372088777ULL,                \
        70368744177643ULL,        140737488355213ULL,                                        \
        281474976710597ULL,        562949953421231ULL,                                       \
        1125899906842597ULL,        2251799813685119ULL,                                     \
        4503599627370449ULL,        9007199254740881ULL,                                     \
        18014398509481951ULL,        36028797018963913ULL,                                   \
        72057594037927931ULL,        144115188075855859ULL,                                  \
        288230376151711717ULL,        576460752303423433ULL,                                 \
        1152921504606846883ULL,        2305843009213693951ULL,                               \
        4611686018427387847ULL,        9223372036854775783ULL,                               \
        18446744073709551557ULL                                                              \
    };                                                                                       \
                                                                                             \
    struct _hash_table(K_T, V_T);                                                            \
                                                                                             \
    typedef struct _hash_table_slot(K_T, V_T) {                                              \
        K_T _key;                                                                            \
        V_T _val;                                                                            \
        uint64_t _hash;                                                                      \
        struct _hash_table_slot(K_T, V_T) *_next;                                            \
    }                                                                                        \
    *hash_table_slot(K_T, V_T);                                                              \
                                                                                             \
    typedef void (*CAT2(hash_table(K_T, V_T), _free_t))                                      \
        (struct _hash_table(K_T, V_T) *);                                                    \
    typedef void (*CAT2(hash_table(K_T, V_T), _clear_t))                                     \
        (struct _hash_table(K_T, V_T) *);                                                    \
    typedef K_T* (*CAT2(hash_table(K_T, V_T), _get_key_t))                                   \
        (struct _hash_table(K_T, V_T) *, const K_T);                                         \
    typedef V_T* (*CAT2(hash_table(K_T, V_T), _get_val_t))                                   \
        (struct _hash_table(K_T, V_T) *, const K_T);                                         \
    typedef V_T* (*CAT2(hash_table(K_T, V_T), _get_val_with_hash_t))                         \
        (struct _hash_table(K_T, V_T) *, const K_T, const uint64_t);                         \
    typedef V_T* (*CAT2(hash_table(K_T, V_T), _insert_t))                                    \
        (struct _hash_table(K_T, V_T) *, const K_T, const V_T);                              \
    typedef V_T* (*CAT2(hash_table(K_T, V_T), _insert_with_hash_t))                          \
        (struct _hash_table(K_T, V_T) *, const K_T, const V_T, const uint64_t);              \
    typedef int (*CAT2(hash_table(K_T, V_T), _delete_t))                                     \
        (struct _hash_table(K_T, V_T) *, const K_T);                                         \
    typedef int (*CAT2(hash_table(K_T, V_T), _delete_with_hash_t))                           \
        (struct _hash_table(K_T, V_T) *, const K_T, const uint64_t);                         \
    typedef unsigned long long (*CAT2(hash_table(K_T, V_T), _hash_t))(const K_T);            \
    typedef int (*CAT2(hash_table(K_T, V_T), _equ_t))(const K_T, const K_T);                 \
                                                                                             \
    typedef struct _hash_table(K_T, V_T) {                                                   \
        hash_table_slot(K_T, V_T) *_data;                                                    \
        uint64_t len, _size_idx, _load_thresh;                                               \
        uint64_t *prime_sizes;                                                               \
                                                                                             \
        CAT2(hash_table(K_T, V_T), _free_t)              const _free;                        \
        CAT2(hash_table(K_T, V_T), _clear_t)             const _clear;                       \
        CAT2(hash_table(K_T, V_T), _get_key_t)           const _get_key;                     \
        CAT2(hash_table(K_T, V_T), _get_val_t)           const _get_val;                     \
        CAT2(hash_table(K_T, V_T), _get_val_with_hash_t) const _get_val_with_hash;           \
        CAT2(hash_table(K_T, V_T), _insert_t)            const _insert;                      \
        CAT2(hash_table(K_T, V_T), _insert_with_hash_t)  const _insert_with_hash;            \
        CAT2(hash_table(K_T, V_T), _delete_t)            const _delete;                      \
        CAT2(hash_table(K_T, V_T), _delete_with_hash_t)  const _delete_with_hash;            \
        CAT2(hash_table(K_T, V_T), _hash_t)              const _hash;                        \
        CAT2(hash_table(K_T, V_T), _equ_t)               const _equ;                         \
    }                                                                                        \
    *hash_table(K_T, V_T);                                                                   \
                                                                                             \
    /* hash_table slot */                                                                    \
    static inline hash_table_slot(K_T, V_T)                                                  \
        CAT2(hash_table_slot(K_T, V_T), _make)                                               \
        (const K_T key, const V_T val, const uint64_t hash) {                                \
                                                                                             \
        hash_table_slot(K_T, V_T) slot = malloc(sizeof(*slot));                              \
                                                                                             \
        slot->_key  = key;                                                                   \
        slot->_val  = val;                                                                   \
        slot->_hash = hash;                                                                  \
        slot->_next = NULL;                                                                  \
                                                                                             \
        return slot;                                                                         \
    }                                                                                        \
                                                                                             \
    /* hash_table */                                                                         \
    static inline void CAT2(hash_table(K_T, V_T), _rehash_insert)                            \
        (hash_table(K_T, V_T) t, hash_table_slot(K_T, V_T) insert_slot) {                    \
                                                                                             \
        uint64_t h, data_size, idx;                                                          \
        hash_table_slot(K_T, V_T) slot, *slot_ptr;                                           \
                                                                                             \
        h         = insert_slot->_hash;                                                      \
        data_size = t->prime_sizes[t->_size_idx];                                            \
        idx       = h % data_size;                                                           \
        slot_ptr  = t->_data + idx;                                                          \
                                                                                             \
        while ((slot = *slot_ptr))    { slot_ptr = &(slot->_next); }                         \
                                                                                             \
        *slot_ptr = insert_slot;                                                             \
    }                                                                                        \
                                                                                             \
    static inline void                                                                       \
        CAT2(hash_table(K_T, V_T), _update_load_thresh)(hash_table(K_T, V_T) t) {            \
                                                                                             \
        uint64_t cur_size;                                                                   \
                                                                                             \
        cur_size        = t->prime_sizes[t->_size_idx];                                      \
        t->_load_thresh = ((double)((cur_size << 1ULL))                                      \
                            / ((double)(cur_size * 3)))                                      \
                            * cur_size;                                                      \
    }                                                                                        \
                                                                                             \
    static inline void CAT2(hash_table(K_T, V_T), _rehash)(hash_table(K_T, V_T) t) {         \
        uint64_t                   old_size,                                                 \
                                   new_data_size;                                            \
        hash_table_slot(K_T, V_T) *old_data,                                                 \
                                   slot,                                                     \
                                  *slot_ptr,                                                 \
                                   next;                                                     \
                                                                                             \
        old_size      = t->prime_sizes[t->_size_idx];                                        \
        old_data      = t->_data;                                                            \
        t->_size_idx += 1;                                                                   \
        new_data_size = sizeof(hash_table_slot(K_T, V_T)) * t->prime_sizes[t->_size_idx];    \
        t->_data      = malloc(new_data_size);                                               \
        memset(t->_data, 0, new_data_size);                                                  \
                                                                                             \
        for (uint64_t i = 0; i < old_size; i += 1) {                                         \
            slot_ptr = old_data + i;                                                         \
            next = *slot_ptr;                                                                \
            while ((slot = next)) {                                                          \
                next        = slot->_next;                                                   \
                slot->_next = NULL;                                                          \
                CAT2(hash_table(K_T, V_T), _rehash_insert)(t, slot);                         \
            }                                                                                \
        }                                                                                    \
                                                                                             \
        free(old_data);                                                                      \
                                                                                             \
        CAT2(hash_table(K_T, V_T), _update_load_thresh)(t);                                  \
    }                                                                                        \
                                                                                             \
    static inline V_T*                                                                       \
        CAT2(hash_table(K_T, V_T), _insert_with_hash)                                        \
        (hash_table(K_T, V_T) t, const K_T key, const V_T val, const uint64_t h) {           \
                                                                                             \
        uint64_t data_size, idx;                                                             \
        hash_table_slot(K_T, V_T) slot, *slot_ptr;                                           \
                                                                                             \
        data_size = t->prime_sizes[t->_size_idx];                                            \
        idx       = h % data_size;                                                           \
        slot_ptr  = t->_data + idx;                                                          \
                                                                                             \
        while ((slot = *slot_ptr)) {                                                         \
            if (_HASH_TABLE_EQU(t, slot->_key, key)) {                                       \
                slot->_val = val;                                                            \
                return &(slot->_val);                                                        \
            }                                                                                \
            slot_ptr = &(slot->_next);                                                       \
        }                                                                                    \
                                                                                             \
        *slot_ptr = CAT2(hash_table_slot(K_T, V_T), _make)(key, val, h);                     \
        t->len   += 1;                                                                       \
                                                                                             \
        if (t->len == t->_load_thresh) {                                                     \
            CAT2(hash_table(K_T, V_T), _rehash)(t);                                          \
                                                                                             \
            data_size = t->prime_sizes[t->_size_idx];                                        \
            idx       = h % data_size;                                                       \
            slot_ptr  = t->_data + idx;                                                      \
                                                                                             \
            while ((slot = *slot_ptr)) {                                                     \
                if (_HASH_TABLE_EQU(t, slot->_key, key)) {                                   \
                    goto out;                                                                \
                }                                                                            \
                slot_ptr = &(slot->_next);                                                   \
            }                                                                                \
            return NULL;                                                                     \
        }                                                                                    \
                                                                                             \
out:;                                                                                        \
        return &((*slot_ptr)->_val);                                                         \
    }                                                                                        \
                                                                                             \
    static inline V_T*                                                                       \
        CAT2(hash_table(K_T, V_T), _insert)                                                  \
        (hash_table(K_T, V_T) t, const K_T key, const V_T val) {                             \
                                                                                             \
        return CAT2(hash_table(K_T, V_T), _insert_with_hash)(t, key, val, t->_hash(key));    \
    }                                                                                        \
                                                                                             \
    static inline int CAT2(hash_table(K_T, V_T), _delete_with_hash)                          \
        (hash_table(K_T, V_T) t, const K_T key, const uint64_t h) {                          \
                                                                                             \
        uint64_t data_size, idx;                                                             \
        hash_table_slot(K_T, V_T) slot, prev, *slot_ptr;                                     \
                                                                                             \
        data_size = t->prime_sizes[t->_size_idx];                                            \
        idx = h % data_size;                                                                 \
        slot_ptr = t->_data + idx;                                                           \
        prev = NULL;                                                                         \
                                                                                             \
        while ((slot = *slot_ptr)) {                                                         \
            if (_HASH_TABLE_EQU(t, slot->_key, key)) {                                       \
                break;                                                                       \
            }                                                                                \
            prev     = slot;                                                                 \
            slot_ptr = &(slot->_next);                                                       \
        }                                                                                    \
                                                                                             \
        if ((slot = *slot_ptr)) {                                                            \
            if (prev) {                                                                      \
                prev->_next = slot->_next;                                                   \
            } else {                                                                         \
                *slot_ptr = slot->_next;                                                     \
            }                                                                                \
            free(slot);                                                                      \
            t->len -= 1;                                                                     \
            return 1;                                                                        \
        }                                                                                    \
        return 0;                                                                            \
    }                                                                                        \
                                                                                             \
    static inline int CAT2(hash_table(K_T, V_T), _delete)                                    \
        (hash_table(K_T, V_T) t, const K_T key) {                                            \
        return CAT2(hash_table(K_T, V_T), _delete_with_hash)(t, key, t->_hash(key));         \
    }                                                                                        \
                                                                                             \
    static inline K_T*                                                                       \
        CAT2(hash_table(K_T, V_T), _get_key)(hash_table(K_T, V_T) t, const K_T key) {        \
                                                                                             \
        uint64_t h, data_size, idx;                                                          \
        hash_table_slot(K_T, V_T) slot, *slot_ptr;                                           \
                                                                                             \
        h         = t->_hash(key);                                                           \
        data_size = t->prime_sizes[t->_size_idx];                                            \
        idx       = h % data_size;                                                           \
        slot_ptr  = t->_data + idx;                                                          \
                                                                                             \
        while ((slot = *slot_ptr)) {                                                         \
            if (_HASH_TABLE_EQU(t, slot->_key, key)) {                                       \
                return &slot->_key;                                                          \
            }                                                                                \
            slot_ptr = &(slot->_next);                                                       \
        }                                                                                    \
                                                                                             \
        return NULL;                                                                         \
    }                                                                                        \
                                                                                             \
    static inline V_T*                                                                       \
        CAT2(hash_table(K_T, V_T), _get_val_with_hash)(hash_table(K_T, V_T) t,               \
                                                       const K_T key,                        \
                                                       const uint64_t h) {                   \
                                                                                             \
        uint64_t data_size, idx;                                                             \
        hash_table_slot(K_T, V_T) slot, *slot_ptr;                                           \
                                                                                             \
        data_size = t->prime_sizes[t->_size_idx];                                            \
        idx       = h % data_size;                                                           \
        slot_ptr  = t->_data + idx;                                                          \
                                                                                             \
        while ((slot = *slot_ptr)) {                                                         \
            if (_HASH_TABLE_EQU(t, slot->_key, key)) {                                       \
                return &slot->_val;                                                          \
            }                                                                                \
            slot_ptr = &(slot->_next);                                                       \
        }                                                                                    \
                                                                                             \
        return NULL;                                                                         \
    }                                                                                        \
                                                                                             \
    static inline V_T*                                                                       \
        CAT2(hash_table(K_T, V_T), _get_val)(hash_table(K_T, V_T) t, const K_T key) {        \
        return CAT2(hash_table(K_T, V_T), _get_val_with_hash)(t, key, t->_hash(key));        \
    }                                                                                        \
                                                                                             \
    static inline void CAT2(hash_table(K_T, V_T), _clear)(hash_table(K_T, V_T) t) {          \
        for (uint64_t i = 0; i < t->prime_sizes[t->_size_idx]; i += 1) {                     \
            hash_table_slot(K_T, V_T) next, slot = t->_data[i];                              \
            while (slot != NULL) {                                                           \
                next = slot->_next;                                                          \
                free(slot);                                                                  \
                slot = next;                                                                 \
            }                                                                                \
            t->_data[i] = NULL;                                                              \
        }                                                                                    \
        t->len = 0;                                                                          \
    }                                                                                        \
                                                                                             \
    static inline void CAT2(hash_table(K_T, V_T), _free)(hash_table(K_T, V_T) t) {           \
        CAT2(hash_table(K_T, V_T), _clear)(t);                                               \
        free(t->_data);                                                                      \
        free(t);                                                                             \
    }                                                                                        \
                                                                                             \
    static inline hash_table(K_T, V_T)                                                       \
    CAT2(hash_table(K_T, V_T), _make)(CAT2(hash_table(K_T, V_T), _hash_t) hash,              \
                                      CAT2(hash_table(K_T, V_T), _equ_t)equ) {               \
        hash_table(K_T, V_T) t = malloc(sizeof(*t));                                         \
                                                                                             \
        uint64_t data_size                                                                   \
            =   CAT2(hash_table(K_T, V_T), _prime_sizes)[DEFAULT_START_SIZE_IDX]             \
              * sizeof(hash_table_slot(K_T, V_T));                                           \
        hash_table_slot(K_T, V_T) *the_data = calloc(1, data_size);                          \
                                                                                             \
        struct _hash_table(K_T, V_T)                                                         \
            init                        = {._size_idx = DEFAULT_START_SIZE_IDX,              \
                    ._data              = the_data,                                          \
                    .len                = 0,                                                 \
                    .prime_sizes        = CAT2(hash_table(K_T, V_T), _prime_sizes),          \
                    ._free              = CAT2(hash_table(K_T, V_T), _free),                 \
                    ._clear             = CAT2(hash_table(K_T, V_T), _clear),                \
                    ._get_key           = CAT2(hash_table(K_T, V_T), _get_key),              \
                    ._get_val           = CAT2(hash_table(K_T, V_T), _get_val),              \
                    ._get_val_with_hash = CAT2(hash_table(K_T, V_T), _get_val_with_hash),    \
                    ._insert            = CAT2(hash_table(K_T, V_T), _insert),               \
                    ._insert_with_hash  = CAT2(hash_table(K_T, V_T), _insert_with_hash),     \
                    ._delete            = CAT2(hash_table(K_T, V_T), _delete),               \
                    ._delete_with_hash  = CAT2(hash_table(K_T, V_T), _delete_with_hash),     \
                    ._equ               = (CAT2(hash_table(K_T, V_T), _equ_t))equ,           \
                    ._hash              = (CAT2(hash_table(K_T, V_T), _hash_t))hash};        \
                                                                                             \
        memcpy(t, &init, sizeof(*t));                                                        \
                                                                                             \
        CAT2(hash_table(K_T, V_T), _update_load_thresh)(t);                                  \
                                                                                             \
        return t;                                                                            \
    }                                                                                        \


// small, fast 64 bit hash function (version 2).
//
// https://github.com/N-R-K/ChibiHash
//
// This is free and unencumbered software released into the public domain.
// For more information, please refer to <https://unlicense.org/>
#include <stdint.h>
#include <stddef.h>

static inline uint64_t chibihash64__load32le(const uint8_t *p) {
    return (uint64_t)p[0] <<  0 | (uint64_t)p[1] <<  8 |
           (uint64_t)p[2] << 16 | (uint64_t)p[3] << 24;
}

static inline uint64_t chibihash64__load64le(const uint8_t *p) {
    return chibihash64__load32le(p) | (chibihash64__load32le(p+4) << 32);
}

static inline uint64_t chibihash64__rotl(uint64_t x, int n) {
    return (x << n) | (x >> (-n & 63));
}

static inline uint64_t chibihash64(const void *keyIn, ptrdiff_t len, uint64_t seed) {
    const uint8_t *p = (const uint8_t *)keyIn;
    ptrdiff_t l = len;

    const uint64_t K = UINT64_C(0x2B7E151628AED2A7); // digits of e
    uint64_t seed2 = chibihash64__rotl(seed-K, 15) + chibihash64__rotl(seed-K, 47);
    uint64_t h[4] = { seed, seed+K, seed2, seed2+(K*K^K) };

    // depending on your system unrolling might (or might not) make things
    // a tad bit faster on large strings. on my system, it actually makes
    // things slower.
    // generally speaking, the cost of bigger code size is usually not
    // worth the trade-off since larger code-size will hinder inlinability
    // but depending on your needs, you may want to uncomment the pragma
    // below to unroll the loop.
    //#pragma GCC unroll 2
    for (; l >= 32; l -= 32) {
        for (int i = 0; i < 4; ++i, p += 8) {
            uint64_t stripe = chibihash64__load64le(p);
            h[i] = (stripe + h[i]) * K;
            h[(i+1)&3] += chibihash64__rotl(stripe, 27);
        }
    }

    for (; l >= 8; l -= 8, p += 8) {
        h[0] ^= chibihash64__load32le(p+0); h[0] *= K;
        h[1] ^= chibihash64__load32le(p+4); h[1] *= K;
    }

    if (l >= 4) {
        h[2] ^= chibihash64__load32le(p);
        h[3] ^= chibihash64__load32le(p + l - 4);
    } else if (l > 0) {
        h[2] ^= p[0];
        h[3] ^= p[l/2] | ((uint64_t)p[l-1] << 8);
    }

    h[0] += chibihash64__rotl(h[2] * K, 31) ^ (h[2] >> 31);
    h[1] += chibihash64__rotl(h[3] * K, 31) ^ (h[3] >> 31);
    h[0] *= K; h[0] ^= h[0] >> 31;
    h[1] += h[0];

    uint64_t x = (uint64_t)len * K;
    x ^= chibihash64__rotl(x, 29);
    x += seed;
    x ^= h[1];

    x ^= chibihash64__rotl(x, 15) ^ chibihash64__rotl(x, 42);
    x *= K;
    x ^= chibihash64__rotl(x, 13) ^ chibihash64__rotl(x, 31);

    return x;
}

static unsigned long long julie_charptr_hash(char *s) {
    return chibihash64(s, strlen(s), 0xDEADBEEF);
}

static int julie_charptr_equ(char *a, char *b) { return strcmp(a, b) == 0; }


/* qsort() + a context argument is a total portability mess. Thanks to this guy,
   who wrote a nice wrapper and fallback so that I didn't have to. */

/* Isaac Turner 29 April 2014 Public Domain */

/*

sort_r function to be exported.

Parameters:
  base is the array to be sorted
  nel is the number of elements in the array
  width is the size in bytes of each element of the array
  compar is the comparison function
  arg is a pointer to be passed to the comparison function

void sort_r(void *base, size_t nel, size_t width,
            int (*compar)(const void *_a, const void *_b, void *_arg),
            void *arg);

*/

#define _SORT_R_INLINE inline

#if (defined __APPLE__ || defined __MACH__ || defined __DARWIN__ || \
     (defined __FreeBSD__ && !defined(qsort_r)) || defined __DragonFly__)
#  define _SORT_R_BSD
#elif (defined __GLIBC__ || (defined (__FreeBSD__) && defined(qsort_r)))
#  define _SORT_R_LINUX
#elif (defined _WIN32 || defined _WIN64 || defined __WINDOWS__ || \
       defined __MINGW32__ || defined __MINGW64__)
#  define _SORT_R_WINDOWS
#  undef _SORT_R_INLINE
#  define _SORT_R_INLINE __inline
#else
  /* Using our own recursive quicksort sort_r_simple() */
#endif

#if (defined NESTED_QSORT && NESTED_QSORT == 0)
#  undef NESTED_QSORT
#endif

#define SORT_R_SWAP(a,b,tmp) ((tmp) = (a), (a) = (b), (b) = (tmp))

/* swap a and b */
/* a and b must not be equal! */
static _SORT_R_INLINE void sort_r_swap(char *__restrict a, char *__restrict b,
                                       size_t w)
{
  char tmp, *end = a+w;
  for(; a < end; a++, b++) { SORT_R_SWAP(*a, *b, tmp); }
}

/* swap a, b iff a>b */
/* a and b must not be equal! */
/* __restrict is same as restrict but better support on old machines */
static _SORT_R_INLINE int sort_r_cmpswap(char *__restrict a,
                                         char *__restrict b, size_t w,
                                         int (*compar)(const void *_a,
                                                       const void *_b,
                                                       void *_arg),
                                         void *arg)
{
  if(compar(a, b, arg) > 0) {
    sort_r_swap(a, b, w);
    return 1;
  }
  return 0;
}

/*
Swap consecutive blocks of bytes of size na and nb starting at memory addr ptr,
with the smallest swap so that the blocks are in the opposite order. Blocks may
be internally re-ordered e.g.

  12345ab  ->   ab34512
  123abc   ->   abc123
  12abcde  ->   deabc12
*/
static _SORT_R_INLINE void sort_r_swap_blocks(char *ptr, size_t na, size_t nb)
{
  if(na > 0 && nb > 0) {
    if(na > nb) { sort_r_swap(ptr, ptr+na, nb); }
    else { sort_r_swap(ptr, ptr+nb, na); }
  }
}

/* Implement recursive quicksort ourselves */
/* Note: quicksort is not stable, equivalent values may be swapped */
static _SORT_R_INLINE void sort_r_simple(void *base, size_t nel, size_t w,
                                         int (*compar)(const void *_a,
                                                       const void *_b,
                                                       void *_arg),
                                         void *arg)
{
  char *b = (char *)base, *end = b + nel*w;

  /* for(size_t i=0; i<nel; i++) {printf("%4i", *(int*)(b + i*sizeof(int)));}
  printf("\n"); */

  if(nel < 10) {
    /* Insertion sort for arbitrarily small inputs */
    char *pi, *pj;
    for(pi = b+w; pi < end; pi += w) {
      for(pj = pi; pj > b && sort_r_cmpswap(pj-w,pj,w,compar,arg); pj -= w) {}
    }
  }
  else
  {
    /* nel > 6; Quicksort */

    int cmp;
    char *pl, *ple, *pr, *pre, *pivot;
    char *last = b+w*(nel-1), *tmp;

    /*
    Use median of second, middle and second-last items as pivot.
    First and last may have been swapped with pivot and therefore be extreme
    */
    char *l[3];
    l[0] = b + w;
    l[1] = b+w*(nel/2);
    l[2] = last - w;

    /* printf("pivots: %i, %i, %i\n", *(int*)l[0], *(int*)l[1], *(int*)l[2]); */

    if(compar(l[0],l[1],arg) > 0) { SORT_R_SWAP(l[0], l[1], tmp); }
    if(compar(l[1],l[2],arg) > 0) {
      SORT_R_SWAP(l[1], l[2], tmp);
      if(compar(l[0],l[1],arg) > 0) { SORT_R_SWAP(l[0], l[1], tmp); }
    }

    /* swap mid value (l[1]), and last element to put pivot as last element */
    if(l[1] != last) { sort_r_swap(l[1], last, w); }

    /*
    pl is the next item on the left to be compared to the pivot
    pr is the last item on the right that was compared to the pivot
    ple is the left position to put the next item that equals the pivot
    ple is the last right position where we put an item that equals the pivot

                                           v- end (beyond the array)
      EEEEEELLLLLLLLuuuuuuuuGGGGGGGEEEEEEEE.
      ^- b  ^- ple  ^- pl   ^- pr  ^- pre ^- last (where the pivot is)

    Pivot comparison key:
      E = equal, L = less than, u = unknown, G = greater than, E = equal
    */
    pivot = last;
    ple = pl = b;
    pre = pr = last;

    /*
    Strategy:
    Loop into the list from the left and right at the same time to find:
    - an item on the left that is greater than the pivot
    - an item on the right that is less than the pivot
    Once found, they are swapped and the loop continues.
    Meanwhile items that are equal to the pivot are moved to the edges of the
    array.
    */
    while(pl < pr) {
      /* Move left hand items which are equal to the pivot to the far left.
         break when we find an item that is greater than the pivot */
      for(; pl < pr; pl += w) {
        cmp = compar(pl, pivot, arg);
        if(cmp > 0) { break; }
        else if(cmp == 0) {
          if(ple < pl) { sort_r_swap(ple, pl, w); }
          ple += w;
        }
      }
      /* break if last batch of left hand items were equal to pivot */
      if(pl >= pr) { break; }
      /* Move right hand items which are equal to the pivot to the far right.
         break when we find an item that is less than the pivot */
      for(; pl < pr; ) {
        pr -= w; /* Move right pointer onto an unprocessed item */
        cmp = compar(pr, pivot, arg);
        if(cmp == 0) {
          pre -= w;
          if(pr < pre) { sort_r_swap(pr, pre, w); }
        }
        else if(cmp < 0) {
          if(pl < pr) { sort_r_swap(pl, pr, w); }
          pl += w;
          break;
        }
      }
    }

    pl = pr; /* pr may have gone below pl */

    /*
    Now we need to go from: EEELLLGGGGEEEE
                        to: LLLEEEEEEEGGGG

    Pivot comparison key:
      E = equal, L = less than, u = unknown, G = greater than, E = equal
    */
    sort_r_swap_blocks(b, ple-b, pl-ple);
    sort_r_swap_blocks(pr, pre-pr, end-pre);

    /*for(size_t i=0; i<nel; i++) {printf("%4i", *(int*)(b + i*sizeof(int)));}
    printf("\n");*/

    sort_r_simple(b, (pl-ple)/w, w, compar, arg);
    sort_r_simple(end-(pre-pr), (pre-pr)/w, w, compar, arg);
  }
}


#if defined NESTED_QSORT

  static _SORT_R_INLINE void sort_r(void *base, size_t nel, size_t width,
                                    int (*compar)(const void *_a,
                                                  const void *_b,
                                                  void *aarg),
                                    void *arg)
  {
    int nested_cmp(const void *a, const void *b)
    {
      return compar(a, b, arg);
    }

    qsort(base, nel, width, nested_cmp);
  }

#else /* !NESTED_QSORT */

  /* Declare structs and functions */

  #if defined _SORT_R_BSD

    /* Ensure qsort_r is defined */
    extern void qsort_r(void *base, size_t nel, size_t width, void *thunk,
                        int (*compar)(void *_thunk,
                                      const void *_a, const void *_b));

  #endif

  #if defined _SORT_R_BSD || defined _SORT_R_WINDOWS

    /* BSD (qsort_r), Windows (qsort_s) require argument swap */

    struct sort_r_data
    {
      void *arg;
      int (*compar)(const void *_a, const void *_b, void *_arg);
    };

    static _SORT_R_INLINE int sort_r_arg_swap(void *s,
                                              const void *a, const void *b)
    {
      struct sort_r_data *ss = (struct sort_r_data*)s;
      return (ss->compar)(a, b, ss->arg);
    }

  #endif

  #if defined _SORT_R_LINUX

    typedef int(* __compar_d_fn_t)(const void *, const void *, void *);
    extern void (qsort_r)(void *base, size_t nel, size_t width,
                          __compar_d_fn_t __compar, void *arg)
      __attribute__((nonnull (1, 4)));

  #endif

  /* implementation */

  static _SORT_R_INLINE void sort_r(void *base, size_t nel, size_t width,
                                    int (*compar)(const void *_a,
                                                  const void *_b, void *_arg),
                                    void *arg)
  {
    #if defined _SORT_R_LINUX

      #if defined __GLIBC__ && ((__GLIBC__ < 2) || (__GLIBC__ == 2 && __GLIBC_MINOR__ < 8))

        /* no qsort_r in glibc before 2.8, need to use nested qsort */
        sort_r_simple(base, nel, width, compar, arg);

      #else

        qsort_r(base, nel, width, compar, arg);

      #endif

    #elif defined _SORT_R_BSD

      struct sort_r_data tmp;
      tmp.arg = arg;
      tmp.compar = compar;
      qsort_r(base, nel, width, &tmp, sort_r_arg_swap);

    #elif defined _SORT_R_WINDOWS

      struct sort_r_data tmp;
      tmp.arg = arg;
      tmp.compar = compar;
      qsort_s(base, nel, width, sort_r_arg_swap, &tmp);

    #else

      /* Fall back to our own quicksort implementation */
      sort_r_simple(base, nel, width, compar, arg);

    #endif
  }

#endif /* !NESTED_QSORT */

#undef _SORT_R_INLINE
#undef _SORT_R_WINDOWS
#undef _SORT_R_LINUX
#undef _SORT_R_BSD


struct Julie_Array_Struct {
    unsigned long long  len;
    unsigned long long  cap;
    void               *aux;
    void               *data[];
};

#define JULIE_ARRAY_INIT        ((Julie_Array*)NULL)
#define JULIE_ARRAY_INITIAL_CAP (16)

static void julie_array_free(Julie_Array *array) {
    if (array != NULL) { free(array); }
}

static unsigned long long julie_array_len(Julie_Array *array) {
    return array == NULL ? 0 : array->len;
}

static Julie_Array *julie_array_reserve(Julie_Array *array, unsigned long long cap) {
    if (cap == 0) { return array; }

    if (cap < JULIE_ARRAY_INITIAL_CAP) {
        cap = JULIE_ARRAY_INITIAL_CAP;
    }

    if (array == NULL) {
        array = malloc(sizeof(Julie_Array) + (cap * sizeof(void*)));
        array->len = 0;
        array->cap = cap;
        array->aux = NULL;
        return array;
    }

    if (array->cap >= cap) { return array; }

    array->cap = cap;
    array      = realloc(array, sizeof(Julie_Array) + (array->cap * sizeof(void*)));

    return array;
}

static Julie_Array *julie_array_set_aux(Julie_Array *array, void *aux) {
    if (array == NULL) {
        array = malloc(sizeof(Julie_Array) + (JULIE_ARRAY_INITIAL_CAP * sizeof(void*)));
        array->len = 0;
        array->cap = JULIE_ARRAY_INITIAL_CAP;
    }
    array->aux = aux;
    return array;
}

static void *julie_array_get_aux(Julie_Array *array) {
    return array == NULL ? NULL : array->aux;
}

static Julie_Array *julie_array_push(Julie_Array *array, void *item) {
    if (unlikely(array == NULL)) {
        array = malloc(sizeof(Julie_Array) + (JULIE_ARRAY_INITIAL_CAP * sizeof(void*)));
        array->len = 0;
        array->cap = JULIE_ARRAY_INITIAL_CAP;
        array->aux = NULL;
        goto push;
    }

    if (unlikely(array->len >= array->cap)) {
        array->cap += ((array->cap >> 1) > 0) ? (array->cap >> 1) : 1;
        array       = realloc(array, sizeof(Julie_Array) + (array->cap * sizeof(void*)));
    }

push:;
    array->data[array->len] = item;
    array->len += 1;

    return array;
}

static Julie_Array *julie_array_insert(Julie_Array *array, void *item, unsigned long long idx) {
    if (unlikely(array == NULL)) {
        array = malloc(sizeof(Julie_Array) + (JULIE_ARRAY_INITIAL_CAP * sizeof(void*)));
        array->len = 0;
        array->cap = JULIE_ARRAY_INITIAL_CAP;
        array->aux = NULL;
        goto push;
    }

    if (unlikely(array->len >= array->cap)) {
        array->cap += ((array->cap >> 1) > 0) ? (array->cap >> 1) : 1;
        array       = realloc(array, sizeof(Julie_Array) + (array->cap * sizeof(void*)));
    }

push:;
    JULIE_ASSERT(idx <= array->cap);

    memmove(array->data + idx + 1, array->data + idx, (array->len - idx) * sizeof(void*));

    array->data[idx] = item;
    array->len += 1;

    return array;
}

static void *julie_array_elem(Julie_Array *array, unsigned idx) {
    JULIE_ASSERT(array != NULL && idx < array->len);
    return array->data[idx];
}

static void *julie_array_top(Julie_Array *array) {
    if (array == NULL || array->len == 0) {
        return NULL;
    }

    return array->data[array->len - 1];
}

static void *julie_array_pop(Julie_Array *array) {
    void *r;

    r = NULL;

    if (array != NULL && array->len > 0) {
        r = julie_array_top(array);
        array->len -= 1;
    }

    return r;
}

static void julie_array_erase(Julie_Array *array, unsigned idx) {
    if (array == NULL || idx >= array->len) {
        return;
    }

    memmove(array->data + idx, array->data + idx + 1, (array->len - idx - 1) * sizeof(void*));

    array->len -= 1;
}

#define JULIE_ARRAY_RESERVE(_arrayp, _cap)       ((_arrayp) = julie_array_reserve((_arrayp), (_cap)))
#define JULIE_ARRAY_PUSH(_arrayp, _item)         ((_arrayp) = julie_array_push((_arrayp), (_item)))
#define JULIE_ARRAY_INSERT(_arrayp, _item, _idx) ((_arrayp) = julie_array_insert((_arrayp), (_item), (_idx)))
#define JULIE_ARRAY_SET_AUX(_arrayp, _aux)       ((_arrayp) = julie_array_set_aux((_arrayp), (_aux)))

#define ARRAY_FOR_EACH(_arrayp, _it)                                                                 \
    for (unsigned long long _each_i = 0;                                                             \
         ((_arrayp) != NULL && _each_i < (_arrayp)->len && (((_it) = (_arrayp)->data[_each_i]), 1)); \
         _each_i += 1)



/*********************************************************
 *                         Core                          *
 *********************************************************/



#define _JULIE_STATUS_X(e, s) s,
const char *_julie_error_strings[] = { _JULIE_STATUS };
#undef _JULIE_STATUS_X

const char *julie_error_string(Julie_Status error) {
    return _julie_error_strings[error];
}

#define _JULIE_TYPE_X(e, s) s,
const char *_julie_type_strings[] = { _JULIE_TYPE };
#undef _JULIE_TYPE_X

const char *julie_type_string(Julie_Type type) {
    return _julie_type_strings[type];
}

enum {
    JULIE_STRING_TYPE_EMBED = 0,
    JULIE_STRING_TYPE_INTERN,
    JULIE_STRING_TYPE_MALLOC,

    JULIE_INFIX_FN,
    JULIE_REARRANGED_INFIX_SOURCE_LIST,
};

#define JULIE_MAX_BC_POT (32ull)
#define JULIE_EMBEDDED_STRING_MAX_SIZE (sizeof(unsigned long long))

struct Julie_Value_Struct {
    union {
        struct {
            union {
                long long           sint;
                unsigned long long  uint;
                double              floating;
                Julie_String_ID     string_id;
                char               *cstring;
                void               *object;
                Julie_Array        *list;
                Julie_Fn            builtin_fn;
            };

            unsigned char tag;
            unsigned char source_node;
            unsigned char type;
            unsigned char owned;
            unsigned int  borrow_count;
        };
        struct {
            /* Last byte of embedded_string_bytes aliases with tag, which should be 0 when
               tag == JULIE_STRING_TYPE_EMBED, giving us an extra byte and natural NULL
               terminator. */
            char          embedded_string_bytes[JULIE_EMBEDDED_STRING_MAX_SIZE + 1];
            unsigned char _source_node;
            unsigned char _type;
            unsigned char _owned;
            unsigned int  _borrow_count;
        };
    };
};

#define JULIE_BORROW(_val)                                                 \
do {                                                                       \
    JULIE_ASSERT(!(_val)->source_node);                                    \
                                                                           \
    JULIE_ASSERT((_val)->borrow_count < (1ull << (JULIE_MAX_BC_POT - 1))); \
    (_val)->borrow_count += 1;                                             \
} while (0)

#define JULIE_BORROW_NO_CHECK(_val)                                        \
do {                                                                       \
    JULIE_ASSERT((_val)->borrow_count < (1ull << (JULIE_MAX_BC_POT - 1))); \
    (_val)->borrow_count += 1;                                             \
} while (0)

#define JULIE_UNBORROW(_val)                                               \
do {                                                                       \
    JULIE_ASSERT(!(_val)->source_node);                                    \
                                                                           \
    JULIE_ASSERT((_val)->borrow_count > 0);                                \
    (_val)->borrow_count -= 1;                                             \
} while (0)

#define JULIE_UNBORROW_NO_CHECK(_val)                                      \
do {                                                                       \
    JULIE_ASSERT((_val)->borrow_count > 0);                                \
    (_val)->borrow_count -= 1;                                             \
} while (0)

typedef Julie_Value *Julie_Value_Ptr;


#define JULIE_NEW() (malloc(sizeof(Julie_Value)))
#define JULIE_DEL(_value) (free((_value)))


Julie_Source_Value_Info *julie_get_source_value_info(Julie_Value *value) {
    unsigned long long p;

    if (unlikely(value->type != JULIE_LIST)) { return NULL; }

    p = (unsigned long long)julie_array_get_aux(value->list);

    if (unlikely(!(p & 1))) { return NULL; }

    return (void*)((p >> 1ull) << 1ull);
}

typedef struct Julie_Parse_Context_Struct {
    Julie_Interp       *interp;
    const char         *cursor;
    const char         *end;
    unsigned long long  line;
    unsigned long long  col;
    unsigned long long  ind;
    unsigned long long  plevel;
    Julie_Array        *parse_stack;
} Julie_Parse_Context;

typedef char *Char_Ptr;
use_hash_table(Char_Ptr, Julie_String_ID)

use_hash_table(Julie_String_ID, Julie_Value_Ptr)

use_hash_table(Julie_String_ID, regex_t)

/* A lambda's list->aux must point to a Julie_Closure_Info. */
struct Julie_Closure_Info_Struct {
    Julie_String_ID                              cur_file;
    hash_table(Julie_String_ID, Julie_Value_Ptr) captures;
};


#define JULIE_SYMTAB_SIZE (16)

struct Julie_Symbol_Table_Struct {
    Julie_String_ID                               syms[JULIE_SYMTAB_SIZE] __attribute__((aligned(64)));
    Julie_Value                                  *vals[JULIE_SYMTAB_SIZE] __attribute__((aligned(64)));
    hash_table(Julie_String_ID, Julie_Value_Ptr)  expansion;
    unsigned                                      cache_idx;
};

typedef struct Julie_Symbol_Table_Struct Julie_Symbol_Table;


#define JULIE_STRING_CACHE_SIZE (16)

#define JULIE_SINT_VALUE_CACHE_SIZE (256)

struct Julie_Interp_Struct {
    Julie_Error_Callback                   error_callback;
    Julie_Output_Callback                  output_callback;
#ifdef JULIE_ENABLE_EVAL_CALLBACKS
    Julie_Eval_Callback                    eval_callback;
    Julie_Post_Eval_Callback               post_eval_callback;
#endif

    Julie_Array                           *argv;

    Julie_String_ID                        cur_file_id;

    unsigned long long                     string_cache_sizes[JULIE_STRING_CACHE_SIZE];
    char                                  *string_cache_pointers[JULIE_STRING_CACHE_SIZE];

    hash_table(Char_Ptr, Julie_String_ID)  strings;
    Julie_String_ID                        ellipses_id;

    Julie_Symbol_Table                    *global_symtab;
    Julie_Array                           *local_symtab_stack;
    unsigned long long                     local_symtab_depth;

    Julie_Array                           *roots;
    Julie_Array                           *source_infos;
    Julie_Value                           *nil_value;
    Julie_Value                           *__class___value;
    Julie_Value                           *sint_values[JULIE_SINT_VALUE_CACHE_SIZE];

    Julie_Array                           *value_stack;
    unsigned long long                     apply_depth;
    Julie_Array                           *apply_contexts;
    Julie_Fn                               last_popped_builtin_fn;
    int                                    last_if_was_true;
    Julie_Array                           *iter_vals;

    int                                    use_package_forbidden;
    int                                    add_package_directory_forbidden;
    Julie_Array                           *package_dirs;
    Julie_Array                           *package_handles;
    Julie_Array                           *package_values;

    hash_table(Julie_String_ID, regex_t)   compiled_regex;
};


static Julie_Apply_Context *julie_push_cxt(Julie_Interp *interp, Julie_Value *value) {
    Julie_Apply_Context *cxt;

    interp->apply_depth += 1;

    JULIE_ARRAY_PUSH(interp->value_stack, value);

    if (unlikely(interp->apply_depth > julie_array_len(interp->apply_contexts))) {
        cxt = malloc(sizeof(*cxt));
        cxt->args = JULIE_ARRAY_INIT;
        JULIE_ARRAY_PUSH(interp->apply_contexts, cxt);
    } else {
        cxt = julie_array_elem(interp->apply_contexts, interp->apply_depth - 1);
    }

    return cxt;
}

static void julie_pop_cxt(Julie_Interp *interp) {
    Julie_Apply_Context *cxt;

    julie_array_pop(interp->value_stack);

    cxt = julie_array_elem(interp->apply_contexts, interp->apply_depth - 1);

    if (likely(cxt->args != NULL)) {
        cxt->args->len = 0;
    }

    interp->apply_depth -= 1;
}


Julie_Source_Value_Info *julie_get_top_source_value_info(Julie_Interp *interp) {
    unsigned long long       n;
    unsigned long long       i;
    Julie_Value             *expr;
    Julie_Source_Value_Info *info;

    n = julie_array_len(interp->value_stack);
    for (i = n; i > 0; i -= 1) {
        expr = julie_array_elem(interp->value_stack, i - 1);
        info = julie_get_source_value_info(expr);

        if (info != NULL) {
            return info;
        }
    }

    return NULL;
}


enum {
    _JULIE_STRING_NO_TAG,
    JULIE_STRING_AMPERSAND,
    JULIE_STRING_QUOTE,
};

struct Julie_String_Struct {
    char               *chars;
    unsigned long long  len;
    unsigned long long  hash;
    unsigned            tag;
};

#define JULIE_STRING_ID_HASH(_id) (((const Julie_String*)(_id))->hash)

static unsigned long long julie_string_id_hash(Julie_String_ID id) {
    return JULIE_STRING_ID_HASH(id);
}

Julie_String_ID julie_get_string_id(Julie_Interp *interp, const char *s) {
    Julie_String_ID    *lookup;
    Julie_String       *newstring;
    unsigned long long  len;

    lookup = hash_table_get_val(interp->strings, (char*)s);

    if (unlikely(lookup == NULL)) {
        newstring        = malloc(sizeof(*newstring));
        len              = strlen(s);
        newstring->len   = len;
        newstring->chars = strdup(s);
        newstring->hash  = julie_charptr_hash(newstring->chars);
        newstring->tag   = _JULIE_STRING_NO_TAG;

        if (newstring->len >= 2) {
            if (newstring->chars[0] == '&') {
                newstring->tag = JULIE_STRING_AMPERSAND;
            } else if (newstring->chars[0] == '\'') {
                newstring->tag = JULIE_STRING_QUOTE;
            }
        }

        lookup = hash_table_insert(interp->strings, newstring->chars, newstring);
        JULIE_ASSERT(lookup != NULL);
    }

    return *lookup;
}

static void julie_free_string(Julie_String *string) {
    free(string->chars);
    string->chars = NULL;
    string->len   = 0;
}

const Julie_String *julie_get_string(Julie_Interp *interp, const Julie_String_ID id) {
    (void)interp;
    return id;
}

const char *julie_get_cstring(const Julie_String_ID id) {
    return ((const Julie_String*)id)->chars;
}

const char *julie_value_cstring(const Julie_Value *value) {
    JULIE_ASSERT(value->type == JULIE_STRING || value->type == JULIE_SYMBOL);
    if (value->tag == JULIE_STRING_TYPE_EMBED) {
        return value->embedded_string_bytes;
    }
    if (value->tag == JULIE_STRING_TYPE_INTERN) {
        return julie_get_cstring(value->string_id);
    }
    if (value->tag == JULIE_STRING_TYPE_MALLOC) {
        return value->cstring;
    }

    JULIE_ASSERT(0);
    __builtin_unreachable();
}

Julie_String_ID julie_value_string_id(Julie_Interp *interp, const Julie_Value *value) {
    JULIE_ASSERT(value->type == JULIE_STRING || value->type == JULIE_SYMBOL);
    if (likely(value->tag == JULIE_STRING_TYPE_INTERN)) {
        return value->string_id;
    }
    if (value->tag == JULIE_STRING_TYPE_EMBED) {
        return julie_get_string_id(interp, value->embedded_string_bytes);
    }
    if (value->tag == JULIE_STRING_TYPE_MALLOC) {
        return julie_get_string_id(interp, value->cstring);
    }

    JULIE_ASSERT(0);
    __builtin_unreachable();
}


static int julie_equal(Julie_Value *a, Julie_Value *b) {
    unsigned long long  i;
    Julie_Value        *ia;
    Julie_Value        *ib;

    if (a->type != b->type) { return 0; }

    switch (a->type) {
        case JULIE_NIL:
            return 1;
        case JULIE_SINT:
            return a->sint == b->sint;
        case JULIE_UINT:
            return a->uint == b->uint;
        case JULIE_FLOAT:
            return a->floating == b->floating;
        case JULIE_STRING:
        case JULIE_SYMBOL:
            if (a->tag == JULIE_STRING_TYPE_INTERN && b->tag == JULIE_STRING_TYPE_INTERN) {
                return a->string_id == b->string_id;
            }
            return strcmp(julie_value_cstring(a), julie_value_cstring(b)) == 0;
        case JULIE_LIST:
            if (julie_array_len(a->list) != julie_array_len(b->list)) { return 0; }
            for (i = 0; i < julie_array_len(a->list); i += 1) {
                ia = julie_array_elem(a->list, i);
                ib = julie_array_elem(b->list, i);
                if (!julie_equal(ia, ib)) { return 0; }
            }
            return 1;
        default:
            /* @todo: all types should be covered here */
            JULIE_ASSERT(0);
            break;
    }

    return 0;
}


static unsigned long long julie_value_hash(Julie_Value *val) {
    JULIE_ASSERT(JULIE_TYPE_IS_KEYLIKE(val->type));

    /* @todo zeros, nan, inf w/ sign */
    switch (val->type) {
        case JULIE_NIL:    return 0;
        case JULIE_SINT:   return val->sint;
        case JULIE_UINT:   return val->uint;
        case JULIE_FLOAT:  return val->floating;
        case JULIE_STRING:
        case JULIE_SYMBOL:
            if (val->tag == JULIE_STRING_TYPE_INTERN) {
                return ((Julie_String*)val->string_id)->hash;
            }
            return julie_charptr_hash((char*)julie_value_cstring(val));
    }

    JULIE_ASSERT(0);

    return 0;
}


use_hash_table(Julie_Value_Ptr, Julie_Value_Ptr)
typedef hash_table(Julie_Value_Ptr, Julie_Value_Ptr) _Julie_Object;


static Julie_Value *_julie_copy_real(Julie_Interp *interp, Julie_Value *value, int force);

__attribute__((always_inline))
static inline Julie_Value *_julie_copy(Julie_Interp *interp, Julie_Value *value, int force) {
    if ((value->owned | (value->source_node)) && !force) { return value; }

    return _julie_copy_real(interp, value, force);
}

static Julie_Value *_julie_copy_real(Julie_Interp *interp, Julie_Value *value, int force) {
    Julie_Value         *copy;
    Julie_Value         *it;
    _Julie_Object        obj;
    Julie_Value         *key;
    Julie_Value        **val;
    Julie_Closure_Info  *closure;
    Julie_Closure_Info  *closure_cpy;
    Julie_String_ID      sym;

    copy = JULIE_NEW();

    *copy              = *value;
    copy->owned        = 0;
    copy->borrow_count = 0;
    copy->source_node  = 0;

    switch (value->type) {
        case JULIE_STRING:
        case JULIE_SYMBOL:
            if (value->tag == JULIE_STRING_TYPE_MALLOC) {
                copy->cstring = strdup(value->cstring);
            }
            break;

        case JULIE_LIST:
            copy->list = JULIE_ARRAY_INIT;
            JULIE_ARRAY_RESERVE(copy->list, julie_array_len(value->list));
            ARRAY_FOR_EACH(value->list, it) {
                JULIE_ARRAY_PUSH(copy->list, _julie_copy(interp, it, 1));
            }
            JULIE_ARRAY_SET_AUX(copy->list, julie_array_get_aux(value->list));
            break;

        case JULIE_OBJECT:
            obj = copy->object;
            copy->object = hash_table_make_e(Julie_Value_Ptr, Julie_Value_Ptr, julie_value_hash, julie_equal);
            hash_table_traverse(obj, key, val) {
                hash_table_insert((_Julie_Object)copy->object,
                                  key->source_node ? key : _julie_copy(interp, key, 1),
                                  _julie_copy(interp, *val, 1));
            }
            break;

        case JULIE_FN:
            copy->list = JULIE_ARRAY_INIT;
            JULIE_ARRAY_RESERVE(copy->list, julie_array_len(value->list));
            ARRAY_FOR_EACH(value->list, it) {
//                 JULIE_ARRAY_PUSH(copy->list, _julie_copy(interp, it, 1));
                JULIE_ARRAY_PUSH(copy->list, it);
            }
            break;

        case JULIE_LAMBDA:
            copy->list = JULIE_ARRAY_INIT;
            JULIE_ARRAY_RESERVE(copy->list, julie_array_len(value->list));
            ARRAY_FOR_EACH(value->list, it) {
//                 JULIE_ARRAY_PUSH(copy->list, _julie_copy(interp, it, 1));
                JULIE_ARRAY_PUSH(copy->list, it);
            }

            closure     = julie_array_get_aux(value->list);
            closure_cpy = malloc(sizeof(*closure_cpy));

            closure_cpy->cur_file = closure->cur_file;
            closure_cpy->captures = hash_table_make(Julie_String_ID, Julie_Value_Ptr, julie_string_id_hash);

            hash_table_traverse(closure->captures, sym, val) {
                hash_table_insert(closure_cpy->captures, sym, _julie_copy(interp, *val, 1));
            }
            JULIE_ARRAY_SET_AUX(copy->list, closure_cpy);
            break;
    }

    return copy;
}

static Julie_Value *julie_copy(Julie_Interp *interp, Julie_Value *value) {
    return _julie_copy(interp, value, 0);
}

static Julie_Value *julie_force_copy(Julie_Interp *interp, Julie_Value *value) {
    return _julie_copy(interp, value, 1);
}


static void _julie_free_value_real(Julie_Interp * interp, Julie_Value *value, int free_root, int force, int free_source_nodes);

__attribute__((always_inline))
static inline void _julie_free_value(Julie_Interp * interp, Julie_Value *value, int free_root, int force, int free_source_nodes) {

    JULIE_ASSERT(free_root || !value->owned);

    if (value->owned        && !force)             { return; }
    if (value->source_node  && !free_source_nodes) { return; }

    _julie_free_value_real(interp, value, free_root, force, free_source_nodes);
}

static void _julie_free_value_real(Julie_Interp * interp, Julie_Value *value, int free_root, int force, int free_source_nodes) {
    int                  i;
    Julie_Value         *it;
    Julie_Value         *key;
    Julie_Value        **val;
    Julie_Closure_Info  *closure;
    Julie_String_ID      sym;

    switch (value->type) {
        case JULIE_STRING:
        case JULIE_SYMBOL:
            if (value->tag == JULIE_STRING_TYPE_MALLOC) {
                for (i = 0; i < JULIE_STRING_CACHE_SIZE; i += 1) {
                    if (interp->string_cache_pointers[i] == NULL) {
                        interp->string_cache_pointers[i] = value->cstring;
                        interp->string_cache_sizes[i]    = strlen(value->cstring);
                        goto done_string;
                    }
                }
                free(value->cstring);
            }
done_string:;
            break;

        case JULIE_LIST:
            ARRAY_FOR_EACH(value->list, it) {
                _julie_free_value(interp, it, 1, force, free_source_nodes);
            }
            julie_array_free(value->list);
            break;

        case JULIE_OBJECT:
            hash_table_traverse((_Julie_Object)value->object, key, val) {
                _julie_free_value(interp, key, 1, force, free_source_nodes);
                _julie_free_value(interp, *val, 1, force, free_source_nodes);
            }
            hash_table_free((_Julie_Object)value->object);
            break;

        case JULIE_FN:
            ARRAY_FOR_EACH(value->list, it) {
                _julie_free_value(interp, it, 1, force, free_source_nodes);
            }
            julie_array_free(value->list);
            break;

        case JULIE_LAMBDA:
            closure = julie_array_get_aux(value->list);
            hash_table_traverse(closure->captures, sym, val) {
                (void)sym;
                _julie_free_value(interp, *val, 1, force, free_source_nodes);
            }
            hash_table_free(closure->captures);
            free(closure);

            ARRAY_FOR_EACH(value->list, it) {
                _julie_free_value(interp, it, 1, force, free_source_nodes);
            }
            julie_array_free(value->list);

            break;
    }

    if (free_root) {
        JULIE_DEL(value);
    }
}

void julie_free_value(Julie_Interp *interp, Julie_Value *value) {
    _julie_free_value(interp, value, 1, 0, 0);
}

void julie_force_free_value(Julie_Interp *interp, Julie_Value *value) {
    _julie_free_value(interp, value, 1, 1, 0);
}

void julie_free_and_reuse_value(Julie_Interp *interp, Julie_Value *value) {
    _julie_free_value(interp, value, 0, 1, 0);
}

void julie_free_source_node(Julie_Interp *interp, Julie_Value *value) {
    _julie_free_value(interp, value, 1, 1, 1);
}


static int julie_borrows_to_subvalues_outstanding(Julie_Value *top, Julie_Value *value) {
    Julie_Value  *it;
    Julie_Value  *key;
    Julie_Value **val;

    if (value != top && value->borrow_count > 0) {
        return 1;
    }

    switch (value->type) {
        case JULIE_LIST:
            ARRAY_FOR_EACH(value->list, it) {
                if (julie_borrows_to_subvalues_outstanding(top, it)) {
                    return 1;
                }
            }
            break;

        case JULIE_OBJECT:
            hash_table_traverse((_Julie_Object)value->object, key, val) {
                (void)key;
                if (julie_borrows_to_subvalues_outstanding(top, *val)) {
                    return 1;
                }
            }
            break;

        case JULIE_FN:
        case JULIE_LAMBDA:
            ARRAY_FOR_EACH(value->list, it) {
                if (julie_borrows_to_subvalues_outstanding(top, it)) {
                    return 1;
                }
            }
            break;
    }

    return 0;
}

static int julie_borrows_outstanding(Julie_Value *value) {
    if (value->borrow_count > 0) { return 1; }

    return julie_borrows_to_subvalues_outstanding(value, value);
}

static inline void julie_replace_value(Julie_Interp *interp, Julie_Value *dst, Julie_Value *src) {
    unsigned char      save_owned;
    unsigned long long save_bc;

    JULIE_ASSERT(!src->owned);
    JULIE_ASSERT(src->borrow_count == 0);

    /* Overwrite dst with val data, preserving original address. */
    save_owned = dst->owned;
    save_bc = dst->borrow_count;
    dst->borrow_count = 0;
    dst->owned = 0;
    julie_free_and_reuse_value(interp, dst);
    *dst = *src;
    dst->borrow_count = save_bc;
    dst->owned = save_owned;

    if (!src->source_node) {
        /* Free up copied outer src value. */
        memset(src, 0, sizeof(*src));
        src->type = JULIE_NIL;
        julie_free_value(interp, src);
    }
}


static Julie_Status _julie_object_insert_field(Julie_Interp *interp, Julie_Value *object, Julie_Value *key, Julie_Value *val, Julie_Value **out_val, int skip_lookup) {
    unsigned long long   hash;
    Julie_Value        **lookup;

    JULIE_ASSERT(!val->owned);

    hash = julie_value_hash(key);

    if (!skip_lookup && (lookup = hash_table_get_val_with_hash((_Julie_Object)object->object, key, hash)) != NULL) {
        if (*lookup != val) {
            if (object->owned && julie_borrows_to_subvalues_outstanding(*lookup, *lookup)) {
                return JULIE_ERR_RELEASE_WHILE_BORROWED;
            }

            julie_free_value(interp, key);

            julie_replace_value(interp, *lookup, val);
        }

        if (out_val != NULL) {
            *out_val = *lookup;
        }
    } else {
        hash_table_insert_with_hash((_Julie_Object)object->object, key, val, hash);

        if (out_val != NULL) {
            *out_val = val;
        }
    }

    return JULIE_SUCCESS;
}

Julie_Status julie_object_insert_field(Julie_Interp *interp, Julie_Value *object, Julie_Value *key, Julie_Value *val, Julie_Value **out_val) {
    return _julie_object_insert_field(interp, object, key, val, out_val, 0);
}

Julie_Status julie_object_insert_field_skip_lookup(Julie_Interp *interp, Julie_Value *object, Julie_Value *key, Julie_Value *val, Julie_Value **out_val) {
    return _julie_object_insert_field(interp, object, key, val, out_val, 1);
}

Julie_Value *julie_object_get_field(Julie_Value *object, Julie_Value *key) {
    Julie_Value **lookup;

    lookup = hash_table_get_val((_Julie_Object)object->object, key);
    return lookup == NULL ? NULL : *lookup;
}

Julie_Status julie_object_delete_field(Julie_Interp *interp, Julie_Value *object, Julie_Value *key) {
    Julie_Value **lookup;
    Julie_Value  *real_key;
    Julie_Value  *val;

    lookup = hash_table_get_key((_Julie_Object)object->object, key);

    if (lookup == NULL) {
        return JULIE_ERR_BAD_INDEX;
    }

    real_key = *lookup;

    JULIE_ASSERT(real_key != key);
    JULIE_ASSERT(!julie_borrows_to_subvalues_outstanding(object, real_key));

    val = *hash_table_get_val((_Julie_Object)object->object, real_key);

    if (julie_borrows_to_subvalues_outstanding(object, val)) {
        return JULIE_ERR_RELEASE_WHILE_BORROWED;
    }

    hash_table_delete((_Julie_Object)object->object, real_key);

    real_key->owned = 0;
    julie_free_value(interp, real_key);
    val->owned = 0;
    julie_free_value(interp, val);

    return JULIE_SUCCESS;
}

Julie_Value *julie_nil_value(Julie_Interp *interp) {
    return interp->nil_value;
}

static Julie_Value *julie_source_nil_value(Julie_Interp *interp) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_NIL;
    v->tag          = 0;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_sint_value(Julie_Interp *interp, long long sint) {
    Julie_Value *v;

    if (likely(sint >= 0 && sint < JULIE_SINT_VALUE_CACHE_SIZE)) {
        return interp->sint_values[sint];
    }

    v = JULIE_NEW();

    v->type         = JULIE_SINT;
    v->sint         = sint;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

static Julie_Value *julie_source_sint_value(Julie_Interp *interp, long long sint) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_SINT;
    v->sint         = sint;
    v->tag          = 0;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_uint_value(Julie_Interp *interp, unsigned long long uint) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_UINT;
    v->uint         = uint;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

static Julie_Value *julie_source_uint_value(Julie_Interp *interp, unsigned long long uint) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_UINT;
    v->uint         = uint;
    v->tag          = 0;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_float_value(Julie_Interp *interp, double floating) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_FLOAT;
    v->floating     = floating;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

static Julie_Value *julie_source_float_value(Julie_Interp *interp, double floating) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_FLOAT;
    v->floating     = floating;
    v->tag          = 0;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_symbol_value(Julie_Interp *interp, const Julie_String_ID id) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_SYMBOL;
    v->string_id    = id;
    v->tag          = JULIE_STRING_TYPE_INTERN;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

static Julie_Value *julie_source_symbol_value(Julie_Interp *interp, const Julie_String_ID id) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_SYMBOL;
    v->string_id    = id;
    v->tag          = JULIE_STRING_TYPE_INTERN;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_string_value_known_size(Julie_Interp *interp, const char *s, unsigned long long size) {
    Julie_Value *v;
    int          i;

    v = JULIE_NEW();

    v->type = JULIE_STRING;

    if (size <= JULIE_EMBEDDED_STRING_MAX_SIZE) {
        memcpy(v->embedded_string_bytes, s, size);
        v->embedded_string_bytes[size] = 0;
        v->tag = JULIE_STRING_TYPE_EMBED;
    } else {
        for (i = 0; i < JULIE_STRING_CACHE_SIZE; i += 1) {
            if (interp->string_cache_sizes[i] >= size && interp->string_cache_pointers[i] != NULL) {
                v->cstring = interp->string_cache_pointers[i];

                interp->string_cache_pointers[i] = NULL;
                interp->string_cache_sizes[i]    = 0;
                goto copy;
            }
        }
        v->cstring = malloc(size + 1);
copy:;
        memcpy(v->cstring, s, size);
        v->cstring[size] = 0;
        v->tag = JULIE_STRING_TYPE_MALLOC;
    }

    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_string_value(Julie_Interp *interp, const char *s) {
    return julie_string_value_known_size(interp, s, strlen(s));
}

Julie_Value *julie_string_value_giveaway(Julie_Interp *interp, char *s) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_STRING;
    v->cstring      = s;
    v->tag          = JULIE_STRING_TYPE_MALLOC;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_interned_string_value(Julie_Interp *interp, const Julie_String_ID id) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_STRING;
    v->string_id    = id;
    v->tag          = JULIE_STRING_TYPE_INTERN;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

static Julie_Value *julie_source_interned_string_value(Julie_Interp *interp, const Julie_String_ID id) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_STRING;
    v->string_id    = id;
    v->tag          = JULIE_STRING_TYPE_INTERN;
    v->source_node  = 1;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_list_value(Julie_Interp *interp) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_LIST;
    v->list         = JULIE_ARRAY_INIT;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_object_value(Julie_Interp *interp) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_OBJECT;
    v->object       = hash_table_make_e(Julie_Value_Ptr, Julie_Value_Ptr, julie_value_hash, julie_equal);
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}

Julie_Value *julie_fn_value(Julie_Interp *interp, unsigned long long n_values, Julie_Value **values) {
    Julie_Value        *v;
    unsigned long long  i;

    v = JULIE_NEW();

    v->type         = JULIE_FN;
    v->list         = JULIE_ARRAY_INIT;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    for (i = 0; i < n_values; i += 1) {
        JULIE_ARRAY_PUSH(v->list,
                         values[i]->source_node
                             ? values[i]
                             : julie_force_copy(interp, values[i]));
    }

    return v;
}

Julie_Value *julie_lambda_value(Julie_Interp *interp, unsigned long long n_values, Julie_Value **values, Julie_Closure_Info *closure) {
    Julie_Value        *v;
    unsigned long long  i;

    v = JULIE_NEW();

    v->type         = JULIE_LAMBDA;
    v->list         = JULIE_ARRAY_INIT;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    for (i = 0; i < n_values; i += 1) {
        JULIE_ARRAY_PUSH(v->list,
                         values[i]->source_node
                             ? values[i]
                             : julie_force_copy(interp, values[i]));
    }

    JULIE_ARRAY_SET_AUX(v->list, closure);

    return v;
}

Julie_Value *julie_builtin_fn_value(Julie_Interp *interp, Julie_Fn fn) {
    Julie_Value *v;

    v = JULIE_NEW();

    v->type         = JULIE_BUILTIN_FN;
    v->builtin_fn   = fn;
    v->tag          = 0;
    v->source_node  = 0;
    v->owned        = 0;
    v->borrow_count = 0;

    return v;
}



/*********************************************************
 *                       Printing                        *
 *********************************************************/


static int julie_symbol_starts_with_ampersand(Julie_Interp *interp, const Julie_String_ID id);
static Julie_String_ID julie_find_value_in_symtabs(Julie_Interp *interp, const Julie_Value *value);

static void _julie_string_print(Julie_Interp *interp, char **buff, int *len, int *cap, const Julie_Value *value, unsigned ind, int flags) {
    unsigned             i;
    char                 b[128];
    const Julie_String  *string;
    const char          *cstring;
    unsigned long long   string_len;
    Julie_Value         *child;
    Julie_Value         *key;
    Julie_Value        **val;
    Julie_String_ID      sym;
    const char          *label;
    Julie_String_ID      fsym;
    union {
        Julie_Fn         f;
        void            *v;
    }                    prfn;

#define PUSHC(_c)                               \
do {                                            \
    if (*len == *cap) {                         \
        *cap <<= 1;                             \
        *buff = realloc(*buff, *cap);           \
    }                                           \
    (*buff)[*len]  = (_c);                      \
    *len          += 1;                         \
} while (0)

#define PUSHSN(_s, _n)                          \
do {                                            \
    for (unsigned _i = 0; _i < (_n); _i += 1) { \
        PUSHC((_s)[_i]);                        \
    }                                           \
} while (0)

#define PUSHS(_s) PUSHSN((_s), strlen(_s))

    if (flags & JULIE_MULTILINE) {
        for (i = 0; i < ind; i += 1) { PUSHC(' '); }
    }

    switch (value->type) {
        case JULIE_NIL:
            PUSHS("nil");
            break;
        case JULIE_SINT:
            snprintf(b, sizeof(b), "%lld", value->sint);
            PUSHS(b);
            break;
        case JULIE_UINT:
            snprintf(b, sizeof(b), "0x%llx", value->uint);
//             snprintf(b, sizeof(b), "%llu", value->uint);
            PUSHS(b);
            break;
        case JULIE_FLOAT:
            snprintf(b, sizeof(b), "%f", value->floating);
            PUSHS(b);
            break;
        case JULIE_STRING:
            if (value->tag == JULIE_STRING_TYPE_INTERN) {
                string     = julie_get_string(interp, value->string_id);
                cstring    = julie_get_cstring(value->string_id);
                string_len = string->len;
            } else {
                string     = NULL;
                cstring    = julie_value_cstring(value);
                string_len = strlen(cstring);
            }
            if (flags & JULIE_NO_QUOTE) {
                PUSHSN(cstring, string_len);
            } else {
                PUSHC('"');
                PUSHSN(cstring, string_len);
                PUSHC('"');
            }
            break;
        case JULIE_SYMBOL:
            if (value->tag == JULIE_STRING_TYPE_INTERN) {
                string     = julie_get_string(interp, value->string_id);
                cstring    = julie_get_cstring(value->string_id);
                string_len = string->len;
            } else {
                string     = NULL;
                cstring    = julie_value_cstring(value);
                string_len = strlen(cstring);
            }
            PUSHSN(cstring, string_len);
            break;
        case JULIE_LIST:
            PUSHC('(');
            PUSHC((flags & JULIE_MULTILINE) ? '\n' : ' ');
            ARRAY_FOR_EACH(value->list, child) {
                _julie_string_print(interp, buff, len, cap, child, (flags & JULIE_MULTILINE) ? ind + 2 : 0, flags & ~JULIE_NO_QUOTE);
                PUSHC((flags & JULIE_MULTILINE) ? '\n' : ' ');
            }
            if (flags & JULIE_MULTILINE) {
                for (i = 0; i < ind; i += 1) { PUSHC(' '); }
            }
            PUSHC(')');
            break;
        case JULIE_OBJECT:
            PUSHC('{');
            PUSHC((flags & JULIE_MULTILINE) ? '\n' : ' ');
            hash_table_traverse((_Julie_Object)value->object, key, val) {
                _julie_string_print(interp, buff, len, cap, key, (flags & JULIE_MULTILINE) ? ind + 2 : 0, flags & ~JULIE_NO_QUOTE);
                PUSHC(':');
                _julie_string_print(interp, buff, len, cap, *val, (flags & JULIE_MULTILINE) ? ind + 2 : 0, flags & ~JULIE_NO_QUOTE);
                PUSHC((flags & JULIE_MULTILINE) ? '\n' : ' ');
            }
            if (flags & JULIE_MULTILINE) {
                for (i = 0; i < ind; i += 1) { PUSHC(' '); }
            }
            PUSHC('}');
            break;

        case JULIE_BUILTIN_FN:
            label = "function";
            fsym = NULL;
            if (interp->global_symtab->expansion == NULL) {
                for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
                    if (interp->global_symtab->syms[i] != NULL
                    &&  interp->global_symtab->vals[i]->type == JULIE_BUILTIN_FN
                    &&  interp->global_symtab->vals[i]->builtin_fn == value->builtin_fn) {

                        fsym = interp->global_symtab->syms[i];
                        break;
                    }
                }
            } else {
                hash_table_traverse(interp->global_symtab->expansion, sym, val) {
                    if ((*val)->type == JULIE_BUILTIN_FN
                    &&  (*val)->builtin_fn == value->builtin_fn) {

                        fsym = sym;
                        break;
                    }
                }
            }
            prfn.f = value->builtin_fn;
            if (fsym != NULL) {
                snprintf(b, sizeof(b), "<%s@%p %s>", label, prfn.v, fsym->chars);
            } else {
                snprintf(b, sizeof(b), "<%s@%p>", label, prfn.v);
            }
            PUSHS(b);
            break;
        case JULIE_FN:
        case JULIE_LAMBDA:
            label = value->type == JULIE_LAMBDA ? "lambda" : "fn";

            fsym = julie_find_value_in_symtabs(interp, value);

            if (fsym != NULL) {
                snprintf(b, sizeof(b), "<%s@%p> %s", label, (void*)value, fsym->chars);
                PUSHS(b);
            } else {
                PUSHS(label);
                PUSHC(' ');
                if (flags & JULIE_MULTILINE) {
                    _julie_string_print(interp, buff, len, cap, value->list->data[0], ind, flags & ~JULIE_NO_QUOTE);
                    for (i = 1; i < julie_array_len(value->list); i += 1) {
                        PUSHC('\n');
                        _julie_string_print(interp, buff, len, cap, value->list->data[i], ind + 2, flags & ~JULIE_NO_QUOTE);
                    }
                } else {
                    PUSHC('(');
                    _julie_string_print(interp, buff, len, cap, value->list->data[0], ind, flags & ~JULIE_NO_QUOTE);
                    for (i = 1; i < julie_array_len(value->list); i += 1) {
                        PUSHC(' ');
                        _julie_string_print(interp, buff, len, cap, value->list->data[i], 0, flags & ~JULIE_NO_QUOTE);
                    }
                    PUSHC(')');
                }
            }
            break;
        default:
            JULIE_ASSERT(0);
            break;

    }

    PUSHC(0);
    *len -= 1;
}

char *julie_to_string(Julie_Interp *interp, const Julie_Value *value, int flags) {
    char *buff;
    int   len;
    int   cap;

    buff = malloc(16);
    len  = 0;
    cap  = 16;

    _julie_string_print(interp, &buff, &len, &cap, value, 0, flags);

    return buff;
}

static void julie_output(Julie_Interp *interp, const char *s, int n_bytes) {
    if (interp->output_callback == NULL) {
        fwrite(s, 1, n_bytes, stdout);
    } else {
        interp->output_callback(s, n_bytes);
    }
}

static void julie_print(Julie_Interp *interp, Julie_Value *value, unsigned ind) {
    char *buff;
    int   len;
    int   cap;

    buff = malloc(16);
    len  = 0;
    cap  = 16;

    _julie_string_print(interp, &buff, &len, &cap, value, ind, JULIE_NO_QUOTE | JULIE_MULTILINE);
    julie_output(interp, buff, len);
    free(buff);
}

/*********************************************************
 *                         Symbols                       *
 *********************************************************/

static int julie_symbol_starts_with_ampersand(Julie_Interp *interp, const Julie_String_ID id) {
    return julie_get_string(interp, id)->tag == JULIE_STRING_AMPERSAND;
}

static int julie_symbol_starts_with_single_quote(Julie_Interp *interp, const Julie_String_ID id) {
    return julie_get_string(interp, id)->tag == JULIE_STRING_QUOTE;
}

static void julie_symtab_cache_add(Julie_Symbol_Table *symtab, const Julie_String_ID sym, Julie_Value *val) {
    symtab->syms[symtab->cache_idx] = sym;
    symtab->vals[symtab->cache_idx] = val;

    symtab->cache_idx += 1;
    if (symtab->cache_idx == JULIE_SYMTAB_SIZE) {
        symtab->cache_idx = 0;
    }
}

static inline Julie_Value *julie_symtab_search(const Julie_Symbol_Table * restrict symtab, const Julie_String_ID sym) {
    const Julie_String_ID *const  restrict syms = __builtin_assume_aligned(symtab->syms, 64);
    Julie_Value           *const *restrict vals = __builtin_assume_aligned(symtab->vals, 64);
    unsigned long long                     i;
    Julie_Value                          **lookup;

    for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
        if (syms[i] == sym) {
            return vals[i];
        }
    }

    if (likely(symtab->expansion != NULL)) {
        lookup = hash_table_get_val_with_hash(symtab->expansion, sym, JULIE_STRING_ID_HASH(sym));
        if (likely(lookup != NULL)) {
            julie_symtab_cache_add((Julie_Symbol_Table*)symtab, sym, *lookup);
            return *lookup;
        }
    }

    return NULL;
}

static void julie_symtab_insert(Julie_Symbol_Table *symtab, const Julie_String_ID sym, Julie_Value *val) {
    unsigned i;

    if (symtab->expansion == NULL) {
        for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
            if (symtab->syms[i] == NULL) {
                symtab->syms[i] = sym;
                symtab->vals[i] = val;
                return;
            }
        }

        symtab->expansion = hash_table_make(Julie_String_ID, Julie_Value_Ptr, julie_string_id_hash);

        for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
            JULIE_ASSERT(symtab->syms[i] != NULL);
            hash_table_insert_with_hash(symtab->expansion, symtab->syms[i], symtab->vals[i], JULIE_STRING_ID_HASH(symtab->syms[i]));
        }

        goto insert_into_expansion;

    } else {
insert_into_expansion:;
        hash_table_insert_with_hash(symtab->expansion, sym, val, JULIE_STRING_ID_HASH(sym));
        julie_symtab_cache_add(symtab, sym, val);
    }
}

static void julie_symtab_del(Julie_Symbol_Table *symtab, const Julie_String_ID sym) {
    unsigned i;

    for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
        if (symtab->syms[i] == sym) {
            symtab->syms[i] = NULL;
            symtab->vals[i] = NULL;
            break;
        }
    }

    if (symtab->expansion != NULL) {
        hash_table_delete_with_hash(symtab->expansion, sym, JULIE_STRING_ID_HASH(sym));
    }
}

static Julie_String_ID julie_find_value_in_symtabs(Julie_Interp *interp, const Julie_Value *value) {
    unsigned             i;
    Julie_Symbol_Table  *symtab;
    unsigned             j;
    Julie_String_ID      sym;
    Julie_Value         *val;
    Julie_Value        **valp;

    for (i = interp->local_symtab_depth; i > 0; i -= 1) {
        symtab = julie_array_elem(interp->local_symtab_stack, i - 1);

        if (symtab->expansion == NULL) {
            for (j = 0; j < JULIE_SYMTAB_SIZE; j += 1) {
                sym = symtab->syms[j];

                if (sym != NULL) {
                    val = symtab->vals[j];

                    if (val == value
                    &&  !julie_symbol_starts_with_ampersand(interp, sym)) {

                        return sym;
                    }
                }
            }
        } else {
            hash_table_traverse(symtab->expansion, sym, valp) {
                val = *valp;

                if (val == value
                && !julie_symbol_starts_with_ampersand(interp, sym)) {

                    return sym;
                }
            }
        }
    }

    symtab = interp->global_symtab;

    if (symtab->expansion == NULL) {
        for (j = 0; j < JULIE_SYMTAB_SIZE; j += 1) {
            sym = symtab->syms[j];

            if (sym != NULL) {
                val = symtab->vals[j];

                if (val == value
                &&  !julie_symbol_starts_with_ampersand(interp, sym)) {

                    return sym;
                }
            }
        }
    } else {
        hash_table_traverse(symtab->expansion, sym, valp) {
            val = *valp;

            if (val == value
            && !julie_symbol_starts_with_ampersand(interp, sym)) {

                return sym;
            }
        }
    }

    return NULL;
}

static inline Julie_Symbol_Table *julie_new_symtab(void) {
    Julie_Symbol_Table *symtab;

    posix_memalign((void**)&symtab, 64, sizeof(*symtab));
    memset(symtab, 0, sizeof(*symtab));

    return symtab;
}


static Julie_Symbol_Table *julie_local_symtab(Julie_Interp *interp) {
    return interp->local_symtab_depth > 0
            ? julie_array_elem(interp->local_symtab_stack, interp->local_symtab_depth - 1)
            : NULL;
}

static Julie_Symbol_Table *julie_push_local_symtab(Julie_Interp *interp) {
    Julie_Symbol_Table *symtab;

    interp->local_symtab_depth += 1;

    if (julie_array_len(interp->local_symtab_stack) < interp->local_symtab_depth) {
        symtab = julie_new_symtab();

        JULIE_ARRAY_PUSH(interp->local_symtab_stack, symtab);

        JULIE_ASSERT(julie_array_len(interp->local_symtab_stack) == interp->local_symtab_depth);
    } else {
        symtab = julie_array_elem(interp->local_symtab_stack, interp->local_symtab_depth - 1);
    }

    return symtab;
}

static void julie_clear_symtab(Julie_Interp *interp, Julie_Symbol_Table *symtab) {
    Julie_Array      *collect;
    unsigned          i;
    Julie_String_ID   id;
    Julie_Value      *val;
    Julie_Value     **valp;

    collect = JULIE_ARRAY_INIT;

    if (symtab->expansion == NULL) {
        for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
            id = symtab->syms[i];
            if (id != NULL) {
                val = symtab->vals[i];

                if (!julie_symbol_starts_with_ampersand(interp, id)
                ||  val->type == JULIE_BUILTIN_FN) {

                    JULIE_ARRAY_PUSH(collect, val);
                }
            }
        }
    } else {
        hash_table_traverse(symtab->expansion, id, valp) {
            val = *valp;

            if (!julie_symbol_starts_with_ampersand(interp, id)
            ||  val->type == JULIE_BUILTIN_FN) {

                JULIE_ARRAY_PUSH(collect, val);
            }
        }
    }

    ARRAY_FOR_EACH(collect, val) {
        if (!val->source_node) {
            julie_force_free_value(interp, val);
        }
    }

    julie_array_free(collect);

    if (symtab->expansion != NULL) {
        hash_table_free(symtab->expansion);
    }

    memset(symtab, 0, sizeof(*symtab));
}

static Julie_Status julie_pop_local_symtab(Julie_Interp *interp, Julie_String_ID *err_sym) {
    Julie_Symbol_Table  *symtab;
    unsigned             i;
    Julie_String_ID      id;
    Julie_Value         *val;
    Julie_Value        **valp;

    symtab = julie_local_symtab(interp);
    JULIE_ASSERT(symtab != NULL);

    if (symtab->expansion == NULL) {
        for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
            id = symtab->syms[i];
            if (id != NULL) {
                val = symtab->vals[i];

                if (julie_symbol_starts_with_ampersand(interp, id)
                &&  val->type != JULIE_BUILTIN_FN) {

                    JULIE_UNBORROW(val);
                }
            }
        }

        for (i = 0; i < JULIE_SYMTAB_SIZE; i += 1) {
            id = symtab->syms[i];
            if (id != NULL) {
                val = symtab->vals[i];

                if (!julie_symbol_starts_with_ampersand(interp, id)
                ||  val->type == JULIE_BUILTIN_FN) {

                    if (julie_borrows_outstanding(val)) {
                        if (err_sym != NULL) {
                            *err_sym = id;
                        }
                        return JULIE_ERR_RELEASE_WHILE_BORROWED;
                    }
                }
            }
        }
    } else {
        hash_table_traverse(symtab->expansion, id, valp) {
            val = *valp;

            if (julie_symbol_starts_with_ampersand(interp, id)
            &&  val->type != JULIE_BUILTIN_FN) {

                JULIE_UNBORROW(val);
            }
        }

        hash_table_traverse(symtab->expansion, id, valp) {
            val = *valp;

            if (!julie_symbol_starts_with_ampersand(interp, id)
            ||  (*valp)->type == JULIE_BUILTIN_FN) {

                if (julie_borrows_outstanding(val)) {
                    if (err_sym != NULL) {
                        *err_sym = id;
                    }
                    return JULIE_ERR_RELEASE_WHILE_BORROWED;
                }
            }
        }
    }

    julie_clear_symtab(interp, symtab);

    interp->local_symtab_depth -= 1;

    return JULIE_SUCCESS;
}

static Julie_Status _julie_bind_new(Julie_Interp           *interp,
                                    const Julie_String_ID   name,
                                    Julie_Value           **valuep,
                                    Julie_Symbol_Table     *symtab) {

    int          ref;
    int          need_copy;
    Julie_Value *copy;

    ref = julie_symbol_starts_with_ampersand(interp, name) && (*valuep)->type != JULIE_BUILTIN_FN;

    if (unlikely(ref && !(*valuep)->owned)) {
        return JULIE_ERR_REF_OF_TRANSIENT;
    }

    need_copy = 1;

    if (!(*valuep)->source_node) {
        if (ref) {
            JULIE_ASSERT((*valuep)->owned);

            need_copy = 0;
        } else {
            if (!(*valuep)->owned) {
                need_copy = 0;
            }
        }
    }

    if (need_copy) {
        copy = julie_force_copy(interp, *valuep);
        julie_free_value(interp, *valuep);
        *valuep = copy;
    }

    if (ref) {
        JULIE_BORROW(*valuep);
    } else {
        JULIE_ASSERT(!(*valuep)->owned);
        (*valuep)->owned = 1;
    }

    julie_symtab_insert(symtab, name, *valuep);

    return JULIE_SUCCESS;
}

static Julie_Status _julie_bind_existing(Julie_Interp           *interp,
                                         const Julie_String_ID   name,
                                         Julie_Value           **valuep,
                                         Julie_Symbol_Table     *symtab,
                                         Julie_Value            *existing) {

    Julie_Value *copy;

    (void)symtab;

    if (unlikely(existing == *valuep)) { return JULIE_SUCCESS; }

    if ((*valuep)->source_node || (*valuep)->owned) {
        copy = julie_force_copy(interp, *valuep);
        julie_free_value(interp, *valuep);
        *valuep = copy;
    }

    if (julie_borrows_to_subvalues_outstanding(existing, existing)) {
        return JULIE_ERR_RELEASE_WHILE_BORROWED;
    }

    julie_replace_value(interp, existing, *valuep);

    return JULIE_SUCCESS;
}

static Julie_Status _julie_bind(Julie_Interp *interp, const Julie_String_ID name, Julie_Value **valuep, int local) {
    Julie_Symbol_Table *symtab;
    Julie_Value        *lookup;

    if (local) {
        symtab = julie_local_symtab(interp);
        JULIE_ASSERT(symtab != NULL);
    } else {
        symtab = interp->global_symtab;
    }

    lookup = julie_symtab_search(symtab, name);

    if (lookup == NULL) {
        return _julie_bind_new(interp, name, valuep, symtab);
    }
    return _julie_bind_existing(interp, name, valuep, symtab, lookup);
}

static Julie_Status _julie_unbind(Julie_Interp *interp, const Julie_String_ID name, int local) {
    Julie_Symbol_Table *symtab;
    Julie_Value        *value;
    int                 ref;

    if (local) {
        symtab = julie_local_symtab(interp);
        JULIE_ASSERT(symtab != NULL);
    } else {
        symtab = interp->global_symtab;
    }

    value = julie_symtab_search(symtab, name);

    if (value == NULL) {
        return JULIE_ERR_LOOKUP;
    }

    ref = julie_symbol_starts_with_ampersand(interp, name) && value->type != JULIE_BUILTIN_FN;

    if (ref) {
        JULIE_ASSERT(value->owned);
        JULIE_UNBORROW(value);
    } else {
        if (julie_borrows_outstanding(value)) {
            return JULIE_ERR_RELEASE_WHILE_BORROWED;
        }

        julie_force_free_value(interp, value);
    }

    julie_symtab_del(symtab, name);

    return JULIE_SUCCESS;
}

Julie_Status julie_bind(Julie_Interp *interp, const Julie_String_ID name, Julie_Value **valuep) {
    return _julie_bind(interp, name, valuep, 0);
}
Julie_Status julie_bind_local(Julie_Interp *interp, const Julie_String_ID name, Julie_Value **valuep) {
    return _julie_bind(interp, name, valuep, 1);
}
Julie_Status julie_unbind(Julie_Interp *interp, const Julie_String_ID name) {
    return _julie_unbind(interp, name, 0);
}
Julie_Status julie_unbind_local(Julie_Interp *interp, const Julie_String_ID name) {
    return _julie_unbind(interp, name, 1);
}

Julie_Status julie_bind_fn(Julie_Interp *interp, Julie_String_ID id, Julie_Fn fn) {
    Julie_Value *fn_val;

    fn_val = julie_builtin_fn_value(interp, fn);

    return julie_bind(interp, id, &fn_val);
}

Julie_Status julie_bind_infix_fn(Julie_Interp *interp, Julie_String_ID id, Julie_Fn fn) {
    Julie_Value *fn_val;

    fn_val      = julie_builtin_fn_value(interp, fn);
    fn_val->tag = JULIE_INFIX_FN;

    return julie_bind(interp, id, &fn_val);
}

Julie_Value *julie_lookup(Julie_Interp *interp, const Julie_String_ID id) {
    Julie_Value        *val;
    Julie_Symbol_Table *local_symtab;

    val = NULL;

    local_symtab = julie_local_symtab(interp);
    if (local_symtab != NULL) {
        val = julie_symtab_search(local_symtab, id);
    }

    if (val == NULL) {
        val = julie_symtab_search(interp->global_symtab, id);
    }

    if (unlikely(val == NULL)) { return NULL; }

    return val;
}

/*********************************************************
 *                         Errors                        *
 *********************************************************/

void julie_free_error_info(Julie_Error_Info *info) {

#define FREE_IF_NOT_NULL(x) if ((x) != NULL) { free(x); }

    switch (info->status) {
        case JULIE_ERR_LOOKUP:
            FREE_IF_NOT_NULL(info->lookup.sym);
            break;
        case JULIE_ERR_RELEASE_WHILE_BORROWED:
            FREE_IF_NOT_NULL(info->release_while_borrowed.sym);
            break;
        case JULIE_ERR_MODIFY_WHILE_ITER:
            FREE_IF_NOT_NULL(info->modify_while_iter.sym);
            break;
        case JULIE_ERR_ARITY:
            break;
        case JULIE_ERR_TYPE:
            break;
        case JULIE_ERR_BAD_APPLY:
            break;
        case JULIE_ERR_BAD_INDEX:
            julie_free_value(info->interp, info->bad_index.bad_index);
            break;
        case JULIE_ERR_FILE_NOT_FOUND:
        case JULIE_ERR_FILE_IS_DIR:
        case JULIE_ERR_MMAP_FAILED:
            FREE_IF_NOT_NULL(info->file.path);
            break;
        case JULIE_ERR_LOAD_PACKAGE_FAILURE:
            FREE_IF_NOT_NULL(info->load_package_failure.path);
            FREE_IF_NOT_NULL(info->load_package_failure.package_error_message);
            break;
        case JULIE_ERR_REGEX:
            FREE_IF_NOT_NULL(info->regex.regex_error_message);
            break;
        default:
            break;
    }
}

static void julie_error(Julie_Interp *interp, Julie_Error_Info *info) {
    Julie_Source_Value_Info *source_info;

    source_info = julie_get_top_source_value_info(interp);
    if (source_info != NULL) {
        info->file_id = source_info->file_id;
        info->line    = source_info->line;
        info->col     = source_info->col;
    } else {
        info->file_id = interp->cur_file_id;
    }

    if (interp->error_callback != NULL) {
        interp->error_callback(info);
    } else {
        julie_free_error_info(info);
    }
}

void julie_make_parse_error(Julie_Interp *interp, unsigned long long line, unsigned long long col, Julie_Status status) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = status;
    info.line   = line;
    info.col    = col;
    julie_error(interp, &info);
}

void julie_make_interp_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = status;

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_bad_apply_error(Julie_Interp *interp, Julie_Value *expr, Julie_Type got) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp                   = interp;
    info.status                   = JULIE_ERR_BAD_APPLY;
    info.bad_application.got_type = got;

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_arity_error(Julie_Interp *interp, Julie_Value *expr, int wanted, int got, int at_least) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp             = interp;
    info.status             = JULIE_ERR_ARITY;
    info.arity.wanted_arity = wanted;
    info.arity.got_arity    = got;
    info.arity.at_least     = at_least;

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_type_error(Julie_Interp *interp, Julie_Value *expr, Julie_Type wanted, Julie_Type got) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp           = interp;
    info.status           = JULIE_ERR_TYPE;
    info.type.wanted_type = wanted;
    info.type.got_type    = got;

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_lookup_error(Julie_Interp *interp, Julie_Value *expr, const Julie_String_ID id) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp     = interp;
    info.status     = JULIE_ERR_LOOKUP;
    info.lookup.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_bind_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, Julie_String_ID id) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = status;

    switch (status) {
        case JULIE_ERR_LOOKUP:
            info.lookup.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));
            break;
        case JULIE_ERR_RELEASE_WHILE_BORROWED:
            info.release_while_borrowed.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));
            break;
        case JULIE_ERR_REF_OF_TRANSIENT:
            info.ref_of_transient.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));
            break;
        case JULIE_ERR_REF_OF_OBJECT_KEY:
            info.ref_of_object_key.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));
            break;
        case JULIE_ERR_NOT_LVAL:
            info.not_lval.sym = id == NULL ? NULL : strdup(julie_get_cstring(id));
            break;
        default:
            break;
    }

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_bad_index_error(Julie_Interp *interp, Julie_Value *expr, Julie_Value *bad_index) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = JULIE_ERR_BAD_INDEX;
    info.bad_index.bad_index = julie_force_copy(interp, bad_index);

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_must_follow_if_error(Julie_Interp *interp, Julie_Value *expr) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = JULIE_ERR_MUST_FOLLOW_IF;

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_file_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, const char *path) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp = interp;
    info.status = status;

    info.file.path = strdup(path);

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_load_package_error(Julie_Interp *interp, Julie_Value *expr, Julie_Status status, const char *path, const char *message) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp                = interp;
    info.status                = status;

    info.load_package_failure.path = strdup(path);
    info.load_package_failure.package_error_message = message == NULL ? "unknown error" : strdup(message);

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

void julie_make_regex_error(Julie_Interp *interp, Julie_Value *expr, const char *message) {
    Julie_Error_Info info;
    memset(&info, 0, sizeof(info));
    info.interp                = interp;
    info.status                = JULIE_ERR_REGEX;

    info.regex.regex_error_message = strdup(message);

    JULIE_ARRAY_PUSH(interp->value_stack, expr);
    julie_error(interp, &info);
    julie_array_pop(interp->value_stack);
}

Julie_Backtrace_Entry *julie_bt_entry(Julie_Interp *interp, unsigned long long depth) {
    unsigned long long     apply_depth;
    unsigned long long     idx;
    Julie_Backtrace_Entry *entry;

    apply_depth = interp->apply_depth;

    if (apply_depth < 1)      { return NULL; }
    if (depth >= apply_depth) { return NULL; }

    idx = apply_depth - depth - 1;

    entry = &(((Julie_Apply_Context*)julie_array_elem(interp->apply_contexts, idx))->bt_entry);

    return entry;
}

/*********************************************************
 *                        Parsing                        *
 *********************************************************/

#define PARSE_ERR_RET(_interp, _status, _line, _col)                   \
do {                                                                   \
    if ((_status) != JULIE_SUCCESS) {                                  \
        julie_make_parse_error((_interp), (_line), (_col), (_status)); \
    }                                                                  \
    return (_status);                                                  \
} while (0)

static inline int julie_is_space(int c) {
    unsigned char d = c - 9;
    return (0x80001FU >> (d & 31)) & (1U >> (d >> 5));
}

static inline int julie_is_digit(int c) {
    return (unsigned int)(('0' - 1 - c) & (c - ('9' + 1))) >> (sizeof(c) * 8 - 1);
}

static inline int julie_is_alpha(int c) {
    return (unsigned int)(('a' - 1 - (c | 32)) & ((c | 32) - ('z' + 1))) >> (sizeof(c) * 8 - 1);
}

static inline int julie_is_alnum(int c) {
    return julie_is_alpha(c) || julie_is_digit(c);
}

typedef enum {
    JULIE_TK_NONE,
    JULIE_TK_LPAREN,
    JULIE_TK_RPAREN,
    JULIE_TK_SYMBOL,
    JULIE_TK_SINT,
    JULIE_TK_HEX,
    JULIE_TK_FLOAT,
    JULIE_TK_STRING,
    JULIE_TK_EOS_ERR,
    JULIE_TK_UNEXPECTED_ERR,
} Julie_Token;

#define MORE_INPUT(_cxt)    ((_cxt)->cursor < (_cxt)->end)
#define PEEK_CHAR(_cxt, _c) ((_c) = (MORE_INPUT(_cxt) ? (*(_cxt)->cursor) : 0))
#define NEXT(_cxt)          ((_cxt)->cursor += 1)
#define SPC(_c)             (julie_is_space(_c))
#define DIG(_c)             (julie_is_digit(_c))
#define HEX(_c)             (julie_is_digit(_c) || ('a' <= (_c) && (_c) <= 'f') || ('A' <= (_c) && (_c) <= 'F'))

static Julie_Token julie_parse_token(Julie_Parse_Context *cxt) {
    int         c;
    int         last;
    const char *start;

    if (!PEEK_CHAR(cxt, c)) { return JULIE_TK_NONE; }

    if (c == '(') {
        NEXT(cxt);
        return JULIE_TK_LPAREN;
    } else if (c == ')') {
        NEXT(cxt);
        return JULIE_TK_RPAREN;
    } else if (c == '"') {
        do {
            if (c == '\n') { return JULIE_TK_EOS_ERR; }
            last = c;
            NEXT(cxt);
        } while (PEEK_CHAR(cxt, c) && (c != '"' || last == '\\'));

        NEXT(cxt);

        return JULIE_TK_STRING;
    } else if (c == '-' && ((cxt->cursor + 1) < cxt->end) && DIG(*(cxt->cursor + 1))) {
        NEXT(cxt);
        PEEK_CHAR(cxt, c);
        goto digits;

    } else if (DIG(c)) {
digits:;
        if (c == '0') {
            NEXT(cxt);
            if (PEEK_CHAR(cxt, c) && c == 'x') {
                NEXT(cxt);
                if (!PEEK_CHAR(cxt, c) || !HEX(c)) {
                    return JULIE_TK_UNEXPECTED_ERR;
                }

                do {
                    NEXT(cxt);
                } while (PEEK_CHAR(cxt, c) && HEX(c));

                return JULIE_TK_HEX;
            }
        }

        while (PEEK_CHAR(cxt, c) && DIG(c)) { NEXT(cxt); }
        if (PEEK_CHAR(cxt, c) == '.') {
            NEXT(cxt);
            while (PEEK_CHAR(cxt, c) && DIG(c)) { NEXT(cxt); }
            return JULIE_TK_FLOAT;
        }

        return JULIE_TK_SINT;
    }

    start = cxt->cursor;

    while (PEEK_CHAR(cxt, c)
    &&     !SPC(c)
    &&     c != '#'
    &&     c != '('
    &&     c != ')') {

        NEXT(cxt);
    }

    if (cxt->cursor > start) {
        return JULIE_TK_SYMBOL;
    }

    return JULIE_TK_NONE;
}

static int julie_trim_leading_ws(Julie_Parse_Context *cxt) {
    int w;
    int c;

    w = 0;

    while (PEEK_CHAR(cxt, c) && c != '\n' && SPC(c)) {
        NEXT(cxt);
        w += 1;
    }

    return w;
}

static int julie_consume_comment(Julie_Parse_Context *cxt) {
    int c;

    if (PEEK_CHAR(cxt, c) && c == '#') {
        NEXT(cxt);
        while (PEEK_CHAR(cxt, c)) {
            if (c == '\n') { break; }
            NEXT(cxt);
        }
        return 1;
    }

    return 0;
}

static Julie_Value *julie_push_list(Julie_Parse_Context *cxt) {
    Julie_Interp            *interp;
    Julie_Value             *value;
    Julie_Source_Value_Info *info;

    interp = cxt->interp;
    (void)interp;

    value = JULIE_NEW();
    value->type         = JULIE_LIST;
    value->tag          = 0;
    value->source_node  = 1;
    value->owned        = 0;
    value->borrow_count = 0;
    value->list         = JULIE_ARRAY_INIT;
    JULIE_ARRAY_PUSH(cxt->parse_stack, value);

    info = malloc(sizeof(*info));
    info->file_id = interp->cur_file_id;
    info->ind     = cxt->ind;
    info->line    = cxt->line;
    info->col     = cxt->col;

    JULIE_ARRAY_SET_AUX(value->list, (void*)((unsigned long long)info | 1ull));
    JULIE_ARRAY_PUSH(cxt->interp->source_infos, info);

    return value;
}

static Julie_Status julie_parse_next_value(Julie_Parse_Context *cxt, Julie_Value **valout, Julie_Token *tkout) {
    int                 status;
    Julie_Value        *val;
    int                 start_col;
    const char         *tk_start;
    Julie_Token         tk;
    const char         *tk_end;
    Julie_Value        *top;
    Julie_Value        *child;
    int                 c;
    char               *sbuff;
    unsigned long long  slen;
    char                tk_copy[128];
    long long           s;
    unsigned long long  u;
    double              d;

    status  = JULIE_SUCCESS;
    val     = NULL;
    *valout = NULL;
    *tkout  = JULIE_TK_NONE;

    cxt->col += julie_trim_leading_ws(cxt);
    if (julie_consume_comment(cxt)) { goto out; }

    tk_start = cxt->cursor;
    if ((tk = julie_parse_token(cxt)) == JULIE_TK_NONE) { goto out; }
    if (tk == JULIE_TK_UNEXPECTED_ERR) {
        status = JULIE_ERR_UNEXPECTED_TOK;
        goto out;
    }
    tk_end = cxt->cursor;

    start_col = cxt->col;

    if (tk == JULIE_TK_LPAREN) {
        julie_push_list(cxt);
        val = top = julie_array_top(cxt->parse_stack);

        cxt->col += tk_end - tk_start;

        cxt->plevel += 1;

        child = NULL;
        while ((status = julie_parse_next_value(cxt, &child, tkout)) == JULIE_SUCCESS && child != NULL) {
            JULIE_ARRAY_PUSH(top->list, child);
        }

        if (status != JULIE_SUCCESS) {
            PARSE_ERR_RET(cxt->interp, status, cxt->line, cxt->col);
        }

        if (*tkout != JULIE_TK_RPAREN) {
            PARSE_ERR_RET(cxt->interp, JULIE_ERR_MISSING_RPAREN, cxt->line, cxt->col);
        }

        cxt->plevel -= 1;

        *tkout = JULIE_TK_LPAREN;

        julie_array_pop(cxt->parse_stack);

        goto out_val;
    } else if (tk == JULIE_TK_RPAREN) {
        if (cxt->plevel <= 0) {
            PARSE_ERR_RET(cxt->interp, JULIE_ERR_EXTRA_RPAREN, cxt->line, cxt->col);
        }

        *tkout = JULIE_TK_RPAREN;

        cxt->col += tk_end - tk_start;
        goto out;
    }

    *tkout = tk;

    cxt->col += tk_end - tk_start;

    switch (tk) {
        case JULIE_TK_SYMBOL:
            if (tk_end - tk_start == 3 && strncmp(tk_start, "nil", tk_end - tk_start) == 0) {
                val = julie_source_nil_value(cxt->interp);
            } else {
                sbuff = alloca(tk_end - tk_start + 1);
                memcpy(sbuff, tk_start, tk_end - tk_start);
                sbuff[tk_end - tk_start] = 0;
                val = julie_source_symbol_value(cxt->interp, julie_get_string_id(cxt->interp, sbuff));
            }
            break;
        case JULIE_TK_STRING:
            JULIE_ASSERT(tk_start[0] == '"' && "string doesn't start with quote");
            tk_start += 1;

            sbuff = alloca(tk_end - tk_start + 1);
            slen  = 0;

            for (; tk_start < tk_end; tk_start += 1) {
                c = *tk_start;

                if (c == '"') { break; }
                if (c == '\\') {
                    tk_start += 1;
                    if (tk_start < tk_end) {
                        switch (*tk_start) {
                            case '\\':
                                break;
                            case 'n':
                                c = '\n';
                                break;
                            case 'r':
                                c = '\r';
                                break;
                            case 't':
                                c = '\t';
                                break;
                            case '"':
                                c = '"';
                                break;
                            case 'e':
                                c = '\033';
                                break;
                            case '0':
                                c = '\0';
                                break;
                            default:
                                sbuff[slen]  = c;
                                slen        += 1;
                                c            = *tk_start;
                                goto add_char;
                        }
                    }
                    goto add_char;
                } else {
add_char:;
                    sbuff[slen] = c;
                }
                slen += 1;
            }

            sbuff[slen] = 0;

            val = julie_source_interned_string_value(cxt->interp, julie_get_string_id(cxt->interp, sbuff));
            break;
        case JULIE_TK_SINT:
            strncpy(tk_copy, tk_start, tk_end - tk_start);
            tk_copy[tk_end - tk_start] = 0;
            sscanf(tk_copy, "%lld", &s);
            val = julie_source_sint_value(cxt->interp, s);
            break;
        case JULIE_TK_HEX:
            strncpy(tk_copy, tk_start, tk_end - tk_start);
            tk_copy[tk_end - tk_start] = 0;
            sscanf(tk_copy, "%llx", &u);
            val = julie_source_uint_value(cxt->interp, u);
            break;
        case JULIE_TK_FLOAT:
            strncpy(tk_copy, tk_start, tk_end - tk_start);
            tk_copy[tk_end - tk_start] = 0;
            sscanf(tk_copy, "%lg", &d);
            val = julie_source_float_value(cxt->interp, d);
            break;
        case JULIE_TK_EOS_ERR:
            PARSE_ERR_RET(cxt->interp, JULIE_ERR_UNEXPECTED_EOS, cxt->line, start_col + (tk_end - tk_start));
            break;
        default:
            break;
    }

out_val:;

    JULIE_ASSERT(val != NULL);

    *valout = val;

out:;
    return status;
}

static Julie_Status julie_parse_line(Julie_Parse_Context *cxt) {
    int                      status;
    int                      c;
    Julie_Value             *top;
    Julie_Source_Value_Info *info;
    Julie_Value             *val;
    Julie_Token              tk;

    status = JULIE_SUCCESS;

    cxt->ind = julie_trim_leading_ws(cxt);
    cxt->col = 1 + cxt->ind;

    if (!PEEK_CHAR(cxt, c))                      { goto done; }
    if (c == '\n' || julie_consume_comment(cxt)) { goto eol;  }

    while ((top = julie_array_top(cxt->parse_stack)) != NULL
    &&     (info = julie_get_source_value_info(top))
    &&     cxt->ind <= info->ind) {

        julie_array_pop(cxt->parse_stack);
    }

    val = julie_push_list(cxt);
    if (top == NULL) {
        JULIE_ARRAY_PUSH(cxt->interp->roots, val);
    } else {
        JULIE_ARRAY_PUSH(top->list, val);
    }
    top = val;

    val = NULL;
    while ((status = julie_parse_next_value(cxt, &val, &tk)) == JULIE_SUCCESS && val != NULL) {
        JULIE_ARRAY_PUSH(top->list, val);
    }

    if (status != JULIE_SUCCESS) {
        PARSE_ERR_RET(cxt->interp, status, cxt->line, cxt->col);
    }

eol:;
    if (PEEK_CHAR(cxt, c)) {
        if (c == '\n') {
            NEXT(cxt);
        } else {
            PARSE_ERR_RET(cxt->interp, JULIE_ERR_UNEXPECTED_TOK, cxt->line, cxt->col);
        }
    }

done:;
    return status;
}

Julie_Status julie_parse(Julie_Interp *interp, const char *str, int size) {

    Julie_Parse_Context cxt;
    Julie_Status        status;

    memset(&cxt, 0, sizeof(cxt));

    cxt.interp      = interp;
    cxt.cursor      = str;
    cxt.end         = str + size;
    cxt.parse_stack = JULIE_ARRAY_INIT;

    status = JULIE_SUCCESS;


    while (status == JULIE_SUCCESS && MORE_INPUT(&cxt)) {
        cxt.line += 1;
        status = julie_parse_line(&cxt);
    }

    julie_array_free(cxt.parse_stack);

    return status;
}





/*********************************************************
 *                       Builtins                        *
 *********************************************************/

static Julie_Status julie_eval(Julie_Interp *interp, Julie_Value *value, Julie_Value **result);
static Julie_Status julie_invoke(Julie_Interp *interp, Julie_Value *list, Julie_Value *fn, unsigned long long n_values, Julie_Value **values, Julie_Value **result);
static Julie_Value *julie_copy(Julie_Interp *interp, Julie_Value *value);

static unsigned _julie_arg_legend_get_arity(const char *legend) {
    unsigned legend_len;
    unsigned count;
    unsigned i;

    legend_len = strlen(legend);
    count      = 0;
    for (i = 0; i < legend_len; i += 1) {
        count += legend[i] != '-' && legend[i] != '!' && legend[i] != '&';
    }

    return count;
}

static Julie_Status julie_args(Julie_Interp *interp, Julie_Value *expr, const char *legend, unsigned n_values, Julie_Value **values, ...) {
    Julie_Status   status;
    const char    *save_legend;
    va_list        args;
    unsigned       i;
    int            no_eval;
    int            lval;
    int            c;
    Julie_Value   *v;
    Julie_Value  **ve_ptr;
    va_list        cleanup_args;
    unsigned       j;
    int            t;

    status = JULIE_SUCCESS;

    save_legend = legend;

    va_start(args, values);

    i         = 0;
    no_eval   = 0;
    lval      = 0;
    while ((c = *legend)) {
        if (c == '-') {
            no_eval = 1;
            goto nextc;
        }
        if (c == '&') {
            lval = 1;
            goto nextc;
        }

        if (i == n_values) {
            status = JULIE_ERR_ARITY;
            julie_make_arity_error(interp, expr, _julie_arg_legend_get_arity(save_legend), n_values, 0);
            goto out;
        }

        v = values[i];

        ve_ptr = va_arg(args, Julie_Value**);

        if (no_eval) {
            *ve_ptr = julie_force_copy(interp, v);
        } else {
            status = julie_eval(interp, v, ve_ptr);
            if (status != JULIE_SUCCESS) {
                va_start(cleanup_args, values);
                for (j = 0; j < i; j += 1) {
                    ve_ptr = va_arg(cleanup_args, Julie_Value**);
                    julie_free_value(interp, *ve_ptr);
                    *ve_ptr = NULL;
                }
                va_end(cleanup_args);
                goto out;
            }
        }

        switch (c) {
            case '*': goto type_good;
            case '0': t = JULIE_NIL;    break;
            case 's': t = JULIE_STRING; break;
            case '$': t = JULIE_SYMBOL; break;
            case 'l': t = JULIE_LIST;   break;
            case 'o': t = JULIE_OBJECT; break;
            case 'u': t = JULIE_UINT;   break;
            case 'd': t = JULIE_SINT;   break;
            case 'f': t = JULIE_FLOAT;  break;
            case 'i':
                if (JULIE_TYPE_IS_INTEGER((*ve_ptr)->type)) {
                    t = (*ve_ptr)->type;
                } else {
                    t = _JULIE_INTEGER;
                }
                break;
            case 'n':
                if (JULIE_TYPE_IS_NUMBER((*ve_ptr)->type)) {
                    t = (*ve_ptr)->type;
                } else {
                    t = _JULIE_NUMBER;
                }
                break;
            case '#':
                if ((*ve_ptr)->type == JULIE_LIST || (*ve_ptr)->type == JULIE_OBJECT) {
                    t = (*ve_ptr)->type;
                } else {
                    t = _JULIE_LIST_OR_OBJECT;
                }
                break;
            case 'k':
                if (JULIE_TYPE_IS_KEYLIKE((*ve_ptr)->type)) {
                    t = (*ve_ptr)->type;
                } else {
                    t = _JULIE_KEYLIKE;
                }
                break;
            default:
                t = JULIE_UNKNOWN;
                break;
        }

        if ((*ve_ptr)->type != t) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, v, t, (*ve_ptr)->type);
            va_start(cleanup_args, values);
            for (j = 0; j <= i; j += 1) {
                ve_ptr = va_arg(cleanup_args, Julie_Value**);
                julie_free_value(interp, *ve_ptr);
                *ve_ptr = NULL;
            }
            va_end(cleanup_args);
            goto out;
        }

type_good:;

        if (lval && !(*ve_ptr)->owned) {
            status = JULIE_ERR_NOT_LVAL;
            julie_make_bind_error(interp, v, status, NULL);
            va_start(cleanup_args, values);
            for (j = 0; j <= i; j += 1) {
                ve_ptr = va_arg(cleanup_args, Julie_Value**);
                julie_free_value(interp, *ve_ptr);
                *ve_ptr = NULL;
            }
            va_end(cleanup_args);
            goto out;
        }

        i += 1;

        no_eval = lval = 0;

nextc:;
        legend += 1;
    }

    if (i != n_values) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, _julie_arg_legend_get_arity(save_legend), n_values, 0);
        goto out;
    }

out:;
    va_end(args);

    return status;
}

static Julie_Status julie_builtin_typeof(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;

    status = julie_args(interp, expr, "*", n_values, values, &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    *result = julie_interned_string_value(interp, julie_get_string_id(interp, julie_type_string(val->type)));

    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_sint(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_NUMBER(val->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, val->type);
        goto out_free;
    }

    if (val->type == JULIE_SINT) {
        *result = julie_sint_value(interp, val->sint);
    } else if (val->type == JULIE_UINT) {
        *result = julie_sint_value(interp, (long long)val->uint);
    } else if (val->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (long long)val->floating);
    } else {
        JULIE_ASSERT(0);
    }

out_free:;
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_uint(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_NUMBER(val->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, val->type);
        goto out_free;
    }

    if (val->type == JULIE_SINT) {
        *result = julie_uint_value(interp, (unsigned long long)val->sint);
    } else if (val->type == JULIE_UINT) {
        *result = julie_uint_value(interp, val->uint);
    } else if (val->type == JULIE_FLOAT) {
        *result = julie_uint_value(interp, (unsigned long long)val->floating);
    } else {
        JULIE_ASSERT(0);
    }

out_free:;
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_float(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_NUMBER(val->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, val->type);
        goto out_free;
    }

    if (val->type == JULIE_SINT) {
        *result = julie_float_value(interp, (double)val->sint);
    } else if (val->type == JULIE_UINT) {
        *result = julie_float_value(interp, (double)val->uint);
    } else if (val->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, val->floating);
    } else {
        JULIE_ASSERT(0);
    }

out_free:;
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_string(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;
    char         *s;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    s = julie_to_string(interp, val, JULIE_NO_QUOTE);

    *result = julie_string_value_giveaway(interp, s);

    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_id(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *value;
    Julie_Value  *ev;
    Julie_Value  *lookup;

    status = julie_args(interp, expr, "-*", n_values, values, &value);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    switch (value->type) {
        case JULIE_SINT:
        case JULIE_UINT:
        case JULIE_FLOAT:
        case JULIE_STRING:
        case JULIE_LIST:
        case JULIE_OBJECT:
            status = julie_eval(interp, value, &ev);
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                goto out_free;
            }
            break;
        case JULIE_SYMBOL:
            lookup = julie_lookup(interp, value->string_id);
            if (lookup == NULL) {
                status = JULIE_ERR_LOOKUP;
                julie_make_lookup_error(interp, value, value->string_id);
                *result = NULL;
                goto out_free;
            }

            ev = julie_copy(interp, lookup);
            break;
        default:
            JULIE_ASSERT(0);
            ev = NULL;
            break;
    }

    *result = ev;

out_free:;
    julie_free_value(interp, value);

out:;
    return status;
}

static Julie_Status julie_builtin_quote(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status status;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values != 1) {
        *result = NULL;
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    *result = julie_copy(interp, values[0]);

out:;
    return status;
}

static Julie_Status _julie_builtin_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result, int global) {
    Julie_Status     status;
    Julie_Value     *l;
    Julie_Value     *rval;
    Julie_String_ID  id;
    Julie_Value     *lval;
    Julie_Value     *cpy;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    l = values[0];
    status = julie_eval(interp, values[1], &rval);
    if (status != JULIE_SUCCESS) { goto out; }

    if (l->type == JULIE_SYMBOL) {
        id = julie_value_string_id(interp, l);

        if (global || interp->local_symtab_depth == 0) {
            status = julie_bind(interp, id, &rval);
        } else {
            status = julie_bind_local(interp, id, &rval);
        }
        if (status != JULIE_SUCCESS) {
            julie_make_bind_error(interp, expr, status, id);
            julie_free_value(interp, rval);
            goto out;
        }
    } else {
        if ((status = julie_eval(interp, l, &lval)) != JULIE_SUCCESS) { goto out; }

        if (!lval->owned) {
            julie_free_value(interp, lval);
            julie_free_value(interp, rval);
            *result = NULL;
            status = JULIE_ERR_NOT_LVAL;
            julie_make_bind_error(interp, l, status, NULL);
            goto out_free;
        }

        if (rval->owned) {
            cpy = julie_force_copy(interp, rval);
            julie_free_value(interp, rval);
            rval = cpy;
        }
        julie_replace_value(interp, lval, rval);
        rval = lval;
    }

    *result = julie_nil_value(interp);

out_free:;
    julie_free_value(interp, l);

out:;
    return status;
}

static Julie_Status julie_builtin_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_assign(interp, expr, n_values, values, result, 0);
}

static Julie_Status julie_builtin_assign_global(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_assign(interp, expr, n_values, values, result, 1);
}

static Julie_Status julie_builtin_unref(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status     status;
    Julie_Value     *sym;
    Julie_String_ID  id;
    Julie_Value     *lookup;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    sym = values[0];

    if (sym->type != JULIE_SYMBOL) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_SYMBOL, sym->type);
        *result = NULL;
        goto out;
    }

    id = julie_value_string_id(interp, sym);

    if (!julie_symbol_starts_with_ampersand(interp, id)) {
        status = JULIE_ERR_NOT_REF;
        julie_make_interp_error(interp, values[0], status);
        *result = NULL;
        goto out;
    }

    lookup = julie_lookup(interp, id);

    if (lookup == NULL) {
        status = JULIE_ERR_LOOKUP;
        julie_make_lookup_error(interp, values[0], id);
        *result = NULL;
        goto out;
    }

    if (interp->local_symtab_depth > 0) {
        status = julie_unbind_local(interp, id);
    } else {
        status = JULIE_ERR_LOOKUP;
    }

    if (status != JULIE_SUCCESS) {
        status = julie_unbind(interp, id);
        if (status != JULIE_SUCCESS) {
            julie_make_bind_error(interp, values[0], status, id);
            *result = NULL;
            goto out;
        }
    }

    *result = julie_nil_value(interp);

out:;
    return status;
}

static Julie_Status julie_builtin_is_bound(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status     status;
    Julie_Value     *sym;
    Julie_String_ID  id;
    Julie_Value     *lookup;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    sym = values[0];

    if (sym->type != JULIE_SYMBOL) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_SYMBOL, sym->type);
        *result = NULL;
        goto out;
    }

    id = julie_value_string_id(interp, sym);

    lookup = julie_lookup(interp, id);

    *result = julie_sint_value(interp, lookup != NULL);

out:;
    return status;
}

static Julie_Status julie_builtin_move(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *val;
    unsigned char       save_owned;
    unsigned long long  save_bc;
    Julie_Value        *dst;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        goto out;
    }

    if (val->owned && julie_borrows_to_subvalues_outstanding(val, val)) {
        *result = NULL;
        julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        goto out_free;
    }

    save_owned = val->owned;
    save_bc    = val->borrow_count;

    dst = JULIE_NEW();
    *dst = *val;

    memset(val, 0, sizeof(*val));
    val->type         = JULIE_NIL;
    val->owned        = save_owned;
    val->borrow_count = save_bc;

    dst->owned        = 0;
    dst->borrow_count = 0;

    *result = dst;

out_free:;
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_add(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint + b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint + b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->sint + b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint + b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint + (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->uint + b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, a->floating + b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_float_value(interp, a->floating + (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_float_value(interp, a->floating + (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_add_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!a->owned) {
        status = JULIE_ERR_NOT_LVAL;
        julie_make_bind_error(interp, values[0], status, NULL);
        goto out_free_a;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint += b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint += b->uint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        a->sint += b->floating;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint += b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint += b->sint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        a->uint += b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        a->floating += b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        a->floating += b->sint;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        a->floating += b->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_sub(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint - b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint - b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->sint - b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint - b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint - (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->uint - b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, a->floating - b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_float_value(interp, a->floating - (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_float_value(interp, a->floating - (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_sub_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint -= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint -= b->uint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        a->sint -= b->floating;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint -= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint -= b->sint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        a->uint -= b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        a->floating -= b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        a->floating -= b->sint;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        a->floating -= b->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_mul(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint * b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint * b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->sint * b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint * b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint * (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, (double)a->uint * b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_float_value(interp, a->floating * b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_float_value(interp, a->floating * (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_float_value(interp, a->floating * (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_mul_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint *= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint *= b->uint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        a->sint *= b->floating;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint *= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint *= b->sint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        a->uint *= b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        a->floating *= b->floating;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        a->floating *= b->sint;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        a->floating *= b->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_div(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if ((b->type == JULIE_SINT  && b->sint     == 0)
    ||  (b->type == JULIE_UINT  && b->uint     == 0)
    ||  (b->type == JULIE_FLOAT && b->floating == 0.0)) {

        *result = julie_nil_value(interp);
    } else {
        if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
            *result = julie_sint_value(interp, a->sint / b->sint);
        } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
            *result = julie_uint_value(interp, (unsigned long long)a->sint / b->uint);
        } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, (double)a->sint / b->floating);
        } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
            *result = julie_uint_value(interp, a->uint / b->uint);
        } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
            *result = julie_uint_value(interp, a->uint / (unsigned long long)b->sint);
        } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, (double)a->uint / b->floating);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, a->floating / b->floating);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
            *result = julie_float_value(interp, a->floating / (double)b->sint);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
            *result = julie_float_value(interp, a->floating / (double)b->uint);
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_div_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if ((b->type == JULIE_SINT  && b->sint     == 0)
    ||  (b->type == JULIE_UINT  && b->uint     == 0)
    ||  (b->type == JULIE_FLOAT && b->floating == 0.0)) {

        a->type = JULIE_NIL;
        a->uint = 0;
    } else {
        if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
            a->sint /= b->sint;
        } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
            a->sint /= b->uint;
        } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
            a->sint /= b->floating;
        } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
            a->uint /= b->uint;
        } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
            a->uint /= b->sint;
        } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
            a->uint /= b->floating;
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
            a->floating /= b->floating;
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
            a->floating /= b->sint;
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
            a->floating /= b->uint;
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_mod(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if ((b->type == JULIE_SINT  && b->sint     == 0)
    ||  (b->type == JULIE_UINT  && b->uint     == 0)
    ||  (b->type == JULIE_FLOAT && b->floating == 0.0)) {

        *result = julie_nil_value(interp);
    } else {
        if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
            *result = julie_sint_value(interp, a->sint % b->sint);
        } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
            *result = julie_uint_value(interp, (unsigned long long)a->sint % b->uint);
        } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, fmod((double)a->sint, b->floating));
        } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
            *result = julie_uint_value(interp, a->uint % b->uint);
        } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
            *result = julie_uint_value(interp, a->uint % (unsigned long long)b->sint);
        } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, fmod((double)a->uint, b->floating));
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
            *result = julie_float_value(interp, fmod(a->floating, b->floating));
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
            *result = julie_float_value(interp, fmod(a->floating, (double)b->sint));
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
            *result = julie_float_value(interp, fmod(a->floating, (double)b->uint));
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_mod_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if ((b->type == JULIE_SINT  && b->sint     == 0)
    ||  (b->type == JULIE_UINT  && b->uint     == 0)
    ||  (b->type == JULIE_FLOAT && b->floating == 0.0)) {

        a->type = JULIE_NIL;
        a->uint = 0;
    } else {
        if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
            a->sint %= b->sint;
        } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
            a->sint %= b->uint;
        } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
            a->sint = fmod((double)a->sint, b->floating);
        } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
            a->uint %= b->uint;
        } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
            a->uint %= b->sint;
        } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
            a->uint = fmod((double)a->uint, b->floating);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
            a->floating = fmod(a->floating, b->floating);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
            a->floating = fmod(a->floating, (double)b->sint);
        } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
            a->floating = fmod(a->floating, (double)b->uint);
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_not(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;

    status = julie_args(interp, expr, "i", n_values, values, &a);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT) {
        *result = julie_sint_value(interp, ~(a->sint));
    } else if (a->type == JULIE_UINT) {
        *result = julie_uint_value(interp, ~(a->uint));
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_and(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_INTEGER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_INTEGER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_INTEGER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_INTEGER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint & b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint & b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint & b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint & (unsigned long long)b->sint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_and_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint &= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint &= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint &= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint &= b->sint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_or(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint | b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint | b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint | b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint | (unsigned long long)b->sint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_or_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint |= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint |= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint |= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint |= b->sint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_xor(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint ^ b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint ^ b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint ^ b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint ^ (unsigned long long)b->sint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_xor_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint ^= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint ^= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint ^= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint ^= b->sint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_shl(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint << b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint << b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint << b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint << (unsigned long long)b->sint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_shl_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint <<= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint <<= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint <<= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint <<= b->sint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_shr(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_INTEGER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_INTEGER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_INTEGER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_INTEGER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint >> b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, (unsigned long long)a->sint >> b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_uint_value(interp, a->uint >> b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_uint_value(interp, a->uint >> (unsigned long long)b->sint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_bit_shr_assign(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "&ii", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        a->sint >>= b->sint;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        a->sint >>= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        a->uint >>= b->uint;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        a->uint >>= b->sint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_copy(interp, a);

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_equ(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_a;
    }

    *result = julie_sint_value(interp, julie_equal(a, b));

    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_neq(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "**", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    *result = julie_sint_value(interp, !julie_equal(a, b));

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_lss(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint < b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, (unsigned long long)a->sint < b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->sint < b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->uint < b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->uint < (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->uint < b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, a->floating < b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->floating < (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->floating < (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    julie_free_value(interp, b);
out_free_a:;
    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_leq(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint <= b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, (unsigned long long)a->sint <= b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->sint <= b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->uint <= b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->uint <= (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->uint <= b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, a->floating <= b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->floating <= (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->floating <= (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_gtr(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint > b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, (unsigned long long)a->sint > b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->sint > b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->uint > b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->uint > (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->uint > b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, a->floating > b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->floating > (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->floating > (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_geq(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    status = julie_args(interp, expr, "nn", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->sint >= b->sint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, (unsigned long long)a->sint >= b->uint);
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->sint >= b->floating);
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->uint >= b->uint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->uint >= (unsigned long long)b->sint);
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, (double)a->uint >= b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, a->floating >= b->floating);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = julie_sint_value(interp, a->floating >= (double)b->sint);
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = julie_sint_value(interp, a->floating >= (double)b->uint);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_not(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;

    status = julie_args(interp, expr, "n", n_values, values, &a);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (a->type == JULIE_SINT) {
        *result = julie_sint_value(interp, !(a->sint));
    } else if (a->type == JULIE_UINT) {
        *result = julie_sint_value(interp, !(a->uint));
    } else if (a->type == JULIE_FLOAT) {
        *result = julie_sint_value(interp, !(a->floating));
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    julie_free_value(interp, a);

out:;
    return status;
}

static Julie_Status julie_builtin_and(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    int           short_circuit;
    unsigned      i;
    Julie_Value  *cond;
    Julie_Value  *ev;

    status = JULIE_SUCCESS;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    short_circuit = 0;

    for (i = 0; i < n_values; i += 1) {
        cond   = values[i];
        status = julie_eval(interp, cond, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }

        if (!JULIE_TYPE_IS_NUMBER(ev->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, ev, _JULIE_NUMBER, ev->type);
            julie_free_value(interp, ev);
            *result = NULL;
            goto out;
        }

        if (ev->type == JULIE_SINT) {
            short_circuit = ev->sint == 0;
        } else if (ev->type == JULIE_UINT) {
            short_circuit = ev->uint == 0;
        } else if (ev->type == JULIE_FLOAT) {
            short_circuit = ev->floating == 0;
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }

        julie_free_value(interp, ev);

        if (short_circuit) {
            *result = julie_sint_value(interp, 0);
            goto out;
        }
    }

    *result = julie_sint_value(interp, 1);

out:;
    return status;
}

static Julie_Status julie_builtin_or(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    int          short_circuit;
    unsigned     i;
    Julie_Value  *cond;
    Julie_Value  *ev;

    status = JULIE_SUCCESS;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    short_circuit = 0;

    for (i = 0; i < n_values; i += 1) {
        cond = values[i];
        status = julie_eval(interp, cond, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }

        if (!JULIE_TYPE_IS_NUMBER(ev->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, ev, _JULIE_NUMBER, ev->type);
            julie_free_value(interp, ev);
            *result = NULL;
            goto out;
        }

        if (ev->type == JULIE_SINT) {
            short_circuit = ev->sint != 0;
        } else if (ev->type == JULIE_UINT) {
            short_circuit = ev->uint != 0;
        } else if (ev->type == JULIE_FLOAT) {
            short_circuit = ev->floating != 0;
        } else {
            JULIE_ASSERT(0 && "bad number type");
        }

        julie_free_value(interp, ev);

        if (short_circuit) {
            *result = julie_sint_value(interp, 1);
            goto out;
        }
    }

    *result = julie_sint_value(interp, 0);

out:;
    return status;
}

static Julie_Status julie_builtin_inc(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        *result = NULL;
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        julie_free_value(interp, a);
        goto out;
    }

    switch (a->type) {
        case JULIE_SINT:
            ++a->sint;
            break;
        case JULIE_UINT:
            ++a->uint;
            break;
        case JULIE_FLOAT:
            ++a->floating;
            break;
        default:
            JULIE_ASSERT(0 && "bad number type");
            break;
    }

    *result = a;

out:;
    return status;
}

static Julie_Status julie_builtin_dec(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;

    *result = NULL;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        *result = NULL;
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        julie_free_value(interp, a);
        goto out;
    }

    switch (a->type) {
        case JULIE_SINT:
            --a->sint;
            break;
        case JULIE_UINT:
            --a->uint;
            break;
        case JULIE_FLOAT:
            --a->floating;
            break;
        default:
            JULIE_ASSERT(0 && "bad number type");
            break;
    }

    *result = a;

out:;
    return status;
}

static Julie_Status julie_builtin_max(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = a->sint >= b->sint ? a : b;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = (unsigned long long)a->sint >= b->uint ? a : b;
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = (double)a->sint >= b->floating ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = a->uint >= b->uint ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = a->uint >= (unsigned long long)b->sint ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = (double)a->uint >= b->floating ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = a->floating >= b->floating ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = a->floating >= (double)b->sint ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = a->floating >= (double)b->uint ? a : b;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    if (*result != b) {
        julie_free_value(interp, b);
    }
out_free_a:;
    if (*result != a) {
        julie_free_value(interp, a);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_min(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *a;
    Julie_Value  *b;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &a);
    if (status != JULIE_SUCCESS) { goto out; }

    status = julie_eval(interp, values[1], &b);
    if (status != JULIE_SUCCESS) { goto out_free_a; }

    if (!JULIE_TYPE_IS_NUMBER(a->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_NUMBER, a->type);
        goto out_free_ab;
    }

    if (!JULIE_TYPE_IS_NUMBER(b->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_NUMBER, b->type);
        goto out_free_ab;
    }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        *result = a->sint < b->sint ? a : b;
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        *result = (unsigned long long)a->sint < b->uint ? a : b;
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        *result = (double)a->sint < b->floating ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        *result = a->uint < b->uint ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        *result = a->uint < (unsigned long long)b->sint ? a : b;
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        *result = (double)a->uint < b->floating ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        *result = a->floating < b->floating ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        *result = a->floating < (double)b->sint ? a : b;
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        *result = a->floating < (double)b->uint ? a : b;
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

out_free_ab:;
    if (*result != b) {
        julie_free_value(interp, b);
    }
out_free_a:;
    if (*result != a) {
        julie_free_value(interp, a);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_list(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *list;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *ev;
    Julie_Value  *tmp;

    (void)expr;

    status = JULIE_SUCCESS;

    list = julie_list_value(interp);
    JULIE_ARRAY_RESERVE(list->list, n_values);

    for (i = 0; i < n_values; i += 1) {
        it     = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free;
        }

        if (ev->owned || ev->source_node) {
            tmp = julie_force_copy(interp, ev);
            julie_free_value(interp, ev);
            ev = tmp;
        }

        JULIE_ARRAY_PUSH(list->list, ev);
    }

    *result = list;
    goto out;

out_free:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status _julie_builtin_elem(Julie_Interp *interp, Julie_Value *expr, Julie_Value *list, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *idx;
    unsigned long long  i;
    Julie_Value        *val;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    JULIE_ASSERT(list->type == JULIE_LIST);

    status = julie_eval(interp, values[0], &idx);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_INTEGER(idx->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], _JULIE_INTEGER, idx->type);
        goto out_free_idx;
    }

    if (idx->type == JULIE_SINT) {
        i = idx->sint;
    } else if (idx->type == JULIE_UINT) {
        i = idx->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        i = 0;
    }

    if (i >= julie_array_len(list->list)) {
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, values[0], idx);
        *result = NULL;
        goto out_free_idx;
    }

    val = julie_array_elem(list->list, i);
    val->owned = list->owned;

    *result = julie_copy(interp, val);

out_free_idx:;
    julie_free_value(interp, idx);

out:;
    return status;

}

static Julie_Status julie_builtin_elem(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *list;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (list->type != JULIE_LIST) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_LIST, list->type);
        goto out_free_list;
    }

    status = _julie_builtin_elem(interp, expr, list, n_values - 1, values + 1, result);

out_free_list:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_last(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *list;
    Julie_Value  *it;
    Julie_Value  *last;
    Julie_Value  *neg_one;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (list->type != JULIE_LIST) {
        *result = NULL;
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_LIST, list->type);
        goto out_free;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == list) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, values[0]->type == JULIE_SYMBOL ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    if (julie_array_len(list->list) <= 0) {
        *result = NULL;
        status = JULIE_ERR_BAD_INDEX;
        neg_one = julie_sint_value(interp, -1);
        julie_make_bad_index_error(interp, expr, neg_one);
        julie_free_value(interp, neg_one);
        goto out_free;
    }

    last = julie_array_top(list->list);
    last->owned = list->owned;

    *result = julie_copy(interp, last);

out_free:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_index(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *list;
    Julie_Value        *val;
    unsigned long long  i;
    Julie_Value        *it;

    status = julie_args(interp, expr, "l*", n_values, values, &list, &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    i = 0;
    ARRAY_FOR_EACH(list->list, it) {
        if (julie_equal(val, it)) {
            *result = julie_sint_value(interp, i);
            break;
        }
        i += 1;
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

    julie_free_value(interp, val);
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_append(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status   status;
    Julie_Value   *list;
    Julie_Value   *val;
    Julie_Value   *cpy;
    Julie_Value   *it;

    *result = NULL;

    status = JULIE_SUCCESS;

    if (n_values != 2) {
        *result = NULL;
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (list->type != JULIE_LIST) {
        *result = NULL;
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_LIST, list->type);
        goto out_free_list;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == list) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, values[0]->type == JULIE_SYMBOL ? values[0]->string_id : NULL);
            goto out_free_list;
        }
    }

    status = julie_eval(interp, values[1], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_list;
    }

    if (val->owned || val->source_node) {
        cpy = julie_force_copy(interp, val);
        julie_free_value(interp, val);
        val = cpy;
    }

    JULIE_ASSERT(!val->owned);

    JULIE_ARRAY_PUSH(list->list, val);

    *result = julie_nil_value(interp);

out_free_list:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_insert(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *list;
    Julie_Value        *val;
    Julie_Value        *idx;
    Julie_Value        *cpy;
    Julie_Value        *it;
    unsigned long long  i;

    status = julie_args(interp, expr, "l*i", n_values, values, &list, &val, &idx);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == list) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, values[0]->type == JULIE_SYMBOL ? values[0]->string_id : NULL);
            julie_free_value(interp, val);
            goto out_free;
        }
    }

    if (val->owned || val->source_node) {
        cpy = julie_force_copy(interp, val);
        julie_free_value(interp, val);
        val = cpy;
    }

    if (idx->type == JULIE_SINT) {
        i = idx->sint;
    } else if (idx->type == JULIE_UINT) {
        i = idx->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        i = 0;
    }

    if (i > julie_array_len(list->list)) {
        *result = NULL;
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, idx, idx);
        julie_free_value(interp, val);
        goto out_free;
    }

    JULIE_ASSERT(!val->owned);

    JULIE_ARRAY_INSERT(list->list, val, i);

    *result = julie_nil_value(interp);

out_free:;
    julie_free_value(interp, list);
    julie_free_value(interp, idx);

out:;
    return status;
}

static Julie_Status julie_builtin_pop(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *list;
    Julie_Value  *it;
    Julie_Value  *last;
    Julie_Value  *neg_one;

    status = julie_args(interp, expr, "l", n_values, values, &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == list) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, values[0]->type == JULIE_SYMBOL ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    if (julie_array_len(list->list) <= 0) {
        *result = NULL;
        status = JULIE_ERR_BAD_INDEX;
        neg_one = julie_sint_value(interp, -1);
        julie_make_bad_index_error(interp, expr, neg_one);
        julie_free_value(interp, neg_one);
        goto out_free;
    }

    last = julie_array_top(list->list);

    if (julie_borrows_to_subvalues_outstanding(list, last)) {
        *result = NULL;
        julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        goto out_free;
    }

    *result = julie_array_pop(list->list);
    (*result)->owned = 0;

out_free:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_erase(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *list;
    Julie_Value        *idx;
    Julie_Value        *it;
    unsigned long long  i;
    Julie_Value        *val;

    status = julie_args(interp, expr, "li", n_values, values, &list, &idx);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == list) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, values[0]->type == JULIE_SYMBOL ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    i = idx->type == JULIE_SINT ? (unsigned long long)idx->sint : idx->uint;

    if (i >= julie_array_len(list->list)) {
        *result = NULL;
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, idx, julie_copy(interp, idx));
        goto out_free;
    }

    julie_free_value(interp, idx);

    val = julie_array_elem(list->list, i);

    if (julie_borrows_to_subvalues_outstanding(list, val)) {
        *result = NULL;
        julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        goto out_free;
    }

    val->owned = 0;

    julie_array_erase(list->list, i);
    julie_free_value(interp, val);

    *result = julie_nil_value(interp);

out_free:;
    julie_free_value(interp, list);
    julie_free_value(interp, idx);

out:;
    return status;
}

typedef struct {
    Julie_Interp *interp;
    Julie_Value  *fn;
    Julie_Value  *fn_expr;
    Julie_Status  status;
} _Julie_Sort_Arg;

static int julie_sort_value_num_cmp(const void *_a, const void *_b, void *_arg) {
    int                r;
    const Julie_Value *a;
    const Julie_Value *b;

    (void)_arg;

    r   = 0;
    a   = *(const Julie_Value**)_a;
    b   = *(const Julie_Value**)_b;

    if (a->type == JULIE_NIL) { return -1; }
    if (b->type == JULIE_NIL) { return  1; }

    if (a->type == JULIE_SINT && b->type == JULIE_SINT) {
        if      (a->sint == b->sint) { r =  0; }
        else if (a->sint <  b->sint) { r = -1; }
        else                         { r =  1; }
    } else if (a->type == JULIE_SINT && b->type == JULIE_UINT) {
        if      ((unsigned long long)a->sint == b->uint) { r =  0; }
        else if ((unsigned long long)a->sint <  b->uint) { r = -1; }
        else                                             { r =  1; }
    } else if (a->type == JULIE_SINT && b->type == JULIE_FLOAT) {
        if      (a->sint == b->floating) { r =  0; }
        else if (a->sint <  b->floating) { r = -1; }
        else                             { r =  1; }
    } else if (a->type == JULIE_UINT && b->type == JULIE_UINT) {
        if      (a->uint == b->uint)  { r =  0; }
        else if (a->uint <  b->uint)  { r = -1; }
        else                          { r =  1; }
    } else if (a->type == JULIE_UINT && b->type == JULIE_SINT) {
        if      (a->uint == (unsigned long long)b->sint) { r =  0; }
        else if (a->uint <  (unsigned long long)b->sint) { r = -1; }
        else                                             { r =  1; }
    } else if (a->type == JULIE_UINT && b->type == JULIE_FLOAT) {
        if      (a->uint == b->floating) { r =  0; }
        else if (a->uint <  b->floating) { r = -1; }
        else                             { r =  1; }
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_FLOAT) {
        if      (a->floating == b->floating) { r =  0; }
        else if (a->floating <  b->floating) { r = -1; }
        else                                 { r =  1; }
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_SINT) {
        if      (a->floating == b->sint) { r =  0; }
        else if (a->floating <  b->sint) { r = -1; }
        else                             { r =  1; }
    } else if (a->type == JULIE_FLOAT && b->type == JULIE_UINT) {
        if      (a->floating == b->uint) { r =  0; }
        else if (a->floating <  b->uint) { r = -1; }
        else                             { r =  1; }
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    return r;
}

static int julie_sort_value_str_cmp(const void *_a, const void *_b, void *_arg) {
    int               r;
    const Julie_Value *a;
    const Julie_Value *b;
    _Julie_Sort_Arg   *arg;
    char             *ac;
    char             *bc;
    const char       *as;
    const char       *bs;

    r   = 0;
    a   = *(const Julie_Value**)_a;
    b   = *(const Julie_Value**)_b;
    arg = _arg;

    if (a->type == JULIE_NIL) { return -1; }
    if (b->type == JULIE_NIL) { return  1; }

    ac = bc = NULL;
    if (a->type == JULIE_STRING || a->type == JULIE_SYMBOL) {
        as = julie_value_cstring(a);
    } else {
        as = ac = julie_to_string(arg->interp, a, JULIE_NO_QUOTE);
    }

    if (b->type == JULIE_STRING || b->type == JULIE_SYMBOL) {
        bs = julie_value_cstring(b);
    } else {
        bs = bc = julie_to_string(arg->interp, b, JULIE_NO_QUOTE);
    }

    r = strcmp(as, bs);

    if (ac != NULL) { free(ac); }
    if (bc != NULL) { free(bc); }

    return r;
}

static int julie_sort_value_fn_cmp(const void *_a, const void *_b, void *_arg) {
    int                r;
    const Julie_Value *a;
    const Julie_Value *b;
    _Julie_Sort_Arg   *arg;
    Julie_Value       *quote_fn;
    Julie_Value       *values[2];
    Julie_Status       status;
    Julie_Value       *result;

    r   = 0;
    a   = *(const Julie_Value**)_a;
    b   = *(const Julie_Value**)_b;
    arg = _arg;

    if (arg->status != JULIE_SUCCESS) { goto out; }

    quote_fn = julie_builtin_fn_value(arg->interp, julie_builtin_quote);

    ((Julie_Value*)a)->owned = 1;
    ((Julie_Value*)b)->owned = 1;

    values[0] = julie_list_value(arg->interp);
    JULIE_ARRAY_PUSH(values[0]->list, quote_fn);
    JULIE_ARRAY_PUSH(values[0]->list, (Julie_Value*)a);

    values[1] = julie_list_value(arg->interp);
    JULIE_ARRAY_PUSH(values[1]->list, quote_fn);
    JULIE_ARRAY_PUSH(values[1]->list, (Julie_Value*)b);

    status = julie_invoke(arg->interp, arg->fn_expr, arg->fn, 2, values, &result);

    julie_free_value(arg->interp, quote_fn);
    julie_array_free(values[0]->list);
    values[0]->list = JULIE_ARRAY_INIT;
    julie_array_free(values[1]->list);
    values[1]->list = JULIE_ARRAY_INIT;
    julie_free_value(arg->interp, values[0]);
    julie_free_value(arg->interp, values[1]);


    if (status == JULIE_SUCCESS) {
        if (!JULIE_TYPE_IS_INTEGER(result->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(arg->interp, arg->fn_expr, _JULIE_INTEGER, result->type);
            goto err;
        }

        if (result->type == JULIE_SINT) {
            r = (int)result->sint ? -1 : 1;
        } else if (result->type == JULIE_UINT) {
            r = (int)result->uint ? -1 : 1;
        } else {
            JULIE_ASSERT(0);
        }

        julie_free_value(arg->interp, result);
    } else {
err:;
        arg->status = status;
    }

out:;
    return r;
}

static Julie_Status julie_builtin_sorted(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status     status;
    Julie_Value     *sorted;
    Julie_Value     *fn;
    Julie_Type       sort_type;
    Julie_Value     *it;
    _Julie_Sort_Arg  sort_arg;

    if (n_values < 1 || n_values > 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &sorted);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (sorted->type != JULIE_LIST) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_LIST, sorted->type);
        julie_free_value(interp, sorted);
        goto out;
    }

    if (n_values == 2) {
        status = julie_eval(interp, values[1], &fn);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            julie_free_value(interp, sorted);
            goto out;
        }
    } else {
        fn = NULL;
    }

    if (sorted->owned || sorted->source_node) {
        sorted = julie_force_copy(interp, sorted);
    }

    if (julie_array_len(sorted->list) > 0) {
        if (fn == NULL) {
            sort_type = JULIE_UNKNOWN;

            ARRAY_FOR_EACH(sorted->list, it) {
                if (JULIE_TYPE_IS_KEYLIKE(it->type)) {
                    if (it->type == JULIE_STRING) {
                        sort_type = JULIE_STRING;
                    } else if (sort_type != JULIE_STRING) {
                        sort_type = _JULIE_NUMBER;
                    }
                } else {
                    status = JULIE_ERR_TYPE;
                    julie_make_type_error(interp, values[0], _JULIE_KEYLIKE, it->type);
                    *result = NULL;
                    julie_free_value(interp, sorted);
                    goto out_free_fn_list;
                }
            }

            JULIE_ASSERT(sort_type);

            sort_arg.interp  = interp;
            sort_arg.fn      = NULL;
            sort_arg.fn_expr = NULL;
            sort_arg.status  = JULIE_SUCCESS;

            if (sort_type == _JULIE_NUMBER) {
                sort_r(sorted->list->data, julie_array_len(sorted->list), sizeof(*(sorted->list->data)), julie_sort_value_num_cmp, &sort_arg);
            } else if (sort_type == JULIE_STRING) {
                sort_r(sorted->list->data, julie_array_len(sorted->list), sizeof(*(sorted->list->data)), julie_sort_value_str_cmp, &sort_arg);
            }
        } else {
            sort_arg.interp  = interp;
            sort_arg.fn      = fn;
            sort_arg.fn_expr = values[1];
            sort_arg.status  = JULIE_SUCCESS;
            sort_r(sorted->list->data, julie_array_len(sorted->list), sizeof(*(sorted->list->data)), julie_sort_value_fn_cmp, &sort_arg);

            if (sort_arg.status != JULIE_SUCCESS) {
                *result = NULL;
                julie_free_value(interp, sorted);
                goto out_free_fn_list;
            }
        }
    }

    *result = sorted;

out_free_fn_list:;
    if (fn != NULL) {
        julie_free_value(interp, fn);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_sorted_insert(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status         status;
    Julie_Value         *list;
    Julie_Value         *val;
    Julie_Value         *cpy;
    Julie_Value         *fn;
    int                (*cmp)(const void*, const void*, void*);
    Julie_Type           sort_type;
    Julie_Value         *it;
    _Julie_Sort_Arg      sort_arg;
    Julie_Value         *elem;
    int                  c;
    unsigned long long   low;
    unsigned long long   high;
    unsigned long long   mid;

    if (n_values < 2 || n_values > 3) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (list->type != JULIE_LIST) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_LIST, list->type);
        goto out_free_list;
    }

    status = julie_eval(interp, values[1], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_list;
    }

    if (val->owned || val->source_node) {
        cpy = julie_force_copy(interp, val);
        julie_free_value(interp, val);
        val = cpy;
    }

    if (n_values == 3) {
        status = julie_eval(interp, values[2], &fn);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            julie_free_value(interp, val);
            goto out_free_list;
        }
    } else {
        fn = NULL;
    }

    if (julie_array_len(list->list) == 0) {
        JULIE_ARRAY_PUSH(list->list, val);
        goto out_result;
    }

    cmp = NULL;

    if (fn == NULL) {
        sort_type = JULIE_UNKNOWN;

        ARRAY_FOR_EACH(list->list, it) {
            if (JULIE_TYPE_IS_KEYLIKE(it->type)) {
                if (it->type == JULIE_STRING) {
                    sort_type = JULIE_STRING;
                } else if (sort_type != JULIE_STRING) {
                    sort_type = _JULIE_NUMBER;
                }
            } else {
                status = JULIE_ERR_TYPE;
                julie_make_type_error(interp, values[0], _JULIE_KEYLIKE, it->type);
                *result = NULL;
                julie_free_value(interp, val);
                goto out_free_fn_list;
            }
        }

        JULIE_ASSERT(sort_type);

        sort_arg.interp  = interp;
        sort_arg.fn      = NULL;
        sort_arg.fn_expr = NULL;
        sort_arg.status  = JULIE_SUCCESS;

        if (sort_type == _JULIE_NUMBER) {
            cmp = julie_sort_value_num_cmp;
        } else if (sort_type == JULIE_STRING) {
            cmp = julie_sort_value_str_cmp;
        }
    } else {
        sort_arg.interp  = interp;
        sort_arg.fn      = fn;
        sort_arg.fn_expr = values[1];
        sort_arg.status  = JULIE_SUCCESS;

        cmp = julie_sort_value_fn_cmp;
    }

    elem = julie_array_elem(list->list, julie_array_len(list->list) - 1);

    c = cmp(&elem, &val, &sort_arg);
    if (sort_arg.status != JULIE_SUCCESS) {
        *result = NULL;
        julie_free_value(interp, val);
        goto out_free_fn_list;
    }

    if (c > 0) {
        JULIE_ARRAY_PUSH(list->list, val);
    } else {
        low = 0;
        high = julie_array_len(list->list);

        while (low < high) {
            mid = (low + high) / 2;

            elem = julie_array_elem(list->list, mid);

            c = cmp(&elem, &val, &sort_arg);
            if (sort_arg.status != JULIE_SUCCESS) {
                *result = NULL;
                julie_free_value(interp, val);
                goto out_free_fn_list;
            }

            if (c < 0) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        JULIE_ARRAY_INSERT(list->list, val, low);
    }

out_result:;
    *result = julie_nil_value(interp);

out_free_fn_list:;
    if (fn != NULL) {
        julie_free_value(interp, fn);
    }

out_free_list:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_apply(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *list;

    status = julie_args(interp, expr, "l", n_values, values, &list);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, list, result);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free;
    }

out_free:;
    julie_free_value(interp, list);

out:;
    return status;
}

static Julie_Status julie_builtin_pair(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *first;
    Julie_Value  *second;
    Julie_Value  *cpy;
    Julie_Value  *list;

    *result = NULL;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &first);
    if (status != JULIE_SUCCESS) {
        goto out;
    }

    status = julie_eval(interp, values[1], &second);
    if (status != JULIE_SUCCESS) {
        julie_free_value(interp, first);
        goto out;
    }

    if (first->owned || first->source_node) {
        cpy = julie_force_copy(interp, first);
        julie_free_value(interp, first);
        first = cpy;
    }

    if (second->owned || second->source_node) {
        cpy = julie_force_copy(interp, second);
        julie_free_value(interp, second);
        second = cpy;
    }

    list = julie_list_value(interp);

    JULIE_ARRAY_PUSH(list->list, first);
    JULIE_ARRAY_PUSH(list->list, second);

    *result = list;

out:;
    return status;
}

static Julie_Status julie_builtin_object(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *object;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *sym;
    unsigned      key_idx;
    unsigned      val_idx;
    Julie_Value  *key;
    Julie_Value  *val;
    Julie_Value  *ev;

    (void)expr;

    status = JULIE_SUCCESS;

    object = julie_object_value(interp);

    for (i = 0; i < n_values; i += 1) {
        it = values[i];

        /* Agressive optimization of common case -- skip all copies created to construct the pair. */
        if (it->type == JULIE_LIST
        &&  julie_array_len(it->list) == 3) {

            sym = julie_array_elem(it->list, 1);
            if (sym->type != JULIE_SYMBOL) { goto check_for_rewritten; }

            sym = julie_lookup(interp, sym->string_id);
            if (sym == NULL
            ||  sym->type != JULIE_BUILTIN_FN
            ||  sym->builtin_fn != julie_builtin_pair) {

check_for_rewritten:;
                if (!it->source_node) { goto slow_path; }

                /* Most likely rewritten to be prefix. */

                sym = julie_array_elem(it->list, 0);
                if (sym->type != JULIE_SYMBOL) { goto slow_path; }

                sym = julie_lookup(interp, sym->string_id);
                if (sym == NULL
                ||  sym->type != JULIE_BUILTIN_FN
                ||  sym->builtin_fn != julie_builtin_pair) {

                    goto slow_path;
                }

                key_idx = 1;
                val_idx = 2;
            } else {
                key_idx = 0;
                val_idx = 2;
            }


            status = julie_eval(interp, julie_array_elem(it->list, key_idx), &key);
            if (status != JULIE_SUCCESS) {
                goto out_free_object;
            }

            if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
                status = JULIE_ERR_TYPE;
                julie_make_type_error(interp, julie_array_elem(it->list, key_idx), _JULIE_KEYLIKE, key->type);
                *result = NULL;
                goto out_free_object;
            }

            status = julie_eval(interp, julie_array_elem(it->list, val_idx), &val);
            if (status != JULIE_SUCCESS) {
                julie_free_value(interp, key);
                goto out_free_object;
            }

            /* We are allowed to ellide copy of a source_node since object keys are read-only. */
            if (key->owned) {
                key = julie_force_copy(interp, key);
            }
            if (val->owned || val->source_node) {
                val = julie_force_copy(interp, val);
            }

            status = julie_object_insert_field(interp, object, key, val, NULL);
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
                    julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
                } else {
                    julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
                }
                julie_free_value(interp, key);
                julie_free_value(interp, val);
                goto out_free_object;
            }

            continue;
        }

slow_path:;
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free_object;
        }

        if (ev->type != JULIE_LIST) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, ev, JULIE_LIST, ev->type);
            *result = NULL;
            goto out_free_list;
        }

        if (julie_array_len(ev->list) != 2) {
            status = JULIE_ERR_NOT_PAIR;
            julie_make_interp_error(interp, it, status);
            *result = NULL;
            goto out_free_list;
        }

        key = julie_array_elem(ev->list, 0);
        val = julie_array_elem(ev->list, 1);

        if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, key, _JULIE_KEYLIKE, key->type);
            *result = NULL;
            goto out_free_list;
        }

        if (!ev->owned && !key->source_node && !val->source_node) {
            julie_array_free(ev->list);
            ev->list = JULIE_ARRAY_INIT;
        } else {
            key = julie_force_copy(interp, key);
            val = julie_force_copy(interp, val);
        }

        status = julie_object_insert_field(interp, object, key, val, NULL);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
                julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
            } else {
                julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
            }
            julie_free_value(interp, key);
            julie_free_value(interp, val);
            goto out_free_list;
        }

        julie_free_value(interp, ev);
    }

    *result = object;
    goto out;

out_free_list:;
    julie_free_value(interp, ev);

out_free_object:;
    julie_free_value(interp, object);

out:;
    return status;
}

static Julie_Status _julie_builtin_field(Julie_Interp *interp, Julie_Value *expr, Julie_Value *object, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *key;
    Julie_Value  *field;

    status = JULIE_SUCCESS;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        *result = NULL;
        goto out;
    }

    JULIE_ASSERT(object->type == JULIE_OBJECT);

    status = julie_eval(interp, values[0], &key);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, key, _JULIE_KEYLIKE, key->type);
        *result = NULL;
        goto out_free_key;
    }

    field = julie_object_get_field(object, key);

    if (field == NULL) {
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, key, key);
        *result = NULL;
        goto out_free_key;
    } else {
        field->owned = object->owned;
        *result = julie_copy(interp, field);
    }

out_free_key:;
    julie_free_value(interp, key);

out:;
    return status;
}

static Julie_Status julie_builtin_field(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *object;

    status = JULIE_SUCCESS;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &object);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (object->type != JULIE_OBJECT) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_OBJECT, object->type);
        *result = NULL;
        goto out_free_object;
    }

    status = _julie_builtin_field(interp, expr, object, n_values - 1, values + 1, result);

out_free_object:;
    julie_free_value(interp, object);

out:;
    return status;
}

static Julie_Status julie_builtin_delete(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *object;
    Julie_Value  *key;
    Julie_Value  *it;

    status = julie_args(interp, expr, "ok", n_values, values, &object, &key);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == object) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, (values[0]->type == JULIE_SYMBOL && values[0]->tag == JULIE_STRING_TYPE_INTERN) ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    status = julie_object_delete_field(interp, object, key);

    if (status == JULIE_ERR_BAD_INDEX) {
        *result = NULL;
        julie_make_bad_index_error(interp, key, key);
        goto out_free;
    } else if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
        *result = NULL;
        julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        goto out_free;
    } else if (status != JULIE_SUCCESS) {
        JULIE_ASSERT(0);
    }

    *result = julie_nil_value(interp);

out_free:;
    julie_free_value(interp, object);
    julie_free_value(interp, key);

out:;
    return status;
}

static Julie_Status julie_builtin_update_object(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status   status;
    Julie_Value   *o1;
    Julie_Value   *o2;
    Julie_Value   *it;
    Julie_Value   *key;
    Julie_Value   *val;
    Julie_Value  **valp;

    status = julie_args(interp, expr, "o#", n_values, values, &o1, &o2);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == o1) {
            *result = NULL;
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            julie_make_bind_error(interp, expr, status, (values[0]->type == JULIE_SYMBOL && values[0]->tag == JULIE_STRING_TYPE_INTERN) ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    if (o2->type == JULIE_LIST) {
        if (julie_array_len(o2->list) != 2) {
            *result = NULL;
            status = JULIE_ERR_NOT_PAIR;
            julie_make_interp_error(interp, it, status);
            goto out_free;
        }

        key = julie_array_elem(o2->list, 0);
        val = julie_array_elem(o2->list, 1);

        if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
            *result = NULL;
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, key, _JULIE_KEYLIKE, key->type);
            goto out_free;
        }

        if (!o2->owned && !key->source_node && !val->source_node) {
            julie_array_free(o2->list);
            o2->list = JULIE_ARRAY_INIT;
        } else {
            key = julie_force_copy(interp, key);
            val = julie_force_copy(interp, val);
        }

        if ((status = julie_object_insert_field(interp, o1, key, val, NULL)) != JULIE_SUCCESS) {
            *result = NULL;
            if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
                julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
            } else {
                julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
            }
            julie_free_value(interp, key);
            julie_free_value(interp, val);
            goto out_free;
        }
    } else if (o2->type == JULIE_OBJECT) {
        hash_table_traverse((_Julie_Object)o2->object, key, valp) {
            key = julie_force_copy(interp, key);
            val = julie_force_copy(interp, *valp);
            if ((status = julie_object_insert_field(interp, o1, key, val, NULL)) != JULIE_SUCCESS) {
                *result = NULL;
                if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
                    julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
                } else {
                    julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
                }
                julie_free_value(interp, key);
                julie_free_value(interp, val);
                goto out_free;
            }
        }
    }

    *result = julie_nil_value(interp);

out_free:;
    julie_free_value(interp, o1);
    julie_free_value(interp, o2);

out:;
    return status;
}

static Julie_Status julie_builtin_get_or_insert_field(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *o;
    Julie_Value  *key;
    Julie_Value  *val;
    Julie_Value  *it;
    Julie_Value  *lookup;

    *result = NULL;

    status = JULIE_SUCCESS;

    if (n_values != 3) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 3, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &o);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    ARRAY_FOR_EACH(interp->iter_vals, it) {
        if (it == o) {
            status  = JULIE_ERR_MODIFY_WHILE_ITER;
            *result = NULL;
            julie_make_bind_error(interp, expr, status, (values[0]->type == JULIE_SYMBOL && values[0]->tag == JULIE_STRING_TYPE_INTERN) ? values[0]->string_id : NULL);
            goto out_free;
        }
    }

    status = julie_eval(interp, values[1], &key);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free;
    }

    if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], _JULIE_KEYLIKE, key->type);
        julie_free_value(interp, key);
        goto out_free;
    }

    lookup = julie_object_get_field(o, key);

    if (lookup != NULL) {
        *result = julie_copy(interp, lookup);
        (*result)->owned = o->owned;
        goto out_free;
    }


    status = julie_eval(interp, values[2], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        julie_free_value(interp, key);
        goto out_free;
    }

    if (key->owned) {
        key = julie_force_copy(interp, key);
    }
    if (val->owned || val->source_node) {
        val = julie_force_copy(interp, val);
    }

    if ((status = julie_object_insert_field_skip_lookup(interp, o, key, val, result)) != JULIE_SUCCESS) {
        *result = NULL;
        if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
            julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        } else {
            julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
        }
        julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
        julie_free_value(interp, key);
        julie_free_value(interp, val);
        goto out_free;
    }

    (*result)->owned = o->owned;

out_free:;
    julie_free_value(interp, o);

out:;
    return status;
}

static Julie_Status julie_builtin_keys(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status   status;
    Julie_Value   *object;
    Julie_Value   *list;
    Julie_Value   *key;
    Julie_Value  **val;

    status = julie_args(interp, expr, "o", n_values, values, &object);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    list = julie_list_value(interp);
    JULIE_ARRAY_RESERVE(list->list, hash_table_len((_Julie_Object)object->object));
    hash_table_traverse((_Julie_Object)object->object, key, val) {
        (void)val;
        JULIE_ARRAY_PUSH(list->list, julie_force_copy(interp, key));
    }

    julie_free_value(interp, object);

    *result = list;

out:;
    return status;
}

static Julie_Status julie_builtin_values(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status   status;
    Julie_Value   *object;
    Julie_Value   *list;
    Julie_Value   *key;
    Julie_Value  **val;

    status = julie_args(interp, expr, "o", n_values, values, &object);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    list = julie_list_value(interp);
    JULIE_ARRAY_RESERVE(list->list, hash_table_len((_Julie_Object)object->object));
    hash_table_traverse((_Julie_Object)object->object, key, val) {
        (void)key;
        JULIE_ARRAY_PUSH(list->list, julie_force_copy(interp, *val));
    }

    julie_free_value(interp, object);

    *result = list;

out:;
    return status;
}

static Julie_Status julie_builtin_define_class(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status     status;
    Julie_Value     *sym;
    Julie_String_ID  id;
    Julie_Value     *object;
    unsigned         i;
    Julie_Value     *it;
    Julie_Value     *ev;
    Julie_Value     *key;
    Julie_Value     *val;

    *result = NULL;

    status = JULIE_SUCCESS;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        goto out;
    }

    sym = values[0];

    if (sym->type != JULIE_SYMBOL) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_SYMBOL, sym->type);
        goto out;
    }

    id = julie_value_string_id(interp, sym);

    object = julie_object_value(interp);

    key = interp->__class___value;
    val = julie_force_copy(interp, sym);
    julie_object_insert_field(interp, object, key, val, NULL);

    for (i = 1; i < n_values; i += 1) {
        it     = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free_object;
        }

        if (ev->type != JULIE_LIST) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, ev, JULIE_LIST, ev->type);
            *result = NULL;
            goto out_free_list;
        }

        if (julie_array_len(ev->list) != 2) {
            status = JULIE_ERR_NOT_PAIR;
            julie_make_interp_error(interp, it, status);
            *result = NULL;
            goto out_free_list;
        }

        key = julie_array_elem(ev->list, 0);
        val = julie_array_elem(ev->list, 1);

        if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, key, _JULIE_KEYLIKE, key->type);
            *result = NULL;
            goto out_free_list;
        }

        if (!ev->owned && !key->source_node && !val->source_node) {
            julie_array_free(ev->list);
            ev->list = JULIE_ARRAY_INIT;
        } else {
            key = key->source_node ? key : julie_force_copy(interp, key);
            val = julie_force_copy(interp, val);
        }

        status = julie_object_insert_field(interp, object, key, val, NULL);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            if (status == JULIE_ERR_RELEASE_WHILE_BORROWED) {
                julie_make_bind_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED, NULL);
            } else {
                julie_make_interp_error(interp, expr, JULIE_ERR_RELEASE_WHILE_BORROWED);
            }
            julie_free_value(interp, key);
            julie_free_value(interp, val);
            goto out_free_list;
        }

        julie_free_value(interp, ev);
    }

    if (interp->local_symtab_depth == 0) {
        status = julie_bind(interp, id, &object);
    } else {
        status = julie_bind_local(interp, id, &object);
    }

    if (status != JULIE_SUCCESS) {
        julie_make_bind_error(interp, expr, status, id);
        goto out_free_object;
    }

    *result = object;
    goto out;

out_free_list:;
    julie_free_value(interp, ev);

out_free_object:;
    julie_free_value(interp, object);

out:;
    return status;
}

static Julie_Status julie_builtin_new_instance(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status     status;
    Julie_Value     *class;
    Julie_Value     *object;
    Julie_Value     *key;
    Julie_Value    **valp;
    Julie_Value     *val;

    *result = NULL;

    status = JULIE_SUCCESS;

    if (n_values != 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &class);

    if (status != JULIE_SUCCESS) {
        goto out;
    }

    if (class->type != JULIE_OBJECT) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_OBJECT, class->type);
        goto out;
    }

    object = julie_object_value(interp);

    hash_table_traverse((_Julie_Object)class->object, key, valp) {
        val = *valp;

        if (val->type == JULIE_FN || val->type == JULIE_LAMBDA || val->type == JULIE_BUILTIN_FN) {
            continue;
        }

        key = key->source_node ? key : julie_force_copy(interp, key);
        val = julie_force_copy(interp, val);

        julie_object_insert_field(interp, object, key, val, NULL);
    }

    *result = object;

out:;
    return status;
}

static Julie_Status julie_builtin_method_call(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status         status;
    Julie_Value         *instance;
    Julie_Value         *list;
    Julie_Value         *fn_sym;
    Julie_Value         *class_sym;
    char                *s;
    Julie_String_ID      id;
    Julie_Value         *class;
    Julie_Value         *fn;
    Julie_Value        **args;
    unsigned long long   n_args;

    *result = NULL;

    status = JULIE_SUCCESS;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &instance);
    if (status != JULIE_SUCCESS) {
        goto out;
    }

    if (instance->type != JULIE_OBJECT) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_OBJECT, instance->type);
        goto out_free_instance;
    }

    list = values[1];

    if (list->type != JULIE_LIST) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], JULIE_LIST, list->type);
        goto out_free_instance;
    }

    if (julie_array_len(list->list) < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, values[1], 1, julie_array_len(list->list), 1);
        goto out_free_instance;
    }

    fn_sym = julie_array_elem(list->list, 0);

    class_sym = julie_object_get_field(instance, interp->__class___value);

    if (class_sym == NULL) {
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, values[0], interp->__class___value);
        goto out_free_instance;
    }

    if (class_sym->type != JULIE_SYMBOL) {
        s = julie_to_string(interp, class_sym, 0);
        id = julie_get_string_id(interp, s);
        free(s);
    } else {
        id = julie_value_string_id(interp, class_sym);
    }

    class = julie_lookup(interp, id);

    if (class == NULL) {
        status = JULIE_ERR_LOOKUP;
        julie_make_lookup_error(interp, values[0], id);
        goto out_free_instance;
    }

    if (class->type != JULIE_OBJECT) {
        goto not_found;
    }

    fn = julie_object_get_field(class, fn_sym);

    if (fn == NULL) {
not_found:;
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, fn_sym, fn_sym);
        goto out_free_instance;
    }

    args   = alloca(julie_array_len(list->list) * sizeof(Julie_Value*));
    n_args = julie_array_len(list->list);

    memcpy(args + 1, (Julie_Value**)(list->list->data + 1), (n_args - 1) * sizeof(Julie_Value*));
    args[0] = instance;

    status = julie_invoke(interp, expr, fn, n_args, args, result);

    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_instance;
    }

out_free_instance:;
    julie_free_value(interp, instance);

out:;
    return status;
}

static Julie_Status julie_builtin_in(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    int           found;
    Julie_Value  *container;
    Julie_Value  *key;
    Julie_Value  *lookup;
    Julie_Value  *it;

    status = JULIE_SUCCESS;

    found = 0;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &key);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[1], &container);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_container;
    }

    if (container->type == JULIE_OBJECT) {
        if (!JULIE_TYPE_IS_KEYLIKE(key->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, key, _JULIE_KEYLIKE, key->type);
            *result = NULL;
            goto out_free_key;
        }

        lookup = julie_object_get_field(container, key);

        found = lookup != NULL;

    } else if (container->type == JULIE_LIST) {
        ARRAY_FOR_EACH(container->list, it) {
            if (julie_equal(key, it)) {
                found = 1;
                break;
            }
        }
    } else {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, container, _JULIE_LIST_OR_OBJECT, container->type);
        *result = NULL;
        goto out_free_key;
    }

    *result = julie_sint_value(interp, found);

out_free_key:;
    julie_free_value(interp, key);

out_free_container:;
    julie_free_value(interp, container);

out:;
    return status;
}

static Julie_Status julie_builtin_len(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *ev;
    const Julie_String *string;

    status = julie_args(interp, expr, "*", n_values, values, &ev);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    switch (ev->type) {
        case JULIE_NIL:
            *result = julie_sint_value(interp, 0);
            break;
        case JULIE_SINT:
        case JULIE_UINT:
            *result = julie_copy(interp, ev);
            break;
        case JULIE_FLOAT:
            *result = julie_sint_value(interp, (long long)ev->floating);
            break;
        case JULIE_STRING:
        case JULIE_SYMBOL:
            if (ev->tag == JULIE_STRING_TYPE_INTERN) {
                string  = julie_get_string(interp, ev->string_id);
                *result = julie_sint_value(interp, string->len);
            } else {
                *result = julie_sint_value(interp, strlen(julie_value_cstring(ev)));
            }
            break;
        case JULIE_LIST:
            *result = julie_sint_value(interp, julie_array_len(ev->list));
            break;
        case JULIE_OBJECT:
            *result = julie_sint_value(interp, hash_table_len((_Julie_Object)ev->object));
            break;
        case JULIE_FN:
            *result = julie_sint_value(interp, 0);
            break;
        default:
            JULIE_ASSERT(0);
            break;
    }

    julie_free_value(interp, ev);

out:;
    return status;
}

static Julie_Status julie_builtin_empty(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *ev;

    status = julie_args(interp, expr, "#", n_values, values, &ev);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (ev->type == JULIE_LIST) {
        *result = julie_sint_value(interp, julie_array_len(ev->list) == 0);
    } else if (ev->type == JULIE_OBJECT) {
        *result = julie_sint_value(interp, hash_table_len((_Julie_Object)ev->object) == 0);
    }

    julie_free_value(interp, ev);

out:;
    return status;
}

static Julie_Status julie_builtin_select(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *cond;
    unsigned      truth;
    Julie_Value  *then;

    status = JULIE_SUCCESS;

    if (n_values != 3) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 3, n_values, 0);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &cond);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_NUMBER(cond->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, cond, _JULIE_NUMBER, cond->type);
        goto out_free_cond;
    }

    if (cond->type == JULIE_SINT) {
        truth = !!cond->sint;
    } else if (cond->type == JULIE_UINT) {
        truth = !!cond->uint;
    } else if (cond->type == JULIE_FLOAT) {
        truth = !!cond->floating;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        truth = 0;
    }


    then   = values[1 + (truth == 0)];
    status = julie_eval(interp, then, &then);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_cond;
    }

    *result = then;

out_free_cond:;
    julie_free_value(interp, cond);

out:;
    return status;
}

static Julie_Status julie_builtin_do(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    unsigned long long  i;
    Julie_Value        *it;
    Julie_Value        *ev;

    status  = JULIE_SUCCESS;
    *result = NULL;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    for (i = 0; i < n_values; i += 1) {
        it     = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            if (*result != NULL) {
                julie_free_value(interp, *result);
            }
            *result = NULL;
            goto out;
        }

        if (i == n_values - 1) {
            *result = ev;
        } else {
            julie_free_value(interp, ev);
        }
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_if(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *cond;
    unsigned      truth;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *ev;

    status = JULIE_SUCCESS;

    if (n_values < 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 2);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &cond);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (!JULIE_TYPE_IS_NUMBER(cond->type)) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, cond, _JULIE_NUMBER, cond->type);
        goto out_free_cond;
    }

    if (cond->type == JULIE_SINT) {
        truth = !!cond->sint;
    } else if (cond->type == JULIE_UINT) {
        truth = !!cond->uint;
    } else if (cond->type == JULIE_FLOAT) {
        truth = !!cond->floating;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        truth = 0;
    }

    if (truth) {
        for (i = 1; i < n_values; i += 1) {
            it     = values[i];
            status = julie_eval(interp, it, &ev);
            if (status != JULIE_SUCCESS) {
                if (*result != NULL) {
                    julie_free_value(interp, *result);
                }
                *result = NULL;
                goto out_free_cond;
            }

            if (i == n_values - 1) {
                *result = ev;
            } else {
                julie_free_value(interp, ev);
            }
        }
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

    interp->last_if_was_true = truth;

out_free_cond:;
    julie_free_value(interp, cond);

out:;
    return status;
}

static Julie_Status julie_builtin_elif(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *cond;
    unsigned      truth;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *ev;

    status = JULIE_SUCCESS;

    if (interp->last_popped_builtin_fn != julie_builtin_if
    &&  interp->last_popped_builtin_fn != julie_builtin_elif) {
        status  = JULIE_ERR_MUST_FOLLOW_IF;
        *result = NULL;
        julie_make_must_follow_if_error(interp, expr);
        goto out;
    }

    if (n_values < 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 2);
        *result = NULL;
        goto out;
    }

    if (!interp->last_if_was_true) {
        status = julie_eval(interp, values[0], &cond);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }


        if (!JULIE_TYPE_IS_NUMBER(cond->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, cond, _JULIE_NUMBER, cond->type);
            goto out_free_cond;
        }

        if (cond->type == JULIE_SINT) {
            truth = !!cond->sint;
        } else if (cond->type == JULIE_UINT) {
            truth = !!cond->uint;
        } else if (cond->type == JULIE_FLOAT) {
            truth = !!cond->floating;
        } else {
            JULIE_ASSERT(0 && "bad number type");
            truth = 0;
        }

        if (truth) {
            for (i = 1; i < n_values; i += 1) {
                it     = values[i];
                status = julie_eval(interp, it, &ev);
                if (status != JULIE_SUCCESS) {
                    if (*result != NULL) {
                        julie_free_value(interp, *result);
                    }
                    *result = NULL;
                    goto out_free_cond;
                }

                if (i == n_values - 1) {
                    *result = ev;
                } else {
                    julie_free_value(interp, ev);
                }
            }
        }

        interp->last_if_was_true = truth;

out_free_cond:;
        julie_free_value(interp, cond);
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_else(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *ev;

    status  = JULIE_SUCCESS;
    *result = NULL;

    if (interp->last_popped_builtin_fn != julie_builtin_if
    &&  interp->last_popped_builtin_fn != julie_builtin_elif) {
        status  = JULIE_ERR_MUST_FOLLOW_IF;
        *result = NULL;
        julie_make_must_follow_if_error(interp, expr);
        goto out;
    }

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    if (!interp->last_if_was_true) {
        for (i = 0; i < n_values; i += 1) {
            it     = values[i];
            status = julie_eval(interp, it, &ev);
            if (status != JULIE_SUCCESS) {
                if (*result != NULL) {
                    julie_free_value(interp, *result);
                }
                *result = NULL;
                goto out;
            }

            if (i == n_values - 1) {
                *result = ev;
            } else {
                julie_free_value(interp, ev);
            }
        }
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_while(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *_cond;
    Julie_Value  *val;
    Julie_Value  *cond;
    int           cont;
    unsigned      i;
    Julie_Value  *_val;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values < 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 1);
        *result = NULL;
        goto out;
    }

    _cond = values[0];
    val   = NULL;

    for (;;) {
        status = julie_eval(interp, _cond, &cond);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }

        if (!JULIE_TYPE_IS_NUMBER(cond->type)) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, cond, _JULIE_NUMBER, cond->type);
            julie_free_value(interp, cond);
            goto out;
        }

        if (cond->type == JULIE_SINT) {
            cont = !!cond->sint;
        } else if (cond->type == JULIE_UINT) {
            cont = !!cond->uint;
        } else if (cond->type == JULIE_FLOAT) {
            cont = !!cond->floating;
        } else {
            JULIE_ASSERT(0 && "bad number type");
            cont = 0;
        }

        julie_free_value(interp, cond);

        if (!cont) {
            *result = val != NULL
                        ? val
                        : julie_nil_value(interp);
            break;
        }

        if (val != NULL) {
            julie_free_value(interp, val);
        }

        for (i = 1; i < n_values; i += 1) {
            _val  = values[i];
            status = julie_eval(interp, _val, &val);
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                goto out;
            }

            if (i < n_values - 1) {
                julie_free_value(interp, val);
                val = NULL;
            }
        }
    }

out:;
    return status;
}

static Julie_Status julie_builtin_repeat(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *sym;
    Julie_Value        *n;
    long long int       times;
    Julie_String_ID     id;
    long long int       i;
    Julie_Value        *it;
    unsigned long long  j;
    Julie_Value        *_val;
    Julie_Value        *val;
    Julie_Status        save_status;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values < 3) {
        *result = NULL;
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 3, n_values, 1);
        goto out;
    }

    sym = values[0];

    status = julie_eval(interp, values[1], &n);
    if (status != JULIE_SUCCESS) {
        goto out;
    }

    if (n->type != JULIE_SINT) {
        *result = NULL;
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], JULIE_SINT, n->type);
        julie_free_value(interp, n);
        goto out;
    }

    times = n->sint;
    if (times < 0) { times = 0; }

    julie_free_value(interp, n);

    id = julie_value_string_id(interp, sym);

    it = NULL;
    for (i = 0; i < times; i += 1) {
        if (*result != NULL) {
            julie_free_value(interp, *result);
        }

        it = julie_sint_value(interp, i);
        if (interp->local_symtab_depth == 0) {
            status = julie_bind(interp, id, &it);
        } else {
            status = julie_bind_local(interp, id, &it);
        }

        if (status != JULIE_SUCCESS) {
            *result = NULL;
            julie_make_bind_error(interp, sym, status, id);
            goto out;
        }

        for (j = 1; j < n_values; j += 1) {
            _val  = values[j];
            status = julie_eval(interp, _val, &val);
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                goto out_unbind;
            }

            if (j == n_values - 1) {
                *result = val;
            } else {
                julie_free_value(interp, val);
                val = NULL;
            }
        }
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out_unbind:;
    if (it != NULL) {
        if (*result == it) {
            *result = julie_force_copy(interp, *result);
        }

        save_status = status;

        if (interp->local_symtab_depth == 0) {
            status = julie_unbind(interp, id);
        } else {
            status = julie_unbind_local(interp, id);
        }

        if (status != JULIE_SUCCESS) {
            if (*result != NULL) {
                julie_free_value(interp, *result);
            }
            *result = NULL;
            julie_make_bind_error(interp, sym, status, id);
            goto out;
        }

        status = save_status;
    }

out:;
    return status;
}

static Julie_Status julie_builtin_foreach(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status         status;
    Julie_Value         *sym;
    Julie_String_ID      id;
    Julie_Value         *_container;
    Julie_Value         *container;
    unsigned long long   i;
    Julie_Value         *val;
    unsigned long long   j;
    Julie_Value         *it;
    Julie_Value         *bound;
    Julie_Value         *ev;
    Julie_Value        **valp;

    *result = NULL;

    if (n_values < 3) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 3, n_values, 1);
        *result = NULL;
        goto out;
    }

    sym = values[0];

    if (sym->type != JULIE_SYMBOL) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, sym, JULIE_SYMBOL, sym->type);
        goto out;
    }

    id = julie_value_string_id(interp, sym);

    _container = values[1];

    status = julie_eval(interp, _container, &container);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (container->type != JULIE_LIST
    &&  container->type != JULIE_OBJECT) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, container, _JULIE_LIST_OR_OBJECT, container->type);
        goto out_free;
    }

    JULIE_ARRAY_PUSH(interp->iter_vals, container);

    if (container->type == JULIE_LIST) {
        i = 0;
        ARRAY_FOR_EACH(container->list, it) {
            it->owned = 1;
            JULIE_BORROW_NO_CHECK(it);

            bound = it;

            if (interp->local_symtab_depth == 0) {
                status = julie_bind(interp, id, &bound);
            } else {
                status = julie_bind_local(interp, id, &bound);
            }
            if (status != JULIE_SUCCESS) {
                JULIE_UNBORROW(it);
                *result = NULL;
                julie_make_bind_error(interp, sym, status, id);
                goto out_pop;
            }

            JULIE_BORROW_NO_CHECK(it);

            for (j = 2; j < n_values; j += 1) {
                val    = values[j];
                status = julie_eval(interp, val, &ev);
                if (status != JULIE_SUCCESS) {
                    JULIE_UNBORROW(it);
                    if (interp->local_symtab_depth == 0) {
                        julie_unbind(interp, id);
                    } else {
                        julie_unbind_local(interp, id);
                    }
                    JULIE_UNBORROW_NO_CHECK(it);
                    it->owned = 0;
                    *result = NULL;
                    goto out_pop;
                }

                if (j < n_values - 1) {
                    julie_free_value(interp, ev);
                    ev = NULL;
                }
            }

            i += 1;

            if (i == julie_array_len(container->list)) {
                if (ev == bound) {
                    ev = julie_force_copy(interp, bound);
                }
                *result = ev;
            } else {
                julie_free_value(interp, ev);
            }

            JULIE_UNBORROW_NO_CHECK(it);

            if (interp->local_symtab_depth == 0) {
                status = julie_unbind(interp, id);
            } else {
                status = julie_unbind_local(interp, id);
            }
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                julie_make_bind_error(interp, sym, status, id);
                goto out_pop;
            }

            JULIE_UNBORROW_NO_CHECK(it);
            it->owned = 0;
        }
    } else {
        if (julie_symbol_starts_with_ampersand(interp, id)) {
            *result = NULL;
            status = JULIE_ERR_REF_OF_OBJECT_KEY;
            julie_make_bind_error(interp, sym, status, id);
            goto out_pop;
        }

        i = 0;
        hash_table_traverse((_Julie_Object)container->object, it, valp) {
            (void)valp;

            it->owned = 1;
            JULIE_BORROW_NO_CHECK(it);

            bound = it;

            if (interp->local_symtab_depth == 0) {
                status = julie_bind(interp, id, &bound);
            } else {
                status = julie_bind_local(interp, id, &bound);
            }
            if (status != JULIE_SUCCESS) {
                JULIE_UNBORROW(it);
                *result = NULL;
                julie_make_bind_error(interp, sym, status, id);
                goto out_pop;
            }

            JULIE_BORROW_NO_CHECK(it);

            for (j = 2; j < n_values; j += 1) {
                val    = values[j];
                status = julie_eval(interp, val, &ev);
                if (status != JULIE_SUCCESS) {
                    JULIE_UNBORROW(it);
                    if (interp->local_symtab_depth == 0) {
                        julie_unbind(interp, id);
                    } else {
                        julie_unbind_local(interp, id);
                    }
                    JULIE_UNBORROW_NO_CHECK(it);
                    it->owned = 0;
                    *result = NULL;
                    goto out_pop;
                }

                if (j < n_values - 1) {
                    julie_free_value(interp, ev);
                    ev = NULL;
                }
            }

            i += 1;


            if (i == hash_table_len((_Julie_Object)container->object)) {
                if (ev == bound) {
                    ev = julie_force_copy(interp, bound);
                }
                *result = ev;
            } else {
                julie_free_value(interp, ev);
            }

            JULIE_UNBORROW_NO_CHECK(it);

            if (interp->local_symtab_depth == 0) {
                status = julie_unbind(interp, id);
            } else {
                status = julie_unbind_local(interp, id);
            }
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                julie_make_bind_error(interp, sym, status, id);
                goto out_pop;
            }

            JULIE_UNBORROW_NO_CHECK(it);
            it->owned = 0;
        }
    }

    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out_pop:;
    julie_array_pop(interp->iter_vals);

out_free:;
    julie_free_value(interp, container);

out:;
    return status;
}

static Julie_Status julie_builtin_match(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *val;
    unsigned      i;
    Julie_Value  *list;
    Julie_Value  *match;
    int           equ;
    unsigned      j;

    status = JULIE_SUCCESS;

    *result = NULL;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 1);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    for (i = 1; i < n_values; i += 1) {
        list = values[i];

        if (list->type != JULIE_LIST) {
            *result = NULL;
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, values[i], JULIE_LIST, list->type);
            goto out_free_val;
        }

        if (julie_array_len(list->list) < 2) {
            *result = NULL;
            status = JULIE_ERR_ARITY;
            julie_make_arity_error(interp, values[i], 2, julie_array_len(list->list), 0);
            goto out_free_val;
        }

        status = julie_eval(interp, julie_array_elem(list->list, 0), &match);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free_val;
        }

        equ = julie_equal(val, match);

        julie_free_value(interp, match);

        if (!equ) { continue; }

        for (j = 1; j < julie_array_len(list->list); j += 1) {
            status = julie_eval(interp, julie_array_elem(list->list, j), result);
            if (status != JULIE_SUCCESS) {
                *result = NULL;
                goto out_free_val;
            }

            if (j < julie_array_len(list->list) - 1) {
                julie_free_value(interp, *result);
                *result = NULL;
            }
        }

        break;
    }


    if (*result == NULL) {
        *result = julie_nil_value(interp);
    }

out_free_val:;
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status _julie_builtin_print(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result, int nl) {
    Julie_Status  status;
    unsigned      i;
    Julie_Value  *it;
    Julie_Value  *ev;

    (void)expr;

    status = JULIE_SUCCESS;

    for (i = 0; i < n_values; i += 1) {
        it = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }
        julie_print(interp, ev, 0);

        julie_free_value(interp, ev);
    }

    *result = julie_nil_value(interp);

    if (nl) { julie_output(interp, "\n", 1); }

out:;
    return status;
}

static Julie_Status julie_builtin_print(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_print(interp, expr, n_values, values, result, 0);
}

static Julie_Status julie_builtin_println(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_print(interp, expr, n_values, values, result, 1);
}

static Julie_Status julie_builtin_fmt(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *fmt;
    const Julie_String *fstring;
    unsigned            n;
    unsigned            extra;
    char                last;
    char                c;
    unsigned            i;
    Julie_Array        *strings = JULIE_ARRAY_INIT;
    Julie_Value        *it;
    Julie_Value        *ev;
    char               *s;
    int                 len;
    char               *formatted;
    char               *ins;
    int                 sublen;

    status = JULIE_SUCCESS;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &fmt);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (fmt->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, fmt, JULIE_STRING, fmt->type);
        *result = NULL;
        goto out_free_fmt;
    }

    fstring = julie_get_string(interp, julie_value_string_id(interp, fmt));
    n       = 0;
    extra   = 0;
    last    = 0;
    for (i = 0; i < fstring->len; i += 1) {
        c = fstring->chars[i];
        if (c == '%') {
            extra += 1;
            if (last != '\\') {
                n += 1;
            }
        }
        last = c;
    }

    if (n_values - 1 != n) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, n + 1, n_values, 0);
        *result = NULL;
        goto out_free_fmt;
    }

    for (i = 1; i < n_values; i += 1) {
        it = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free_strings;
        }
        if (ev->type == JULIE_STRING || ev->type == JULIE_SYMBOL) {
            s = strdup(julie_value_cstring(ev));
        } else {
            s = julie_to_string(interp, ev, JULIE_NO_QUOTE);
        }
        JULIE_ARRAY_PUSH(strings, s);
        julie_free_value(interp, ev);
    }

    len = fstring->len - extra;
    ARRAY_FOR_EACH(strings, s) {
        len += strlen(s);
    }

    formatted = malloc(len + 1);
    ins       = formatted;

    n    = 0;
    last = 0;
    for (i = 0; i < fstring->len; i += 1) {
        c = fstring->chars[i];
        if (c == '\\' && i < fstring->len - 1 && fstring->chars[i + 1] == '%') {
            /* skip */
        } else if (c == '%' && last != '\\') {
            s      = julie_array_elem(strings, n);
            sublen = strlen(s);
            memcpy(ins, s, sublen);
            ins += sublen;
            n += 1;
        } else {
            *ins  = c;
            ins  += 1;
        }
        last = c;
    }

    formatted[len] = 0;

    *result = julie_string_value_giveaway(interp, formatted);

out_free_strings:;
    ARRAY_FOR_EACH(strings, s) {
        free(s);
    }
    julie_array_free(strings);

out_free_fmt:;
    julie_free_value(interp, fmt);

out:;
    return status;
}

static Julie_Status julie_builtin_num_fmt(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *fmt;
    Julie_Value  *val;
    const char   *cstring;
    char          fbuff[128];
    char          buff[128];

    status = julie_args(interp, expr, "sn", n_values, values, &fmt, &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    cstring = julie_value_cstring(fmt);

    snprintf(fbuff, sizeof(fbuff), "%%%s", cstring);

    if (val->type == JULIE_SINT) {
        snprintf(buff, sizeof(buff), fbuff, val->sint);
    } else if (val->type == JULIE_UINT) {
        snprintf(buff, sizeof(buff), fbuff, val->uint);
    } else if (val->type == JULIE_FLOAT) {
        snprintf(buff, sizeof(buff), fbuff, val->floating);
    } else {
        JULIE_ASSERT(0 && "bad number type");
    }

    *result = julie_string_value(interp, buff);

    julie_free_value(interp, fmt);
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_spad(Julie_Interp *interp, Julie_Value *tree, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *w;
    Julie_Value  *val;
    int           width;
    int           ljust;
    char         *s;
    int           len;
    int           padding;
    char         *padded;

    status = julie_args(interp, tree, "i*", n_values, values, &w, &val);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    width = w->type == JULIE_SINT ? w->sint : w->uint;
    ljust = width < 0;
    s     = julie_to_string(interp, val, JULIE_NO_QUOTE);
    len   = strlen(s);

    if (ljust) { width = -width; }

    padding = width > len
                ? width - len
                : 0;

    padded = malloc(len + padding + 1);
    memset(padded, ' ', len + padding);
    memcpy(padded + ((!ljust) * padding), s, len);
    padded[len + padding] = 0;

    *result = julie_string_value(interp, padded);

    free(padded);
    free(s);

    julie_free_value(interp, w);
    julie_free_value(interp, val);

out:;
    return status;
}

static Julie_Status julie_builtin_printf(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *fmt;
    const Julie_String *fstring;
    unsigned           n;
    unsigned           extra;
    char               last;
    char               c;
    unsigned           i;
    Julie_Array        *strings = JULIE_ARRAY_INIT;
    Julie_Value        *it;
    Julie_Value        *ev;
    char              *s;
    int                len;
    char              *formatted;
    char              *ins;
    int                sublen;

    status = JULIE_SUCCESS;

    if (n_values < 1) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 1, n_values, 1);
        *result = NULL;
        goto out;
    }

    status = julie_eval(interp, values[0], &fmt);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (fmt->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, fmt, JULIE_STRING, fmt->type);
        *result = NULL;
        goto out_free_fmt;
    }

    fstring = julie_get_string(interp, julie_value_string_id(interp, fmt));
    n       = 0;
    extra   = 0;
    last    = 0;
    for (i = 0; i < fstring->len; i += 1) {
        c = fstring->chars[i];
        if (c == '%') {
            extra += 1;
            if (last != '\\') {
                n += 1;
            }
        }
        last = c;
    }

    if (n_values - 1 != n) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, n + 1, n_values, 0);
        *result = NULL;
        goto out_free_fmt;
    }

    for (i = 1; i < n_values; i += 1) {
        it = values[i];
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_free_strings;
        }
        if (ev->type == JULIE_STRING || ev->type == JULIE_SYMBOL) {
            s = strdup(julie_value_cstring(ev));
        } else {
            s = julie_to_string(interp, ev, JULIE_NO_QUOTE);
        }
        JULIE_ARRAY_PUSH(strings, s);
        julie_free_value(interp, ev);
    }

    len = fstring->len - extra;
    ARRAY_FOR_EACH(strings, s) {
        len += strlen(s);
    }

    formatted = malloc(len + 1);
    ins       = formatted;

    n    = 0;
    last = 0;
    for (i = 0; i < fstring->len; i += 1) {
        c = fstring->chars[i];
        if (c == '\\' && i < fstring->len - 1 && fstring->chars[i + 1] == '%') {
            /* skip */
        } else if (c == '%' && last != '\\') {
            s      = julie_array_elem(strings, n);
            sublen = strlen(s);
            memcpy(ins, s, sublen);
            ins += sublen;
            n += 1;
        } else {
            *ins  = c;
            ins  += 1;
        }
        last = c;
    }

    formatted[len] = 0;

    *result = julie_string_value_giveaway(interp, formatted);

    julie_print(interp, *result, 0);

out_free_strings:;
    ARRAY_FOR_EACH(strings, s) {
        free(s);
    }
    julie_array_free(strings);

out_free_fmt:;
    julie_free_value(interp, fmt);

out:;
    return status;
}

static Julie_Status julie_builtin_parse_int(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *s;
    const char   *cstring;
    long long     i;

    status = julie_args(interp, expr, "s", n_values, values, &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    cstring = julie_value_cstring(s);

    if (sscanf(cstring, "%lld", &i) == 1) {
        *result = julie_sint_value(interp, i);
    } else {
        *result = julie_nil_value(interp);
    }

    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_parse_hex(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status         status;
    Julie_Value         *s;
    const char          *cstring;
    unsigned long long   i;

    status = julie_args(interp, expr, "s", n_values, values, &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    cstring = julie_value_cstring(s);

    if (sscanf(cstring, "%llx", &i) == 1) {
        *result = julie_uint_value(interp, i);
    } else {
        *result = julie_nil_value(interp);
    }

    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_parse_float(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *s;
    const char   *cstring;
    double        d;

    status = julie_args(interp, expr, "s", n_values, values, &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    cstring = julie_value_cstring(s);

    if (sscanf(cstring, "%lg", &d) == 1) {
        *result = julie_float_value(interp, d);
    } else {
        *result = julie_nil_value(interp);
    }

    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_fn(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *param_list;
    long long     i;
    long long     rest_idx;
    Julie_Value  *it;

    status = JULIE_SUCCESS;

    if (n_values < 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 1);
        *result = NULL;
        goto out;
    }

    param_list = values[0];

    if (param_list->type != JULIE_LIST) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, param_list, JULIE_LIST, param_list->type);
        *result = NULL;
        goto out;
    }

    i        = 0;
    rest_idx = -1;
    ARRAY_FOR_EACH(param_list->list, it) {
        if (it->type != JULIE_SYMBOL) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, it, JULIE_SYMBOL, it->type);
            *result = NULL;
            goto out;
        }

        if (rest_idx != -1) {
            status = JULIE_ERR_REST_MUST_BE_LAST;
            julie_make_interp_error(interp, it, status);
            *result = NULL;
            goto out;
        }

        if (julie_value_string_id(interp, it) == interp->ellipses_id) {
            rest_idx = i;
        }

        i += 1;
    }

    *result = julie_fn_value(interp, n_values, values);

out:;
    return status;
}

static void _julie_collect_lambda_free_variables(Julie_Interp *interp, Julie_Value *expr, Julie_Array *bounds, Julie_Array **frees) {
    Julie_Value     *it;
    Julie_Value     *first;
    Julie_String_ID  id;

    switch (expr->type) {
        case JULIE_SYMBOL:
            ARRAY_FOR_EACH(bounds, it) {
                if (julie_equal(expr, it)) { return; }
            }
            ARRAY_FOR_EACH(*frees, it) {
                if (julie_equal(expr, it)) { return; }
            }

            JULIE_ARRAY_PUSH(*frees, expr);
            break;

        case JULIE_LIST:
            if (julie_array_len(expr->list) == 0) { return; }

            first = julie_array_elem(expr->list, 0);

            if (first->type == JULIE_SYMBOL
            &&  ((id = julie_value_string_id(interp, first)), 1)
            &&  (   id == julie_get_string_id(interp, "lambda")
                ||  id == julie_get_string_id(interp, "fn")
                ||  id == julie_get_string_id(interp, "'"))) {

                /* Skip these forms. */
                return;
            } else {
                ARRAY_FOR_EACH(expr->list, it) {
                    _julie_collect_lambda_free_variables(interp, it, bounds, frees);
                }
            }
            break;
    }
}

static Julie_Status julie_builtin_lambda(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *param_list;
    long long           i;
    long long           rest_idx;
    Julie_Array        *bounds = JULIE_ARRAY_INIT;
    Julie_Value        *it;
    Julie_Closure_Info *closure;
    Julie_Array        *frees = JULIE_ARRAY_INIT;
    Julie_Value        *lookup;
    Julie_String_ID     id;

    status = JULIE_SUCCESS;

    if (n_values < 1 || n_values > 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2 - (n_values == 1), n_values, 1 - (n_values == 2));
        *result = NULL;
        goto out;
    }

    if (n_values == 2) {
        param_list = values[0];

        if (param_list->type == JULIE_LIST) {
            i        = 0;
            rest_idx = -1;
            ARRAY_FOR_EACH(param_list->list, it) {
                if (it->type != JULIE_SYMBOL) {
                    status = JULIE_ERR_TYPE;
                    julie_make_type_error(interp, param_list, JULIE_SYMBOL, it->type);
                    *result = NULL;
                    goto out;
                }

                if (rest_idx != -1) {
                    status = JULIE_ERR_REST_MUST_BE_LAST;
                    julie_make_interp_error(interp, it, status);
                    *result = NULL;
                    goto out;
                }

                if (julie_value_string_id(interp, it) == interp->ellipses_id) {
                    rest_idx = i;
                }

                bounds = julie_array_push(bounds, it);

                i += 1;
            }
        } else {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, param_list, JULIE_LIST, param_list->type);
            *result = NULL;
            goto out;
        }
    }

    closure = malloc(sizeof(*closure));

    closure->captures = hash_table_make(Julie_String_ID, Julie_Value_Ptr, julie_string_id_hash);

    _julie_collect_lambda_free_variables(interp, values[n_values == 2], bounds, &frees);

    ARRAY_FOR_EACH(frees, it) {
        id = julie_value_string_id(interp, it);
        lookup = julie_lookup(interp, id);
        if (lookup != NULL) {
            hash_table_insert(closure->captures, id, julie_force_copy(interp, lookup));
        }
    }

    julie_array_free(frees);
    julie_array_free(bounds);

    *result = julie_lambda_value(interp, n_values, values, closure);

out:;
    return status;
}

typedef union {
    char          c;
    unsigned char u_c;
    unsigned char bytes[4];
} Julie_Glyph;

#define JULIE_G_IS_ASCII(g) (!((g)->u_c >> 7))
static const unsigned char julie_utf8_lens[] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 4, 1
};

#define julie_glyph_len(g)                          \
    (likely(JULIE_G_IS_ASCII(g))                    \
        ? 1                                         \
        : (int)(julie_utf8_lens[(g)->u_c >> 3ULL]))

static Julie_Status julie_builtin_chars(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int          status;
    Julie_Value *s;
    Julie_Glyph *g;
    int          len;
    char         buff[sizeof(Julie_Glyph) + 1];

    status = julie_args(interp, expr, "s", n_values, values, &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    *result = julie_list_value(interp);

    g = (Julie_Glyph*)julie_value_cstring(s);

    while (g->c) {
        len = julie_glyph_len(g);
        memcpy(buff, g->bytes, len);
        buff[len] = 0;
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value(interp, buff));
        g = (Julie_Glyph*)(((char*)g) + len);
    }

    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_split(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int          status;
    Julie_Value *s;
    Julie_Value *t;
    char        *cpy;
    const char  *delim;
    const char  *tok;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (s->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_STRING, s->type);
        goto out_free_s;
    }

    status = julie_eval(interp, values[1], &t);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_s;
    }

    if (t->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], JULIE_STRING, t->type);
        goto out_free_st;
    }

    cpy   = strdup(julie_value_cstring(s));
    delim = julie_value_cstring(t);

    *result = julie_list_value(interp);

    for (tok = strtok(cpy, delim); tok != NULL; tok = strtok(NULL, delim)) {
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value(interp, tok));
    }

    free(cpy);

out_free_st:;
    julie_free_value(interp, t);
out_free_s:;
    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_splits(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int                 status;
    Julie_Value        *s;
    Julie_Value        *t;
    const char         *string;
    const char         *delim;
    unsigned long long  delim_len;
    const char         *tok;
    char               *next;

    if (n_values != 2) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 2, n_values, 0);
        goto out;
    }

    status = julie_eval(interp, values[0], &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (s->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[0], JULIE_STRING, s->type);
        goto out_free_s;
    }

    status = julie_eval(interp, values[1], &t);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_free_s;
    }

    if (t->type != JULIE_STRING) {
        status = JULIE_ERR_TYPE;
        julie_make_type_error(interp, values[1], JULIE_STRING, t->type);
        goto out_free_st;
    }

    string    = julie_value_cstring(s);
    delim     = julie_value_cstring(t);
    delim_len = strlen(delim);

    *result = julie_list_value(interp);

    tok = string;

    while ((next = strstr(tok, delim)) != NULL) {
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value_known_size(interp, tok, next - tok));
        tok = next + delim_len;
    }
    JULIE_ARRAY_PUSH((*result)->list, julie_string_value(interp, tok));

out_free_st:;
    julie_free_value(interp, t);
out_free_s:;
    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_replace(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int          status;
    Julie_Value *s;
    Julie_Value *a;
    Julie_Value *b;
    const char  *base;
    const char  *old;
    const char  *new;
    char        *str;
    const char  *found;

    status = julie_args(interp, expr, "sss", n_values, values, &s, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    base = julie_value_cstring(s);
    old  = julie_value_cstring(a);
    new  = julie_value_cstring(b);

    str = malloc(strlen(base) + 1);

    str[0] = 0;

    if (strlen(old) > 0) {
        while ((found = strstr(base, old)) != NULL) {
            str = realloc(str, strlen(str) + (found - base) + 1);
            strncat(str, base, (found - base));
            str = realloc(str, strlen(str) + strlen(new) + 1);
            strcat(str, new);
            base = found + strlen(old);
        }
    }

    str = realloc(str, strlen(str) + strlen(base) + 1);
    strcat(str, base);

    *result = julie_string_value_giveaway(interp, str);

    julie_free_value(interp, s);
    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_trim(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int                 status;
    Julie_Value        *s;
    char               *cpy;
    char               *p;
    unsigned long long  len;

    status = julie_args(interp, expr, "s", n_values, values, &s);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    cpy = strdup(julie_value_cstring(s));
    p   = cpy;

    while (*p && julie_is_space(*p)) { p += 1; }
    len = strlen(p);
    while (len && julie_is_space(p[len - 1])) {
        p[len - 1] = 0;
        len -= 1;
    }

    *result = julie_string_value(interp, p);

    free(cpy);

    julie_free_value(interp, s);

out:;
    return status;
}

static Julie_Status julie_builtin_contains(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int          status;
    Julie_Value *haystack;
    Julie_Value *needle;
    const char  *h;
    const char  *n;
    const char  *s;

    status = julie_args(interp, expr, "ss", n_values, values, &haystack, &needle);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    h = julie_value_cstring(haystack);
    n = julie_value_cstring(needle);

    s = strstr(h, n);

    *result = julie_sint_value(interp, s != NULL);

    julie_free_value(interp, haystack);
    julie_free_value(interp, needle);

out:;
    return status;
}

static Julie_Status julie_builtin_startswith(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int                 status;
    Julie_Value        *a;
    Julie_Value        *b;
    const char         *sa;
    const char         *sb;
    unsigned long long  la;
    unsigned long long  lb;

    status = julie_args(interp, expr, "ss", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    sa = julie_value_cstring(a);
    sb = julie_value_cstring(b);
    la = a->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, a->string_id)->len
            : strlen(sa);
    lb = b->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, b->string_id)->len
            : strlen(sb);

    *result = julie_sint_value(interp, lb <= la && (strncmp(sa, sb, lb) == 0));

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_endswith(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int                 status;
    Julie_Value        *a;
    Julie_Value        *b;
    const char         *sa;
    const char         *sb;
    unsigned long long  la;
    unsigned long long  lb;

    status = julie_args(interp, expr, "ss", n_values, values, &a, &b);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    sa = julie_value_cstring(a);
    sb = julie_value_cstring(b);
    la = a->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, a->string_id)->len
            : strlen(sa);
    lb = b->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, b->string_id)->len
            : strlen(sb);

    *result = julie_sint_value(interp, lb <= la && (strncmp(sa + la - lb, sb, lb) == 0));

    julie_free_value(interp, a);
    julie_free_value(interp, b);

out:;
    return status;
}

static Julie_Status julie_builtin_substr(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int          status;
    Julie_Value *s;
    Julie_Value *pos;
    Julie_Value *len;
    const char  *cs;
    long long    cl;
    long long    p;
    long long    l;

    status = julie_args(interp, expr, "sii", n_values, values, &s, &pos, &len);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    if (pos->type == JULIE_SINT) {
        p = pos->sint;
    } else if (pos->type == JULIE_UINT) {
        p = (long long)pos->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        p = 0;
    }

    if (len->type == JULIE_SINT) {
        l = len->sint;
    } else if (len->type == JULIE_UINT) {
        l = (long long)len->uint;
    } else {
        JULIE_ASSERT(0 && "bad number type");
        l = 0;
    }

    cs = julie_value_cstring(s);
    cl = s->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, julie_value_string_id(interp, s))->len
            : strlen(cs);

    if (p < 0 || p >= cl) {
        status = JULIE_ERR_BAD_INDEX;
        julie_make_bad_index_error(interp, values[1], pos);
        *result = NULL;
        goto out_free;
    }

    if (l > cl - p) {
        l = cl - p;
    }

    *result = julie_string_value_known_size(interp, cs + p, l);

out_free:;
    julie_free_value(interp, s);
    julie_free_value(interp, pos);
    julie_free_value(interp, len);

out:;
    return status;
}

static Julie_Status julie_builtin_regex_match(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int              status;
    Julie_Value     *s;
    Julie_Value     *rs;
    Julie_String_ID  rid;
    regex_t         *re;
    int              err;
    regex_t          new_re;
    size_t           err_size;
    char            *err_buff;
    const char      *cs;
    int              nmatch;
    regmatch_t      *matches;
    int              i;

    status = julie_args(interp, expr, "ss", n_values, values, &s, &rs);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    rid = julie_value_string_id(interp, rs);

    re = hash_table_get_val_with_hash(interp->compiled_regex, rid, JULIE_STRING_ID_HASH(rid));
    if (re != NULL) { goto do_match; }

    err = regcomp(&new_re, rid->chars, REG_EXTENDED);

    if (err != 0) {
        err_size = regerror(err, &new_re, NULL, 0);
        err_buff = malloc(err_size);
        regerror(err, &new_re, err_buff, err_size);
        *result = NULL;
        status = JULIE_ERR_REGEX;
        julie_make_regex_error(interp, values[1], err_buff);
        free(err_buff);
        goto out_free;
    }

    re = hash_table_insert(interp->compiled_regex, rid, new_re);

do_match:;
    cs = julie_value_cstring(s);

    nmatch  = re->re_nsub + 1;
    matches = alloca(sizeof(regmatch_t) * nmatch);

    err = regexec(re, cs, nmatch, matches, 0);

    if (err != 0) {
        *result = julie_nil_value(interp);
        goto out_free;
    }

    *result = julie_list_value(interp);

    for (i = 0; i < nmatch; i += 1) {
        JULIE_ARRAY_PUSH((*result)->list,
                         julie_string_value_known_size(interp, cs + matches[i].rm_so, matches[i].rm_eo - matches[i].rm_so));
    }

out_free:;
    julie_free_value(interp, s);
    julie_free_value(interp, rs);

out:;
    return status;
}

static Julie_Status _julie_builtin_fopen(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result, const char *mode) {
    Julie_Status  status;
    Julie_Value  *pathv;
    const char   *path;
    FILE         *f;
    Julie_Value  *key;
    Julie_Value  *val;

    status = julie_args(interp, expr, "s", n_values, values, &pathv);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    path = julie_value_cstring(pathv);

    f = fopen(path, mode);

    if (f == NULL) {
        julie_free_value(interp, pathv);
        *result = julie_nil_value(interp);
        goto out;
    }

    *result = julie_object_value(interp);
    key = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    val = julie_uint_value(interp, (unsigned long long)(void*)f);
    julie_object_insert_field(interp, *result, key, val, NULL);
    key = julie_symbol_value(interp, julie_get_string_id(interp, "'__path__"));
    val = pathv;
    if (val->owned || val->source_node) {
        val = julie_force_copy(interp, val);
        julie_free_value(interp, pathv);
    }
    julie_object_insert_field(interp, *result, key, val, NULL);

out:;
    return status;
}

static Julie_Status julie_builtin_fopen_rd(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_fopen(interp, expr, n_values, values, result, "r");
}

static Julie_Status julie_builtin_fopen_wr(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    return _julie_builtin_fopen(interp, expr, n_values, values, result, "w");
}

static Julie_Status julie_builtin_fclose(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *file;
    Julie_Value  *key;
    Julie_Value  *handle;
    FILE         *f;

    status = julie_args(interp, expr, "o", n_values, values, &file);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    key    = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    handle = julie_object_get_field(file, key);
    julie_free_value(interp, key);

    if (handle != NULL && handle->type == JULIE_UINT) {
        f = (void*)handle->uint;
    } else {
        f = NULL;
    }

    julie_free_value(interp, file);

    if (f == NULL) {
        *result = julie_nil_value(interp);
        goto out;
    }

    fclose(f);
    *result = julie_sint_value(interp, 0);

out:;
    return status;
}

static Julie_Status julie_builtin_frewind(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *file;
    Julie_Value  *key;
    Julie_Value  *handle;
    FILE         *f;

    status = julie_args(interp, expr, "o", n_values, values, &file);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    key    = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    handle = julie_object_get_field(file, key);
    julie_free_value(interp, key);

    if (handle != NULL && handle->type == JULIE_UINT) {
        f = (void*)handle->uint;
    } else {
        f = NULL;
    }

    julie_free_value(interp, file);

    if (f == NULL) {
        *result = julie_nil_value(interp);
        goto out;
    }

    rewind(f);
    *result = julie_sint_value(interp, 0);

out:;
    return status;
}

static Julie_Status julie_builtin_fread_line(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *file;
    Julie_Value  *key;
    Julie_Value  *handle;
    FILE         *f;
    char         *line;
    size_t        cap;
    ssize_t       len;

    status = julie_args(interp, expr, "o", n_values, values, &file);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    key    = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    handle = julie_object_get_field(file, key);
    julie_free_value(interp, key);

    if (handle != NULL && handle->type == JULIE_UINT) {
        f = (void*)handle->uint;
    } else {
        f = NULL;
    }

    julie_free_value(interp, file);

    if (f == NULL) {
        *result = julie_nil_value(interp);
        goto out;
    }

    line = NULL;
    cap  = 0;

    if ((len = getline(&line, &cap, f)) <= 0) {
        if (line != NULL) {
            free(line);
        }
        *result = julie_nil_value(interp);
        goto out;
    }

    if (line[len - 1] == '\n') {
        line[len - 1] = 0;
    }

    *result = julie_string_value_giveaway(interp, line);

out:;
    return status;
}

static Julie_Status julie_builtin_fread_lines(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *file;
    Julie_Value  *key;
    Julie_Value  *handle;
    FILE         *f;
    char         *line;
    size_t        cap;
    ssize_t       len;

    status = julie_args(interp, expr, "o", n_values, values, &file);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    key    = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    handle = julie_object_get_field(file, key);
    julie_free_value(interp, key);

    if (handle != NULL && handle->type == JULIE_UINT) {
        f = (void*)handle->uint;
    } else {
        f = NULL;
    }

    julie_free_value(interp, file);

    if (f == NULL) {
        *result = julie_nil_value(interp);
        goto out;
    }

    *result = julie_list_value(interp);

    line = NULL;
    cap  = 0;
    while ((len = getline(&line, &cap, f)) > 0) {
        if (line[len - 1] == '\n') {
            line[len - 1] = 0;
        }
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value_giveaway(interp, line));
        line = NULL;
        cap  = 0;
    }

    if (line != NULL) {
        free(line);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_fwrite(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *file;
    Julie_Value        *string;
    Julie_Value        *key;
    Julie_Value        *handle;
    const char         *s;
    unsigned long long  len;
    FILE               *f;
    size_t              r;

    status = julie_args(interp, expr, "os", n_values, values, &file, &string);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    key    = julie_symbol_value(interp, julie_get_string_id(interp, "'__handle__"));
    handle = julie_object_get_field(file, key);
    julie_free_value(interp, key);

    if (handle != NULL && handle->type == JULIE_UINT) {
        f = (void*)handle->uint;
    } else {
        f = NULL;
    }

    julie_free_value(interp, file);

    if (f == NULL) {
        *result = julie_nil_value(interp);
        goto out;
    }

    s   = julie_value_cstring(string);
    len = string->tag == JULIE_STRING_TYPE_INTERN
            ? julie_get_string(interp, string->string_id)->len
            : strlen(s);

    r = fwrite(s, 1, len, f);
    fflush(f);

    julie_free_value(interp, string);

    *result = julie_sint_value(interp, r);

out:;
    return status;
}


static Julie_Status julie_builtin_backtrace(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    int                    status;
    unsigned long long     i;
    Julie_Backtrace_Entry *it;
    char                  *s;
    char                   buff[4096];

    status = JULIE_SUCCESS;

    (void)values;
    if (n_values != 0) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 0, n_values, 0);
        *result = NULL;
        goto out;
    }

    *result = julie_list_value(interp);

    i = 1;
    while ((it = julie_bt_entry(interp, i)) != NULL) {
        s = julie_to_string(interp, it->fn, 0);
        snprintf(buff, sizeof(buff), "%s:%llu:%llu %s",
                 it->file_id == NULL ? "<?>" : julie_get_cstring(it->file_id),
                 it->line,
                 it->col,
                 s);
        free(s);
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value(interp, buff));

        i += 1;
    }

out:;
    return status;
}

#if 0
static Julie_Status julie_builtin_eval_file(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *path;
    const Julie_String *pstring;
    Julie_String_ID     save_file;
    const char         *mem;
    unsigned long long  size;
    Julie_Array        *nodes = JULIE_ARRAY_INIT;
    unsigned long long  i;
    Julie_Value        *it;
    Julie_Value        *ev;

    status = julie_args(interp, expr, "s", n_values, values, &path);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    pstring = julie_get_string(interp, julie_value_string_id(interp, path));
    julie_free_value(interp, path);

    status = julie_map_file_into_readonly_memory(pstring->chars, &mem, &size);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        julie_make_file_error(interp, expr, status, pstring->chars);
        goto out_free;
    }

    save_file           = interp->cur_file_id;
    interp->cur_file_id = (Julie_String_ID)pstring;

    status = julie_parse_nodes(interp, mem, size, &nodes);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out_restore_file;
    }

    i = 0;
    ARRAY_FOR_EACH(nodes, it) {
        status = julie_eval(interp, it, &ev);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out_restore_file;
        }

        i += 1;

        if (i == julie_array_len(nodes)) {
            *result = ev;
        } else {
            julie_free_value(interp, ev);
        }
    }

    if (*result != NULL) {
        *result = julie_force_copy(interp, *result);
    } else {
        *result = julie_nil_value(interp);
    }

out_restore_file:;
    interp->cur_file_id = save_file;

out_free:;
    ARRAY_FOR_EACH(nodes, it) {
        julie_force_free_value(interp, it);
    }
    julie_array_free(nodes);

out:;
    return status;
}
#endif

static Julie_Status julie_builtin_use_package(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *name;
    const Julie_String *name_string;

    if (interp->use_package_forbidden) {
        *result = NULL;
        status  = JULIE_ERR_USE_PACKAGE_FORBIDDEN;
        julie_make_interp_error(interp, expr, status);
        goto out;
    }

    status = julie_args(interp, expr, "s", n_values, values, &name);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    name_string = julie_value_string_id(interp, name);
    julie_free_value(interp, name);

    status = julie_load_package(interp, name_string->chars, result);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        julie_make_load_package_error(interp, expr, status, name_string->chars, dlerror());
        goto out;
    }

out:;
    return status;
}

static Julie_Status julie_builtin_add_package_directory(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status        status;
    Julie_Value        *path;
    const Julie_String *pstring;

    if (interp->add_package_directory_forbidden) {
        *result = NULL;
        status  = JULIE_ERR_USE_PACKAGE_FORBIDDEN;
        julie_make_interp_error(interp, expr, status);
        goto out;
    }

    status = julie_args(interp, expr, "s", n_values, values, &path);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    pstring = julie_get_string(interp, path->string_id);
    julie_free_value(interp, path);

    julie_add_package_directory(interp, pstring->chars);

    *result = julie_string_value(interp, pstring->chars);

out:;
    return status;
}

static Julie_Status julie_builtin_argv(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    char         *arg;

    status = JULIE_SUCCESS;

    (void)values;
    if (n_values != 0) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 0, n_values, 0);
        *result = NULL;
        goto out;
    }

    *result = julie_list_value(interp);

    ARRAY_FOR_EACH(interp->argv, arg) {
        JULIE_ARRAY_PUSH((*result)->list, julie_string_value(interp, arg));
    }

out:;
    return status;
}

static Julie_Status julie_builtin_exit(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *exit_code;
    int           code;

    (void)expr;

    *result   = NULL;
    exit_code = NULL;

    if (n_values >= 1) {
        status = julie_eval(interp, values[0], &exit_code);
        if (status != JULIE_SUCCESS) {
            *result = NULL;
            goto out;
        }

        if (exit_code->type != _JULIE_INTEGER) {
            status = JULIE_ERR_TYPE;
            julie_make_type_error(interp, exit_code, _JULIE_INTEGER, exit_code->type);
            goto out_free;
        }
    }

    if (exit_code == NULL) {
        code = 0;
    } else if (exit_code->type == JULIE_SINT) {
        code = (int)exit_code->sint;
    } else if (exit_code->type == JULIE_UINT) {
        code = (int)exit_code->uint;
    } else {
        code = 0;
    }

    exit(code);

out_free:;
    if (exit_code != NULL) {
        julie_free_value(interp, exit_code);
    }

out:;
    return status;
}

static Julie_Status julie_builtin_rand(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status status;

    status = JULIE_SUCCESS;

    (void)values;
    if (n_values != 0) {
        status = JULIE_ERR_ARITY;
        julie_make_arity_error(interp, expr, 0, n_values, 0);
        *result = NULL;
        goto out;
    }

    *result = julie_sint_value(interp, random());

out:;
    return status;
}

static Julie_Status julie_builtin_abs(Julie_Interp *interp, Julie_Value *expr, unsigned n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status  status;
    Julie_Value  *f;

    status = julie_args(interp, expr, "f", n_values, values, &f);
    if (status != JULIE_SUCCESS) {
        *result = NULL;
        goto out;
    }

    *result = julie_float_value(interp, fabs(f->floating));

    julie_free_value(interp, f);

out:;
    return status;
}

/*********************************************************
 *                        Interp                         *
 *********************************************************/

static Julie_Status julie_eval(Julie_Interp *interp, Julie_Value *value, Julie_Value **result);

static Julie_Status _julie_invoke_with_cxt(Julie_Interp *interp, Julie_Apply_Context *cxt, Julie_Value *expr, Julie_Value *fn, Julie_Value **result) {
    Julie_Status              status;
    unsigned                  n_values;
    Julie_Value             **values;
    int                       pushed_symtab;
    Julie_Closure_Info       *closure;
    Julie_String_ID           cap_sym;
    Julie_Value             **cap_valp;
    Julie_Value              *cap_val;
    int                       no_param_lambda;
    unsigned long long        n_params;
    Julie_Value             **params;
    Julie_Value              *param_list;
    int                       vargs;
    Julie_Array              *arg_vals;
    unsigned                  i;
    Julie_Value              *ev;
    Julie_Value              *rest;
    Julie_Value              *cpy;
    Julie_Value              *arg_sym;
    Julie_String_ID           id;
    Julie_Value              *val;
    unsigned long long        n_exprs;
    int                       transient_to_ref;

    status = JULIE_SUCCESS;

    n_values = julie_array_len(cxt->args);
    values   = (Julie_Value**)(cxt->args == JULIE_ARRAY_INIT ? NULL : cxt->args->data);

    /* Evaluate function application. */
    switch (fn->type) {
        case JULIE_BUILTIN_FN:
            status = fn->builtin_fn(interp, expr, n_values, values, result);
            interp->last_popped_builtin_fn = fn->builtin_fn;
            break;
        case JULIE_FN:
        case JULIE_LAMBDA:
            no_param_lambda = fn->type == JULIE_LAMBDA && julie_array_len(fn->list) == 1;

            if (no_param_lambda) {
                n_params = 0;
                params   = NULL;
            } else {
                param_list = julie_array_elem(fn->list, 0);
                JULIE_ASSERT(param_list->type == JULIE_LIST);

                n_params = julie_array_len(param_list->list);
                params   = (Julie_Value**)param_list->list->data;
            }

            vargs =    n_params > 0
                    && julie_value_string_id(interp, ((Julie_Value*)julie_array_elem(param_list->list, n_params - 1))) == interp->ellipses_id;

            if ((!vargs && n_values != n_params)
            ||  (vargs  && n_values < n_params - 1)) {

                status = JULIE_ERR_ARITY;
                julie_make_arity_error(interp, expr, vargs ? n_params - 1 : n_params, n_values, !!vargs);
                *result = NULL;
                goto out;
            }

            pushed_symtab = 0;

            arg_vals = JULIE_ARRAY_INIT;
            JULIE_ARRAY_RESERVE(arg_vals, n_params);

            for (i = 0; i < n_params - !!vargs; i += 1) {
                status = julie_eval(interp, values[i], &ev);
                if (status != JULIE_SUCCESS) { goto cleanup; }
                JULIE_ARRAY_PUSH(arg_vals, ev);
            }

            if (vargs) {
                rest = julie_list_value(interp);
                for (; i < n_values; i += 1) {
                    status = julie_eval(interp, values[i], &ev);
                    if (status != JULIE_SUCCESS) {
                        julie_free_value(interp, rest);
                        goto cleanup;
                    }
                    if (ev->owned || ev->source_node) {
                        cpy = julie_force_copy(interp, ev);
                        julie_free_value(interp, ev);
                        JULIE_ARRAY_PUSH(rest->list, cpy);
                    } else {
                        JULIE_ARRAY_PUSH(rest->list, ev);
                    }
                }
                JULIE_ARRAY_PUSH(arg_vals, rest);
            }

            julie_push_local_symtab(interp);
            pushed_symtab = 1;

            if (fn->type == JULIE_LAMBDA) {
                closure = julie_array_get_aux(fn->list);
                hash_table_traverse(closure->captures, cap_sym, cap_valp) {
                    cap_val = julie_force_copy(interp, *cap_valp);
                    status  = julie_bind_local(interp, cap_sym, &cap_val);

                    if (status != JULIE_SUCCESS) {
                        julie_make_bind_error(interp, cap_val, status, cap_sym);
                        goto cleanup;
                    }
                }
            }

            i = 0;
            ARRAY_FOR_EACH(arg_vals, ev) {
                arg_sym = params[i];
                JULIE_ASSERT(arg_sym->type == JULIE_SYMBOL);

                id = julie_value_string_id(interp, arg_sym);

                if (julie_symbol_starts_with_ampersand(interp, id) && !ev->owned) {
                    ev->owned = 1;
                    arg_vals->data[i] = (void*)((unsigned long long)ev | 0x1);
                }

                status = julie_bind_local(interp, id, &ev);

                if (status != JULIE_SUCCESS) {
                    julie_make_bind_error(interp, values[i], status, id);
                    goto cleanup;
                }

                i += 1;
            }

            n_exprs = julie_array_len(fn->list) - !no_param_lambda;

            for (i = 0; i < n_exprs; i += 1) {
                val = julie_array_elem(fn->list, i + !no_param_lambda);

                JULIE_BORROW_NO_CHECK(val);

                status = julie_eval(interp, val, &ev);
                if (status != JULIE_SUCCESS) {
                    JULIE_UNBORROW_NO_CHECK(val);
                    goto cleanup;
                }

                if (i == n_exprs - 1) {
                    if (!ev->owned) {
                        *result = ev;
                    } else {
                        *result = julie_force_copy(interp, ev);
                        julie_free_value(interp, ev);
                    }
                } else {
                    julie_free_value(interp, ev);
                }

                JULIE_UNBORROW_NO_CHECK(val);
            }

cleanup:;
            if (status == JULIE_SUCCESS) {
                status = julie_pop_local_symtab(interp, &id);
                if (status != JULIE_SUCCESS) {
                    *result = NULL;
                    julie_make_bind_error(interp, expr, status, id);
                }
            } else {
                if (pushed_symtab) {
                    julie_pop_local_symtab(interp, NULL);
                }
                *result = NULL;
            }

            ARRAY_FOR_EACH(arg_vals, ev) {
                transient_to_ref = !!((unsigned long long)ev & 0x1);
                ev = (void*)((unsigned long long)ev & ~0x1);

                if (transient_to_ref) {
                    ev->owned = 0;
                    julie_force_free_value(interp, ev);
                }
            }
            julie_array_free(arg_vals);

            break;

        case JULIE_LIST:
            if (n_values == 0) {
                status = julie_eval(interp, fn, result);
            } else {
                status = _julie_builtin_elem(interp, expr, fn, n_values, values, result);
            }
            break;

        case JULIE_OBJECT:
            if (n_values == 0) {
                status = julie_eval(interp, fn, result);
            } else {
                status = _julie_builtin_field(interp, expr, fn, n_values, values, result);
            }
            break;

        default:
            JULIE_ASSERT(0);
            break;
    }

out:;
    return status;
}

static Julie_Status julie_invoke(Julie_Interp *interp, Julie_Value *expr, Julie_Value *fn, unsigned long long n_values, Julie_Value **values, Julie_Value **result) {
    Julie_Status             status;
    Julie_Apply_Context     *cxt;
    unsigned long long       i;
    Julie_Source_Value_Info *source_info;

    cxt = julie_push_cxt(interp, expr);

    /* Set up backtrace frame. */
    source_info = julie_get_source_value_info(expr);
    if (likely(source_info != NULL)
    ||  (source_info = julie_get_top_source_value_info(interp)) != NULL) {

        cxt->bt_entry.file_id = source_info->file_id;
        cxt->bt_entry.line    = source_info->line;
        cxt->bt_entry.col     = source_info->col;
    } else {
        memset(&cxt->bt_entry, 0, sizeof(cxt->bt_entry));
    }
    cxt->bt_entry.fn = fn;

    for (i = 0; i < n_values; i += 1) {
        JULIE_ARRAY_PUSH(cxt->args, values[i]);
    }

    status = _julie_invoke_with_cxt(interp, cxt, expr, fn, result);

    julie_pop_cxt(interp);

    return status;
}

static Julie_Status julie_apply(Julie_Interp *interp, Julie_Value *list, Julie_Value **result) {
    Julie_Status             status;
    Julie_Apply_Context     *cxt;
    Julie_Value             *fn;
    unsigned long long       list_len;
    Julie_Value             *maybe_infix_fn;
    Julie_String_ID          id;
    Julie_Value             *lookup;
    unsigned                 i;
    Julie_Source_Value_Info *source_info;

    status = JULIE_SUCCESS;

    cxt = julie_push_cxt(interp, list);

    /* Set up backtrace frame. */
    source_info = julie_get_source_value_info(list);
    if (likely(source_info != NULL)
    ||  (source_info = julie_get_top_source_value_info(interp)) != NULL) {

        cxt->bt_entry.file_id = source_info->file_id;
        cxt->bt_entry.line    = source_info->line;
        cxt->bt_entry.col     = source_info->col;
    } else {
        memset(&cxt->bt_entry, 0, sizeof(cxt->bt_entry));
    }
    cxt->bt_entry.fn = julie_array_elem(list->list, 0);

    /* Get the function value. */
    fn = NULL;

    list_len = julie_array_len(list->list);

    /* Check for infix. */
    if (list->tag != JULIE_REARRANGED_INFIX_SOURCE_LIST && list_len == 3) {
        maybe_infix_fn = julie_array_elem(list->list, 1);

        if (likely(maybe_infix_fn->type == JULIE_SYMBOL)) {
            id = julie_value_string_id(interp, maybe_infix_fn);

            if (likely(!julie_symbol_starts_with_single_quote(interp, id))) {
                lookup = julie_lookup(interp, id);
                if (lookup != NULL && lookup->tag == JULIE_INFIX_FN) {
                    fn = lookup;
infix_args:;
                    cxt->bt_entry.fn = fn;
                    JULIE_ARRAY_PUSH(cxt->args, julie_array_elem(list->list, 0));
                    JULIE_ARRAY_PUSH(cxt->args, julie_array_elem(list->list, 2));

                    if (list->source_node) {
                        XOR_SWAP_PTR(list->list->data[0], list->list->data[1]);
                        list->tag = JULIE_REARRANGED_INFIX_SOURCE_LIST;
                    }

                    goto invoke;
                }
            }
        } else if (unlikely(maybe_infix_fn->tag == JULIE_INFIX_FN)) {
            fn = julie_copy(interp, maybe_infix_fn);
            goto infix_args;
        }
    }


    /* Function value is first element of list -- eval. */
    status = julie_eval(interp, julie_array_elem(list->list, 0), &fn);
    if (status != JULIE_SUCCESS) {
        goto out;
    }
    cxt->bt_entry.fn = fn;

    for (i = 1; i < list_len; i += 1) {
        JULIE_ARRAY_PUSH(cxt->args, julie_array_elem(list->list, i));
    }

invoke:;
    /* Evaluate function application. */
    switch (fn->type) {
        case JULIE_BUILTIN_FN:
        case JULIE_FN:
        case JULIE_LAMBDA:
        case JULIE_LIST:
        case JULIE_OBJECT:
            status = _julie_invoke_with_cxt(interp, cxt, list, fn, result);
            break;
        default:
            if (likely(julie_array_len(cxt->args) == 0)) {
                status = julie_eval(interp, fn, result);
            } else {
                status = JULIE_ERR_BAD_APPLY;
                julie_make_bad_apply_error(interp, fn, fn->type);
            }
            break;
    }

    if (likely(*result != fn)) {
        julie_free_value(interp, fn);
    }

out:;
    julie_pop_cxt(interp);

    return status;
}

static Julie_Status julie_eval(Julie_Interp *interp, Julie_Value *value, Julie_Value **result) {
    Julie_Status        status;
    unsigned long long  list_len;
    Julie_Value        *orig_value;
    Julie_Value        *first;
    Julie_String_ID     id;

    status = JULIE_SUCCESS;

    *result = NULL;

#ifdef JULIE_ENABLE_EVAL_CALLBACKS
    if (interp->eval_callback != NULL) {
        status = interp->eval_callback(value);
        if (status != JULIE_SUCCESS) {
            julie_make_interp_error(interp, value, status);
            goto out;
        }
    }
#endif

    orig_value = value;

    if (value->type == JULIE_LIST) {
        list_len = julie_array_len(value->list);

        if (unlikely(list_len <= 1)) {
            if (list_len == 1) {
                first = julie_array_elem(value->list, 0);

                if (JULIE_TYPE_IS_NUMBER(first->type)
                ||  first->type == JULIE_STRING
                ||  first->type == JULIE_NIL) {

                    value = first;
                    goto copy;
                }
            } else if (list_len == 0) {
                value = julie_nil_value(interp);
                goto copy;
            }
        }

        status = julie_apply(interp, value, result);

    } else {
        if (value->type == JULIE_SYMBOL) {
            id = julie_value_string_id(interp, value);

            if (!julie_symbol_starts_with_single_quote(interp, id)) {
                if (unlikely((value = julie_lookup(interp, id)) == NULL)) {
                    status = JULIE_ERR_LOOKUP;
                    julie_make_lookup_error(interp, orig_value, id);
                    goto out;
                }
            }
        }

copy:;
        *result = julie_copy(interp, value);
    }

out:;

#ifdef JULIE_ENABLE_EVAL_CALLBACKS
    if (interp->post_eval_callback != NULL && status == JULIE_SUCCESS) {
        status = interp->post_eval_callback(status, orig_value, result);
        if (status != JULIE_SUCCESS) {
            julie_make_interp_error(interp, orig_value, status);
            goto out;
        }
    }
#endif

    return status;
}


Julie_Status julie_set_error_callback(Julie_Interp *interp, Julie_Error_Callback cb) {
    interp->error_callback = cb;
    return JULIE_SUCCESS;
}

Julie_Status julie_set_output_callback(Julie_Interp *interp, Julie_Output_Callback cb) {
    interp->output_callback = cb;
    return JULIE_SUCCESS;
}

Julie_Status julie_set_eval_callback(Julie_Interp *interp, Julie_Eval_Callback cb) {
#ifdef JULIE_ENABLE_EVAL_CALLBACKS
    interp->eval_callback = cb;
    return JULIE_SUCCESS;
#else
    return JULIE_ERR_NO_EVAL_CALLBACKS;
#endif
}

Julie_Status julie_set_post_eval_callback(Julie_Interp *interp, Julie_Post_Eval_Callback cb) {
#ifdef JULIE_ENABLE_EVAL_CALLBACKS
    interp->post_eval_callback = cb;
    return JULIE_SUCCESS;
#else
    return JULIE_ERR_NO_EVAL_CALLBACKS;
#endif
}

Julie_Status julie_set_argv(Julie_Interp *interp, int argc, char **argv) {
    char *arg;
    int   i;

    ARRAY_FOR_EACH(interp->argv, arg) {
        free(arg);
    }
    julie_array_free(interp->argv);

    interp->argv = JULIE_ARRAY_INIT;

    for (i = 0; i < argc; i += 1) {
        JULIE_ARRAY_PUSH(interp->argv, strdup(argv[i]));
    }

    return JULIE_SUCCESS;
}

Julie_Status julie_set_cur_file(Julie_Interp *interp, Julie_String_ID id) {
    interp->cur_file_id = id;
    return JULIE_SUCCESS;
}

Julie_Status julie_add_package_directory(Julie_Interp *interp, const char *path) {
    char *home;
    char  buff[4096];

    if (path[0] == '~') {
        home = getenv("HOME");

        if (home != NULL) {
            snprintf(buff, sizeof(buff), "%s%s", home, path + 1);
            path = buff;
        }
    }

    JULIE_ARRAY_PUSH(interp->package_dirs, (void*)julie_get_string(interp, julie_get_string_id(interp, path)));

    return JULIE_SUCCESS;
}

Julie_Status julie_load_package(Julie_Interp *interp, const char *name, Julie_Value **result) {
    Julie_Status         status;
    const Julie_String  *dir;
    unsigned             i;
    char                 buff[4096];
    void                *handle;
    unsigned             idx;
    void                *it;
    Julie_Value *      (*init)(Julie_Interp*);
    Julie_Value         *val;

    status = JULIE_SUCCESS;

    if (result != NULL) { *result = NULL; }

    snprintf(buff, sizeof(buff), "./%s.so", name);

    if (access(buff, F_OK) >= 0) {
        handle = dlopen(buff, RTLD_LAZY);

        if (handle == NULL) {
            status = JULIE_ERR_LOAD_PACKAGE_FAILURE;
            goto out;
        } else {
            goto found_handle;
        }
    }

    if (julie_array_len(interp->package_dirs) > 0) {
        for (i = julie_array_len(interp->package_dirs); i > 0; i -= 1) {
            dir = julie_array_elem(interp->package_dirs, i - 1);

            snprintf(buff, sizeof(buff), "%s/%s.so", dir->chars, name);

            if (access(buff, F_OK) == -1) { continue; }

            handle = dlopen(buff, RTLD_LAZY);

            if (handle == NULL) {
                status = JULIE_ERR_LOAD_PACKAGE_FAILURE;
                goto out;
            } else {
                goto found_handle;
            }
        }
    }

    handle = dlopen(buff, RTLD_LAZY); /* get dl to create an error */
    status = JULIE_ERR_LOAD_PACKAGE_FAILURE;
    goto out;

found_handle:;
    idx = 0;
    ARRAY_FOR_EACH(interp->package_handles, it) {
        if (it == handle) {
            dlclose(handle);
            if (result != NULL) {
                *result = julie_force_copy(interp, julie_array_elem(interp->package_values, idx));
            }
            goto out;
        }
        idx += 1;
    }
    *(void**)(&init) = dlsym(handle, "julie_init_package");
    if (init == NULL) {
        *result = NULL;
        status = JULIE_ERR_LOAD_PACKAGE_FAILURE;
        goto out;
    }

    val = init(interp);

    JULIE_ARRAY_PUSH(interp->package_handles, handle);
    JULIE_ARRAY_PUSH(interp->package_values,  val);

    if (result != NULL) {
        *result = julie_force_copy(interp, val);
    }

out:;
    return status;
}


Julie_Interp *julie_init_interp(void) {
    Julie_Interp *interp;
    int           i;

    srandom(time(NULL));

    posix_memalign((void**)&interp, 64, sizeof(*interp));

    memset(interp, 0, sizeof(*interp));

    interp->strings     = hash_table_make_e(Char_Ptr, Julie_String_ID, julie_charptr_hash, julie_charptr_equ);

    interp->ellipses_id = julie_get_string_id(interp, "...");

    interp->global_symtab = julie_new_symtab();
    interp->local_symtab_stack = JULIE_ARRAY_INIT;

    interp->value_stack    = JULIE_ARRAY_INIT;
    interp->roots          = JULIE_ARRAY_INIT;
    interp->iter_vals      = JULIE_ARRAY_INIT;
    interp->source_infos   = JULIE_ARRAY_INIT;
    interp->apply_contexts = JULIE_ARRAY_INIT;

    interp->nil_value               = JULIE_NEW();
    interp->nil_value->type         = JULIE_NIL;
    interp->nil_value->tag          = 0;
    interp->nil_value->source_node  = 1;
    interp->nil_value->owned        = 0;
    interp->nil_value->borrow_count = 0;

    interp->__class___value               = JULIE_NEW();
    interp->__class___value->type         = JULIE_SYMBOL;
    interp->__class___value->string_id    = julie_get_string_id(interp, "'__class__");
    interp->__class___value->tag          = JULIE_STRING_TYPE_INTERN;
    interp->__class___value->source_node  = 1;
    interp->__class___value->owned        = 0;
    interp->__class___value->borrow_count = 0;

    for (i = 0; i < JULIE_SINT_VALUE_CACHE_SIZE; i += 1) {
        interp->sint_values[i]               = JULIE_NEW();
        interp->sint_values[i]->type         = JULIE_SINT;
        interp->sint_values[i]->sint         = i;
        interp->sint_values[i]->tag          = 0;
        interp->sint_values[i]->source_node  = 1;
        interp->sint_values[i]->owned        = 0;
        interp->sint_values[i]->borrow_count = 0;
    }

    interp->argv            = JULIE_ARRAY_INIT;

    interp->package_dirs    = JULIE_ARRAY_INIT;
    interp->package_handles = JULIE_ARRAY_INIT;
    interp->package_values  = JULIE_ARRAY_INIT;

    interp->compiled_regex  = hash_table_make(Julie_String_ID, regex_t, julie_string_id_hash);

#define JULIE_BIND_FN(_name, _fn)       julie_bind_fn(interp, julie_get_string_id(interp, (_name)), (_fn))
#define JULIE_BIND_INFIX_FN(_name, _fn) julie_bind_infix_fn(interp, julie_get_string_id(interp, (_name)), (_fn))

    JULIE_BIND_FN(      "typeof",                julie_builtin_typeof);
    JULIE_BIND_FN(      "sint",                  julie_builtin_sint);
    JULIE_BIND_FN(      "uint",                  julie_builtin_uint);
    JULIE_BIND_FN(      "float",                 julie_builtin_float);
    JULIE_BIND_FN(      "string",                julie_builtin_string);
    JULIE_BIND_FN(      "`",                     julie_builtin_id);
    JULIE_BIND_FN(      "'",                     julie_builtin_quote);

    JULIE_BIND_INFIX_FN("=",                     julie_builtin_assign);
    JULIE_BIND_INFIX_FN(":=",                    julie_builtin_assign_global);
    JULIE_BIND_FN(      "unref",                 julie_builtin_unref);
    JULIE_BIND_FN(      "is-bound",              julie_builtin_is_bound);
    JULIE_BIND_FN(      "move",                  julie_builtin_move);

    JULIE_BIND_INFIX_FN("+",                     julie_builtin_add);
    JULIE_BIND_INFIX_FN("+=",                    julie_builtin_add_assign);
    JULIE_BIND_INFIX_FN("-",                     julie_builtin_sub);
    JULIE_BIND_INFIX_FN("-=",                    julie_builtin_sub_assign);
    JULIE_BIND_INFIX_FN("*",                     julie_builtin_mul);
    JULIE_BIND_INFIX_FN("*=",                    julie_builtin_mul_assign);
    JULIE_BIND_INFIX_FN("/",                     julie_builtin_div);
    JULIE_BIND_INFIX_FN("/=",                    julie_builtin_div_assign);
    JULIE_BIND_INFIX_FN("%",                     julie_builtin_mod);
    JULIE_BIND_INFIX_FN("%=",                    julie_builtin_mod_assign);

    JULIE_BIND_FN(      "~",                     julie_builtin_bit_not);
    JULIE_BIND_INFIX_FN("&",                     julie_builtin_bit_and);
    JULIE_BIND_INFIX_FN("&=",                    julie_builtin_bit_and_assign);
    JULIE_BIND_INFIX_FN("|",                     julie_builtin_bit_or);
    JULIE_BIND_INFIX_FN("|=",                    julie_builtin_bit_or_assign);
    JULIE_BIND_INFIX_FN("^",                     julie_builtin_bit_xor);
    JULIE_BIND_INFIX_FN("^=",                    julie_builtin_bit_xor_assign);
    JULIE_BIND_INFIX_FN("<<",                    julie_builtin_bit_shl);
    JULIE_BIND_INFIX_FN("<<=",                   julie_builtin_bit_shl_assign);
    JULIE_BIND_INFIX_FN(">>",                    julie_builtin_bit_shr);
    JULIE_BIND_INFIX_FN(">>=",                   julie_builtin_bit_shr_assign);

    JULIE_BIND_INFIX_FN("==",                    julie_builtin_equ);
    JULIE_BIND_INFIX_FN("!=",                    julie_builtin_neq);
    JULIE_BIND_INFIX_FN("<",                     julie_builtin_lss);
    JULIE_BIND_INFIX_FN("<=",                    julie_builtin_leq);
    JULIE_BIND_INFIX_FN(">",                     julie_builtin_gtr);
    JULIE_BIND_INFIX_FN(">=",                    julie_builtin_geq);
    JULIE_BIND_FN(      "not",                   julie_builtin_not);
    JULIE_BIND_INFIX_FN("and",                   julie_builtin_and);
    JULIE_BIND_INFIX_FN("or",                    julie_builtin_or);

    JULIE_BIND_FN(      "++",                    julie_builtin_inc);
    JULIE_BIND_FN(      "--",                    julie_builtin_dec);

    JULIE_BIND_FN(      "max",                   julie_builtin_max);
    JULIE_BIND_FN(      "min",                   julie_builtin_min);

    JULIE_BIND_FN(      "list",                  julie_builtin_list);
    JULIE_BIND_FN(      "elem",                  julie_builtin_elem);
    JULIE_BIND_FN(      "last",                  julie_builtin_last);
    JULIE_BIND_FN(      "index",                 julie_builtin_index);
    JULIE_BIND_FN(      "append",                julie_builtin_append);
    JULIE_BIND_FN(      "insert",                julie_builtin_insert);
    JULIE_BIND_FN(      "pop",                   julie_builtin_pop);
    JULIE_BIND_FN(      "erase",                 julie_builtin_erase);
    JULIE_BIND_FN(      "sorted",                julie_builtin_sorted);
    JULIE_BIND_FN(      "sorted-insert",         julie_builtin_sorted_insert);

    JULIE_BIND_FN(      "apply",                 julie_builtin_apply);

    JULIE_BIND_INFIX_FN(":",                     julie_builtin_pair);
    JULIE_BIND_FN(      "pair",                  julie_builtin_pair);

    JULIE_BIND_FN(      "object",                julie_builtin_object);
    JULIE_BIND_FN(      "field",                 julie_builtin_field);
    JULIE_BIND_INFIX_FN("->",                    julie_builtin_delete);
    JULIE_BIND_INFIX_FN("<-",                    julie_builtin_update_object);
    JULIE_BIND_FN(      "get-or-insert",         julie_builtin_get_or_insert_field);
    JULIE_BIND_FN(      "keys",                  julie_builtin_keys);
    JULIE_BIND_FN(      "values",                julie_builtin_values);

    JULIE_BIND_FN(      "define-class",          julie_builtin_define_class);
    JULIE_BIND_FN(      "new-instance",          julie_builtin_new_instance);
    JULIE_BIND_INFIX_FN("@",                     julie_builtin_method_call);

    JULIE_BIND_INFIX_FN("in",                    julie_builtin_in);
    JULIE_BIND_FN(      "len",                   julie_builtin_len);
    JULIE_BIND_FN(      "empty",                 julie_builtin_empty);

    JULIE_BIND_FN(      "select",                julie_builtin_select);
    JULIE_BIND_FN(      "do",                    julie_builtin_do);
    JULIE_BIND_FN(      "if",                    julie_builtin_if);
    JULIE_BIND_FN(      "elif",                  julie_builtin_elif);
    JULIE_BIND_FN(      "else",                  julie_builtin_else);
    JULIE_BIND_FN(      "while",                 julie_builtin_while);
    JULIE_BIND_FN(      "repeat",                julie_builtin_repeat);
    JULIE_BIND_FN(      "foreach",               julie_builtin_foreach);
    JULIE_BIND_FN(      "match",                 julie_builtin_match);

    JULIE_BIND_FN(      "print",                 julie_builtin_print);
    JULIE_BIND_FN(      "println",               julie_builtin_println);
    JULIE_BIND_FN(      "fmt",                   julie_builtin_fmt);
    JULIE_BIND_FN(      "spad",                  julie_builtin_spad);
    JULIE_BIND_FN(      "num-fmt",               julie_builtin_num_fmt);
    JULIE_BIND_FN(      "printf",                julie_builtin_printf);
    JULIE_BIND_FN(      "parse-int",             julie_builtin_parse_int);
    JULIE_BIND_FN(      "parse-hex",             julie_builtin_parse_hex);
    JULIE_BIND_FN(      "parse-float",           julie_builtin_parse_float);

    JULIE_BIND_FN(      "fn",                    julie_builtin_fn);
    JULIE_BIND_FN(      "lambda",                julie_builtin_lambda);

    JULIE_BIND_FN(      "chars",                 julie_builtin_chars);
    JULIE_BIND_FN(      "split",                 julie_builtin_split);
    JULIE_BIND_FN(      "splits",                julie_builtin_splits);
    JULIE_BIND_FN(      "replace",               julie_builtin_replace);
    JULIE_BIND_FN(      "trim",                  julie_builtin_trim);
    JULIE_BIND_FN(      "contains",              julie_builtin_contains);
    JULIE_BIND_FN(      "startswith",            julie_builtin_startswith);
    JULIE_BIND_FN(      "endswith",              julie_builtin_endswith);
    JULIE_BIND_FN(      "substr",                julie_builtin_substr);
    JULIE_BIND_INFIX_FN("=~",                    julie_builtin_regex_match);

    JULIE_BIND_FN(      "fopen-rd",              julie_builtin_fopen_rd);
    JULIE_BIND_FN(      "fopen-wr",              julie_builtin_fopen_wr);
    JULIE_BIND_FN(      "fclose",                julie_builtin_fclose);
    JULIE_BIND_FN(      "frewind",               julie_builtin_frewind);
    JULIE_BIND_FN(      "fread-line",            julie_builtin_fread_line);
    JULIE_BIND_FN(      "fread-lines",           julie_builtin_fread_lines);
    JULIE_BIND_FN(      "fwrite",                julie_builtin_fwrite);

    JULIE_BIND_FN(      "backtrace",             julie_builtin_backtrace);

//     JULE_BIND_FN(       "eval-file",             julie_builtin_eval_file);
    JULIE_BIND_FN(      "use-package",           julie_builtin_use_package);
    JULIE_BIND_FN(      "add-package-directory", julie_builtin_add_package_directory);

    JULIE_BIND_FN(      "argv",                  julie_builtin_argv);
    JULIE_BIND_FN(      "exit",                  julie_builtin_exit);
    JULIE_BIND_FN(      "rand",                  julie_builtin_rand);
    JULIE_BIND_FN(      "abs",                   julie_builtin_abs);

    return interp;
}

Julie_Status julie_interp(Julie_Interp *interp) {
    Julie_Status  status;
    Julie_Value  *root;
    Julie_Value  *result;

    status = JULIE_SUCCESS;

    ARRAY_FOR_EACH(interp->roots, root) {
        result = NULL;
        status = julie_eval(interp, root, &result);
        if (status != JULIE_SUCCESS) {
            goto out;
        }
        if (result) {
            julie_free_value(interp, result);
        }
    }

out:;
    return status;
}

void julie_free(Julie_Interp *interp) {
    char                    *arg;
    Julie_Value             *it;
    Julie_Symbol_Table      *symtab;
    char                    *key;
    Julie_String_ID         *id;
    unsigned long long       i;
    Julie_Source_Value_Info *info;
    Julie_Apply_Context     *cxt;
    void                    *handle;
    Julie_String_ID          re_id;
    regex_t                 *re;

    ARRAY_FOR_EACH(interp->argv, arg) {
        free(arg);
    }
    julie_array_free(interp->argv);

    for (i = julie_array_len(interp->local_symtab_stack); i > 0; i -= 1) {
        symtab = julie_array_elem(interp->local_symtab_stack, i - 1);
        if (i <= interp->local_symtab_depth) {
            julie_clear_symtab(interp, symtab);
        }
        free(symtab);
    }
    julie_array_free(interp->local_symtab_stack);

    julie_clear_symtab(interp, interp->global_symtab);
    free(interp->global_symtab);

    ARRAY_FOR_EACH(interp->package_values, it) {
        julie_force_free_value(interp, it);
    }
    julie_array_free(interp->package_values);


    ARRAY_FOR_EACH(interp->roots, it) {
        julie_free_source_node(interp, it);
    }
    julie_array_free(interp->roots);

    julie_free_source_node(interp, interp->nil_value);
    julie_free_source_node(interp, interp->__class___value);

    for (i = 0; i < JULIE_SINT_VALUE_CACHE_SIZE; i += 1) {
        julie_free_source_node(interp, interp->sint_values[i]);
    }

    hash_table_traverse(interp->compiled_regex, re_id, re) {
        (void)re_id;
        regfree(re);
    }
    hash_table_free(interp->compiled_regex);

    hash_table_traverse(interp->strings, key, id) {
        (void)key;
        julie_free_string((Julie_String*)julie_get_string(interp, *id));
        free((void*)*id);
    }

    hash_table_free(interp->strings);

    for (i = 0; i < JULIE_STRING_CACHE_SIZE; i += 1) {
        if (interp->string_cache_pointers[i] != NULL) {
            free(interp->string_cache_pointers[i]);
        }
    }

    julie_array_free(interp->iter_vals);

    julie_array_free(interp->value_stack);

    ARRAY_FOR_EACH(interp->source_infos, info) {
        free(info);
    }
    julie_array_free(interp->source_infos);

    ARRAY_FOR_EACH(interp->apply_contexts, cxt) {
        julie_array_free(cxt->args);
        free(cxt);
    }
    julie_array_free(interp->apply_contexts);

    ARRAY_FOR_EACH(interp->package_handles, handle) {
        dlclose(handle);
    }
    julie_array_free(interp->package_handles);

    julie_array_free(interp->package_dirs);

    free(interp);
}


/*********************************************************
 *                         Misc                          *
 *********************************************************/

Julie_Status julie_map_file_into_readonly_memory(const char *path, const char **addr, unsigned long long *size) {
    Julie_Status  status;
    FILE        *f;
    int          fd;
    struct stat  fs;

    status = JULIE_SUCCESS;
    f      = fopen(path, "r");

    if (f == NULL) { status = JULIE_ERR_FILE_NOT_FOUND; goto out; }

    fd = fileno(f);

    if      (fstat(fd, &fs) != 0) { status = JULIE_ERR_FILE_NOT_FOUND; goto out_fclose; }
    else if (S_ISDIR(fs.st_mode)) { status = JULIE_ERR_FILE_IS_DIR;    goto out_fclose; }

    *size = fs.st_size;

    if (*size == 0) {
        *addr = NULL;
        goto out_fclose;
    }

    *addr = mmap(NULL, *size, PROT_READ, MAP_SHARED, fd, 0);

    if (*addr == MAP_FAILED) { status = JULIE_ERR_MMAP_FAILED; goto out_fclose; }

out_fclose:
    fclose(f);

out:
    return status;
}

#undef PARSE_ERR_RET
#undef MORE_INPUT
#undef PEEK_CHAR
#undef SPC
#undef DIG
#undef ALIGN_UP
#undef ALIGN_DOWN
#undef IS_ALIGNED
#undef IS_POWER_OF_TWO
#undef NEXT_POT_2
#undef NEXT_POT_4
#undef NEXT_POT_8
#undef NEXT_POT_16
#undef NEXT_POT_32
#undef NEXT_POT_64
#undef NEXT_POT
#undef CLZ
#undef STR
#undef _STR
#undef CAT2
#undef _CAT2
#undef CAT3
#undef _CAT3
#undef CAT4
#undef _CAT4
#undef hash_table
#undef hash_table_make
#undef hash_table_make_e
#undef hash_table_len
#undef hash_table_free
#undef hash_table_get_key
#undef hash_table_get_val
#undef hash_table_insert
#undef hash_table_delete
#undef hash_table_traverse
#undef _hash_table_slot
#undef hash_table_slot
#undef _hash_table
#undef hash_table
#undef hash_table_pretty_name
#undef _HASH_TABLE_EQU
#undef DEFAULT_START_SIZE_IDX
#undef use_hash_table
#undef STORE_BLOCK_ALIGN

#endif /* JULIE_IMPL */

#endif /* __JULIE_H__ */
