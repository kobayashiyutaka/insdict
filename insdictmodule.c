#include <Python.h>
#include "../cpython/Objects/dict-common.h"
//#include "dict-common.h"

static PyObject *method_insdict(PyObject *self,PyObject *args){
  int i;
  Py_ssize_t ma_used;
  uint8_t index_tbl_size;
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

  index_tbl_size = ma_keys->dk_log2_size;
  dk_nentries = ma_keys->dk_nentries;

  printf("---- Internal state of dictionary ----\n");
  printf("Number of items: \t%lld\n",ma_used);
  printf("Size of index table: \t%d\n",index_tbl_size);
  printf("Index table: ");
  for(i=0;i<index_tbl_size;i++){
    printf("%d ",d->ma_keys->dk_indices[i]);
  }
  printf("\n");
  printf("dk_nentries: %I64d\n",dk_nentries);

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

