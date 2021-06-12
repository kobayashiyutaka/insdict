#include <Python.h>
#include "dict-common.h"

#define USABLE_FRACTION(n) (((n) << 1)/3)
#define DK_SIZE(dk) ((dk)->dk_size)
#if SIZEOF_VOID_P > 4
#define DK_IXSIZE(dk)                          \
    (DK_SIZE(dk) <= 0xff ?                     \
        1 : DK_SIZE(dk) <= 0xffff ?            \
            2 : DK_SIZE(dk) <= 0xffffffff ?    \
                4 : sizeof(int64_t))
#else
#define DK_IXSIZE(dk)                          \
    (DK_SIZE(dk) <= 0xff ?                     \
        1 : DK_SIZE(dk) <= 0xffff ?            \
            2 : sizeof(int32_t))
#endif
#define DK_ENTRIES(dk) \
    ((PyDictKeyEntry*)(&((int8_t*)((dk)->dk_indices))[DK_SIZE(dk) * DK_IXSIZE(dk)]))

static PyObject *method_insdict(PyObject *self,PyObject *args){

  int i;
  Py_ssize_t ma_used;
  Py_ssize_t index_tbl_size;
  Py_ssize_t dk_nentries;
  Py_ssize_t dk_usable;
  PyDictObject *d;
  PyDictKeysObject *ma_keys;
  PyObject **ma_values;
  int dict_type;
  PyDictKeyEntry *dk_entries;
  
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, "O", &d)){
    return NULL;
  }
  
  /* Check if the argument is a dictionary */
  if(!PyDict_Check(d)){
    PyErr_SetString(PyExc_TypeError,"argument must be a dictionary");
    return NULL;
  }
  
  ma_used = d->ma_used;
  ma_keys = d->ma_keys;
  ma_values = d->ma_values;
  index_tbl_size = ma_keys->dk_size;
  dk_nentries = ma_keys->dk_nentries;
  dk_usable = ma_keys->dk_usable;
  dk_entries = DK_ENTRIES(ma_keys);

  /* Insepcting the dictionary type */
  if(ma_values==NULL){
    dict_type = 0;  // combined
  } else {
    dict_type = 1;  // split
  }

  printf("---- Internal state of dictionary ----\n");
  if(dict_type==0){
    printf("Dictionary type: combined\n");
  } else {
    printf("Dictionary type: split\n");
  }
  printf("Number of items: \t%llu\n",(unsigned long long)ma_used);
  printf("Size of index array: \t%llu\n",(unsigned long long)index_tbl_size);
  printf("Size of entry table: \t%llu\n",(unsigned long long) USABLE_FRACTION(index_tbl_size));
  printf("Index array: ");
  for(i=0;i<index_tbl_size;i++){
    printf("%lld ",(long long)d->ma_keys->dk_indices[i]);
  }
  printf("\n");
  printf("Number of used entries: %llu\n",(unsigned long long)dk_nentries);
  printf("Number of usable entries: %llu\n",(unsigned long long)dk_usable);

  if(dict_type==0){
    printf("Entry table:\n");
    printf("|----|----------------|------|----------------|----------------|\n");
    printf("|slot|hash(key) 8bytes|masked|     &key 8bytes|   &value 8bytes|\n");
    printf("|----|----------------|------|----------------|----------------|\n");
    for(i=0;i<USABLE_FRACTION(index_tbl_size);i++){
      printf("|%4d|%16llx|%6lld|%p|%p|\n",i,(long long)dk_entries[i].me_hash,
	     (long long)(dk_entries[i].me_hash & (index_tbl_size-1)),
	     dk_entries[i].me_key,
	     dk_entries[i].me_value);
    }
  }
  
  return Py_None;
}

static PyMethodDef InsdictMethods[] =
  {
   {"insdict",method_insdict,METH_VARARGS,\
   "Method for inspecting the internal state of a dictionary"},
   {NULL,NULL,0,NULL}
  };

static struct PyModuleDef insdictmodule =
  {
   PyModuleDef_HEAD_INIT,
   "insdict",
   "Module for inspecting the internal state of a dictionary",
   -1,
   InsdictMethods
  };

PyMODINIT_FUNC PyInit_insdict(void) {
  return PyModule_Create(&insdictmodule);
}

