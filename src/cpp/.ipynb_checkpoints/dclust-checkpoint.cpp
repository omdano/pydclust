#include <queue>
#include <limits>
#include <cmath>
#include <Python.h>
#include <numpy/arrayobject.h>
#include <iostream>
#include <experimental_heuristics.h>
#include<map>
#include <string>


const float INF = std::numeric_limits<float>::infinity();

// represents a single pixel
class Node {
  public:
    int pidx; // previous index
    int idx; // index in the flattened grid
    float cost; // cost of traversing this pixel
    int path_length; // the length of the path to reach this node

    Node(int i, float c, int path_length) : idx(i), cost(c), path_length(path_length) {}
};

// the top of the priority queue is the greatest element by default,
// but we want the smallest, so flip the sign
bool operator<(const Node &n1, const Node &n2) {
  return n1.cost > n2.cost;
}

// See for various grid heuristics:
// http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S7
// L_\inf norm (diagonal distance)
inline float linf_norm(int i0, int j0, int i1, int j1) {
  return std::max(std::abs(i0 - i1), std::abs(j0 - j1));
}

// L_1 norm (manhattan distance)
inline float l1_norm(int i0, int j0, int i1, int j1) {
  return std::abs(i0 - i1) + std::abs(j0 - j1);
}




// weights:        flattened h x w grid of costs
// h, w:           height and width of grid
// start, goal:    index of start/goal in flattened grid
// diag_ok:        if true, allows diagonal moves (8-conn.)
// paths (output): for each node, stores previous node in path
static PyObject *dclust(PyObject *self, PyObject *args) {
  const PyArrayObject* edges_object;
  const PyArrayObject* values_object;
  const PyArrayObject* lengths_object;
  const PyArrayObject* locations_object;
  const PyArrayObject* neighbors_object;    
  int m;
  int n;
  int num_clusters;

  if (!PyArg_ParseTuple(
        args, "OOOOOiii, // i = int, O = object
        &edges_object,
        &values_object,
        &lengths_object,
        &locations_object,
        &neighbors_object, &m, &n, &num_clusters
        ))
    return NULL;

  int* edges = (int*) edges_object->data;
  float* values = (float*) values_object->data;
  int* lengths = (int*) lengths_object->data;
  int* locations = (int*) locations_object->data;
  int* neighbors = (int*) neighbors_object->data;


  //PyErr_SetString(PyExc_Warning, (std::to_string(starts[0]) + std::to_string(starts[1]) + std::to_string(starts[2]) + std::to_string(starts[3]) + std::to_string(starts[4])).c_str());
  //PyErr_Print();
  std::map<std::pair<int, int>, float> value_map;

  for (int i=0; i<m; i++)
  {
      value_map.insert({{edges[i*2], edges[i*2+1]}, values[i]});
  }
  //return NULL;
  int* paths = new int[n];
  int path_length = -1;

  float* costs = new float[n];
  float* clust_assign = new int[n];
    
  for (int i = 0; i < n; ++i)
    costs[i] = INF;

  std::priority_queue<Node> nodes_to_visit;
  
  

  

  
  
  
  return return_val;
}






static PyMethodDef dclust_methods[] = {
    {"dclust", (PyCFunction)dclust, METH_VARARGS, "dclust"},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef dclust_module = {
    PyModuleDef_HEAD_INIT,"dclust", NULL, -1, dclust_methods
};

PyMODINIT_FUNC PyInit_dclust(void) {
  import_array();
  return PyModule_Create(&dclust_module);
}

