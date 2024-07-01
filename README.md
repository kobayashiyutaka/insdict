# insdict 0.1.0

## About

This is a module to explore the internal structure of a dictionary. I'm developing this for a purely pedagogical reason. The module is still under development and hence you should not install it **unless you are a student of my programming course** at the current stage.

## Requirement

- CPython (3.8 <= ver <= 3.10 recommended, does not work for 3.11)
- The same C compiler as used to compile your CPython

For Windows, you need to install Microsoft Visual Studio, which is available for free. For Linux, GCC is required.

## How to install

Clone and cd to the repository. Create and activate an Anaconda or Python virtual environment. (Do not install the module to the default environment.) Then run Python REPL and type:

```python
python setup.py install
```

## How to uninstall

Type on the command line:

```bash
python -m pip uninstall insdict
```

## How to use

Module `insdict` includes a single function whose name is again `insdict`. The following is an example code which prints the internal structure of a dictionary with three entries:

```python
from insdict import *
x = {'foo':123,'bar':456,'baz':789}
insdict(x)
```
