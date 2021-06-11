#include <Python.h>
#include "/home/yutaka/GitHub/cpython/Objects/dict-common.h"
//#include "dict-common.h"

static PyObject *method_insdict(PyObject *self,PyObject *args){
  PyDictObject *d;
  /* Parse arguments */
  if(!PyArg_ParseTuple(args, "O", &d)){
    return NULL;
  }

  printf("%d\n",d->ma_keys->dk_indices[0]);
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

