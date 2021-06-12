#include <Python.h>
#include "dict-common.h"
#define USABLE_FRACTION(n) (((n) << 1)/3)

static PyObject *method_insdict(PyObject *self,PyObject *args){
  int i;
  Py_ssize_t ma_used;
  Py_ssize_t index_tbl_size;
  Py_ssize_t dk_nentries;
  PyDictObject *d;
  PyDictKeysObject *ma_keys;
  PyObject **ma_values;
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, "O", &d)){
    return NULL;
  }
  
  ma_used = d->ma_used;
  ma_keys = d->ma_keys;
  ma_values = d->ma_values;

  index_tbl_size = ma_keys->dk_size;
  dk_nentries = ma_keys->dk_nentries;

  printf("---- Internal state of dictionary ----\n");
  printf("Number of items: \t%lld\n",(long long)ma_used);
  printf("Size of index array: \t%lld\n",(long long)index_tbl_size);
  printf("Size of entry table: \t%lld\n",(long long) USABLE_FRACTION(index_tbl_size));
  printf("Index array: ");
  for(i=0;i<index_tbl_size;i++){
    printf("%lld ",(long long)d->ma_keys->dk_indices[i]);
  }
  printf("\n");
  printf("Number of used entries: %lld\n",(long long)dk_nentries);
  
  return Py_None;
}

static PyMethodDef InsdictMethods[] =
  {
   {"insdict",method_insdict,METH_VARARGS,"Method for inspecting dictionaries"},
   {NULL,NULL,0,NULL}
  };

static struct PyModuleDef insdictmodule =
  {
   PyModuleDef_HEAD_INIT,
   "insdict",
   "Module for inspecting dictionaries",
   -1,
   InsdictMethods
  };

PyMODINIT_FUNC PyInit_insdict(void) {
  return PyModule_Create(&insdictmodule);
}

