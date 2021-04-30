#include <stdio.h>
#include <stdlib.h>
#include <Python.h>
//#include <python2.7/Python.h>

double getTemperature(PyObject *pModule)
{

    double temperature = 0.0;

    PyObject *pFunc = PyObject_GetAttrString(pModule, "getTemperature");
    if (pFunc && PyCallable_Check(pFunc)) {
        PyObject *pValue = PyObject_CallObject(pFunc, NULL);
	temperature = PyFloat_AsDouble(pValue);
	Py_DECREF(pValue);
    } else {
	PyErr_Print();
    }

    Py_DECREF(pFunc);

    return temperature;

}

int main(int argc, char *argv[])
{

    Py_Initialize();

    //PyRun_SimpleString("import sys");
    //PyRun_SimpleString("sys.path.append(\".\")");
    
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");
    PyList_Append(path, PyUnicode_FromString("."));
    
    PyObject *pName = PyUnicode_FromString("senseHatModules");
    if (pName == NULL) {
        PyErr_Print();
	return -1;
    }

    PyObject *pModule = PyImport_Import(pName);
    if (pModule == NULL) {
        PyErr_Print();
	return -1;
    }

    printf("Temperature: %lf \n", getTemperature(pModule));

    Py_Finalize();

    return 0;

}


